//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE cursor_algorithm test
#include <boost/test/included/unit_test.hpp>

#include <boost/tree/ascending_cursor.hpp>

#include "fake_binary_tree.hpp"

using namespace boost::tree;

BOOST_FIXTURE_TEST_SUITE( ascending_cursor_test, fake_binary_tree_fixture<int> )

BOOST_AUTO_TEST_CASE( test_ascending_cursor_constructors )
{
    typedef fake_binary_tree<int>::descending_cursor dc_t;
    typedef fake_binary_tree<int>::const_descending_cursor cdc_t;

    ascending_cursor<dc_t> ac1;
    ascending_cursor<dc_t> ac2(ac1);
    
    BOOST_CHECK(ac1 == ac2);
    
    ascending_cursor<cdc_t> cac1;
    ascending_cursor<cdc_t> cac2(cac1);

    BOOST_CHECK(cac1 == cac2);

    ascending_cursor<cdc_t> cac3(ac1);
    BOOST_CHECK(cac3 == ac1);
}

BOOST_AUTO_TEST_CASE( test_ascending_cursor )
{
    typedef fake_binary_tree<int>::descending_cursor dc_t;
    ascending_cursor<dc_t> ac = make_ascending_cursor(fbt1.descending_root());

    ac.to_begin().to_end().to_begin();

    BOOST_CHECK_EQUAL(*ac, 4);
    ac.to_parent();
    BOOST_CHECK_EQUAL(*ac, 6);
    ac.to_parent();
    BOOST_CHECK_EQUAL(*ac, 3);
    ac.to_parent();
    BOOST_CHECK_EQUAL(*ac, 8);
}

BOOST_AUTO_TEST_SUITE_END()