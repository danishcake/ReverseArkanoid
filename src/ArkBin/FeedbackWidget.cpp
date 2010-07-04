#include "StdAfx.h"
#include "FeedbackWidget.h"

FeedbackWidget::FeedbackWidget(void) : 
	Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), Widget::GetScreenSize().x - 32, Widget::GetScreenSize().y - 32),
	mCentredPosition(16, 16)
{
	SetTextSize(TextSize::Small);
	SetText("Feedback:\nPlease send me feedback - use the button to vist GitHub and leave feedback there, or launch your email client. Alternatively leave feedback in the Something Awful Game Development thread", TextAlignment::TopLeft);
	SetRejectsFocus(true);
	SetHidesHighlight(true);
	SetVisibility(false);
	
	mOffscreenPosition = size_ * -1;
	SetPosition(mOffscreenPosition);
	SetTextWrap(true);
	SetMargins(6, 6, 8, 6);

	Widget* git_hub = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), 256, 32);
	git_hub->SetText("GitHub", TextAlignment::Centre);
	git_hub->SetPosition(Widget::GetScreenCentre() - git_hub->GetSize()/2 - Vector2i(0, 64));
	AddChild(git_hub);

	Widget* email = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), 256, 32);
	email->SetText("Email", TextAlignment::Centre);
	email->SetPosition(Widget::GetScreenCentre() - git_hub->GetSize()/2 - Vector2i(0, 16));
	AddChild(email);

	Widget* thread = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), 256, 32);
	thread->SetText("Thread", TextAlignment::Centre);
	thread->SetPosition(Widget::GetScreenCentre() - git_hub->GetSize()/2 + Vector2i(0, 32));
	AddChild(thread);


	Widget* back_button = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), 96, 32);
	back_button->SetText("Back", TextAlignment::Centre);
	back_button->SetPosition(Vector2i(16, size_.y - back_button->GetSize().y - 16));
	AddChild(back_button);

	//Register events
	back_button->OnClick.connect(boost::bind(&FeedbackWidget::backClick, this, _1));
}

FeedbackWidget::~FeedbackWidget(void)
{
}

void FeedbackWidget::backClick(Widget* /*widget*/)
{
	SetModal(false);
	SetVisibility(false);
	SetPosition(mOffscreenPosition);
}

void FeedbackWidget::Show()
{
	SetModal(true);
	SetVisibility(true);
	SetPosition(mCentredPosition);
}