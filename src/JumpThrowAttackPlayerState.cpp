#include "../include/Events.h"

#include "../include/JumpThrowAttackPlayerState.h"

#include "../include/RunRightPlayerState.h"
#include "../include/GlidePlayerState.h"
#include "../include/DiedPlayerState.h"

PlayerState* JumpThrowAttackPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("JumpThrowAttackPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::THROW_STOP_EVENT)
	{
		DEBUG_MSG("JumpThrowAttackPlayerState -> GlidePlayerState");
		return new GlidePlayerState();
	}
	return nullptr;
}
void JumpThrowAttackPlayerState::update(Player& player, float dt) {}
void JumpThrowAttackPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering JumpThrowAttackPlayerState");
	player.getAnimatedSprite().clearFrames();
	player.getAnimatedSprite().addFrame(new TextureData(4596, 0, 360, 431));
	player.getAnimatedSprite().addFrame(new TextureData(4956, 0, 360, 431));
	player.getAnimatedSprite().addFrame(new TextureData(5316, 0, 360, 431));
	player.getAnimatedSprite().addFrame(new TextureData(4596, 431, 360, 431));
	player.getAnimatedSprite().addFrame(new TextureData(4956, 431, 360, 431));
	player.getAnimatedSprite().addFrame(new TextureData(5316, 431, 360, 431));
	player.getAnimatedSprite().addFrame(new TextureData(4596, 862, 360, 431));
	player.getAnimatedSprite().addFrame(new TextureData(4956, 862, 360, 431));
	player.getAnimatedSprite().addFrame(new TextureData(5316, 862, 360, 431));
	player.getAnimatedSprite().addFrame(new TextureData(4596, 1293, 360, 431));

	player.getAnimatedSprite().setTime(0.05f);
}
void JumpThrowAttackPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting JumpThrowAttackPlayerState");
}