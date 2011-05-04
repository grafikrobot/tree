//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_TEST_MOCK_BINARY_CURSOR_HPP
#define LIBS_TREE_TEST_MOCK_BINARY_CURSOR_HPP

#include "test_data.hpp"

template <class Iter>
class mock_binary_cursor;

// Mock template class to check the correct value
// to be assigned to a given position within a tree,
// and if these assignments are done in a given order.
//
// The position checking logic is identical to that of fake_binary_tree,
// so we might want to factor that part out to a position_tracking_nary_cursor.
template <class Iter>
class mock_binary_cursor
: public boost::tree::cursor_facade<
        mock_binary_cursor<Iter>
      , mock_binary_cursor<Iter>
      , boost::bidirectional_traversal_tag
      , boost::tree::descending_vertical_traversal_tag
    >
{
private:
    Iter& m_iter, m_end;
    std::size_t m_pos;
public:
    typedef mock_binary_cursor<Iter> cursor;
    typedef mock_binary_cursor<Iter/* const*/> const_cursor;

    typedef typename mock_binary_cursor<Iter>::cursor_facade_::size_type size_type;
    
    mock_binary_cursor(Iter& iter, Iter& end, std::size_t pos = 0)
    : m_iter(iter), m_end(end), m_pos(pos) {}

    mock_binary_cursor(mock_binary_cursor<Iter> const& other)
    : m_iter(other.m_iter), m_end(other.m_end), m_pos(other.m_pos) {}

    void operator=(typename Iter::value_type::value_type const& val)
    {
        BOOST_CHECK(m_iter != m_end);
        if (m_iter == m_end)
            return;  
        BOOST_CHECK_EQUAL((m_pos-1)/2, m_iter->pos_level);
        BOOST_CHECK_EQUAL(val, m_iter->val);
        ++m_iter;
    }
    
private:
    friend class boost::iterator_core_access;
    friend class boost::tree::cursor_core_access;
    
    typename mock_binary_cursor<Iter>::cursor_facade_::reference
    dereference() const
    {
        return const_cast< mock_binary_cursor<Iter>& >(*this);
    }

    bool equal(mock_binary_cursor<Iter> const& other) const
    {
        return false;
    }

    void increment()
    {
        ++m_pos;
    }
    
    void decrement()
    {
        --m_pos;
    }  

    void left()
    {
        m_pos *= 2;
        ++m_pos;
    }

    void right()
    {
        ++m_pos;
        m_pos *= 2;
    }

    void up()
    {
        --m_pos;
        m_pos /= 2;
    }
    
    bool const empty_() const
    {
        return true;
    }

    size_type const idx() const
    {
        return (m_pos + 1) % 2;
    }
    
    bool is_root_() const
    {
        return true;
    }
};

#endif // LIBS_TREE_TEST_MOCK_BINARY_CURSOR_HPP
