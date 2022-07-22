/* Controller
This class is responsible for controlling the Model and View according to interactions
with the user.
*/
#ifndef MVC_VEHICHOLES_SIMULATION_CONTROLLER_H
#define MVC_VEHICHOLES_SIMULATION_CONTROLLER_H

#include <cstring>
#include "View.h"
#include "Model.h"

class Controller {
private:
    View* view_ptr;
    VehicleFactory *vf;
public:
	Controller(){
	    this->view_ptr = new View();

    }
	void init(int argc, char** argv){
        Model &model = Model::get_Instance();
	    if(argc < 5){
            throw MyExceptions("");
	    }
        if(strcmp(argv[1], "-w") != 0){
            throw MyExceptions("");
        }
        if(strcmp(argv[2], "depot.dat") != 0){
            throw MyExceptions("");
        }
        else{
            fstream whFile(argv[2]);
            string whName, buff;
            Point pos;
            int inv;
            while(whFile.peek() != EOF){
                whFile >> whName;
                whFile >> buff;
                pos.x = stod(buff.substr(1, buff.size()-2));
                whFile >> buff;
                pos.y = stod(buff.substr(0, buff.size()-3));
                whFile >> inv;
                whName.pop_back();
                model.addWarehouse(new Warehouse(pos,whName, inv), whName);
            }
        }
        if(strcmp(argv[3], "-t") != 0){
            throw MyExceptions("");
        }
        for (int i = 4; i < argc ; ++i) {
            string track_dat_file = string(argv[i]);
            /**check file validation**/
            ifstream inFile(track_dat_file);
            Point p;
            string buff, name;
            bool first_wh_flag = true;
            while(inFile >> buff){
                name = buff.substr(0, buff.find(','));
                if(model.getWarehouse(name) == NULL){
                    throw MyExceptions("Error:: wh dont exist" + name);

                }
                if(first_wh_flag){
                    first_wh_flag = false;
                    p = model.getWarehouse(name)->getPosition();
                }
            }
            inFile.close();
            model.addVehicle(p, track_dat_file, (string &) "", "Track");
        }

    }
	~Controller() = default;

	// creates View object, runs the program by accepting user commands, then destroys View object
	void run(){

        Model &model = Model::get_Instance();
        string buff;
        cout << "[time: "; model.getTime().print(); cout<< "] Enter commend: ";

        while( cin >> buff){
            if(buff == "exit"){
                throw MyExceptions("exit");
            }
            else if(buff == "default"){
                view_ptr->default_args();
            }
            else if(buff == "size"){
                int s;

                try{
                    cin >> s;
                    view_ptr->set_size(s);
                }catch (MyExceptions e){
                    cerr<< e.what()<<endl;
                }
            }
            else if(buff == "zoom"){
                int s;
                cin >> s;
                try{
                    view_ptr->set_zoom(s);
                }catch (MyExceptions e){
                    cerr<< e.what()<<endl;
                }

            }
            else if(buff == "pan"){
                Point cen;
                cin >> cen.x;
                cin >> cen.y;
                try{
                    view_ptr->set_center(cen);
                }catch (MyExceptions e){
                    cerr<< e.what()<<endl;
                }

            }
            else if(buff == "show"){
                cout<<endl;
                view_ptr->show();
            }
            else if(buff == "go"){
                model.advance();
            }
            else if(buff == "create"){
                string name, type, wh_name;
                Point p;
                cin >> name;
                if(name.size() > 12){
                    cerr<<"Error:: name length mast be less then 12 characters\n";
                }
                cin >> type;
                if(type == "State_trooper"){
                    cin >> wh_name;
                }
                else if(type == "Chopper") {
                    cin >> buff;
                    p.x = stod(buff.substr(1, buff.size() - 2));
                    cin >> buff;
                    p.y = stod(buff.substr(0, buff.size() - 2));
                }
                model.addVehicle(p,name,wh_name,type);
            }
            else if(buff == "status"){
                model.print_all_wh();
                model.print_all_ve();
            }
            else {
                /**************** commend to vehicles ********************/
                Vehicle * vehicle = model.getVehicle(buff);
                if (vehicle == NULL) {
                    throw MyExceptions("Error:: illegal vehicle name: " + buff);
                }
                cin >> buff;
                if (buff == "course") {
                    cin >> buff;
                    if(!check_numeric(buff)){
                        throw MyExceptions("Error:: illegal parameter"+buff);
                    }
                    vehicle->moving_on_course(to_radians(stod(buff)));
                    vehicle->movement = onCourse;
                    if(vehicle->type == Cho){
                        cin >> buff;
                        if(!check_numeric(buff)){
                            throw MyExceptions("Error:: illegal parameter"+buff);
                        }
                        vehicle->speed = stod(buff) / 100;
                    }
                }
                else if (buff == "position") {
                    Point p;
                    cin >> buff;
                    if(!check_numeric(buff)){
                        throw MyExceptions("Error:: illegal parameter"+buff);
                    }
                    p.x = stod(buff);
                    cin >> buff;
                    if(!check_numeric(buff)){
                        throw MyExceptions("Error:: illegal parameter"+buff);
                    }
                    p.y = stod(buff);
                    vehicle->moving_to_dest(p);
                    vehicle->movement = toPosition;
                    if(vehicle->type == Cho){
                        cin >> buff;
                        if(!check_numeric(buff)){
                            throw MyExceptions("Error:: illegal parameter"+buff);
                        }
                        vehicle->speed = stod(buff) / 100;
                    }
                }
                else if (buff == "destination") {
                    cin >> buff;
                    Warehouse * wh = model.getWarehouse(buff);
                    if(wh == NULL){
                        throw MyExceptions("wh dont exist "+buff);
                    }
                    if(vehicle->type != Sta){
                        throw MyExceptions("Error:: illegal commend: "+ buff+" not a State_trooper");
                    }else {
                        State_trooper *st = (State_trooper *) vehicle;
                        st->nextWh = buff;
                        st->moving_to_dest(wh->getPosition());
                        st->movement = toDest;
                    }
                }
                else if (buff == "attack") {
                    if(vehicle->type != Cho){
                        throw MyExceptions("Error:: "+vehicle->name+" is not a Chopper");
                    }
                    Chopper * chop = (Chopper*) vehicle;
                    cin >>buff;
                    Vehicle * target = model.getVehicle(buff);
                    if(target == NULL){
                        throw MyExceptions("Error:: "+ buff + " doesn't exist");
                    }
                    if(target->type != Tra){
                        throw MyExceptions("Error:: "+target->name+" is not a Track");
                    }
                    chop->set_target((Track*) target);
                }
                else if (buff == "stop") {
                    vehicle->state = stopped;
                }
            }
            cout << "[time: "; model.getTime().print(); cout<< "] Enter commend: ";
        }

	}
    bool check_numeric(string & str){
        string::iterator it = str.begin();
        while(it != str.end()){
            if(!isdigit(*it) && *it != '.'){
                return false;
            }
            it++;
        }
        return true;
    }
};
#endif //MVC_VEHICHOLES_SIMULATION_CONTROLLER_H
