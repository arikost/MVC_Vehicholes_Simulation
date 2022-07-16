//
// Created by USER on 6/19/2022.
//
#ifndef MVC_VEHICHOLES_SIMULATION_VEHICLE_H
#define MVC_VEHICHOLES_SIMULATION_VEHICLE_H
#include "Geometry.h"
#include "Warehouse.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include "MyExceptions.h"


enum state{stopped=1, parked, offRoad, movingTo};

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
    Track(string &data_filename, Point & starting_point){
        currentPosition = starting_point;
        ifstream data_file_obj(data_filename);
        if(!data_file_obj.is_open()){
            throw MyExceptions("failed to open "+data_filename);
        }
        string buff, token;
        int param_num;
        while(data_file_obj.peek() != EOF){
            data_file_obj >> buff;
            param_num = 0;
            track_dataNode trackDataNode;
            time_hm t;
            string::iterator buff_iter = buff.begin();
            for(param_num; param_num < 4; param_num++) {
                token.clear();
                while (*buff_iter != ',' && buff_iter != buff.end()) {
                    token.push_back(*buff_iter++);
                }
                buff_iter++;
                switch(param_num){
                    case 0:
                        trackDataNode.whName = token;
                        break;
                    case 1:
                        t.hours = stoi(token.substr(0,2));
                        t.minutes = stoi(token.substr(3,4));
                        trackDataNode.departure_time = t;
                        break;
                    case 2:
                        if(_trackCourse_data.empty()){
                            trackDataNode.case_quantity = 0;
                        }
                        else {
                            trackDataNode.case_quantity = stoi(token);
                        }
                        break;
                    case 3:
                        if(_trackCourse_data.empty()){
                            break;
                        }
                        t.hours = stoi(token.substr(0,2));
                        t.minutes = stoi(token.substr(3,4));
                        trackDataNode.arrival_time = t;
                        break;
                }
            }
            _trackCourse_data.push_back(trackDataNode);
        }data_file_obj.close();
    }
    void moving_on_course(double theta) override{

    }
    void moving_to_dest(Point point) override{

    }
    void get_state() override{}

protected:
    typedef struct track_dataNode{
        time_hm arrival_time;
        time_hm departure_time;
        string whName;
        int case_quantity;

    }track_dataNode;
    vector<track_dataNode> _trackCourse_data;

};

class VehicleFactory{
public:
    Track * makeTrack(string  name, Point & starting_point){ return new Track(name, starting_point);}
    Chopper * makeChopper(string  name){return new Chopper(name);}
    State_trooper * makeState_trooper(string  name, Point p){return new State_trooper(name, p);}
};




#endif //MVC_VEHICHOLES_SIMULATION_VEHICLE_H
