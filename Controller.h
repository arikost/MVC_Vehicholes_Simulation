/* Controller
This class is responsible for controlling the Model and View according to interactions
with the user.
*/
#ifndef MVC_VEHICHOLES_SIMULATION_CONTROLLER_H
#define MVC_VEHICHOLES_SIMULATION_CONTROLLER_H

#include "View.h"
#include "Model.h"
class Controller {
public:	
	Controller();
	~Controller();

	// creates View object, runs the program by accepting user commands, then destroys View object
	void run(){
	    VehicleFactory *vf;
        Model &model = Model::get_Instance();

	}

private:
	View* view_ptr;
};
#endif //MVC_VEHICHOLES_SIMULATION_CONTROLLER_H
