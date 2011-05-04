//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_TREE_BALANCERS_RED_BLACK_HPP
#define BOOST_TREE_BALANCERS_RED_BLACK_HPP

//TODO: lots.
//templatize with bool add_data?

#include <boost/tree/detail/nary_cursor.hpp>

namespace boost {
namespace tree {
namespace balancers {
    
enum red_black_color { black, red };

class red_black_metadata {
public:    
    red_black_metadata()
    : m_color(black) {}
    
    red_black_color get_color()
    {
        return m_color;
    }
    
    void set_color(red_black_color col)
    {
        m_color = col;
    }
private:
    red_black_color m_color;

};

class red_black {
public:
    typedef red_black_metadata metadata_type;
    
    template <class Tree>
    static void add(Tree& t, typename Tree::cursor& x) 
    {
        x->metadata().set_color(red);
        while (x.parent()->metadata().get_color() == red) {
            typename Tree::cursor y = x.parent();
            y = (y == y.parent().begin() ? y.parent().end() : y.parent().begin());
            if (y->metadata().get_color() == red) {
                x.parent()->metadata().set_color(black);
                x.parent().parent()->metadata().set_color(red);
                y->metadata().set_color(black);
                x = x.parent().parent();
            } else {
                if (index(x) != index(x.parent())) {
                    t.rotate(x);
                    x = (index(x) ? x.end() : x.begin());
                }
                x.parent()->metadata().set_color(black);
                x.parent().parent()->metadata().set_color(red);
                x = x.parent(); //FIXME: was x.parent.rotate();
                t.rotate(x); 
            }
        if (x.parent() == t.root())
            x->metadata().set_color(black);
        }
    }
    
    // second argument also used to pass second parameter for detach,
    // if required.
    template <class Tree>
    static void remove(Tree& t, typename Tree::cursor& x)
    {
        
    }
    
    template <class Tree>
    static void touch(Tree& t, typename Tree::cursor&)
    { }
  
};

} // namespace balancers
} // namespace tree
} // namespace boost


#endif // BOOST_TREE_BALANCERS_RED_BLACK_HPP


