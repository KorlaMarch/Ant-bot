#include "Hunter.h"
#include "MyState.h"

#include <algorithm>
#include <map>
#include <queue>

int Hunter::move ( void ) {

	// search for anything thereby
	// by using very inefficient BFS
	std::map< Location, int > dis;
	dis.clear();
	std::queue< Location > que;

	dis[ getLocation() ] = 0;
	que.push( getLocation() );

	Location dest = getLocation();
	while ( not que.empty() ) {

		const Location current = que.front();
		que.pop();

		if ( dis[ current ] > viewradius ) {
			continue;
		}

		const auto& grid = state().getGrid( current );
		if ( grid.isFood or ( grid.isHill and grid.hillPlayer > 0 ) or grid.ant > 0 ) {
			dest = current;
			break;
		}

		for ( int dir = 0 ; dir < TDIRECTIONS ; dir++ ) {
			
			Location nwloc = state().getLocation( current, dir );
		
			if ( ( not state().getGrid( nwloc ).isFood ) and ( not state().isGridEmpty( nwloc ) ) ) {
				continue;
			}	

			if ( dis.find( nwloc ) == dis.end() ) {
				dis[ nwloc ] = dis[ current ] + 1;
				que.push( nwloc );
			}
		}
	}

	// if the object is found, move towards it
	if ( dest != getLocation() ) {
		return state().pathfinder().getDirection( getLocation(), dest );
	}

	// if the target is not found, the ant will go straight
	Location loc = state().getLocation( getLocation(), direction );
	if ( not state().isGridEmpty( loc ) ) {
		int nxd = rand() % 3 + 1;
		direction = ( direction + nxd ) % TDIRECTIONS;
	}


	return direction;
}

Hunter::Hunter( MyState& _state, int _id, int _x , int _y, int _viewradius ) : Role( _state, _id, _x, _y ), viewradius( _viewradius ), direction( rand() % TDIRECTIONS ) {}
