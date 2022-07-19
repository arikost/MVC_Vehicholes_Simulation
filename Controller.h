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
                model.addWarehouse(new Warehouse(pos, whName.substr(0, whName.size()-1), inv), whName.substr(0, whName.size()-1));
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
                    throw MyExceptions("wh dont exist");
                }
                if(first_wh_flag){
                    first_wh_flag = false;
                    p = model.getWarehouse(name)->getPosition();
                }
            }
            model.addVehicle(p, track_dat_file, "Track");
        }

    }
	~Controller() = default;

	// creates View object, runs the program by accepting user commands, then destroys View object
	void run(){

        Model &model = Model::get_Instance();
        string buff;
        while( cin >> buff){
            if(buff == "exit"){
                cout << "goodbye..."<< endl;
                break;
            }
            if(buff == "default"){
                view_ptr->default_args();
            }
            if(buff == "size"){
                int s;
                cin >> s;
                try{
                    view_ptr->set_size(s);
                }catch (MyExceptions e){
                    cerr<< e.what()<<endl;
                }
            }
            if(buff == "zoom"){
                int s;
                cin >> s;
                try{
                    view_ptr->set_zoom(s);
                }catch (MyExceptions e){
                    cerr<< e.what()<<endl;
                }

            }
            if(buff == "pan"){
                Point cen;
                cin >> cen.x;
                cin >> cen.y;
                try{
                    view_ptr->set_center(cen);
                }catch (MyExceptions e){
                    cerr<< e.what()<<endl;
                }

            }
            if(buff == "show"){
                model.print_all_wh();
                view_ptr->show();
            }
            if(buff == "go"){
                model.advance();
            }
            if(buff == "create"){
                string name, type;
                Point p;
                cin >> name;
                cin >> type;
                cin >> buff;
                p.x = stod(buff.substr(1, buff.size() - 2));
                cin >> buff;
                p.y = stod(buff.substr(0,buff.size()-2));
                model.addVehicle(p,name,type);
            }
            if(buff == "course"){

            }
            if(buff == "position"){

            }
            if(buff == "destination"){

            }
            if(buff == "attack"){

            }
            if(buff == "stop"){

            }
            if(buff == "status"){

            }
        }

	}

};
#endif //MVC_VEHICHOLES_SIMULATION_CONTROLLER_H
