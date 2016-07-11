#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include "State.h"
class Pathfinder{
	public:
		//return direction that will move closer to the destination
		int getDirection(Location source, Location destination);


};

#endif