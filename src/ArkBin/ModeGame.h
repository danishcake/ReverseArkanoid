#pragma once
#include "IMode.h"

class Widget;

/* ModeGame
 * Where the game occurs
 */
class ModeGame : 
	public IMode
{
private:
	void clickBack(Widget* /*widget*/);
public:
	ModeGame();

	virtual IMode* Teardown();
	virtual void Setup();
	virtual ModeAction::Enum Tick(float _dt);
	virtual ModeType::Enum GetType();
	virtual void Draw(SDL_Surface* screenSurface);
};
