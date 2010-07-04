#include "StdAfx.h"
#include "ModeGame.h"
#include "ModeMenu.h"
#include <Widget.h>
#include "FeedbackWidget.h"

using std::vector;

ModeGame::ModeGame() :
	mGame(new ArkGame())
{
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

	}
	if(mGame->GetWall().get())
	{
		vector<Brick::SharedPointer> bricks = mGame->GetWall()->GetBricks();
		for(vector<Brick::SharedPointer>::iterator brick = bricks.begin(); brick != bricks.end(); ++brick)
		{

		}
	}
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