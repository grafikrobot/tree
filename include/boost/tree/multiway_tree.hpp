//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file multiway_tree.hpp
 * Binary tree based multiway tree implementation
 */


#ifndef BOOST_TREE_MULTIWAY_TREE_HPP
#define BOOST_TREE_MULTIWAY_TREE_HPP

//#include <boost/tree/cursor.hpp>
//#include <boost/tree/binary_tree.hpp>

#include <boost/tree/detail/multiway_cursor.hpp>

#include <boost/tree/nary_tree.hpp>

#include <vector>
//#include <memory>

namespace boost {
namespace tree {

using detail::const_multiway_tree_cursor;
using detail::multiway_tree_cursor;


/** 
 * @brief A %multiway_tree.
 * This class models the hierarchy concept, the container concept and the
 * sequence concept. TODO: complete this...
 *
*/
template <class T, class Hierarchy = nary_tree<std::vector<T> >/*, class Balance,
          class Augment*/>
class multiway_tree {
    typedef multiway_tree<T, Hierarchy> self_type;
 public:
    typedef T value_type;
    typedef Hierarchy hierarchy_type;

//    typedef ascending_node<2, T, typename augmentor::metadata_type, typename balancer::metadata_type> node_type;
    
    typedef typename hierarchy_type::cursor base_cursor;
    typedef typename hierarchy_type::const_cursor base_const_cursor;
    
    typedef multiway_tree_cursor<base_cursor> cursor;
    typedef const_multiway_tree_cursor<base_const_cursor> const_cursor;

//    typedef iterator<inorder, , cursor> iterator;
//    typedef iterator<inorder, , const_cursor> const_iterator;
//    
//    typedef std::reverse_iterator<iterator> reverse_iterator;
//    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    
    typedef typename cursor_pointer<cursor>::type pointer;
    typedef typename cursor_reference<cursor>::type reference;
    typedef typename cursor_size<cursor>::type size_type;
    typedef typename cursor_difference<cursor>::type difference_type;
    
//    typedef typename node_traits<node_type>::node_base_type node_base_type;
//    typedef typename node_traits<node_type>::node_pointer node_pointer;

//    typedef typename ValAlloc::template rebind<value_type>::other 
//        value_allocator_type;
//    typedef typename NodeAlloc::template rebind<node_type>::other 
//        node_allocator_type;

//    multiway_tree()
//    {
//        h.insert(h.root(), );
//    }
    
    explicit multiway_tree(Hierarchy const& hier = Hierarchy()) : h(hier)
    { }
    
    bool is_leaf()
    {
        return h.is_leaf();
    }
    
    size_type size() const
    {
        return h.size();
    }
    

    
    /**
     * Returns a read/write ("mutable") cursor to the %nary_tree's root.
     */     
    cursor root()
    {
        return cursor(h.root());
    }

    /**
     * Returns a read-only const_cursor to the %nary_tree's root.
     */     
    const_cursor root() const
    {
        return croot();
    }
    
    /**
     * Returns a read-only const_cursor to the %nary_tree's root.
     */     
    const_cursor croot() const
    {
        return const_cursor(h.croot());
    }
    
    cursor insert(cursor pos, value_type const& val)
    {
        base_cursor bc = base_cursor(pos);
//        if (bc != h.root())
//            bc = bc.parent();
//if (bc.index())
        //h.insert(bc, val);
        //if (bc == h.root())
        //    bc =
        if (bc->is_leaf()) {
            bc->push_back(val);
            bc.m_pos = 0;
        } 
        else {
            bc->insert((bc->begin()+index(bc)), val);
        }
        return cursor(bc);
        
    }
    
 protected:
    hierarchy_type h;
     
};


} // namespace tree
} // namespace boost

#endif // BOOST_TREE_MULTIWAY_TREE_HPP
