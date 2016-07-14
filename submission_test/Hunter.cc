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

		if ( dis[ current ] > state().viewradius2 ) {
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
		
		int dir = -1;
		while ( dest != getLocation() ) {
			for ( int d = 0 ; d < TDIRECTIONS ; d++ ) {

				Location nwloc = state().getLocation( dest, d );

				if ( dis.find( nwloc ) != dis.end() and dis[ nwloc ] + 1 == dis[ dest ] ) {
					dest = nwloc;
					dir = state().getOppositeDirection( d );
					break;
				}
			}
		}
		return dir;
	}

	// if the target is not found, the ant will go straight
	Location loc = state().getLocation( getLocation(), direction );
	if ( not state().isGridEmpty( loc ) ) {
		int nxd = rand() % 3 + 1;
		direction = ( direction + nxd ) % TDIRECTIONS;
	}


	return direction;
}

Hunter::Hunter( MyState& _state, int _id, int _x , int _y ) : Role( _state, _id, _x, _y ), direction( rand() % TDIRECTIONS ) {}
