//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/algorithm.hpp>

#include <boost/lambda/bind.hpp>

#define BOOST_TEST_MODULE cursor_algorithm test
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>


#include "test_tree_traversal_data.hpp"

#include "fake_binary_tree.hpp"

using namespace boost::tree;

BOOST_AUTO_TEST_SUITE( empty_subtree_algorithms_test )

BOOST_AUTO_TEST_CASE_TEMPLATE( test_first_equals_last, Order, orders )
{
    typedef fake_binary_tree<int> tree_type;
    tree_type fbt(1);
    tree_type::descending_cursor f = fbt.descending_root();
    tree_type::descending_cursor l = fbt.descending_root();
    boost::tree::to_first(Order(), f);
    boost::tree::to_first(Order(), l);
    BOOST_CHECK(f == l);
}

BOOST_AUTO_TEST_SUITE_END()