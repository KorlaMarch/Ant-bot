
#ifndef ROLE_H_
#define ROLE_H_

#include "Location.h"
#include "State.h"

#include <vector>
#include <memory>

// this class is partial abstract
class Role {

public:

    // reference to the main state
    State& state;

    // neighbors
    std::vector<int> neighbors;

private:

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

    // terminate function
    void die(void); 

    // return the status of the ant
    bool isDead(void) const;

    // return location of the ant
    Location getLocation(void) const;

    // return the id of the ant
    int getID() const;

    // constructor
    Role(State _state, int _id = 0, int _x = 0, int _y = 0);


