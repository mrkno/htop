#include "pwd.h"
#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h>
#include <lm.h>
#include <Secext.h>
/*
* The way to implement these function is discribed here ...
*  http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dnucmg/html/UCMGch09.asp
*/

/**
*
*/
static struct passwd current_user;

size_t
strlcpy(char *dst, const char *src, size_t dsize)
{
   const char *osrc = src;
   size_t nleft = dsize;

   /* Copy as many bytes as will fit. */
   if (nleft != 0) {
      while (--nleft != 0) {
         if ((*dst++ = *src++) == '\0')
            break;
      }
   }

   /* Not enough room in dst, add NUL and traverse rest of src. */
   if (nleft == 0) {
      if (dsize != 0)
         *dst = '\0';		/* NUL-terminate dst */
      while (*src++)
         ;
   }

   return(src - osrc - 1);	/* count does not include NUL */
}

//uid_t getuid(void)
//{
//   return 0;
//}

struct passwd *getpwuid(uid_t uid)
{
   LPTSTR lpszSystemInfo;          // pointer to system information string 
   TCHAR tchBuffer[MAX_PATH + 1];  // buffer for expanded string
   DWORD cchBuff = MAX_PATH + 1;    // size of user name

   lpszSystemInfo = tchBuffer;

   // Get and display the user name.
   GetUserName(lpszSystemInfo, &cchBuff);

   

   strlcpy(current_user.pw_name, lpszSystemInfo, MAX_PATH);
   strlcpy(current_user.pw_gecos, lpszSystemInfo, MAX_PATH);
   return     &current_user;
}

struct passwd* getpwnam(const char* username)
{
   return NULL;
}
