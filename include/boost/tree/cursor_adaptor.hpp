//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file cursor_adaptor.hpp
 * Cursor adaptor implementation
 */

// TODO: Use TR1 type_traits (integral_constant)

#ifndef BOOST_TREE_CURSOR_ADAPTOR_HPP
#define BOOST_TREE_CURSOR_ADAPTOR_HPP

#include <boost/tree/cursor.hpp>

#include <boost/tree/cursor_facade.hpp>

#include <boost/iterator/iterator_adaptor.hpp>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost {
namespace tree {

using boost::iterator_core_access;

// We'll abuse iterator_adaptor to determine our types.
template <
    class Derived
  , class Base
  , class Value                         = use_default
  , class HorizontalTraversalOrCategory = use_default
  , class VerticalTraversal             = use_default
  , class Reference                     = use_default
  , class Difference                    = use_default
  , class Size                          = use_default
>
class cursor_adaptor_base
: private iterator_adaptor<Derived 
                         , Base
                         , Value
                         , HorizontalTraversalOrCategory
                         , Reference
                         , Difference>
{
private:
    cursor_adaptor_base() {} // This class is used for typedefs only.
    
    typedef typename iterator_adaptor<Derived, Base, Value
                                    , HorizontalTraversalOrCategory, Reference
                                    , Difference>::super_t h_super_t;
public:
    typedef typename h_super_t::value_type value_type;    
    typedef typename h_super_t::reference reference;
    typedef typename h_super_t::difference_type difference_type;
    typedef typename h_super_t::pointer pointer;
    typedef typename h_super_t::iterator_category iterator_category;
    
    // size_type isn't in iterator_adaptor or _facade, 
    // so we have to calculate it on our own: 
    typedef typename mpl::eval_if<
        is_same<Size, use_default>
      , boost::tree::cursor_size<Base>
      , mpl::identity<Size>
    >::type size_type;

    // Same for vertical_traversal
    typedef typename mpl::eval_if<
        is_same<VerticalTraversal, use_default>
      , boost::tree::cursor_vertical_traversal<Base>
      , mpl::identity<VerticalTraversal>
    >::type vertical_traversal;
    
    typedef cursor_facade<Derived
                        , value_type
                        , iterator_category
                        , vertical_traversal
                        , reference
                        , difference_type
                        , size_type> type;
};

template <
    class Derived
  , class Base
  , class Value                         = use_default
  , class HorizontalTraversalOrCategory = use_default
  , class VerticalTraversal   = use_default
  , class Reference                     = use_default
  , class Difference                    = use_default
  , class Size                          = use_default
>
class cursor_adaptor 
: public cursor_adaptor_base< Derived
                            , Base
                            , Value
                            , HorizontalTraversalOrCategory
                            , VerticalTraversal
                            , Reference
                            , Difference
                            , Size >::type
{
protected:
    typedef cursor_adaptor<Derived, Base, Value, HorizontalTraversalOrCategory,
                           VerticalTraversal, Reference, Difference,
                           Size> cursor_adaptor_;
    
    typedef typename cursor_adaptor_base<Derived, Base, Value 
                                       , HorizontalTraversalOrCategory
                                       , VerticalTraversal
                                       , Reference
                                       , Difference
                                       , Size>::type cursor_facade_;
    
    Base const& base_reference() const
    { return m_cursor; }
    
    Base& base_reference()
    { return m_cursor; }
    
private:
    mutable Base m_cursor; // mutable for use with output cursors.
    
    friend class iterator_core_access;
    friend class cursor_core_access;

public: 
    typedef Base base_type;
     
    typedef typename cursor_facade_::iterator_category iterator_category;

    typedef typename cursor_facade_::horizontal_traversal horizontal_traversal;
    typedef typename cursor_facade_::vertical_traversal cursor_category;
    
    typedef typename cursor_facade_::difference_type difference_type;
    typedef typename cursor_facade_::size_type size_type;
 
    cursor_adaptor() {}
    
    explicit cursor_adaptor(Base const& cur) : m_cursor(cur) {}
    
    Base const& base() const
    { return m_cursor; }
    
    typename cursor_facade_::reference dereference() const
    {
        return *m_cursor;
    }
    
private:     
    void increment()
    {
        ++m_cursor;
    }
     
    void decrement()
    {
        --m_cursor;
    }
     
    template <class OtherDerived, class OtherCursor, class V, class C, 
              class R, class D, class S>
    bool equal(cursor_adaptor<OtherDerived, OtherCursor, 
                              V, C, R, D, S> const& x) const
    {
        return m_cursor == x.base();
    }
     
    template <class OtherDerived, class OtherCursor, class V, class C, 
              class R, class D, class S>
    difference_type distance_to(cursor_adaptor<OtherDerived, OtherCursor, 
                                          V, C, R, D, S> const& x) const
    {
        return x.base() - m_cursor;
    }
     
    bool const empty_() const
    {
        return m_cursor.is_leaf();
    }

    bool const is_root_() const
    {
        return m_cursor.is_root();
    }
    
    size_type const size_() const
    {
        return m_cursor.size();
    }
    
    size_type const max_size_() const
    {
        return m_cursor.max_size();
    }

    size_type const idx() const
    {
        return m_cursor.index();
    }

    void left()
    {
        m_cursor.to_begin();
    }

    void right()
    {
        m_cursor.to_end();
    }
    
    void up()
    {
        m_cursor.to_parent();
    }
};

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_CURSOR_ADAPTOR_HPP
