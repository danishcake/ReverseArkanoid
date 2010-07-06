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
//Private members
private:
	Widget* mLogo1;
	Widget* mLogo2;
	Widget* mFeedbackWidget;
	boost::signals::scoped_connection mKeyCallback;
//Private methods
private:
	void KeySkip(Widget* /*widget*/, KeyPressEventArgs /*key_args*/);
	void clickBetaTag(Widget* /*widget*/);
public:
	virtual IMode* Teardown();
	virtual void Setup();
	virtual ModeAction::Enum Tick(float _dt);
	virtual ModeType::Enum GetType();
	virtual void Draw(SDL_Surface* screenSurface);
};
