//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file recursive_preorder_algorithms.hpp
 * Recursive subtree preorder traversal algorithms
 */

#ifndef BOOST_TREE_DETAIL_RECURSIVE_PREORDER_ALGORITHMS_HPP
#define BOOST_TREE_DETAIL_RECURSIVE_PREORDER_ALGORITHMS_HPP

#include <boost/tree/cursor_concepts.hpp>

#include <boost/concept/requires.hpp>

namespace boost {
namespace tree {
namespace detail {

using namespace boost_concepts;

//#ifdef BOOST_RECURSIVE_ORDER_ALGORITHMS

template <class Cursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>)),
    (void)) // return type
for_each_recursive(preorder, Cursor s, Cursor t2, Op& f)
{
    f(*s);
    Cursor t = s.end();
    for (s.to_begin(); s != t; ++s)
        if (!s.is_leaf() && s != t2)
            for_each_recursive(preorder(), s, t2, f);
    
    // Multiway cursor
    if (!s.is_leaf() && s != t2)
        for_each_recursive(preorder(), s, t2, f);
}

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
for_each_recursive(preorder, Cursor s, Op& f)
{
    f(*s);
    Cursor t = s.end();
    for (s.to_begin(); s != t; ++s)
        if (!s.is_leaf())
            for_each_recursive(preorder(), s, f);
    
    // Multiway cursor
    if (!s.is_leaf())
        for_each_recursive(preorder(), s, f);
}

template <class Cursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>)),
    (Op)) // return type
for_each(preorder, Cursor s, Cursor t2, Op f, descending_vertical_traversal_tag)
{
    f(*s);
    Cursor t = s.end();
    --t2; // Bit tweaky.
    for (s.to_begin(); s != t ; ++s)
        if (!s.is_leaf() && s != t2)
            for_each_recursive(preorder(), s, t2, f);
    
    // Multiway cursor
    if (!t.is_leaf() && t != t2)
        for_each_recursive(preorder(), t, t2, f);
    
    return f;
}

/**
 * @brief	Apply a function to every element of a subtree, in preorder.
 * @param s	A cursor.
 * @param f	A unary function object.
 * @return  @p f
 *
 * Applies the function object @p f to each element in the @p subtree, using  
 * preorder. @p f must not modify the order of the sequence.
 * If @p f has a return value it is ignored.
 */
template <class Cursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>))
    ((UnaryFunction<Op, void, typename cursor_value<Cursor>::type>)),
    (Op)) // return type
for_each(preorder, Cursor s, Op f, descending_vertical_traversal_tag)
{
	if (s.is_leaf())
		return f;

    f(*s);
    Cursor t = s.end();
    for (s.to_begin(); s != t; ++s) {
        if (!s.is_leaf())
            for_each_recursive(preorder(), s, f);
    }
    
    // Multiway cursor
    if (!s.is_leaf())
        for_each_recursive(preorder(), s, f);
    
    return f;
}

//#endif //BOOST_RECURSIVE_ORDER_ALGORITHMS

/**
 * @brief     Performs an operation on a subtree, by traversing it in preorder.
 * @param s  An input cursor.
 * @param t  An output cursor.
 * @param op A unary operation.
 * @result     A cursor past t's preorder end, after the transforming has 
 *              finished.
 * 
 * By traversing the input subtree s in preorder, apply the operation op 
 * to each element and write the result to the output subtree t.
 * 
 * op must not change its argument.
 */
template <class InCursor, class OutCursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<InCursor>))
    ((DescendingCursor<OutCursor>)),
    (OutCursor)) // return type
transform(preorder, InCursor s, OutCursor t, Op op, descending_vertical_traversal_tag)
{
	if (s.is_leaf())
		return t;

	*t = op(*s);

    InCursor r = s.end();
    s.to_begin();
    t.to_begin();
    for (; s != r; ++s, ++t) {
        //*t = op(*s);
        if (!s.is_leaf())
            transform(preorder(), s, t, op, descending_vertical_traversal_tag());
    }

    // Multiway cursor
    if (!s.is_leaf())
        transform(preorder(), s, t, op, descending_vertical_traversal_tag());
        
    return t;
}

//#endif //BOOST_RECURSIVE_ORDER_ALGORITHMS

} // namespace detail
} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_RECURSIVE_PREORDER_ALGORITHMS_HPP
