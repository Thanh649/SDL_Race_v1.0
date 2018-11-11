#include <iostream>
#include <sstream>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <SDL_mixer.h>
#include <string>
#include <time.h>
#include "Utility.h"

#ifndef CWindow_h_
#include "CWindow.h"
#endif
#ifndef CButtonsMenu_h_
#include "CButtonsMenu.h"
#endif
#ifndef CTexture_h_
#include "CTexture.h"
#endif
#ifndef CCarPlayer_h_
#include "CCarPlayer.h"
#endif
#ifndef CCarEnemy_h_
#include "CCarEnemy.h"
#endif
#ifndef CGeneral_h_
#include "CGeneral.h"
#endif

using namespace std;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Resize window render
void resizeWindow();

//Our custom window
LWindow gWindow;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Scene textures
LTexture gScore;

//LTexture
LTexture gRoad;
LTexture gCarPlayer;
LTexture gCarEnemy[MAX_ENEMY];
LTexture gBackGround;
LTexture gBackGroundMenu;
LTexture gTextureButtons[4];

//event Button
LButton gButtons[4];

//The music that will be played
Mix_Music *gMusic = NULL;
Mix_Music *gMusicMenu = NULL;

//Class CarPlayer
carPlayer pCarPlayer;

//Class CarEnemy
carEnemy pCarEnemy[MAX_ENEMY];

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		if( !gWindow.init(SCREEN_WIDTHPLUS, SCREEN_HEIGHTPLUS ) )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = gWindow.createRenderer();
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}

				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	
	//Load Button' texture
	if( !gTextureButtons[0].loadFromFile( "picture/button_start.png", gRenderer )){
		printf( "Failed to load Button' texture image!\n" );
		success = false;
	}

	if( !gTextureButtons[1].loadFromFile( "picture/button_score.png", gRenderer )){
		printf( "Failed to load Button' texture image!\n" );
		success = false;
	}

	if( !gTextureButtons[2].loadFromFile( "picture/button_exit.png", gRenderer )){
		printf( "Failed to load Button' texture image!\n" );
		success = false;
	}

	//Load music
	gMusic = Mix_LoadMUS( "sound/03ptalit.mid" );
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gMusicMenu = Mix_LoadMUS( "sound/1_rosann.mid" );
	if( gMusicMenu == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Load BackGround menu
	if( !gBackGroundMenu.loadFromFile( "picture/backGroundMenu.png", gRenderer )){
		printf( "Failed to load backGroundMenu' texture image!\n" );
		success = false;
	}

	//Load background
	if( !gBackGround.loadFromFile( "picture/background_01.png", gRenderer ) )
	{
		printf( "Failed to load background_01 texture!\n" );
		success = false;
	}

	//Load car enemy texture
	if( !gCarEnemy[0].loadFromFile( "picture/CarPolice.png", gRenderer ) )
	{
		printf( "Failed to load gCarEnemy[0] texture!\n" );
		success = false;
	}

	if( !gCarEnemy[1].loadFromFile( "picture/Car_1_01.png", gRenderer ) )
	{
		printf( "Failed to load gCarEnemy[1] texture!\n" );
		success = false;
	}

	if( !gCarEnemy[2].loadFromFile( "picture/Car_2_01.png", gRenderer ) )
	{
		printf( "Failed to load gCarEnemy[2] texture!\n" );
		success = false;
	}

	if( !gCarEnemy[3].loadFromFile( "picture/Car_3_01.png", gRenderer ) )
	{
		printf( "Failed to load gCarEnemy[3] texture!\n" );
		success = false;
	}

	if( !gCarEnemy[4].loadFromFile( "picture/CarPlayer.png", gRenderer ) )
	{
		printf( "Failed to load gCarEnemy[5] texture!\n" );
		success = false;
	}

	//Load background texture
	if( !gRoad.loadFromFile( "picture/Road.png", gRenderer ) )
	{
		printf( "Failed to load gRoad texture!\n" );
		success = false;
	}

	//Load car player texture
	if( !gCarPlayer.loadFromFile( "picture/CarPlayer.png", gRenderer ) )
	{
		printf( "Failed to load gCarPlayer texture!\n" );
		success = false;
	}

	//font
	gFont = TTF_OpenFont( "font/VnArial.TTF", 100 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	//Nothing to load
	return success;
}

void close()
{
	//Free the music
	Mix_FreeMusic( gMusic );
	gMusic = NULL;

	Mix_FreeMusic( gMusicMenu );
	gMusicMenu = NULL;

	//Destroy texture
	gBackGroundMenu.free();
	gBackGround.free();
	gRoad.free();
	gCarPlayer.free();
	for(int i = 0; i < MAX_ENEMY; i++)
		gCarEnemy[i].free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	gWindow.free();
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void resizeWindow()
{
	int mPosX_resize;
	int mPosY_resize;
	SCREEN_WIDTHPLUS	= gWindow.getWidth(); 
	SCREEN_HEIGHTPLUS	= gWindow.getHeight();
	FACTOR = gWindow.getWidth() / MUL_SCREEN_WIDTH;
	mPosX_resize = pCarPlayer.getPosX()*(16 * FACTOR)/SCREEN_WIDTH;
	mPosY_resize = pCarPlayer.getPosY()*(9 * FACTOR)/SCREEN_HEIGHT;
	pCarPlayer.setPosition(mPosX_resize, mPosY_resize);
	for(int i = 0; i < MAX_ENEMY; i++)
	{
		mPosX_resize = pCarEnemy[i].getPosX()*(16 * FACTOR)/SCREEN_WIDTH;
		mPosY_resize = pCarEnemy[i].getPosY()*(9 * FACTOR)/SCREEN_HEIGHT;
		pCarEnemy[i].setPosition(mPosX_resize, mPosY_resize);
	}
	SCREEN_WIDTH		= 16 * FACTOR;
	SCREEN_HEIGHT		= 9 * FACTOR;
	//width, height road
	ROAD_WIDTH		= SCREEN_WIDTH/2;
	ROAD_HEIGHT		= SCREEN_HEIGHT;

	//roadside
	ROADSIDE_WIDTH	= ROAD_WIDTH/8;

	//roadway
	ROADWAY_WIDTH	= (ROAD_WIDTH - 2 * ROADSIDE_WIDTH);

	//x, y road top left
	ROAD_X			= SCREEN_WIDTH/4;
	ROAD_Y			= 0;

	//width, height car
	CAR_WIDTH		= ROAD_WIDTH/8;
	CAR_HEIGHT		= ROAD_HEIGHT/6;
	
}

bool conditionPositionCar()
{
	if((pCarEnemy[0].getPosX() == pCarEnemy[1].getPosX()) && (pCarEnemy[1].getPosX() == pCarEnemy[2].getPosX()) && (pCarEnemy[2].getPosX() == pCarEnemy[3].getPosX()))
		return false;
	/*for(int i = 0; i < MAX_ENEMY-1; i++)
		for( int j = i+1; j < MAX_ENEMY; j++)
			if((pCarEnemy[i].getPosY() + CAR_HEIGHT) > pCarEnemy[j].getPosY())
				return false;*/
	return true;
}

void DrawMenu()
{
	gBackGroundMenu.setHeight(SCREEN_HEIGHT);
	gBackGroundMenu.setWidth(SCREEN_WIDTH);
	gBackGroundMenu.render(SCREEN_WIDTH_X, SCREEN_HEIGHT_Y, gRenderer);

	for(int i = 0; i < TOTAL_BUTTONS - 1; i++){
		gTextureButtons[i].setHeight(SCREEN_HEIGHTPLUS/6);
		gTextureButtons[i].setWidth(SCREEN_WIDTH/4);
		gButtons[i].setPosition(SCREEN_WIDTH_X + SCREEN_WIDTH/2 - gTextureButtons[i].getWidth()/2, SCREEN_HEIGHT_Y + SCREEN_HEIGHTPLUS/3 + gTextureButtons[i].getHeight()*i);
		gTextureButtons[i].setColor(255, 255, 255);
	}
	gTextureButtons[SelectButton].setColor(255, 0, 0);

	//Rebder button menu
	for(int i = 0; i < TOTAL_BUTTONS - 1; i++)
		gButtons[i].render(gTextureButtons[i], gRenderer);
	SDL_RenderPresent( gRenderer );
}

void ButtonMenuInteract( SDL_Event& e)
{
	
	if(e.type == SDL_KEYDOWN)
	{
		switch( e.key.keysym.sym )
		{
			case SDLK_UP:
				if(SelectButton > 0){
					gTextureButtons[SelectButton].setColor(255, 255, 255);
					SelectButton --;
					cout<<SelectButton<<endl;
				}
				break;
			case SDLK_DOWN:
				if(SelectButton < 2){
					gTextureButtons[SelectButton].setColor(255, 255, 255);
					SelectButton ++;
					cout<<SelectButton<<endl;
				}
				break;
			case SDLK_KP_ENTER:
			case SDLK_RETURN:
				if(SelectButton == 0){
					endGame = false;
					Mix_HaltMusic();
					if( Mix_PlayingMusic() == 0 )
						{
							//Play the music
							Mix_PlayMusic( gMusic, -1 );
						}
				}
				else if(SelectButton == 1){

				}
				else if(SelectButton == 2){
					quit = true;
				}
				break;
			case SDLK_ESCAPE:
				quit = true;
				break;
			default:
				break;
		}
	}

	
	//Handle button events
	for(int i = 0; i < TOTAL_BUTTONS - 1; i++)
		gButtons[i].handleEvent( &e );

	if(gButtons[0].getCurrent() == BUTTON_MOUSE_DOWN){
		endGame = false;
		Mix_HaltMusic();
		if( Mix_PlayingMusic() == 0 )
			{
				//Play the music
				Mix_PlayMusic( gMusic, -1 );
			}
		gButtons[0].setCurrent(BUTTON_MOUSE_OUT);
	}

	if(gButtons[1].getCurrent() == BUTTON_MOUSE_DOWN){
					
	}

	if(gButtons[2].getCurrent() == BUTTON_MOUSE_DOWN){
		quit = true;
		return;
	}
	for(int i = 0; i < TOTAL_BUTTONS - 1 ; i++)
		if(gButtons[i].getCurrent() == BUTTON_MOUSE_OVER_MOTION)
			SelectButton = i;
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Event handler
			SDL_Event e;

			//Set text color as black
			SDL_Color textColor = { 0, 0, 0, 255 };

			//In memory text stream
			std::stringstream scoreText;

			//The background scrolling offset
			int scrollingOffset = SCREEN_HEIGHT_Y;

			int value = 0;

			//Play menu music
			if( Mix_PlayingMusic() == 0 )
				{
					//Play the music
					Mix_PlayMusic( gMusicMenu, -1 );
				}
			//index Y car enemy
			int indexY = 0;
			//While application is running
			while( !quit )
			{
				//init parameter
				endGame = true;
				value = 0;
				Score = 0;
				Speed = 5;
				scrollingOffset = SCREEN_HEIGHT_Y;
				indexY = 0;

				//init car player
				pCarPlayer.initCarPlayer();

				//Init Position car enemy random
				srand((unsigned)time(NULL));
				do{
					for(int i = 0; i < MAX_ENEMY; i++)
					{
						if(indexY > 4)
							indexY = 0;
						pCarEnemy[i].setPosition(mPosX_init[randomPos()], mPosY_init[indexY]);
						indexY++;
					}
				}while(!conditionPositionCar());
				
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//Handle window events
					gWindow.handleEvent( e, gRenderer );
					resizeWindow();

					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle button events
					ButtonMenuInteract( e );
				}

				//Draw menu main
				DrawMenu();

				while( !endGame && !quit )
				{
						//Draw background play
						gBackGround.setWidth( SCREEN_WIDTH );
						gBackGround.setHeight( SCREEN_HEIGHT );
						gBackGround.render( SCREEN_WIDTH_X, scrollingOffset, gRenderer );
						gBackGround.render( SCREEN_WIDTH_X, scrollingOffset - SCREEN_HEIGHT, gRenderer );

						//Set width, height Road
						gRoad.setWidth(ROAD_WIDTH);
						gRoad.setHeight(ROAD_HEIGHT);
						//Render Road
						gRoad.render( ROAD_X, scrollingOffset, gRenderer);
						gRoad.render( ROAD_X, scrollingOffset - gRoad.getHeight(), gRenderer);
						
						//Scroll background
						scrollingOffset += Speed;
						if( scrollingOffset > gRoad.getHeight() )
						{
							scrollingOffset = SCREEN_HEIGHT_Y;
						}

						//Render Score
						//Set text to be rendered
						scoreText.str( "" );
						scoreText << "Your Score: " << Score;
						//Render text
						if( !gScore.loadFromRenderedText( scoreText.str().c_str(), textColor, gFont, gRenderer ))
						{
							printf( "Unable to render score texture!\n" );
						}
						// Set width, height font Score
						gScore.setHeight(FACTOR);
						gScore.setWidth(FACTOR*3);
						gScore.render(SCREEN_WIDTH_X, SCREEN_HEIGHT_Y, gRenderer);

						//Set width, height Car
						gCarPlayer.setWidth( CAR_WIDTH );
						gCarPlayer.setHeight( CAR_HEIGHT );
						for(int i = 0; i < MAX_ENEMY; i++)
						{
							gCarEnemy[i].setWidth( CAR_WIDTH );
							gCarEnemy[i].setHeight( CAR_HEIGHT );
						}

						while( SDL_PollEvent( &e ) != 0 )
							{
								//Handle window events
								gWindow.handleEvent( e, gRenderer );
								resizeWindow();

								//User requests quit
								if( e.type == SDL_QUIT )
								{
									quit = true;
								}

								pCarPlayer.handleEvent( e );
							}
					if( !gWindow.isMinimized() )
					{
						//move car player
						pCarPlayer.moveCar();
						srand((unsigned)time(NULL));
						int check;
						for(int i = 0; i < MAX_ENEMY; i++)
						{
							if(indexY > 4)
									indexY = 0;
							value = pCarEnemy[i].moveCar( pCarEnemy[i].getCollider(), pCarPlayer.getCollider() );
	
							if(pCarEnemy[i].getPosY() > ROAD_HEIGHT){
								check = false;
								while(1){
								pCarEnemy[i].setPosition(pCarEnemy[i].getPosX(), mPosY_init[indexY]);
								for(int j = 0; j < MAX_ENEMY; j++)
									if(j != i && (pCarEnemy[i].checkCollision(pCarEnemy[i].getCollider(), pCarEnemy[j].getCollider())))
										check = true;
								if(check == false)
									break;
								indexY++;
								if(indexY > 4)
									indexY = 0;
								}
								indexY++;
							}

							//check again
							if(pCarEnemy[i].getPosY() > ROAD_HEIGHT)
							{
									check = false;
									while(1){
									pCarEnemy[i].setPosition(pCarEnemy[i].getPosX(), mPosY_init[indexY]);
									for(int j = 0; j < MAX_ENEMY; j++)
										if(j != i && (pCarEnemy[i].checkCollision(pCarEnemy[i].getCollider(), pCarEnemy[j].getCollider())))
											check = true;
									if(check == false)
										break;
									indexY++;
									if(indexY > 4)
										indexY = 0;
									}
									indexY++;
							}

							if(Score >= Speed*5)
								Speed +=5;
							//end game
							if( value == -1)
							{
								value = 0;
								endGame = true;
								Mix_HaltMusic();
								gScore.setHeight(SCREEN_HEIGHT/3);
								gScore.setWidth(SCREEN_WIDTH/2);
								gScore.render(SCREEN_WIDTH_X + SCREEN_WIDTH/4, SCREEN_HEIGHT_Y + SCREEN_HEIGHT/3, gRenderer);
								Sleep(1000);
								SDL_RenderPresent( gRenderer );
								Sleep(1000);
								if( Mix_PlayingMusic() == 0 )
									{
										//Play the music
										Mix_PlayMusic( gMusicMenu, -1 );
									}
							}
						}

						//Render CarPlayer
						pCarPlayer.renderCar( gCarPlayer, gRenderer);

						//Render CarEnemy
						for(int i = 0; i < MAX_ENEMY; i++)
							pCarEnemy[i].renderCar( gCarEnemy[i], gRenderer);
					
						//Clear screen plus
						SDL_Rect screenPlus = { 0, SCREEN_HEIGHT, SCREEN_WIDTHPLUS, SCREEN_HEIGHTPLUS - SCREEN_HEIGHT };
						SDL_SetRenderDrawColor( gRenderer, 0x97, 0xFF, 0xFF, 0xFF );
						SDL_RenderFillRect( gRenderer, &screenPlus );

						//Update screen
						SDL_RenderPresent( gRenderer );
					}
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}