//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file postorder_algorithms.hpp
 * Subtree postorder traversal algorithms
 */

#ifndef BOOST_TREE_POSTORDER_ALGORITHMS_HPP
#define BOOST_TREE_POSTORDER_ALGORITHMS_HPP

#include <boost/tree/cursor_concepts.hpp>
#include <boost/tree/cursor.hpp>

#include <boost/concept/requires.hpp>

namespace boost {
namespace tree {

using namespace boost_concepts;

/** \addtogroup traversal */
/*\@{*/

struct postorder {
    typedef bidirectional_traversal_tag iterator_category;
};

/**
 * @brief   Postorder successor
 * @param c Cursor to be set to its postorder successor
 * @return	true if the operation succeeded;
 * 			false if c already was the last element in postorder
 * 
 * Note that this is equivalent to the reverse preorder predecessor.
 */
template <class Cursor>
inline
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>))
    ((RootTrackingCursor<Cursor>)),
    (bool)) // return type
successor(postorder, Cursor& c)
{
    if (c.is_root())
        return false;

    if (index(c)) { // Right child? Return parent.
        c.to_parent();
        return true;
    }
        
    // Left child.
    ++c;
    while (!c.is_leaf()) {
        c.to_begin();
        if (c.is_leaf())
            ++c;
    }
    c.to_parent();
    return true;
}

/**
 * @brief   Postorder predecessor
 * @param c Cursor to be set to its postorder predecessor
 * @return	true if the operation succeeded;
 * 			false if c already was the first element in postorder
 * 
 * Note that this is equivalent to the reverse preorder successor.
 */
template <class Cursor>
inline
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>))
    ((RootTrackingCursor<Cursor>)),
    (bool)) // return type
predecessor(postorder, Cursor& c)
{
    if (!c.to_end().is_leaf()) // Right
        return true;
    if (!(--c).is_leaf()) // Left
        return true;
    
    // Move up in the hierarchy until we find a descendant that has a right
    // child (which is what we'll return) or we land at root.
    while (!c.is_root()) {
        c.to_parent();
        if (!c.is_root() && index(c))
            if (!(--c).is_leaf())
                return true;
    }
    return false;
}

/**
 * @brief   First element of a subtree in postorder traversal
 * @param c Subtree root cursor that will be set to the first postorder 
 *          position in the subtree.
 *
 * Note that this is equivalent to the reverse preorder to_last.
 */
template <class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>)),
    (void)) // return type
to_first(postorder, Cursor& c)
{
    Cursor d = c;
    while (true)
        if (!d.is_leaf()) {
            c = d;
            d.to_begin();
        } else if (!(++d).is_leaf()) {
            c = d;
            d.to_begin();
        } else {
            return;
        }
}

/**
 * @brief   Last element of a subtree in postorder traversal
 * @param c Subtree root cursor that will be set to the last postorder 
 *          position in the subtree.
 *
 * Note that this is equivalent to the reverse preorder to_first.
 */
template <class Cursor>
void to_last(postorder, Cursor& c)
{ }

/*\@}*/

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_POSTORDER_ALGORITHMS_HPP
