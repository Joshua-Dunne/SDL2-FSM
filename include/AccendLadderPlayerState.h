#ifndef ACCEND_LADDER_PLAYER_STATE_H
#define ACCEND_LADDER_PLAYER_STATE_H

#include "../include/Player.h"
#include "../include/PlayerState.h"

class AccendLadderPlayerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&, float dt);
	virtual void enter(Player&);
	virtual void exit(Player&);
};

#endif
