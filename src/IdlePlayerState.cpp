#include "../include/Events.h"

#include "../include/IdlePlayerState.h"

#include "../include/AttackPlayerState.h"
#include "../include/ThrowAttackPlayerState.h"
#include "../include/RunRightPlayerState.h"
#include "../include/AccendLadderPlayerState.h"
#include "../include/DecendLadderPlayerState.h"
#include "../include/JumpPlayerState.h"
#include "../include/DiedPlayerState.h"

IdlePlayerState::~IdlePlayerState() {}

PlayerState* IdlePlayerState::handleInput(gpp::Events& input) {

	if (input.getCurrent() == gpp::Events::Event::ATTACK_START_EVENT)
	{
		DEBUG_MSG("IdlePlayerState -> AttackPlayerState");
		return new AttackPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::THROW_START_EVENT)
	{
		DEBUG_MSG("IdlePlayerState -> ThrowAttackPlayerState");
		return new ThrowAttackPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT) {
		DEBUG_MSG("IdlePlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT) {
		DEBUG_MSG("IdlePlayerState -> AccendLadderPlayerState");
		return new AccendLadderPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::HIT_LADDER_TOP_EVENT) {
		DEBUG_MSG("IdlePlayerState -> DecendLadderPlayerState");
		return new DecendLadderPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::JUMP_UP_EVENT) {
		DEBUG_MSG("IdlePlayerState -> JumpPlayerState");
		return new JumpPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("IdlePlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}

void IdlePlayerState::update(Player& player, float dt) {}

void IdlePlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering IdlePlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(new TextureData(3900, 0, 232, 439));
	player.getAnimatedSprite().addFrame(new TextureData(4132, 0, 232, 439));
	player.getAnimatedSprite().addFrame(new TextureData(4364, 0, 232, 439));
	player.getAnimatedSprite().addFrame(new TextureData(3900, 439, 232, 439));
	player.getAnimatedSprite().addFrame(new TextureData(4132, 439, 232, 439));
	player.getAnimatedSprite().addFrame(new TextureData(4364, 439, 232, 439));
	player.getAnimatedSprite().addFrame(new TextureData(3900, 878, 232, 439));
	player.getAnimatedSprite().addFrame(new TextureData(4132, 878, 232, 439));
	player.getAnimatedSprite().addFrame(new TextureData(4364, 878, 232, 439));
	player.getAnimatedSprite().addFrame(new TextureData(3900, 1317, 232, 439));

	player.getAnimatedSprite().setTime(0.05f);
}

void IdlePlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting IdlePlayerState");
}