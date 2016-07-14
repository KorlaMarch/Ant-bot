#include "Pathfinder.h"
#include "Location.h"
#include "MyState.h"

#include <queue>
#include <vector>
#include <functional>

Pathfinder::SearchState::SearchState( const Location& _loc, int _dis ) : loc( _loc ), dis( _dis ) {}

Pathfinder::Pathfinder( MyState& _mystate ) : mystate( _mystate ), ID( 1 ) {}

inline MyState& Pathfinder::state( void ) {
	return mystate;
}

void Pathfinder::setup( void ) {
	distance.assign( state().rows, std::vector< std::pair<int, int> > ( state().cols, { 0, 0 } ) );	
}

inline std::pair< int, int >& Pathfinder::getDistance( const Location& loc ) {
	return distance[ loc.row ][ loc.col ];
}

int Pathfinder::heuristic( const Location &source, const Location &destination ) {
	int dx = abs( source.row - destination.row );
	int dy = abs( source.col - destination.col );
	dx = std::min( dx, state().rows - dx );
	dy = std::min( dy, state().cols - dy );
	return dx + dy;
}

int Pathfinder::getDirection( const Location &source, const Location &destination ) {

	// A* search

	if ( state().getGrid( source ).isWater ) {
		return -1;
	}


	auto compare_heuristic_function = [&] ( SearchState s1, SearchState s2 ) {
		return s1.dis + heuristic( s1.loc, destination ) > s2.dis + heuristic( s2.loc, destination );
	};

	std::priority_queue< SearchState, std::vector< SearchState >, decltype( compare_heuristic_function ) > heap( compare_heuristic_function );

	state().bug << "source : " << source.row << " " << source.col << " " << std::endl;
	state().bug << "destination : " << destination.row << " " << destination.col << " " << std::endl;

	getDistance( source ) = { ID, 0 };
	heap.push( SearchState( source ) );
	

	while ( not heap.empty() ) {

		SearchState bestState = heap.top();
		heap.pop();

		if ( bestState.loc == destination ) {
			break;
		}

		for ( int dir = 0 ; dir < TDIRECTIONS ; ++dir ) {

			const Location nLoc = state().getLocation( bestState.loc, dir );

			if ( getDistance( nLoc ).first == ID and getDistance( bestState.loc ).second + 1 >= getDistance( nLoc ) . second) {
				continue;
			}

			if ( state().isGridEmpty( nLoc ) or state().getGrid( nLoc ).isFood ) {
				getDistance( nLoc ) = { ID, getDistance( bestState.loc ).second + 1 };
				heap.push( SearchState( nLoc, getDistance( nLoc ).second ) );
			}
		}
	}


	int direction = -1;
	
	if ( getDistance( destination ).first == ID ) {
		// the path is found
		Location loc = destination;
		while ( loc != source ) {
			
			for ( int dir = 0 ; dir < TDIRECTIONS ; ++ dir ) {

				const Location nLoc = state().getLocation( loc, dir );
				
				if ( getDistance( nLoc ).first == ID and getDistance( loc ).second == getDistance( nLoc ).second + 1 ) {
					loc = nLoc;
					direction = state().getOppositeDirection( dir );
				}
			}
		}
	}

	state().bug << direction << std::endl;

	// increase the ID
	ID++;

	return direction;
}