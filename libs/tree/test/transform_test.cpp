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
#include "mock_binary_cursor.hpp"
#include "fake_binary_tree.hpp"

using namespace boost::tree;

// TODO: Actually transform back and forth; eg, add 1 using STL transform, then subtract it
// again using the subtree algorithm.

BOOST_FIXTURE_TEST_SUITE(cursor_algorithms_test, fake_binary_tree_fixture<int>)

BOOST_AUTO_TEST_CASE_TEMPLATE( test_transform_descending, Order, orders)
{
    test_data_set mpo;
    mock_cursor_data(mpo);

    typedef typename test_data_set::index<Order>::type container_type;
    const container_type& order_index = mpo.get<Order>();

    typename container_type::const_iterator ci = order_index.begin();
    typename container_type::const_iterator cie = order_index.end();
    mock_binary_cursor< typename container_type::const_iterator > mc(ci, cie);
    
    //boost::tree::transform(Order(), fbt1.root(), mc, std::bind2nd(std::plus<int>(),0));
}

BOOST_AUTO_TEST_CASE_TEMPLATE( test_transform_ascending, Order, orders)
{
    test_data_set mpo;
    mock_cursor_data(mpo);

    typedef typename test_data_set::index<Order>::type container_type;
    const container_type& order_index = mpo.get<Order>();

    typename container_type::const_iterator ci = order_index.begin();
    typename container_type::const_iterator cie = order_index.end();
//    mock_binary_cursor< typename container_type::const_iterator > mc(ci, cie);
    
//    fake_binary_tree<int, boost::tree::ascending_vertical_traversal_tag> fabt1(fbt1);
//    boost::tree::transform(Order(), fabt1.root(), mc, std::bind2nd(std::plus<int>(),0));
}

BOOST_AUTO_TEST_SUITE_END()
