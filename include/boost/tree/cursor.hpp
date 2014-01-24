//  Copyright 20013-2014, Rene Rivera
//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_CURSOR_HPP
#define BOOST_TREE_CURSOR_HPP

#include <cstddef>
#include <iterator>

namespace boost
{
namespace tree
{

// 24.7.4, cursor primitives

// 24.7.4.1, cursor traits
template<class Cursor> struct cursor_value
{
    typedef typename Cursor::value_type type;
};
template<class Cursor> struct cursor_reference
{
    typedef typename Cursor::reference type;
};
template<class Cursor> struct cursor_const_reference
{
    typedef typename Cursor::const_reference type;
};
template<class Cursor> struct cursor_pointer
{
    typedef typename Cursor::pointer type;
};
template<class Cursor> struct cursor_difference
{
    typedef typename Cursor::difference_type type;
};
template<class Cursor> struct cursor_size
{
    typedef typename Cursor::size_type type;
};
template<class Cursor> struct cursor_category
{
    typedef typename Cursor::cursor_category type;
};

// 24.7.4.2, basic cursor
template<class Category, class T, class Distance = ptrdiff_t,
    class Size = size_t, class Pointer = T*, class Reference = T&>
struct cursor
{
    typedef Category cursor_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Size size_type;
    typedef Pointer pointer;
    typedef Reference reference;
};

// 24.7.4.3, standard cursor tags
struct cursor_tag :
    public std::input_iterator_tag,
    public std::output_iterator_tag
{
};
struct descending_cursor_tag : public cursor_tag
{
};
struct descending_forward_cursor_tag :
    public descending_cursor_tag,
    public std::forward_iterator_tag
{
};
struct descending_bidirectional_cursor_tag :
    public descending_cursor_tag,
    public std::bidirectional_iterator_tag
{
};
struct descending_random_access_cursor_tag :
    public descending_cursor_tag,
    public std::random_access_iterator_tag
{
};
struct ascending_cursor_tag : public descending_cursor_tag
{
};
struct ascending_forward_cursor_tag : public descending_forward_cursor_tag
{
};
struct ascending_bidirectional_cursor_tag :
    public descending_bidirectional_cursor_tag
{
};
struct ascending_random_access_cursor_tag :
    public descending_random_access_cursor_tag
{
};

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_CURSOR_HPP
