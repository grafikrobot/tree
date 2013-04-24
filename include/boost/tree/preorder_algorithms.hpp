//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file preorder_algorithms.hpp
 * Subtree preorder traversal algorithms
 */

#ifndef BOOST_TREE_PREORDER_ALGORITHMS_HPP
#define BOOST_TREE_PREORDER_ALGORITHMS_HPP

#include <boost/tree/cursor_concepts.hpp>
#include <boost/tree/cursor.hpp>

#include <boost/concept/requires.hpp>

namespace boost {
namespace tree {

using namespace boost_concepts;

/** \addtogroup traversal */
/*\@{*/

struct preorder {
    typedef bidirectional_traversal_tag iterator_category;
};

/**
 * @brief   Preorder successor
 * @param c Cursor to be set to its preorder successor
 * @return	true if the operation succeeded;
 * 			false if c already was the last element in preorder
 * 
 * Note that this is the reverse postorder predecessor. 
 */
template <typename Cursor>
inline
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>))
    ((RootTrackingCursor<Cursor>)),
    (bool)) // return type
successor(preorder, Cursor& c)
{
    // If we have a left child, go there.
    if (!c.to_begin().is_leaf())
        return true;
    
    // No left child. So if we have a right child, go there.
    if (!(++c).is_leaf())
        return true;
    
    // (Here's where we'd need to check if this is the end().)
    
    // No children at all.
    // As we've already visited all the ancestors, we'll move upwards until
    // we find an ancestor that has a right child.
    while (!c.is_root()) { // Doesn't work with subtrees!    
        c.to_parent();
        if (!c.is_root() && !index(c))
            if (!(++c).is_leaf())
                return true;
    }

    return false;
}

/**
 * @brief   Preorder successor
 * @param c Cursor to be set to its preorder successor 
 */
template <typename Cursor>
inline
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>))
    ((RootTrackingCursor<Cursor>)),
    (void)) // return type
successor(preorder, Cursor& c, Cursor& r)
{
    // If we have a left child, go there.
    if (!c.is_leaf() && c!=r) {
        c.to_begin();
        return;
    }
    
    // No left child. So if we have a right child, go there.
    if (!(++c).is_leaf() && c!=r) {
        c.to_begin();
        return;
    }
    
    // (Here's where we'd need to check if this is the end().)
    
    // No children at all.
    // As we've already visited all the ancestors, we'll move upwards until
    // we find an ancestor that has a right child.
    while (!c.is_root()) { // Doesn't work with subtrees!    
        c.to_parent();
        if (!c.is_root() && !index(c)) {
            if (!(++c).is_leaf()) {
                c.to_begin();
                return;
            }
        }
    }
    return;
}

/**
 * @brief   Preorder predecessor
 * @param c Cursor to be set to its preorder predecessor
 * @return	true if the operation succeeded;
 * 			false if c already was the first element in preorder
 * 
 * Note that this is the reverse postorder successor. 
 */
template <class Cursor>
inline
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>))
    ((RootTrackingCursor<Cursor>)),
    (bool)) // return type
predecessor(preorder, Cursor& c)
{
    if (c.is_root())
        return false;

    if (!index(c)) { // Left child? Return parent.
        c.to_parent();
        return true;
    }
        
    // Right child.
    --c;
    while (!c.is_leaf()) {
        c.to_end();
        if (c.is_leaf())
            --c;
    }
    c.to_parent();
    return true;
}

/**
 * @brief   First element of a subtree in preorder traversal
 * @param c Subtree root cursor that will be set to the first preorder 
 *          position in the subtree.
 *
 * Note that this is equivalent to the reverse postorder to_last.
 */
template <class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>)),
    (void)) // return type
to_first(preorder, Cursor& c)
{}

/**
 * @brief   Last element of a subtree in preorder traversal
 * @param c Subtree root cursor that will be set to the last preorder 
 *          position in the subtree.
 *
 * Note that this is equivalent to the reverse postorder to_first.
 */
template <class Cursor>
void to_last(preorder, Cursor& c)
{
    while (!c.is_leaf())
        if (c.to_end().is_leaf())
            --c;
    c.to_parent();
}

/*\@}*/

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_PREORDER_ALGORITHMS_HPP
