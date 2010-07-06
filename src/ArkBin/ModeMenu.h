#pragma once
#include "IMode.h"
#include <Wall.h>
#include <vector>

class Widget;

/* ModeMenu
 * Provides list
 * New Game, Editor, Options, Exit Game
 */
class ModeMenu : 
	public IMode
{
//Private members
private:
	bool mExitClicked;
	Widget* mFeedbackWidget;
	Wall::SharedPointer mWall;
	std::vector<std::string> mLevels;
	int mLevelIndex;

//Private methods
private:
	void clickExit(Widget* /*widget*/);
	void clickNewGame(Widget* /*widget*/);
	void clickBetaTag(Widget* /*widget*/);

	void clickNextLevel(Widget* /*widget*/);
	void clickPrevLevel(Widget* /*widget*/);

	void findLevels();
	void loadLevel();
public:
	ModeMenu();

	virtual IMode* Teardown();
	virtual void Setup();
	virtual ModeAction::Enum Tick(float _dt);
	virtual ModeType::Enum GetType();
	virtual void Draw(SDL_Surface* screenSurface);
};
