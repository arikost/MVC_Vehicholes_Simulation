#include "Controller.h"
int main(int argc, char** argv) {
    Controller controller;
    controller.init(argc, argv);
    controller.run();
    return 0;
}
