#ifndef BOT_H_
#define BOT_H_

#include "MyState.h"
#include "Location.h"
#include "Role.h"
#include "Pathfinder.h"

#include <memory>

// forward declaration
class MyState;
class Role;
class Pathfinder;

class Bot
{
public:

    // engines
    std::unique_ptr< MyState* > mystate;

    void playGame();    //plays a single game of Ants

    void makeMoves();   //makes moves for a single turn
    void endTurn();     //indicates to the engine that it has made its moves

    MyState& state(void);

    virtual Role* createAnt( int antID, const Location ); // virtual functions for adding more ants

    Bot(void);
};

#endif //BOT_H_
