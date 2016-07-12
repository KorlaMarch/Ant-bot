#ifndef GATHER_H_
#define GATHER_H_

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
            dis(state.rows,std::vector<int>(state.cols,-1));
        }

        bool isFarmZone(Location loc);

    private:
        
        std::vector<std::vector<int> > dis;

        bool bfs_checkLoc(Location loc);
        void bfs(int x, int y, int d);
};

#endif