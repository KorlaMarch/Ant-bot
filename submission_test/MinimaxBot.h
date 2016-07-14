#ifndef MINIMAXBOT_H
#define MINIMAXBOT_H

#include "Role.h"

class MinimaxBot : public Role {

	public:

		MinimaxBot( MyState& _state, int _id, int _x , int _y );

		int move(void);
};

#endif