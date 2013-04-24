//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_DETAIL_NODE_TRAITS_HPP
#define BOOST_TREE_DETAIL_NODE_TRAITS_HPP

namespace boost {
namespace tree {
namespace detail {

template <class Node>
struct node_traits
{
    typedef Node node_type;
    
    // Value
    typedef typename node_type::value_type  value_type;
    typedef typename node_type::pointer     pointer;
    typedef typename node_type::reference   reference;
    //typedef typename node_type::size_type    size_type;
    
    // Node
    typedef typename node_type::node_pointer    node_pointer;
    typedef typename node_type::node_reference  node_reference;
    
    // Node base
    typedef typename node_type::node_base   node_base_type;
};

} // namespace detail
} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_NODE_TRAITS_HPP
