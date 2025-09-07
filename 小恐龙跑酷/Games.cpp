#include<iostream>
#include<SDL.h>
#include<vector>
#include<SDL_image.h>
#include<SDL_ttf.h>
using namespace std;
SDL_Rect groundRect1;
SDL_Rect groundRect2;

const char* SPRITES_FOLDER = "images/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 400;
const char* FONT_PATH = "font/AGENCYB.TTF";
const int FONT_SIZE = 28;

bool gameOver = false;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* dino01Texture = NULL;
SDL_Texture* dino02Texture = NULL;
SDL_Texture* dino03Texture = NULL;

SDL_Texture* groundTexture1 = NULL;
SDL_Texture* groundTexture2 = NULL;
SDL_Texture* ptera1Texture = NULL;
SDL_Texture* ptera2Texture = NULL;
SDL_Texture* gameOverTexture = NULL;
SDL_Texture* replayTexture = NULL;

TTF_Font *font = NULL;

int groundImageWidth = 400;
int groundSpeed = 2;
int ground1X = 0;
int ground2X = groundImageWidth;


SDL_Texture* groundTexture = NULL;

const double GRAVITY = 0.1;
const double JUMP_FORCE = 6.0;


int dinoX = 100;
int dinoY = SCREEN_HEIGHT - 48 - 40;
double dinoYVelocity = 0.0;
bool isJumping = false;

const int ANIMATION_FRAME_TIME = 200;

Uint32 lastCloudSpawnTime = 0;
const int CLOUD_SPAWN_INTERVAL = 2000;


const int MIN_CACTUS_SPACING = 300; 
Uint32 lastCactusSpawnTime = 0;
const int CACTUS_SPAWN_INTERVAL = 1500;

class Cactus
{
public:
	Cactus(int type, int x, int speed);
	
	void Update();
	void Render();

	SDL_Rect GetHitbox() const 
	{
		return hitbox;
	}

private:
	SDL_Texture* texture;
	SDL_Rect hitbox;
	int speed;
};

Cactus::Cactus(int type, int x, int speed):speed(speed)
{
	string imagePath;
	int width;

	if (type == 0)
	{
		imagePath = SPRITES_FOLDER + string("cacti02.png");
		width = 45;
	}
	else
	{
		imagePath = SPRITES_FOLDER + string("cacti01.png");
		width = 65;
	}

	SDL_Surface *surface = IMG_Load(imagePath.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	hitbox = { x, SCREEN_HEIGHT - 36-40, width, 44 };
}


void Cactus::Update()
{
	hitbox.x -= speed;
}
void Cactus::Render()
{
	SDL_RenderCopy(renderer, texture, NULL, &hitbox);
}

class Ptera
{
public:
	Ptera(int type, int x, int altitude,int speed);

	void Update();
	void Render();

	SDL_Rect GetHitbox() const
	{
		return hitbox;
	}

private:
	SDL_Texture* texture;
	SDL_Rect hitbox;
	int speed;
	int altitude;
};

Ptera::Ptera(int type, int x,int altitude, int speed) :speed(speed),altitude(altitude)
{
	string imagePath;
	int width;

	if (type == 0)
	{
		imagePath = SPRITES_FOLDER + string("ptera1.png");
	}
	else
	{
		imagePath = SPRITES_FOLDER + string("ptera2.png");
	}

	SDL_Surface* surface = IMG_Load(imagePath.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	hitbox = { x, altitude, 46, 40 };
}


void Ptera::Update()
{
	hitbox.x -= speed;
}
void Ptera::Render()
{
	SDL_RenderCopy(renderer, texture, NULL, &hitbox);
}



class Cloud
{
public:
	Cloud(int x, int altitude, int speed);

	void Update();
	void Render();

	SDL_Rect GetHitbox() const
	{
		return hitbox;
	}

private:
	SDL_Texture* texture;
	SDL_Rect hitbox;
	int speed;
	int altitude;
};

Cloud::Cloud(int x, int altitude, int speed) :speed(speed), altitude(altitude)
{
	string imagePath;
	int width;

	imagePath = SPRITES_FOLDER + string("cloud.png");

	SDL_Surface* surface = IMG_Load(imagePath.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	int Width = 50 + rand() % 40;
	int Height = 50 + rand() % 30;

	hitbox = { x, altitude, Width, Height };
}


void Cloud::Update()
{
	hitbox.x -= speed;
}
void Cloud::Render()
{
	SDL_RenderCopy(renderer, texture, NULL, &hitbox);
}


vector<Cactus> cactuses;
vector<Ptera> pteras;
vector<Cloud> clouds;

bool InitializeSDL()
{
	SDL_Init(SDL_INIT_VIDEO);

	if (TTF_Init() == -1)
	{
		cout << "TTF³õÊ¼»¯Ê§°Ü" << endl;
		return false;
	}

	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
	{
		cout << "SDL³õÊ¼»¯Ê§°Ü" << endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		cout<<"äÖÈ¾Æ÷³õÊ¼»¯Ê§°Ü"<<endl;
		return false;
	}

	return true;
}
bool LoadMedia() {
	string dino01ImagePath = SPRITES_FOLDER + string("dino01.png");
	string dino02ImagePath = SPRITES_FOLDER + string("dino02.png");
	string dino03ImagePath = SPRITES_FOLDER + string("dino03.png");

	string groundImagePath1 = SPRITES_FOLDER + string("ground.png");
	string ptera1ImagePath = SPRITES_FOLDER + string("ptera1.png");
	string ptera2ImagePath = SPRITES_FOLDER + string("ptera2.png");

	SDL_Surface* dino01Surface = IMG_Load(dino01ImagePath.c_str());
	if (!dino01Surface) {
		cout << "¼ÓÔØÍ¼Æ¬Ê§°Ü: " << IMG_GetError() << endl;
		return false;
	}
	dino01Texture = SDL_CreateTextureFromSurface(renderer, dino01Surface);
	SDL_FreeSurface(dino01Surface);
	SDL_Surface* dino02Surface = IMG_Load(dino02ImagePath.c_str());
	if (!dino02Surface) {
		cout << "¼ÓÔØÍ¼Æ¬Ê§°Ü: " << IMG_GetError() << endl;
		return false;
	}
	dino02Texture = SDL_CreateTextureFromSurface(renderer, dino02Surface);
	SDL_FreeSurface(dino02Surface);
	SDL_Surface* dino03Surface = IMG_Load(dino03ImagePath.c_str());
	if (!dino03Surface) {
		cout << "¼ÓÔØÍ¼Æ¬Ê§°Ü: " << IMG_GetError() << endl;
		return false;
	}
	dino03Texture = SDL_CreateTextureFromSurface(renderer, dino03Surface);
	SDL_FreeSurface(dino03Surface);



	SDL_Surface* groundSurface = IMG_Load(groundImagePath1.c_str());
	if (!groundSurface) {
		cout << "¼ÓÔØµØÃæÍ¼Æ¬Ê§°Ü: " << IMG_GetError() << endl;
		return false;
	}

	groundTexture1 = SDL_CreateTextureFromSurface(renderer, groundSurface);
	groundTexture2 = SDL_CreateTextureFromSurface(renderer, groundSurface);

	groundImageWidth = SCREEN_WIDTH;
	SDL_FreeSurface(groundSurface);

	// ³õÊ¼»¯µØÃæÎ»ÖÃ
	ground1X = 0;
	ground2X = groundImageWidth;

	SDL_Surface* ptera1Surface = IMG_Load(ptera1ImagePath.c_str());
	if (!ptera1Surface) {
		cout << "¼ÓÔØÍ¼Æ¬Ê§°Ü: " << IMG_GetError() << endl;
		return false;
	}
	ptera1Texture = SDL_CreateTextureFromSurface(renderer, ptera1Surface);
	SDL_FreeSurface(ptera1Surface);

	SDL_Surface* ptera2Surface = IMG_Load(ptera2ImagePath.c_str());
	if (!ptera2Surface) {
		cout << "¼ÓÔØÍ¼Æ¬Ê§°Ü: " << IMG_GetError() << endl;
		return false;
	}
	ptera2Texture = SDL_CreateTextureFromSurface(renderer, ptera2Surface);
	SDL_FreeSurface(ptera2Surface);


	font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	if (!font)
	{
		cout << "¼ÓÔØ×ÖÌåÊ§°Ü" << endl;
		return false;
	}


	return true;
}

void RenderText(const char* text, SDL_Texture*& texture, SDL_Rect& destRect)
{
	SDL_Color textColor = {255,0,0};
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	destRect.w = textSurface->w;
	destRect.h = textSurface->h;

	SDL_FreeSurface(textSurface);
	destRect.x = (SCREEN_WIDTH - destRect.w) / 2;
}



void UpdateGround()
{
	ground1X -= groundSpeed;
	ground2X -= groundSpeed;

	if (ground1X + groundImageWidth < 0) 
	{
		ground1X = ground2X + groundImageWidth;
	}

	if (ground2X + groundImageWidth < 0)
	{
		ground2X = ground1X + groundImageWidth;
	}
}




void HandleJump()
{
	if (!isJumping)
	{
		dinoYVelocity = -JUMP_FORCE;
		isJumping = true;
	}
}

bool checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
	return !(rect1.x + rect1.w < rect2.x ||
		rect2.x + rect2.w < rect1.x ||
		rect1.y + rect1.h < rect2.y ||
		rect2.y + rect2.h < rect1.y);
}

void RenderGameOverText()
{
	SDL_Rect gameOverRect;
	SDL_Rect replayRect;

	gameOverRect.y = SCREEN_HEIGHT / 2 - 30;
	replayRect.y = gameOverRect.y + 50;

	RenderText("Game Over", gameOverTexture, gameOverRect);
	RenderText("Press Space To Replay", replayTexture, replayRect);

	SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
	SDL_RenderCopy(renderer, replayTexture, NULL, &replayRect);
}


void UpdateDino()
{
	dinoY += static_cast<int>(dinoYVelocity);
	dinoYVelocity += GRAVITY;

	if (dinoY >= SCREEN_HEIGHT - 48 - 40)
	{
		dinoY = SCREEN_HEIGHT - 48 - 40;
		dinoYVelocity = 0.0;
		isJumping = false;
	}
}

Uint32 lastFrameChangeTime = SDL_GetTicks();
int currentFrame = 0;

void dinomove()
{
	Uint32 currentTime = SDL_GetTicks();
	if (currentTime - lastFrameChangeTime >= ANIMATION_FRAME_TIME) {
		currentFrame = (currentFrame + 1) % 2; 
		lastFrameChangeTime = currentTime;
	}
}

bool quit = false;
SDL_Event event;

void ResetGame()
{
	cactuses.clear();
	pteras.clear();
	cactuses.push_back(Cactus(0, 800, groundSpeed));
	cactuses.push_back(Cactus(1, 1200, groundSpeed));
	cactuses.push_back(Cactus(0, 1600, groundSpeed));

	dinoY = SCREEN_HEIGHT - 40 - 48;
	dinoYVelocity = 0.0;

	isJumping = false;
	groundSpeed = 2;
	ground1X = 0;
	ground2X = SCREEN_WIDTH;
	gameOver = false;
}

void HandleEvents()
{
	while (SDL_PollEvent(&event)!=0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
			{				
				HandleJump();
			}
			if (event.key.keysym.sym == SDLK_SPACE && gameOver)
			{
				ResetGame();
			}
			break;
		}
	}
}


int main(int argc, char* argv[])
{
	if (!InitializeSDL())
	{
		cout << "³õÊ¼»¯SDLÊ§°Ü" << endl;
		return 1;
	}


	if (!LoadMedia())
	{
		cout<<"¼ÓÔØÃ½ÌåÊ§°Ü"<<endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}



	cactuses.push_back(Cactus(0, 800, groundSpeed));
	cactuses.push_back(Cactus(1, 1200, groundSpeed));
	cactuses.push_back(Cactus(0, 1600, groundSpeed));



	while (!quit)
	{
		HandleEvents();
		if (!gameOver)
		{
			UpdateDino();
			UpdateGround();


			for (size_t i = 0; i < cactuses.size(); i++)
			{
				cactuses[i].Update();
				if (checkCollision({ dinoX,dinoY,44,48 }, cactuses[i].GetHitbox()))
				{
					gameOver = true;
				}
			}

			if (SDL_GetTicks() % 3000 == 0)
			{
				int type = rand() % 2;
				int altitude = rand() % 100 + 100;
				pteras.push_back(Ptera(type, SCREEN_WIDTH, altitude, groundSpeed));
			}


			for (size_t i = 0; i < pteras.size(); i++)
			{
				pteras[i].Update();
				if (checkCollision({ dinoX,dinoY,44,48 }, pteras[i].GetHitbox()))
				{
					gameOver = true;
				}
			}

			if (SDL_GetTicks() - lastCloudSpawnTime > CLOUD_SPAWN_INTERVAL) {
				int altitude = rand() % 100 + 20;
				int speed = max(1, groundSpeed / 2); 
				clouds.push_back(Cloud(SCREEN_WIDTH, altitude, speed));
				lastCloudSpawnTime = SDL_GetTicks();
			}

			for (size_t i = 0; i < clouds.size(); i++)
			{
				clouds[i].Update();
			}
		}


		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);


		groundRect1 = { ground1X,SCREEN_HEIGHT-50,groundImageWidth,30 };
		SDL_RenderCopy(renderer, groundTexture1, NULL, &groundRect1);


		groundRect2 = { ground2X,SCREEN_HEIGHT-50,groundImageWidth,30 };
		SDL_RenderCopy(renderer, groundTexture2, NULL, &groundRect2);
		


		for (size_t i = 0; i < cactuses.size(); i++)
		{
			cactuses[i].Render();
			if (cactuses[i].GetHitbox().x + cactuses[i].GetHitbox().w < 0)
			{
				cactuses[i] = Cactus(rand() % 2, rand() % 300+300+SCREEN_WIDTH, groundSpeed);
			}
		}

		for (size_t i = 0; i < pteras.size(); i++)
		{
			pteras[i].Render();
			if (pteras[i].GetHitbox().x + pteras[i].GetHitbox().w < 0)
			{
				pteras.erase(pteras.begin() + i);
			}
		}

		for (size_t i = 0; i < clouds.size(); i++)
		{
			clouds[i].Render();
			if (clouds[i].GetHitbox().x + clouds[i].GetHitbox().w < 0)
			{
				clouds.erase(clouds.begin() + i);
			}
		}

		SDL_Rect dinoRect = { dinoX, dinoY, 44, 48 };


		dinomove();

		if (dinoY == SCREEN_HEIGHT - 48 - 40)
		{
			if (currentFrame == 0)
				SDL_RenderCopy(renderer, dino02Texture, NULL, &dinoRect);
			else
				SDL_RenderCopy(renderer, dino03Texture, NULL, &dinoRect);
		}
		else
		{
			SDL_RenderCopy(renderer, dino01Texture, NULL, &dinoRect);
		}



		if (gameOver)
		{
			RenderGameOverText();
		}

		SDL_RenderPresent(renderer);
		SDL_Delay(5);
	}
	TTF_CloseFont(font);
	SDL_DestroyTexture(dino01Texture);
	SDL_DestroyTexture(dino02Texture);
	SDL_DestroyTexture(dino03Texture);
	SDL_DestroyTexture(groundTexture1);
	SDL_DestroyTexture(groundTexture2);
	SDL_DestroyTexture(ptera1Texture);
	SDL_DestroyTexture(ptera2Texture);
	SDL_DestroyTexture(gameOverTexture);
	SDL_DestroyTexture(replayTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}