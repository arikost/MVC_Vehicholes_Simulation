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
#include <valarray>
#include "MyExceptions.h"


enum state{stopped=1, parked, offRoad, movingTo};
enum movement_type{onCourse=1, toDest, toPosition};
enum v_type{Cho, Sta, Tra}; // types of vehicles
class Chopper;
class Track;
class State_trooper;
class Vehicle{
public:
    /**
     * Vehicle is an abstract class
     * with parameter v_type to determent how to cast
     * an object from an inheriting class**/
    virtual void moving_to_dest(Point point) = 0;
    virtual void moving_on_course(double theta) = 0;
    virtual void get_state() = 0;
    /**parameters**/
    v_type type;
    string name;
    Cartesian_vector cv;
    Polar_vector pv;
    double speed;
    state state;
    movement_type movement;
    Point destination;
    Point currentPosition;
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
    int courser;
public:
    int inventory;
    Track(string &data_filename, Point & starting_point, string & name){
        this->name = name;
        currentPosition = starting_point;
        type = Tra;
        inventory = 105;
        state = parked;
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
                            trackDataNode.departure_time.hours = stoi(token.substr(0,2));
                            trackDataNode.departure_time.minutes = stoi(token.substr(3,4));
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
                        if(_trackCourse_data.empty()){
                            break;
                        }
                        trackDataNode.departure_time.hours = stoi(token.substr(0,2));
                        trackDataNode.departure_time.minutes = stoi(token.substr(3,4));
                        break;
                }
            }
            _trackCourse_data.push_back(trackDataNode);
        }data_file_obj.close();
        courser = 0;
    }
    void moving_to_dest(Point point){
        destination = point;
        cv.delta_x =  destination.x - currentPosition.x;
        cv.delta_y =  destination.y - currentPosition.y;
        pv = cv;
        speed = pv.r / (_trackCourse_data[courser].arrival_time - _trackCourse_data[courser - 1].departure_time);
    }
    void moving_on_course(double theta){

    }
    void get_state() {
        cout << "at position ";
        currentPosition.print();
        switch (state) {
            case parked:
                cout << ", parking in "<<get_dataNode().whName;
                break;
            case movingTo:
                cout << ", heading to "<<get_dataNode().whName;
                break;
            case offRoad:
                cout << ", was robbed";
                break;
            case stopped:
                cout << ", was stopped";
                break;
        }
        cout << ", Carts: "<< inventory;
    }
    track_dataNode & get_dataNode(){
        return _trackCourse_data[courser];
    }
    void dataNodeNext(){
        if(courser <= _trackCourse_data.size())
            courser++;
        else
            state = stopped;
    }
};

class Chopper: public Vehicle{
public:
    int attacking_range;
    bool attacking_mod;
    Track * target;
    Chopper(Point &starting_point, string & name){
        this->name = name;
        this->type = Cho;
        currentPosition = starting_point;
        state = parked;
        attacking_range = 2;
        attacking_mod = false;
    }
    void moving_to_dest(Point point){
        destination = point;
        cv.delta_x =  destination.x - currentPosition.x;
        cv.delta_y =  destination.y - currentPosition.y;
        pv = cv;
        state = movingTo;
    }
    void moving_on_course(double theta){
        pv.theta = theta;
        state = movingTo;
        movement = onCourse;
    }
    void get_state() override{
        cout << "at position ";
        currentPosition.print();
        switch (state) {
            case movingTo:
                switch (movement) {
                    case toPosition:
                        cout << ", heading to position: ";
                        destination.print();
                        break;
                    case onCourse:
                        cout << ", heading on course "<<setprecision(2) << fixed << to_degrees(pv.theta);
                        break;
                }
                break;
            case stopped:
                cout << ", was stopped";
                break;
        }
        cout << ", speed: "<<setprecision(2)<<fixed<<(speed*100)<<" km/h";
        cout << ", attacking range: "<< attacking_range;
    }
    void set_target(Track *track){
        target = track;
        attacking_mod = true;
    }
    double getDistFromDest() {
        return currentPosition.getDistance(destination);
    }
    void attack(bool flag){
        state = stopped;
        currentPosition = target->currentPosition;
        if(flag) {
            cout<< name<<" robbed "<<target->name<<" successfully\n";
            target->state = offRoad;
            target->inventory = 0;
            attacking_range++;
        }else {
            cout << name << " failed to robb " << target->name << endl;
            attacking_range--;
        }
    }
};

class State_trooper: public Vehicle{
public:
    vector<string> visitedWH;
    string nextWh;
    State_trooper(Point &starting_point, string & name){
        this->name = name;
        this->type = Sta;
        currentPosition = starting_point;
        state = parked;
        speed = 0.9 ;
    }
    void moving_to_dest(Point point){
        destination = point;
        cv.delta_x =  destination.x - currentPosition.x;
        cv.delta_y =  destination.y - currentPosition.y;
        pv = cv;
        state = movingTo;
    }
    void moving_on_course(double theta){
        pv.theta = theta;
        pv.r = 1;
        cv = pv;
        movement = onCourse;
        state = movingTo;
    }
    void get_state() override{
        cout << "at position ";
        currentPosition.print();
        switch (state) {
            case movingTo:
                switch (movement) {
                    case toDest:
                        cout << ", heading to destination: "<<nextWh;
                        break;
                    case onCourse:
                        cout << ", heading on course "<<setprecision(2) << fixed << to_degrees(pv.theta);
                        break;
                    case toPosition:
                        cout << ", heading to position: ";
                        destination.print();
                        break;
                }
            case stopped:
                cout << ", was stopped";
                break;
        }
        cout << ", speed: "<<setprecision(2)<<fixed<<(speed*100)<<" km/h";
    }
    double getDistFromDest() {
        return currentPosition.getDistance(destination);
    }
};

class VehicleFactory{
public:
    Track * makeTrack(string  data_filename, Point & starting_point, string & name){ return new Track(data_filename, starting_point,name);}
    Chopper * makeChopper(Point & starting_point, string & name){return new Chopper(starting_point,name);}
    State_trooper * makeState_trooper(Point & starting_point, string & name){return new State_trooper(starting_point, name);}
};




#endif //MVC_VEHICHOLES_SIMULATION_VEHICLE_H
