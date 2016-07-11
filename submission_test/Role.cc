#include "Role.h"
#include "State.h"
#include "Location.h"

#include <algorithm>
#include <vector>
#include <memory>

void Role::die( void ) {
	if ( not Dead ) {
		state().antDie( getID() );
	}
	Dead = true;
}
bool Role::isDead( void ) const {
	return Dead;
}
Location Role::getLocation( void ) const {
	return Location( x, y );
}
int Role::getID( void ) const {
	return id;
}
MyState& Role::state(void) {
	return mystate;
}
void Role::run( void ) {

	int dir = move();

	if ( 0 < dir and dir < TDIRECTIONS ) {

		x += DIRECTIONS[dir][0];
		y += DIRECTIONS[dir][1];

    	state().makeMove( getLocation(), dir );
	}
}

Role::Role( MyState _state, int _id, int _x, int _y) : mystate(_state), id(_id), x(_x), y(_y), Dead( false ) {}
