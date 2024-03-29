#include "../include/Events.h"

#include "../include/ClimbUpPlayerState.h"

#include "../include/ClimbPausePlayerState.h"
#include "../include/ClimbDownPlayerState.h"
#include "../include/DecendLadderPlayerState.h"


PlayerState* ClimbUpPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::MOVE_UP_STOP_EVENT)
	{
		DEBUG_MSG("ClimbUpPlayerState -> ClimbPausePlayerState");
		return new ClimbPausePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::MOVE_DOWN_START_EVENT)
	{
		DEBUG_MSG("ClimbUpPlayerState -> ClimbDownPlayerState");
		return new ClimbDownPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::HIT_LADDER_TOP_EVENT)
	{
		DEBUG_MSG("ClimbUpPlayerState -> DecendLadderPlayerState");
		return new DecendLadderPlayerState();
	}

	return nullptr;
}
void ClimbUpPlayerState::update(Player& player, float dt) {}
void ClimbUpPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering ClimbUpPlayerState");

	// Climb Up Animated Sprite
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(new TextureData(1608, 1392, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(2172, 928, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(1890, 928, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(1608, 928, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(2172, 464, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(1890, 464, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(1608, 464, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(2172, 0, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(1890, 0, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(1608, 0, 282, 464));

	player.getAnimatedSprite().setTime(0.05f);
}
void ClimbUpPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting ClimbUpPlayerState");
}