#include "../include/AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() : 
	m_current_frame(0),
	m_time(0.5f),
	m_loop(true),
	m_played(false)
{
	DEBUG_MSG("AnimatedSprite()");
}

AnimatedSprite::AnimatedSprite(const SDL_Texture* t) : AnimatedSprite(){
	DEBUG_MSG("AnimatedSprite(const Texture&)");
}

AnimatedSprite::~AnimatedSprite() {
	DEBUG_MSG("~AnimatedSprite()");
}

// Set the time between frames
void AnimatedSprite::setTime(float t)
{
	this->m_maxTime = t;
}

const std::vector<SDL_Texture*>& AnimatedSprite::getFrames() {
	return m_frames;
}

void AnimatedSprite::clearFrames() {
	m_current_frame = 0;
	m_played = false;
	if (!m_frames.empty())
	{
		m_frames.clear();
	}
}

void AnimatedSprite::addFrame(SDL_Texture* frame) {
	m_frames.push_back(frame);
}

const int AnimatedSprite::getCurrentFrame() {
	return m_current_frame;
}

SDL_Texture* AnimatedSprite::getCurrentAnimatedFrame()
{
	return m_frames[m_current_frame];
}

void AnimatedSprite::setLooped(bool loop) {
	this->m_loop = loop;
}

const bool AnimatedSprite::getLooped() {
	return this->m_loop;
}

void AnimatedSprite::setPlayed(bool played) {
	this->m_played = played;
}

const bool AnimatedSprite::getPlayed() {
	return this->m_played;
}

void AnimatedSprite::update(float dt){
	// If not looped only play once
	if (m_played == true && !m_loop)
	{
		m_current_frame = m_frames.size() - 1;
	}
	else {
		if (m_time >= m_maxTime) {
			if (m_frames.size() > m_current_frame + 1)
			{
				m_current_frame++;
			}
			else {
				m_current_frame = 0;
				m_played = true;
			}
			m_time = 0.0f;
		}
		else {
			m_time += dt;
		}
	}
}

