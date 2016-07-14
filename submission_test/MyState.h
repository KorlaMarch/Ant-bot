#ifndef MY_STATE_H_
#define MY_STATE_H_

#include "State.h"
#include "Role.h"
#include "Bot.h"

#include <memory>

// forward declaration
class Role;
class Bot;

class MyState : public State {

	typedef std::unique_ptr< Role* > rolePtr;

private: 

    Bot& MyBot;

	int antCnt;
    int antMaxID;

public:

	// the ants
	std::vector< std::vector< int > > gridToAnt;
	std::vector< rolePtr > myAntsWithRoles;

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
    Role& getAnt( const Location ) const;

    bool isAnt( const Location ) const;

    Square& getGrid( const Location loc );
    bool isGridEmpty( const Location loc );

    // constructor
    MyState( Bot& );
};

#endif