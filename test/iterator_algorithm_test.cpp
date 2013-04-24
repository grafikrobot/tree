//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/iterator.hpp>

#define BOOST_TEST_MODULE iterator_algorithm test
#include <boost/test/included/unit_test.hpp>

#include "fake_binary_tree.hpp"
#include "test_tree_traversal_data.hpp"

using namespace boost::tree;

// We should actually just check if operators++ and -- call next and prior
// and also begin() and end() (call to_first(), to_last())
// Use a mock cursor object?

BOOST_FIXTURE_TEST_SUITE( iterator_algorithms_test, fake_binary_tree_fixture<int> )

BOOST_AUTO_TEST_CASE( test_iterator )
{

}

//BOOST_AUTO_TEST_CASE_TEMPLATE( test_iterator_algorithms, Order, orders )
//{
//    test_traversal(Order(), begin(Order(), fbt1.ascending_root())
//                          , end(Order(), fbt1.ascending_root()));
//
//    test_reverse_traversal(Order(), end(Order(), fbt1.ascending_root())
//                                  , begin(Order(), fbt1.ascending_root()));
//                                    
//    BOOST_CHECK_EQUAL(std::distance(begin(Order(), fbt1.ascending_root()) 
//                                  , end(Order(), fbt1.ascending_root())), 11);
//}
//
//BOOST_AUTO_TEST_CASE( test_subtree3_iterator_algorithms )
//{
//    test_subtree_traversal(preorder(), begin(preorder(), fbt1.ascending_root().begin())
//                                     , end(preorder(), fbt1.ascending_root().begin()), 1);
//    BOOST_CHECK_EQUAL(std::distance(begin(preorder(), fbt1.ascending_root().begin())
//                                  , end(preorder(), fbt1.ascending_root().begin())), 5);
//
//    test_subtree_traversal(inorder(), begin(inorder(), fbt1.ascending_root().begin())
//                                    , end(inorder(), fbt1.ascending_root().begin()), 0);
//    BOOST_CHECK_EQUAL(std::distance(begin(inorder(), fbt1.ascending_root().begin())
//                                  , end(inorder(), fbt1.ascending_root().begin())), 5);
//
//    test_subtree_traversal(postorder(), begin(postorder(), fbt1.ascending_root().begin())
//                                      , end(postorder(), fbt1.ascending_root().begin()), 0);
//    BOOST_CHECK_EQUAL(std::distance(begin(postorder(), fbt1.ascending_root().begin())
//                                  , end(postorder(), fbt1.ascending_root().begin())), 5);
//}
//
//BOOST_AUTO_TEST_CASE( test_subtree6_iterator_algorithms )
//{
//    test_subtree_traversal(preorder(), begin(preorder(), fbt1.ascending_root().begin().end())
//                                     , end(preorder(), fbt1.ascending_root().begin().end()), 3);
//    BOOST_CHECK_EQUAL(std::distance(begin(preorder(), fbt1.ascending_root().begin().end())
//                                  , end(preorder(), fbt1.ascending_root().begin().end())), 3);
//
//    test_subtree_traversal(inorder(), begin(inorder(), fbt1.ascending_root().begin().end())
//                                    , end(inorder(), fbt1.ascending_root().begin().end()), 2);
//    BOOST_CHECK_EQUAL(std::distance(begin(inorder(), fbt1.ascending_root().begin().end())
//                                  , end(inorder(), fbt1.ascending_root().begin().end())), 3);
//
//    test_subtree_traversal(postorder(), begin(postorder(), fbt1.ascending_root().begin().end())
//                                      , end(postorder(), fbt1.ascending_root().begin().end()), 1);
//    BOOST_CHECK_EQUAL(std::distance(begin(postorder(), fbt1.ascending_root().begin().end())
//                                  , end(postorder(), fbt1.ascending_root().begin().end())), 3);
//}
//
//BOOST_AUTO_TEST_CASE( test_subtree10_iterator_algorithms )
//{
//    test_subtree_traversal(preorder(), begin(preorder(), fbt1.ascending_root().end())
//                                     , end(preorder(), fbt1.ascending_root().end()), 6);
//    BOOST_CHECK_EQUAL(std::distance(begin(preorder(), fbt1.ascending_root().end())
//                                  , end(preorder(), fbt1.ascending_root().end())), 5);
//
//    test_subtree_traversal(inorder(), begin(inorder(), fbt1.ascending_root().end())
//                                    , end(inorder(), fbt1.ascending_root().end()), 6);
//    BOOST_CHECK_EQUAL(std::distance(begin(inorder(), fbt1.ascending_root().end())
//                                  , end(inorder(), fbt1.ascending_root().end())), 5);
//
//    test_subtree_traversal(postorder(), begin(postorder(), fbt1.ascending_root().end())
//                                      , end(postorder(), fbt1.ascending_root().end()), 5);
//    BOOST_CHECK_EQUAL(std::distance(begin(postorder(), fbt1.ascending_root().end())
//                                  , end(postorder(), fbt1.ascending_root().end())), 5);
//}

BOOST_AUTO_TEST_SUITE_END()