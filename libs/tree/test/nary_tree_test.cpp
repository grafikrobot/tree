//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/nary_tree.hpp>

#define BOOST_TEST_MODULE nary_tree test
//#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( nary_tree_test )
{
    using namespace boost::tree;
    
    typedef nary_tree<int> tree_type;
    tree_type mytree;
    tree_type::cursor c = mytree.root();
    BOOST_CHECK(mytree.root().is_leaf());
    BOOST_CHECK(c.is_leaf());

    c = mytree.insert(c, 4);
    BOOST_CHECK_EQUAL(*c, 4);
    BOOST_CHECK_EQUAL(c, mytree.root());
    BOOST_CHECK(c.is_leaf());
    
    c = mytree.insert(c, 5);
    BOOST_CHECK_EQUAL(*c, 5);
    BOOST_CHECK_EQUAL(c, mytree.root());
    ++c;
    BOOST_CHECK_EQUAL(*c, 4);
    BOOST_CHECK(c != mytree.root());
    BOOST_CHECK(c.is_leaf());
//    BOOST_CHECK(c.m_cur != tree_type::node_type::nil());

    mytree.insert(c.end(), 3);
    BOOST_CHECK_EQUAL(*(c.begin()), 3);
    BOOST_CHECK(!c.is_leaf());
    BOOST_CHECK_EQUAL(c, c.begin().parent());

}
