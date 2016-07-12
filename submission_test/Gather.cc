#include "Gather.h"

Gather::Gather(MyState& _state, int _id, int _x, int _y, int _anchorX, int _anchorY) : Role(_state, _id, _x, _y){
    anchorX = _anchorX;
    anchorY = _anchorY;
    LeftTop = Location((anchorX-(int)state().viewradius+state().rows)%state().rows,
        (anchorY-(int)state().viewradius+state().cols)%state().cols);
}

// ===================== Dis vector manipulate =====================

void Gather::clearDis(int offX, int offY, int rsize, int csize){
    disOffX = offX;
    disOffY = offY;
    dis.assign(rsize,std::vector<int>(csize,-1));
}

//Get true index on Dis
Location Gather::getDisIndex(Location loc){
    return Location((loc.row-disOffX+state().rows)%state().rows,(loc.col-disOffY+state().cols)%state().cols);
}

int Gather::getDis(Location loc){
    loc = getDisIndex(loc);
    return dis[loc.row][loc.col];
}

void Gather::setDis(Location loc, int v){
    loc = getDisIndex(loc);
    dis[loc.row][loc.col] = v;
}

// =================================================================

bool Gather::isFarmZone(Location loc){
    return (loc.row-anchorX)*(loc.row-anchorX)+(loc.col-anchorY)*(loc.col-anchorY)<=state().viewradius2;
}

int Gather::move(){
    return bfsFood(getLocation());
}

//check if loc is suitable to bfs to
bool Gather::bfs_checkLoc(Location loc){
    return isFarmZone(loc) && !state().getGrid(loc).isWater && getDis(loc)==-1;
}

//make a small bfs inside a farm zone
//Return -> which direction to move
int Gather::bfsFood(Location currentLoc){
    std::queue<Location> qu;
    clearDis(LeftTop.row,LeftTop.col,2*(int)state().viewradius+2,2*(int)state().viewradius+2);
    qu.push(currentLoc);
    setDis(currentLoc,0);
    while(!qu.empty())
    {
        auto loc = qu.front();
        
        if(state().getGrid(loc).isFood){
            //return Pathfinder.getDirection(currentLoc,loc);
            return 0; //tmp
        }
        
        qu.pop();
        int newd = getDis(loc)+1;

        for(int i = 0; i < TDIRECTIONS; i++){
            Location newloc = state().getLocation(loc,i);
            if(bfs_checkLoc(newloc))
            {
                setDis(newloc,newd);
                qu.push(newloc);
            }
        }
    }
    //no food found -> return to anchor
    //return Pathfinder.getDirection(currentLoc,Location(anchorX,anchorY));
    return 0; //tmp
}
