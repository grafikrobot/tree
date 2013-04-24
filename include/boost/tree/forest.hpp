//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file forest.hpp
 * Binary tree based forest implementation
 */

#ifndef BOOST_TREE_FOREST_HPP
#define BOOST_TREE_FOREST_HPP

#include <boost/tree/detail/forest_cursor.hpp>

#include <boost/tree/binary_tree.hpp>
#include <boost/tree/algorithm.hpp>
#include <boost/tree/cursor_concepts.hpp>

#include <boost/concept_check.hpp>

namespace boost {
namespace tree {

using detail::forest_cursor;
using namespace boost_concepts;

/** 
 * @brief A %forest.
 * This class models the hierarchy concept. It is a (binary) tree adaptor,
 * and a (forest) tree of its own right.
 * TODO: complete this..
 *
*/

template <class T, class Hierarchy = binary_tree<T> >
class forest {

BOOST_CONCEPT_ASSERT((DefaultConstructible<T>));
BOOST_CONCEPT_ASSERT((DescendingCursor< typename Hierarchy::cursor >));
BOOST_CONCEPT_ASSERT((DescendingCursor< typename Hierarchy::const_cursor >));
//BOOST_CONCEPT_ASSERT((SameType<T, typename Hierarchy::value_type>)); 
// Is there a SameType concept in BCCL?

    typedef forest<T, Hierarchy> self_type;

 public:
    typedef T value_type;
    typedef Hierarchy hierarchy_type;

    typedef typename hierarchy_type::cursor base_cursor;
    typedef typename hierarchy_type::const_cursor base_const_cursor;
    
    typedef forest_cursor<base_cursor> cursor;
    typedef forest_cursor<base_const_cursor> const_cursor;
    
    typedef typename cursor_pointer<cursor>::type pointer;
    typedef typename cursor_reference<cursor>::type reference;
    typedef typename cursor_size<cursor>::type size_type;
    typedef typename cursor_difference<cursor>::type difference_type;

    /**
     *  @brief    The default constructor creates one element at the root.
     *  @param    val   The value the root will be assigned. 
     */
//    forest(/*value_type const& val = value_type()*/) : h(Hierarchy())
//    {
//        //h.insert(h.root(), val);
//    }

    /**
     *  @brief    The default constructor creates no elements.
     *  @param    hier    A hierarchy object that will be used as a base to
     *                    construct this forest.
     */
    explicit forest(Hierarchy const& hier = Hierarchy()) : h(hier)
    {
//        if (h.is_leaf())
//            h.insert(h.root(), value_type());
    }

    /**
     * Returns true if the %forest is empty.
     */
    bool empty()
    {
        return h.empty();
    }
    
    /**
     * Returns a read/write ("mutable") cursor to the %forest's 
     * first element.
     */     
    cursor begin()
    {
        return cursor(h.root());
    }

    /**
     * Returns a read-only const_cursor to the %forest's
     * first element.
     */     
    const_cursor begin() const
    {
        return cbegin();
    }
    
    /**
     * Returns a read-only const_cursor to the %forest's
     * first element.
     */     
    const_cursor cbegin() const
    {
        return const_cursor(h.croot());
    }

    // TODO: end.

    /**
     * Returns a read/write ("mutable") cursor past the %forest's
     * last element.
     */     
    cursor end()
    {
        base_cursor b(h.root());
        to_rightmost(b);
        return cursor(b);
    }

    /**
     * Returns a read-only const_cursor past the %forest's
     * last element.
     */     
    const_cursor end() const
    {
        return cend();
    }
    
    /**
     * Returns a read-only const_cursor past the %forest's
     * last element.
     */     
    const_cursor cend() const
    {
        base_const_cursor b(h.croot());
        to_rightmost(b);
        return const_cursor(b);
    }

    /**
     * @brief       Inserts val in front of @a pos.
     * @param pos   The %forest cursor in front of which to insert.
     * @param val   The value to insert.
     * @return      A cursor that points to the inserted data.
     */
    cursor insert(cursor pos, value_type const& val)
    {
        return cursor(h.insert(pos.base(), val));
    }

    /**
     * @brief Clears all data from the forest tree.
     */
     void clear()
     {
        h.clear();
     }
    
protected:
    hierarchy_type h;
};


// TODO: template <class Cursor> -> template <class T, class Hierarchy>
// forest_cursor<Cursor> -> forest<T, Hierarchy>::cursor
// const_cursor?
template <class Cursor>
typename forest_cursor<Cursor>::size_type
index(forest_cursor<Cursor> const& cur)
{
    return cur.index();
}

/// Use natural forest-binary_tree correspondence:
/// Preoder - preorder

template <class Cursor, class Op>
Op for_each(preorder, forest_cursor<Cursor> s, Op f)
{
    return for_each(preorder(), Cursor(s), f);
}

template <class InCursor, class OutCursor, class Op>
OutCursor transform (preorder, forest_cursor<InCursor> s, forest_cursor<OutCursor> t, Op op)
{
    return transform(preorder(), InCursor(s), OutCursor(t), op);
}

template <class InCursor, class OutCursor>
OutCursor copy (preorder, forest_cursor<InCursor> s, forest_cursor<OutCursor> t)
{
    return copy(preorder(), InCursor(s), OutCursor(t));
}

/// Postoder - inorder

template <class Cursor, class Op>
Op for_each(postorder, forest_cursor<Cursor> s, Op f)
{
    return for_each(inorder(), Cursor(s), f);
}

template <class InCursor, class OutCursor, class Op>
OutCursor transform (postorder, forest_cursor<InCursor> s, forest_cursor<OutCursor> t, Op op)
{
    return transform(inorder(), InCursor(s), OutCursor(t), op);
}

template <class InCursor, class OutCursor>
OutCursor copy (postorder, forest_cursor<InCursor> s, forest_cursor<OutCursor> t)
{
    return copy(inorder(), InCursor(s), OutCursor(t));
}

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_FOREST_HPP
