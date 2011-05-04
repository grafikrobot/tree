//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file general_algorithms.hpp
 * General algorithms for cursors
 */

#ifndef BOOST_TREE_GENERAL_ALGORITHMS_HPP
#define BOOST_TREE_GENERAL_ALGORITHMS_HPP

#include <boost/tree/cursor_concepts.hpp>

#include <boost/concept/requires.hpp>
#include <boost/concept_check.hpp>

namespace boost {
namespace tree {

using namespace boost_concepts;

/**
 * @brief      The leftmost descendant of the given cursor
 * @param c    Cursor to be set to its leftmost descendant
 * @ingroup    traversal
 */
template <class Cursor>
inline
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>)),
    (void)) // return type
to_leftmost(Cursor& c)
{
    while (!c.is_leaf())
        c.to_begin();
}

/**
 * @brief      The rightmost descendant of the given cursor
 * @param c    Cursor to be set to its rightmost descendant
 * @ingroup    traversal
 */
template <class Cursor>
inline
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>)),
    (void)) // return type
to_rightmost(Cursor& c)
{
    while (!c.is_leaf())
        c.to_end();
}

// These algorithms are actually mostly preorder, as it's most efficient, but I
// think it doesn't make much sense having in- and postorder versions of them. 
// The only reason I can think of is that there might be some cases
// where it's likely to find a mismatch or whatever faster in in- or postorder
// than in preorder -- but for things like size() or count(), this doesn't really matter.

// What about the subtree shapes?
/**
 *  @brief      Checks two subtrees for element-wise equality.
 *  @param c1   An input cursor.
 *  @param c2   An input cursor.
 *  @return     A boolean true or false.
 *
 *  Compares the elements of two subtrees using @c ==. Returns true if
 *  all the corresponding elements of the subtrees are equal; otherwise,
 *  it returns false.
 */
//[ equal
template <class InCursor1, class InCursor2>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<InCursor1>))
    ((DescendingCursor<InCursor2>)),
    (bool)) // return type
equal(InCursor1 c1, InCursor2 c2)
//]
{
    if (!(*c1 == *c2))
        return false;

    InCursor1 d1 = c1.end();
    c1.to_begin();
    c2.to_begin();

    do {
        if (!c1.is_leaf())
            if (!equal(c1, c2))
                return false;
        ++c2;
    } while (c1++ != d1);
    
    return true;
}

/**
 *  @brief        Checks two subtrees for element-wise equality.
 *  @param c1    An input cursor.
 *  @param c2    An input cursor.
 *  @param p    A binary predicate.
 *  @return        A boolean true or false.
 *
 *  Compares the elements of two subtrees using the p parameter. 
 *  Returns true if all the corresponding elements of the 
 *  subtrees are equal; otherwise, it returns false.
 */
//[ equal_pred
template <class InCursor1, class InCursor2, class BinPred>
//FIXME
//BOOST_CONCEPT_REQUIRES(
//    ((DescendingCursor<InCursor1>))
//    ((DescendingCursor<InCursor2>))
//    ((BinaryPredicate<BinPred, typename cursor_value<InCursor1>::type
//                             , typename cursor_value<InCursor2>::type>)),
//    (bool)) // return type
bool
equal(InCursor1 c1, InCursor2 c2, BinPred p)
//]
{
    if (!p(*c1,*c2))
        return false;

    InCursor1 d1 = c1.end();
    c1.to_begin();
    c2.to_begin();

    do {
        if (!c1.is_leaf())
            if (!equal(c1, c2))
                return false;
        ++c2;
    } while (c1++ != d1);
    
    return true;
}

/**
 *  @brief        Calculates the number of elements in a subtree.
 *  @param c    An input cursor.
 *  @param s    The size type of @c c1.
 * 
 * After finishing, s will have been increased by the number of elements in c.         
 */
template <class InCursor>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<InCursor>)),
    (void)) // return type
size(InCursor c, typename InCursor::subtree_size_type& s)
{
    InCursor d = c.end();
    c.to_begin();
    ++s;
    do
        if (!c.is_leaf())
            size(c, s);
    while (c++ != d);
}

/**
 *  @brief        Returns the number of elements in a subtree.
 *  @param c    An input cursor.
 *  @return        The size type of @c c1.
 */
//[ size
template <class InCursor>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<InCursor>)),
    (typename InCursor::subtree_size_type)) // return type
size(InCursor c)
//]
{
    typename InCursor::subtree_size_type s = 0;
    InCursor d = c.end();
    c.to_begin();
    ++s;
    do
        if (!c.is_leaf())
            size(c, s);
    while (c++ != d);
    
    return s;
}


} // namespace tree
} // namespace boost

#endif // BOOST_TREE_GENERAL_ALGORITHMS_HPP
