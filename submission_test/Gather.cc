#include "Role.h"
#include "queue"
#include "array"
#include "math.h"

bool Gather::isFarmZone(Location loc){
    return (loc.row-anchorX)*(loc.row-anchorX)+(loc.col-anchorY)*(loc.col-anchorY)<=state.viewradius2;
}

int Gather::move(){

}

//check if loc is suitable to bfs to
bool Gather::bfs_checkLoc(Location loc){
    return !state.getGrid(loc.row,loc.col).isWater && dis[loc.row][loc.col]==0 && !(loc.row==anchorX&&loc.col==anchorY);
}

//make a small bfs over a small distance (d)
void Gather::bfs(int x, int y, int d){
    std::queue<Location> qu;
    qu.push_back(Location(x,y));
    dis[x][y] = 1;
    while(!qu.empty())
    {
        auto loc = qu.front();
        qu.pop();
        int newd = dis[loc.row][loc.col]+1;
        //if bfs more than d , break
        if(newd>d) break;
        for(int i = 0; i < TDIRECTIONS; i++){
            Location newloc = state.getLocation(loc,i);
            if(checkLoc(newloc))
            {
                dis[newloc.row][newloc.col] = newd;
                qu.push(newloc);
            }
        }
    }
}
