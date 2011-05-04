//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file unaugmented.hpp
 * Trivial augmentor (does nothing)
 */

#ifndef BOOST_TREE_AUGMENTORS_UNAUGMENTED_HPP
#define BOOST_TREE_AUGMENTORS_UNAUGMENTED_HPP

namespace boost {
namespace tree {
namespace augmentors {

/**
 * Trivial augmentor (does nothing)
 */
class unaugmented {
 public:
     struct metadata_type {};
 protected:
    template <class Tree>
     void pre_rotate(Tree&, typename Tree::cursor&)
     { }
     
     template <class Tree>
     void pre_detach(Tree&, typename Tree::cursor&)
     { }
     
     template <class Tree>
     void pre_detach(Tree&, typename Tree::cursor&, typename Tree::cursor&)
     { }
     
     template <class Tree>
     void descend(Tree&, typename Tree::cursor&)
     { }
};

} // namespace augmentors
} // namespace tree
} // namespace boost

#endif // BOOST_TREE_AUGMENTORS_UNAUGMENTED_HPP


