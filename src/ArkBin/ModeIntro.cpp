#include "StdAfx.h"
#include "ModeIntro.h"
#include "ModeMenu.h"
#include "FeedbackWidget.h"

IMode* ModeIntro::Teardown()
{
	Widget::ClearRoot();
	return IMode::Teardown();
}

void ModeIntro::Setup()
{
	mLogo1 = new Widget("GameDev5Logo.png");
	mLogo1->SetPosition(Widget::GetScreenCentre() - (mLogo1->GetSize() / 2) - Vector2i(0, 64));
	mLogo1->SetRejectsFocus(true);

	Widget* betaTag = new Widget("Beta.png");
	betaTag->SetPosition(Widget::GetScreenSize() - betaTag->GetSize());

	mFeedbackWidget = new FeedbackWidget();

	//Attach callback
	mKeyCallback = Widget::OnGlobalKeyUp.connect(boost::bind(&ModeIntro::KeySkip, this, _1, _2));
	betaTag->OnClick.connect(boost::bind(&ModeIntro::clickBetaTag, this, _1));
}

ModeAction::Enum ModeIntro::Tick(float dt)
{
	if(!mFeedbackWidget->HasModal())
	{
		if(mAge > 3.0f && mPendMode == NULL)
		{
			mPendMode = new ModeMenu();
		}

		ModeAction::Enum result = IMode::Tick(dt);
		Widget::SetFade(mFade);
		return result;
	}
	Widget::SetFade(0);
	return ModeAction::NoAction;
}

ModeType::Enum ModeIntro::GetType()
{
	return ModeType::Intro;
}

void ModeIntro::Draw(SDL_Surface* screenSurface)
{
}

void ModeIntro::KeySkip(Widget* /*widget*/, KeyPressEventArgs /*key_args*/)
{
	mPendMode = new ModeMenu();
}

void ModeIntro::clickBetaTag(Widget* /*widget*/)
{
	((FeedbackWidget*)mFeedbackWidget)->Show();
}