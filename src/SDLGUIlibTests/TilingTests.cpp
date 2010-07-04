#include "stdafx.h"
#include <Widget.h>

TEST_FIXTURE(SDL_fixture, VerticalTile)
{
	CHECK(SDL_init_ok);
	if(SDL_init_ok)
	{
		VerticalTile vt("Top.png", "Middle.png", "Bottom.png");
		CHECK_EQUAL("Top.png", vt.top);
		CHECK_EQUAL("Middle.png", vt.middle);
		CHECK_EQUAL("Bottom.png", vt.bottom);
		CHECK_EQUAL(TilingType::Vertical, vt.type);

		Widget* tiled = new Widget(vt, 100);
		CHECK(tiled);
	}
}

TEST_FIXTURE(SDL_fixture, HorizontalTile)
{
	CHECK(SDL_init_ok);
	if(SDL_init_ok)
	{
		HorizontalTile ht("Left.png", "Middle.png", "Right.png");
		CHECK_EQUAL("Left.png", ht.left);
		CHECK_EQUAL("Middle.png", ht.middle);
		CHECK_EQUAL("Right.png", ht.right);
		CHECK_EQUAL(TilingType::Horizontal, ht.type);

		Widget* tiled = new Widget(ht, 100);
		CHECK(tiled);
	}
}

TEST_FIXTURE(SDL_fixture, NinePatch)
{
	CHECK(SDL_init_ok);
	if(SDL_init_ok)
	{
		NinePatch np("NavyButton.png", 1, 2, 3, 4);

		CHECK_EQUAL("NavyButton.png", np.image);
		CHECK_EQUAL(1, np.top);
		CHECK_EQUAL(2, np.left);
		CHECK_EQUAL(3, np.bottom);
		CHECK_EQUAL(4, np.right);
	}
}

TEST_FIXTURE(SDL_fixture, MissingFilesReportError)
{
	CHECK(SDL_init_ok);
	if(SDL_init_ok)
	{
	}
}
