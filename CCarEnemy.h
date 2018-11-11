#ifndef CCarEnemy_h_
#define CCarEnemy_h_
#endif
#ifndef CGeneral_h_
#include "CGeneral.h"
#endif
#ifndef CTexture_h_
#include "CTexture.h"
#endif
#include <ctime>

class carEnemy
{
private:
	//The X and Y offsets of the car
	int mPosX, mPosY;

	//Car's collision box
	SDL_Rect mCollider;

public:
	carEnemy();

	void initCarEnemy();

	void setPosition(int x, int y);

	//Get x, y
	int getPosX();

	int getPosY();

	int moveCar( SDL_Rect& a, SDL_Rect& b );

	void renderCar(LTexture &gCarEnemy, SDL_Renderer* gRenderer);

	SDL_Rect getCollider();

	bool checkCollision( SDL_Rect a, SDL_Rect b );

};

carEnemy::carEnemy()
{
	mPosX =  mPosX_init[0];
	mPosY = ROAD_Y;

	//Set collision box dimension
	mCollider.w = CAR_WIDTH;
	mCollider.h = CAR_HEIGHT;
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}

void carEnemy::initCarEnemy()
{
	mPosX =  mPosX_init[0];
	mPosY = ROAD_Y;

	//Set collision box dimension
	mCollider.w = CAR_WIDTH;
	mCollider.h = CAR_HEIGHT;

	mCollider.x = mPosX;
	mCollider.y = mPosY;
}

void carEnemy::setPosition(int x, int y)
{
	mPosX = x;
	mPosY = y;
}

int carEnemy::getPosX()
{
	return this->mPosX;
}

int carEnemy::getPosY()
{
	return this->mPosY;
}

int carEnemy::moveCar(SDL_Rect& a, SDL_Rect& b )
{
	mPosY += Speed;
	if( mPosY > ROAD_HEIGHT){
		Score++;
		mPosX = mPosX_init[randomPos()];
		mPosY = mPosY_init[randomPos()];
	}

	mCollider.y = mPosY;
	mCollider.x = mPosX;
	
	if( checkCollision(a, b) )
	{
		return -1;
	}
	return 0;
}

void carEnemy::renderCar(LTexture &gCarEnemy, SDL_Renderer* gRenderer)
{
	gCarEnemy.render(mPosX, mPosY, gRenderer);
}

SDL_Rect carEnemy::getCollider()
{
	return this->mCollider;
}

bool carEnemy::checkCollision(SDL_Rect carEnemy, SDL_Rect carPlayer )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = carEnemy.x + CAR_WIDTH/8;
    rightA = carEnemy.x + carEnemy.w - CAR_WIDTH/8;
    topA = carEnemy.y + CAR_HEIGHT/16;
    bottomA = carEnemy.y + carEnemy.h - CAR_HEIGHT/16 ;

    //Calculate the sides of rect B
    leftB = carPlayer.x + CAR_WIDTH/8;
    rightB = carPlayer.x + carPlayer.w - CAR_WIDTH/8;
    topB = carPlayer.y + CAR_HEIGHT/16 ;
    bottomB = carPlayer.y + carPlayer.h - CAR_HEIGHT/16 ;

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
