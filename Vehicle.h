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

    virtual void moving_to_dest(Point point) = 0;
    virtual void moving_on_course(double theta) = 0;
    virtual void get_state() = 0;
    Point & getCurrentPosition(){
        return currentPosition;
    }

    Cartesian_vector destination;
    Polar_vector pv;
    state state;
    Point currentPosition;
};

class State_trooper: public Vehicle{
public:
    State_trooper(Point &starting_point, string & name){

    }
    void moving_to_dest(Point point){

    }
    void moving_on_course(double theta){

    }
    void get_state() override{

    }
};
class Chopper: public Vehicle{
public:
    Chopper(Point &starting_point, string & name){
    }
    void moving_to_dest(Point point){

    }
    void moving_on_course(double theta){

    }
    void get_state() override{

    }
};
class Track: public Vehicle{
protected:
    typedef struct track_dataNode{

        time_hm arrival_time = time_hm();
        time_hm departure_time = time_hm();
        string whName;
        int case_quantity;
    }track_dataNode;
    vector<track_dataNode> _trackCourse_data;
    __gnu_cxx::__normal_iterator<track_dataNode *, vector<track_dataNode>> currentDataNode;
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
            string::iterator buff_iter = buff.begin();
            for(param_num; param_num < 4; param_num++) {
                token.clear();
                while (*buff_iter != ',' && buff_iter != buff.end()) {
                    token.push_back(*buff_iter++);
                }
                if(buff_iter != buff.end())
                    buff_iter++;
                switch(param_num){
                    case 0:
                        trackDataNode.whName = token;
                        break;
                    case 1:
                        if(_trackCourse_data.empty()){
                            break;
                        }
                        trackDataNode.arrival_time.hours = stoi(token.substr(0,2));
                        trackDataNode.arrival_time.minutes = stoi(token.substr(3,4));
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
                        trackDataNode.departure_time.hours = stoi(token.substr(0,2));
                        trackDataNode.departure_time.minutes = stoi(token.substr(3,4));
                        break;
                }
            }
            _trackCourse_data.push_back(trackDataNode);
        }data_file_obj.close();
        currentDataNode = _trackCourse_data.begin();
    }
    void moving_to_dest(Point point){

    }
    void moving_on_course(double theta){

    }
    void get_state() {

    }
    track_dataNode & get_dataNode(){
        return *currentDataNode;
    }
};

class VehicleFactory{
public:
    Track * makeTrack(string  data_filename, Point & starting_point){ return new Track(data_filename, starting_point);}
    Chopper * makeChopper(Point & starting_point, string & name){return new Chopper(starting_point, name);}
    State_trooper * makeState_trooper(Point & starting_point, string & name){return new State_trooper(starting_point, name);}
};




#endif //MVC_VEHICHOLES_SIMULATION_VEHICLE_H
