#include "Controller.h"

int main(int argc, char** argv) {
    Controller controller;
    controller.init(argc, argv);
    /** interactive exceptions system**/
    while(1) {
        try {
            controller.run();
        } catch (MyExceptions myExceptions) {
            if (strcmp(myExceptions.what(), "exit") == 0) {
                cout << "goodbye..." << endl;
                break;
            }
            cerr << myExceptions.what() << endl;
            continue;
        }
    }
    return 0;
}
