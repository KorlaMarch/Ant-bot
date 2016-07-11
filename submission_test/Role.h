
#ifndef ROLE_H_
#define ROLE_H_

#include "Location.h"
#include "MyState.h"
#include "Bot.h"

#include <vector>
#include <memory>

// forward declaration
class MyState;
class Bot;

// this class is partial abstract
class Role {

public:
    
    // neighbors
    std::vector<int> neighbors;

private:

    // reference to the main state
    MyState& mystate;

    // check whether the ant is dead
    bool Dead;

    // position of the ant
    int x, y;

    // ant's id
    int id;

public:

    // -- virtual functions that will be implemented separately
    
    // communicate
    virtual void receive ( int msg ) {
        // do nothing
    }

    // action move
    virtual int move() {
        // move north by default
        return 0;
    }
    
    void run(void);

    // helper functions
    MyState& state(void);

    // terminate function
    void die(void); 

    // return the status of the ant
    bool isDead(void) const;

    // return location of the ant
    Location getLocation(void) const;

    // return the id of the ant
    int getID() const;

    // constructor
    Role( MyState _state, int _id = 0, int _x = 0, int _y = 0);
};

#endif