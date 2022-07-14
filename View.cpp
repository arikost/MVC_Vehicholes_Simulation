//
// Created by USER on 6/19/2022.
//

#include "View.h"

View::View(int size) {
    if (size< 6 || size >30){
        throw exception();
    }
    this->size = size;
    this->zoom = 2;
    this->center = Point(-10, -10);
}

void View::default_args() {
    this->size = 25;
    this->center.x = -10;
    this->center.y = -10;
    this->zoom = 2;
}

void View::set_size(int size) {
    if (size< 6 || size >30){
        throw exception();
    }
    this->size = size;
}

void View::set_center(Point p) {
    this->center.x = p.x;
    this->center.y = p.y;
}

void View::set_zoom(double z) {
    this->zoom = z;
}

void View::show() {
    Model &model = Model::get_Instance();
    Point p;
    for(int i = size-1; i>=0; i--){
        if (i == (size-1)%3){
            if(0<=(center.y + (i*zoom)) < 10){
                cout<<" "<< center.y + (i*zoom) ;
            }
            else{
                cout<< center.y + (i*zoom);
            }
        }
        else{
            cout<<"  ";
        }
        for(int j = size-1; j>=0; j--){
            p.y = center.y + (i*zoom);
            p.x = center.x + (j*zoom);
            cout<< model.get_entity_by_point(p);
        }
        cout<< endl;
    }
    for(int i = size-1; i>=0 ; i--){
        if (i == (size-1)%3){
            if(0<=(center.x + (i*zoom)) < 10){
                cout<<" "<< center.x + (i*zoom) ;
            }
            else{
                cout<< center.x + (i*zoom);
            }
        }
        else{
            cout<<"  ";
        }
    }
    cout<< endl;
}

