#include "MyState.h"
#include "Role.h"

#include <algorithm>
#include <memory>

// MyState function
Role& MyState::getAnt( const int id ) {
	return **myAntsWithRoles[id];
}
Role& MyState::getAnt( const rolePtr& ant ) {
	return **ant;
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

		while ( !vec.empty() ) {

			auto &ant = getAnt( vec.back() );
			if ( getAnt( vec.back() ).isDead() ) {
				vec.pop_back();
			}

			// if ( distance( ant, ))
		}
	}

	for( const Location& hill : myHills ) {
		if( getGrid( hill ).ant != 0 ) {
			// new ant found
			myAntsWithRoles.push_back( createAnt() );
		}
	}
}

std::unique_ptr< Role* > MyState::createAnt(void) {

}