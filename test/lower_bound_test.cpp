//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/algorithm.hpp>

//#define BOOST_TEST_MODULE cursor_algorithm test

//#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

using namespace boost::unit_test;

#include "fake_binary_tree.hpp"

using namespace boost::tree;

template <class T>
struct val_less
: public std::binary_function <T, int, bool>
{
    bool operator() (const T& x, const int y) const
    {
        return x.val < y;
    }
};

void lower_bound_test(int i)
{
    fake_binary_tree_fixture<int> f;
    fake_binary_tree<int>::cursor c(f.fbt1, 0), d(f.fbt1, 0);

    test_data_set mpo;
    mock_cursor_data(mpo);

    c = lower_bound(f.fbt1.root(), i);
    test_data_set::index<inorder>::type::const_iterator ci 
    = std::lower_bound(mpo.get<inorder>().begin(), mpo.get<inorder>().end(), i
                     , val_less<test_data_set::value_type>());
    BOOST_CHECK_EQUAL(*c, ci->val);
}    

void lower_bound_pred_test(int i)
{   
    fake_binary_tree_fixture<int> f;
    fake_binary_tree<int>::cursor c(f.fbt1, 0), d(f.fbt1, 0);

    test_data_set mpo;
    mock_cursor_data(mpo);

    c = lower_bound(f.fbt1.root(), i, std::less<int>());
    test_data_set::index<inorder>::type::const_iterator ci 
    = std::lower_bound(mpo.get<inorder>().begin(), mpo.get<inorder>().end(), i
                     , val_less<test_data_set::value_type>());
    BOOST_CHECK_EQUAL(*c, ci->val);
}

test_suite*
init_unit_test_suite( int argc, char* argv[] )
{
    int params[] = { 4, 7, 6, 8, 5 };
//    4: Left Leaf
//    7: Right Leaf
//    6: Non-Leaf
//    8: Non-Leaf, Root
//    5: Not in Tree

    framework::master_test_suite().
        add( BOOST_PARAM_TEST_CASE( &lower_bound_test, params, params+5 ) );
    framework::master_test_suite().
        add( BOOST_PARAM_TEST_CASE( &lower_bound_pred_test, params, params+5 ) );

    return 0;
}