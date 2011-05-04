//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file binary_tree.hpp
 * Binary tree implementation
 */

#ifndef BOOST_TREE_BINARY_TREE_HPP
#define BOOST_TREE_BINARY_TREE_HPP

#include <boost/tree/cursor.hpp>
//#include <boost/tree/algorithm.hpp>
#include <boost/tree/insert_cursor.hpp>

#include <boost/tree/detail/node_traits.hpp>
#include <boost/tree/detail/nary_cursor.hpp>

#include <memory>

namespace boost {
namespace tree {

// TODO: Remove shoot() remains (was m_header->m_parent)

/** 
 * @brief A %binary_tree.
 * This class models the hierarchy concept. TODO: complete this...
 *
*/
template < class Tp, class Alloc = std::allocator<Tp> >
class binary_tree {
    typedef binary_tree<Tp, Alloc> self_type;
public:
    typedef Tp value_type;
    typedef typename Alloc::template rebind<value_type>::other allocator_type;
    // Allocator usage roughly follows gcc's stl_list.h practice.

private:        
    typedef detail::ascending_node<value_type> node_type;
    
    typedef typename Alloc::template rebind<node_type>::other 
        node_allocator_type;
    typedef typename detail::node_traits<node_type>::node_base_type node_base_type;
    typedef node_base_type* node_base_pointer;
    typedef typename detail::node_traits<node_type>::node_pointer node_pointer;
    
public:
    typedef detail::ascending_nary_cursor<node_type> cursor;
    typedef detail::ascending_nary_cursor<node_type const> const_cursor;

    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;
    
    template <class U> struct rebind {
      typedef binary_tree< U, typename allocator_type::template rebind<U>::other >
        other;
    };
    
    explicit binary_tree (allocator_type const& alloc = allocator_type())
    : m_header(), m_node_alloc(alloc) {}

    template <class InputCursor>
    binary_tree(InputCursor subtree, 
                allocator_type const& alloc = allocator_type())
    : m_header(), m_node_alloc(alloc)
    {
        insert(root(), subtree);
    }
    
    /**
     * @brief  Binary tree copy constructor.
     * @param  x  A %binary_tree of identical element and allocator types.
     * The newly-created %binary_tree uses a copy of the allocation object used
     * by @a x.
     */

    binary_tree (self_type const& x)
    : m_header(), m_node_alloc(x.m_node_alloc)
    {
        if (!x.empty())
            insert(root(), x.root());
    }
    
    ~binary_tree()
    {
        this->clear();
    }
    
    /**
     * @brief  Binary tree assignment operator.
     * @param  x  A %binary_tree of identical element and allocator types.
     * 
     * All the elements of @a x are copied, but unlike the
     * copy constructor, the allocator object is not copied.
     */
    binary_tree<Tp, Alloc>& operator=(binary_tree<Tp, Alloc> const& x)
    {
        binary_tree temp(x);
        swap(temp);
        return *this;
    }
    
    template <class InputCursor>
    void assign(InputCursor subtree)
    {
        clear();
        insert(this->root(), subtree);
    }

    /// Get a copy of the memory allocation object.
    allocator_type get_allocator() const
    {
        return allocator_type(m_node_alloc);
    }
    
    /// Functions returning cursors (as required by the Hierarchy concept)
    
    /**
     * Returns a read/write ("mutable") cursor to the %binary_tree's root.
     */     
    cursor root()
    {
        return cursor(&m_header, 0);
    }

    /**
     * Returns a read-only const_cursor to the %binary_tree's root.
     */     
    const_cursor root() const
    {
        return croot();
    }
    
    /**
     * Returns a read-only const_cursor to the %binary_tree's root.
     */     
    const_cursor croot() const
    {
        return const_cursor(&m_header, 0);
    }
    
//    /**
//     * Returns a read/write ("mutable") cursor to the first (inorder) value.
//     */      
//    cursor inorder_first()
//    {
//        return cursor(&m_header, 1);
//    }
//    
//    /**
//     * Returns a read-only const_cursor to the first (inorder) value.
//     */      
//    const_cursor inorder_first() const
//    {
//        return inorder_cfirst();
//    }
//
//    /**
//     * Returns a read-only const_cursor to the first (inorder) value.
//     */      
//    const_cursor inorder_cfirst() const
//    {
//        return const_cursor(&m_header, 1);
//    }
    
    /**
     * Returns true if the %binary_tree is empty.
     */
    bool empty() const
    {
        return root().is_leaf(); //m_header.m_children[1] == &m_header;
    }
    
    // Hierarchy-specific
    
    /**
     * @brief       Inserts val in front of @a pos, or, if @a pos' parent is
     *              already full, creates a new child node containing @a val 
     *              instead.
     * @param pos   The %binary_tree cursor in front of which to insert.
     * @param val   The value to insert.
     * @return      A cursor that points to the inserted data.
     */
    cursor insert(cursor pos, value_type const& val)
    {
        void* node_hint = 0;
        
        node_pointer p_node = m_node_alloc.allocate(1, node_hint);
        //m_node_alloc.construct(p_node, val);
        *p_node = node_type(val);
        
        detail::attach(pos.parent_node(), pos.child_node(), p_node, p_node->m_children[pos.index()]);

        // Readjust begin
//        if ((pos == this->inorder_first()))
//            m_header.m_children[1] = p_node; 

        return pos; 
    }

    // TODO: Optimise. Especially wrt header links. 
    // Making the other insert() a special case of this one might be more
    // reasonable -- cf. gcc's C++0X optimisations wrt sequence ctors.
    /**
     * @brief       Inserts val in front of @a pos, or, if @a pos' parent is
     *              already full, creates a new child node containing @a val 
     *              instead.
     * @param pos   The %binary_tree cursor in front of which to insert.
     * @param val   The value to insert.
     * @return      An cursor that points to the inserted data.
     */
    template <class InputCursor>
    cursor insert(cursor pos, InputCursor subtree)
    {
//    // Optimise insert_cursor (or introduce another class) before using this
//    return cursor(boost::tree::copy(boost::tree::preorder()
//                , subtree 
//                , boost::tree::tree_inserter(*this, pos)
//                , descending_vertical_traversal_tag()));

        //subtree.to_begin();
        insert(pos, *subtree);
        if (!subtree.begin().is_leaf())
            insert(pos.begin(), subtree.begin());
        if (!subtree.end().is_leaf())
            insert(pos.end(), subtree.end());
        return pos;
    }

     /** 
      * @brief      Removes a node and its descendants recursively in postorder
      * @param c    Cursor pointing to the node to be removed.
      */
     // TODO: Take care of header-pointers
    cursor clear(cursor position) 
    {
//    return cursor(boost::tree::for_each(boost::tree::postorder()
//                , direct_cursor(position)
//                , destroy_node
//                , descending_vertical_traversal_tag()));

        if (!position.is_leaf()) {
            node_pointer pos_node = 
                static_cast<node_pointer>(
                    position.child_node()
                );

            size_type parent_idx = index(position.parent());
            
            // recurse
            _clear(position.begin());
            _clear(position.end());

            // Make this node a leaf
            static_cast<node_base_pointer>(pos_node->m_parent)->m_children[parent_idx] = 0;

            m_node_alloc.destroy(pos_node);
            m_node_alloc.deallocate(pos_node, 1);
            
            if (position == root())
                m_header.m_children[0] = 0;
        }
         return position;
    }     

private:    
    void _clear(cursor position) {
        if (!position.is_leaf()) {
            node_pointer pos_node = 
                static_cast<node_pointer>(
                     position.child_node()
                );

            // recurse
            _clear(position.begin());
            _clear(position.end());

            m_node_alloc.destroy(pos_node);
            m_node_alloc.deallocate(pos_node, 1);
         }
    }

public:
    void rotate(cursor& pos)
    {
        detail::rotate(pos.child_node(), pos.parent_node(), pos.index());
    }
    
    /**
     * @brief  Swaps data with another %binary_tree.
     * @param  x  A %binary_tree of the same element and allocator types.
     * 
     * This exchanges the elements between two binary trees in constant time.
     */
    void swap(self_type& other)
    {
        detail::swap_trees(m_header, other.m_header);
    }

    /**
     * @brief Clears all data from the tree.
     */
     void clear()
     {
        clear(this->root());
     }
     
    // splice operations

    /**
     * @brief   Insert contents of another %binary_tree.
     * @param   position    Empty cursor that is going to be the root of the newly
     *                      inserted subtree.
     * @param   x   Source binary_tree.
     * 
     * The elements of @a x are inserted in constant time as the subtree whose
     * root is referenced by @a position.  @a x becomes an empty
     * binary_tree.
     */
    void splice(cursor position, binary_tree& x)
    {
        splice(position, x, x.root());
    }

    /**
     * @brief   Insert contents of another %binary_tree's subtree.
     * @param   position    Empty cursor that is going to be the root of the newly
     *                      inserted subtree.
     * @param   x           Source binary_tree.
     * @param   root        The source subtree.
     * 
     * The elements of @a root (which is subtree of @a x) are inserted in
     * constant time as the subtree whose root is referenced by @a position.
     * @a x becomes an empty binary_tree.
     */
    void splice(cursor position, binary_tree& x, cursor root)
    {
        // x isn't actually used currently...
        detail::splice(position.parent_node(), position.child_node(), root.child_node());
    }

    /**
     * @brief  Erases an element.
     * @param  position  Cursor indicating the element to be erased.
     * @return Child element assuming the erased element's position.
     */
    cursor erase(cursor position)
    {
        node_pointer p_node = static_cast<node_pointer>(position.parent_node());

        detach(position.parent_node(), position.child_node());

        position.parent_node() = static_cast<node_base_pointer>(position.child_node());

        m_node_alloc.destroy(p_node);
        m_node_alloc.deallocate(p_node, 1);

        return position;
    }

private:
    node_base_type m_header;
    node_allocator_type m_node_alloc;
};

/// See boost::tree::binary_tree::swap().
template <class T, class Alloc>
inline void swap(binary_tree<T, Alloc>& x, binary_tree<T, Alloc>& y)
{
    x.swap(y);
}

/**
 *  @brief  Binary tree equality comparison.
 *  @param  x  A %binary_tree.
 *  @param  y  A %binary_tree of the same type as @a x.
 *  @return  True iff the size and elements of the binary trees are equal.
 *
 *  This is an equivalence relation.  It is linear in the size of the
 *  binary trees. Binary trees are considered equivalent if their sizes are equal,
 *  their shapes are equal, and if corresponding elements compare equal.
 */
template <class Tp, class Alloc>
inline bool operator==(binary_tree<Tp, Alloc> const& x 
                     , binary_tree<Tp, Alloc> const& y)
{
     return (size(x.root()) == size(y.root()) && equal(x.root(), y.root()));
}

/// Based on operator==
template <class Tp, class Alloc>
inline bool operator!=(binary_tree<Tp, Alloc> const& x 
                     , binary_tree<Tp, Alloc> const& y)
{
     return (!(x == y));
}

///**
// * @brief   First element of a MultiwayTree in inorder traversal.
// *          O(1) overload for binary_tree
// * @param t A binary_tree
// * @return  Mutable cursor to the first element of @a t in inorder traversal
// */
//template <class T, class Alloc>
//typename binary_tree<T, Alloc>::cursor 
//first_cursor(inorder, binary_tree<T, Alloc>& t)
//{
//    return t.inorder_first();
//}
//
///**
// * @brief   First element of a MultiwayTree in inorder traversal 
// *          (alias of cfirst()). O(1) overload for binary_tree.
// * @param t A binary_tree
// * @return  Read-only cursor to the first element of @a t in inorder traversal
// */
//template <class T, class Alloc>
//typename binary_tree<T, Alloc>::const_cursor 
//first_cursor(inorder, binary_tree<T, Alloc> const& t)
//{
//    return t.inorder_first();
//}
//
///**
// * @brief   First element of a MultiwayTree in inorder traversal.
// *          O(1) overload for binary_tree
// * @param t A binary_tree
// * @return  Read-only cursor to the first element of @a t in inorder traversal
// */
//template <class T, class Alloc>
//typename binary_tree<T, Alloc>::const_cursor 
//cfirst_cursor(inorder, binary_tree<T, Alloc> const& t)
//{
//    return t.inorder_first();
//}

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_BINARY_TREE_HPP
