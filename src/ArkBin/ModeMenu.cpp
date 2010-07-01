#include "StdAfx.h"
#include "ModeMenu.h"
#include "ModeGame.h"
#include <Widget.h>

ModeMenu::ModeMenu() :
	mExitClicked(false)
{
	
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
	const int btn_seperation = btn_height + 10;

	Widget* newGame = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), btn_width, btn_height);
	newGame->SetPosition(Vector2i(Widget::GetScreenCentre().x - newGame->GetSize().x / 2, Widget::GetScreenCentre().y - 2 * btn_seperation));
	newGame->SetText("New game", TextAlignment::Centre);

	Widget* loadEditor = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), btn_width, btn_height);
	loadEditor->SetPosition(Vector2i(Widget::GetScreenCentre().x - loadEditor->GetSize().x / 2, Widget::GetScreenCentre().y - btn_seperation));
	loadEditor->SetText("Editor", TextAlignment::Centre);

	Widget* showOptions = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), btn_width, btn_height);
	showOptions->SetPosition(Vector2i(Widget::GetScreenCentre().x - showOptions->GetSize().x / 2, Widget::GetScreenCentre().y));
	showOptions->SetText("Options", TextAlignment::Centre);

	Widget* exitGame = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), btn_width, btn_height);
	exitGame->SetPosition(Vector2i(Widget::GetScreenCentre().x - exitGame->GetSize().x / 2, Widget::GetScreenCentre().y + btn_seperation));
	exitGame->SetText("Exit", TextAlignment::Centre);

	Widget* betaTag = new Widget("Beta.png");
	betaTag->SetPosition(Widget::GetScreenSize() - betaTag->GetSize());

	newGame->LinkDown(loadEditor);
	loadEditor->LinkUp(newGame);
	loadEditor->LinkDown(showOptions);
	showOptions->LinkUp(loadEditor);
	showOptions->LinkDown(exitGame);
	exitGame->LinkUp(showOptions);

	//Attach callback
	exitGame->OnClick.connect(boost::bind(&ModeMenu::clickExit, this, _1));
	newGame->OnClick.connect(boost::bind(&ModeMenu::clickNewGame, this, _1));
}

ModeAction::Enum ModeMenu::Tick(float dt)
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

ModeType::Enum ModeMenu::GetType()
{
	return ModeType::Menu;
}

void ModeMenu::Draw(SDL_Surface* screenSurface)
{
}

void ModeMenu::clickExit(Widget* /*widget*/)
{
	if(!mExitClicked)
		mAge = mPendTime;
	mExitClicked = true;
}

void ModeMenu::clickNewGame(Widget* /*widget*/)
{
	if(!mPendMode)
		mPendMode = new ModeGame();
}