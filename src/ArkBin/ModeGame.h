#pragma once
#include "IMode.h"
#include <ArkGame.h>
#include <Widget.h>

class Widget;

/* ModeGame
 * Where the game occurs
 */
class ModeGame : 
	public IMode
{
//Private members
private:
	ArkGame::SharedPointer mGame;
	Widget* mFeedbackWidget;
	boost::signals::scoped_connection mMouseMoveKeyback;
//Private methods
private:
	void clickBack(Widget* /*widget*/);
	void clickBetaTag(Widget* /*widget*/);
	void mouseMove(Widget* /*widget*/, MouseEventArgs args);
	
public:
	ModeGame(std::string filename);

	virtual IMode* Teardown();
	virtual void Setup();
	virtual ModeAction::Enum Tick(float _dt);
	virtual ModeType::Enum GetType();
	virtual void Draw(SDL_Surface* screenSurface);
};
