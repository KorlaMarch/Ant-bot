#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include "MyState.h"
#include "queue"

class Pathfinder{
	public:
		MyState& state;
		Pathfinder(MyState& _state);
		//return direction that will move closer to the destination
		int getDirection(Location source, Location destination);
	private:
		std::vector<std::vector<int> > bfsDis;
		//cqu == queue for reset bfsDis
    	std::queue<Location> cqu;
		void setDis(Location loc, int var);
		int getDis(Location loc);
};

#endif