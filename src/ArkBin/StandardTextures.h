
#include <Animation.h>
#include <AnimationFrame.h>
namespace StandardTextures
{
	extern Animation* ball_animation;
	extern Animation* ball_trail_animation;
	extern Animation* red_brick_animation[2];
	extern Animation* blue_brick_animation[2];
	extern Animation* yellow_brick_animation[3];
	extern Animation* paddle_animation;


	//Load textures
	void LoadTextures();
	//Advances animation
	void TickAnimations(float dt);
}