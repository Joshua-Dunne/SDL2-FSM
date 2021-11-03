#ifndef PLAYER_H
#define PLAYER_H

#include "../include/Events.h"
#include "../include/PlayerState.h"
#include "../include/AnimatedSprite.h"
#include "../include/TextureData.h"
#include "../include/Vector2.h"

class Player
{
private:
	PlayerState* m_state;
	AnimatedSprite m_animated_sprite;

public:
	Player();
	Player(Vector2 t_pos);
	virtual void handleInput(gpp::Events);
	virtual void update(float dt);
	AnimatedSprite& getAnimatedSprite();
	TextureData* getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite&);
	PlayerState* getPlayerState();
	void setPlayerState(PlayerState*);

	void move(Vector2);

	Vector2 m_pos;

	float m_speed = 250.0f;
	bool m_runningRight = false;
};
#endif

