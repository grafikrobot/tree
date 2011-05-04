//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/graph.hpp>

#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/visitors.hpp>

#define BOOST_TEST_MODULE graph test
//#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>

#include <list>
#include <iterator>

#include <boost/tree/balance.hpp>

#include "test_tree_traversal_data.hpp"
#include "binary_tree_test_data.hpp" // TODO: Remove

typedef boost::tree::augmented_type< int, boost::default_color_type > data_type;

BOOST_FIXTURE_TEST_SUITE(graph_algorithms_test, test_binary_tree_fixture<data_type>)

BOOST_AUTO_TEST_CASE( graph_test )
{
    using namespace boost;
    using boost::tree::binary_tree;
    
    typedef color_traits<default_color_type> Color;

    typedef binary_tree< data_type > tree_type;
    typedef tree_type::cursor cursor;
    
    //tree_type test_tree;
    //create_test_dataset1_tree(test_tree);
    
    std::list<int> test_list;
    typedef std::back_insert_iterator< std::list<int> > bi_list_int_type;
    bi_list_int_type bi_list_int = std::back_inserter(test_list);

    // TODO:

    // Wrap a BGL (Incidence)Graph around test_tree
    
    // Traverse the Graph and check if the result is equal
    // to the test data sets, using the depth_first_visit algorithm and 
    // a visitor that is invoked at entering (preorder)
    // the vertices.

    boost::extract_property_map<
        cursor, 
        boost::tree::cursor_value<cursor>::type::extract_data
    > dpm;
    
    boost::extract_property_map<
        cursor, 
        boost::tree::cursor_value<cursor>::type::extract_meta
    > cpm;

    BOOST_CHECK_EQUAL(get(dpm, bt.root()), 8); // Check the entire tree?
    BOOST_CHECK_EQUAL(get(cpm, bt.root()), Color::white());
    
    put(cpm, bt.root(), Color::gray());    
    BOOST_CHECK_EQUAL(get(cpm, bt.root()), Color::gray());
    put(cpm, bt.root(), Color::white());    
    BOOST_CHECK_EQUAL(get(cpm, bt.root()), Color::white());
    
    boost::dfs_visitor< 
        boost::property_writer<
            boost::extract_property_map<
                cursor, 
                boost::tree::cursor_value<cursor>::type::extract_data
            >, 
            bi_list_int_type, 
            boost::on_discover_vertex> 
        > 
        preorder_writer(write_property(dpm, bi_list_int, 
                        boost::on_discover_vertex()));
        
//     boost::depth_first_visit(bt, bt.root(), preorder_writer, cpm, empty_cursor<tree_type>);
    
    graph_traits<tree_type>::vertex_descriptor v = bt.root();
    
    graph_traits<tree_type>::out_edge_iterator oei, oei_end;
    tie(oei, oei_end) = out_edges(v, bt);
    
    cursor w = target(*oei, bt);
    
    w = bt.root().begin().end().begin();
    default_color_type color = get(cpm, w);
    BOOST_CHECK_EQUAL(color, Color::white());
    
    put(cpm, w, Color::white());
    BOOST_CHECK_EQUAL(get(cpm, w), Color::white());
    
    BOOST_CHECK(!empty_cursor(v, bt));
    
    BOOST_CHECK(oei != oei_end);
    
    BOOST_CHECK(source(*oei, bt) == bt.root());
    BOOST_CHECK(source(*oei_end, bt) == bt.root());
    
    BOOST_CHECK(target(*oei, bt) == bt.root().begin());
    BOOST_CHECK(target(*oei_end, bt) == bt.root());
    
    BOOST_CHECK_EQUAL(out_degree(v, bt), 2);
//        
//    BOOST_CHECK_EQUAL(test_list.size(), 2);
//    
//    std::list<int>::const_iterator ci = test_list.begin();
//    
//    BOOST_CHECK_EQUAL(*ci, 8);
//    BOOST_CHECK_EQUAL(*++ci, 10); //FIXME
    
//    test::traversal(preorder(), test_list.begin(), test_list.end());
    
    // Output bt using write_graphviz. This might require copying
    // the IncidenceGraph to a VertexListGraph (using copy_component) 
}

BOOST_AUTO_TEST_SUITE_END()