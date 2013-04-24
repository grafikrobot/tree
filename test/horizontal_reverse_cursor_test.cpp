//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE cursor_algorithm test
#include <boost/test/included/unit_test.hpp>

#include <boost/tree/horizontal_reverse_cursor.hpp>

#include "fake_binary_tree.hpp"

using namespace boost::tree;

BOOST_FIXTURE_TEST_SUITE( horizontal_reverse_cursor_test, fake_binary_tree_fixture<int> )

BOOST_AUTO_TEST_CASE( test_horizontal_reverse_cursor )
{
    horizontal_reverse_cursor<fake_binary_tree<int>::descending_cursor> cur(fbt1.root());
    
    // TODO: Also check ++ and -- operators!
    
    BOOST_CHECK_EQUAL(*cur, 8);
    BOOST_CHECK_EQUAL(*cur.end(), 3);
    BOOST_CHECK_EQUAL(*cur.end().end(), 1);
    BOOST_CHECK(cur.end().end().begin().is_leaf());
    BOOST_CHECK(cur.end().end().end().is_leaf()); //Leaf
    
    BOOST_CHECK_EQUAL(*cur.end().begin(), 6);
    BOOST_CHECK_EQUAL(*cur.end().begin().end(), 4);
    BOOST_CHECK(cur.end().begin().end().end().is_leaf()); //Leaf

    BOOST_CHECK_EQUAL(*cur.end().begin().begin(), 7);
    BOOST_CHECK(cur.end().begin().begin().end().is_leaf()); //Leaf

    BOOST_CHECK_EQUAL(*cur.begin(), 10);
    BOOST_CHECK(cur.begin().end().is_leaf());
    BOOST_CHECK_EQUAL(*cur.begin().begin(), 14);
    BOOST_CHECK(cur.begin().begin().begin().is_leaf());
    BOOST_CHECK_EQUAL(*cur.begin().begin().end(), 13);
    BOOST_CHECK(cur.begin().begin().end().begin().is_leaf());
    BOOST_CHECK_EQUAL(*cur.begin().begin().end().end(), 11);
    BOOST_CHECK(cur.begin().begin().end().end().end().is_leaf()); 
    BOOST_CHECK_EQUAL(*cur.begin().begin().end().end().begin(), 12);
    BOOST_CHECK(cur.begin().begin().end().end().begin().end().is_leaf()); //Leaf
}

BOOST_AUTO_TEST_SUITE_END()