//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file multiway_cursor.hpp
 * Multiway cursor template
 */

#ifndef BOOST_TREE_DETAIL_MULTIWAY_CURSOR_HPP
#define BOOST_TREE_DETAIL_MULTIWAY_CURSOR_HPP

#include <boost/tree/detail/nary_cursor.hpp>

#include <boost/tree/cursor.hpp>
#include <boost/tree/cursor_adaptor.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <iterator>
#include <utility>

namespace boost {
namespace tree {
namespace detail {

template <class Cursor>
class multiway_tree_cursor;

template<class Cursor>
class const_multiway_tree_cursor
 : public cursor_adaptor<const_multiway_tree_cursor<Cursor>
      , Cursor const
      , boost::use_default
      , bidirectional_traversal_tag
      , descending_vertical_traversal_tag
    > {
 private:
    struct enabler {};

 public:
     //TODO: Tidy up typedefs

    typedef Cursor base_cursor;
    
     typedef multiway_tree_cursor<Cursor> cursor;
     typedef const_multiway_tree_cursor<Cursor> const_cursor;

    typedef typename cursor_size<base_cursor>::type size_type;

    typedef bidirectional_traversal_tag cursor_category;
    
    typedef typename Cursor::metadata_type metadata_type;
    
    // Container-specific:
    typedef cursor iterator;  // For (range) concepts' sake, mainly
    typedef const_cursor const_iterator;
    
     // Common iterator facade stuff
    const_multiway_tree_cursor()
     : const_multiway_tree_cursor::cursor_adaptor_() {}

    explicit const_multiway_tree_cursor(base_cursor p)
     : const_multiway_tree_cursor::cursor_adaptor_(p) {}
      
    template <class OtherCursor>
    const_multiway_tree_cursor(
        const_multiway_tree_cursor<OtherCursor> const& other
      , typename boost::enable_if<
            boost::is_convertible<OtherCursor*, 
               typename Cursor::base_pointer>  // is that correct?
          , enabler
        >::type = enabler()
    )
      : const_multiway_tree_cursor::cursor_adaptor_(other.base()) {}

    operator base_cursor()
    {
        return this->base();
    }

 private:
    
    friend class boost::iterator_core_access;
    
    typename const_multiway_tree_cursor::cursor_adaptor_::reference dereference() const
    {
        return this->base()->m_parent->operator[](this->index());
    }
};

template <class Cursor> 
class multiway_tree_cursor
 : public cursor_adaptor<multiway_tree_cursor<Cursor>
      , Cursor
      , boost::use_default
      , bidirectional_traversal_tag
      , descending_vertical_traversal_tag
    > {
 private:
    struct enabler {};
    friend class cursor_core_access;
 public:
     //TODO: Tidy up typedefs

    typedef Cursor base_cursor;
    
     typedef multiway_tree_cursor<Cursor> cursor;
     typedef const_multiway_tree_cursor<Cursor> const_cursor;

    typedef typename cursor_size<base_cursor>::type size_type;

    //typedef bidirectional_traversal_tag cursor_category;
        
    // Container-specific:
    typedef cursor iterator;  // For (range) concepts' sake, mainly
    typedef const_cursor const_iterator;
    
     // Common iterator facade stuff
    multiway_tree_cursor()
     : multiway_tree_cursor::cursor_adaptor_() {}

    explicit multiway_tree_cursor(base_cursor p)
     : multiway_tree_cursor::cursor_adaptor_(p) {}
      
    template <class OtherCursor>
    multiway_tree_cursor(
        multiway_tree_cursor<OtherCursor> const& other
      , typename boost::enable_if<
            boost::is_convertible<OtherCursor*, 
               typename Cursor::node_base_type*>  // is that correct?
          , enabler
        >::type = enabler()
    )
      : multiway_tree_cursor::cursor_adaptor_(other.base()) {}

    operator base_cursor()
    {
        return this->base();
    }


 private:
    
    friend class boost::iterator_core_access;
    
    typename multiway_tree_cursor::cursor_adaptor_::reference dereference() const
    {
        return this->base()->m_parent->operator[](this->index());
    }
    
public:
    // Range stuff.
//    cursor begin()
//    {
//        return cursor(this->base_reference().begin()); 
//    }
    
//    const_cursor begin() const
//    {
//        return const_cursor(this->base_reference().begin()); 
//    }        

    // Cursor stuff. 
    
//    const_cursor parent() const
//    {
//        if (!this->base_reference().index())) {
//            return this->base_reference().parent();
//        }
//    }
};

} // namespace detail
} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_MULTIWAY_CURSOR_HPP
