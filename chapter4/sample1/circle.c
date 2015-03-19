
#include <stdarg.h>
#include <stdio.h>

#include "new_r.h"
#include "point.h"
#include "point_r.h"
#include "circle_r.h"
#include "circle.h"

static void * Circle_ctor (void * _self, va_list * app) {
    struct Circle * self = ((const struct Class *) Point)->ctor(_self, app);
    self->rad = va_arg(* app, int);
    return self;
}

static void Circle_draw (const void * _self) {
    const struct Circle * self = _self;
    printf("circle at %d,%d rad %d\n", get_x(self), get_y(self), self->rad);
}

static const struct Class _Circle = {
    sizeof(struct Circle),
    Circle_ctor,
    0,
    Circle_draw
};

const void * Circle = &_Circle;