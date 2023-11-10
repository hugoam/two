#ifdef __GLIBCXX__
// These are defined in <bits/c++config.h> which we have pre-included.
namespace std
{
typedef __SIZE_TYPE__         size_t;
typedef __PTRDIFF_TYPE__      ptrdiff_t;
typedef decltype(nullptr)     nullptr_t;
}
#endif

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include <utility>
#include <type_traits>

#include <exception>
#include <stdexcept>
#include <system_error>

#include <new>
#include <memory>

#include <limits>
#include <ctime>
#include <atomic>
#include <chrono>
#include <bitset>
#include <cmath>


#include <iterator>
#include <algorithm>
#include <functional>

#include <string>
#include <cstring> // @@ Not in the proposal.

#include <array>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <forward_list>
#include <stack>

#include <random>