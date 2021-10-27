#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <vector>
#include <SDL2/SDL.h>
#include "../include/TextureData.h"
#include "../include/Debug.h"

class AnimatedSprite {
public:
	AnimatedSprite();
	AnimatedSprite(const SDL_Texture*);
	~AnimatedSprite();

	const std::vector<TextureData*>& getFrames();
	void clearFrames();
	const TextureData& getFrame(int);
	void addFrame(TextureData*);
	TextureData* getCurrentAnimatedFrame();
	const int getCurrentFrame();
	void setLooped(bool);
	const bool getLooped();
	void setPlayed(bool);
	const bool getPlayed();
	void setTime(float time);
	void update(float dt);
	
private:
	float m_maxTime;
	float m_time;
	std::vector<TextureData*> m_frames;
	unsigned int m_current_frame;
	bool m_loop;
	bool m_played;
};

#endif // !ANIMATED_SPRITE_H
