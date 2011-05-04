//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file augmented_iterator.hpp
 * Augmented iterator implementation
 */


#ifndef BOOST_TREE_DETAIL_AUGMENTED_ITERATOR_HPP
#define BOOST_TREE_DETAIL_AUGMENTED_ITERATOR_HPP

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/bind.hpp>
#include <boost/multi_index/identity.hpp>

#include <iterator>

namespace boost {
namespace tree {
namespace detail {

using boost::multi_index::identity;

//TODO: Add extractor as 2nd ctor parameter?
//        Possibly use boost::transform_iterator?
template <class InorderIter, 
          class Extract = identity<typename InorderIter::value_type>,
          class Tag = typename std::iterator_traits<InorderIter>::iterator_category
         >
class augmented_iterator;

template <class InorderIter, class Extract>
class augmented_iterator<InorderIter, Extract, bidirectional_traversal_tag>
 : public boost::iterator_adaptor<augmented_iterator<InorderIter, Extract, bidirectional_traversal_tag>
      , InorderIter
      , typename Extract::result_type //InorderIter::value_type::value_type
      , bidirectional_traversal_tag
    > {
 private:
    struct enabler {};
 public:
    augmented_iterator()
    : augmented_iterator::iterator_adaptor_() {}

    explicit augmented_iterator(InorderIter p)
    : augmented_iterator::iterator_adaptor_(p) {}

    explicit augmented_iterator(typename InorderIter::base_type c)
    : augmented_iterator::iterator_adaptor_(InorderIter(c)) {}

    template <class OtherInorderIter>
    augmented_iterator(
        augmented_iterator<OtherInorderIter> const& other
      , typename boost::enable_if<
            boost::is_convertible<OtherInorderIter,InorderIter>
          , enabler
        >::type = enabler()
    )
      : augmented_iterator::iterator_adaptor_(other.base()) {}

    operator InorderIter()
    {
        return this->base();
    }
    
 private:
    friend class boost::iterator_core_access;
    
    typename augmented_iterator::iterator_adaptor_::reference
    dereference() const
    {
        return Extract()(this->base());
    }    
};


} // namespace detail
} // namespace tree
} // namespace boost

#endif // BOOST_TREE_DETAIL_AUGMENTED_ITERATOR_HPP
