#include "../include/scheme.h"

Scheme::Scheme(int capacity) {
    figures_ = new Figure*[capacity];
    size_ = 0;
}

Scheme::~Scheme() {
    for(int i = 0; i < size_; ++i)
        delete figures_[i];
    delete [] figures_;
}

void Scheme::push_back_figure(Figure* fg) {
    figures_[size_++] = fg;
}

void Scheme::remove_figure(int id) {
    int i = 0;
    while ( i < size_ && figures_[i]->get_id() != id) ++i;
    if(i < size_)
        delete figures_[i];
    for (; i + 1 < size_; ++i)
        figures_[i] = figures_[i + 1];
    --size_;
} // элементы смещаются влево

void Scheme::print_all_figures() {
    for(int i = 0; i < size_; ++i)
        figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
    for(int i = 0; i < size_; ++i)
        if (figures_[i]->get_id() == id){
            figures_[i]->zoom(factor);
            break;
        }
}

Figure* Scheme::is_inside_figure(int x, int y){
    for(int i = 0; i < size_; ++i)
        if (figures_[i]->is_inside(x, y))
            return figures_[i];
    return 0;
} // если внутри нескольких фигур, то возвращается любая из них

void Scheme::move(int id, int new_x, int new_y) {
    for(int i = 0; i < size_; ++i)
        if (figures_[i]->get_id() == id)
            figures_[i]->move(new_x, new_y);
}
