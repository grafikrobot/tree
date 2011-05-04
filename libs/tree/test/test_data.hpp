//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef LIBS_TREE_TEST_TEST_DATA_HPP
#define LIBS_TREE_TEST_TEST_DATA_HPP

#include <boost/tree/algorithm.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

struct test_data {
    typedef std::size_t size_type;
    typedef int value_type;
    
    size_type pos_level;
    size_type pre;
    size_type in;
    size_type post;
    
    value_type val;
    
    test_data(size_type lop, size_type _pre, size_type _in, size_type _post, int v)
    : pos_level (lop)
    , pre(_pre), in(_in), post(_post)
    , val(v)
    {}
    
    size_type const& get(boost::tree::preorder) const { return pre; }
    size_type const& get(boost::tree::inorder) const { return in; }
    size_type const& get(boost::tree::postorder) const { return post; }
};

template <class Cont>
void mock_cursor_data(Cont& data)
{ 
    data.insert(test_data( 0, 0, 5,10, 8));
    data.insert(test_data( 1, 1, 1, 4, 3));
    data.insert(test_data( 3, 2, 0, 0, 1));
    data.insert(test_data( 4, 3, 3, 3, 6));
    data.insert(test_data( 9, 4, 2, 1, 4));
    data.insert(test_data(10, 5, 4, 2, 7));
    data.insert(test_data( 2, 6, 6, 9,10));
    data.insert(test_data( 6, 7,10, 8,14));
    data.insert(test_data(13, 8, 9, 7,13));
    data.insert(test_data(27, 9, 7, 6,11));
    data.insert(test_data(56,10, 8, 5,12));
}

using boost::multi_index::indexed_by;
using boost::multi_index::member;
using boost::multi_index::ordered_unique;
using boost::multi_index::tag;

typedef boost::multi_index::multi_index_container<
  test_data,
  indexed_by<        
    ordered_unique< member<test_data,test_data::size_type,&test_data::pos_level> >,
    
    ordered_unique<tag<boost::tree::preorder>,member<test_data,test_data::size_type,&test_data::pre> >,
    ordered_unique<tag<boost::tree::inorder>,member<test_data,test_data::size_type,&test_data::in> >,
    ordered_unique<tag<boost::tree::postorder>,member<test_data,test_data::size_type,&test_data::post> >
  > 
> test_data_set;

#endif // LIBS_TREE_TEST_TEST_DATA_HPP
