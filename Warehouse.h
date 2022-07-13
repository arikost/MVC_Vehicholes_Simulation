//
// Created by USER on 6/19/2022.
//

#ifndef MVC_VEHICHOLES_SIMULATION_WAREHOUSE_H
#define MVC_VEHICHOLES_SIMULATION_WAREHOUSE_H


class Warehouse {
public:
    Warehouse(Point position, string name, int inv){
        cout<< name<< " created"<<endl;
        this->name = name;
        this->inventory = inv;
        this->position = Point(position.x, position.y);
    }

private:
    int inventory;
    string name;
    Point position;

};


#endif //MVC_VEHICHOLES_SIMULATION_WAREHOUSE_H
