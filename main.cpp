#include "Controller.h"

int main(int argc, char** argv) {
    Controller controller;
    try {
        controller.init(argc, argv);
        controller.run();
    }catch(MyExceptions myExceptions){
        cerr<< myExceptions.what()<<endl;
    }
    return 0;
}
