//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/algorithm.hpp>

#define BOOST_TEST_MODULE cursor_algorithm test
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>

#include "fake_binary_tree.hpp"
#include "test_tree_traversal_data.hpp"

using namespace boost::tree;

BOOST_FIXTURE_TEST_SUITE(cursor_algorithms_test, fake_binary_tree_fixture<int>)

BOOST_AUTO_TEST_CASE_TEMPLATE( test_to_first, Order, orders )
{
    test_data_set mpo;
    mock_cursor_data(mpo);

    typename test_data_set::index<Order>::type::const_iterator ci 
    = mpo.get<Order>().begin();
    
    fake_binary_tree<int>::descending_cursor c = fbt1.descending_root();
    fake_binary_tree<int>::descending_cursor d = fbt1.descending_root();
    boost::tree::to_first(Order(), c);
    fake_to_first(Order(), d);
    BOOST_CHECK(c == d);
    BOOST_CHECK_EQUAL(*c, ci->val);
}

BOOST_AUTO_TEST_SUITE_END()