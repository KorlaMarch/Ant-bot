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

	if ( isDead() ) return;

	int dir = move();

	if ( 0 <= dir and dir < TDIRECTIONS ) {

		const Location nwloc = state().getLocation( getLocation(), dir );
		if ( state().isGridEmpty( nwloc ) ) {		
	    	state().makeMove( getLocation(), dir );
	    	x = nwloc.row;
	    	y = nwloc.col;
		}
	}
}

Role::Role( MyState& _state, int _id, int _x, int _y) : mystate(_state), id(_id), x(_x), y(_y), Dead( false ) {}
