//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/multiway_tree.hpp>

#define BOOST_TEST_MODULE multiway_tree test
//#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>

//TODO: Make this a test suite.

BOOST_AUTO_TEST_CASE( multiway_tree_test )
{
    using namespace boost::tree;
    
    typedef multiway_tree<int> tree_type;
    tree_type mytree;

    //tree_type::cursor c = 
    //mytree.insert(mytree.root(), 3);
}