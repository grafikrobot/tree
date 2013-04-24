//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/forest.hpp>

#define BOOST_TEST_MODULE forest test
//#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>

#include "fake_binary_tree.hpp"

using namespace boost::tree;

template <class Forest>
static void create_test_dataset1_forest(Forest& f)
{
    // For augmented trees. (Why is this necessary? Nothing here is explicit!)
    typedef typename Forest::value_type value_type; 
    
    // Insert top level elements in their proper order.
    typename Forest::cursor cur = f.insert(f.end(), value_type(8));
    cur = f.insert(f.end(), value_type(10));
    cur = f.insert(f.end(), value_type(14));

    // Insert 8's child elements in a more random order to test if this also works.
    cur = f.begin().begin();
    cur = f.insert(cur, value_type(3));
    cur = f.insert(++cur, value_type(7));
    cur = f.insert(cur, value_type(6));

    cur = f.begin().begin().begin();
    cur = f.insert(cur, value_type(1));

    cur = f.begin().begin();
    cur = f.insert((++cur).to_begin(), value_type(4));

    cur = f.begin();
    cur = f.insert((++++cur).to_begin(), value_type(13));
    cur = f.insert(cur.to_begin(), value_type(11));
    cur = f.insert(++cur, value_type(12));
}

template <class Cursor>
static void validate_test_dataset1_forest(Cursor cur, Cursor e)
{
    Cursor c = cur;
    BOOST_CHECK_EQUAL(*c, 8);
    BOOST_CHECK_EQUAL(*c.to_begin(), 3);
    BOOST_CHECK_EQUAL(*++c, 6);
    BOOST_CHECK_EQUAL(*++c, 7);
    BOOST_CHECK(++c == cur.end());
    
    c = cur.begin();
    BOOST_CHECK_EQUAL(*c.to_begin(), 1);
    BOOST_CHECK(++c == cur.begin().end());

    c = cur.begin();
    ++c;
    Cursor d = c; 
    BOOST_CHECK_EQUAL(*c.to_begin(), 4);
    BOOST_CHECK(++c == d.end());
    
    c = cur;
    BOOST_CHECK_EQUAL(*++c, 10);
    BOOST_CHECK_EQUAL(*++c, 14);
    d = c;
    BOOST_CHECK(++c == e);
    c = d;
    BOOST_CHECK_EQUAL(*c.to_begin(), 13);
    BOOST_CHECK(++c == d.end());
    c = d.to_begin();
    BOOST_CHECK_EQUAL(*c.to_begin(), 11);
    BOOST_CHECK_EQUAL(*++c, 12);
    BOOST_CHECK(++c == d.end());
}

BOOST_AUTO_TEST_SUITE( basic_forest_test )

BOOST_AUTO_TEST_CASE( constructors_test )
{
    forest<int> ft0;
    BOOST_CHECK(ft0.empty());
    BOOST_CHECK(ft0.begin() == ft0.end());
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_FIXTURE_TEST_SUITE(forest_fixture_test, fake_binary_tree_fixture<int>)

BOOST_AUTO_TEST_CASE( binary_tree_constructor_test )
{
    forest<int, fake_binary_tree<int> > ft0(fbt1);
    validate_test_dataset1_forest(ft0.begin(), ft0.end());
}

BOOST_AUTO_TEST_CASE( insert_test )
{
    forest<int, fake_binary_tree<int> > ft0;
    create_test_dataset1_forest(ft0);
    validate_test_dataset1_forest(ft0.begin(), ft0.end());
}

BOOST_AUTO_TEST_SUITE_END()
