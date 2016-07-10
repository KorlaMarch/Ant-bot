#ifndef ROLE_H_
#define ROLE_H_

#include "State.h"

struct Role{
    State& state;
    int x,y;
    Role(State _state, int _id = 0, int _x = 0, int _y = 0) : state(_state), id(_id), x(_x), y(_y) {}
    int getID(){
        return id;
    }
    virtual void move() = 0;
    private:
        //changing id is impossible
        int id;
};

#endif
