// To detect the standard library we need to include a certain header first.
//
#if defined(__clang__)
#  if   __has_include(<__config>)         // libc++    _LIBCPP_VERSION
#    include <__config>
#  elif __has_include(<bits/c++config.h>) // libstdc++ __GLIBCXX__
#    include <bits/c++config.h>
#  endif
#elif defined(__GNUC__)
#  include <bits/c++config.h>             // libstdc++ __GLIBCXX__
#endif

#if !defined(_MSC_VER) && !defined(__GLIBCXX__) && !defined(_LIBCPP_VERSION)
#  error unknown standard library implementation
#endif
