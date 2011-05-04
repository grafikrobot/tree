//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/insert_cursor.hpp>

#define BOOST_TEST_MODULE cursor_algorithm test
#include <boost/test/included/unit_test.hpp>

#include "test_tree_traversal_data.hpp"
#include "fake_binary_tree.hpp"

using namespace boost::tree;

template <class Cursor>
void fill_subtree_with_data(Cursor cur)
{
    //cur.to_begin();
    *cur = 8;
    *cur.begin() = 3;
    *cur.begin().begin() = 1;  //Leaf
    *cur.begin().end() = 6;
    *cur.begin().end().begin() = 4; //Leaf
    *cur.begin().end().end() = 7; //Leaf
    *cur.end() = 10;
    *cur.end().end() = 14;
    *cur.end().end().begin() = 13;
    *cur.end().end().begin().begin() = 11; 
    *cur.end().end().begin().begin().end() = 12; //Leaf
}

template <class Cursor>
void fill_subtree_with_data_in_preorder(Cursor cur)
{
    *cur = 8;
    *cur.to_begin() = 3;
    Cursor c2(cur);
    *cur.to_begin() = 1;
    *++cur = 6;
    *cur.to_begin() = 4;
    *++cur = 7;

    *++c2 = 10;
    *c2.to_end() = 14;
    *c2.to_begin() = 13;
    *c2.to_begin() = 11;
    *c2.to_end() = 12;
}

template <class Cursor>
void fill_subtree_with_data_in_inorder(Cursor cur)
{
    Cursor c2(cur);
    cur.to_begin();
    Cursor c3(cur);
    *cur.to_begin() = 1;
    *c3 = 3;
    Cursor c4(c3);
    *c3.to_end();
    Cursor c5(c3);
    *c3.to_begin() = 4;
    *c5 = 6;
    *c5.to_end() = 7;
    *c2 = 8;
    
    *c2.to_end() = 10;
    c2.to_end();
    Cursor c14(c2);
    c2.to_begin();
    Cursor c13(c2);
    *c2.to_begin() = 11;
    *c2.to_end() = 12;
    *c13 = 13;
    *c14 = 14;
}

template <class Cursor>
void fill_subtree_with_data_in_postorder(Cursor cur)
{
    Cursor c2(cur);
    cur.to_begin();
    Cursor c3(cur);
    *cur.to_begin() = 1;
    Cursor c4(c3);
    *c4.to_end();
    Cursor c6(c4);
    Cursor c7(c4);
    *c4.to_begin() = 4;
    *c7.to_end() = 7;
    *c6 = 6;
    *c3 = 3;
    
    Cursor c8(c2);
    c2.to_end();
    Cursor c10(c2);
    c2.to_end();
    Cursor c14(c2);
    c2.to_begin();
    Cursor c13(c2);
    c2.to_begin();
    Cursor c11(c2);
    *c2.to_end() = 12;
    *c11 = 11;
    *c13 = 13;
    *c14 = 14;
    *c10 = 10;
    *c8 = 8;
}

BOOST_FIXTURE_TEST_SUITE(insert_cursor_test, fake_binary_tree_fixture<int>)

BOOST_AUTO_TEST_CASE ( test_desc_copy_using_insert_cursor_preorder )
{
    fill_subtree_with_data_in_preorder(tree_inserter(fbt2, fbt2.descending_root()));

    validate_test_dataset1_tree(fbt2.descending_root());
}

BOOST_AUTO_TEST_CASE ( test_desc_copy_using_insert_cursor_inorder )
{
    fill_subtree_with_data_in_inorder(tree_inserter(fbt2, fbt2.descending_root()));

    validate_test_dataset1_tree(fbt2.descending_root());
}

BOOST_AUTO_TEST_CASE ( test_desc_copy_using_insert_cursor_postorder )
{
    fill_subtree_with_data_in_postorder(tree_inserter(fbt2, fbt2.descending_root()));

    validate_test_dataset1_tree(fbt2.descending_root());
}

BOOST_AUTO_TEST_CASE ( test_desc_copy_using_insert_cursor )
{
    fill_subtree_with_data(tree_inserter(fbt2, fbt2.descending_root()));

    validate_test_dataset1_tree(fbt2.descending_root());
}

//BOOST_AUTO_TEST_CASE_TEMPLATE ( test_asc_copy_using_insert_cursor, Order, orders )
//{    
//    fbt2.clear();
//        
//    boost::tree::copy(Order(), bt.root(), tree_inserter(fbt2, fbt2.root())
//                    , boost::tree::ascending_vertical_traversal_tag());
//
//    validate_test_dataset1_tree(fbt2.root());
//    BOOST_CHECK_EQUAL(size(fbt2.root()), size(bt.root())); 
//}

BOOST_AUTO_TEST_SUITE_END()