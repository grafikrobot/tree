//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file treap.hpp
 * Treap balancer and metadata
 */
//TODO: maybe have treap really model binary_heap?

#ifndef BOOST_TREE_BALANCERS_TREAP_HPP
#define BOOST_TREE_BALANCERS_TREAP_HPP

#include <boost/tree/detail/nary_cursor.hpp>

#include <limits.h>
#include <stdlib.h>

namespace boost {
namespace tree {
namespace balancers {

class treap_metadata {
public:    
    treap_metadata()
    : m_priority((lrand48() >> 1) + 1) {}
    
    int const get_priority() const
    {
        return m_priority;
    }
    
    void set_priority(int priority)
    {
        m_priority = priority;
    }
private:
    int m_priority;
};

class treap {
 public:
    typedef treap_metadata metadata_type;
    
    template <class Tree>
    static void add(Tree& t, typename Tree::cursor& x) 
    {
        int priority = x->metadata().get_priority();
        
        x.to_parent();
        while ((x != t.root()) && (priority > x->metadata().get_priority())) {
            t.rotate(x);
            priority = x->metadata().get_priority();
        }
        x.to_begin();
    }
      
    template <class Tree>
    static typename Tree::cursor remove(Tree& t, typename Tree::cursor& p)
    {
        typename Tree::cursor q;
        while((q = ((p.begin()->metadata().get_priority()
                     > p.end()->metadata().get_priority())
                     ? p.begin() : p.end())).is_leaf())
            t.rotate(q);
        p = q;
        return p;
    }
    
    template <class Tree>
    static void touch(Tree&, typename Tree::cursor&)
    { }
};

} // namespace balancers
} // namespace tree
} // namespace boost


#endif // BOOST_TREE_BALANCERS_TREAP_HPP


