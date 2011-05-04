//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file insert_cursor.hpp
 * Insert cursor implementation
 */

#ifndef BOOST_TREE_INSERT_CURSOR_HPP
#define BOOST_TREE_INSERT_CURSOR_HPP

#include <boost/tree/cursor_adaptor.hpp>

#include <boost/tree/cursor_concepts.hpp>
#include <boost/tree/tree_concepts.hpp>

namespace boost {
namespace tree {

using boost::iterator_core_access;
using namespace boost_concepts;

/** \addtogroup cursor_adaptors
 *  \@{ */

template <class Tree>
class insert_cursor;

/**
 * @brief Turns assignment into insertion.
 * 
 * This is a generalisation of std::insert_iterator. Consequently,
 * it requires a Tree and a cursor to a position in that tree,
 * which will we used as the root of the subtree of elements that
 * will be inserted.
 * 
 * For construction, the tree_insert wrapper might come in useful
 * in saving keystrokes.
 */
// TODO: Complete this.
template <class Tr>
class insert_cursor
: public cursor_adaptor<insert_cursor<Tr>
                      , typename Tr::cursor 
//                      , boost::use_default
//                      , boost::use_default
//                      , boost::use_default
    >
{

BOOST_CONCEPT_ASSERT((Tree<Tr>));

protected:
    mutable Tr& tree;
public:        
    /**
     * For construction, we obviously need a tree and a cursor to work on (i.e., write to).
     */
    explicit insert_cursor(Tr& x, typename Tr::cursor cur)
    : insert_cursor::cursor_adaptor_(cur), tree(x) {}

    insert_cursor(insert_cursor const& other)
    : insert_cursor::cursor_adaptor_(other.base()), tree(other.tree) {}

    // Cursor-specific
    typedef insert_cursor<typename Tr::cursor> cursor;
    typedef insert_cursor<typename Tr::const_cursor> const_cursor;

    operator typename Tr::cursor()
    {
        return this->base_reference();
    }
    
private:
    friend class boost::iterator_core_access;
    friend class boost::tree::cursor_core_access;

    typename insert_cursor::cursor_adaptor_::reference dereference() const
    {
        if (this->base_reference().index()) { // FIXME: use freestanding index!
            //const_cast<typename Tr::cursor&>(this->base_reference()) =
            tree.insert(this->base_reference(), typename Tr::value_type());
            //const_cast<typename Tr::cursor&>(this->base_reference()).to_begin();
        }
        return *this->base_reference();
    }

    void left()
    {
        if (this->base_reference().is_leaf())
//            this->base_reference() = 
                tree.insert(this->base_reference(), typename Tr::value_type());
        this->base_reference().to_begin();
    }
};

/** 
 * @param o An output cursor.
 * @result  An instance of insert_cursor working on o.
 * 
 * Use as shortcut for cumbersome typenames, just as with std::inserter and the like.
 */
template<class Tr>
inline insert_cursor<Tr>
tree_inserter(Tr& t, typename Tr::cursor c)
{
    return insert_cursor<Tr>(t, c);
}

/** @} */

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_INSERT_CURSOR_HPP
