#ifndef MY_STATE_H_
#define MY_STATE_H_

#include "State.h"
#include "Role.h"
#include "Bot.h"

#include <memory>
#include <vector>

// forward declaration
class Bot;
class Pathfinder;
class Role;

class MyState : public State {

	typedef std::unique_ptr< Role* > rolePtr;

private: 

    Bot& MyBot;

	int antCnt;
    int antMaxID;

    // path finder
    std::unique_ptr< Pathfinder* > PathFinder;

public:

	// the ants
	std::vector< std::vector< int > > gridToAnt;
	std::vector< rolePtr > myAntsWithRoles;

    // pathfinder
    Pathfinder& pathfinder( void );
    
	// setup function
    void setup();

    // run function
    void run();

    // makemove function ( overide from State )
    void makeMove( const Location &loc, int direction );
    
	// update functions	
	void updateState(void);
    
    // helper functions

    int getOppositeDirection( int );

    void antDie( int antID );
    int getAntSize( void ) const;

    Role& getAnt( const int ) const ;
    Role& getAnt( const rolePtr& ) const;
    Role& getAnt( const Location& ) const;

    bool isAnt( const Location& ) const;

    Square& getGrid( const Location& loc );
    Square& operator[]( const Location& loc );

    bool isGridEmpty( const Location& loc );

    // constructor
    MyState( Bot& );


};

#endif