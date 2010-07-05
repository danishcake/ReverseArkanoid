#include "StdAfx.h"
#include "ModeGame.h"
#include "ModeMenu.h"
#include <Widget.h>
#include "FeedbackWidget.h"
#include "StandardTextures.h"

using std::vector;

ModeGame::ModeGame() :
	mGame(new ArkGame())
{
	Wall::SharedPointer wall(new Wall());
	Brick::SharedPointer brick(new Brick(BrickType::RedBrick));
	brick->SetPosition(Vector2f(-20, 0));
	Brick::SharedPointer brick2(new Brick(BrickType::BlueBrick));
	brick2->SetPosition(Vector2f(20, 0));
	wall->AddBrick(brick);
	wall->AddBrick(brick2);

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
	vector<Ball::SharedPointer> balls = mGame->GetBalls();
	for(vector<Ball::SharedPointer>::iterator ball = balls.begin(); ball != balls.end(); ++ball)
	{
		Vector2i inverted_y = (*ball)->GetPosition();
		inverted_y.y = 480 - (inverted_y.y + 2 * (*ball)->GetRadius());
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
				sprite = StandardTextures::red_brick_animation[0];
				break;
			case BrickType::YellowBrick:
				sprite = StandardTextures::red_brick_animation[0]; //TODO add yellow
				break;
			}

			Vector2i inverted_y = (*brick)->GetPosition() + wall->GetPosition();
			inverted_y.y = 480 - (inverted_y.y + (*brick)->GetSize().y);
			sprite->GetCurrentFrame()->Draw(inverted_y);
		}
	}
	Paddle::SharedPointer paddle = mGame->GetPaddle();
	Vector2i inverted_y = paddle->GetPosition();
	inverted_y.y = 480 - (inverted_y.y + paddle->GetSize().y);
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