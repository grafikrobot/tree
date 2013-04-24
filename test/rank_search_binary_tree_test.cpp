//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/binary_tree.hpp>
#include <boost/tree/balancers/unbalanced.hpp>
#include <boost/tree/augmentors/rank.hpp>

#include <boost/tree/searcher.hpp>
#include <boost/tree/algorithm.hpp>



//TODO: Make this a test suite.


BOOST_AUTO_TEST_CASE( rank_search_binary_tree_test )
{
    using namespace boost::tree;
//    
//    typedef binary_tree<int, balancers::unbalanced, augmentors::rank<> > tree_t;
//    typedef searcher<false, tree_t> searcher_t;
//    searcher_t my_searcher;
//    
//    create_test_data_searcher(my_searcher);
//    tree_t& my_tree = my_searcher.container();
//    
//    tree_t::cursor c = select(my_tree, 3);
//    BOOST_CHECK(*c < 14);

//    typedef binary_tree<int, balancers::unbalanced, augmentors::rank<> > tree_t;
//    typedef test_searcher<false, tree_t> searcher_t;
//    searcher_t my_searcher;
//    
//    create_test_data_searcher(my_searcher);
//    tree_t& my_tree = my_searcher.container();
//
//    tree_t::cursor c = select_rank(my_tree, 3);
    //BOOST_CHECK(*c < 14);

}

//boost::unit_test::test_suite*
//init_unit_test_suite( int argc, char* argv[] )
//{
//    boost::unit_test::test_suite* rank_search_test = 
//            BOOST_TEST_SUITE( "Key search binary vector test" );
//
//    rank_search_test->add( BOOST_TEST_CASE( &rank_search_binary_tree_test ) );
//
//    return rank_search_test;
//}
