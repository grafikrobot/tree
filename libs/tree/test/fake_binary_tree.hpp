//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_TEST_FAKE_BINARY_TREE_HPP
#define LIBS_TREE_TEST_FAKE_BINARY_TREE_HPP

#include <boost/tree/cursor_facade.hpp>
#include <boost/tree/cursor_adaptor.hpp>

#include <vector>

#include "test_data.hpp"

template <class T, class HT> 
class fake_binary_cursor;

template <class T>
struct fake_root_tracking_binary_cursor;

using boost::tree::descending_vertical_traversal_tag;
using boost::tree::ascending_vertical_traversal_tag;

template <class T, class VT = descending_vertical_traversal_tag>
struct fake_binary_tree;

/// See http://en.wikipedia.org/wiki/Binary_Tree#Methods_for_storing_binary_trees
template <class T>
struct fake_binary_tree<T, descending_vertical_traversal_tag> {
    typedef std::vector<T> children_type;
    typedef typename children_type::size_type size_type;
    typedef typename children_type::value_type value_type;
    typedef typename children_type::difference_type difference_type;
    typedef typename children_type::pointer pointer;
    typedef typename children_type::reference reference;

    typedef fake_binary_cursor<T, descending_vertical_traversal_tag> descending_cursor;
    typedef fake_binary_cursor<T/* const*/, descending_vertical_traversal_tag> const_descending_cursor; //FIXME

    typedef descending_cursor cursor;
    typedef const_descending_cursor const_cursor;
    
protected:
    typedef fake_binary_cursor<T, ascending_vertical_traversal_tag> ascending_cursor;
    typedef fake_binary_cursor<T, ascending_vertical_traversal_tag> const_ascending_cursor; //FIXME

    typedef fake_root_tracking_binary_cursor<T> root_tracking_cursor;
    typedef fake_root_tracking_binary_cursor<T> const_root_tracking_cursor; //FIXME

public:        
    fake_binary_tree(size_type s = 0) : m_data(s)
    { }
    
    descending_cursor descending_root()
    {
        return descending_cursor(*this, 0);
    }

    descending_cursor root()
    {
        return descending_cursor(*this, 0);
    }

    const_descending_cursor root() const
    {
        return const_descending_cursor(*this, 0);
    }

protected:
    ascending_cursor ascending_root()
    {
        return ascending_cursor(*this, 0);
    }

    const_ascending_cursor ascending_root() const
    {
        return const_ascending_cursor(*this, 0);
    }

    root_tracking_cursor root_tracking_root()
    {
        return root_tracking_cursor(*this, 0);
    }

    const_root_tracking_cursor root_tracking_root() const
    {
        return const_root_tracking_cursor(*this, 0);
    }

public:
    descending_cursor insert(descending_cursor c, value_type const& v)
    {
        if (c.m_pos >= m_data.size())
            m_data.resize(c.m_pos + 1);
        else {
            value_type tmp;
            size_type s = c.m_pos;
            
            while (m_data[s]) {
                tmp = m_data[s];
                s = 2*s + 1 + c.index();

                if (s >= m_data.size()) {
                    m_data.resize(s + 1);
                    m_data[s] = tmp;
                    break;
                }
                m_data[s] = tmp;
            }
        }
        
        m_data[c.m_pos] = v;
        return c;
    }

//    ascending_cursor insert(ascending_cursor c, value_type const& v)
//    {
//        m_data[c.m_pos] = v;
//        return c;
//    }
//
//    root_tracking_cursor insert(root_tracking_cursor c, value_type const& v)
//    {
//        m_data[c.m_pos] = v;
//        return c;
//    }
    
    children_type m_data;  
};

template <class T>
struct fake_binary_tree<T, ascending_vertical_traversal_tag>
: fake_binary_tree<T, descending_vertical_traversal_tag> {
    typedef typename fake_binary_tree<T>::size_type size_type;
    typedef typename fake_binary_tree<T>::ascending_cursor cursor;
    typedef typename fake_binary_tree<T>::const_ascending_cursor const_cursor;
    
    fake_binary_tree(size_type s = 0)
    : fake_binary_tree<T, descending_vertical_traversal_tag>(s) { }
    
    fake_binary_tree(fake_binary_tree<T, descending_vertical_traversal_tag> const& f)
    : fake_binary_tree<T, descending_vertical_traversal_tag>(f) { }

    cursor root()
    {
        return fake_binary_tree<T, descending_vertical_traversal_tag>::ascending_root();
    }

    const_cursor root() const
    {
        return fake_binary_tree<T, descending_vertical_traversal_tag>::ascending_root();
    }
};

template <class T>
struct fake_root_tracking_binary_tree
: fake_binary_tree<T, descending_vertical_traversal_tag> {
    typedef typename fake_binary_tree<T>::size_type size_type;
    typedef typename fake_binary_tree<T>::root_tracking_cursor cursor;
    typedef typename fake_binary_tree<T>::const_root_tracking_cursor const_cursor;
    
    fake_root_tracking_binary_tree(size_type s = 0)
    : fake_binary_tree<T, descending_vertical_traversal_tag>(s) { }
    
    fake_root_tracking_binary_tree(fake_binary_tree<T, descending_vertical_traversal_tag> const& f)
    : fake_binary_tree<T, descending_vertical_traversal_tag>(f) { }

    cursor root()
    {
        return fake_binary_tree<T, descending_vertical_traversal_tag>::root_tracking_root();
    }

    const_cursor root() const
    {
        return fake_binary_tree<T, descending_vertical_traversal_tag>::root_tracking_root();
    }
};

template <class T, class VT>
bool operator==(fake_binary_tree<T, VT> const& x, fake_binary_tree<T, VT> const& y)
{
    return (x.m_data == y.m_data);
}

template <class T, class VT>
bool operator!=(fake_binary_tree<T, VT> const& x, fake_binary_tree<T, VT> const& y)
{
    return !(x == y);
}

// This should be easily extensible to nary by replacing the
// factor 2 by n in dereference, left, right and idx. 
template <class T> 
class fake_binary_cursor<T, descending_vertical_traversal_tag>
: public boost::tree::cursor_facade<
        fake_binary_cursor<T, descending_vertical_traversal_tag>
      , T
      , boost::bidirectional_traversal_tag
      , boost::tree::descending_vertical_traversal_tag
    >
{
public:
    typedef fake_binary_cursor<T, descending_vertical_traversal_tag> cursor;
    typedef fake_binary_cursor<T/* const*/, descending_vertical_traversal_tag> const_cursor;

    typedef typename fake_binary_cursor<T, descending_vertical_traversal_tag>::cursor_facade_::size_type size_type;
    typedef size_type subtree_size_type;

    fake_binary_cursor()
    : m_tree(0), m_pos(0) {}

    explicit fake_binary_cursor(fake_binary_tree<T>& t, size_type p = 0)
    : m_tree(&t), m_pos(p) {}
    
    fake_binary_cursor(fake_binary_cursor<T, descending_vertical_traversal_tag> const& other)
    : m_tree(other.m_tree), m_pos(other.m_pos) {}

    fake_binary_cursor<T, descending_vertical_traversal_tag>& operator=(fake_binary_cursor<T, descending_vertical_traversal_tag> const& other)
    {
        m_tree = other.m_tree;
        m_pos = other.m_pos;
        return *this;
    }

    fake_binary_tree<T>* m_tree;
    typename fake_binary_tree<T>::size_type m_pos;

private:
    friend class boost::iterator_core_access;
    friend class boost::tree::cursor_core_access;

    static const 
    typename fake_binary_cursor<T, descending_vertical_traversal_tag>::cursor_facade_::value_type def_val
    = typename fake_binary_cursor<T, descending_vertical_traversal_tag>::cursor_facade_::value_type();

    typename fake_binary_cursor<T, descending_vertical_traversal_tag>::cursor_facade_::reference
    dereference() const
    {
        return m_tree->m_data[m_pos];
    }

    bool equal(fake_binary_cursor<T, descending_vertical_traversal_tag> const& other) const
    {
        return (this->m_tree == other.m_tree) 
            && (this->m_pos == other.m_pos);
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
    
    bool const empty_() const
    {
        if (m_pos >= m_tree->m_data.size())
            return true;
        if (m_pos == 0)
            return false;
        return (m_tree->m_data[m_pos] == def_val);
    }

    size_type const idx() const
    {
        return (m_pos + 1) % 2;
    }
};        

template <class T>
typename fake_binary_cursor<T, descending_vertical_traversal_tag>::size_type
index(fake_binary_cursor<T, descending_vertical_traversal_tag> const& cur)
{
    return cur.index();
}

template <class T>
struct fake_binary_cursor<T, ascending_vertical_traversal_tag>
: public boost::tree::cursor_adaptor<fake_binary_cursor<T, ascending_vertical_traversal_tag>
                                   , fake_binary_cursor<T, descending_vertical_traversal_tag>
                                   , boost::use_default
                                   , boost::use_default
                                   , boost::tree::ascending_vertical_traversal_tag >
{
    typedef fake_binary_cursor<T, ascending_vertical_traversal_tag> cursor;
    typedef fake_binary_cursor<T const, ascending_vertical_traversal_tag> const_cursor;

    fake_binary_cursor(fake_binary_tree<T>& t
                                    , typename fake_binary_tree<T>::size_type p)
    : fake_binary_cursor::cursor_adaptor_(fake_binary_cursor<T, descending_vertical_traversal_tag>(t, p)) {}

private: 
    friend class boost::iterator_core_access;
    friend class boost::tree::cursor_core_access;
    
    void up()
    {
        --this->base_reference().m_pos;
        this->base_reference().m_pos /= 2;
    }

public:
    bool is_root() const
    {
        return this->base_reference().m_pos == 0;
    }
};

template <class T>
struct fake_root_tracking_binary_cursor
: public boost::tree::cursor_adaptor<fake_root_tracking_binary_cursor<T>
                                   , fake_binary_cursor<T, ascending_vertical_traversal_tag>
                                    >
{
    typedef fake_root_tracking_binary_cursor<T> cursor;
    typedef fake_root_tracking_binary_cursor<T const> const_cursor;

    fake_root_tracking_binary_cursor(fake_binary_tree<T>& t
                                    , typename fake_binary_tree<T>::size_type p)
    : fake_root_tracking_binary_cursor::cursor_adaptor_(fake_binary_cursor<T, ascending_vertical_traversal_tag>(t, p)) {}

private: 
    friend class boost::iterator_core_access;
    friend class boost::tree::cursor_core_access;

public:
    bool is_root() const
    {
        return this->base_reference().is_root();
    }
};

fake_binary_tree<int> generate_fake_binary_tree()
{
    test_data_set mpo;
    mock_cursor_data(mpo);

    typedef test_data_set::nth_index<0>::type container_type;
    const container_type& order_index = mpo.get<0>();

    container_type::const_iterator ci = order_index.begin();
    container_type::const_iterator cie = order_index.end();
    
    fake_binary_tree<int> mt(57);
    
    for(;ci!=cie;++ci) {
        if (ci->pos_level >= mt.m_data.size())
            mt.m_data.resize(ci->pos_level + 1);
        mt.m_data[ci->pos_level] = ci->val;
    }

    return mt;
}

template <class T = int>
struct fake_binary_tree_fixture {
    fake_binary_tree_fixture() : fbt1(generate_fake_binary_tree()), fbt2(57) {}
    
    template <class Cursor>
    static void validate_test_dataset1_tree(Cursor cur)
    {
        BOOST_CHECK_EQUAL(*cur, 8);
        BOOST_CHECK_EQUAL(*cur.begin(), 3);
        BOOST_CHECK_EQUAL(*cur.begin().begin(), 1);  //Leaf
        BOOST_CHECK_EQUAL(*cur.begin().end(), 6);
        BOOST_CHECK_EQUAL(*cur.begin().end().begin(), 4); //Leaf
        BOOST_CHECK_EQUAL(*cur.begin().end().end(), 7); //Leaf
        BOOST_CHECK_EQUAL(*cur.end(), 10);
        BOOST_CHECK_EQUAL(*cur.end().end(), 14);
        BOOST_CHECK_EQUAL(*cur.end().end().begin(), 13);
        BOOST_CHECK_EQUAL(*cur.end().end().begin().begin(), 11); 
        BOOST_CHECK_EQUAL(*cur.end().end().begin().begin().end(), 12); //Leaf
    }

    template <class Cursor>
    static void validate_test_dataset1_minus_1_tree(Cursor cur)
    {
        BOOST_CHECK_EQUAL(*cur, 7);
        BOOST_CHECK_EQUAL(*cur.begin(), 2);    
        BOOST_CHECK_EQUAL(*cur.begin().begin(), 0);  //Leaf
        BOOST_CHECK_EQUAL(*cur.begin().end(), 5);        
        BOOST_CHECK_EQUAL(*cur.begin().end().begin(), 3); //Leaf
        BOOST_CHECK_EQUAL(*cur.begin().end().end(), 6); //Leaf
    
        BOOST_CHECK_EQUAL(*cur.end(), 9);
        BOOST_CHECK_EQUAL(*cur.end().end(), 13);
        BOOST_CHECK_EQUAL(*cur.end().end().begin(), 12);
        BOOST_CHECK_EQUAL(*cur.end().end().begin().begin(), 10); 
        BOOST_CHECK_EQUAL(*cur.end().end().begin().begin().end(), 11); //Leaf
    }
    
    fake_binary_tree<T> fbt1, fbt2;
};

//template <class T = int>
//struct fake_binary_tree_with_list_fixture
//: public fake_binary_tree_fixture<T>
//, public test_with_list_fixture {
//     fake_binary_tree_with_list_fixture()
//     : fake_binary_tree_fixture<T>()
//     , test_with_list_fixture() {}
//};

#endif // LIBS_TREE_TEST_FAKE_BINARY_TREE_HPP
