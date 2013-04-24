//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file searcher.hpp
 * Generalized tree search algorithms and front-end class
 */
// TODO: 
// * Concept checks all over.
// * add versions without cmp argument (just using <)
// * Move functionality to TR1 (wrappers)
// * use boost:: (or tr1::)function

#ifndef BOOST_TREE_SEARCHER_HPP
#define BOOST_TREE_SEARCHER_HPP

#include <boost/tree/iterator.hpp>

#include <boost/bind.hpp>
#include <boost/multi_index/identity.hpp>

using boost::multi_index::identity;

namespace boost {
namespace tree {


/** @brief A %searcher
 * 
 * This class models the 
 * \link http://www.sgi.com/tech/stl/SortedAssociativeContainer.html
 * Sorted Associative Container \endlink concept; it is 
 * actually nothing else than a container adaptor bundling a Container 
 * together with key extraction and comparison functors, guaranteeing
 * that insertion of a value will not violate the ordering (which is established
 * by comparing the values' keys).
 * For an "ordinary", one-dimensional Sequence, the STL's binary search 
 * algorithms (lower_bound, upper_bound etc.) are wrapped as members and used to
 * determine the correct insertion position. If the Container however models a 
 * Hierarchical Container, corresponding sorted tree search algorithms are
 * used instead.
 * Note that this declaration is empty;
 * there are two specializations, one for each of the two possible values of the
 * %Multi template argument:
 *     - true for a 
 * \link http://www.sgi.com/tech/stl/MultipleSortedAssociativeContainer.html
 * Multiple Sorted Associative Container \endlink , i.e. one that allows
 * multiple values to share the same key
 *     - false for a 
 * \link http://www.sgi.com/tech/stl/UniqueSortedAssociativeContainer.html
 * Unique Sorted Associative Container \endlink , allowing only one value for 
 * each key.
 * 
 * These specializations are necessary as their interfaces differ.
 */
template <bool Multi, class Container,
          class Extract = 
              boost::multi_index::identity<typename Container::value_type>,
          class Compare = std::less<typename Extract::result_type>
          >
class searcher; 

//derive both specializations from common base modelling only 
//SortedAssociativeContainer

/** 
 * @brief Unique %searcher specialization
 * 
 * This class models the 
 * \link http://www.sgi.com/tech/stl/UniqueSortedAssociativeContainer.html
 * Unique Sorted Associative Container \endlink concept. Refer to the 
 * unspecialized template's (boost::tree::searcher)
 * documentation for further information.
 */
template <class Container, class Extract, class Compare>
class searcher<false, Container, Extract, Compare> {

    typedef searcher<false, Container, Extract, Compare> self_type;

public:
     typedef Container container_type; // type name as in STL sequence adaptors
    
    typedef typename container_type::iterator iterator;
    typedef typename container_type::const_iterator const_iterator;
            
     typedef typename container_type::value_type value_type;
     typedef typename container_type::size_type size_type;
 
     typedef Extract key_extract;
     typedef typename key_extract::result_type key_type;
     typedef Compare key_compare;
     
     searcher(key_extract const& extract = key_extract(), 
              key_compare const& compare = key_compare(),
             container_type const& sortable = container_type())
      : c(sortable), comp(compare), ext(extract) { }
             
     /**
     * Returns a read/write ("mutable") iterator to first value in the 
     * %searcher. Iteration is done in ascending order as  dictated by comparing
     * the keys (extracted from the values via %extract) using %cmp.
     */
     iterator begin()
    {
        return c.begin();
    }

    /**
     * Returns a read-only const_iterator to the first value in the %searcher. 
     * Iteration is done in ascending order as dictated by comparing the keys 
     * (extracted from the values via %extract) using %cmp.
     */      
    const_iterator begin() const
    {
        return cbegin();
    }
      
     /**
     * Returns a read-only const_iterator to the first value in the %searcher. 
     * Iteration is done in ascending order as dictated by comparing the keys 
     * (extracted from the values via %extract) using %cmp.
     */      
    const_iterator cbegin() const
    {
        return c.cbegin();
    }      
     
    /**
     * Returns a read/write ("mutable") iterator to the position one past the 
     * last value in the %searcher. Iteration is done in ascending order as 
     * dictated by comparing the keys (extracted from the values via 
     * %extract) using %cmp.
     */
    iterator end()
    {
        return c.end();
    }
    
    /**
     * Returns a read-only const_iterator to the position one past the last 
     * value in the %searcher. Iteration is done in ascending order as dictated 
     * by comparing the keys (extracted from the values via 
     * %extract) using %cmp.
     */
    const_iterator end() const
    {
        return cend();
    }
    
    /**
     * Returns a read-only const_iterator to the position one past the last 
     * value in the %searcher. Iteration is done in ascending order as dictated 
     * by comparing the keys (extracted from the values via 
     * %extract) using %cmp.
     */
    const_iterator cend() const
    {
        return c.cend();
    }

    /**
     * @brief        Finds the first position in the searcher in which @a val 
     *                 could be inserted without changing the ordering, using comp
     *                 for comparisons.
     * @param k        The search term
     * @return        An iterator pointing to the first element not less than 
     *                @a k, or end() if every element in the searcher is less than 
     *                 @a k.
     */
     iterator lower_bound(key_type const& k)
     {
         return c.lower_bound(k, bind<bool>(comp, bind(ext(), _1), _2));
     }

    /**
     * @brief        Finds the first position in the searcher in which @a val 
     *                 could be inserted without changing the ordering, using comp
     *                 for comparisons.
     * @param k        The search term
     * @return        A const_iterator pointing to the first element not less than 
     *                @a k, or end() if every element in the searcher is less than 
     *                 @a k.
     */
     const_iterator lower_bound(key_type const& k) const
     {
         return c.lower_bound(k, bind<bool>(comp, bind(ext(), _1), _2));
     }

    /**
     * @brief        Finds the last position in the searcher in which @a val 
     *                 could be inserted without changing the ordering, using comp
     *                 for comparisons.
     * @param k        The search term
     * @return        An iterator pointing to the first element greater than 
     *                @a k, or end() if no element in the searcher is greater than 
     *                 @a k.
     */
     iterator upper_bound(key_type const& k)
     {
         return c.upper_bound(k, bind<bool>(comp, bind(ext(), _1), _2));
     }

    /**
     * @brief        Finds the last position in the searcher in which @a val 
     *                 could be inserted without changing the ordering, using comp
     *                 for comparisons.
     * @param k        The search term
     * @return        A const_iterator pointing to the first element greater than 
     *                @a k, or end() if no element in the searcher is greater than 
     *                 @a k.
     */
     const_iterator upper_bound(key_type const& k) const
     {
         return c.upper_bound(k, bind<bool>(comp, bind(ext(), _1), _2));
     }
     
     /**
     * @brief        Attempts to insert @a val into the %searcher
     * @param val    Value to be inserted
     * @return        A pair, whose 
     *                 - second member is a bool that is true iff the
     *                 insertion was successful (which is only the case if there 
     *                 was no element with the same key as @a val before the
     *                 attempted insertion)
     *                 - and whose first member is an iterator indicating the 
     *                 position where @val was inserted (if the second pair member 
     *                 is true) or the element's position whose key part is equal 
     *                 to @a val's (if the second pair member is false)
     */
    std::pair<iterator, bool> insert(value_type const& val)
    {
        //TODO
        iterator it = c.lower_bound(ext(val), bind<bool>(comp, 
            bind<typename key_extract::result_type>(ext, _1), _2));
        if (it == c.end())
            return std::make_pair(it, false);
        return std::make_pair(c.insert(it, val), true);
     }
     
    
    /**
     * @brief        Attempts to insert @a val into the %searcher
     * @param pos    An iterator that serves as a hint to indicate the position
     *                 in front of which @a val must be inserted so the %searcher's
     *                 order (determined by the key part of @a val) is kept.
     * @param val    Value to be inserted
     * @return        An iterator pointing to the element whose key is equal to
     *                 @a val's (may be different from @a val if such an element
     *                 already existed before the attempted insertion).
     */
    iterator insert (iterator pos, value_type const& val)
     {
         key_type key = ext(val);
         
        if ((pos != c.end()) && comp(key, *pos))
            if (comp(*--pos, key))
                 return iterator(c.insert(++pos, val));

         //the pos hint was not useful
        return this->insert(val).first;
     }
     

     template <class InputIterator>
    void insert (InputIterator a, InputIterator b)
    {
        
    }
    
    /** 
     * @brief Erases the value at pos
     * @param pos    The iterator pointing to the value to be erased.
     */
     iterator erase (iterator pos)
     {
         return c.erase(pos);
     }
     
     size_type erase (key_type const& k)
     {
     }
     
     void erase (iterator a, iterator b)
     {
     }
     
     void clear()
     {
         c.clear();
     }
     
// protected. It's a sequence (and hierarchy) adaptor, and the STL ones do the 
// same.
protected: 
     container_type c;
     key_compare comp;
     key_extract ext;
};

/* @brief Multiple key %searcher specialization
 * 
 * This class models the 
 * \link http://www.sgi.com/tech/stl/MultipleSortedAssociativeContainer.html
 * Multiple Sorted Associative Container \endlink concept. Refer to the 
 * unspecialized template's documentation for further information.
 */
// (TODO)

} // namespace tree
} // namespace boost

#endif // BOOST_TREE_SEARCHER_HPP


