//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file string.hpp
 * Optimising string comparator
 */

#ifndef BOOST_TREE_COMPARATORS_STRING_HPP
#define BOOST_TREE_COMPARATORS_STRING_HPP

#include <algorithm>

namespace boost {
namespace tree {

//concept check Cntnr1::value_type == Cntnr2::value_type
//ditto for size_type
//ForwardContainer? (cause we need quick positioning with size_type...)
template <class Cntnr1, class Cntnr2>
class container_lexicographical_compare : public std::binary_function<Cntnr1, Cntnr2, bool> {
public:
    container_lexicographical_compare(typename Cntnr1::size_type pos = 0) : m_pos(pos) {}
    bool operator() (Cntnr1 const& x, Cntnr2 const& y)
    {
        typename Cntnr1::const_iterator it1 = x.begin();
        typename Cntnr2::const_iterator it2 = y.begin();
        std::advance(it1, m_pos);
        std::advance(it2, m_pos);
        bool ret = std::lexicographical_compare(it1, x.end(), it2, y.end());
        m_pos = std::distance(x.begin(), it1);
        return ret;
    }
private:
     typename Cntnr1::size_type m_pos;
};

//TODO: even more efficient version for strings (using their compare members)
      
} // namespace tree
} // namespace boost

#endif // BOOST_TREE_COMPARATORS_STRING_HPP


