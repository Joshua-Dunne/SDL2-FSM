#ifndef IDLE_PLAYER_STATE_H
#define IDLE_PLAYER_STATE_H

#include "../include/Player.h"
#include "../include/PlayerState.h"

class IdlePlayerState : public PlayerState{
public:
	virtual ~IdlePlayerState();
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&, float dt);
	virtual void enter(Player&);
	virtual void exit(Player&);
};
#endif