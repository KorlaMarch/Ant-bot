#include "MyState.h"
#include "Role.h"
#include "Bot.h"
#include "Square.h"

#include <algorithm>
#include <memory>

// MyState function
Role& MyState::getAnt( const int id ) {
	return **myAntsWithRoles[id];
}
Role& MyState::getAnt( const rolePtr& ant ) {
	return **ant;
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
		if( getGrid( hill ).ant != 0 ) {
			// new ant found
			Role *newAnt = MyBot.createAnt( hill );
			myAntsWithRoles.push_back( rolePtr ( &newAnt ) );
		}
	}
}

MyState::MyState( Bot &mybot ) : MyBot( mybot ) {}