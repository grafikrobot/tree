//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/binary_tree.hpp>
#include <boost/tree/searcher.hpp>

#include <boost/numeric/interval.hpp>
//#include <boost/numeric/interval/compare/lexicographic.hpp>
#include <boost/multi_index/identity.hpp>

#define BOOST_TEST_MODULE interval_search test
//#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>

//TODO: add real tests. (what is where?)
// test overlaps stuff.

// Interval example data as in GCC libstdc++'s pb_ds

// FIXME: Still buggy.
// Is the following really what we want?
using namespace boost::numeric::interval_lib::compare::lexicographic;
using boost::numeric::interval_lib::cerlt;
using boost::numeric::interval;

template <typename T>
struct cerless {
    inline bool operator() (T const& a, T const& b)
    {
        return boost::numeric::interval_lib::cerlt(a,b);
    }
};

BOOST_AUTO_TEST_CASE( interval_search_binary_tree_test )
{
    using boost::tree::searcher;
    using boost::tree::binary_tree;
    
    using boost::multi_index::identity;
    
    typedef searcher<false, binary_tree<interval<int> >, identity<interval<int> >,
                     cerless<interval<int> > > searcher_t;
    searcher_t my_tree;
    
    my_tree.insert(interval<int>(20,36));    
    my_tree.insert(interval<int>( 3,41));
    my_tree.insert(interval<int>(10,15));    
    my_tree.insert(interval<int>( 0, 1));    
    my_tree.insert(interval<int>(29,99));    

    searcher_t::iterator ci = my_tree.begin(); 
    BOOST_CHECK_EQUAL(*ci++, interval<int>( 0, 1));
//    BOOST_CHECK_EQUAL(*ci++, interval<int>( 3,41));
    BOOST_CHECK_EQUAL(*ci++, interval<int>(10,15));
//    BOOST_CHECK_EQUAL(*ci++, interval<int>(20,36));
//    BOOST_CHECK_EQUAL(*ci++, interval<int>(29,99));
//    BOOST_CHECK_EQUAL(ci, my_tree.end());
    
}
