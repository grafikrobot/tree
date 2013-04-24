//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/balance.hpp>
#include <boost/tree/binary_tree.hpp>
#include <boost/tree/detail/balancers/treap.hpp>
#include <boost/tree/detail/augmentors/unaugmented.hpp>

#include <vector>
#include <algorithm>

#define BOOST_TEST_MODULE treap_tree test
//#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>

//TODO: Use a mock_binary_tree
BOOST_AUTO_TEST_CASE( treap_test )
{
    using namespace boost::tree;
    
    std::vector<int> my_vector;
    typedef binary_tree<int> tree_t;
    //typedef test_searcher<false, tree_t> searcher_t;
    typedef balance<binary_tree<int>, balancers::treap> treap_t;
    
    //searcher_t my_searcher;
    treap_t my_balance;
    //tree_t my_tree;
    
    //create_test_data_searcher(my_searcher);
    //create_test_data_sequence(my_balancer);
    //create_test_data_sequence(my_vector);

//    Segfaults:    
//    BOOST_CHECK(std::equal(my_balancer.begin(), my_balancer.end(), my_vector.begin()));

    //TODO: More tests?
    for (treap_t::iterator ci = my_balance.begin(); ci != my_balance.end(); ++ci) {
        treap_t::hierarchy_type::cursor c = ci.base().base().base();
//        int priority = c->metadata().get_priority(); // FIXME: Segfaults!
//        if (!c.is_leaf()) {
//            BOOST_CHECK(priority
//                      > c.begin()->metadata().get_priority());
//        }
    }
    
    //treap_t::iterator ci = my_balancer.begin();
    //treap_t::hierarchy_type::cursor c;
    //c = ci.base().base();
    //c = c.parent();
    //treap_t::metadata_type m = c->metadata();
    //int i = ci.base().base().parent()->metadata().get_priority();//m.get_priority();
}