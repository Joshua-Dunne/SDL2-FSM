#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <vector>
#include "../include/Debug.h"

class AnimatedSprite {
public:
	AnimatedSprite();
	AnimatedSprite(const Texture&);
	AnimatedSprite(const Texture&, const IntRect&);
	~AnimatedSprite();

	const Clock& getClock();
	const Time& getTime();
	const vector<IntRect>& getFrames();
	void clearFrames();
	const IntRect& getFrame(int);
	void addFrame(const IntRect&);
	const int getCurrentFrame();
	void setLooped(bool);
	const bool getLooped();
	void setPlayed(bool);
	const bool getPlayed();
	void setTime(Time);
	void update();
	
private:
	Clock m_clock;
	Time m_time;
	vector<IntRect> m_frames;
	unsigned int m_current_frame;
	bool m_loop;
	unsigned int m_play_count;
	unsigned int m_max_plays;
	bool m_played;
};

#endif // !ANIMATED_SPRITE_H
