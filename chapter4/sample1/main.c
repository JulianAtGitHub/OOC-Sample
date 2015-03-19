
#include "point.h"
#include "circle.h"
#include "new.h"

int main (int argc, char ** argv) {
    void * p;

    while ( * (++ argv)) {
        switch (** argv) {
            case 'p':
                p = alloc(Point, 1, 2);
                break;
            case 'c':
                p = alloc(Circle, 1, 2, 3);
                break;
            default:
                continue;
        }

        draw(p);
        move(p, 10, 20);
        draw(p);
        dealloc(p);
    }

    return 0;
}