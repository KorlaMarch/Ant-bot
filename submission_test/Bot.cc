#include "Bot.h"
#include "Gather.h"
#include "Hunter.h"

using namespace std;

//constructor
Bot::Bot() : mystate ( new MyState*( new MyState( *this ) ) )
{
};

MyState& Bot::state( void ) {
    return **mystate;
}

//plays a single game of Ants.
void Bot::playGame()
{
    //reads the game parameters and sets up
    cin >> state();
    state().setup();
    endTurn();

    //continues making moves while the game is not over
    while(cin >> state())
    {
        state().updateState();
        makeMoves();
        endTurn();
    }
};

//makes the bots moves for the turn
void Bot::makeMoves()
{
    state().bug << "turn " << state().turn << ":" << endl;
    state().bug << state() << endl;
    state().run();
    state().bug << "time taken: " << state().timer.getTime() << "ms" << endl << endl;
};

Role* Bot::createAnt( int antID, const Location loc ) {
    return new Hunter( state(), antID, loc.row, loc.col );
}
//finishes the turn
void Bot::endTurn()
{
    if(state().turn > 0)
        state().reset();
    state().turn++;

    cout << "go" << endl;
};
