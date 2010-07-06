#include "StdAfx.h"
#include "ModeMenu.h"
#include "ModeGame.h"
#include <Widget.h>
#include "FeedbackWidget.h"
#include "StandardTextures.h"
#include <boost/filesystem.hpp>

ModeMenu::ModeMenu() :
	mExitClicked(false),
	mLevelIndex(0)
{
	findLevels();
	loadLevel();
}

IMode* ModeMenu::Teardown()
{
	Widget::ClearRoot();
	return IMode::Teardown();
}

void ModeMenu::Setup()
{
	const int btn_width = 160;
	const int btn_height = 40;
	const int btn_border = 10;

	Widget* newGame = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), btn_width, btn_height);
	newGame->SetPosition(Vector2i(Widget::GetScreenCentre().x - newGame->GetSize().x / 2, btn_border));
	newGame->SetText("New game", TextAlignment::Centre);

	Widget* scrollRight = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), btn_height, btn_height);
	scrollRight->SetPosition(newGame->GetPosition() + Vector2i(newGame->GetSize().x + btn_border, 0));
	scrollRight->SetText(">", TextAlignment::Centre);

	Widget* scrollLeft = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), btn_height, btn_height);
	scrollLeft->SetPosition(newGame->GetPosition() - Vector2i(scrollLeft->GetSize().x + btn_border, 0));
	scrollLeft->SetText("<", TextAlignment::Centre);

	Widget* loadEditor = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), btn_width, btn_height);
	loadEditor->SetPosition(Vector2i(btn_border, Widget::GetScreenSize().y - btn_height - btn_border));
	loadEditor->SetText("Editor", TextAlignment::Centre);

	Widget* showOptions = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), btn_width, btn_height);
	showOptions->SetPosition(Vector2i(btn_border * 2 + btn_width, Widget::GetScreenSize().y - btn_height - btn_border));
	showOptions->SetText("Options", TextAlignment::Centre);

	Widget* exitGame = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), btn_width, btn_height);
	exitGame->SetPosition(Vector2i(btn_border * 3 + btn_width * 2, Widget::GetScreenSize().y +  - btn_height - btn_border));
	exitGame->SetText("Exit", TextAlignment::Centre);

	Widget* betaTag = new Widget("Beta.png");
	betaTag->SetPosition(Widget::GetScreenSize() - betaTag->GetSize());

	mFeedbackWidget = new FeedbackWidget();

	
	scrollLeft->LinkDown(showOptions);
	scrollLeft->LinkRight(newGame);
	newGame->LinkLeft(scrollLeft);
	newGame->LinkDown(showOptions);
	newGame->LinkRight(scrollRight);
	scrollRight->LinkLeft(newGame);
	scrollRight->LinkDown(showOptions);
	loadEditor->LinkUp(newGame);
	loadEditor->LinkRight(showOptions);
	showOptions->LinkLeft(loadEditor);
	showOptions->LinkUp(newGame);
	showOptions->LinkRight(exitGame);
	exitGame->LinkLeft(showOptions);
	exitGame->LinkUp(newGame);

	//Attach callback
	exitGame->OnClick.connect(boost::bind(&ModeMenu::clickExit, this, _1));
	newGame->OnClick.connect(boost::bind(&ModeMenu::clickNewGame, this, _1));
	betaTag->OnClick.connect(boost::bind(&ModeMenu::clickBetaTag, this, _1));
	scrollRight->OnClick.connect(boost::bind(&ModeMenu::clickNextLevel, this, _1));
	scrollLeft->OnClick.connect(boost::bind(&ModeMenu::clickPrevLevel, this, _1));

}

void ModeMenu::findLevels()
{
	/* Load a list of campaigns */
	mLevels.clear();
	boost::filesystem::directory_iterator end_itr;	
	for(boost::filesystem::directory_iterator itr = boost::filesystem::directory_iterator("./Levels");
		itr != end_itr;
		++itr)
	{
		if(boost::filesystem::is_regular((itr->status())))
		{
			std::string ext = boost::filesystem::extension(*itr);
			if(ext == ".Level")
			{
				mLevels.push_back(itr->path().leaf());
			}
		}
	}
}

void ModeMenu::loadLevel()
{
	if(mLevelIndex < mLevels.size())
	{
		std::string filename = mLevels[mLevelIndex];
		mWall = Wall::SharedPointer(new Wall(filename));
		//Wall should go in middle of play area relative to left
		//So move left edge so that middle of wall in centre
		//eg left = -5, right = 25 -> middle = 10, so position should be -10 + centre position
		mWall->SetX(mWall->GetBounds().x / 2 - (mWall->GetRightEdge() + mWall->GetLeftEdge()) / 2);
		mWall->SetY(400 - mWall->GetTopEdge());
	} //TODO else show 'no levels found'
}

ModeAction::Enum ModeMenu::Tick(float dt)
{
	if(!mFeedbackWidget->HasModal())
	{
		ModeAction::Enum result = IMode::Tick(dt);
		if(!mExitClicked)
		{
			Widget::SetFade(mFade);
		} else
		{
			Widget::SetFade((mAge - mPendTime) / mPendTime);
			if(mAge - mPendTime >= mPendTime)
				result = ModeAction::Exit;
		}
		return result;
	}
	Widget::SetFade(0);
	return ModeAction::NoAction;
}

ModeType::Enum ModeMenu::GetType()
{
	return ModeType::Menu;
}

void ModeMenu::Draw(SDL_Surface* screenSurface)
{
	if(mWall.get())
	{
		Vector2f offset((Widget::GetScreenSize().x - mWall->GetBounds().x) / 2, 0);

		vector<Brick::SharedPointer> bricks = mWall->GetBricks();
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

			Vector2i inverted_y = (*brick)->GetPosition() + mWall->GetPosition() + offset;
			inverted_y.y = 480 - (inverted_y.y + (*brick)->GetSize().y);
			sprite->GetCurrentFrame()->Draw(inverted_y);
		}
	}
}

void ModeMenu::clickExit(Widget* /*widget*/)
{
	if(!mExitClicked)
		mAge = mPendTime;
	mExitClicked = true;
}

void ModeMenu::clickNewGame(Widget* /*widget*/)
{
	if(!mPendMode && mLevelIndex < mLevels.size())
		mPendMode = new ModeGame(mLevels[mLevelIndex]);
}

void ModeMenu::clickNextLevel(Widget* /*widget*/)
{
	if(mLevels.size() > 0)
	{
		mLevelIndex++;
		mLevelIndex %= mLevels.size();
		loadLevel();
	}
}

void ModeMenu::clickPrevLevel(Widget* /*widget*/)
{
	if(mLevels.size() > 0)
	{
		mLevelIndex--;
		if(mLevelIndex < 0)
			mLevelIndex = mLevels.size() - 1;
		loadLevel();
	}
}

void ModeMenu::clickBetaTag(Widget* /*widget*/)
{
	((FeedbackWidget*)mFeedbackWidget)->Show();
}