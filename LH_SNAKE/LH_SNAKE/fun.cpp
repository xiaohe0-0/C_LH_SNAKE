#include <time.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "fun.h"

/*�����ߵ�*/
TBLOCK gSnake[PASSNUM];				//��¼������ĸ���ͼ�������
short possition[PASSNUM];			//��¼�߸����ֵ�λ��
int gLength = 2;					//��¼�ߵĳ���
int gDirection = 2;					//�ߵķ��� 1:��,2:��,3:��4:��

/*����ʳ��*/
TBLOCK gFood;					//��¼ʳ�������
int foodNum;					//��¼ʳ�������


//SDL_Surface *image = NULL;
SDL_Surface *screen;				//��Ļͼ��ָ��
SDL_Surface *gOptimizedImage[27];	//��Ϸ������ͼƬ

/*������Ϣ*/
TTF_Font *overTxt = NULL;
SDL_Surface * gameFace;
SDL_Surface *Txt = NULL;


//��Ϸ�ĵ�ͼ
short gStaticMap[IMGNUM + 1][IMGNUM] = {
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0}
};


/************************************************************************/
/* SDL��ʼ��                                                            */
/************************************************************************/
int init(void)
{
	//��ʼ��
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	{
		return 0;
	}

	//��Ļ
	screen = SDL_SetVideoMode( KSCREEN_WIDTH, KSCREEN_HEIGHT, KSCREEN_BPP, SDL_SWSURFACE );

	if( screen == NULL )
	{
		return 0;
	}

	if(TTF_Init() == -1)
	{
		return 0;
	}

	//������Ϣ
	SDL_WM_SetCaption( "Snake Game", NULL );

	//��ȷ��ʼ��
	return 1;
}
/************************************************************************/
/* ͼƬ��ʼ��                                                           */
/************************************************************************/
void initImages(void){
	SDL_Surface * temp;
	int i;
	char imageAll[27][30] ={
		"images./food.jpg","images./grass.bmp","images./wall.bmp",     //�ײ��
		"images./p0.bmp","images./p1.bmp","images./p2.bmp","images./p3.bmp","images./p4.bmp",
		"images./p5.bmp","images./p6.bmp","images./p7.bmp","images./p8.bmp","images./p9.bmp",//����
		"images./s1.png","images./s2.png",							//����
		"images./sw1.png","images./sw2.png","images./sw3.png","images./sw4.png",//����
		"images./t1.png","images./t2.png","images./t3.png","images./t4.png", //��ͷ
		"images./w1.png","images./w2.png","images./w3.png","images./w4.png" //��β	
	}; 
	for (i = 0; i < 27;i++)
	{
		temp = IMG_Load(imageAll[i]);
		if (temp == NULL)
		{
			return;
		}
		gOptimizedImage[i] = SDL_DisplayFormat(temp);
		SDL_FreeSurface(temp);
	}

}
/************************************************************************/
/* ������Ļ                                                             */
/************************************************************************/
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) 
 { 
	SDL_Rect offset; 
	offset.x = y; 
	offset.y = x;  

	Uint32 colorkey2 = SDL_MapRGB(source->format, 0xFF, 0xFF, 0xFF); 
	SDL_SetColorKey( source, SDL_SRCCOLORKEY  , colorkey2 );

	SDL_BlitSurface( source, NULL, destination,&offset); 
}

/************************************************************************/
/* ��ʾͼƬ����						                                    */
/************************************************************************/
void initNowMaps(void)
{
	int i,j;

	for(i=0;i<IMGNUM+ 1;i++)
	{
		for(j=0;j<IMGNUM ;j++)
		{
			if(gStaticMap[i][j] == 1)
			{
				apply_surface(32*i,32*j,gOptimizedImage[1],screen);
			}
			if(gStaticMap[i][j] == 2)
			{
				apply_surface(32*i,32*j,gOptimizedImage[2],screen);
			}
			if(gStaticMap[i][j] == 3)
			{
				apply_surface(32*i,32*j,gOptimizedImage[3],screen);
			}
		}
	}
	SDL_Flip(screen);

}
/************************************************************************/
/* �ݵظ��Ǻ���                                                         */
/************************************************************************/
void grass(void)
{
	int i;
	for (i = 0;i < gLength;i++)
	{
		apply_surface((gSnake[i].y) * 32,(gSnake[i].x)*32,gOptimizedImage[1],screen);
	}
}
/************************************************************************/
/* ״̬�ı亯��                                                         */
/************************************************************************/
void changesate(void)
{
	int i;
	for(i = gLength - 1;i > 0;i--)
	{
		gSnake[i].x = gSnake[i - 1].x;
		gSnake[i].y = gSnake[i - 1].y;
	}
}
/************************************************************************/
/* �Ƿֺ���                                                             */
/************************************************************************/
void score(int num)
{
	switch (num/10)
	{
	case 0:
		apply_surface(32*20,32*11,gOptimizedImage[3],screen);
		break;
	case 1:
		apply_surface(32*20,32*11,gOptimizedImage[4],screen);
		break;
	case 2:
		apply_surface(32*20,32*11,gOptimizedImage[5],screen);
		break;
	}
	switch (num%10)
	{
	case 0:
		apply_surface(32*20,32*12,gOptimizedImage[3],screen);
		break;
	case 1:
		apply_surface(32*20,32*12,gOptimizedImage[4],screen);
		break;
	case 2:
		apply_surface(32*20,32*12,gOptimizedImage[5],screen);
		break;
	case 3:
		apply_surface(32*20,32*12,gOptimizedImage[6],screen);
		break;
	case 4:
		apply_surface(32*20,32*12,gOptimizedImage[7],screen);
		break;
	case 5:
		apply_surface(32*20,32*12,gOptimizedImage[8],screen);
		break;
	case 6:
		apply_surface(32*20,32*12,gOptimizedImage[9],screen);
		break;
	case 7:
		apply_surface(32*20,32*12,gOptimizedImage[10],screen);
		break;
	case 8:
		apply_surface(32*20,32*12,gOptimizedImage[11],screen);
		break;
	case 9:
		apply_surface(32*20,32*12,gOptimizedImage[12],screen);
		break;
	}
	SDL_Flip(screen);
}
/************************************************************************/
/* ���������λͼƬ                                                     */
/************************************************************************/
void snakePic(void)
{
	int i;
	/*ͷ��ͼƬ*/
	switch (gDirection)
	{
	case 1:
		possition[0] = 22; //����
		break;
	case 2:
		possition[0] = 19;  //����
		break;
	case 3:
		possition[0] = 20;  //����
		break;
	case 4:
		possition[0] = 21;  //����
		break;
	}

	/*����ͼƬ*/
	for (i = 1;i < gLength - 1;i++)
	{
		int minX,maxX,minY,maxY;
		minX = (gSnake[i - 1].x < gSnake[i + 1].x ? gSnake[i - 1].x:gSnake[i + 1].x);
		maxX = (gSnake[i - 1].x > gSnake[i + 1].x ? gSnake[i - 1].x:gSnake[i + 1].x);
		minY = (gSnake[i - 1].y < gSnake[i + 1].y ? gSnake[i - 1].y:gSnake[i + 1].y);
		maxY = (gSnake[i - 1].y > gSnake[i + 1].y ? gSnake[i - 1].y:gSnake[i + 1].y);

		/*����*/
		if ((gSnake[i - 1].x == gSnake[i + 1].x + 1 && gSnake[i - 1].y == gSnake[i + 1].y - 1) ||
			(gSnake[i - 1].x == gSnake[i + 1].x - 1 && gSnake[i - 1].y == gSnake[i + 1].y + 1))
		{
			
			if (gSnake[i].x == minX && gSnake[i].y == minY)
			{
				possition[i] = 15;
			}
			if (gSnake[i].x == maxX && gSnake[i].y == maxY)
			{
				possition[i] = 17;
			}
		}
		if ((gSnake[i - 1].x == gSnake[i + 1].x + 1 && gSnake[i - 1].y == gSnake[i + 1].y + 1) ||
 			(gSnake[i - 1].x == gSnake[i + 1].x - 1 && gSnake[i - 1].y == gSnake[i + 1].y - 1))
		{
			if (gSnake[i].x == maxX && gSnake[i].y == minY)
			{
				possition[i] = 16;
			}
			if (gSnake[i].x == minX && gSnake[i].y == maxY)
			{
				possition[i] = 18;
			}
		}
	
		/*ֱ��*/
		if(gSnake[i - 1].y == gSnake[i + 1].y)
		{
			possition[i] = 13;
		}
		if (gSnake[i - 1].x == gSnake[i + 1].x)
		{
			possition[i] = 14;
		}
	}
	/*��βͼƬ*/
	if (gSnake[gLength - 2].x == gSnake[gLength - 1].x + 1  && 
		gSnake[gLength -2].y ==gSnake[gLength - 1].y)
	{
		possition[gLength - 1] = 26;
	}
	if (gSnake[gLength - 2].x == gSnake[gLength - 1].x - 1  && 
		gSnake[gLength -2].y ==gSnake[gLength - 1].y)
	{
		possition[i] = 24;
	}
	if (gSnake[gLength - 2].x == gSnake[gLength - 1].x   && 
		gSnake[gLength -2].y ==gSnake[gLength - 1].y - 1)
	{
		possition[i] = 25;
	}
	if (gSnake[gLength - 2].x == gSnake[gLength - 1].x  && 
		gSnake[gLength -2].y ==gSnake[gLength - 1].y + 1)
	{
		possition[i] = 23;
	}

}
/************************************************************************/
/* ��ʾС��                                                             */
/************************************************************************/
void initSnake(void)
{ 
	int i;
	snakePic();
	for (i = 0; i < gLength;i++)
	{
		apply_surface((gSnake[i].y) * 32,(gSnake[i].x)*32,gOptimizedImage[possition[i]],screen);
	}
	SDL_Flip(screen);
}
/************************************************************************/
/* �������ʳ��                                                         */
/************************************************************************/
void makeFood(void)
{	
	int tmp;	
	int i;
	srand((unsigned) time(NULL));

	do{	
		tmp = 0;
		gFood.x = rand()%(IMGNUM - 2) + 1;
		gFood.y = rand()%(IMGNUM - 2) + 1;
		for(i = 0;i < gLength;i++)
		{			
			if (gFood.x == gSnake[i].y && gFood.y == gSnake[i].x)
			{			
				tmp = 1;
				break;
			}
		}
		
	}while (tmp);
	apply_surface((gFood.x) * 32,(gFood.y)*32,gOptimizedImage[0],screen);
	SDL_Flip(screen);
}
/************************************************************************/
/* �˳���Ϸ                                                             */
/************************************************************************/
void quitGame(void)
{
	SDL_FreeSurface( gameFace );  
	TTF_CloseFont( overTxt ); 
	TTF_Quit();
	SDL_Delay(2000);
	SDL_Quit();
}
/************************************************************************/
/* С�������ƶ�                                                         */
/************************************************************************/
void moveLeft(void)
{
	if (gDirection == 1 || gDirection == 3)
	{
		grass();
		changesate();
		gSnake[0].x -= 1;
		gDirection = 4;

		initSnake();	
		SDL_Flip(screen);
		SDL_Delay(speed);
	}
}
/************************************************************************/
/* С������                                                             */
/************************************************************************/
void moveUp(void)
{
	if (gDirection == 2 || gDirection == 4)
	{
		grass();
		changesate();
		gSnake[0].y -= 1;
		gDirection = 1;

		initSnake();	
		SDL_Flip(screen);
		SDL_Delay(speed);
	}
}
/************************************************************************/
/* С������                                                             */
/************************************************************************/
void moveRight(void)
{
	if (gDirection == 1 || gDirection == 3)
	{
		grass();
		changesate();
		gSnake[0].x += 1;

		gDirection = 2;

		initSnake();	
		SDL_Flip(screen);
		SDL_Delay(speed);
	}
}
/************************************************************************/
/* С��������                                                           */
/************************************************************************/
void moveDown(void)
{
	if (gDirection == 2 || gDirection == 4)
	{
		grass();
		changesate();
		gSnake[0].y += 1;
		gDirection = 3;

		initSnake();	
		SDL_Flip(screen);
		SDL_Delay(speed);
	}
}


/************************************************************************/
/* �жϳԵ�ʳ�                                                       */
/************************************************************************/
int judgeEat(void)
{
	if(gFood.x == gSnake[0].y && gFood.y == gSnake[0].x)
	{
		foodNum += 1;
		score(foodNum);
		return 1;
	}
	else return 0;
}
/************************************************************************/
/*�Ե�ʳ�� ����䳤                                                   */
/************************************************************************/
void eatFood(void)
{
	grass();
	gLength += 1;

	switch (possition[gLength - 2])
	{
	case 23:
		gSnake[gLength - 1].y  = gSnake[gLength - 2].y - 1;
		gSnake[gLength - 1].x  = gSnake[gLength - 2].x;
		break;
	case 24:
		gSnake[gLength - 1].x  = gSnake[gLength - 2].x + 1;
		gSnake[gLength - 1].y  = gSnake[gLength - 2].y;
		break;
	case 25:
		gSnake[gLength - 1].y  = gSnake[gLength - 2].y + 1;
		gSnake[gLength - 1].x  = gSnake[gLength - 2].x;
		break;
	case 26:
		gSnake[gLength - 1].x  = gSnake[gLength - 2].x - 1;
		gSnake[gLength - 1].y  = gSnake[gLength - 2].y;
		break;
	}
	initSnake();
}
/************************************************************************/
/* �Զ��ƶ�                                                             */
/************************************************************************/
void autoMove(void)
{
	grass();

	changesate();
	switch (gDirection)
	{
	case 1:
		gSnake[0].y -= 1; 
		break;
	case 2:
		gSnake[0].x += 1;
		break;
	case 3:
		gSnake[0].y += 1;
		break;
	case 4:
		gSnake[0].x -= 1;
		break;
	}
	initSnake();
}
/************************************************************************/
/* �жϽ�������                                                         */
/************************************************************************/
int judgeOver(void)
{
	int i;
	for(i = 1;i < gLength;i++)
	{
		if (gSnake[0].x == gSnake[i].x && gSnake[0].y == gSnake[i].y)
		{
			return 1;
		}
		if (gSnake[0].x == 0 ||gSnake[0].x == IMGNUM - 1 || gSnake[0].y == 0 || gSnake[0].y == IMGNUM - 1)
		{
			return 1;
		}
	}
	return 0;
}
/************************************************************************/
/* ��������                                                             */
/************************************************************************/
void showOverFace(void)
{
	SDL_Color textColor = { 0XFF, 0XFF, 0XFF};
	SDL_Rect offset; 
	offset.x = 150; 
	offset.y = 250;  
	
	overTxt = TTF_OpenFont("simhei.ttf",60);
	gameFace = TTF_RenderText_Solid(overTxt,"Game over!",textColor);
	SDL_BlitSurface( gameFace, NULL, screen,&offset);
	SDL_Flip(screen);
	quitGame();
	exit(0);
}
/************************************************************************/
/*���ػ���                                                              */
/************************************************************************/
void showPassFace(void)
{
	SDL_Color textColor = { 0XFF, 0XFF, 0XFF};
	SDL_Rect offset; 
	offset.x = 350; 
	offset.y = 250;  

	overTxt = TTF_OpenFont("simhei.ttf",60);
	gameFace = TTF_RenderText_Solid(overTxt,"PASS!",textColor);
	SDL_BlitSurface( gameFace, NULL, screen,&offset);
	SDL_Flip(screen);
	quitGame();
	exit(0);
}