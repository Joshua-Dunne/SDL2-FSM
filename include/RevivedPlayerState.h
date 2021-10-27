#ifndef REVIVED_PLAYER_STATE_H
#define REVIVED_PLAYER_STATE_H

#include "../include/Player.h"
#include "../include/PlayerState.h"

class RevivedPlayerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&, float dt);
	virtual void enter(Player&);
	virtual void exit(Player&);
private:
	float m_clock;
};

#endif