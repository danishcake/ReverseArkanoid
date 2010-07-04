#include "stdafx.h"
#include <ctime>
#include <vmath.h>
#include <Widget.h>
#include "IMode.h"
#include "ModeIntro.h"
#include "StandardTextures.h"
#include "SDLAnimationFrame.h"

const float targetFrameTime = 0.02f;
IMode* gameMode = NULL;


SDL_Surface* SDL_init()
{
	SDL_Init(SDL_INIT_VIDEO);
	Vector2i resolution = Vector2i(640, 480);
	SDL_Surface* p_surface = SDL_SetVideoMode(resolution.x, resolution.y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(!p_surface)
	{
		Logger::ErrorOut() << "Unable to create screen surface, aborting\n";
	} else
	{
		Logger::DiagnosticOut() << "Screen surface created\n" <<
								   "Resolution = " << p_surface->w << "," << p_surface->h << "\n" <<
								   "Bitdepth = " << p_surface->format->BitsPerPixel <<"\n" <<
								   "Hardware = "  << (p_surface->flags & SDL_HWSURFACE ? "true" : "false") << "\n" <<
								   "Doublebuffered = " << (p_surface->flags & SDL_DOUBLEBUF ? "true" : "false") << "\n";				
	}

	SDL_ShowCursor(0);
	return p_surface;
}

bool GameTick(float dt)
{
	ModeAction::Enum action = gameMode->Tick(dt);
	if(action == ModeAction::ChangeMode)
	{
		IMode* pendMode = gameMode->Teardown();
		delete gameMode;
		gameMode = pendMode;
		gameMode->Setup();
	} else if(action == ModeAction::Exit)
	{
		return true;
	}
	return false;
}

void Draw(SDL_Surface* screenSurface, BlittableRect& screenRect)
{
	SDL_FillRect(screenSurface, NULL, 0);
	gameMode->Draw(screenSurface);
	Widget::RenderRoot(&screenRect);
	SDL_Flip(screenSurface);
}

int _tmain(int argc, char* argv[])
{
	bool bFinished = false;
	SDL_Surface* pScreen = SDL_init();
	BlittableRect screenRect(pScreen, true);

	for(int arg = 1; arg < argc; arg++)
	{
		Logger::DiagnosticOut() << "Command line parameter:" << argv[arg] << "\n";
		if(!strcmp("-cheat", argv[arg]))
		{

		}
	}
	
	if(pScreen)
	{
		SDLAnimationFrame::screen_ = pScreen;
		StandardTextures::LoadTextures();
		gameMode = new ModeIntro();
		gameMode->Setup();

		Widget::SetScreenSize(Vector2i(pScreen->w, pScreen->h));
	} else
	{
		bFinished = true;
	}
	
	while(!bFinished)
	{
		clock_t start_time = clock();
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				bFinished = true;
				break;
			}
			Widget::DistributeSDLEvents(&event);
		}
		
		bFinished |= GameTick(targetFrameTime);
		Draw(pScreen, screenRect);
		clock_t end_time = clock();

		float remainingTime = targetFrameTime - ((float)(end_time - start_time)) / 1000.0f;
		if(remainingTime > 0)
		{
			SDL_Delay(static_cast<int>(remainingTime * 1000));
		}
	}

	SDL_Quit();
	return 0;
}

