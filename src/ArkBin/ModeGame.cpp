#include "StdAfx.h"
#include "ModeGame.h"
#include "ModeMenu.h"
#include <Widget.h>
#include "FeedbackWidget.h"
#include "StandardTextures.h"

using std::vector;

ModeGame::ModeGame(std::string filename) :
	mGame(new ArkGame())
{
	Wall::SharedPointer wall(new Wall(filename));
	mGame->SetWall(wall);
}

IMode* ModeGame::Teardown()
{
	Widget::ClearRoot();
	return IMode::Teardown();
}

void ModeGame::Setup()
{
	Widget* back = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), 96, 32);
	back->SetPosition(Vector2i(4, Widget::GetScreenSize().y - back->GetSize().y - 4));
	back->SetText("Back", TextAlignment::Centre);

	Widget* betaTag = new Widget("Beta.png");
	betaTag->SetPosition(Widget::GetScreenSize() - betaTag->GetSize());

	mFeedbackWidget = new FeedbackWidget();

	//Attach callback
	mMouseMoveKeyback = Widget::OnGlobalMouseMove.connect(boost::bind(&ModeGame::mouseMove, this, _1, _2));
	back->OnClick.connect(boost::bind(&ModeGame::clickBack, this, _1));
	betaTag->OnClick.connect(boost::bind(&ModeGame::clickBetaTag, this, _1));
}

ModeAction::Enum ModeGame::Tick(float dt)
{
	if(!mFeedbackWidget->HasModal())
	{
		mGame->Tick(dt);

		ModeAction::Enum result = IMode::Tick(dt);
		Widget::SetFade(mFade);
		return result;
	}
	Widget::SetFade(0);
	return ModeAction::NoAction;
}

ModeType::Enum ModeGame::GetType()
{
	return ModeType::Game;
}

void ModeGame::Draw(SDL_Surface* screenSurface)
{
	StandardTextures::background_animation->GetFrameByIndex(0)->Draw(Vector2f(0, 0));

	vector<Ball::SharedPointer> balls = mGame->GetBalls();
	for(vector<Ball::SharedPointer>::iterator ball = balls.begin(); ball != balls.end(); ++ball)
	{
		const std::deque<Vector2f> trail = (*ball)->GetTrail();
		int frame = 0;
		for(std::deque<Vector2f>::const_iterator it = trail.begin(); it != trail.end(); ++it)
		{
			Vector2i trail_inverted_y = *it;
			trail_inverted_y .y = 480 - trail_inverted_y.y;
			StandardTextures::ball_trail_animation->GetFrameByIndex(frame++)->Draw(trail_inverted_y);
		}

		Vector2i inverted_y = ArkGame::BallToGame(*ball);
		inverted_y.y = 480 - inverted_y.y;
		StandardTextures::ball_animation->GetCurrentFrame()->Draw(inverted_y);
	}
	if(mGame->GetWall().get())
	{
		Wall::SharedPointer wall = mGame->GetWall();
		vector<Brick::SharedPointer> bricks = wall->GetBricks();
		for(vector<Brick::SharedPointer>::iterator brick = bricks.begin(); brick != bricks.end(); ++brick)
		{
			Animation* sprite;
			switch((*brick)->GetBrickType())
			{
			default:
			case BrickType::BlueBrick:
				sprite = StandardTextures::blue_brick_animation[0];
				break;
			case BrickType::RedBrick:
				sprite = StandardTextures::red_brick_animation[(*brick)->GetLives() - 1];
				break;
			case BrickType::YellowBrick:
				sprite = StandardTextures::yellow_brick_animation[(*brick)->GetLives() - 1];
				break;
			}

			Vector2i inverted_y = ArkGame::BrickToGame(*brick, wall);
			inverted_y.y = 480 - inverted_y.y;
			sprite->GetCurrentFrame()->Draw(inverted_y);
		}
	}
	Paddle::SharedPointer paddle = mGame->GetPaddle();
	Vector2i inverted_y = ArkGame::PaddleToGame(paddle);
	inverted_y.y = 480 - inverted_y.y;
	StandardTextures::paddle_animation->GetCurrentFrame()->Draw(inverted_y);
}

void ModeGame::clickBack(Widget* /*widget*/)
{
	if(!mPendMode)
		mPendMode = new ModeMenu();
}

void ModeGame::clickBetaTag(Widget* /*widget*/)
{
	((FeedbackWidget*)mFeedbackWidget)->Show();
}

void ModeGame::mouseMove(Widget* /*widget*/, MouseEventArgs args)
{
	Wall::SharedPointer wall = mGame->GetWall();
	if(wall.get())
	{
		Vector2f offset((Widget::GetScreenSize().x - wall->GetBounds().x) / 2 + 2 * Brick::BRICK_WIDTH, 0);
		wall->SetX(args.x - offset.x);
	}
}