#include <cctype>
#include <cwctype>
#include <locale>
#include <clocale>

#include <cctype>
#include <iosfwd>
#include <iomanip>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>

#ifdef __GLIBCXX__
// Contents of <iostream> without static __ioinit.
namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION
  extern istream cin;
  extern ostream cout;
  extern ostream cerr;
  extern ostream clog;

  static inline ios_base::Init __ioinit;
_GLIBCXX_END_NAMESPACE_VERSION
}
#else
#include <iostream>
#endif
