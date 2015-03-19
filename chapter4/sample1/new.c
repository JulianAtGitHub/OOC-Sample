
#include <assert.h>
#include <stdlib.h>

#include "new_r.h"
#include "new.h"

void * alloc(const void * _class, ...) {
    const struct Class * desc = _class;
    void * p = calloc(1, desc->size);

    assert(p);
    * (const struct Class **) p = desc;

    if (desc->ctor) {
        va_list ap;
        va_start(ap, _class);
        p = desc->ctor(p, &ap);
        va_end(ap);
    }
    return p;
}

void dealloc (void * self) {
    const struct Class ** cp = self;
    if (self && * cp && (* cp)->dtor)
        self = (* cp)->dtor(self);
    free(self);
}

void draw (const void * self) {
    const struct Class * const * cp = self;

    assert(self && * cp && (* cp)->draw);
    (* cp)->draw(self);
}