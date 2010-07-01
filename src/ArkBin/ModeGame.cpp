#include "StdAfx.h"
#include "ModeGame.h"
#include "ModeMenu.h"
#include <Widget.h>

ModeGame::ModeGame()
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

	//Attach callback
	back->OnClick.connect(boost::bind(&ModeGame::clickBack, this, _1));
}

ModeAction::Enum ModeGame::Tick(float dt)
{
	ModeAction::Enum result = IMode::Tick(dt);
	Widget::SetFade(mFade);
	return result;
}

ModeType::Enum ModeGame::GetType()
{
	return ModeType::Game;
}

void ModeGame::Draw(SDL_Surface* screenSurface)
{
}

void ModeGame::clickBack(Widget* /*widget*/)
{
	if(!mPendMode)
		mPendMode = new ModeMenu();
}