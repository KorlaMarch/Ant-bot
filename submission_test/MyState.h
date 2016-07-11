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

private: 

	Bot& MyBot;
	typedef std::unique_ptr< Role* > rolePtr;

public:

	int antCnt;
    int antMaxID;

	// the ants
	std::vector< std::vector< int > > gridToAnt;
	std::vector< rolePtr > myAntsWithRoles;

	// setup function
    void setup();

    // run function
    void run();
    
	// update functions	
	void updateState(void);

    rolePtr createAnt(void);
    
    // helper functions
    Role& getAnt( const int );
    Role& getAnt( const rolePtr& );

    // constructor
    MyState( Bot& );
};

#endif