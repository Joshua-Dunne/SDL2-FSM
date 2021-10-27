#ifndef ATTACK_PLAYER_STATE_H
#define ATTACK_PLAYER_STATE_H

#include "../include/Player.h"
#include "../include/PlayerState.h"

class AttackPlayerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&, float dt);
	virtual void enter(Player&);
	virtual void exit(Player&);
};

#endif