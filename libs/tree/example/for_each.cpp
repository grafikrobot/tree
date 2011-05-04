//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/tree/binary_tree.hpp>
//[ for_each_include_algorithm
#include <boost/tree/algorithm.hpp>
//]

#include <iostream>

#include "../test/binary_tree_test_data.hpp"

using namespace boost::tree;

//[ for_each_example
void to_cout(int i) {
    std::cout << ' ' << i;
    return;
}

int main() {
    binary_tree<int> bt;
    
    // Fill it with data...
    test_binary_tree_fixture<int>::create_test_dataset1_tree(bt);

    std::cout << "Preorder:";
    for_each(preorder(), bt.root(), to_cout);
    
    std::cout << std::endl << "Inorder:";
    for_each(inorder(), bt.root(), to_cout);
    
    std::cout << std::endl << "Postorder:";
    for_each(postorder(), bt.root(), to_cout);

    return 0;
}
//]