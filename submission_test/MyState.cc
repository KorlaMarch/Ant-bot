#include "Bot.h"
#include "MyState.h"
#include "Pathfinder.h"
#include "Role.h"
#include "Square.h"

#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>

// helper functions

int MyState::getOppositeDirection( int dir ) {
	return ( dir + 2 ) % TDIRECTIONS;
}
void MyState::antDie( int antID ) {
	// antID just die
	if ( not getAnt( antID ).isDead() ) {
		antCnt--;
	}
}

Pathfinder& MyState::pathfinder( void ) {
	return **PathFinder;
}

Role& MyState::getAnt( const int id ) const {
	return **myAntsWithRoles[id];
}
Role& MyState::getAnt( const rolePtr& ant ) const {
	return **ant;
}
Role& MyState::getAnt( const Location& loc ) const {
	return getAnt( gridToAnt[ loc.row ][ loc.col ] );
}

bool MyState::isAnt( const Location& loc ) const {
	return gridToAnt[ loc.row ][ loc.col ] != -1;
}

Square& MyState::getGrid( const Location& loc ) {
    return grid[ loc.row ][ loc.col ];
}
Square& MyState::operator[]( const Location& loc ) {
	return grid[ loc.row ][ loc.col ];
}

bool MyState::isGridEmpty( const Location& loc ) {
	const auto &grid = getGrid( loc );
	return ( not grid.isWater ) and ( not grid.isFood ) and ( ( not grid.isHill ) or ( grid.hillPlayer > 0 ) ) and ( grid.isVisible ) and ( grid.ant != 0 );
}
int MyState::getAntSize( void ) const {
	return antCnt;
}

void MyState::setup() {
    grid = std::vector< std::vector<Square> >( rows, std::vector<Square>( cols, Square() ) );
    gridToAnt = std::vector< std::vector<int> >( rows, std::vector<int>( cols, -1) );
    pathfinder().setup();
}

void MyState::run( void ) {
	for ( const auto& antPtr : myAntsWithRoles ) {
		getAnt( antPtr ).run();
	}
}

void MyState::makeMove( const Location& loc, int direction ) {

    Location nLoc = getLocation( loc, direction );

    // check the valiadtion of the command
    if ( !isGridEmpty( nLoc ) or ( getGrid( loc ).ant != 0 ) ) { 
    	return;
    }
    
    std::cout << "o " << loc.row << " " << loc.col << " " << CDIRECTIONS[direction] << std::endl;
    
    std::swap( getGrid( loc ).ant, getGrid( nLoc ).ant );
    std::swap( gridToAnt[ nLoc.row ][ nLoc.col ], gridToAnt[ loc.row ][ loc.col ] );
};

void MyState::updateState( void ) {

	updateVisionInformation();

	for( const Location& food_loc : food ) {
		getGrid( food_loc ).isFood = true;
	}

	for( const Location& ant : myAnts ) {
		if( gridToAnt[ ant.row ][ ant.col ] == -1 ) {

			// new ant found
			gridToAnt[ ant.row ][ ant.col ] = antMaxID;
			myAntsWithRoles.push_back( rolePtr( new Role*( MyBot.createAnt( antMaxID, ant ) ) ) );
			antMaxID++;
			antCnt++;
		}
	}

	for ( const auto& antPtr : myAntsWithRoles ) {

		auto& ant = getAnt( antPtr );

		if ( getGrid( ant.getLocation() ).ant != 0 ) {
			// this ant is dead
			ant.die(); 
			gridToAnt[ ant.getLocation().row ][ ant.getLocation().col ] = -1;
		}
	}

	for ( auto& antPtr : myAntsWithRoles ) {
		
		auto &ant = **antPtr;
		auto &vec = ant.neighbors;

		// add new ants that are at the border of its vision
		{

			const int offset = 3;
			int posx = ( ant.getLocation().row - (int) viewradius + rows ) % rows;
			int posy = ant.getLocation().col;
			int dx = -1, dy = 1;

			for ( int i = 0 ; i < 4 * viewradius ; i++ ) {

				while ( distance( ant.getLocation(), Location( posx, posy ) ) > viewradius ) {
					posy = ( posy + dy + cols ) % cols;
				} 

				for ( int j = 0 ; j < offset ; j++ ) {
					int nposy = ( posx + offset * dy + cols ) % cols;
					if ( distance( ant.getLocation(), Location( posx, nposy ) ) <= viewradius and gridToAnt[ posx ][ nposy ] != -1 ) {
						int antID = gridToAnt[ posx ][ nposy ];
						if ( std::find( vec.begin(), vec.end(), antID ) == vec.end() ) {
							vec.push_back( antID );
						}
					}
				}

				posx = ( posx + dx + 1 ) % rows;
				if ( i == viewradius ) {
					dx = -1;
					dy = -1;
				} else if ( i == 3 * viewradius ) {
					dx = 1;
					dy = 1;
				}
			}
		}

		std::sort( vec.begin(), vec.end(), [&] ( int id1, int id2 ) {
			auto& ant1 = getAnt( id1 );
			auto& ant2 = getAnt( id2 );
			if ( ant1.isDead() and ant2.isDead() ) return ant1.getID() < ant2.getID();
			if ( ant1.isDead() ) return false;
			if ( ant2.isDead() ) return true;

			return distance( ant.getLocation(), ant1.getLocation() ) < distance( ant.getLocation(), ant2.getLocation() );
		});

		// remove out-of-range ants and dead ants
		while ( !vec.empty() ) {

			auto &concerned_ant = getAnt( vec.back() );

			if ( getAnt( vec.back() ).isDead() ) {
				vec.pop_back();
			} else if ( distance( ant.getLocation(), concerned_ant.getLocation() ) > viewradius ) {
				vec.pop_back();
			} else {
				break;
			}
		}
	}
}

MyState::MyState( Bot &mybot ) : MyBot( mybot ), PathFinder( new Pathfinder*( new Pathfinder( *this ) ) ), antCnt(0), antMaxID(0) {}