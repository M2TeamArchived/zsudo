///
#ifndef ZSUDO_HPP
#define ZSUDO_HPP
#if defined(__has_include)
#if __has_include(<zsudoversion.h>)
#include <zsudoversion.h>
#endif
#endif
#include <string>

#ifndef ZSUDO_VERSION
#define ZSUDO_VERSION L"1.0"
#endif

#ifndef ZSUDO_HASH
#define ZSUDO_HASH L"none"
#endif

#ifndef ZSUDO_REFS
#define ZSUDO_REFS L"none"
#endif

#ifndef ZSUDO_APPNAME
#define ZSUDO_APPNAME L"zsudo-1.0.0"
#endif

namespace zsudo {
//
inline std::wstring zsudo_version() {
  // todo
  return ZSUDO_APPNAME;
}
} // namespace zsudo

#endif