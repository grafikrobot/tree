//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file cursor_facade.hpp
 * Cursor facade implementation
 */

// TODO: Use TR1 type_traits (integral_constant)

#ifndef BOOST_TREE_CURSOR_FACADE_HPP
#define BOOST_TREE_CURSOR_FACADE_HPP

#include <boost/tree/cursor.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace tree {

using boost::iterator_core_access;

class cursor_core_access {
public:

    friend class iterator_core_access;
     
    template <class Facade>
    static bool empty_(Facade const& f)
    {
        return f.empty_();
    }

    template <class Facade>
    static bool is_root_(Facade const& f)
    {
        return f.is_root_();
    }
    
    template <class Facade>
    static typename Facade::size_type size_(Facade const& f)
    {
        return f.size_();
    }
    
    template <class Facade>
    static typename Facade::size_type max_size_(Facade const& f)
    {
        return f.max_size_();
    }

    template <class Facade>
    static typename Facade::size_type idx(Facade const& f)
    {
        return f.idx();
    }
        
    template <class Facade>
    static void left(Facade& f)
    {
        f.left();
    }
    
    template <class Facade>
    static void right(Facade& f)
    {
        f.right();
    }
    
    //only if ascending
    template <class Facade>
    static void up(Facade& f)
    {
        f.up();
    }

private:
    cursor_core_access();
};

template <
    class Derived             // The derived cursor type being constructed
  , class Value
  , class HorizontalCategoryOrTraversal
  , class VerticalCategoryOrTraversal
  , class Reference   = Value&
  , class Difference  = std::ptrdiff_t
  , class Size        = std::size_t
>
class cursor_facade 
 : public iterator_facade<Derived, Value, HorizontalCategoryOrTraversal, 
                          Reference, Difference> {
private:
    // Curiously Recurring Template interface.

    Derived& derived()
    {
        return *static_cast<Derived*>(this);
    }
    
    Derived const& derived() const
    {
        return *static_cast<Derived const*>(this);
    }

    typedef typename cursor_facade::iterator_facade_ iterator_facade_;

protected:
    // For use by derived classes
    typedef cursor_facade<Derived, Value, HorizontalCategoryOrTraversal,
                          VerticalCategoryOrTraversal, Reference, Difference> 
            cursor_facade_;
public:
    typedef typename iterator_facade_::value_type value_type;
    typedef typename iterator_facade_::reference reference;
    typedef typename iterator_facade_::difference_type difference_type;
    typedef typename iterator_facade_::pointer pointer;
    typedef typename iterator_facade_::iterator_category iterator_category;

    typedef Size size_type;

    typedef bidirectional_traversal_tag cursor_category; //TODO
    typedef typename 
        iterator_category_to_traversal<iterator_category>::type
        horizontal_traversal; 
    typedef //typename 
        //iterator_category_to_traversal<
        VerticalCategoryOrTraversal
        //>::type
        vertical_traversal; 

    bool const is_leaf() const
    {
        return cursor_core_access::empty_(this->derived());
    }

    bool const is_root() const
    {
        return cursor_core_access::is_root_(this->derived());
    }
    
    size_type const size() const
    {
        return cursor_core_access::size_(this->derived());
    }
    
    size_type const max_size() const
    {
        return cursor_core_access::max_size_(this->derived());
    }

    size_type const index() const
    {
        return cursor_core_access::idx(this->derived());
    }

    Derived& to_begin()
    {
        cursor_core_access::left(this->derived());
        return this->derived();
    }
                  
    Derived begin() const
    {
        Derived tmp(this->derived());
        return tmp.to_begin();
    }

    Derived& to_end()
    {
        cursor_core_access::right(this->derived());
        return this->derived();
    }
     
    Derived end() const
    {
        Derived tmp(this->derived());
        return tmp.to_end();
    }
     
    Derived& to_parent()
    {
        cursor_core_access::up(this->derived());
        return this->derived();
    }
     
    Derived parent() const
    {
        Derived tmp(this->derived());
        return tmp.to_parent();
    }
};

//TODO: Put somewhere else?
template <class Value>
struct metadata {
    struct type {};
};

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_CURSOR_FACADE_HPP
