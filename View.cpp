//
// Created by USER on 6/19/2022.
//

#include "View.h"

View::View(int size) {
    if (size< 6 || size >30){
        throw exception();
    }
    this->zoom = 2;
    this->center = Point(0, size-1);

    for(int i=0; i < size; i++){
        for(int j=0 ; j<size; j++){
            plan[i][j] = ". ";
        }
    }
}

void View::default_args() {

}

void View::set_size(int size) {

}

void View::set_center(Point *p) {

}

void View::set_zoom(double z) {

}

void View::print() {

}
