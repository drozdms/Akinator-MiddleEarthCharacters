#ifndef GOAL_H
#define GOAL_H
#include "Database.h"
#include <iostream>
typedef unsigned int uint;
class Goal {


public:
    virtual std::string returnType() = 0;
    virtual bool isActual() = 0;
    virtual int getNumber() = 0;
    virtual void setActual() = 0;
    virtual void setNumber(uint number) = 0;
};



#endif // GOAL_H
