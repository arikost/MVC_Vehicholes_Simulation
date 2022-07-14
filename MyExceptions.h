//
// Created by USER on 7/14/2022.
//

#ifndef MVC_VEHICHOLES_SIMULATION_MYEXCEPTIONS_H
#define MVC_VEHICHOLES_SIMULATION_MYEXCEPTIONS_H

class MyExceptions: virtual public std::exception{
protected:
    string msg;
public:
    MyExceptions(string msg){
        this->msg = msg;
    }
    virtual const char* what() const throw () {
        return msg.c_str();
    }
};


#endif //MVC_VEHICHOLES_SIMULATION_MYEXCEPTIONS_H
