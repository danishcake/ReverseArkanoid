#pragma once
#include <Widget.h>

class FeedbackWidget :
	public Widget
{
private:
	void backClick(Widget* /*widget*/);
	void emailClick(Widget* /*widget*/);
	void threadClick(Widget* /*widget*/);
	void githubClick(Widget* /*widget*/);

	Vector2i mCentredPosition;
	Vector2f mOffscreenPosition;
public:
	FeedbackWidget(void);
	virtual ~FeedbackWidget(void);

	void Show();
};
