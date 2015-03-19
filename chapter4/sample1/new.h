
#ifndef NEW_H
#define NEW_H

void * alloc (const void * _class, ...);
void dealloc (void * item);
void draw (const void * self);

#endif