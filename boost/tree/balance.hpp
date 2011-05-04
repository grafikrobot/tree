//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/** 
 * @file balance.hpp
 * Balanced tree implementation
 */


#ifndef BOOST_TREE_balance_HPP
#define BOOST_TREE_balance_HPP

#include <boost/tree/cursor.hpp>
#include <boost/tree/iterator.hpp>

#include <boost/tree/detail/balancers/unbalanced.hpp>
#include <boost/tree/detail/augmentors/unaugmented.hpp>

#include <boost/tree/inorder_algorithms.hpp>
#include <boost/tree/detail/augmented_iterator.hpp>

#include <boost/bind.hpp>
#include <boost/multi_index/member.hpp>

#include <iterator>
#include <memory>

namespace boost {
namespace tree {

using detail::augmented_iterator;

using boost::multi_index::member;

struct empty_class { };

// TODO: Remove Meta2. This stuff must be done via some MPL magic.
 
template <class Val, class Meta, class Meta2 = empty_class>
struct augmented_type {
    typedef Val value_type;
    typedef Meta metadata_type;
//    struct metadata_type : public Meta, public Meta2 {
//        metadata_type() : Meta(), Meta2() {}
//    };
    
    value_type data;
    metadata_type meta;
    
    augmented_type(value_type const& d = value_type()
                 , metadata_type const& m = metadata_type())
    : data(d), meta(m) {}
    
    augmented_type(augmented_type const& x)
    : data(x.data), meta(x.meta) {}
    
    metadata_type& metadata()
    {
        return meta;
    }
    
    metadata_type const& metadata() const
    {
        return meta;
    }

    typedef member<augmented_type,value_type,&augmented_type::data> extract_data;
    typedef member<augmented_type,metadata_type,&augmented_type::meta> extract_meta;
};

// metadata traits type specialization for augmented_type
template <class Val, class Meta, class Meta2>
struct metadata< augmented_type<Val,Meta,Meta2> > {
    typedef typename augmented_type<Val,Meta,Meta2>::metadata_type type;
};

template <class Cursor> 
class is_on_top_cursor
: public cursor_adaptor<is_on_top_cursor<Cursor>, Cursor>
{
public:
    is_on_top_cursor()
    : is_on_top_cursor::cursor_adaptor_() {}

    is_on_top_cursor(Cursor p)
    : is_on_top_cursor::cursor_adaptor_(p) {}
    
    bool is_root() const
    {
        return this->base_reference().is_on_top();
    }
};

template <class Cursor>
typename is_on_top_cursor<Cursor>::size_type
index(is_on_top_cursor<Cursor> const& cur)
{
    return cur.index();
}

/** 
 * @brief A %balance.
 * This class models the hierarchy concept, the container concept and the
 * sequence concept. TODO: complete this...
 *
*/
template <class Hierarchy, class Balance>
class balance {
 public:
    typedef typename Hierarchy::value_type value_type;
    typedef Balance balancer_type;
    
    typedef typename Balance::metadata_type metadata_type;
    
    typedef augmented_type< value_type, metadata_type, 
                            typename metadata<value_type>::type > data_type;
    typedef typename Hierarchy::template rebind<data_type>::other hierarchy_type;

protected:
    hierarchy_type h;

private:
    typedef balance<Hierarchy, Balance> self_type;
    
    typedef typename hierarchy_type::cursor cursor;
    typedef typename hierarchy_type::const_cursor const_cursor;

public:    
    typedef augmented_iterator<boost::tree::iterator<inorder, is_on_top_cursor<cursor> >, typename data_type::extract_data, bidirectional_traversal_tag> iterator;
    typedef augmented_iterator<boost::tree::iterator<inorder, is_on_top_cursor<const_cursor> >, typename data_type::extract_data, bidirectional_traversal_tag> const_iterator;
    
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef typename hierarchy_type::allocator_type allocator_type;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::size_type size_type;
    typedef typename allocator_type::difference_type difference_type;

    explicit balance (hierarchy_type const& hier = hierarchy_type())
    : h(hier)
    {}
    
    // TODO: 3rd arg...?
    explicit balance (size_type n, value_type const& value = value_type(), 
                      hierarchy_type const& hier = hierarchy_type())
    : h(hier)
    {
        for (n; n!=0; --n)
            this->insert(this->end(), value);
    }

    template <class InputIterator>
    balance (InputIterator first, InputIterator last, 
             hierarchy_type const& hier = hierarchy_type())
    : h(hier)
    {
        while (first++ != last)
            this->insert(this->end(), *first);
    }
    
    balance (self_type const& other)
    : h(other.h)
    {}
    
    self_type& operator=(
        self_type const& x);
    template <class InputIterator>
        void assign(InputIterator first, InputIterator last);
    template <class Size, class T>
        void assign(Size n, const T& t = T());
        
    /// Functions returning (inorder) iterators (as required by the Sequence
    /// concept)
    
    /**
     * Returns a read/write ("mutable") iterator to the first (inorder) value.
     */      
    iterator begin()
    {
        cursor c = h.root();
        to_first(inorder(), c);
        return iterator(c);
        //return iterator(first(inorder(), h.root()));
    }
    
    /**
     * Returns a read-only const_iterator to the first (inorder) value.
     */      
    const_iterator begin() const
    {
        return cbegin();
    }
    
    /**
     * Returns a read-only const_iterator to the first (inorder) value.
     */      
    const_iterator cbegin() const
    {
        const_cursor c = h.croot();
        to_first(inorder(), c);
        return const_iterator(c);
        //return const_iterator(h.inorder_cfirst());
    }

    /**
     * Returns a read/write ("mutable") inorder iterator to the position one 
     * past the last (inorder) value in the %balance.  
     */
    iterator end()
    {
        cursor c = h.root();
        to_past(inorder(), c);
        return iterator(c);
    }

    /**
     * Returns a read-only inorder const_iterator to the position one past the 
     * last (inorder) value in the %balance.
     */    
    const_iterator end() const
    {
        return cend();
    }
    
    /**
     * Returns a read-only inorder const_iterator to the position one past the 
     * last (inorder) value in the %balance. 
     */    
    const_iterator cend() const
    {
        const_cursor c = h.croot();
        to_past(inorder(), c);
        return const_iterator(c);
    }

    /**
     * @brief        Finds the first position in the @balance in which @a k
     *                 could be inserted without changing the ordering, using <
     *                 (less than) for comparisons.
     * @param k        The search term
     * @return        An iterator pointing to the first element not less than 
     *                @a k, or end() if every element in the @balance is
     *                 less than @a k.
     */
     iterator lower_bound(value_type const& k)
     {
         return lower_bound(k, std::less<value_type>());
     }

    /**
     * @brief        Finds the first position in the @balance in which @a k
     *                 could be inserted without changing the ordering, using <
     *                 (less than) for comparisons.
     * @param k        The search term
     * @return        A const_iterator pointing to the first element not less than 
     *                @a k, or end() if every element in the @balance is
     *                 less than @a k.
     */
     const_iterator lower_bound(value_type const& k) const
     {
         return lower_bound(k, std::less<value_type>());
     }

    /**
     * @brief        Finds the first position in the @balance in which @a k
     *                 could be inserted without changing the ordering, using cmp
     *                 for comparisons.
     * @param k        The search term
     * @param cmp    The comparison functor
     * @return        An iterator pointing to the first element not less than 
     *                @a k, or end() if every element in the @balance is
     *                 less than @a k.
     */
     template <class Cmp>
     iterator lower_bound(value_type const& k, Cmp cmp)
     {
         return iterator(boost::tree::lower_bound(h.root(), k, 
             bind<bool>(cmp, bind(typename data_type::extract_data(), _1), _2)));
     }

    /**
     * @brief        Finds the first position in the @balance in which @a k
     *                 could be inserted without changing the ordering, using cmp
     *                 for comparisons.
     * @param k        The search term
     * @param cmp    The comparison functor
     * @return        A const_iterator pointing to the first element not less than 
     *                @a k, or end() if every element in the @balance is
     *                 less than @a k.
     */
     template <class Cmp>
     const_iterator lower_bound(value_type const& k, Cmp cmp) const
     {
         return const_iterator(boost::tree::lower_bound(h.croot(), k,
             bind<bool>(cmp, bind(typename data_type::extract_data(), _1), _2)));
     }

    /**
     * @brief        Finds the last position in the @balance in which @a k
     *                 could be inserted without changing the ordering, using <
     *                 (less than) for comparisons.
     * @param k        The search term
     * @return        An iterator pointing to the first element greater than 
     *                @a k, or end() if no element in the @balance is
     *                 greater than @a k.
     */
     iterator upper_bound(value_type const& k)
     {
         return upper_bound(k, std::less<value_type>());
     }

    /**
     * @brief        Finds the last position in the @balance in which @a k
     *                 could be inserted without changing the ordering, using <
     *                 (less than) for comparisons.
     * @param k        The search term
     * @return        A const_iterator pointing to the first element greater than 
     *                @a k, or end() if no element in the @balance is
     *                 greater than @a k.
     */
     const_iterator upper_bound(value_type const& k) const
     {
         return upper_bound(k, std::less<value_type>());
     }

    /**
     * @brief        Finds the last position in the @balance in which @a k
     *                 could be inserted without changing the ordering, using cmp
     *                 for comparisons.
     * @param k        The search term
     * @param cmp    The comparison functor
     * @return        An iterator pointing to the first element greater than 
     *                @a k, or end() if no element in the @balance is
     *                 greater than @a k.
     */
     template <class Cmp>
     iterator upper_bound(value_type const& k, Cmp cmp)
     {
         return iterator(boost::tree::upper_bound(h.root(), k, 
             bind<bool>(cmp, bind(typename data_type::extract_data(), _1), _2)));
     }

    /**
     * @brief        Finds the last position in the @balance in which @a k
     *                 could be inserted without changing the ordering, using cmp
     *                 for comparisons.
     * @param k        The search term
     * @param cmp    The comparison functor
     * @return        A const_iterator pointing to the first element greater than 
     *                @a k, or end() if no element in the @balance is
     *                 greater than @a k.
     */
     template <class Cmp>
     const_iterator upper_bound(value_type const& k, Cmp cmp) const
     {
         return const_iterator(boost::tree::upper_bound(h.croot(), k,
             bind<bool>(cmp, bind(typename data_type::extract_data(), _1), _2)));
     }
          
    /**
     * @brief  Add data to the front of the %balance.
     * @param  x  Data to be added.
     * 
     * This is a typical stack operation.  The function creates an
     * element at the front of the %balance and assigns the given data to
     * it.  Due to the nature of a %balance this operation can be done
     * in constant time, and does not invalidate iterators and references.
     */
    void push_front(value_type const& x)
    {
        insert(begin(), x);
    }

    /**
     * @brief  Removes first element.
     * 
     * This is a typical stack operation.  It shrinks the %balance_tree by
     * one.  Due to the nature of a %balance this operation can be done
     * in constant time, and only invalidates iterators/references to
     * the element being removed.
     * 
     * Note that no data is returned, and if the first element's data
     * is needed, it should be retrieved before pop_front() is called.
     */
    void pop_front()
    {
        erase(begin());
    }

    /**
     * @brief  Add data to the end of the %balance.
     * @param  x  Data to be added.
     * 
     * This is a typical stack operation.  The function creates an
     * element at the end of the %balance and assigns the given data to
     * it.  Due to the nature of a %balance this operation can be done
     * in constant time, and does not invalidate iterators and references.
     */
    void push_back(value_type const& x)
    {
        insert(end(), x);
    }

    /**
     * @brief  Removes last element.
     * 
     * This is a typical stack operation.  It shrinks the %balance_tree by
     * one.  Due to the nature of a %balance this operation can be done
     * in constant time, and only invalidates iterators/references to
     * the element being removed.
     * 
     * Note that no data is returned, and if the last element's data
     * is needed, it should be retrieved before pop_back() is called.
     */
    void pop_back()
    {
    }
      
    /**
     * @brief        Inserts val in front of @a pos.
     * @param pos    The %balance iterator in front of which to insert.
     * @param val    The value to insert.
     * @return        An inorder iterator that points to the inserted data.
     */
    iterator insert(iterator pos, value_type const& val)
    {
        //TODO: we might need to go down in the hierarchy first
        // That means some redundant work if pos was yielded by upper_bound,
        // so maybe saving two cursors in the iterator would make sense
        // (one for deref, one for insert)
        
        // Then again... that's too much of a fuss. Maybe we should just
        // build a searcher that does all that.
        
        // Do balancers have to work for non-leaf newly inserted elements?
        // If yes, we could just insert at pos.
        
        cursor c = pos.base().base().base();
        //to_rightmost(c);
        
        c = h.insert(c, data_type(val));
        
        balancer_type::add(h, c);
        return iterator(c);
    }

    /**
     * @brief  Remove element at given position.
     * @param  position  Iterator pointing to element to be erased.
     * @return  An iterator pointing to the next element (or end()).
     * 
     * This function will erase the element at the given position and thus
     * shorten the %balance by one.
     * 
     * Due to the nature of a %balance this operation can be done in
     * constant time, and only invalidates iterators/references to
     * the element being removed.  The user is also cautioned that
     * this function only erases the element, and that if the element
     * is itself a pointer, the pointed-to memory is not touched in
     * any way.  Managing the pointer is the user's responsibilty.
     */
    iterator erase (iterator position)
     {
         cursor c = position.base().base();
         cursor d = balancer_type::remove(h, c);
//         if (c == d)
            return iterator(h.erase(c));
//        return iterator(h.erase(d,c));            
     }

    /**
     * @brief  Remove a range of elements.
     * @param  first  Iterator pointing to the first element to be erased.
     * @param  last  Iterator pointing to one past the last element to be
     *               erased.
     * @return  An iterator pointing to the element pointed to by @a last
     *          prior to erasing (or end()).
     * 
     * This function will erase the elements in the range @a
     * [first,last) and shorten the %balance accordingly.
     * Due to the nature of a %balance this operation can be done in
     * constant time, and only invalidates iterators/references to
     * the elements being removed.  The user is also cautioned that
     * this function only erases the elements, and that if the
     * elements themselves are pointers, the pointed-to memory is not
     * touched in any way.  Managing the pointers is the user's
     * responsibilty.
     */
     void erase (iterator a, iterator b)
     {
     }
     
    /**
     * @brief Clears all data from the tree.
     */
     void clear()
     {
         h.clear();
     }

    /**
     * Returns true if the %balance is empty.  (Thus begin() would
     * equal end().)
     */
    bool is_leaf() const
    {
        return h.is_leaf();
    }
    
    void rotate(iterator& i)
    {
        cursor c = cursor(boost::tree::iterator<inorder, cursor>(i));
        h.rotate(c);
    }
};


} // namespace tree
} // namespace boost

#endif // BOOST_TREE_balance_HPP
