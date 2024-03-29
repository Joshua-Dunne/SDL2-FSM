#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "../include/Debug.h"
#include "../include/Events.h"

class Player;

class PlayerState {
public:
	virtual ~PlayerState() {};
	virtual PlayerState* handleInput(gpp::Events&) = 0;
	virtual void update(Player&, float dt) = 0;
	virtual void enter(Player&) = 0;
	virtual void exit(Player&) = 0;
};

#endif