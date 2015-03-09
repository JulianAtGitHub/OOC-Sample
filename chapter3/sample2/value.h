
#ifndef VALUE_H
#define VALUE_H

extern const void * Number;
extern const void * Positive;
extern const void * Nagetive;
extern const void * Add;
extern const void * Sub;
extern const void * Mult;
extern const void * Div;

void * alloc (const void * type, ...);
void dealloc (void * tree);
void process (const void * tree);

#endif