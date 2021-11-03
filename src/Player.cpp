#include <stdio.h>
#include "../include/Player.h"
#include "../include/Events.h"
#include "../include/IdlePlayerState.h"


Player::Player()
{
	// Set the Player to Default to IdlePlayer State
	// and Enter that State
	m_state = new IdlePlayerState();
	m_state->enter(*this);
}

Player::Player(Vector2 t_pos) : m_pos(t_pos)
{
	// Set the Player to Default to IdlePlayer State
	// and Enter that State
	m_state = new IdlePlayerState();
	m_state->enter(*this);
}

void Player::handleInput(gpp::Events input) {
	PlayerState * state = m_state->handleInput(input);

	if (state != NULL) {

		if(input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT){
			m_runningRight = true;
		} else if( input.getCurrent() == gpp::Events::Event::RUN_RIGHT_STOP_EVENT){
			m_runningRight = false;
		}

		m_state->exit(*this);
		delete m_state;
		m_state = state;
		m_state->enter(*this);
	}
}

void Player::update(float dt) {
	m_animated_sprite.update(dt);
	m_state->update(*this, dt);

	if(m_runningRight)
	{
		move(Vector2(m_speed * dt, 0));
	}
}

AnimatedSprite& Player::getAnimatedSprite() {
	return m_animated_sprite;
}

TextureData* Player::getAnimatedSpriteFrame() {
	return m_animated_sprite.getCurrentAnimatedFrame();
}

void Player::setAnimatedSprite(AnimatedSprite& animated_sprite) {
	this->m_animated_sprite = animated_sprite;
}

PlayerState* Player::getPlayerState() { return this->m_state; }

void Player::setPlayerState(PlayerState* state) { this->m_state = state; }

void Player::move(Vector2 t_dir) {

	m_pos = m_pos + t_dir;
}