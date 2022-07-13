//
// Created by USER on 6/19/2022.
//
#include "Geometry.h"
#ifndef MVC_VEHICHOLES_SIMULATION_VIEW_H
#define MVC_VEHICHOLES_SIMULATION_VIEW_H
#define MAX_SIZE 30
#define MIN_SIZE 6
#include "Model.h"

class View {
public:
    View(int size=25);
    void default_args();
    void set_size(int size);
    void set_center(Point* p);
    void set_zoom(double z);
    void print();

private:
    string** plan;
    Point center;
    double zoom;
};


#endif //MVC_VEHICHOLES_SIMULATION_VIEW_H
