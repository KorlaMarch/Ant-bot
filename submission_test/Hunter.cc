#include "Hunter.h"
#include "MyState.h"
#include <algorithm>

int Hunter::move ( void ) {

	Location loc = state().getLocation( getLocation(), direction );
	if ( not state().isGridEmpty( loc ) ) {
		direction = ( direction + 1 ) % TDIRECTIONS;
	}
	return direction;
}

Hunter::Hunter( MyState& _state, int _id, int _x , int _y ) : Role( _state, _id, _x, _y ), direction( rand() % TDIRECTIONS ) {}
