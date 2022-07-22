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
    string fran = "Frankfurt";
    addWarehouse(new Warehouse(Point(40,10), "Frankfurt",100000 ),  "Frankfurt");
}

Vehicle * Model::getVehicle( string & vehicle_name) {
    if(_vehicleList.find(vehicle_name) != _vehicleList.end())
        return _vehicleList[vehicle_name].get();
    else
        return NULL;
}

void Model::addVehicle(Point & starting_point , string & vehicle_name,string &wareHouse, string type) {
    if(_vehicleList.count(vehicle_name) != 0){
        cerr<<"Error:: vehicle "<< vehicle_name<< " exists\n";
    }
    else if(type == "Track"){
        string track_name = vehicle_name.substr(0,vehicle_name.find('.'));
        _vehicleList[track_name] = make_shared<Track>(*vf.makeTrack(vehicle_name, starting_point, track_name));
    }
    else if(type == "Chopper"){
        _vehicleList[vehicle_name] = make_shared<Chopper>(*vf.makeChopper(starting_point, vehicle_name));
    }
    else if(type == "State_trooper"){
        Warehouse *wh = getWarehouse(wareHouse);
        if(wh == NULL){
            throw MyExceptions("warehouse doesn't exist:: "+wareHouse);
        }
        starting_point.x = wh->getPosition().x;
        starting_point.y = wh->getPosition().y;
        _vehicleList[vehicle_name] = make_shared<State_trooper>(*vf.makeState_trooper(starting_point,vehicle_name));
        State_trooper * st = (State_trooper*) _vehicleList[vehicle_name].get();
        st->visitedWH.push_back(wareHouse);
    }
}

Warehouse * Model::getWarehouse(const string & warehouse_name) {
    if(_warehouseList.find(warehouse_name) != _warehouseList.end())
        return _warehouseList[warehouse_name].get();
    else
        return NULL;
}

void Model::addWarehouse(Warehouse *warehouse, const string & name) {
    _warehouseList[name] = make_shared<Warehouse>(*warehouse);
}

void Model::advance() {
    time.hours++;
    /**vehicles movement**/
    for (auto &[key, value] : _vehicleList) {
        if (value->type == Tra) {
            Track *track = (Track *) value.get();
            if (track->state == offRoad || track->state == stopped) {
                break;
            } else if (track->state == movingTo && time > track->get_dataNode().arrival_time) {
                track->currentPosition = track->destination;
                track->state = parked;
                track->inventory -= track->get_dataNode().case_quantity;
                getWarehouse(track->get_dataNode().whName)->inventory += track->get_dataNode().case_quantity;
            } else if (track->state == movingTo && time < track->get_dataNode().arrival_time) {
                track->currentPosition.x += cos(track->pv.theta) * (track->speed);
                track->currentPosition.y += sin(track->pv.theta) * (track->speed);
            } else if (track->state == parked && time > track->get_dataNode().departure_time) {
                time_hm t = track->get_dataNode().departure_time;
                track->dataNodeNext();
                track->moving_to_dest(getWarehouse(track->get_dataNode().whName)->getPosition());
                track->currentPosition.x += cos(track->pv.theta) * track->speed / (time - t);
                track->currentPosition.y += sin(track->pv.theta) * track->speed / (time - t);
                track->state = movingTo;
            } else if (track->state == offRoad) {
                break;
            }
        } else if (value->type == Sta) {
            State_trooper *st = (State_trooper *) value.get();
            if (st->state == stopped) {
                continue;
            } else if (st->state == parked) {
                double min_dist = 1000000, current_dist;
                string wh;
                Point p;
                for (auto &[key, value] : _warehouseList) {
                    if (count(st->visitedWH.begin(), st->visitedWH.end(), key)) {
                        continue;
                    } else {
                        current_dist = sqrt(pow(st->currentPosition.x - value.get()->getPosition().x, 2) +
                                            pow(st->currentPosition.y - value.get()->getPosition().y, 2));
                        if (current_dist < min_dist) {
                            min_dist = current_dist;
                            wh = key;
                            p = value->getPosition();
                        }
                    }
                }
                st->nextWh = wh;
                st->moving_to_dest(p);
                st->state = movingTo;
                st->currentPosition.x += cos(st->pv.theta) * st->speed;
                st->currentPosition.y += sin(st->pv.theta) * st->speed;
            } else if (st->state == movingTo) {
                if (st->getDistFromDest() <= 0.9 && (st->movement == toDest || st->movement == toPosition)) {
                    st->state = parked;
                    st->currentPosition = st->destination;
                    st->visitedWH.push_back(st->nextWh);
                } else {
                    st->currentPosition.x += cos(st->pv.theta) * st->speed;
                    st->currentPosition.y += sin(st->pv.theta) * st->speed;
                }
            }

        } else if (value->type == Cho) {
            Chopper *chop = (Chopper *) value.get();
            if (chop->state == movingTo) {
                if (chop->movement == onCourse) {
                    chop->currentPosition.x += cos(chop->pv.theta) * chop->speed;
                    chop->currentPosition.y += sin(chop->pv.theta) * chop->speed;
                } else if (chop->getDistFromDest() <= chop->speed && chop->movement == toPosition) {
                    chop->state = parked;
                    chop->currentPosition = chop->destination;
                }
            } else if (chop->state == parked || chop->state == stopped) {
                continue;
            }
        }
    }
    /**Chopper attacking**/
    for (auto &[key, value] : _vehicleList) {
        if(value.get()->type == Cho){
            bool flag = true;//flag is the indicator for a Success or failure of the attack
            Chopper *chop = (Chopper *) value.get();
            if(chop->attacking_mod){
                Point trackPosition = chop->target->currentPosition;
                /**checking if the target is in range**/
                if(chop->currentPosition.getDistance(trackPosition) <= chop->attacking_range) {
                    for (auto &[key2, value2] : _vehicleList) {
                        /**checking fo State_trooper in radios of 10 km from the target position**/
                        if (value2.get()->type == Sta &&
                            value2->currentPosition.getDistance(trackPosition) <= 10) {
                            flag = false;
                        }
                    }
                }
                else
                    flag= false;
                chop->attack(flag);
            }
        }
    }
}
string Model::get_entity_by_point(Point p, double zoom) {
    for(auto & [key, value] : _vehicleList){
        if(abs(p.x  - value.get()->currentPosition.x - 0.1) < zoom/2 && abs(p.y  - value.get()->currentPosition.y - 0.1) < zoom/2){
            return key.substr(0, 2);
        }
    }
    for(auto & [key, value] : _warehouseList){
        if(abs(p.x  - value.get()->getPosition().x - 0.1) < zoom/2 && abs(p.y  - value.get()->getPosition().y - 0.1) < zoom/2){
            return key.substr(0, 2);
        }
    }
    return " .";
}

void Model::print_all_wh() {
    for(auto & [key, value] : _warehouseList){
        cout<< "WareHouses ";
        cout<< key<<" ";
        value.get()->get_state();
        cout<<endl;
    }

}

void Model::print_all_ve() {
    for(auto & [key, value] : _vehicleList){
        cout<<value->type<<" " << key <<" ";
        value->get_state();
        cout<<endl;
    }
}

time_hm Model::getTime() {
    return time;
}



