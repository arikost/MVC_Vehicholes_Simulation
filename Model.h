//
// Created by USER on 6/19/2022.
//
#include <map>
#include <memory>
#ifndef MVC_VEHICHOLES_SIMULATION_MODEL_H
#define MVC_VEHICHOLES_SIMULATION_MODEL_H
#include "Vehicle.h"
#include "Warehouse.h"


class Model {
public:
    static Model & get_Instance();

    Vehicle* getVehicle(const string&);
    void addVehicle(Vehicle*, const string&);

    Warehouse* getWarehouse(const string&);
    void addWarehouse(Warehouse*, const string&);

    void advance();


    Model(const Model&) = delete;
    Model& operator= (const Model&) = delete;
    Model(Model&&) = delete;
    Model& operator= (Model&&) = delete;
private:
    Model();
    static Model* ptr;
    map<string, shared_ptr<Vehicle>> _vehicleList;
    map<string, shared_ptr<Warehouse>> _warehouseList;
};


#endif //MVC_VEHICHOLES_SIMULATION_MODEL_H