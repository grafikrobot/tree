//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file recursive_postorder_algorithms.hpp
 * Recursice subtree postorder traversal algorithms
 */

#ifndef BOOST_TREE_DETAIL_RECURSIVE_POSTORDER_ALGORITHMS_HPP
#define BOOST_TREE_DETAIL_RECURSIVE_POSTORDER_ALGORITHMS_HPP

#include <boost/tree/cursor_concepts.hpp>

#include <boost/concept/requires.hpp>

namespace boost {
namespace tree {
namespace detail {

using namespace boost_concepts;

//#ifdef BOOST_RECURSIVE_ORDER_ALGORITHMS

/**
 * @if maint
 * Helper function for for_each, using a reference parameter in order to
 * require fewer copy and assignment operations.
 * @endif
 */
template <class Cursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>))
    ((UnaryFunction<Op, void, typename cursor_value<Cursor>::type>)),
    (void)) // return type
for_each_recursive(postorder, Cursor s, Op& f)
{
    Cursor t = s;
    for (s.to_begin(); s != t.end(); ++s)
        if (!s.is_leaf())
            for_each_recursive(postorder(), s, f);

    // Multiway cursor
    if (!s.is_leaf())
        for_each_recursive(postorder(), s, f);

    f(*t);
}

/**
 * @brief	Apply a function to every element of a subtree, in postorder.
 * @param s	A cursor.
 * @param f	A unary function object.
 * @return	@p f
 *
 * Applies the function object @p f to each element in the subtree @p s, using 
 * postorder. @p f must not modify the order of the sequence.
 * If @p f has a return value it is ignored.
 */
template <class Cursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>))
    ((UnaryFunction<Op, void, typename cursor_value<Cursor>::type>)),
    (Op)) // return type
for_each(postorder, Cursor s, Op f, descending_vertical_traversal_tag)
{
	if (s.is_leaf())
		return f;

    Cursor t = s;
    for (s.to_begin(); s != t.end(); ++s)
        if (!s.is_leaf())
            for_each_recursive(postorder(), s, f);

    // Multiway cursor
    if (!s.is_leaf())
        for_each_recursive(postorder(), s, f);

    f(*t);

    return f;
}

/**
 * @brief     Performs an operation on a subtree, by traversing it in postorder.
 * @param s  An input cursor.
 * @param t  An output cursor.
 * @param op A unary operation.
 * @result     A cursor past t's postorder end, after the transforming has
 *              finished.
 * 
 * By traversing the input subtree s in postorder, apply the operation op 
 * to each element and write the result to the output subtree t.
 * 
 * op must not change its argument.
 */
template <class InCursor, class OutCursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<InCursor>))
    ((DescendingCursor<OutCursor>)),
    (OutCursor)) // return type
transform(postorder, InCursor s, OutCursor t, Op op, descending_vertical_traversal_tag)
{
	if (s.is_leaf())
		return t;

    InCursor r = s;
    s.to_begin();
    t.to_begin();
    OutCursor t2 = t;
    
    for (; s != r.end(); ++s, ++t)
        if (!s.is_leaf())
            transform(postorder(), s, t, op, descending_vertical_traversal_tag());

    // Multiway cursor
    if (!s.is_leaf())
        transform(postorder(), s, t, op, descending_vertical_traversal_tag());
    
    *t2 = op(*r);
    return t;
}

//#endif //BOOST_RECURSIVE_ORDER_ALGORITHMS

} // namespace detail
} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_RECURSIVE_POSTORDER_ALGORITHMS_HPP
