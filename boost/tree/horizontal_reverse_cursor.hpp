//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file horizontal_reverse_cursor.hpp
 * Horizontal reverse cursor adaptor implementation
 */

#ifndef BOOST_TREE_HORIZONTAL_REVERSE_CURSOR_HPP
#define BOOST_TREE_HORIZONTAL_REVERSE_CURSOR_HPP


#include <boost/tree/cursor_adaptor.hpp>
#include <boost/tree/cursor.hpp>

#include <boost/mpl/eval_if.hpp>

#include <utility>

namespace boost {
namespace tree {

/** \addtogroup cursor_adaptors
 *  \@{ */

template <class Cursor> 
class horizontal_reverse_cursor
: public cursor_adaptor<horizontal_reverse_cursor<Cursor>
                      , Cursor 
//                      , boost::use_default
//                      , typename cursor_horizontal_traversal<Cursor>::type
//                      , typename cursor_vertical_traversal<Cursor>::type
    > {
private:
    struct enabler {};
    typedef horizontal_reverse_cursor<Cursor> self_type;
public:

    // Cursor-specific
    typedef horizontal_reverse_cursor<Cursor> cursor;
    typedef horizontal_reverse_cursor<typename Cursor::const_cursor> const_cursor;
    
    // Container-specific:
    typedef cursor iterator;
    typedef const_cursor const_iterator;
    
    template <class OtherCursor>
    struct rebind {
        typedef horizontal_reverse_cursor<OtherCursor> other;
    };
    
    horizontal_reverse_cursor()
    : horizontal_reverse_cursor::cursor_adaptor_() {}

    explicit horizontal_reverse_cursor(Cursor c)
    : horizontal_reverse_cursor::cursor_adaptor_(c) {}

//    template <class OtherCursor>
//    horizontal_reverse_cursor(
//        horizontal_reverse_cursor<OtherCursor> const& other
//      , typename boost::enable_if<
//            boost::is_convertible<OtherCursor*, Cursor*>
//          , enabler
//        >::type = enabler()
//    )
//    : horizontal_reverse_cursor::cursor_adaptor_(other.base())
//    , m_depth(other.m_depth) {}

//    Cursor const& base() const
//    {
//        return this->base(); 
//    }

private: 
    friend class boost::iterator_core_access;
    friend class boost::tree::cursor_core_access;
         
    void increment()
    {
        --this->base_reference();
    }

    void decrement()
    {
        ++this->base_reference();
    }

    void left()
    {
        this->base_reference().to_end();
    }

    void right()
    {
        this->base_reference().to_begin();
    }

};


/** @} */

} // namespace tree
} // namespace boost


#endif // BOOST_TREE_HORIZONTAL_REVERSE_CURSOR_HPP
