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

Vehicle *Model::getVehicle(const string & vehicle_name) {
    return _vehicleList[vehicle_name].get();
}

void Model::addVehicle(Vehicle * vehicle, const string & vehicle_name) {

    _vehicleList[vehicle_name] = make_shared<Vehicle>(*vehicle);
}

Warehouse *Model::getWarehouse(const string & warehouse_name) {
    return _warehouseList[warehouse_name].get();
}

void Model::addWarehouse(Warehouse *warehouse, const string & name) {
    _warehouseList[name] = make_shared<Warehouse>(*warehouse);
}

void Model::advance() {

}
