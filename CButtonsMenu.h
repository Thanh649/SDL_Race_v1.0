#ifndef CButtonsMenu_h_
#define CButtonsMenu_h_
#include <SDL.h>
#ifndef CTexture_h_
#include "CTexture.h"
#endif
#ifndef CGeneral_h_
#include "CGeneral.h"
#endif
#endif

enum LButtonStatus
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER_MOTION = 1,
	BUTTON_MOUSE_DOWN = 2,
	BUTTON_MOUSE_UP = 3,
	BUTTON_TOTAL = 4
};

//Button constants
const int BUTTON_WIDTH = SCREEN_WIDTHPLUS/4;
const int BUTTON_HEIGHT = SCREEN_HEIGHTPLUS/6;
const int TOTAL_BUTTONS = 4;

//The mouse button
class LButton
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event* e );
	
		//Shows button sprite
		void render(LTexture &bTexture, SDL_Renderer* gRenderer);
		void renderEx(LTexture &bTexture, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* gRenderer);

		//Set mCurrenButton
		void setCurrent(LButtonStatus status);

		//Get mCurrentButton
		LButtonStatus getCurrent();

	private:
		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
		LButtonStatus mCurrentButton;
};

LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentButton = BUTTON_MOUSE_OUT;
}

void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}

void LButton::handleEvent( SDL_Event* e )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentButton = BUTTON_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				mCurrentButton = BUTTON_MOUSE_OVER_MOTION;
				break;
			
				case SDL_MOUSEBUTTONDOWN:
				mCurrentButton = BUTTON_MOUSE_DOWN;
				break;
				
				case SDL_MOUSEBUTTONUP:
				mCurrentButton = BUTTON_MOUSE_UP;
				break;
			}
		}
	}
}
	
void LButton::render(LTexture &bTexture, SDL_Renderer* gRenderer)
{
	//Show current button sprite
	bTexture.render( mPosition.x, mPosition.y, gRenderer );
}

void LButton::renderEx(LTexture &bTexture, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* gRenderer)
{
	bTexture.renderEx( mPosition.x, mPosition.y, clip, angle, center, flip, gRenderer);
}

void LButton::setCurrent(LButtonStatus status)
{
	this->mCurrentButton = status;
}

LButtonStatus LButton::getCurrent()
{
	return this->mCurrentButton;
}