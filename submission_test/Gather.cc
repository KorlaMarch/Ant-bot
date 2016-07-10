#include "Role.h"
#include "queue"

class Gather : public Role{
    public:
        int anchorX, anchorY;
        int move(){

        }
    private:
        //make a small bfs over a small distance (d)
        int dis[stats.rows][stats.cols];
        void bfs(int d){
            std::queue<std::pair<int,int> > qu;
            qu.push_back({anchorX,anchorY});
            while(!qu.empty()){
                auto pi = qu.front();
                qu.pop();
                if(pi.)
            }
        }

};
