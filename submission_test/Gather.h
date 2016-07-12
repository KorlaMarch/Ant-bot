#ifndef GATHER_H_
#define GATHER_H_

#include "Role.h"
#include "queue"
#include "array"
#include "math.h"
#include "Pathfinder.h"

class Gather: public Role{
    public:
        int anchorX, anchorY;
        Gather(MyState& _state, int _id = 0, int _x = 0, int _y = 0, int _anchorX = 0, int _anchorY = 0);
        bool isFarmZone(Location loc);
        int move();
        //left and topmost location of farmzone
        Location LeftTop;
    private:
    	//Dis ==> vector with offset to speed up and save memory
    	std::vector<std::vector<int> > dis;
    	int disOffX, disOffY;

    	void clearDis(int offX, int offY, int rsize, int csize);
    	Location getDisIndex(Location loc);
    	int getDis(Location loc);
    	void setDis(Location loc, int v);
        bool bfs_checkLoc(Location loc);
        int bfsFood(Location currentLoc);
};

#endif