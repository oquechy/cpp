#include <stdio.h>

#include "../include/scheme.h"
#include "../include/rectangle.h"
#include "../include/circle.h"


int main() {
    Scheme scheme(10);

    scheme.push_back_figure(new Rectangle(1, 5, 5, 10, 10));
    scheme.push_back_figure(new Circle(2, 3, 3, 3, "very nice circle"));
    scheme.push_back_figure(new Rectangle(4, 7, 5, 1, 10));
    scheme.push_back_figure(new Circle(3, 300, 300, 3, "very nice circle2"));

    scheme.print_all_figures();

    Figure* found = scheme.is_inside_figure(300, 303);
    if (found != 0) {
        found->print();
    }
    else {
        printf("not found\n");
    }

    scheme.zoom_figure(1, 2);
    scheme.zoom_figure(2, 6);
    scheme.print_all_figures();
    scheme.remove_figure(1);
    scheme.move(3, 100, 100);
    scheme.print_all_figures();

    return 0;
}
