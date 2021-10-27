#ifndef CLIMB_DOWN_PLAYER_STATE_H
#define CLIMB_DOWN_PLAYER_STATE_H

#include "../include/Player.h"
#include "../include/PlayerState.h"

class ClimbDownPlayerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&, float dt);
	virtual void enter(Player&);
	virtual void exit(Player&);
};

#endif