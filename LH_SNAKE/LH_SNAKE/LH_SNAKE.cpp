#include <stdio.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "fun.h"

int main(int argc, char* argv[])
{
	SDL_Event event;
	gSnake[0].x = 3;
	gSnake[0].y = 3;
	gSnake[1].x = 2;
	gSnake[1].y = 3;
	int foodNum = 0;
	while (1)
	{	
		init();
		initImages();
		initNowMaps();
		initSnake();
		makeFood();
		while (1)
		{
			while (SDL_PollEvent(&event))/*�жϼ����¼�*/
			{
				if (event.type = SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						quitGame();
						exit(0);
						break;
					case SDLK_LEFT:
						moveLeft();
						break;
					case SDLK_RIGHT:
						moveRight();
						break;
					case SDLK_UP:
						moveUp();
						break;
					case SDLK_DOWN:
						moveDown();
						break;
					}
					
				}
			}
			if(judgeEat())                //�ж��Ƿ�������ʳ��
			{
				eatFood();				 //�Ե�ʳ��
				makeFood();
			}
			else if(judgeOver())          //��Ϸ��������ʾ�˳�����
			{
				
				showOverFace();
			}
			else if (gLength ==PASSNUM)		  //����
			{
				showPassFace();
			}
			else                          //���û������ʳ��Ҳ��������ô���Զ��ƶ�
			{
				apply_surface((gFood.x) * 32,(gFood.y)*32,gOptimizedImage[0],screen);
				SDL_Flip(screen);
				autoMove();
				SDL_Delay(speed);
			}
		}
	}

	return 0;
}