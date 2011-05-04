//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file nary_cursor.hpp
 * Nary cursor implementation
 */

#ifndef BOOST_TREE_DETAIL_NARY_CURSOR_HPP
#define BOOST_TREE_DETAIL_NARY_CURSOR_HPP

#include <boost/tree/cursor.hpp>
#include <boost/tree/cursor_adaptor.hpp>
#include <boost/tree/detail/nary_node.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_pointer.hpp>

namespace boost {
namespace tree {
namespace detail {

using boost::iterator_core_access;
using boost::tree::cursor_core_access;

template <class Node> 
class ascending_nary_cursor
 : public cursor_adaptor<ascending_nary_cursor<Node>
      , typename mpl::eval_if<
                        is_const<Node>
                      , add_const<typename Node::node_base>
                      , mpl::identity<typename Node::node_base>
                    >::type*                  
      , typename mpl::eval_if<
                    is_const<Node>
                  , add_const<typename Node::value_type>
                  , mpl::identity<typename Node::value_type>
                >::type
      , random_access_traversal_tag
      , ascending_vertical_traversal_tag
    > {

private:
    struct enabler {};

    typedef Node node_type;
    typedef node_type* node_pointer;

    typedef typename mpl::eval_if<
                        is_const<Node>
                      , add_const<typename Node::node_base>
                      , mpl::identity<typename Node::node_base>
                    >::type node_base_type;

public:
    typedef typename mpl::eval_if<
                        is_const<Node>
                       , add_const<typename Node::value_type>
                       , mpl::identity<typename Node::value_type>
                    >::type value_type;

    // Container-specific:
    typedef typename ascending_nary_cursor::cursor_adaptor_::size_type size_type;

    // Cursor-specific
    typedef ascending_nary_cursor<node_type> cursor;
    typedef ascending_nary_cursor<node_type const> const_cursor;
    typedef std::size_t subtree_size_type;
    
    // Container-specific:
    typedef cursor iterator;
    typedef const_cursor const_iterator;
    
    template <class OtherValue>
    struct rebind {
        typedef ascending_nary_cursor<OtherValue> other;
    };
    
    ascending_nary_cursor()
      : ascending_nary_cursor::cursor_adaptor_(0), m_pos(0) {}

    explicit ascending_nary_cursor(node_base_type* p, size_type pos) 
    : ascending_nary_cursor::cursor_adaptor_(p), m_pos(pos) {}

    template <class OtherNode>
    ascending_nary_cursor(
        ascending_nary_cursor<OtherNode> const& other
      , typename boost::enable_if<
            boost::is_convertible<typename OtherNode::value_type*, value_type*>
          , enabler
        >::type = enabler()
    )
    : ascending_nary_cursor::cursor_adaptor_(other.base()), m_pos(other.m_pos) {}

private:
    size_type m_pos;

    friend class iterator_core_access;
    friend class cursor_core_access;
    
    friend class access_detach;
    
    value_type& dereference() const
    {
        return **static_cast<node_type*>(this->base_reference()->m_children[m_pos]);
    }
    
    bool equal(cursor const& other) const
    {
        return (this->base_reference() == other.base_reference()) && (this->m_pos == other.m_pos);
    }
    
    void increment()
    {
        ++m_pos;
        // this->base_reference() += sizeof(node_type);
    }
    
    void decrement()
    {
        --m_pos;
        //this->base_reference() -= sizeof(node_type);
    }    
    
    void advance(typename ascending_nary_cursor::cursor_facade_::difference_type n)
    {
        m_pos += n;
        //this->base_reference() += n * sizeof(node_type);
    }
    
    typename ascending_nary_cursor::cursor_facade_::difference_type
    distance_to(ascending_nary_cursor z) const //FIXME: convertible to instead of ascending_nary_cursor
    {
        return (z.m_pos - this->m_pos);
        //return (z.base_reference() - this->base_reference()) / sizeof(node_type); 
    }
    
    // Container specific
    bool empty_() const
    {
        return //this->base_reference()->m_children[m_pos] == node_type::nil() ||
        this->base_reference()->m_children[m_pos] == 0; //->is_leaf()
        //return this->base_reference()->get_index();
    }
    
    size_type size_() const
    {
        return this->base_reference()->m_children.size();
    }
    
    size_type max_size_() const
    {
        return this->base_reference()->m_children.max_size();
    }
    
    size_type idx() const
    {
        return m_pos;
        //return 
    }

    void left()
    {
        this->base_reference() = 
            static_cast<node_base_type*>(this->base_reference()->m_children[m_pos]);
        m_pos  = 0;
        //this->base_reference() = this->base_reference()->operator[0];
    }

    void right()
    {
        size_type new_pos = this->base_reference()->m_children.size()-1; 
        this->base_reference() = 
            static_cast<node_base_type*>(this->base_reference()->m_children[m_pos]);
        m_pos  = new_pos;
        //this->base_reference() = this->base_reference()->operator[0];
    }

    // Cursor stuff
    void up()
    {
        m_pos  = this->base_reference()->get_index();
        this->base_reference() = static_cast<node_base_type*>(this->base_reference()->parent());
        //this->base_reference() = this->base_reference()->parent();
    }
    
//protected:
public:
    bool is_on_top() const
    {
        node_base_type* parent_begin_node = 
            static_cast<node_base_type*>(
            static_cast<node_base_type*>(this->base_reference()->parent())
            ->m_children[this->base_reference()->get_index()]);
        return (!m_pos && (this->base_reference() != parent_begin_node));
        // (*this != this->parent().begin())
    }

    node_base_type* const& parent_node() const
    {
        return this->base_reference();
    }

    node_base_type*& parent_node()
    {
        return this->base_reference();
    }

    typename node_base_type::descending_node_base* const& child_node() const
    {
        return this->base_reference()->m_children[m_pos];
    }

    typename node_base_type::descending_node_base*& child_node()
    {
        return this->base_reference()->m_children[m_pos];
    }

//    /** 
//     * Detaches the node this cursor points to and returns a pointer to it;
//     * this cursor will be set to its inorder successor afterwards (?)
//     */
//    node_pointer detach()
//    {
//        return static_cast<node_pointer>(m_node->detach(m_pos));
//    }
//    
//    node_pointer detach(cursor y)
//    {
//        return static_cast<node_pointer>(m_node->detach(m_pos, y.m_pos, y.m_node));
//    }

};

} // namespace detail

template <class Node>
typename detail::ascending_nary_cursor<Node>::size_type
index(detail::ascending_nary_cursor<Node> const& cur)
{
    return cur.index();
}

} // namespace tree
} // namespace boost


#endif // BOOST_TREE_DETAIL_NARY_CURSOR_HPP
