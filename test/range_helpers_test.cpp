//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/detail/range_helpers.hpp>

#define BOOST_TEST_MODULE range_helpers test
//#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>

#include <vector>

void test_binary_lower_bound()
{
    using boost::tree::binary_lower_bound;
    
    std::vector<int> vec(1, 9);
    
    std::vector<int>::const_iterator ci = 
        binary_lower_bound(vec.begin(), vec.end(), 9, std::less<int>());
    BOOST_CHECK(ci == vec.begin());
    
    ci = binary_lower_bound(vec.begin(), vec.end(), 7, std::less<int>());
    BOOST_CHECK(ci == vec.begin());
    
    ci = binary_lower_bound(vec.begin(), vec.end(), 17, std::less<int>());
    BOOST_CHECK(ci == vec.end());
}

void test_binary_upper_bound()
{
    using boost::tree::binary_upper_bound;
    std::vector<int> vec(1, 9);
    
    std::vector<int>::const_iterator ci = 
        binary_upper_bound(vec.begin(), vec.end(), 7, std::less<int>());
    BOOST_CHECK(ci == vec.begin());
    
    ci = binary_upper_bound(vec.begin(), vec.end(), 9, std::less<int>());
    BOOST_CHECK(ci == vec.end());
    
    ci = binary_upper_bound(vec.begin(), vec.end(), 17, std::less<int>());
    BOOST_CHECK(ci == vec.end());
}

static std::vector<int>&
vec()
{
    static std::vector<int> myvec(7);
    myvec[0] = -6;
    myvec[1] = -2;
    myvec[2] = -2;
    myvec[3] =  0;
    myvec[4] =  7;
    myvec[5] =  7;
    myvec[6] = 12;
    return myvec;
}

void test_linear_lower_bound()
{
    using boost::tree::linear_lower_bound;
    
    std::vector<int>::const_iterator ci = 
        linear_lower_bound(vec().begin(), vec().end(), 7, std::less<int>());
    BOOST_CHECK(ci == (vec().begin() + 4));
    
    ci = linear_lower_bound(vec().begin(), vec().end(), 9, std::less<int>());
    BOOST_CHECK(ci == (vec().begin() + 6));
    
    ci = linear_lower_bound(vec().begin(), vec().end(), 17, std::less<int>());
    BOOST_CHECK(ci == vec().end());
}

void test_linear_upper_bound()
{
    using boost::tree::linear_upper_bound;
    
    std::vector<int>::const_iterator ci = 
        linear_upper_bound(vec().begin(), vec().end(), 7, std::less<int>());
    BOOST_CHECK(ci == (vec().begin() + 6));
    
    ci = linear_upper_bound(vec().begin(), vec().end(), 9, std::less<int>());
    BOOST_CHECK(ci == (vec().begin() + 6));
    
    ci = linear_upper_bound(vec().begin(), vec().end(), 17, std::less<int>());
    BOOST_CHECK(ci == vec().end());
}

BOOST_AUTO_TEST_CASE( range_helpers_test )
{
    test_binary_lower_bound();
    test_binary_upper_bound();
    
    test_linear_lower_bound();
    test_linear_upper_bound();
}
