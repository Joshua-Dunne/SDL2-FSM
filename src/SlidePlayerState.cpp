#include "../include/Events.h"

#include "../include/SlidePlayerState.h"

#include "../include/RunRightPlayerState.h"
#include "../include/DiedPlayerState.h"
#include "../include/IdlePlayerState.h"

PlayerState* SlidePlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT)
	{
		DEBUG_MSG("SlidePlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("SlidePlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}
void SlidePlayerState::update(Player& player, float dt) {
	// Switch from SlidePlayerState to IdlePlayerState
	// There is a fixed time at which the slide switched
	// back to IdlePlayerState....as the gameplay programmer
	// you may wish to stop the slide and have an appropriate
	// state and animation at the end of the slide
	// this was added so sliding does not go one indefinitely
	m_clock += dt;

	if (m_clock >= 2.0f) {
		DEBUG_MSG("SlidePlayerState -> IdlePlayerState");
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new IdlePlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp; // Delete previous
	}
}
void SlidePlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering SlidePlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(new TextureData(0, 5388, 373, 351));
	player.getAnimatedSprite().addFrame(new TextureData(373, 5388, 373, 351));
	player.getAnimatedSprite().addFrame(new TextureData(746, 5388, 373, 351));
	player.getAnimatedSprite().addFrame(new TextureData(0, 5739, 373, 351));
	player.getAnimatedSprite().addFrame(new TextureData(373, 5739, 373, 351));
	player.getAnimatedSprite().addFrame(new TextureData(746, 5739, 373, 351));
	player.getAnimatedSprite().addFrame(new TextureData(0, 6090, 373, 351));
	player.getAnimatedSprite().addFrame(new TextureData(373, 6090, 373, 351));
	player.getAnimatedSprite().addFrame(new TextureData(746, 6090, 373, 351));
	player.getAnimatedSprite().addFrame(new TextureData(0, 6441, 373, 351));

	player.getAnimatedSprite().setTime(0.03f);
}
void SlidePlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting SlidePlayerState");
}