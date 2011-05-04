//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_TEST_TEST_TREE_TRAVERSAL_DATA_HPP
#define LIBS_TREE_TEST_TEST_TREE_TRAVERSAL_DATA_HPP

#include <boost/tree/algorithm.hpp>

#include <boost/mpl/list.hpp>

typedef boost::mpl::list<boost::tree::preorder
                        ,boost::tree::inorder
                        ,boost::tree::postorder> orders;

template <class Cursor>
static void validate_test_dataset1_tree(Cursor cur)
{
    BOOST_CHECK_EQUAL(*cur, 8);
    BOOST_CHECK_EQUAL(*cur.begin(), 3);
    BOOST_CHECK_EQUAL(*cur.begin().begin(), 1);
    BOOST_CHECK(cur.begin().begin().end().is_leaf());
    BOOST_CHECK(cur.begin().begin().begin().is_leaf()); //Leaf
    
    BOOST_CHECK_EQUAL(*cur.begin().end(), 6);
    BOOST_CHECK_EQUAL(*cur.begin().end().begin(), 4);
    BOOST_CHECK(cur.begin().end().begin().begin().is_leaf()); //Leaf

    BOOST_CHECK_EQUAL(*cur.begin().end().end(), 7);
    BOOST_CHECK(cur.begin().end().end().begin().is_leaf()); //Leaf

    BOOST_CHECK_EQUAL(*cur.end(), 10);
    BOOST_CHECK(cur.end().begin().is_leaf());
    BOOST_CHECK_EQUAL(*cur.end().end(), 14);
    BOOST_CHECK(cur.end().end().end().is_leaf());
    BOOST_CHECK_EQUAL(*cur.end().end().begin(), 13);
    BOOST_CHECK(cur.end().end().begin().end().is_leaf());
    BOOST_CHECK_EQUAL(*cur.end().end().begin().begin(), 11);
    BOOST_CHECK(cur.end().end().begin().begin().begin().is_leaf()); 
    BOOST_CHECK_EQUAL(*cur.end().end().begin().begin().end(), 12);
    BOOST_CHECK(cur.end().end().begin().begin().end().begin().is_leaf()); //Leaf
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

template <class Iterator>
void test_traversal_from_leaf4(Iterator a, Iterator b)
{    
    BOOST_CHECK_EQUAL(*a, 4);
    BOOST_CHECK_EQUAL(*++a, 6);
    BOOST_CHECK_EQUAL(*++a, 3);
    BOOST_CHECK_EQUAL(*++a, 8);
    BOOST_CHECK(++a == b);

}

template <class Cursor>
void fake_to_first(boost::tree::preorder, Cursor& c)
{}

template <class Cursor>
void fake_to_first(boost::tree::inorder, Cursor& c)
{
    c.to_begin().to_begin();
}

template <class Cursor>
void fake_to_first(boost::tree::postorder, Cursor& c)
{
    c.to_begin().to_begin();
}

template <class Cursor>
void fake_to_last(boost::tree::preorder, Cursor& c)
{
    c.to_end().to_end().to_begin().to_begin().to_end();
}

template <class Cursor>
void fake_to_last(boost::tree::inorder, Cursor& c)
{
    c.to_end().to_end();
}

template <class Cursor>
void fake_to_last(boost::tree::postorder, Cursor& c)
{}

template <class Cursor>
void fake_to_past(boost::tree::inorder, Cursor& c)
{
    c.to_end().to_end().to_end();
}

#endif // LIBS_TREE_TEST_TEST_TREE_TRAVERSAL_DATA_HPP
