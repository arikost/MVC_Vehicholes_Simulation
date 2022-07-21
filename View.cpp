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
        if (i % 3 == (size-1)%3){
            if(0<=(center.y + (i*zoom)) && (center.y + (i*zoom))  < 10){
                cout<<"  "<< (int)(center.y + (i*zoom));
            }
            else if((center.y + (i*zoom))  <= -10 || (center.y + (i*zoom)) >= 100){
                cout<< (int)(center.y + (i*zoom));
            }
            else{
                cout<<" "<< (int)(center.y + (i*zoom)) ;
            }
        }
        else{
            cout<<"   ";
        }
        p.y = center.y + (i*zoom);
        for(int j = 0; j < size  ; j++){
            p.x = center.x + (j*zoom);
            cout<< model.get_entity_by_point(p, zoom).substr(0, 2);
        }
        cout<< endl;
    }
    cout<< "  ";
    for(int i = 0; i < size ; i++){
        if (i % 3 == (size-1)%3){
            if(0<=(center.x + (i*zoom)) && (center.x + (i*zoom)) < 10){
                cout<<" "<< (int)(center.y + (i*zoom)) ;
            }
            else{
                cout<< (int)(center.y + (i*zoom));
            }
        }
        else{
            cout<<"  ";
        }
    }
    cout<< endl;
}

