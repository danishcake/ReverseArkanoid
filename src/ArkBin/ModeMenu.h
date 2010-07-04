#pragma once
#include "IMode.h"

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
//Private methods
private:
	void clickExit(Widget* /*widget*/);
	void clickNewGame(Widget* /*widget*/);
	void clickBetaTag(Widget* /*widget*/);
public:
	ModeMenu();

	virtual IMode* Teardown();
	virtual void Setup();
	virtual ModeAction::Enum Tick(float _dt);
	virtual ModeType::Enum GetType();
	virtual void Draw(SDL_Surface* screenSurface);
};
