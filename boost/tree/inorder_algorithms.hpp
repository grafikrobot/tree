//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file inorder_algorithms.hpp
 * Subtree intorder traversal and search algorithms
 */

#ifndef BOOST_TREE_INORDER_ALGORITHMS_HPP
#define BOOST_TREE_INORDER_ALGORITHMS_HPP

#include <boost/tree/general_algorithms.hpp>
#include <boost/tree/cursor_concepts.hpp>
#include <boost/tree/cursor.hpp>

#include <boost/concept/requires.hpp>

#include <algorithm>

namespace boost {
namespace tree {

using namespace boost_concepts;

/** \addtogroup traversal */
/*\@{*/

struct inorder {
    typedef bidirectional_traversal_tag iterator_category;
};

/**
 * @brief	Inorder successor
 * @param c	MultiwayCursor to be set to its inorder successor
 * @return	true if the operation succeeded;
 * 			false if c already was the last element in inorder
 * @ingroup	traversal
 *
 * Note that this is equivalent to the reverse inorder successor.
 */
template <class MultiwayCursor>
inline
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<MultiwayCursor>))
    ((RootTrackingCursor<MultiwayCursor>)),
    (bool)) // return type
successor(inorder, MultiwayCursor& c)
{
    if (!c.to_end().is_leaf()) {
        to_first(inorder(),c);
        return true;
    }

    while (index(c) && !c.is_root())
        c.to_parent();

    if (!c.is_root()) {
        c.to_parent();
        return true;
    }
    else
        return false;
    return true;
}

/**
 * @brief	Inorder predecessor
 * @param c	MultiwayCursor to be set to its inorder predecessor
 * @return	true if the operation succeeded;
 * 			false if c already was the first element in inorder
 *
 * Note that this is equivalent to the reverse inorder predecessor.
 */
template <class MultiwayCursor>
inline
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<MultiwayCursor>))
    ((RootTrackingCursor<MultiwayCursor>)),
    (bool)) // return type
predecessor(inorder, MultiwayCursor& c)
{
	if (!c.to_begin().is_leaf()) {
		to_last(inorder(), c);
		return true;
	}

    while (!index(c) && !c.is_root())
        c.to_parent();

    if (!c.is_root()) {
        c.to_parent();
        return true;
    }
    else
        return false;
}

/**
 * @brief   First element of a subtree in inorder traversal
 * @param c Subtree root cursor that will be set to the first inorder 
 *          position in the subtree.
 *
 * Note that this is equivalent to the reverse inorder to_last.
 */
template <class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>)),
    (void)) // return type
to_first(inorder, Cursor& c)
{
    return to_first(inorder(), c
                  , typename cursor_vertical_traversal<Cursor>::type());
}

template <class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>)),
    (void)) // return type
to_first(inorder, Cursor& c, descending_vertical_traversal_tag)
{
    Cursor d = c;
    while (!d.is_leaf()) {
        c = d;
        d.to_begin();
    }
}

template <class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((AscendingCursor<Cursor>)),
    (void)) // return type
to_first(inorder, Cursor& c, ascending_vertical_traversal_tag)
{
	Cursor d = c;
    to_leftmost(c);
    if (c != d)
		c.to_parent();
}

//template <class Cursor>
//BOOST_CONCEPT_REQUIRES(
//    ((RootTrackingCursor<Cursor>)),
//    (void)) // return type
//to_first(inorder, Cursor& c, root_tracking_vertical_traversal_tag)
//{
//    to_leftmost(c);
//    if (!c.is_root())
//		c.to_parent();
//}

/**
 * @brief   Last element of a subtree in inorder traversal
 * @param c Subtree root cursor that will be set to the last inorder 
 *          position in the subtree.
 *
 * Note that this is equivalent to the reverse inorder to_first.
 */
template <class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>)),
    (void)) // return type
to_last(inorder, Cursor& c)
{
    return to_last(inorder(), c
                  , typename cursor_vertical_traversal<Cursor>::type());
}

template <class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>)),
    (void)) // return type
to_last(inorder, Cursor& c, descending_vertical_traversal_tag)
{
    Cursor d = c;
    while (!d.is_leaf()) {
        c = d;
        d.to_end();
    }
}

template <class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((AscendingCursor<Cursor>)),
    (void)) // return type
to_last(inorder, Cursor& c, ascending_vertical_traversal_tag)
{
	Cursor d = c;
    to_rightmost(c);
    if (c != d)
		c.to_parent();
}

//template <class Cursor>
//BOOST_CONCEPT_REQUIRES(
//    ((RootTrackingCursor<Cursor>)),
//    (void)) // return type
//to_last(inorder, Cursor& c, root_tracking_vertical_traversal_tag)
//{
//    to_rightmost(c);
//    if (!c.is_root())
//		c.to_parent();
//}

/**
 * @brief   One position past the last element of a subtree in inorder 
 *          traversal
 * @param c Subtree root cursor that will be set past the last inorder 
 *          position in the subtree.
 */
template <class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>)),
    (void)) // return type
to_past(inorder, Cursor& c)
{
    to_rightmost(c);
}

template <class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>)),
    (void)) // return type
last_to_past(inorder, Cursor& c)
{
    c.to_end();
}

template <class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((AscendingCursor<Cursor>)),
    (void)) // return type
past_to_last(inorder, Cursor& c)
{
    c.to_parent();
}

/*\@}*/

/// Search

/**
 * @brief        Finds the first position in a multiway subtree in which @a val 
 *                 could be inserted without changing the ordering, using < (less
 *                 than) for comparisons.
 * @param x        The subtree's root
 * @param val    The search term
 * @return        A multiway cursor pointing to the first element not less than 
 *                @a val, or @x if every element in the subtree is less than 
 *                 @a val.
 */
//[ lower_bound
template <class MultiwayCursor, class T>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<MultiwayCursor>))
    ((LessThanComparable<T>)),
    (MultiwayCursor)) // return type
lower_bound(MultiwayCursor x, T const& val)
//]
{
    MultiwayCursor y = x;
    while (!x.is_leaf())
        if (*x < val) {
            x.to_end();
        } else {
            y = x;
            x.to_begin();
        }
    return y;
}

/**
 * @brief        Finds the first position in a multiway subtree in which @a val 
 *                 could be inserted without changing the ordering, using @a cmp 
 *                 for comparisons.
 * @param x        The subtree's root
 * @param val    The search term
 * @param cmp    The comparison functor
 * @return        A multiway cursor pointing to the first element not less than 
 *                @a val, or @x if every element in the subtree is less than 
 *                 @a val.
 */
//[ lower_bound_cmp
template <class MultiwayCursor, class T, class Cmp>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<MultiwayCursor>))
    /*((StrictWeakOrdering<Cmp>))*/, //FIXME
    (MultiwayCursor)) // return type
lower_bound(MultiwayCursor x, T const& val, Cmp cmp)
//]
{
    MultiwayCursor y = x;
    while (!x.is_leaf())
        if (cmp(*x,val)) {
            x.to_end();
        } else {
            y = x;
            x.to_begin();
        }
    return y;
}

/**
 * @brief        Finds the last position in a multiway subtree in which @a val 
 *                 could be inserted without changing the ordering, using < (less
 *                 than) for comparisons.
 * @param x        The subtree's root
 * @param val    The search term
 * @return        A multiway cursor pointing to the first element greater than 
 *                @a val, or @x if no element in the subtree is greater than 
 *                 @a val.
 */
//[ upper_bound
template <class MultiwayCursor, class T>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<MultiwayCursor>))
    ((LessThanComparable<T>)),
    (MultiwayCursor)) // return type
upper_bound(MultiwayCursor x, T const& val)
//]
{
    MultiwayCursor y = x;
    while (!x.is_leaf())
        if (val < *x) {
            y = x;
            x.to_begin();
        } else {
            x.to_end();
        }
    return y;
}

/**
 * @brief        Finds the last position in a multiway subtree in which @a val 
 *                 could be inserted without changing the ordering, using @a cmp 
 *                 for comparisons.
 * @param x        The subtree's root
 * @param val    The search term
 * @param cmp    The comparison functor
 * @return        A multiway cursor pointing to the first element greater than 
 *                @a val, or @x if no element in the subtree is greater than
 *                 @a val.
 */
//[ upper_bound_cmp
template <class MultiwayCursor, class T, class Cmp>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<MultiwayCursor>))
    /*((LessThanComparable<Cmp>))*/, //FIXME
    (MultiwayCursor)) // return type
upper_bound(MultiwayCursor x, T const& val, Cmp cmp)
//]
{
    MultiwayCursor y = x;
    while (!x.is_leaf())
        if (cmp(val,*x)) {
            y = x;
            x.to_begin();
        } else {
            x.to_end();
        }
    return y;
}

// Implement equal_range? Maybe not, if it'd only return a pair 
// consisting of cursors calculated by calling lower_bound and upper_bound.
// This might be a bit more subtle for non-binary multiway trees. 

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_INORDER_ALGORITHMS_HPP
