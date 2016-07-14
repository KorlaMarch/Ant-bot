/*
PathFinder is an engine used for determining the direction
each ant has to move in order to reach the desire target

the path is calulated by using A* search
*/

#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include "MyState.h"

#include <vector>

class MyState;

class Pathfinder {
	
	private:

		// id of the operation
		int ID = 0;

		// mark the visited grid
		std::vector< std::vector< std::pair< int, int > > > distance;

		// refernce to the current state
		MyState& mystate;

		// get the distance
		inline std::pair< int, int >& getDistance( const Location& loc );

	public:

		class SearchState {
			
			public:
				
				Location loc;
				int dis;

				SearchState( const Location& _loc, int _dis = 0 );

		};

		// heuristic function
		int heuristic( const Location& loc1, const Location& loc2 );

		// set up function
		void setup( void );
		
		// helper function
		inline MyState& state( void );

		// constructor
		Pathfinder( MyState& _mystate );

		// return direction that will move closer to the destination
		int getDirection( const Location& source, const Location& destination );


};

#endif