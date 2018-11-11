#ifndef CGeneral_h_
#define CGeneral_h_
#endif

//width, height window
#define MUL_SCREEN_WIDTH 16
#define MUL_SCREEN_HEIGHT 9
int FACTOR				= 80;
int SCREEN_WIDTHPLUS	= 16 * FACTOR; //1280
int SCREEN_HEIGHTPLUS	= 9 * FACTOR;	//720
int SCREEN_WIDTH		= 16 * FACTOR;
int SCREEN_HEIGHT		= 9 * FACTOR;
int SCREEN_WIDTH_X		= ( SCREEN_WIDTHPLUS/2 - SCREEN_WIDTH/2);
int SCREEN_HEIGHT_Y		= ( SCREEN_HEIGHTPLUS/2 - SCREEN_HEIGHT/2);
//width, height road
int ROAD_WIDTH		= SCREEN_WIDTH/2;
int ROAD_HEIGHT		= SCREEN_HEIGHT;

//roadside
int ROADSIDE_WIDTH	= ROAD_WIDTH/8;

//roadway
int ROADWAY_WIDTH	= (ROAD_WIDTH - 2 * ROADSIDE_WIDTH);
int ROADWAY_W_INIT	= (ROADWAY_WIDTH - ROADWAY_WIDTH/16);

//x, y road top left
int ROAD_X			= SCREEN_WIDTH/4 + SCREEN_WIDTH_X;
int ROAD_Y			= 0 + SCREEN_HEIGHT_Y;

//width, height car
int CAR_WIDTH		= ROAD_WIDTH/8;
int CAR_HEIGHT		= ROAD_HEIGHT/6;

//number car enemy
#define MAX_ENEMY 5

//speed
static int Speed = 5;

//Init location car
int mPosX_init[4] = { ROAD_X + ROADWAY_W_INIT/4, ROAD_X + ROADWAY_W_INIT/2, ROAD_X + ROADWAY_W_INIT*3/4, ROAD_X + ROADWAY_W_INIT};
int mPosY_init[5] = { -CAR_HEIGHT - CAR_HEIGHT/2 , -4*CAR_HEIGHT - CAR_HEIGHT/2, -7*CAR_HEIGHT - CAR_HEIGHT/2, -10*CAR_HEIGHT - CAR_HEIGHT/2, -13*CAR_HEIGHT - CAR_HEIGHT/2 };

static int Score = 0;

//random number
int randomPos()
{
    int choose;
    choose = rand()%4;
    return choose;
}

//Select button
int SelectButton = 0;

//Main loop flag
bool quit = false;
bool endGame = true;