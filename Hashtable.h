/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_Hashtable
#define HEADER_Hashtable
/*
htop - Hashtable.h
(C) 2004-2011 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include <stdbool.h>

typedef struct Hashtable_ Hashtable;

typedef void(*Hashtable_PairFunction)(int, void*, void*);

typedef struct HashtableItem {
   unsigned int key;
   void* value;
   struct HashtableItem* next;
} HashtableItem;

struct Hashtable_ {
   int size;
   HashtableItem** buckets;
   int items;
   bool owner;
};

#if defined DEBUG || defined _WIN32

int Hashtable_count(Hashtable* this);

#endif

Hashtable* Hashtable_new(int size, bool owner);

void Hashtable_delete(Hashtable* this);

void Hashtable_put(Hashtable* this, unsigned int key, void* value);

void* Hashtable_remove(Hashtable* this, unsigned int key);

extern void* Hashtable_get(Hashtable* this, unsigned int key);

void Hashtable_foreach(Hashtable* this, Hashtable_PairFunction f, void* userData);

#endif
