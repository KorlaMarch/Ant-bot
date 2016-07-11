#ifndef MY_STATE_H_
#define MY_STATE_H_

#include "State.h"
#include "Role.h"

#include <memory>

class MyState : public State {

	typedef std::unique_ptr< Role* > rolePtr;

public:

	int antCnt;
    int antMaxID;

	// the ants
	std::vector< rolePtr > myAntsWithRoles;

	// update functions	
	void updateState(void);

    rolePtr createAnt(void);
    
    // helper functions
    Role& getAnt( const int );
    Role& getAnt( const rolePtr& );

};

#endif