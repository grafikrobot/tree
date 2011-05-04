//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file coupling_cursor.hpp
 * Coupling cursor implementation
 */

#ifndef BOOST_TREE_COUPLING_CURSOR_HPP
#define BOOST_TREE_COUPLING_CURSOR_HPP

#include <boost/tree/cursor_adaptor.hpp>

namespace boost {
namespace tree {

using boost::iterator_core_access;

/** \addtogroup cursor_adaptors
 *  \@{ */

template <class InCursor, class OutCursor>
class coupling_cursor;

/**
 * @brief Output cursor wrapper around an output iterator.
 * 
 * This can be very useful e.g. to have cursor algorithms actually work on
 * iterators, thus permitting some kind of linearization of a given subtree.
 * (Modelled after std::insert_iterator and the like.)
 * 
 * For construction, the outputter_cursor_iterator_wrapper might come in useful
 * in saving keystrokes.
 */
// TODO: Complete this.
// Shouldn't we be using cursor_facade?
template <class InCursor, class OutCursor>
class coupling_cursor
: public cursor_adaptor<coupling_cursor<InCursor, OutCursor>
                      , InCursor
//                      , boost::use_default
//                      , boost::use_default
//                      , boost::use_default
    >
 {
protected:
    mutable OutCursor m_out;
public:        
    /**
     * For construction, we obviously need a tree and a cursor to work on (i.e., write to).
     */
    explicit coupling_cursor(InCursor i, OutCursor o)
    : coupling_cursor::cursor_adaptor_(i), m_out(o) {}

    // Cursor-specific
    typedef coupling_cursor<InCursor, OutCursor> cursor;
    typedef coupling_cursor<typename InCursor::const_cursor, OutCursor> const_cursor;

//    operator InCursor() {
//        return this->base_reference();
//    }
//

// if InCursor != OutCursor
//    operator OutCursor() {
//        return m_out;
//    }

    InCursor& in()
    {
        return this->base_reference();
    }

    OutCursor& out()
    {
        return m_out;
    }

    bool is_root() const
    {
        return this->base_reference().is_root();
    }
    
private:
    friend class boost::iterator_core_access;
    friend class boost::tree::cursor_core_access;
    
    void increment()
    {
        ++this->base_reference();
        ++m_out;
    }

    void decrement()
    {
        --this->base_reference();
        --m_out;
    }
    
    void left()
    {
        this->base_reference().to_begin();
        m_out.to_begin();
    }
    
    void right()
    {
        this->base_reference().to_end();
        m_out.to_end();
    }
    
    void up()
    {
        this->base_reference().to_parent();
        m_out.to_parent();
    }
};

template <class InCursor, class OutCursor>
typename coupling_cursor<InCursor, OutCursor>::size_type
index(coupling_cursor<InCursor, OutCursor> const& cur)
{
    return cur.index();
}

/** 
 * @param o    An output iterator.
 * @result    An instance of coupling_cursor working on o.
 * 
 * Use as shortcut for cumbersome typenames, just as with std::inserter and the like.
 */
template <class InCursor, class OutCursor>
inline coupling_cursor<InCursor, OutCursor>
make_coupling_cursor(InCursor i, OutCursor o)
{
    return coupling_cursor<InCursor, OutCursor>(i, o);
}

} // namespace tree
} // namespace boost

/** @} */

#endif // BOOST_TREE_COUPLING_CURSOR_HPP
