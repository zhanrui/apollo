/*
 |    FileName: basetype.h
 | Description: base types definition
 |
 */
#ifndef _BASETYPE_H_
#define _BASETYPE_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

#define CHAR char
#define UCHAR unsigned char

#define SHORT short
#define USHORT unsigned short

#define INT int
#define UINT unsigned int

#define LONG long
#define ULONG unsigned long

#define VOID void

#define BOOL_T USHORT
#define BOOL_TRUE ((USHORT)1)
#define BOOL_FALSE ((USHORT)0)

#ifndef NULL
#define NULL ((VOID *)0)
#endif

#ifndef STATIC
#ifdef __DEBUG
#define STATIC
#else
#define STATIC static
#endif
#endif

__END_DECLS
#endif
