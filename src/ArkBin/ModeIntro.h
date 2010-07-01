#pragma once
#include "IMode.h"
#include <vmath.h>
#include <boost/signal.hpp>
#include <Widget.h>

/* ModeIntro
 * Displays logo for SAGameDev5 and then title
 * Any keypress or mouse click will skip
 */
class ModeIntro : 
	public IMode
{
private:
	void MouseSkip(Widget* /*_widget*/, MouseEventArgs /*mouse_args*/);
	void KeySkip(Widget* /*widget*/, KeyPressEventArgs /*key_args*/);
	Widget* mLogo1;
	Widget* mLogo2;
public:
	virtual IMode* Teardown();
	virtual void Setup();
	virtual ModeAction::Enum Tick(float _dt);
	virtual ModeType::Enum GetType();
	virtual void Draw(SDL_Surface* screenSurface);
};
