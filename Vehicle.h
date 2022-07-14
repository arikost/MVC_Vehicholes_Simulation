//
// Created by USER on 6/19/2022.
//
#ifndef MVC_VEHICHOLES_SIMULATION_VEHICLE_H
#define MVC_VEHICHOLES_SIMULATION_VEHICLE_H
#include "Geometry.h"
#include "Warehouse.h"
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
enum state{stopped=1, parked, offRoad, movingTo};
struct track_timing{
    int hours;
    int minutes;
};
typedef struct track_Schedule{
    track_timing arrival_time;
    track_timing departure_time;
    int case_quantity;
}track_Schedule;

class Vehicle{
public:
    state state;
    Point currentPosition;
    virtual void moving_to_dest(Point point){} ;
    virtual void moving_on_course(double theta){} ;
    virtual void get_state(){};

};

class State_trooper: public Vehicle{
public:
    State_trooper(string & name, Point p){
        cout<<name<<"  created"<<endl;
    }
    void moving_on_course(double theta) override{}
    void moving_to_dest(Point point) override{}
    void get_state() override{}
};
class Chopper: public Vehicle{
public:
    Chopper(string & name){
        cout<<name<<"  created"<<endl;
    }
    void moving_to_dest(Point point) override{}
    void moving_on_course(double theta) override{}
    void get_state() override{}
};
class Track: public Vehicle{
public:
    Track(string &data_filename){
        cout<< data_filename<<"  created"<<endl;
//        ifstream inFile(data_filename);
//        string line;
//        if(inFile.is_open()) {
//            string warehouseName;
//            while (getline(inFile, line)) {
//                warehouseName.clear();
//                string::iterator line_iter = line.begin();
//                while(*line_iter != ','){ warehouseName.pusk_back(*line_iter++);}
//
//            }
//            inFile.close();
//        }
    }
    void moving_on_course(double theta) override{

    }
    void moving_to_dest(Point point) override{

    }
    void get_state() override{}
//private:
//    Point currentPosition;
//    string name;
//    Warehouse* dest;
//    map<shared_ptr< Warehouse*>, track_Schedule*> course_data;
};

class VehicleFactory{
public:
    Track * makeTrack(string  name){ return new Track(name);}
    Chopper * makeChopper(string  name){return new Chopper(name);}
    State_trooper * makeState_trooper(string  name, Point p){return new State_trooper(name, p);}
};




#endif //MVC_VEHICHOLES_SIMULATION_VEHICLE_H
