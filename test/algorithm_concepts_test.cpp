//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/algorithm.hpp>

#include <boost/iterator/iterator_categories.hpp>

#include <boost/tree/cursor_archetypes.hpp>
#include <boost/concept_archetype.hpp>

#define BOOST_TEST_MODULE algorithm_concepts_algorithm test
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>

#include <boost/mpl/list.hpp>

typedef boost::mpl::list<boost::tree::preorder
                        ,boost::tree::inorder
                        ,boost::tree::postorder> orders;

using namespace boost::tree;

BOOST_AUTO_TEST_SUITE( algorithm_concepts_covering_test )

// Each order probably requires different concepts (eg inorder: multiway)! 
BOOST_AUTO_TEST_CASE_TEMPLATE( test_foreach, Order, orders )
{
    boost::detail::dummy_constructor dummy_cons;
    cursor_archetype< boost::null_archetype<>
                      , boost::iterator_archetypes::readable_lvalue_iterator_t // Really lvalue?
                      , boost::forward_traversal_tag    // Lesser requirement!
                      , boost::tree::descending_vertical_traversal_tag
                      > c;
    boost::unary_function_archetype< boost::null_archetype<> , boost::null_archetype<> > 
      f(dummy_cons);
    
    boost::tree::for_each(Order(), c, f);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( test_copy, Order, orders )
{
    cursor_archetype< int // Really int?
                      , boost::iterator_archetypes::readable_iterator_t
                      , boost::forward_traversal_tag
                      , boost::tree::descending_vertical_traversal_tag
                      > i;
    cursor_archetype< int // Really int?
                      , boost::iterator_archetypes::writable_iterator_t
                      , boost::forward_traversal_tag
                      , boost::tree::descending_vertical_traversal_tag
                      > o;
    
    o = boost::tree::copy(Order(), i, o);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( test_transform, Order, orders )
{
    boost::detail::dummy_constructor dummy_cons;
    cursor_archetype< int // Really int?
                      , boost::iterator_archetypes::readable_iterator_t
                      , boost::forward_traversal_tag
                      , boost::tree::descending_vertical_traversal_tag
                      > i;
    cursor_archetype< int // Really int?
                      , boost::iterator_archetypes::writable_iterator_t 
                      , boost::forward_traversal_tag
                      , boost::tree::descending_vertical_traversal_tag
                      > o;
    boost::unary_function_archetype< int , int > // Really int?
      f(dummy_cons);
    
    o = boost::tree::transform(Order(), i, o, f);
}

BOOST_AUTO_TEST_SUITE_END()