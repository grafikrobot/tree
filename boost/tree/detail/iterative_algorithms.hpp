//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** @file   iterative_algorithms.hpp
 * 
 * Some iterative algorithm versions that are identical for all *order cursors 
 * (as we are just calling the appropriate traversal function that are 
 * defined in the respective *order.hpp files).
 */

#ifndef BOOST_TREE_DETAIL_ITERATIVE_ALGORITHMS_HPP
#define BOOST_TREE_DETAIL_ITERATIVE_ALGORITHMS_HPP

#include <boost/tree/coupling_cursor.hpp>

#include <boost/tree/preorder_algorithms.hpp>
#include <boost/tree/inorder_algorithms.hpp>
#include <boost/tree/postorder_algorithms.hpp>

#include <boost/tree/root_tracking_cursor.hpp>

#include <boost/tree/cursor_concepts.hpp>

#include <boost/concept/requires.hpp>

namespace boost {
namespace tree {
namespace detail {

// .base() !!!
template <class Order, class Cursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>))
    ((AscendingCursor<Cursor>)), // FIXME: Also RootTrackingCursor? 
    (Op)) // return type
for_each(Order, Cursor s, Cursor s2, Op f, ascending_vertical_traversal_tag)
{
    while (s!=s2) {
        f(*s);
        successor(Order(), s);
    }
    return f;
}

template <class Order, class Cursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<Cursor>))
    ((AscendingCursor<Cursor>)),
    (Op)) // return type
for_each(Order, Cursor is, Op f, ascending_vertical_traversal_tag)
{
    root_tracking_cursor<Cursor> s(is);
    root_tracking_cursor<Cursor> s2(is);
    to_first(Order(), s);
//    to_last(Order(), s2);
//    return detail::for_each(Order(), s, s2, f, ascending_vertical_traversal_tag());
    do {
        f(*s);
    } while (successor(Order(), s));
    return f;
}

template <class Order, class InCursor, class OutCursor, class Op>
BOOST_CONCEPT_REQUIRES(
    ((DescendingCursor<InCursor>))
    ((AscendingCursor<InCursor>))
    ((DescendingCursor<OutCursor>))
    ((AscendingCursor<OutCursor>)),
    (OutCursor)) // return type
transform (Order, InCursor is, OutCursor t, Op op
                   , ascending_vertical_traversal_tag)
{
    root_tracking_cursor<InCursor> s(is);
    root_tracking_cursor<InCursor> s2(s);
    
    boost::tree::coupling_cursor< root_tracking_cursor<InCursor>, OutCursor > cc(s, t);

    to_first(Order(), cc);
    to_last(Order(), s2);

    while (cc.in()!=s2) {
        *cc.out() = op(*cc.in());
        successor(Order(), cc);
    }
    return cc.out();
}

} // namespace detail
} // namespace tree
} // namespace boost

#endif //BOOST_TREE_DETAIL_ITERATIVE_ALGORITHMS_HPP
