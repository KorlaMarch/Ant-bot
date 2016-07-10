
#ifndef ROLE_H_
#define ROLE_H_

#include "Location.h"
#include "State.h"

#include <vector>

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
    virtual int move() = 0;
    
    void run(void) {

    	int dir = move();

    	if ( 0 < dir and dir < TDIRECTIONS ) {

    		x += DIRECTIONS[dir][0];
    		y += DIRECTIONS[dir][1];

	    	state.makeMove( getLocation(), dir );
    	}
    }

    // helper functions

    // terminate function
    void die(void) {
    	Dead = true;
    }

    // return the status of the ant
    bool isDead(void) const {
    	return Dead;
    }

    // return location of the ant
    Location getLocation(void) const {
    	return Location( x, y );
    }

    // return the id of the ant
    int getID() const {
        return id;
    }

    // constructor
    Role(State _state, int _id = 0, int _x = 0, int _y = 0) : state(_state), id(_id), x(_x), y(_y), Dead( false ) {}

};

std::vector< std::unique_ptr<Role*> > myAntsWithRoles;

#endif
