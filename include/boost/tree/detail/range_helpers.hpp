//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file searchers/key.hpp
 * Binary (key) tree search algorithms
 */
// TODO: 
// * Concept checks all over.
// * add versions without cmp argument (just using <)
// * Move functionality to TR1 (wrappers)
// * use boost:: (or tr1::)function

#ifndef BOOST_TREE_DETAIL_RANGE_HELPERS_HPP
#define BOOST_TREE_DETAIL_RANGE_HELPERS_HPP


#include <boost/tree/cursor.hpp>

#include <boost/bind.hpp>
#include <boost/type_traits.hpp>

#include <boost/range.hpp>

#include <algorithm>        // lower_bound, upper_bound etc.
#include <functional>    // ptr_fun, not1, tr1::bind


namespace boost {
namespace tree {

//range helpers

/** 
 * @brief \c lower_bound substitute for (efficient) \b binary tree search.
 * @param first    Iterator
 * @param last    Iterator
 * @param val    Search key
 * @param cmp    Comparison functor
 * @return        An iterator to the first element "not less than" @a val,
 *                 or @a last if every element is less than @a val.
 * 
 * Compares only @a first's value to @a val
*/
template<class ForwardIterator, typename T, typename Compare>
ForwardIterator
binary_lower_bound(ForwardIterator first, ForwardIterator last, 
                     T const& val, Compare cmp)
{
    return cmp(*first, val) ? last : first;    
}


/** 
 * @brief \c upper_bound substitute for (efficient) \b binary tree search.
 * @param first    Iterator
 * @param last    Iterator
 * @param val    Search key
 * @param cmp    Comparison functor
 * @return        An iterator to the first element "greater than" @a val,
 *                 or @a last if no element is greater than @a val.
 * 
 * Compares only @a first's value to @a val. 
*/
template<class ForwardIterator, typename T, typename Compare>
ForwardIterator
binary_upper_bound(ForwardIterator first, ForwardIterator last, 
                   T const& val, Compare cmp)
{
    return cmp(val, *first) ? first : last;
}


template<class InputIterator, typename T, typename Compare>
inline InputIterator
linear_lower_bound(InputIterator first, InputIterator last, 
                   T const& val, Compare cmp)
{
    return std::find_if(first, last, !bind(cmp, _1, val));
}

template<class InputIterator, typename T, typename Compare>
inline InputIterator
linear_upper_bound(InputIterator first, InputIterator last, 
                   T const& val, Compare cmp)
{
    return std::find_if(first, last, bind(cmp, val, _1));
}

//template< class ForwardReadableRange, class T >
//inline typename boost::range_iterator< ForwardReadableRange >::type
//find( ForwardReadableRange& c, const T& value )
//{
//   return std::find( boost::begin( c ), boost::end( c ), value );
//}
//
//template< class ForwardReadableRange, class T >
//inline typename boost::range_const_iterator< ForwardReadableRange >::type
//find( const ForwardReadableRange& c, const T& value )
//{
//   return std::find( boost::begin( c ), boost::end( c ), value );
//}

// does this exist already in boost.range?
template <class ForwardReadableRange, class T, class Cmp>
inline typename boost::range_iterator<ForwardReadableRange>::type
lower_bound(ForwardReadableRange r, T const& val, Cmp cmp)
{
    return std::lower_bound(boost::begin(r), boost::end(r), val, cmp);
}

template <class ForwardReadableRange, class T, class Cmp>
inline typename boost::range_const_iterator<ForwardReadableRange>::type
lower_bound(ForwardReadableRange r, T const& val, Cmp cmp)
{
    return std::lower_bound(boost::begin(r), boost::end(r), val, cmp);
}



} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_RANGE_HELPERS_HPP






