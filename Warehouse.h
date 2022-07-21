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
        this->position = position;
    }
    Point getPosition(){
        return this->position;
    }
    void get_state(){
        cout << "at position ";
        position.print();
        cout<<", Inventory: "<<inventory;
    }
    int inventory;
private:
    string name;
    Point position;

};


#endif //MVC_VEHICHOLES_SIMULATION_WAREHOUSE_H
