//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_BINARY_TREE_TEST_DATA_HPP
#define LIBS_TREE_BINARY_TREE_TEST_DATA_HPP

#include <boost/tree/binary_tree.hpp>

template <class T = int>
struct test_binary_tree_fixture {
    test_binary_tree_fixture()
    {
        create_test_dataset1_tree(bt);
        create_test_dataset1_tree(bt2);
        
        typename boost::tree::binary_tree<T>::cursor d = bt2.root();

        // Just to make sure we won't be getting any false positives when 
        // copying test_tree1 to test_tree2, we'll change one of test_tree2's
        // values.
        d = d.begin().end().begin();
        *d = T(29);
    }
    
    // Test data from http://en.wikipedia.org/wiki/Image:Binary_search_tree.svg
    // (With two additional nodes: 11 inserted left of 13; 12 right of 11)
    // and in combination with http://en.wikipedia.org/wiki/Tree_traversal#Examples
    // (as tree shapes are equal [apart from the extra nodes])
    static void create_test_dataset1_tree(boost::tree::binary_tree<T>& ret)
    {
        // For augmented trees. (Why is this necessary? Nothing here is explicit!)
        typedef typename boost::tree::binary_tree<T>::value_type value_type; 
        
        typename boost::tree::binary_tree<T>::cursor cur = ret.insert(ret.root(), value_type(8));
        cur = ret.insert(cur.to_begin(), value_type(3));
        ret.insert(cur.to_begin(), value_type(1));
        cur = ret.insert(++cur, value_type(6));
        ret.insert(cur.to_begin(), value_type(4));
        ret.insert(++cur, value_type(7));
        cur = ret.insert(ret.root().end(), value_type(10));
        cur = ret.insert(ret.root().end().end(), value_type(14));
        //cur = ret.insert(cur.to_begin(), value_type(13));
        // First insert 11 as left child of 14, 12 as child of 11
        cur = ret.insert(cur.to_begin(), value_type(11));
        cur = ret.insert(++cur.to_begin(), value_type(12));
        // Now insert 13 as left child of 14, which makes it 11's parent
        ret.insert(ret.root().end().end().begin(), value_type(13));
    }

    boost::tree::binary_tree<T> bt, bt2;
};

#endif // LIBS_TREE_BINARY_TREE_TEST_DATA_HPP
