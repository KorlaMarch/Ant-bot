#ifndef HUNTER_H
#define HUNTER_H

#include "Role.h"

class Hunter : public Role {

	public:

		int viewradius;
		int direction;
		
		int move(void);
		Hunter( MyState& _state, int _id, int _x , int _y, int _viewradius );

};

#endif