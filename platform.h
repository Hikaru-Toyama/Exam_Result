#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
#include <io.h>           // _access() のため
#define access  _access   // access → Windows版_access
#ifndef F_OK
#define F_OK  0          // 存在確認用フラグ
#endif
#else
#include <unistd.h>       // Unix系の access(), F_OK
#endif

#endif // PLATFORM_H
