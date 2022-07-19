//
// Created by USER on 6/19/2022.
//

#include "Model.h"



Model *Model::ptr = nullptr;
Model &Model::get_Instance() {
    if (ptr == nullptr)
        ptr = new Model();
    return *ptr;
}
Model::Model() {
    addWarehouse(new Warehouse(Point(40,10), "Frankfurt",100000 ), "Frankfurt");
}

Vehicle * Model::getVehicle(const string & vehicle_name) {
    return _vehicleList[vehicle_name].get();
}

void Model::addVehicle(Point & starting_point , string & vehicle_name, string type) {
    if(type == "Track"){
        _vehicleList[type] = make_shared<Track>(*vf.makeTrack(vehicle_name,starting_point));
    }
    else if(type == "Chopper"){
        _vehicleList[type] = make_shared<Chopper>(*vf.makeChopper(starting_point, vehicle_name));
    }
    else if(type == "State_trooper"){
        _vehicleList[type] = make_shared<State_trooper>(*vf.makeState_trooper(starting_point, vehicle_name));
    }
}

Warehouse * Model::getWarehouse(const string & warehouse_name) {
    return _warehouseList[warehouse_name].get();
}

void Model::addWarehouse(Warehouse *warehouse, const string & name) {
    _warehouseList[name] = make_shared<Warehouse>(*warehouse);
}

void Model::advance() {
    time.hours++;
    for(auto & [key, value] : _vehicleList){
        if(key == "Track"){
            Track * track = (Track*) value.get();

        }
    }
}

string Model::get_entity_by_point(Point p) {
    for(auto & [key, value] : _vehicleList){
        if(p.x == value.get()->getCurrentPosition().x && p.y == value.get()->getCurrentPosition().y){
            return key.substr(0, 2);
        }
    }
    for(auto & [key, value] : _warehouseList){
        if(p.x == value.get()->getPosition().x && p.y == value.get()->getPosition().y){
            return key.substr(0, 2);
        }
    }
    return " .";
}

void Model::print_all_wh() {
    for(auto & [key, value] : _warehouseList){
        cout<< key<<"  ";
        value.get()->getPosition().print();
        cout<<endl;
    }

}

