
#ifndef POINT_R_H
#define POINT_R_H

struct Point {
    const void * _class;
    int x, y;               /* coordinates */
};

#define get_x(p) (((const struct Point *)(p))->x)
#define get_y(p) (((const struct Point *)(p))->y)

#define set_x(p,v) (((struct Point *)(p))->x = (v))
#define set_y(p,v) (((struct Point *)(p))->y = (v))

#endif