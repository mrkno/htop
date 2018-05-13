/*
htop - StringUtils.c
(C) 2004-2011 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include "StringUtils.h"
#include "XAlloc.h"

#include "config.h"

#include <string.h>
#include <strings.h>
#include <stdlib.h>

/*{
#include <stdio.h>

#define String_startsWith(s, match) (strncmp((s),(match),strlen(match)) == 0)
#define String_contains_i(s1, s2) (strcasestr(s1, s2) != NULL)
}*/

/*
 * String_startsWith gives better performance if strlen(match) can be computed
 * at compile time (e.g. when they are immutable string literals). :)
 */

char* String_cat(const char* s1, const char* s2) {
   size_t l1 = strlen(s1);
   size_t l2 = strlen(s2);
   char* out = xMalloc(l1 + l2 + 1);
   strncpy(out, s1, l1);
   strncpy(out + l1, s2, l2 + 1);
   return out;
}

char* String_trim(const char* in) {
   while (in[0] == ' ' || in[0] == '\t' || in[0] == '\n') {
      in++;
   }
   size_t len = strlen(in);
   while (len > 0 && (in[len-1] == ' ' || in[len-1] == '\t' || in[len-1] == '\n')) {
      len--;
   }
   char* out = xMalloc(len+1);
   strncpy(out, in, len);
   out[len] = '\0';
   return out;
}

inline int String_eq(const char* s1, const char* s2) {
   if (s1 == NULL || s2 == NULL) {
      if (s1 == NULL && s2 == NULL)
         return 1;
      else
         return 0;
   }
   return (strcmp(s1, s2) == 0);
}

char** String_split(const char* s, char sep, int* n) {
   *n = 0;
   const int rate = 10;
   char** out = xCalloc(rate, sizeof(char*));
   int ctr = 0;
   int blocks = rate;
   char* where;
   while ((where = strchr(s, sep)) != NULL) {
      int size = where - s;
      char* token = xMalloc(size + 1);
      strncpy(token, s, size);
      token[size] = '\0';
      out[ctr] = token;
      ctr++;
      if (ctr == blocks) {
         blocks += rate;
         out = (char**) xRealloc(out, sizeof(char*) * blocks);
      }
      s += size + 1;
   }
   if (s[0] != '\0') {
      size_t size = strlen(s);
      char* token = xMalloc(size + 1);
      strncpy(token, s, size + 1);
      out[ctr] = token;
      ctr++;
   }
   out = xRealloc(out, sizeof(char*) * (ctr + 1));
   out[ctr] = NULL;
   *n = ctr;
   return out;
}

void String_freeArray(char** s) {
   if (!s) {
      return;
   }
   for (int i = 0; s[i] != NULL; i++) {
      free(s[i]);
   }
   free(s);
}

char* String_getToken(const char* line, const unsigned short int numMatch) {
   const unsigned short int len = strlen(line);
   char inWord = 0;
   unsigned short int count = 0;
   char match[50];

   unsigned short int foundCount = 0;

   for (unsigned short int i = 0; i < len; i++) {
      char lastState = inWord;
      inWord = line[i] == ' ' ? 0:1;

      if (lastState == 0 && inWord == 1)
         count++;
    
      if(inWord == 1){
         if (count == numMatch && line[i] != ' ' && line[i] != '\0' && line[i] != '\n' && line[i] != (char)EOF) {
            match[foundCount] = line[i];
            foundCount++;
         }
      }
   }

   match[foundCount] = '\0';
   return((char*)xStrdup(match));
}

char* String_readLine(FILE* fd) {
   const int step = 1024;
   int bufSize = step;
   char* buffer = xMalloc(step + 1);
   char* at = buffer;
   for (;;) {
      char* ok = fgets(at, step + 1, fd);
      if (!ok) {
         free(buffer);
         return NULL;
      }
      char* newLine = strrchr(at, '\n');
      if (newLine) {
         *newLine = '\0';
         return buffer;
      } else {
         if (feof(fd)) {
            return buffer;
         }
      }
      bufSize += step;
      buffer = xRealloc(buffer, bufSize + 1);
      at = buffer + bufSize - step;
   }
}

#ifdef _WIN32

static const unsigned char charmap[] = {
   '\000', '\001', '\002', '\003', '\004', '\005', '\006', '\007',
   '\010', '\011', '\012', '\013', '\014', '\015', '\016', '\017',
   '\020', '\021', '\022', '\023', '\024', '\025', '\026', '\027',
   '\030', '\031', '\032', '\033', '\034', '\035', '\036', '\037',
   '\040', '\041', '\042', '\043', '\044', '\045', '\046', '\047',
   '\050', '\051', '\052', '\053', '\054', '\055', '\056', '\057',
   '\060', '\061', '\062', '\063', '\064', '\065', '\066', '\067',
   '\070', '\071', '\072', '\073', '\074', '\075', '\076', '\077',
   '\100', '\141', '\142', '\143', '\144', '\145', '\146', '\147',
   '\150', '\151', '\152', '\153', '\154', '\155', '\156', '\157',
   '\160', '\161', '\162', '\163', '\164', '\165', '\166', '\167',
   '\170', '\171', '\172', '\133', '\134', '\135', '\136', '\137',
   '\140', '\141', '\142', '\143', '\144', '\145', '\146', '\147',
   '\150', '\151', '\152', '\153', '\154', '\155', '\156', '\157',
   '\160', '\161', '\162', '\163', '\164', '\165', '\166', '\167',
   '\170', '\171', '\172', '\173', '\174', '\175', '\176', '\177',
   '\200', '\201', '\202', '\203', '\204', '\205', '\206', '\207',
   '\210', '\211', '\212', '\213', '\214', '\215', '\216', '\217',
   '\220', '\221', '\222', '\223', '\224', '\225', '\226', '\227',
   '\230', '\231', '\232', '\233', '\234', '\235', '\236', '\237',
   '\240', '\241', '\242', '\243', '\244', '\245', '\246', '\247',
   '\250', '\251', '\252', '\253', '\254', '\255', '\256', '\257',
   '\260', '\261', '\262', '\263', '\264', '\265', '\266', '\267',
   '\270', '\271', '\272', '\273', '\274', '\275', '\276', '\277',
   '\300', '\341', '\342', '\343', '\344', '\345', '\346', '\347',
   '\350', '\351', '\352', '\353', '\354', '\355', '\356', '\357',
   '\360', '\361', '\362', '\363', '\364', '\365', '\366', '\367',
   '\370', '\371', '\372', '\333', '\334', '\335', '\336', '\337',
   '\340', '\341', '\342', '\343', '\344', '\345', '\346', '\347',
   '\350', '\351', '\352', '\353', '\354', '\355', '\356', '\357',
   '\360', '\361', '\362', '\363', '\364', '\365', '\366', '\367',
   '\370', '\371', '\372', '\373', '\374', '\375', '\376', '\377',
};

int strncasecmp(const char *s1, const char *s2, register size_t n) {
   register unsigned char u1, u2;
   for (; n != 0; --n) {
      u1 = (unsigned char)*s1++;
      u2 = (unsigned char)*s2++;
      if (charmap[u1] != charmap[u2]) {
         return charmap[u1] - charmap[u2];
      }
      if (u1 == '\0') {
         return 0;
      }
   }
   return 0;
}

char* strcasestr(const char *s, const char *find) {
   char c, sc;
   size_t len;
   if ((c = *find++) != 0) {
      c = (char)tolower((unsigned char)c);
      len = strlen(find);
      do {
         do {
            if ((sc = *s++) == 0)
               return (NULL);
         } while ((char)tolower((unsigned char)sc) != c);
      } while (strncasecmp(s, find, len) != 0);
      s--;
   }
   return ((char *)s);
}

#endif
