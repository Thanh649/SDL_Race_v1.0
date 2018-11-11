#ifndef CCarPlayer_h_
#define CCarPlayer_h_
#endif
#ifndef CGeneral_h_
#include "CGeneral.h"
#endif
#ifndef CTexture_h_
#include "CTexture.h"
#endif

class carPlayer
{
private:
	//The X and Y offsets of the car
	int mPosX, mPosY;

	//The velocity of the car
	int mVelX, mVelY;

	//Car's collision box
	SDL_Rect mCollider;

	//check die car
	bool die;

public:
	//Maximum axis velocity of the car
	static const int CAR_VEL = 10;

	//Initializes the variables
	carPlayer();

	//Set top left x y
	void setPosition(int x, int y);

	//Get x, y
	int getPosX();

	int getPosY();

	//init car
	void initCarPlayer();

	//Takes key presses and adjusts the car's velocity
	void handleEvent( SDL_Event& e );

	//move the car
	void moveCar();

	//shows the car on the screen
	void renderCar(LTexture &gCarPlayer, SDL_Renderer* gRenderer);

	//Car collision detector
	bool checkCollision( SDL_Rect b );

	//Get die car
	bool dieCar();

	SDL_Rect getCollider();
};

carPlayer::carPlayer()
{
		//Initialize the offsets
		mPosX = mPosX_init[0];
		mPosY = ROAD_Y + SCREEN_HEIGHT - CAR_HEIGHT;

		 //Initialize the velocity
		mVelX = 0;
		mVelY = 0;

		//Set collision box dimension
		mCollider.w = CAR_WIDTH;
		mCollider.h = CAR_HEIGHT;
		mCollider.x = mPosX;
		mCollider.y = mPosY;
		//Set die car
		die = false;
}

void carPlayer::setPosition(int x, int y)
{
		this->mPosX = x;
		this->mPosY = y;
}

int carPlayer::getPosX()
{
	return this->mPosX;
}

int carPlayer::getPosY()
{
	return this->mPosY;
}

void carPlayer::initCarPlayer()
{
		//Initialize the offsets
		mPosX = mPosX_init[0];
		mPosY = ROAD_Y + SCREEN_HEIGHT - CAR_HEIGHT;

		 //Initialize the velocity
		mVelX = 0;
		mVelY = 0;

		//Set collision box dimension
		mCollider.w = CAR_WIDTH;
		mCollider.h = CAR_HEIGHT;
		mCollider.x = mPosX;
		mCollider.y = mPosY;
		//Set die car
		die = false;
}

void carPlayer::handleEvent( SDL_Event& e )
{
	//If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= CAR_VEL; break;
            case SDLK_DOWN: mVelY += CAR_VEL; break;
            case SDLK_LEFT: mVelX -= CAR_VEL; break;
            case SDLK_RIGHT: mVelX += CAR_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += CAR_VEL; break;
            case SDLK_DOWN: mVelY -= CAR_VEL; break;
            case SDLK_LEFT: mVelX += CAR_VEL; break;
            case SDLK_RIGHT: mVelX -= CAR_VEL; break;
        }
    }
}

void carPlayer::moveCar( )
{
	 //Move the car left or right
    mPosX += mVelX;
	mCollider.x = mPosX;

    //If the car went too far to the left or right
    if( ( mPosX < ROAD_X + ROADSIDE_WIDTH) || ( mPosX + CAR_WIDTH > ROAD_X + ROAD_WIDTH - ROADSIDE_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
		mCollider.x = mPosX;
    }

    //Move the car up or down
    mPosY += mVelY;
	mCollider.y = mPosY;

    //If the car went too far up or down
    if( ( mPosY < ROAD_Y ) || ( mPosY + CAR_HEIGHT > ROAD_Y + ROAD_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
		mCollider.y = mPosY;
    }
}

void carPlayer::renderCar(LTexture &gCarPlayer, SDL_Renderer* gRenderer)
{
	gCarPlayer.render(mPosX, mPosY, gRenderer);
}


bool carPlayer::checkCollision( SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = mCollider.x;
    rightA = mCollider.x + mCollider.w;
    topA = mCollider.y;
    bottomA = mCollider.y + mCollider.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool carPlayer::dieCar()
{
	return die;
}

SDL_Rect carPlayer::getCollider()
{
	return this->mCollider;
}