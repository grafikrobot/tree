//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TREE_AUGMENTORS_RANK_HPP
#define BOOST_TREE_AUGMENTORS_RANK_HPP

namespace boost {
namespace tree {
namespace augmentors {
    
//TODO: lots. current implementation is dysfunctional.

template <typename SizeType>
class rank_data {
 public:
    typedef SizeType size_type;
    //get_rank - just show rank info    
    
//    size_type const get_rank() const
//    {
//        return m_rank;
//    }
//    
//    void set_rank(size_type priority)
//    {
//        m_rank = rank;
//    }
    
    rank_data(size_type r = 1)
    : m_rank(r) {}
    
    size_type& rank()
    {
        return m_rank;
    }

    size_type const& rank() const
    {
        return m_rank;
    }
        
    //operator[] ? rather not...
    
    
private:
    size_type m_rank;
};

template <typename SizeType = std::size_t>
class rank {
 public:
     typedef SizeType size_type;
     typedef rank_data<size_type> metadata_type;
     
 protected:
    //or metadata as param-type?
    template <class Tree>
     void pre_rotate(Tree&, typename Tree::cursor& q)
     {
         typename Tree::cursor p = q->parent();
        if (!index(q))
            p.metadata().rank() -= q.metadata().rank();
        else
            q.metadata().rank() += p.metadata().rank();
     }
     
     template <class Tree>
     void pre_detach(Tree& t, typename Tree::cursor& y)
     {
         typename Tree::cursor p = y;
         while (p.parent() != t.root()) {
            if (!index(p))
                 --p.parent().metadata().rank();
             p = p.parent();
         }
     }
     
     template <class Tree>
     void pre_detach(Tree& t, typename Tree::cursor& y, typename Tree::cursor& z)
     {
         typename Tree::cursor p = y;
         while (p.parent() != t.root()) {
            if (!index(p))
                 --p.parent().metadata().rank();
             p = p.parent();
         }
         if (z == t.root())
             y.metadata().rank() = z.metadata().rank();
     }

     template <class Tree>
     void descend(Tree&, typename Tree::cursor& p)
     {
        if (index(p) == 0) {
             ++p.metadata().rank();
         }
     }
     
};

} // namespace augmentors

// This is actually some kind of algorithm...
template <class Tree>
typename Tree::const_cursor select_rank(Tree const& tree, typename Tree::augmentor_type::size_type i)
{
    typename Tree::const_cursor p = tree.root().begin();
    if (p.metadata().rank() < i) {
        return p;
    }
    ++i;
    p = p.begin();
    for (;;) {
        if (i < p.metadata().rank())
            p = p.begin();
        else {
            i -= p.metadata().rank();
            if (i == 0)
                return p;
            p = p.end();
        }
    }
}

template <class Tree>
typename Tree::cursor select_rank(Tree& tree, typename Tree::augmentor_type::size_type i)
{
    typename Tree::cursor p = tree.root().begin();
    if (p.metadata().rank() < i) {
        return p;
    }
    ++i;
    p = p.begin();
    for (;;) {
        if (i < p.metadata().rank())
            p = p.begin();
        else {
            i -= p.metadata().rank();
            if (i == 0)
                return p;
            p = p.end();
        }
    }
}

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_AUGMENTORS_RANK_HPP


