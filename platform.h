#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
#include <io.h>           // _access() �̂���
#define access  _access   // access �� Windows��_access
#ifndef F_OK
#define F_OK  0          // ���݊m�F�p�t���O
#endif
#else
#include <unistd.h>       // Unix�n�� access(), F_OK
#endif

#endif // PLATFORM_H
