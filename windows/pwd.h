#pragma once

#ifndef _PWD_H_
#define	_PWD_H_

#include <sys/types.h>
#include <windows.h>
/*
* Definitions of uid_t and getuid is the one found in the cygwin <sys/types.h>
*/
typedef unsigned short uid_t;
//uid_t   getuid(void);

/*
* The passwd struct is not completly redefined,
* only the fields used by GRISBI are declared
*/
struct passwd {
   char pw_name[MAX_PATH];		/* user name */
   char pw_gecos[MAX_PATH];		/* Honeywell login info */
   int pw_uid;
};

struct passwd* getpwuid(uid_t);
struct passwd* getpwnam(const char*);

#endif
