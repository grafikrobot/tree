//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** @file   iterator.hpp
 * 
 * Iterator wrapper around a cursor, using a given type of traversal.
 */

#ifndef BOOST_TREE_ITERATOR_HPP
#define BOOST_TREE_ITERATOR_HPP

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/tree/root_tracking_cursor.hpp>
#include <boost/tree/inorder_algorithms.hpp>

#include <boost/tree/cursor_concepts.hpp>

#include <boost/concept_check.hpp>
#include <boost/concept/requires.hpp>

namespace boost {
namespace tree {
    
using namespace boost_concepts;

/**
 * @brief   Traversal order iterator adaptor
 * 
 * This wrapper adapts a cursor (which is used for hierarchical
 * traversal) to work as an iterator (for linear traversal, such
 * as required by STL algorithms), along a specified order.
 * 
 */
template <class Order, class Cursor>
class iterator
 : public boost::iterator_adaptor<iterator<Order, Cursor>
      , Cursor
      , boost::use_default
      , typename Order::iterator_category
    > {
BOOST_CONCEPT_ASSERT((RootTrackingCursor<Cursor>));

 private:
    struct enabler {};

 public:
    iterator()
      : iterator::iterator_adaptor_() {}

    explicit iterator(Cursor p)
      : iterator::iterator_adaptor_(p) {}

    template <class OtherCursor>
    iterator(
        iterator<Order, OtherCursor> const& other
      , typename boost::enable_if<
            boost::is_convertible<OtherCursor, Cursor>
          , enabler
        >::type = enabler()
    )
      : iterator::iterator_adaptor_(other.base()) {}

    operator Cursor()
    {
        return this->base();
    }
 private:
    friend class boost::iterator_core_access;
    
    void increment()
    {
        successor(Order(), this->base_reference());
    }
    
    void decrement()
    {
        predecessor(Order(), this->base_reference());
    }
};

 template <class Cursor>
 class iterator<inorder, Cursor>
  : public boost::iterator_adaptor<iterator<inorder, Cursor>
       , Cursor
       , boost::use_default
       , inorder::iterator_category
     > {
 BOOST_CONCEPT_ASSERT((RootTrackingCursor<Cursor>));

  private:
     struct enabler {};

  public:
     iterator()
       : iterator::iterator_adaptor_() {}

     explicit iterator(Cursor p)
       : iterator::iterator_adaptor_(p) {}

     template <class OtherCursor>
     iterator(
         iterator<inorder, OtherCursor> const& other
       , typename boost::enable_if<
             boost::is_convertible<OtherCursor, Cursor>
           , enabler
         >::type = enabler()
     )
       : iterator::iterator_adaptor_(other.base()) {}

     operator Cursor()
     {
         return this->base();
     }
  private:
     friend class boost::iterator_core_access;

     void increment()
     {
    	 Cursor c = this->base_reference();
         if (successor(inorder(), this->base_reference()))
        	 return;

         last_to_past(inorder(), c);
         this->base_reference() = c;
     }

     void decrement()
     {
    	 // Works also if we're past the last element:
    	 predecessor(inorder(), this->base_reference());
     }
 };

/**
 * @brief   First element of a subtree in traversal
 * @param c A cursor
 * @return  Iterator to the first element of @a c
 */
template <class Order, class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((AscendingCursor<Cursor>)),
    (iterator< Order, root_tracking_cursor<Cursor> >)) // return type
//iterator< Order, root_tracking_cursor<Cursor> >
begin(Order, Cursor c)
{
    root_tracking_cursor<Cursor> rtc(c);
    to_first(Order(), rtc);
    return iterator< Order, root_tracking_cursor<Cursor> >(rtc);
}

/**
 * @brief    One position past the last element of a subtree 
 *             in traversal (Alias of cend())
 * @param c    A cursor
 * @return    Iterator one position past the last element of @a c 
 */
template <class Order, class Cursor>
BOOST_CONCEPT_REQUIRES(
    ((AscendingCursor<Cursor>)),
    (iterator< Order, root_tracking_cursor<Cursor> >)) // return type
//iterator<Order, root_tracking_cursor<Cursor> >
end(Order, Cursor c)
{
    root_tracking_cursor<Cursor> rtc(c);
    to_past(Order(), rtc);
    return iterator< Order, root_tracking_cursor<Cursor> >(rtc);
}

/// Reverse iterators

template <class Order, class Cursor>
std::reverse_iterator< iterator<Order, Cursor> >
rbegin(Order, Cursor c)
{
    return std::reverse_iterator< iterator<Order, Cursor> >(end(Order(), c));
}

template <class Order, class Cursor>
std::reverse_iterator< iterator<Order, Cursor> >
rend(Order, Cursor c)
{
    return std::reverse_iterator< iterator<Order, Cursor> >(begin(Order(), c));
}

} // namespace tree
} // namespace boost

#endif //BOOST_TREE_ITERATOR_HPP
