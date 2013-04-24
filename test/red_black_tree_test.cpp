//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/binary_tree.hpp>
#include <boost/tree/balancers/red_black.hpp>
#include <boost/tree/augmentors/unaugmented.hpp>

#include <vector>
#include <algorithm>

#define BOOST_TEST_MODULE red_black_tree test
//#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>



using boost::tree::binary_tree;

//TODO: Make this a test suite.

BOOST_AUTO_TEST_CASE( red_black_tree_test )
{
    using namespace boost::tree;
    
    typedef test_balancer<binary_tree<int>, balancers::red_black> red_black_tree_t;

    red_black_tree_t my_balancer;
    std::vector<int> my_vector;
        
    create_test_data_sequence(my_balancer);
    create_test_data_sequence(my_vector);
    
    BOOST_CHECK(std::equal(my_balancer.begin(), my_balancer.end(), my_vector.begin()));

    
//    typedef binary_tree<int, balancers::red_black> tree_t;
//    typedef searcher<false, tree_t> searcher_t;
//    searcher_t my_searcher;
//    
//    searcher_t::iterator it, c1, c2, c3, c4, c5;
//    searcher_t::const_iterator cit;
//

//create_test_data_searcher(my_searcher);

//    it = my_searcher.end();
//    
    //c1 = my_searcher.insert(c, 8);
//    c1 = my_searcher.insert(it, 8);
//    

//    cit = my_searcher.begin();
//    BOOST_CHECK_EQUAL(*c1, 8);

//    my_searcher.insert(5);
//    my_searcher.insert(it, 7);
//    my_searcher.insert(it, 12);
//    my_searcher.insert(it, 14);
//    my_searcher.insert(it, 2);
//    my_searcher.insert(it, 11);
    
//    searcher_t::container_type core = my_searcher.get_container();
//    searcher_t::container_type::cursor c = core.root().begin();
//    BOOST_CHECK_EQUAL(*c, 8);

//    BOOST_CHECK_EQUAL(c1.parent(), c); //Maybe factor out specifc tests (parent(), begin(), ...)    
//    BOOST_CHECK_EQUAL(c1, my_searcher.end().begin()); //FIXME. end means root
//    BOOST_CHECK(c1 != my_searcher.end().end()); //ditto
//    BOOST_CHECK_EQUAL(*c1, 8);
//    BOOST_CHECK(!c1.has_child());
//    
//    BOOST_CHECK(c.has_child());
//    BOOST_CHECK_EQUAL(c, my_searcher.end());
    
//    ret = key_lower_bound(my_searcher.end(), 18, 
//                                       lower_bound_wrapper<mycursor, int, std::less<int> >(),
//                                       boost::multi_index::identity<int>(), std::less<int>());
                                       
//    BOOST_CHECK_EQUAL(ret.first, my_searcher.root().end());
//    BOOST_CHECK(ret.second.first);
//    //BOOST_CHECK_EQUAL(ret.first.m_pos, 1);    
//    c2 = my_searcher.insert(c, 18); //so where does that go?
//    //BOOST_CHECK_EQUAL(c2.parent(), c1);
//    //BOOST_CHECK_EQUAL(c1.end(), c2);    
//    //BOOST_CHECK(c2 != my_searcher.root().end());    
//        
//    BOOST_CHECK_EQUAL(*c2, 18);
//    BOOST_CHECK(!c2.has_child());
//
//    BOOST_CHECK_EQUAL(c2, my_searcher.root().end().begin());        
//    //BOOST_CHECK_EQUAL(c2.m_parent, c.m_parent);    
//    //BOOST_CHECK_EQUAL(c2, c.m_parent);    
//    //BOOST_CHECK(c1.has_child());  ///also fails!!!
//    
//
//    
//    c2 = my_searcher.insert(c, 31);
//    
//    c2 = my_searcher.insert(c, 412);
//    c3 = my_searcher.insert(c, 39);
//    
//    c4 = my_searcher.insert(c, 7);
//    
//    BOOST_CHECK_EQUAL(*(c2.parent()), 31);
//    BOOST_CHECK_EQUAL(*(c2.begin()), 39);
//    
//    //BOOST_CHECK_EQUAL(c4.parent(), c1);
//
//    BOOST_CHECK_EQUAL(*c3, 39);
//    BOOST_CHECK_EQUAL(c4.parent(), c1);
//    BOOST_CHECK_EQUAL(c1.begin(), c4);

        
    //*(mytree.root()) = -5;
    //c = my_searcher.root();
    //my_searcher.c();
//    //*c = 5;
////    //BOOST_CHECK_EQUAL(*c, 5);
////    
//    c1 = mytree.insert(c, 1);
//    BOOST_CHECK_EQUAL(*c, 1);
//    c2 = mytree.insert(c1, 2);
//    BOOST_CHECK_EQUAL(*c1, 1);
//    BOOST_CHECK_EQUAL(*c2, 2);


//    *c1 = 14; //how can we forbid this? by setting key to int const&
//    BOOST_CHECK_EQUAL(*c1, 14);
//    BOOST_CHECK_EQUAL(*c2, 2);
//    BOOST_CHECK_EQUAL(c2.parent(), c1);
//    BOOST_CHECK_EQUAL(c1.parent(), c);
//    
//    c3 = c1.end();
//    --c3;
//    BOOST_CHECK_EQUAL(*c3, 2);
//    ++c3;
//    c4 = mytree.insert(c3, 4);
//    BOOST_CHECK_EQUAL(*c4, 4);
//    c4 = c4.parent();
//    --c4;
//    BOOST_CHECK_EQUAL(*c4, 2);
//    
//    //BOOST_CHECK_EQUAL(c4.parent(), c1);
        
}

