#include "StdAfx.h"
#include "FeedbackWidget.h"

FeedbackWidget::FeedbackWidget(void) : 
Widget(NinePatch("NavyButton.png", 16, 16, 16, 16), Widget::GetScreenSize().x - 32, Widget::GetScreenSize().y - 32)
{
	SetTextSize(TextSize::Small);
	SetText("Feedback:\nPlease send me feedback - either type it in below and click send, or use the button to vist GitHub and leave feedback there", TextAlignment::TopLeft);
	SetRejectsFocus(true);
	SetHidesHighlight(true);
	SetVisibility(false);
	SetPosition(Vector2i(16, 16));
	SetTextWrap(true);
	
}

FeedbackWidget::~FeedbackWidget(void)
{
}
