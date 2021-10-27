#ifndef PLAYER_H
#define PLAYER_H

#include "../include/Events.h"
#include "../include/PlayerState.h"
#include "../include/AnimatedSprite.h"
#include "../include/TextureData.h"

class Player
{
private:
	PlayerState* m_state;
	AnimatedSprite m_animated_sprite;

public:
	Player(const SDL_Texture*);
	virtual void handleInput(gpp::Events);
	virtual void update(float dt);
	AnimatedSprite& getAnimatedSprite();
	SDL_Texture* getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite&);
	PlayerState* getPlayerState();
	void setPlayerState(PlayerState*);
};
#endif

