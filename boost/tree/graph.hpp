//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file graph.hpp
 * Interoperability with the BGL (Boost Graph Library).
 */
 
#ifndef BOOST_TREE_GRAPH_HPP
#define BOOST_TREE_GRAPH_HPP

#include <boost/tree/cursor.hpp>
#include <boost/tree/binary_tree.hpp>

#include <boost/graph/graph_traits.hpp>
#include <boost/property_map.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/multi_index/identity.hpp>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {

using boost::tree::cursor_size;
using boost::tree::cursor_horizontal_traversal;

namespace tree {

// TODO: For ascendant cursors, we don't really need a pair<Cursor, Cursor>
template <class Cursor>
class out_edge_iterator
 : public iterator_facade<out_edge_iterator<Cursor>
                         , std::pair<Cursor, Cursor>
                         , typename cursor_horizontal_traversal<Cursor>::type
                         /*, Reference, Difference*/> {

    struct enabler {};
public:
    out_edge_iterator() : m_edge() {}
    
    explicit out_edge_iterator(Cursor u, Cursor v) : m_edge(u, v) {}

    template <class OtherCursor>
    out_edge_iterator(
        out_edge_iterator<OtherCursor> const& other
      , typename boost::enable_if<
            boost::is_convertible<OtherCursor*,Cursor*>
          , enabler
        >::type = enabler()
    )
      : m_edge(other.m_edge) {}

    
private:
    friend class boost::iterator_core_access;

    template <class OtherCursor>
    bool equal(out_edge_iterator<OtherCursor> const& other) const
    {
        return this->m_edge == other.m_edge;
    }

    void increment()
    {
        // We also need to account for the cursor's end()!
        if (m_edge.second == m_edge.first.end()) { 
            m_edge.second = m_edge.first;
            return;
        }
        ++m_edge.second; 
    }

    void decrement()
    { 
           if (m_edge.second == m_edge.first) { 
            m_edge.second = m_edge.first.end();
            return;
        }
        --m_edge.second;
    }

    std::pair<Cursor, Cursor>& dereference() const
    { return const_cast<std::pair<Cursor, Cursor>&>(m_edge); }

    std::pair<Cursor, Cursor> m_edge; 
};

} // namespace tree

using boost::tree::binary_tree;

// Unsure how we can avoid redundancies here, as this should be pretty much the same for 
// all kinds of trees.

template <class Tp, class Alloc>
struct graph_traits< binary_tree<Tp, Alloc> > {
    typedef typename binary_tree<Tp, Alloc>::cursor vertex_descriptor;
    typedef std::pair<vertex_descriptor
                    , vertex_descriptor> edge_descriptor; // Might be tunable...

    typedef boost::tree::out_edge_iterator<vertex_descriptor> out_edge_iterator;

    typedef directed_tag directed_category;
    typedef disallow_parallel_edge_tag edge_parallel_category;
    typedef incidence_graph_tag traversal_category;
    typedef 
        typename cursor_size<vertex_descriptor>::type 
        vertices_size_type;
    typedef
        typename cursor_size<vertex_descriptor>::type
        edges_size_type;
    typedef
        typename cursor_size<vertex_descriptor>::type
        degree_size_type;
};

//template <class Tp, class Alloc>
//typename graph_traits< binary_tree<Tp, Alloc> >::vertex_descriptor
//source(
//    typename graph_traits< binary_tree<Tp, Alloc> >::edge_descriptor e,
//    const binary_tree<Tp, Alloc>& g)
//{
//    return e.first;
//}
//
//template <class Tp, class Alloc>
//typename graph_traits< binary_tree<Tp, Alloc> >::vertex_descriptor
//target(
//    typename graph_traits< binary_tree<Tp, Alloc> >::edge_descriptor e,
//    const binary_tree<Tp, Alloc>& g)
//{
//    return e.second;
//}

template <class Tp, class Alloc>
inline std::pair<
    typename graph_traits< binary_tree<Tp, Alloc> >::out_edge_iterator,
    typename graph_traits< binary_tree<Tp, Alloc> >::out_edge_iterator >  
out_edges(
    typename graph_traits< binary_tree<Tp, Alloc> >::vertex_descriptor u, 
    const binary_tree<Tp, Alloc>& g)
{
    typedef
        typename graph_traits< binary_tree<Tp, Alloc> >::out_edge_iterator
        Iter;
    return std::make_pair(Iter(u, u.begin()), Iter(u, u));
}

template <class Tp, class Alloc>
inline typename graph_traits< binary_tree<Tp, Alloc> >::degree_size_type  
out_degree(
    typename graph_traits< binary_tree<Tp, Alloc> >::vertex_descriptor u, 
    const binary_tree<Tp, Alloc>& g)
{
    return u.size();
}

template <
    class Cursor, 
    class Op //= typename identity<typename boost::tree::cursor_value<Cursor>::type>
>
struct extract_property_map;

template <class Cursor, class Op>
class extract_property_map
: public boost::put_get_helper<typename Op::result_type&
                             , extract_property_map<Cursor, Op> >
{
public:
    typedef Cursor key_type;
    typedef typename Op::result_type value_type;
    typedef value_type& reference;
    typedef boost::lvalue_property_map_tag category;

    extract_property_map(Op op = Op()) : m_op(op) {}

    inline reference operator[](key_type v) const
    {
        return m_op(*v.to_begin());
    }
    
private:
    Op m_op;
};

template <class Tree>
bool empty_cursor(typename Tree::cursor u, Tree)
{
    return u.is_leaf();
}

} // namespace boost


#endif // BOOST_TREE_GRAPH_HPP
