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

BOOST_AUTO_TEST_CASE_TEMPLATE( test_to_last, Order, orders )
{
    test_data_set mpo;
    mock_cursor_data(mpo);

    typename test_data_set::index<Order>::type::const_iterator cie
    = mpo.get<Order>().end();
    --cie;

    fake_root_tracking_binary_tree<int> frbt1(fbt1);
    fake_root_tracking_binary_tree<int>::cursor c = frbt1.root();
    fake_root_tracking_binary_tree<int>::cursor d = frbt1.root();
    boost::tree::to_last(Order(), c);
    fake_to_last(Order(), d);
    BOOST_CHECK(c == d);
//    boost::tree::predecessor(Order(), c);
//    BOOST_CHECK_EQUAL(*c, cie->val);
}

BOOST_AUTO_TEST_CASE( test_to_past )
{
    fake_root_tracking_binary_tree<int> frbt1(fbt1);
    fake_root_tracking_binary_tree<int>::cursor c = frbt1.root();
    fake_root_tracking_binary_tree<int>::cursor d = frbt1.root();

    boost::tree::to_past(inorder(), c);
    fake_to_past(inorder(), d);
    BOOST_CHECK(c == d);

	c = frbt1.root();
    fake_to_last(inorder(), c);
    boost::tree::last_to_past(inorder(), c);
    BOOST_CHECK(c == d);

    d = frbt1.root();
    fake_to_last(inorder(), d);
    boost::tree::past_to_last(inorder(), c);
    BOOST_CHECK(c == d);

    c = frbt1.root();
    fake_to_past(inorder(), c);
    d = frbt1.root();
    fake_to_last(inorder(), d);
    boost::tree::predecessor(inorder(), c);
    BOOST_CHECK(c == d);
}

BOOST_AUTO_TEST_SUITE_END()
