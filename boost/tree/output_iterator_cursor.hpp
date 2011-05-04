//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file output_iterator_cursor.hpp
 * Cursor wrapper around a given output iterator.
 */
 
#ifndef BOOST_TREE_OUTPUT_ITERATOR_CURSOR_HPP
#define BOOST_TREE_OUTPUT_ITERATOR_CURSOR_HPP

#include <boost/tree/cursor_facade.hpp>
#include <boost/tree/cursor.hpp>

namespace boost {
namespace tree {

template <class OutputIterator>
class output_iterator_cursor;

template <class OutputIterator>
class output_iterator_cursor
: public boost::tree::cursor_facade<
        output_iterator_cursor<OutputIterator>
      , output_iterator_cursor<OutputIterator>
      , boost::bidirectional_traversal_tag
      , boost::tree::ascending_vertical_traversal_tag
>
{
private:
    OutputIterator& m_iter;
public:
    typedef output_iterator_cursor<OutputIterator> cursor;
    typedef output_iterator_cursor<OutputIterator/* const*/> const_cursor;

    typedef typename output_iterator_cursor<OutputIterator>::cursor_facade_::size_type size_type;
    
    output_iterator_cursor(OutputIterator& iter)
    : m_iter(iter) {}

    output_iterator_cursor(output_iterator_cursor<OutputIterator> const& other)
    : m_iter(other.m_iter) {}

    template <class ValueType>
    output_iterator_cursor&
    operator=(ValueType const& val)
    {
        *m_iter++ = val;
        return *this; 
    }
    
private:
    friend class boost::iterator_core_access;
    friend class boost::tree::cursor_core_access;
    
    typename output_iterator_cursor<OutputIterator>::cursor_facade_::reference
    dereference() const
    {
        return const_cast< output_iterator_cursor<OutputIterator>& >(*this);
    }

    bool equal(output_iterator_cursor<OutputIterator> const& other) const
    {
        return m_iter == other.m_iter;
    }
    
    bool const empty_() const
    {
        return true;
    }

    size_type const idx() const
    {
        return 0;
    }
    
    void increment() {}
    void decrement() {}
    void left() {}
    void right() {}
    void up() {}
};

template <class OutputIterator>
typename output_iterator_cursor<OutputIterator>::size_type
index(output_iterator_cursor<OutputIterator> const& cur)
{
    return cur.index();
}

/** 
 * @param o    An output iterator.
 * @result    An instance of output_iterator_cursor working on o.
 * 
 * Use as shortcut for cumbersome typenames, just as with std::inserter and the like.
 */
template<class OutputIterator>
inline output_iterator_cursor<OutputIterator>
outputter_cursor_iterator_wrapper(OutputIterator o)
{
    return output_iterator_cursor<OutputIterator>(o);
}

} // namespace tree
} // namespace boost


#endif // BOOST_TREE_OUTPUT_ITERATOR_CURSOR_HPP
