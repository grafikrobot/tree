//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file recursive_inorder_algorithms.hpp
 * Recursive subtree inorder traversal and search algorithms.
 */

#ifndef BOOST_TREE_DETAIL_RECURSIVE_INORDER_ALGORITHMS_HPP
#define BOOST_TREE_DETAIL_RECURSIVE_INORDER_ALGORITHMS_HPP

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
template <class MultiwayCursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<MultiwayCursor>))
    ((UnaryFunction<Op, void, typename cursor_value<MultiwayCursor>::type>)),
    (void)) // return type
for_each_recursive(inorder, MultiwayCursor r, Op& f)
{
    MultiwayCursor s = r.begin();
    MultiwayCursor t = r.end();

    for (; s!=t; ++s) {
        if (!s.is_leaf())
            for_each_recursive(inorder(), s, f);
        f(*r);
    }
    
    // Multiway cursor
    if (!t.is_leaf())
        for_each_recursive(inorder(), t, f);
}

/**
 * @brief	Apply a function to every element of a multiway subtree,
 *          in inorder.
 * @param s	A MultiwayTree cursor.
 * @param f A unary function object.
 * @return  @p f
 *
 * Applies the function object @p f to each element in the @p subtree, using
 * inorder. @p f must not modify the order of the sequence.
 * If @p f has a return value it is ignored.
 */
template <class MultiwayCursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<MultiwayCursor>))
    ((UnaryFunction<Op, void, typename cursor_value<MultiwayCursor>::type>)),
    (Op)) // return type
for_each(inorder, MultiwayCursor r, Op f, descending_vertical_traversal_tag)
{
	if (r.is_leaf())
		return f;

    MultiwayCursor s = r.begin();
    MultiwayCursor t = r.end();

    for (; s!=t; ++s) {
        if (!s.is_leaf())
            for_each_recursive(inorder(), s, f);
        f(*r);
    }
    
    // Multiway cursor
    if (!t.is_leaf())
        for_each_recursive(inorder(), t, f);
    return f;
}

/**
 * @brief		Performs an operation on a subtree, by traversing it in inorder.
 * @param s		An input cursor.
 * @param t		An output cursor.
 * @param op	A unary operation.
 * @result		A cursor past t's inorder end, after the transforming has
 *              finished.
 * 
 * By traversing the input subtree s in inorder, apply the operation op 
 * to each element and write the result to the output subtree t.
 * 
 * op must not change its argument.
 */
template <class InCursor, class OutCursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<InCursor>))
    ((DescendingCursor<OutCursor>))
    /*((UnaryFunction<Op>))*/,
    (OutCursor)) // return type
transform(inorder, InCursor s, OutCursor t, Op op, descending_vertical_traversal_tag)
{
	if (s.is_leaf())
		return t;

	*t = op(*s);

    InCursor r = s;

    s.to_begin();
    t.to_begin();
    
    for (; s != r.end(); ++s, ++t) {
        if (!s.is_leaf())
            transform(inorder(), s, t, op, descending_vertical_traversal_tag());
        *t=op(*r);
    }

    // Multiway cursor
    if (!r.to_end().is_leaf())
        transform(inorder(), r, t, op, descending_vertical_traversal_tag());
    return t;
}

//#endif //BOOST_RECURSIVE_ORDER_ALGORITHMS

} // namespace detail
} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_RECURSIVE_INORDER_ALGORITHMS_HPP
