#pragma once

#pragma region 头文件引用

// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include<stdio.h>

// 资源头文件
#include "resource.h"
#pragma comment(lib, "Msimg32.lib")			//图象处理的函数接口，例如：透明色的位图的绘制TransparentBlt函数


// TODO:  在此处引用程序需要的其他头文件
#include <vector>
#include <math.h>
#include<conio.h>
#include<MMSystem.h>
#pragma comment(lib,"winmm.lib")

#pragma endregion


#pragma region 宏定义

#define WINDOW_TITLEBARHEIGHT	32			//标题栏高度
#define WINDOW_WIDTH			1200		//游戏窗口宽度
#define WINDOW_HEIGHT			660		//游戏窗口高度


#define STAGE_STARTMENU			0		//开始画面的ID
#define STAGE_1					1		//第一个游戏场景的IDspring
#define STAGE_CHOSE             2       //选择界面的ID
#define STAGE_2					3		//summer
#define STAGE_3                 4		//autumn
#define STAGE_4					5		//winter
#define STAGE_STOP				6		//stop
#define STAGE_DEFEAT            7
#define STAGE_VICTORY           8
#define STAGE_HELP              9     

#define UNIT_SIZE_X				86		//单位的宽度
#define UNIT_SIZE_Y				150		//单位的高度
#define UNIT_LAST_FRAME			19		//单位的动画帧最大值

#define BULLET_SIZE_X				100	//单位的宽度
#define BULLET_SIZE_Y				100		//单位的高度
#define BULLET_LAST_FRAME			6		//单位的动画帧最大值

#define ENEMY_MUSHROOM              10
#define MUSHROOM_SIZE_X				120		//单位的宽度
#define MUSHROOM_SIZE_Y				131		//单位的高度
#define MUSHROOM_LAST_FRAME			7		//单位的动画帧最大值

#define ENEMY_GHOST					11
#define GHOST_SIZE_X				170		//单位的宽度
#define GHOST_SIZE_Y				150		//单位的高度
#define GHOST_LAST_FRAME			7		//单位的动画帧最大值

#define ENEMY_DUCK                 12
#define DUCK_SIZE_X               142
#define DUCK_SIZE_Y               150

#define ENEMY_GIRL             13
#define GIRL_SIZE_X            300
#define GIRL_SIZE_Y            150
#define GIRL_LAST_FRAME        19



//单位阵营定义
#define UNIT_SIDE_RED			10000	//红方
#define UNIT_SIDE_BLUE			10001	//蓝方

//敌人阵营定义
#define ENEMY_SIDE_GHOST         10000
#define ENEMY_SIDE_DUCK         10001
#define ENEMY_SIDE_MUSHROOM      10002
#define ENEMY_SIDE_MUSHROOM1     10003
#define ENEMY_SIDE_DUCK1         10004
#define ENEMY_SIDE_GIRL               10005

//单位类型定义
#define UNIT_TYPE_REAPER		0		//收割者
#define UNIT_TYPE_CASTER		1		//魔术师
#define UNIT_TYPE_SABER			2		//剑士
#define UNIT_TYPE_SHIELDER		3		//盾卫
#define UNIT_TYPE_HOPLITE		4		//重装步兵

//敌人类型定义
#define ENEMY_TYPE_COMMEN       0
#define ENEMY_TYPE_FLY          1
#define ENEMY_TYPE_COMMEN1      2
#define ENEMY_TYPE_COMMEN2      3
#define ENEMY_TYPE_COMMEN3      4
#define ENEMY_TYPE_GIRL         5

//地砖类型定义
#define GROUND_TYPE_COMMEN      0
#define GROUND_TYPE_MOVE        1
#define GROUND_TYPE_UP          2

//单位状态定义
#define UNIT_STATE_HOLD			0		//静止
#define UNIT_STATE_WALK			1		//行走
#define UNIT_STATE_ATTACK		2		//攻击
#define UNIT_STATE_JUMP         3       //跳跃

// 敌人状态定义
#define ENEMY_WALK              0

//单位方向定义
#define UNIT_DIRECT_RIGHT		0		//向右
#define UNIT_DIRECT_LEFT		1		//向左


//背景
#define BG_SRC_COUNT			6		//背景资源数量
#define BG_COLUMNS				16		//背景列数
#define BG_ROWS					12		//背景行数
#define BG_ROWS_SKY				3		//背景天空行数
#define BG_ROWS_LAND			9		//背景地面行数
#define BG_CELL_WIDTH			64		//背景单格宽度
#define BG_CELL_HEIGHT			64		//背景单格高度

//其它定义
#define BUTTON_STARTGAME			1001	//开始游戏按钮ID
#define BUTTON_STARTGAME_WIDTH		355 	//开始游戏按钮宽度
#define BUTTON_STARTGAME_HEIGHT		142 	//开始游戏按钮高度

#define BUTTON_CHOSE1			1002	//选择游戏按钮ID
#define BUTTON_CHOSE1_WIDTH		250		//选择游戏按钮宽度
#define BUTTON_CHOSE1_HEIGHT	100		//选择游戏按钮高度


#define BUTTON_CHOSE2			1003	//选择游戏按钮ID
#define BUTTON_CHOSE2_WIDTH		250		//选择游戏按钮宽度
#define BUTTON_CHOSE2_HEIGHT	100		//选择游戏按钮高度

#define BUTTON_CHOSE3			1004	//选择游戏按钮ID
#define BUTTON_CHOSE3_WIDTH		250		//选择游戏按钮宽度
#define BUTTON_CHOSE3_HEIGHT	100		//选择游戏按钮高度

#define BUTTON_CHOSE4			1005	//选择游戏按钮ID
#define BUTTON_CHOSE4_WIDTH		250		//选择游戏按钮宽度
#define BUTTON_CHOSE4_HEIGHT	100		//选择游戏按钮高度

#define BUTTON_STOP				1006	//暂停游戏按钮ID
#define BUTTON_STOP_WIDTH		50		//选择游戏按钮宽度
#define BUTTON_STOP_HEIGHT		50		//选择游戏按钮高度

#define BUTTON_RESTART				1007	//暂停游戏按钮ID
#define BUTTON_RESTART_WIDTH		355		//选择游戏按钮宽度
#define BUTTON_RESTART_HEIGHT		142		//选择游戏按钮高度

#define BUTTON_CONTINUE				1008	
#define BUTTON_CONTINUE_WIDTH		355		
#define BUTTON_CONTINUE_HEIGHT		142		

#define BUTTON_MENU				1009	
#define BUTTON_MENU_WIDTH		355	
#define BUTTON_MENU_HEIGHT		142		

#define BUTTON_HELP			1010	
#define BUTTON_HELP_WIDTH		50	
#define BUTTON_HELP_HEIGHT	50	

#define BUTTON_LIFE1			1011	
#define BUTTON_LIFE_WIDTH		69	
#define BUTTON_LIFE_HEIGHT	60	

#define BUTTON_LIFE2			1012	
#define BUTTON_LIFE_WIDTH		69	
#define BUTTON_LIFE_HEIGHT	60	

#define BUTTON_LIFE3			1013	
#define BUTTON_LIFE_WIDTH		69	
#define BUTTON_LIFE_HEIGHT	60	

#define BUTTON_TRYAGAIN         1014
#define BUTTON_TRYAGAIN_WIDTH   355
#define BUTTON_TRYAGAIN_HEIGHT  142

#define BUTTON_NEXT         1015
#define BUTTON_NEXT_WIDTH   284
#define BUTTON_NEXT_HEIGHT  114

#define BUTTON_OK          1016
#define BUTTON_OK_WIDTH   100
#define BUTTON_OK_HEIGHT   60


#define GROUND1_1			100	
#define GROUND1_1_WIDTH		1200	
#define GROUND1_1_HEIGHT		40	

#define GROUND1_2			101	
#define GROUND1_2_WIDTH		400	
#define GROUND1_2_HEIGHT	40	

#define GROUND2_1           102
#define GROUND2_1_WIDTH     200
#define GROUND2_1_HEIGHT    40

#define GROUND2_2	103	
#define GROUND2_2_WIDTH		400	
#define GROUND2_2_HEIGHT	40	

#define GROUND2_3      104
#define GROUND2_3_WIDTH  400
#define GROUN2_3_HEIGHT  40

#define GROUND2_4    105

#define GROUND2_5       106
#define GROUND3_1       107
#define GROUND3_2       108
#define GROUND3_3       109
#define GROUND3_4       110

#define GROUND3_5       111
#define GROUND3_6       112
#define GROUND4_1       113
#define GROUND4_2       114
#define GROUND4_3       115
#define GROUND4_4       116
#define GROUND4_5       117
#define GROUND4_6       118



#define SPEED			100000	
#define SPEED_WIDTH		55	
#define SPEED_HEIGHT		60	

#define STAR            100001
#define STAR_WIDTH      60
#define STAR_HEIGHT     60

#define MONEY           100002
#define MONEY_WIDTH       60
#define MONEY_HEIGHT      60

#define DIAMOND         100003
#define DIAMOND_WIDTH   62
#define DIAMOND_HEIGHT  50

#define TIMER_GAMETIMER				1		//游戏的默认计时器ID
#define TIMER_GAMETIMER_ELAPSE		30		//默认计时器刷新间隔的毫秒数

#define UNIT_a                      2.0     //加速度
#define ENEMY_SPEED                 3.0

int UNIT_SPEED = 4.0;

#pragma endregion


#pragma region 结构体声明

// 场景结构体
struct Stage
{
	int stageID;		//场景编号
	HBITMAP bg;			//背景图片
	int timeCountDown;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）

};

struct Button
{
	int buttonID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度

	

};

struct Ground
{
	int groundID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int vx;
	int vy;
	int width;		//宽度
	int height;		//高度
	int type;		//单位类型
	int state;		//单位状态
	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列
	int direction;

	int* frame_sequence;	//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几个

	int xx;
	int yy;
};

// 单位结构体
struct Unit
{
	HBITMAP img;	//图片

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;	//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几个


	int side;		//单位阵营
	int type;		//单位类型
	int state;		//单位状态
	
	int direction;	//单位方向

	int x;			//坐标x
	int y;			//坐标y
	double vx;		//速度x
	double vy;		//速度y
	double ax;      //x加速度
	double ay;      //y加速度
	int health;		//生命值

	int xx;
	int yy;
};

struct Enemy
{
	HBITMAP img;	//图片
	int enemyID;

	int frame1_row;			//当前显示的是图像的第几行
	int frame1_column;		//当前显示的是图像的第几列

	int* frame1_sequence;	//当前的帧序列
	int frame1_count;		//帧序列的长度
	int frame1_id;			//当前显示的是帧序列的第几个


	int side;		//单位阵营
	int type;		//单位类型
	int state;		//单位状态

	int direction;	//单位方向

	int x1;			//坐标x
	int y1;			//坐标y
	double vx1;		//速度x
	double vy1;		//速度y
	double ax1;      //x加速度
	double ay1;      //y加速度
	int health1;		//生命值

	bool visible;

	int xx;//图片长
	int yy;
};

struct Bullet
{
	HBITMAP img;	//图片

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;	//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几个

	int direction;	//单位方向

	int width;
	int height;

	int x;			//坐标x
	int y;			//坐标y
	int vx;		//速度x

	bool visible;
};

struct Prop
{
	int propID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度

	int type;
};



//TODO: 添加游戏需要的更多种数据（地物、砖块等）


#pragma endregion


#pragma region 事件处理函数声明


// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

#pragma endregion


#pragma region 其它游戏状态处理函数声明

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y);

//添加道具函数
Prop* CreateProp(int propID, HBITMAP img, int width, int height, int x, int y);

//添加地砖函数
Ground* CreateGround(int groundID, HBITMAP img, int width, int height, int x, int y, int type);

// 添加单位函数
Unit* CreateUnit(int side, int type, int x, int y, int health);

//添加敌人函数
Enemy* CreateEnemy(int side, int type, int x, int y, int health);

//添加子弹函数
Bullet* CreateBullet(HBITMAP img, int width,int height);

// 初始化场景函数
void InitStage(HWND hWnd, int stageID);
//初始化道具函数
void InitProp(HWND hWnd, int propID);



// 刷新单位状态函数
void UpdateUnits(HWND hWnd);
//刷新敌人状态函数
void UpdateEnemy(HWND hWnd);
//刷新地砖状态函数
void UpdateGround(HWND hWnd);
//刷新子弹状态函数
void UpdateBullet(HWND hWnd);
//刷新道具状态函数
void UpdateProp(HWND hWnd);

//单位行为函数
void UnitBehaviour_1(Unit* unit);
void UnitBehaviour_2(Unit* unit);

//敌人行为函数
void EnemyBehaviour_1(Enemy* enemy);
void EnemyBehaviour_2(Enemy* enemy);
void EnemyBehaviour_3(Enemy* enemy);
void EnemyBehaviour_4(Enemy* enemy);
void EnemyBehaviour_5(Enemy* enemy);
void EnemyBehaviour_6(Enemy* enemy);


//地砖行为函数
void GroundBehaviour_1(Ground* ground);
void GroundBehaviour_2(Ground* ground);
void GroundBehaviour_3(Ground* ground);

//TODO: 添加游戏需要的更多函数


#pragma endregion 


#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);

// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src);

#pragma endregion

BOOL PlaySound(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound);