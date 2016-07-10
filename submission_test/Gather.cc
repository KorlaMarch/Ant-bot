#include "Role.h"
#include "queue"
#include "array"
#include "math.h"

class Gather : public Role{
    public:
        int anchorX, anchorY;
        Gather(State _state, int _id = 0, int _x = 0, int _y = 0, int _anchorX = 0, int _anchorY = 0) : Role(State _state, _id, _x, _y){
            anchorX = _anchorX;
            anchorY = _anchorY;
            dis(state.rows,std::vector<int>(state.cols));
            bfs
        }

        int move(){

        }
    private:
        //make a small bfs over a small distance (d)
        std::vector<std::vector<int> > dis;

        //check if loc is suitable to bfs to
        bool bfs_checkLoc(Location loc){
            return !state.getGrid(loc.row,loc.col).isWater && dis[loc.row][loc.col]==0 && !(loc.row==anchorX&&loc.col==anchorY);
        }

        void bfs(int d){
            std::queue<Location> qu;
            qu.push_back(Location(anchorX,anchorY));
            dis[anchorX][anchorY] = 0;
            while(!qu.empty())
            {
                auto loc = qu.front();
                qu.pop();
                int newd = dis[loc.row][loc.col]+1;
                //if bfs more than d , break
                if(newd>d) break;
                for(int i = 0; i < 4; i++){
                    Location newloc = state.getLocation(loc,i);
                    if(checkLoc(newloc))
                    {
                        dis[newloc.row][newloc.col] = newd;
                        qu.push(newloc);
                    }
                }
            }
        }

};
