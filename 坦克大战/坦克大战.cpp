#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define ENERMY_NUMBER 10
int map[26][26]={
	{101,101,0,0,0,0,0,0,102,102,0,0,0,0,0,103,103,0,0,0,0,0,0,0,0,0},
	{101,101,0,0,0,0,0,0,102,102,0,0,0,0,0,103,103,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0},
	{0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,1,1,0,0,1,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,1,1,0,0,1,1,1,0,0}, 
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,0,0,1,1,0,0,1,1,1,0,0},
	{0,0,1,1,2,2,1,1,0,0,1,1,0,0,1,0,0,1,1,2,2,1,1,1,0,0},
	{0,0,1,1,2,2,1,1,0,0,1,1,0,0,1,0,0,1,1,2,2,1,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
	{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
	{2,2,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{2,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,2,2},
	{0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,2,2},
	{0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
	{0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0},
	{0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,200,200,1,1,3,3,1,1,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,200,200,1,1,3,3,1,1,0,0,0,0,0,0,0,0,0,0},	
};
//定义一个枚举变量
enum DIRECTION{UP,DOWN,LEFT,RIGHT};
//定义坦克结构体
struct tank_s{
	int x;
	int y;
	DIRECTION direction;
	int live;//坦克是否存活？1代表存活
};
//定义子弹结构体
struct bullet_s{
	int pos_x;
	int pos_y;
	DIRECTION direction;
	int status;//子弹的状态
};


void menu();
void init();
void play();
int do_tank_walk(tank_s*tank,DIRECTION direction,IMAGE*img, int step,int tank_kind);
void tank_walk(tank_s*tank,DIRECTION direction,IMAGE*img,int tank_kind);
void map_change(int x,int y,int sort);
int my_bullet_action(bullet_s*bullet,tank_s*enermy_tank);
int enermy_bullet_action(bullet_s*bullet,tank_s*enermy_tank);
DIRECTION enermy_direction(tank_s*tank,int x,int y);
void tank_fire(tank_s*tank,bullet_s*bullet);
/**************
*主函数********
***************/
int main(void){
	//搭建舞台
	initgraph(650,650);
	//打印菜单
	menu();
	//初始化地图
	init();
	//实现游戏场景
	play();

	system("pause");
	return 0;
}
/**********************
*加载游戏的初始界面***
**********************/
void menu(){
	IMAGE logo_img;
	loadimage(&logo_img,_T("logo.bmp"),433,147);
	putimage(108.5,0,&logo_img);

	//设置线的颜色白色，填充的颜色为黑色
	setlinecolor(WHITE);
	setfillcolor(BLACK);

	//在背景上画出一个填充的长方形，并在里面写上文字“说明”。
	fillrectangle(205,247,305,287);
	settextstyle(30,0,_T("宋体"));
	outtextxy(220,252,_T("说明"));

	//在背景上画出一个填充的长方形，并在里面写上文字“开始”。
	fillrectangle(345,247,445,287);
	settextstyle(30,0,_T("宋体"));
	outtextxy(360,252,_T("开始"));

	IMAGE  illustrate_img;
	loadimage(&illustrate_img,_T("illustrate.jpg"),300,300);


	//定义一个结构体，用以存储鼠标的信息
	MOUSEMSG mouse;
	int flag=0;
	while(1){
		mouse=GetMouseMsg();

		switch(mouse.uMsg){
		case WM_MOUSEMOVE:
			if((mouse.x>205&&mouse.x<305)&&(mouse.y>247&&mouse.y<287)){
				putimage(175,300,&illustrate_img);
			}
			else{
				solidrectangle(175,300,475,600);
			}
			break;
		case WM_LBUTTONDOWN:
			if((mouse.x>345&&mouse.x<445)&&(mouse.y>247&&mouse.y<287)){
				cleardevice();
				return;
			}
		}
	}	
}
/**********************
*初始化地图上的图片***
**********************/
void init(){
	int i=0;
	int j=0;
	IMAGE img_home;
	IMAGE img_wall_1;//可被打烂的墙
	IMAGE img_wall_2;//不可被打烂的墙
	loadimage(&img_home,_T("home.jpg"),50,50);
	loadimage(&img_wall_1,_T("wall2.jpg"),25,25);
	loadimage(&img_wall_2,_T("wall1.jpg"),25,25);

	//实现对地图的初始化

	for(i=0;i<26;i++){
		for(j=0;j<26;j++){
			if(map[i][j]==1){
				putimage(j*25,i*25,&img_wall_1);
			}
			else if(map[i][j]==2){
				putimage(j*25,i*25,&img_wall_2);
			}
			else if(map[i][j]==3){
				putimage(j*25,i*25,&img_home);
				map_change(j,i,4);
			}
		}
	}



}
/********************************
***************实现游戏**********
*********************************/
void play(){
	IMAGE end_img;
	loadimage(&end_img,_T("success.jpg"),650,650);
	tank_s my_tank;
	IMAGE tank_img[4];//定义一个图片数组

	//定义敌方坦克结构体数组
	tank_s enermy_tank[ENERMY_NUMBER];
	//定义敌方坦克的图片数组
	IMAGE enermy_tank_img[4];


	my_tank.x=8;
	my_tank.y=24;
	my_tank.direction=UP;
	my_tank.live=1;

	bullet_s my_bullet;
	my_bullet.status=0;

	bullet_s enermy_bullet[ENERMY_NUMBER];


	//加载我方坦克的图片

	loadimage(&tank_img[UP],_T("tank_up.jpg"),50,50);

	loadimage(&tank_img[DOWN],_T("tank_down.jpg"),50,50);

	loadimage(&tank_img[LEFT],_T("tank_left.jpg"),50,50);

	loadimage(&tank_img[RIGHT],_T("tank_right.jpg"),50,50);

	//加载敌方坦克的图片

	loadimage(&enermy_tank_img[UP],_T("enemy_tank_up.jpg"),50,50);

	loadimage(&enermy_tank_img[DOWN],_T("enemy_tank_down.jpg"),50,50);

	loadimage(&enermy_tank_img[LEFT],_T("enemy_tank_left.jpg"),50,50);

	loadimage(&enermy_tank_img[RIGHT],_T("enemy_tank_right.jpg"),50,50);


	//放置我方坦克的图片
	putimage(my_tank.x*25,my_tank.y*25,&tank_img[my_tank.direction]);

	int enermy_tatol=3;
	//初始化随机数种子
	srand(time(NULL));

	//敌方坦克的数据初始化
	for(int i=0;i<ENERMY_NUMBER;i++){
		if(i%3==0){
			enermy_tank[i].x=0;		
		}
		else if(i%3==1){
			enermy_tank[i].x=8;		
		}
		else if(i%3==2){
			enermy_tank[i].x=15;		
		}
		enermy_tank[i].y=0;
		map_change(enermy_tank[i].x,enermy_tank[i].y,101+i);
		enermy_tank[i].live=0;
		enermy_tank[i].direction=DOWN;	
		enermy_bullet[i].status=0;
	}

	//登场三辆敌方坦克
	do_tank_walk(&enermy_tank[0],enermy_tank[0].direction,&enermy_tank_img[enermy_tank[0].direction],0,101);
	do_tank_walk(&enermy_tank[1],enermy_tank[1].direction,&enermy_tank_img[enermy_tank[1].direction],0,102);
	do_tank_walk(&enermy_tank[2],enermy_tank[2].direction,&enermy_tank_img[enermy_tank[2].direction],0,103);
	enermy_tank[0].live=1;
	enermy_tank[1].live=1;
	enermy_tank[2].live=1;

	int game=0;
	int key;
	int times=0;
	int i=enermy_tatol;

	while(1){
		if(_kbhit()){
			key=_getch();
			switch(key){
			case 'a':
				tank_walk(&my_tank,LEFT,&tank_img[LEFT],200);
				break;
			case 'w':
				tank_walk(&my_tank,UP,&tank_img[UP],200);
				break;
			case 's':
				tank_walk(&my_tank,DOWN,&tank_img[DOWN],200);
				break;
			case 'd':
				tank_walk(&my_tank,RIGHT,&tank_img[RIGHT],200);
				break;
			case 'j':
				PlaySound(_T("paoji.wav"),NULL,SND_FILENAME|SND_ASYNC);
				if(my_bullet.status == 0)
					tank_fire(&my_tank,&my_bullet);
				break;
			case 'p':
				system("pause");
				break;			
			}
		}

		if((my_bullet.status==1)&&(times%70==0)){
			game=my_bullet_action(&my_bullet,enermy_tank);
		}
		if(game == 1){
			setfillcolor(BLACK);
			fillrectangle(0,0,650,650);
			settextstyle(300,0,_T("宋体"));
			outtextxy(0,0,_T("失败"));
			break;
		}

		if(times != 0&&times%8000 == 0&&enermy_tatol < ENERMY_NUMBER&&i%3 == 0&&map[0][0] == 0&&map[1][0] == 0&&map[0][1] == 0&&map[1][1] == 0){
			map_change(0,0,101+enermy_tatol); 
			enermy_tank[enermy_tatol].live=1;
			do_tank_walk(&enermy_tank[enermy_tatol],enermy_tank[enermy_tatol].direction,&enermy_tank_img[enermy_tank[enermy_tatol].direction],0,101+enermy_tatol);
			enermy_tatol = enermy_tatol + 1;
		}
		if(times != 0&&times%15000 == 0&&enermy_tatol < ENERMY_NUMBER&&i%3 == 0&&map[8][0] == 0&&map[9][0] == 0&&map[8][1] == 0&&map[9][1] == 0){
			map_change(8,0,101+enermy_tatol);
			enermy_tank[enermy_tatol].live=1;
			do_tank_walk(&enermy_tank[enermy_tatol],enermy_tank[enermy_tatol].direction,&enermy_tank_img[enermy_tank[enermy_tatol].direction],0,101+enermy_tatol);
			enermy_tatol = enermy_tatol + 1;
		}
		if(times != 0&&times%20000 == 0&&enermy_tatol < ENERMY_NUMBER&&i%3 == 0&&map[15][0] == 0&&map[16][0] == 0&&map[15][1] == 0&&map[16][1] == 0){
			map_change(15,0,101+enermy_tatol);
			enermy_tank[enermy_tatol].live=1;
			do_tank_walk(&enermy_tank[enermy_tatol],enermy_tank[enermy_tatol].direction,&enermy_tank_img[enermy_tank[enermy_tatol].direction],0,101+enermy_tatol);
			enermy_tatol = enermy_tatol + 1;
		}
		if(times%500==0){
			for(int i=0;i<=ENERMY_NUMBER;i++) {
				if(i%2==0&&enermy_tank[i].live==1){//调整敌方坦克的方向，进攻我方坦克
					enermy_tank[i].direction=enermy_direction(&enermy_tank[i],my_tank.x,my_tank.y);
				}
				else if(i%2==1&&enermy_tank[i].live==1){//进攻我方老鹰
					enermy_tank[i].direction=enermy_direction(&enermy_tank[i],12,24);
				}	
			}
			for(int i=0;i<ENERMY_NUMBER;i++){
				if(enermy_tank[i].live == 1){
					tank_walk(&enermy_tank[i],enermy_tank[i].direction,&enermy_tank_img[enermy_tank[i].direction],101+i);
				}
			}
			for(int i=0;i<enermy_tatol;i++){
				if(enermy_bullet[i].status == 0&&enermy_tank[i].live == 1){
					tank_fire(&enermy_tank[i],&enermy_bullet[i]);
				}
			}		

		}
		game = 0;
		for(int i=0;i<ENERMY_NUMBER;i++){
			if(enermy_bullet[i].status == 1&&times%100 == 0){
				game = enermy_bullet_action(&enermy_bullet[i],&my_tank);
				if(game == 1){
					setfillcolor(BLACK);
					fillrectangle(0,0,650,650);
					settextstyle(300,0,_T("宋体"));
					outtextxy(0,0,_T("失败"));
					break;
				}
			}
		}

		int score=0;
		for(int i=0;i<ENERMY_NUMBER;i++){
			score=score+enermy_tank[i].live;
		}
		if (score==0&&enermy_tatol==10){//所有的敌方坦克都被摧毁
			putimage(0,0,&end_img);
			system("pause");
			break;
		}
		times+=10;		
		Sleep(10);

	}

}
/**************************
*根据步长和坦克的方向来运动坦克
***************************/
int do_tank_walk(tank_s*tank,DIRECTION direction,IMAGE*img,int step,int tank_kind){
	int new_x;
	int new_y;
	new_x=tank->x;
	new_y=tank->y;
	setfillcolor(BLACK);
	solidrectangle(tank->x*25,tank->y*25,tank->x*25+50,tank->y*25+50);
	if(step==1){
		if(direction==UP){
			new_y-=1;
		}
		else if(direction==DOWN){
			new_y+=1;
		}
		else if(direction==LEFT){
			new_x-=1; 
		}
		else if(direction==RIGHT){
			new_x+=1;
		}
		else 
			return 0;
	}
	map_change(tank->x,tank->y,0);
	map_change(new_x, new_y,tank_kind);
	tank->x=new_x;
	tank->y=new_y;
	putimage(tank->x*25,tank->y*25,img);
	return 1;
}
/**********************
*实现坦克的移动
**********************/
void tank_walk(tank_s*tank,DIRECTION direction,IMAGE*img,int tank_kind){
	switch(direction){
	case LEFT:
		if((tank->x-1)>=0&&map[tank->y][tank->x-1]==0&&map[tank->y+1][tank->x-1]==0&&tank->direction==LEFT){
			tank->direction=LEFT;
			do_tank_walk(tank,LEFT,img,1,tank_kind);

		}
		else if(tank->direction!=LEFT){
			tank->direction=LEFT;
			do_tank_walk(tank,LEFT,img,0,tank_kind);
		}
		break;
	case UP:
		if((tank->y-1)>=0&&map[tank->y-1][tank->x]==0&&map[tank->y-1][tank->x+1]==0&&tank->direction==UP){
			tank->direction=UP;
			do_tank_walk(tank,UP,img,1,tank_kind);

		}
		else if(tank->direction!=UP){
			tank->direction=UP;
			do_tank_walk(tank,UP,img,0,tank_kind);
		}
		break;
	case DOWN:
		if((tank->y+1)<=24&&map[tank->y+2][tank->x]==0&&map[tank->y+2][tank->x+1]==0&&tank->direction==DOWN){
			tank->direction=DOWN;
			do_tank_walk(tank,DOWN,img,1,tank_kind);
		}
		else if(tank->direction!=DOWN){
			tank->direction=DOWN;
			do_tank_walk(tank,DOWN,img,0,tank_kind);
		}
		break;
	case RIGHT:
		if((tank->x+1)<=24&&map[tank->y][tank->x+2]==0&&map[tank->y+1][tank->x+2]==0&&tank->direction==RIGHT){
			tank->direction=RIGHT;
			do_tank_walk(tank,RIGHT,img,1,tank_kind);

		}
		else if(tank->direction!=RIGHT){
			tank->direction=RIGHT;
			do_tank_walk(tank,RIGHT,img,0,tank_kind);
		}
		break;
	}
}
/*******************************
*改变地图的数据
********************************/
void map_change(int x,int y,int sort){
	map[y][x]=sort;
	map[y+1][x]=sort;
	map[y][x+1]=sort;
	map[y+1][x+1]=sort;
}
/*******************************
*子弹运动过程，并进行碰撞检测
******************************/
int my_bullet_action(bullet_s*bullet,tank_s*enermy_tank){
	int x,y,x1,y1;  //子弹目前所在的二维数组中的坐标

	x = bullet->pos_x/25;
	y = bullet->pos_y/25;

	//1.擦除上一次绘制的子弹
	setfillcolor(BLACK);
	solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x+3, bullet->pos_y+3);

	//2.根据方向计算子弹在“戏台”上的坐标
	if(bullet->direction == UP){
		bullet->pos_y -=  20;
		x1 = x+1;
		y1 = y;
	}else if(bullet->direction == DOWN){
		bullet->pos_y +=  20;
		x1 = x+1;
		y1 = y;
	}else if(bullet->direction == LEFT){
		bullet->pos_x -=  20;
		x1 = x;
		y1 = y+1;

	}else if(bullet->direction == RIGHT){
		bullet->pos_x +=  20;
		x1 = x;
		y1 = y+1;
	}else{
		return 0;
	}

	if(bullet->pos_x<0 || bullet->pos_x>650 || bullet->pos_y<0 || bullet->pos_y>650){
		bullet->status = 0;
		return 0;
	}

	//碰撞检测
	if(map[y][x] == 4 || map[y1][x1] == 4){
		return 1;
	}

	if(map[y][x]== 1){//子弹击中可消除的墙
		map[y][x]= 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x*25, y*25, x*25+25, y*25+25);
		return 0;
	}else if(map[y][x] == 2){
		bullet->status = 0;
		return 0;
	}
	if(map[y1][x1] == 1){//子弹击中可消除的墙
		map[y1][x1]= 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x1*25, y1*25, x1*25+25, y1*25+25);
		return 0;
	}else if(map[y1][x1] ==  2){
		bullet->status = 0;
		return 0;
	}

	if((map[y][x] >= 101&&map[y][x] <= 110)||(map[y1][x1] >= 101&&map[y1][x1] <= 110)){  //打中了敌方的坦克
		tank_s*tank = NULL;
		bullet->status = 0;

		if(map[y][x] >= 101&&map[y][x] <= 110){
			tank = enermy_tank+map[y][x]-101;	
		}else if(map[y1][x1] >= 101&&map[y1][x1] <= 110){
			tank = enermy_tank+map[y1][x1]-101;	
		}
		tank->live = 0;
		map_change(tank->x,tank->y,0);
		setfillcolor(BLACK);
		solidrectangle(tank->x*25,tank->y*25,tank->x*25+50,tank->y*25+50);
		return 0;
	}

	//3.重新绘制子弹
	if(bullet->status == 1){
		setfillcolor(WHITE);
		solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x+3, bullet->pos_y+3);
	}
}
int enermy_bullet_action(bullet_s*bullet,tank_s*enermy_tank){
	int x,y,x1,y1;  //子弹目前所在的二维数组中的坐标

	x = bullet->pos_x/25;
	y = bullet->pos_y/25;

	//1.擦除上一次绘制的子弹
	setfillcolor(BLACK);
	solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x+3, bullet->pos_y+3);

	//2.根据方向计算子弹在“戏台”上的坐标
	if(bullet->direction == UP){
		bullet->pos_y -=  20;
		x1 = x+1;
		y1 = y;
	}else if(bullet->direction == DOWN){
		bullet->pos_y +=  20;
		x1 = x+1;
		y1 = y;
	}else if(bullet->direction == LEFT){
		bullet->pos_x -=  20;
		x1 = x;
		y1 = y+1;

	}else if(bullet->direction == RIGHT){
		bullet->pos_x +=  20;
		x1 = x;
		y1 = y+1;
	}else{
		return 0;
	}

	if(bullet->pos_x<0 || bullet->pos_x>650 || bullet->pos_y<0 || bullet->pos_y>650){
		bullet->status = 0;
		return 0;
	}

	//碰撞检测
	if(map[y][x] == 4 || map[y1][x1] == 4){
		return 1;
	}

	if(map[y][x]== 1){//子弹击中可消除的墙
		map[y][x]= 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x*25, y*25, x*25+25, y*25+25);
		return 0;
	}else if(map[y][x] == 2){
		bullet->status = 0;
		return 0;
	}
	if(map[y1][x1] == 1){//子弹击中可消除的墙
		map[y1][x1]= 0;
		bullet->status = 0;
		setfillcolor(BLACK);
		solidrectangle(x1*25, y1*25, x1*25+25, y1*25+25);
		return 0;
	}else if(map[y1][x1] ==  2){
		bullet->status = 0;
		return 0;
	}
	if(map[y][x]==200||map[y1][x1]==200){  //打中了我方的坦克
		tank_s*tank = NULL;
		bullet->status = 0;
		tank=enermy_tank;
		tank->live = 0;
		map_change(tank->x,tank->y,0);
		setfillcolor(BLACK);
		solidrectangle(tank->x*25,tank->y*25,tank->x*25+50,tank->y*25+50);
		return 1;
	}

	//3.重新绘制子弹
	if(bullet->status == 1){
		setfillcolor(WHITE);
		solidrectangle(bullet->pos_x, bullet->pos_y, bullet->pos_x+3, bullet->pos_y+3);
	}
}
/***************************************
*根据目标的方向，来调整敌方坦克的方向***
****************************************/
DIRECTION enermy_direction(tank_s*tank,int x,int y){
	int r=rand()%100;
	if(tank->x>=x&&tank->y>=y){//目标在左上方
		if(r<=50)return UP;
		else return LEFT;	
	}
	else if(tank->x>=x&&tank->y<y){//目标在左下方
		if(r<=50)return DOWN;
		else return LEFT;	
	}
	else if(tank->x<x&&tank->y>=y){//目标在右上方
		if(r<=50)return UP;
		else return RIGHT;	
	}
	else if(tank->x<x&&tank->y<y){//目标在右下方
		if(r<=50)return DOWN;
		else return RIGHT;	
	}
}
/******************************************
*打出子弹，根据坦克的方向来初始化子弹的数据
******************************************/
void tank_fire(tank_s*tank,bullet_s*bullet){

	if(bullet->status==0){
		if(tank->direction == UP){
			bullet->pos_x = tank-> x* 25 + 23;
			bullet->pos_y = tank-> y*25-3;	
			bullet->direction=UP;
		}else if(tank->direction == LEFT){
			bullet->pos_x = tank->x * 25-3 ;
			bullet->pos_y = tank->y * 25 +23;
			bullet->direction=LEFT;
		}else if(tank->direction == DOWN){
			bullet->pos_x = tank->x * 25 + 23;
			bullet->pos_y = tank->y * 25 + 50;
			bullet->direction=DOWN;
		}else if(tank->direction == RIGHT){
			bullet->pos_x = tank->x * 25 + 50;
			bullet->pos_y = tank->y * 25 + 23;
			bullet->direction=RIGHT;
		}
		bullet->status=1;
	}
}
