#include <stdio.h>
#include "../include/Player.h"
#include "../include/Events.h"
#include "../include/IdlePlayerState.h"


Player::Player(const SDL_Texture* t) : m_animated_sprite(t)
{
	// Set the Player to Default to IdlePlayer State 
	// and Enter that State
	m_state = new IdlePlayerState();
	m_state->enter(*this);
}

void Player::handleInput(gpp::Events input) {
	PlayerState * state = m_state->handleInput(input);

	if (state != NULL) {
		m_state->exit(*this);
		delete m_state;
		m_state = state;
		m_state->enter(*this);
	}
}

void Player::update(float dt) {
	m_animated_sprite.update(dt);
	m_state->update(*this);
}

AnimatedSprite& Player::getAnimatedSprite() {
	return m_animated_sprite;
}

SDL_Texture* Player::getAnimatedSpriteFrame() {
	return m_animated_sprite.getCurrentAnimatedFrame();
}

void Player::setAnimatedSprite(AnimatedSprite& animated_sprite) {
	this->m_animated_sprite = animated_sprite;
}

PlayerState* Player::getPlayerState() { return this->m_state; }

void Player::setPlayerState(PlayerState* state) { this->m_state = state; }