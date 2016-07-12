#include "MyState.h"
#include "Role.h"
#include "Bot.h"
#include "Square.h"

#include <algorithm>
#include <memory>

// helper functions
void MyState::antDie( int antID ) {
	// antID just die
	if ( not getAnt( antID ).isDead() ) {
		antCnt--;
	}
}
Role& MyState::getAnt( const int id ) const {
	return **myAntsWithRoles[id];
}
Role& MyState::getAnt( const rolePtr& ant ) const {
	return **ant;
}
Square& MyState::getGrid(const Location &loc) {
    return grid[ loc.row ][ loc.col ];
}

int MyState::getAntSize( void ) const {
	return antCnt;
}

void MyState::setup()
{
    grid = std::vector< std::vector<Square> >(rows, std::vector<Square>(cols, Square()));
    gridToAnt = std::vector< std::vector<int> >(rows, std::vector<int>(cols, -1) );
}

void MyState::run( void ) {
	for ( const auto& antPtr : myAntsWithRoles ) {
		getAnt( antPtr ).run();
	}
}

void MyState::updateState( void ) {

	updateVisionInformation();

	for ( const auto& antPtr : myAntsWithRoles ) {

		auto& ant = getAnt( antPtr );

		if ( getGrid( ant.getLocation() ).ant != 0 ) {
			// this ant is dead
			ant.die(); 

		}
	}

	for ( auto& antPtr : myAntsWithRoles ) {
		
		auto &ant = **antPtr;
		auto &vec = ant.neighbors;

		// add new ants that are at the border of its vision
		{

			const int r = rows;
			const int c = cols;
			const int offset = 3;
			int posx = ( ant.getLocation().row - (int) viewradius + r ) % r;
			int posy = ant.getLocation().col;
			int dx = -1, dy = 1;

			for ( int i = 0 ; i < 4 * viewradius ; i++ ) {

				while ( distance( ant.getLocation(), Location( posx, posy ) ) > viewradius ) {
					posy = ( posy + dy + c ) % c;
				} 

				for ( int j = 0 ; j < offset ; j++ ) {
					int nposy = ( posx + offset * dy + c ) % c;
					if ( distance( ant.getLocation(), Location( posx, nposy ) ) <= viewradius and gridToAnt[ posx ][ nposy ] != -1 ) {
						int antID = gridToAnt[ posx ][ nposy ];
						if ( std::find( vec.begin(), vec.end(), antID ) == vec.end() ) {
							vec.push_back( antID );
						}
					}
				}

				posx = ( posx + dx + 1 ) % r;
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

	for( const Location& hill : myHills ) {
		if( getGrid( hill ).ant != 0 and gridToAnt[ hill.row ][ hill.col ] == -1 ) {

			// new ant found
			gridToAnt[ hill.row ][ hill.col ] = antMaxID;
			myAntsWithRoles.push_back( rolePtr( new Role*( new Role( MyBot.createAnt( antMaxID, hill ) ) ) ) );
			antMaxID++;
			antCnt++;
		}
	}
}

MyState::MyState( Bot &mybot ) : MyBot( mybot ), antCnt(0), antMaxID(0) {}