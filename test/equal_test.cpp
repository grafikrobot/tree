//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/algorithm.hpp>

#include <boost/lambda/bind.hpp>

#include <boost/tree/forest.hpp>

#define BOOST_TEST_MODULE cursor_algorithm test
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>


#include "test_tree_traversal_data.hpp"

#include "fake_binary_tree.hpp"

using namespace boost::tree;

BOOST_FIXTURE_TEST_SUITE(cursor_algorithms_test, fake_binary_tree_fixture<int>)

BOOST_AUTO_TEST_CASE( test_equal )
{
    BOOST_CHECK(equal(fbt1.root(), fbt1.root()));
    BOOST_CHECK(!equal(fbt1.root(), fbt2.root()));
    // TODO: Also check with empty trees
}

BOOST_AUTO_TEST_CASE( test_equal_pred )
{
    BOOST_CHECK(boost::tree::equal(fbt1.root(), fbt1.root(), std::equal_to<int>()));
    BOOST_CHECK(!boost::tree::equal(fbt1.root(), fbt2.root(), std::equal_to<int>()));
}

BOOST_AUTO_TEST_CASE( test_size )
{
    BOOST_CHECK_EQUAL(size(fbt1.root()), 11);
}

BOOST_AUTO_TEST_SUITE_END()