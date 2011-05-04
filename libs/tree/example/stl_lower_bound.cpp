//  Copyright (c) 2006-2009, Bernhard Reiter
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <algorithm>
#include <cassert>

int main() {
//[ stl_lower_bound_example
    std::vector<int> v(1, 1066); // c contains one element: 1066
    std::vector<int>::const_iterator ci996  = std::lower_bound(v.begin(), v.end(),  996);
    std::vector<int>::const_iterator ci1066 = std::lower_bound(v.begin(), v.end(), 1066);
    std::vector<int>::const_iterator ci2006 = std::lower_bound(v.begin(), v.end(), 2006);

    assert(ci996  == v.begin());
    assert(ci1066 == v.begin());
    assert(ci2006 == v.end());
//]
    return 0;
}
