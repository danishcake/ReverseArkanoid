#include "StdAfx.h"
#include "FeedbackWidget.h"

FeedbackWidget::FeedbackWidget(void) : 
	Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), Widget::GetScreenSize().x - 32, Widget::GetScreenSize().y - 32),
	mCentredPosition(16, 16)
{
	SetTextSize(TextSize::Small);
	SetText("Feedback:\nPlease send me feedback - either type it in below and click send, or use the button to vist GitHub and leave feedback there", TextAlignment::TopLeft);
	SetRejectsFocus(true);
	SetHidesHighlight(true);
	SetVisibility(false);
	
	mOffscreenPosition = size_ * -1;
	SetPosition(mOffscreenPosition);
	SetTextWrap(true);
	SetMargins(6, 6, 8, 6);
	
	Widget* back_button = new Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), 96, 32);
	back_button->SetText("Back", TextAlignment::Centre);
	back_button->SetPosition(size_ - back_button->GetSize() - Vector2i(16, 16));
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