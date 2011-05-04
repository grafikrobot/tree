//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file ascending_cursor.hpp
 * Ascending cursor adaptor implementation
 */

#ifndef BOOST_TREE_ASCENDING_CURSOR_HPP
#define BOOST_TREE_ASCENDING_CURSOR_HPP


#include <boost/tree/cursor.hpp>
#include <boost/tree/cursor_facade.hpp>
#include <boost/tree/iterator.hpp>
#include <boost/tree/root_tracking_cursor.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_pointer.hpp>

#include <stack>

namespace boost {
namespace tree {

/** \addtogroup cursor_adaptors
 * Predefined cursor adaptors equip a given cursor with additional properties.
 *  \@{ */
 
struct ascending;

template <class DescendingCursor> 
class ascending_cursor;

template <class Cursor>
typename iterator< ascending, ascending_cursor<Cursor> >::difference_type
distance(iterator< ascending, ascending_cursor<Cursor> > iter1
       , iterator< ascending, ascending_cursor<Cursor> > iter2);

/**
 * @brief Turns any descending cursor into an ascending one. 
 * 
 * When descending from a given initial cursor, this wrapper
 * tracks any cursors along the way. This way, it is able to
 * re-ascend later (only up to the initially passed cursor,
 * of course).  
 */
template <class DescendingCursor> 
class ascending_cursor
: public cursor_facade<ascending_cursor<DescendingCursor>
      , typename cursor_value<DescendingCursor>::type
      , random_access_traversal_tag
      , ascending_vertical_traversal_tag
    > {
private:
    struct enabler {};
    typedef ascending_cursor<DescendingCursor> self_type;
public:
    typedef typename DescendingCursor::value_type value_type;
    typedef typename DescendingCursor::reference reference;

    // Container-specific:
    typedef typename DescendingCursor::size_type size_type;

    // DescendingCursor-specific
    typedef ascending_cursor<DescendingCursor> cursor;
    typedef ascending_cursor<typename DescendingCursor::const_cursor> const_cursor;
    
    // Container-specific:
    typedef cursor iterator;
    typedef const_cursor const_iterator;
    
    template <class OtherCursor>
    struct rebind {
        typedef ascending_cursor<OtherCursor> other;
    };
    
    ascending_cursor()
    : m_s() {}

    explicit ascending_cursor(DescendingCursor c)
    {
        m_s.push(c); // Subtree root.
    }

    template <class OtherCursor>
    ascending_cursor(
        ascending_cursor<OtherCursor> const& other
      , typename boost::enable_if<
            boost::is_convertible<OtherCursor*, DescendingCursor*>
          , enabler
        >::type = enabler()
    )
      : m_s(other.m_s) {}

private:
    friend class boost::iterator_core_access;
    friend class boost::tree::cursor_core_access;
    
    friend class root_tracking_cursor<self_type>;
    
//    friend 
//        typename boost::tree::iterator<ascending, self_type>::difference_type
//        boost::tree::distance<>(
//            boost::tree::iterator<ascending, self_type> 
//          , boost::tree::iterator<ascending, self_type>);
    
    std::stack<DescendingCursor> m_s; // pimpl?
     
    reference dereference() const
    {
        return *m_s.top();
    }
    
    bool equal(cursor const& other) const
    {
        return (this->m_s == other.m_s);
    }
    
    void increment()
    {
        ++m_s.top();
    }
    
    void decrement()
    {
        --m_s.top();
    }    
    
    void advance(typename ascending_cursor::cursor_facade_::difference_type n)
    {
        m_s.top() += n;
    }
    
    typename ascending_cursor::cursor_facade_::difference_type
    distance_to(ascending_cursor z) const //FIXME: convertible to instead of ascending_cursor
    {
            return (z.m_s.top() - this->m_s.top());
    }
    
    // Container specific
    bool const empty_() const
    {
        return m_s.top().is_leaf();
    }
    
    size_type size_()
    {
        return m_s.top().size();
    }
    
    size_type max_size_()
    {
        return m_s.top().max_size();
    }
    
    size_type const idx() const
    {
        return index(m_s.top());
    }

    void left()
    {
        m_s.push(m_s.top().begin());
    }

    void right()
    {
        m_s.push(m_s.top().end());
    }

    // This is what actually makes it an AscendingCursor
    void up()
    {
        m_s.pop();
    }
};

template <class Cursor>
inline ascending_cursor<Cursor> make_ascending_cursor(Cursor c)
{
    return ascending_cursor<Cursor>(c);
}

template <class Cursor> 
class root_tracking_cursor< ascending_cursor<Cursor> >
: public cursor_adaptor<root_tracking_cursor< ascending_cursor<Cursor> >
                      , ascending_cursor<Cursor> 
                      , boost::use_default
                      , typename cursor_horizontal_traversal<
                              ascending_cursor<Cursor> >::type
                      , ascending_vertical_traversal_tag
    > {
 private:
    struct enabler {};
    typedef root_tracking_cursor< ascending_cursor<Cursor> > self_type;
 public:
    typedef typename ascending_cursor<Cursor>::value_type value_type;

    // Container-specific:
    typedef typename ascending_cursor<Cursor>::size_type size_type;

    // Cursor-specific
     typedef root_tracking_cursor< ascending_cursor<Cursor> > cursor;
     typedef root_tracking_cursor< 
         typename ascending_cursor<Cursor>::const_cursor > const_cursor;
    
    // Container-specific:
    typedef cursor iterator;
    typedef const_cursor const_iterator;
    
    template <class OtherCursor>
    struct rebind {
        typedef root_tracking_cursor< ascending_cursor<OtherCursor> > other;
    };
    
    root_tracking_cursor()
    : root_tracking_cursor::cursor_adaptor_(), m_root_depth(1) {}

    explicit root_tracking_cursor(ascending_cursor<Cursor> c)
    : root_tracking_cursor::cursor_adaptor_(c), m_root_depth(c.m_s.size()) {}

//    template <class OtherCursor>
//    root_tracking_cursor(
//        root_tracking_cursor< ascending_cursor<OtherCursor> > const& other
//      , typename boost::enable_if<
//            boost::is_convertible<OtherCursor*
//                                , Cursor*>
//          , enabler
//        >::type = enabler()
//    )
//    : root_tracking_cursor::cursor_adaptor_(other.base())
//    , m_root_depth(other.m_root_depth) {}
//
//    template <class OtherCursor>
//    root_tracking_cursor(
//        root_tracking_cursor<OtherCursor> const& other
//      , typename boost::enable_if<
//            boost::is_convertible<OtherCursor*
//                                , ascending_cursor<Cursor>*>
//          , enabler
//        >::type = enabler()
//    )
//    : root_tracking_cursor::cursor_adaptor_(other.base())
//    , m_root_depth(other.base().m_s.size()) {}

 private: 
    std::size_t const m_root_depth;
     
    friend class boost::iterator_core_access;
    friend class boost::tree::cursor_core_access;
         
//    bool equal(cursor const& other) const
//    {
//    }

    bool is_root_() const
    {
        return this->base().m_s.size() == m_root_depth;
    }
};

/** @} */

/// Specialization
template <class Cursor>
typename iterator< ascending, ascending_cursor<Cursor> >::difference_type
distance(iterator< ascending, ascending_cursor<Cursor> > iter1
       , iterator< ascending, ascending_cursor<Cursor> > iter2)
{
    return ascending_cursor<Cursor>(iter2).m_s.size() 
         - ascending_cursor<Cursor>(iter1).m_s.size();
}

} // namespace tree
} // namespace boost


#endif // BOOST_TREE_ASCENDING_CURSOR_HPP
