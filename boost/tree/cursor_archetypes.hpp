//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file cursor_archetypes.hpp
 * Cursor archetypes
 */
 
#ifndef BOOST_TREE_CURSOR_ARCHETYPES_HPP
#define BOOST_TREE_CURSOR_ARCHETYPES_HPP

#include <boost/iterator/iterator_archetypes.hpp>
#include <boost/tree/cursor.hpp>

namespace boost {
namespace tree {

class descendingCursor_archetype
{
public:
    typedef descending_vertical_traversal_tag vertical_traversal;
    
    descendingCursor_archetype& to_begin() { return *this; }
    descendingCursor_archetype& to_end() { return *this; }

    descendingCursor_archetype begin() const { return *this; }
    descendingCursor_archetype end() const { return *this; }
    
    bool is_leaf() const { return true; }
};

class ascendingCursor_archetype
{
public:
    ascendingCursor_archetype& to_parent() { return *this; }

    ascendingCursor_archetype parent() const { return *this; }
};

template <
    class Value
  , class AccessCategory
  , class HorizontalTraversal
  , class VerticalTraversal
> 
class cursor_archetype;

template <
    class Value
  , class AccessCategory
  , class HorizontalTraversal
  , class VerticalTraversal
>
class cursor_archetype
: public iterator_archetype<Value, AccessCategory, HorizontalTraversal>
{

};

// Ideally derive from ascendingCursor_archetype.
// The problem: begin() and end() return the wrong type! 
// FIXME: constructors etc
template <
    class Value
  , class AccessCategory
  , class HorizontalTraversal
>
class cursor_archetype<Value
                     , AccessCategory
                     , HorizontalTraversal
                     , descending_vertical_traversal_tag>
: public iterator_archetype<Value, AccessCategory, HorizontalTraversal>
//, public descendingCursor_archetype
{
private:
    typedef cursor_archetype<Value
                     , AccessCategory
                     , HorizontalTraversal
                     , descending_vertical_traversal_tag> self_type;
public:
    typedef descending_vertical_traversal_tag vertical_traversal;
    
    self_type& to_begin() { return *this; }
    self_type& to_end() { return *this; }

    self_type begin() const { return *this; }
    self_type end() const { return *this; }
    
    bool is_leaf() const { return true; }
};

template <
    class Value
  , class AccessCategory
  , class HorizontalTraversal
>
class cursor_archetype<Value
                     , AccessCategory
                     , HorizontalTraversal
                     , ascending_vertical_traversal_tag>
: public iterator_archetype<Value, AccessCategory, HorizontalTraversal>
//, public ascendingCursor_archetype
{
private:
    typedef cursor_archetype<Value
                     , AccessCategory
                     , HorizontalTraversal
                     , ascending_vertical_traversal_tag> self_type;
public:
    typedef ascending_vertical_traversal_tag vertical_traversal;
    
    self_type& to_parent() { return *this; }

    self_type parent() const { return *this; }
};

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_CURSOR_ARCHETYPES_HPP
