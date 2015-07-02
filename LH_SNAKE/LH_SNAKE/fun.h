#ifndef _FUN_H_
#define _FUN_H_

/*���峣��*/
#define PASSNUM 30				//������ص�ʳ������
#define IMGNUM 20				//������Ļ����Ҫ������Ϸ������СͼƬ�ĸ���
#define KSCREEN_WIDTH IMGNUM * 32		//��Ļ�Ŀ��
#define KSCREEN_HEIGHT (IMGNUM+1) * 32		//��Ļ�ĸ߶�
#define KSCREEN_BPP 32			//��Ļ��ˢ��Ƶ��
#define speed 160


/*������Ϸ���õ�������*/
typedef struct LOCATION
{
	int x;
	int y;
}TBLOCK;							

/*�����ߵ�*/
extern TBLOCK gSnake[PASSNUM];				//��¼������ĸ���ͼ�������
extern short possition[PASSNUM];				//��¼�߸����ֵ�λ��
extern int gLength;					//��¼�ߵĳ���
extern int gDirection;					//�ߵķ��� 1:��,2:��,3:��4:��

/*����ʳ��*/
extern TBLOCK gFood;					//��¼ʳ�������
extern int foodNum;					//��¼ʳ�������


/*������Ļ*/
//SDL_Surface *image = NULL;
extern SDL_Surface *screen;					//��Ļͼ��ָ��
extern SDL_Surface *gOptimizedImage[27];	//��Ϸ������ͼƬ
extern short gStaticMap[IMGNUM + 1][IMGNUM];		//��Ϸ�ĵ�ͼ
void score(int num);						//��¼����

/*������Ϣ*/
extern TTF_Font *overTxt;				
extern SDL_Surface * gameFace;
extern SDL_Surface *Txt;



/************************************************************************/
/* ����                                                                 */
/************************************************************************/

int init(void);								//SDL��ʼ��
void initImages(void);						//ͼƬ��ʼ��
void grass(void);						//�ݵظ��Ǻ���
void initNowMaps(void);						//��ʾ����ͼƬ
int judgeOver(void);						//�жϽ�������
void quitGame(void);						//�˳���Ϸ
void showOverFace(void);					//��ʾ��������
void showPassFace(void);					//��ʾ���ػ���
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );


/*�ߵĺ���*/
void snakePic(short *possition);			//�������λͼƬ
void initSnake(void);						//��ʾС��
void moveLeft(void);						//����
void moveDown(void);						//����
void moveRight(void);						//����
void moveUp(void);							//����
void autoMove(void);						//�Զ��ƶ�

/*ʳ�ﺯ��*/
void makeFood(void);						//�漴����ʳ��
int judgeEat(void);							//�жϳԵ�ʳ�
//void distFood(void);						//����ʳ��
void eatFood(void);							//�Ե�ʳ�� ����䳤

#endif _FUN_H_