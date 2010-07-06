#include "stdafx.h"
#include "StandardTextures.h"
#include <AnimationSet.h>
#include "SDLTextureManager.h"
#include <Logger.h>
#include <Animation.h>
#include <SDL.h>
#include "SDLAnimationFrame.h"
#include <boost/lexical_cast.hpp>

namespace StandardTextures
{
	Animation* ball_animation = 0;
	Animation* red_brick_animation[2] = {0, 0};
	Animation* blue_brick_animation[2] = {0, 0};
	Animation* yellow_brick_animation[3] = {0, 0, 0};
	Animation* paddle_animation = 0;
	Animation* ball_trail_animation = 0;

	void LoadTextures()
	{
		TextureManager::SetTextureManager(new SDLTextureManager());

		AnimationSet* ball_animation_set = SDLTextureManager::GetAnimationSet("Ball.animation");
		if(ball_animation_set)
		{
			ball_animation = ball_animation_set->GetAnimation("Ball");
			if(!ball_animation )
			{
				Logger::ErrorOut() << "Unable to load ball animation\n";
			}

			ball_trail_animation = ball_animation_set->GetAnimation("Trail");
			if(!ball_trail_animation )
			{
				Logger::ErrorOut() << "Unable to load ball trail animation\n";
			}
		} else
		{
			Logger::ErrorOut() << "Unable to load ball animations\n";
		}

		AnimationSet* blue_brick_animation_set = SDLTextureManager::GetAnimationSet("BlueBrick.animation");
		if(blue_brick_animation_set)
		{
			blue_brick_animation[0] = blue_brick_animation_set->GetAnimation("Brick");
			if(!blue_brick_animation[0])
				Logger::ErrorOut() << "Unable to load blue brick undamaged animation\n";
			blue_brick_animation[1] = blue_brick_animation_set->GetAnimation("BrickDamaged");
			if(!blue_brick_animation[1])
				Logger::ErrorOut() << "Unable to load blue brick damaged animation\n";
		} else
		{
			Logger::ErrorOut() << "Unable to load blue brick animations\n";
		}

		AnimationSet* red_brick_animation_set = SDLTextureManager::GetAnimationSet("RedBrick.animation");
		if(red_brick_animation_set)
		{
			red_brick_animation[1] = red_brick_animation_set->GetAnimation("Brick");
			if(!red_brick_animation[1])
				Logger::ErrorOut() << "Unable to load red brick undamaged animation\n";
			red_brick_animation[0] = red_brick_animation_set->GetAnimation("BrickDamaged");
			if(!red_brick_animation[0])
				Logger::ErrorOut() << "Unable to load red brick damaged animation\n";
		} else
		{
			Logger::ErrorOut() << "Unable to load red brick animations\n";
		}

		AnimationSet* yellow_brick_animation_set = SDLTextureManager::GetAnimationSet("YellowBrick.animation");
		if(yellow_brick_animation_set)
		{
			yellow_brick_animation[2] = yellow_brick_animation_set->GetAnimation("Brick");
			if(!yellow_brick_animation[2])
				Logger::ErrorOut() << "Unable to load yellow brick undamaged animation\n";
			yellow_brick_animation[1] = yellow_brick_animation_set->GetAnimation("BrickDamaged");
			if(!yellow_brick_animation[1])
				Logger::ErrorOut() << "Unable to load yellow brick damaged animation\n";
			yellow_brick_animation[0] = yellow_brick_animation_set->GetAnimation("BrickDamaged2");
			if(!yellow_brick_animation[0])
				Logger::ErrorOut() << "Unable to load yellow brick damaged 2 animation\n";

		} else
		{
			Logger::ErrorOut() << "Unable to load yellow brick animations\n";
		}

		AnimationSet* paddle_animation_set = SDLTextureManager::GetAnimationSet("Paddle.animation");
		if(paddle_animation_set )
		{
			paddle_animation = paddle_animation_set->GetAnimation("Paddle");
			if(!paddle_animation)
				Logger::ErrorOut() << "Unable to load paddle animation\n";
		} else
		{
			Logger::ErrorOut() << "Unable to load paddle animations\n";
		}
	}

	void TickAnimations(float _dt)
	{
		if(ball_animation)
			ball_animation->Tick(_dt);

		if(paddle_animation)
			paddle_animation->Tick(_dt);
		for(int i = 0; i < 2; i++)
		{
			if(red_brick_animation[i])
				red_brick_animation[i]->Tick(_dt);
			if(blue_brick_animation[i])
				blue_brick_animation[i]->Tick(_dt);
		}
	}
}