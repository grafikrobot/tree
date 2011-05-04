//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/balance.hpp>
#include <boost/tree/detail/balancers/unbalanced.hpp>
#include <boost/tree/binary_tree.hpp>

#define BOOST_TEST_MODULE balance test
//#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>

// TODO: Use a mock_binary_tree.
BOOST_AUTO_TEST_CASE( balance_constructors_test )
{
    using namespace boost::tree;
    typedef binary_tree<int> tree_t;
    typedef balance<tree_t, balancers::unbalanced> balance_t;
    balance_t t1;
    
    balance_t t2(t1);
}

BOOST_AUTO_TEST_CASE( balance_iterator_test )
{
    using namespace boost::tree;
    typedef binary_tree<int> tree_t;
    typedef balance<tree_t, balancers::unbalanced> balance_t;
    
    balance_t::iterator it1;
    balance_t::iterator it2(it1);
}

BOOST_AUTO_TEST_CASE( balance_test )
{
    using namespace boost::tree;
    
    typedef binary_tree<int> tree_t;
    typedef balance<tree_t, balancers::unbalanced> balance_t;
    balance_t my_tree; 
    
    balance_t::iterator c, c1, c2, c3, c4, c5;

    c = my_tree.end();
    BOOST_CHECK(c == my_tree.end());
    BOOST_CHECK(c == my_tree.begin());
        
    c1 = my_tree.insert(c, 8);
    BOOST_CHECK(c1 == my_tree.begin());
    
    BOOST_CHECK_EQUAL(*c1, 8);
    
    c1 = my_tree.insert(c1, 7);
    BOOST_CHECK_EQUAL(*c1, 7);

    ++c1;
    BOOST_CHECK_EQUAL(*c1, 8);

    ++c1;
    BOOST_CHECK(c1 == my_tree.end());
    
    c1 = my_tree.insert(my_tree.end(), 10);
    BOOST_CHECK_EQUAL(*c1, 10);
    
    --c1;
    BOOST_CHECK_EQUAL(*c1, 8);
    
    --c1;
    BOOST_CHECK_EQUAL(*c1, 7);
    
    c = my_tree.lower_bound(8);
    BOOST_CHECK_EQUAL(*c, 8);
    
    ++c;
    BOOST_CHECK_EQUAL(*c, 10);
    --c;
    BOOST_CHECK_EQUAL(*c, 8);
    --c;
    BOOST_CHECK_EQUAL(*c, 7);
    ++c;
    BOOST_CHECK_EQUAL(*c, 8);
    //c = my_tree.erase(c);
    --c;
    BOOST_CHECK_EQUAL(*c, 7);
    
}
