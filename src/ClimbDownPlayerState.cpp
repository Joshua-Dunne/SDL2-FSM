#include "../include/Events.h"

#include "../include/ClimbDownPlayerState.h"

#include "../include/ClimbPausePlayerState.h"
#include "../include/AccendLadderPlayerState.h"


PlayerState* ClimbDownPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::MOVE_DOWN_STOP_EVENT)
	{
		DEBUG_MSG("ClimbDownPlayerState -> ClimbPausePlayerState");
		return new ClimbPausePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT)
	{
		DEBUG_MSG("ClimbDownPlayerState -> AccendLadderPlayerState");
		return new AccendLadderPlayerState();
	}
	return nullptr;
}
void ClimbDownPlayerState::update(Player& player, float dt) {}
void ClimbDownPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering ClimbDownPlayerState");
	// Climb Down Animated Sprite
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(new TextureData(1608, 0, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(1890, 0, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(2172, 0, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(1608, 464, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(1890, 464, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(2172, 464, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(1608, 928, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(1890, 928, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(2172, 928, 282, 464));
	player.getAnimatedSprite().addFrame(new TextureData(1608, 1392, 282, 464));

	player.getAnimatedSprite().setTime(0.05f);

}
void ClimbDownPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting ClimbDownPlayerState");
}