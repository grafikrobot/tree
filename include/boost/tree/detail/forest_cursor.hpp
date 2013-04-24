//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file forest_cursor.hpp
 * Forest cursor template
 */

#ifndef BOOST_TREE_DETAIL_FOREST_CURSOR_HPP
#define BOOST_TREE_DETAIL_FOREST_CURSOR_HPP

#include <boost/tree/cursor.hpp>
#include <boost/tree/cursor_adaptor.hpp>

#include <boost/tree/detail/iterative_algorithms.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <iterator>
#include <utility>

namespace boost {
namespace tree {
namespace detail {

using boost::tree::cursor_core_access;
using boost::iterator_core_access;

template <class Cursor> 
class forest_cursor
: public cursor_adaptor<forest_cursor<Cursor>
      , Cursor
      , boost::use_default
      , bidirectional_traversal_tag
      , ascending_vertical_traversal_tag
    > {

private:
    struct enabler {};

public:
     //TODO: Tidy up typedefs

    typedef Cursor base_cursor;
    
    typedef forest_cursor<Cursor> cursor;
    typedef forest_cursor<Cursor const> const_cursor; //FIXME (?)

    //typedef typename cursor_size<base_cursor>::type size_type;

    //typedef bidirectional_traversal_tag cursor_category;
        
    // Container-specific:
    typedef cursor iterator;  // For (range) concepts' sake, mainly
//    typedef const_cursor const_iterator;
    
     // Common iterator facade stuff
    forest_cursor()
     : forest_cursor::cursor_adaptor_() {}

    explicit forest_cursor(base_cursor p)
     : forest_cursor::cursor_adaptor_(p) {}
      
    template <class OtherCursor>
    forest_cursor(
        forest_cursor<OtherCursor> const& other
      , typename boost::enable_if<
            boost::is_convertible<OtherCursor, 
               Cursor>  // is that correct?
          , enabler
        >::type = enabler()
    )
      : forest_cursor::cursor_adaptor_(other.base()) {}

    operator base_cursor()
    {
        return forest_cursor::cursor_adaptor_::base();
    }
    
    Cursor const& base() const
    {
        return forest_cursor::cursor_adaptor_::base();
    }

private:
    friend class cursor_core_access;
    friend class iterator_core_access;

    void increment()
    {
        this->base_reference().to_end();
    }
    
    void decrement()
    {
        this->base_reference().to_parent();
    }
    
    // Range stuff.
    
    // left() remains unchanged, so no need to re-implement it.

    void right()
    {
        to_forest_end(this->base_reference());
    }
    
    // Cursor stuff. 
    
    void up()
    {
        to_forest_parent(this->base_reference());
    }
};

} // namespace detail

template <class BinaryCursor, class Op>
Op for_each(preorder, boost::tree::detail::forest_cursor<BinaryCursor> s, boost::tree::detail::forest_cursor<BinaryCursor> t, Op f)
{
    return detail::for_each(preorder(), s.base(), t.base(), f
                          , typename cursor_vertical_traversal<BinaryCursor>::type());
}

template <class BinaryCursor, class Op>
Op for_each(postorder, boost::tree::detail::forest_cursor<BinaryCursor> s, boost::tree::detail::forest_cursor<BinaryCursor> t, Op f)
{
    return detail::for_each(inorder(), s.base(), t.base(), f
                          , typename cursor_vertical_traversal<BinaryCursor>::type());
}

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_FOREST_CURSOR_HPP
