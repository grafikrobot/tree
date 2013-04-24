//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/binary_tree.hpp>
#include <boost/tree/balancers/unbalanced.hpp>

#include <boost/tree/searcher.hpp>
#include <boost/tree/algorithm.hpp>

#define BOOST_TEST_MODULE key_search test
//#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>



//TODO: Make this a test suite.

BOOST_AUTO_TEST_CASE( key_search_binary_tree_test )
{
    using namespace boost::tree;
    
    typedef test_searcher<false, balance<binary_tree<int>, balancers::unbalanced> > searcher_t;
    searcher_t my_tree;
    
    searcher_t::iterator c, c1, c2, c3, c4, c5;
    //std::pair<searcher_t::iterator, std::pair<bool, bool> > ret;

    c = my_tree.end();
    BOOST_CHECK_EQUAL(c, my_tree.end());
    BOOST_CHECK_EQUAL(c, my_tree.begin());
    
//    searcher_t::cursor cur = searcher_t::cursor(c);
//    BOOST_CHECK(cur.is_leaf());
//    BOOST_CHECK_EQUAL(cur, searcher_t::cursor(my_tree.end()));
        
    c1 = my_tree.insert(c, 8);
    
    BOOST_CHECK_EQUAL(*c1, 8);
//    BOOST_CHECK_EQUAL(searcher_t::cursor(c1).index(), 0);
    BOOST_CHECK(c != my_tree.end());
    BOOST_CHECK(c1 != my_tree.end());
    
//    cur = searcher_t::cursor(c1);
//    BOOST_CHECK((++cur).is_leaf());
//    BOOST_CHECK(cur.index());
//    
//    cur = cur.parent(); //header-cursor(,1) (root)
//    BOOST_CHECK(!cur.index());
//    BOOST_CHECK_EQUAL(searcher_t::iterator(cur), my_tree.end());    
    BOOST_CHECK(*c1 = 8);

    BOOST_CHECK_EQUAL(++c1, my_tree.end());


    --c1;
    BOOST_CHECK_EQUAL(*c1, 8);
    
//    BOOST_CHECK_EQUAL(searcher_t::cursor(my_tree.end()).index(), 1);
//
//    BOOST_CHECK_EQUAL(cur.end().index(), 1);
//    
//    cur = searcher_t::cursor(c1);
//    
//    BOOST_CHECK_EQUAL(*cur, 8);
//    
//    BOOST_CHECK((++cur).is_leaf());
//    BOOST_CHECK(!(--cur).parent().index()); // root's index...
//
//    BOOST_CHECK_EQUAL(*(searcher_t::cursor(c).begin()), 8);
    
    BOOST_CHECK_EQUAL(*c1, 8);
    BOOST_CHECK_EQUAL(++c1, my_tree.end());
    
    // root (e.g. c) instead of c1 would crash this. but should that be really 
    // illegal?
    c2 = my_tree.insert(c1, 18); 

    BOOST_CHECK_EQUAL(*c2, 18);

    ++c2;
    BOOST_CHECK_EQUAL(c2, my_tree.end());
    
    c = my_tree.end();
    --c;
    BOOST_CHECK_EQUAL(*c, 18);

    c2 = my_tree.insert(c, 31);

    c2 = my_tree.insert(c, 412);
    c3 = my_tree.insert(c, 39);
    
    c4 = my_tree.insert(c, 7);
    
    BOOST_CHECK_EQUAL(*c4, 7);

    BOOST_CHECK_EQUAL(++c2, my_tree.end());
    c = my_tree.end();
    --c;

    BOOST_CHECK(*c != 39);
    BOOST_CHECK_EQUAL(*c, 412);
    --c;
    BOOST_CHECK_EQUAL(*c, 39);
    
    c = my_tree.begin();
//    BOOST_CHECK_EQUAL(searcher_t::cursor(c).index(), 0);
//    BOOST_CHECK(*(searcher_t::cursor(c).parent()) != 412);
    BOOST_CHECK(*c < 413);    
    
//    searcher_t::container_type& the_tree = my_tree.container();
//    searcher_t::cursor tree_cur = boost::tree::lower_bound(the_tree.root(), 
//        39, std::less<int>());
//
//    BOOST_CHECK(tree_cur.is_leaf());
//    BOOST_CHECK((++tree_cur).is_leaf());
//    --tree_cur;
//    BOOST_CHECK_EQUAL(*tree_cur, 39);
//    
//    tree_cur = boost::tree::lower_bound(the_tree.root(), 18);    
//    BOOST_CHECK_EQUAL(*tree_cur, 18);
//    
//    tree_cur = boost::tree::lower_bound(the_tree.root(), 30);    
//    BOOST_CHECK(tree_cur.is_leaf());
//    BOOST_CHECK(!(++tree_cur).is_leaf());
//    --tree_cur;
//    BOOST_CHECK_EQUAL(*tree_cur, 31);
//    
//    tree_cur = boost::tree::lower_bound(the_tree.root(), 3);    
//    BOOST_CHECK_EQUAL(*tree_cur, 7);
    
    c = my_tree.begin();
    BOOST_CHECK_EQUAL(*c++, 7);
    BOOST_CHECK_EQUAL(*c++, 8);
    BOOST_CHECK_EQUAL(*c++, 18);
    BOOST_CHECK_EQUAL(*c++, 31);
    BOOST_CHECK_EQUAL(*c++, 39);
    BOOST_CHECK_EQUAL(*c++, 412);
    BOOST_CHECK_EQUAL(c, my_tree.end());
    BOOST_CHECK_EQUAL(*--c, 412);
    BOOST_CHECK_EQUAL(*--c, 39);
    BOOST_CHECK_EQUAL(*--c, 31);
    BOOST_CHECK_EQUAL(*--c, 18);
    BOOST_CHECK_EQUAL(*--c, 8);
    BOOST_CHECK_EQUAL(*--c, 7);
    BOOST_CHECK_EQUAL(c, my_tree.begin());
    
    while (c != my_tree.end())
        ++c;
    
    ------c;
    BOOST_CHECK_EQUAL(*c, 31);

    //my_tree.erase(c);

    //BOOST_CHECK_EQUAL(*c, 39);
    
//    tree_cur = boost::tree::lower_bound(the_tree.root(), 412);    
//    BOOST_CHECK_EQUAL(*tree_cur, 412);
//    BOOST_CHECK_EQUAL(*tree_cur.parent(), 18);
//    
//    c = my_tree.begin();
//    BOOST_CHECK_EQUAL(*c++, 7);
//    BOOST_CHECK_EQUAL(*c++, 8);
//    BOOST_CHECK_EQUAL(*c++, 18);
//    BOOST_CHECK_EQUAL(*c++, 39);
//    BOOST_CHECK_EQUAL(*c++, 412);
//    BOOST_CHECK_EQUAL(c, my_tree.end());
    

}

//boost::unit_test::test_suite*
//init_unit_test_suite( int argc, char* argv[] )
//{
//    boost::unit_test::test_suite* key_search_test = 
//            BOOST_TEST_SUITE( "Key search binary vector test" );
//
//    key_search_test->add( BOOST_TEST_CASE( &key_search_binary_tree_test ) );
//
//    return key_search_test;
//}
