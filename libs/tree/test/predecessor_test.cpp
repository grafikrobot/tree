//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/algorithm.hpp>

#define BOOST_TEST_MODULE cursor_algorithm test
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>


#include "test_tree_traversal_data.hpp"

#include "fake_binary_tree.hpp"

using namespace boost::tree;

BOOST_FIXTURE_TEST_SUITE(cursor_algorithms_test, fake_binary_tree_fixture<int>)

BOOST_AUTO_TEST_CASE( test_rightmost )
{
    fake_root_tracking_binary_tree<int> frbt1(fbt1);
    fake_root_tracking_binary_tree<int>::cursor c = frbt1.root();
    to_rightmost(c);
    BOOST_CHECK(c.is_leaf());
    BOOST_CHECK(c == frbt1.root().end().end().end());
}

//typedef boost::mpl::list<boost::tree::preorder
//                        ,boost::tree::inorder> preandinorders;

BOOST_AUTO_TEST_CASE_TEMPLATE( test_predecessor, Order, orders )
{
    fake_root_tracking_binary_tree<int> frbt1(fbt1);
    fake_root_tracking_binary_tree<int>::cursor c = frbt1.root();
    fake_to_last(Order(), c);

    test_data_set mpo;
    mock_cursor_data(mpo);

    typedef typename test_data_set::index<Order>::type container_type;
    const container_type& order_index = mpo.get<Order>();

    typename container_type::const_reverse_iterator ci = order_index.rbegin();
    typename container_type::const_reverse_iterator cie = order_index.rend();

    --cie;
    for (; ci!=cie; ++ci) {
        BOOST_CHECK_EQUAL(*c, ci->val);
        BOOST_CHECK_EQUAL(boost::tree::predecessor(Order(), c), true);
    }

    BOOST_CHECK_EQUAL(*c, ci->val);

    fake_root_tracking_binary_tree<int>::cursor d = frbt1.root();
    fake_to_first(Order(), d);
    BOOST_CHECK(c == d);
    
    BOOST_CHECK_EQUAL(boost::tree::predecessor(Order(), c), false);
    BOOST_CHECK(c == frbt1.root());
}

BOOST_AUTO_TEST_SUITE_END()
