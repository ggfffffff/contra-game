// ContraGame.cpp : 定义应用程序的入口点。
//

#include "ContraGame.h"

using namespace std;


#pragma region 全局变量

#define MAX_LOADSTRING			100		

// 全局变量: 
HINSTANCE hInst; // 当前窗体实例
WCHAR szTitle[MAX_LOADSTRING]; // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING]; // 主窗口类名



HBITMAP bmp_StartButton;	//开始按钮图像资源
HBITMAP bmp_Unit_Red;		//红方主角图像资源
HBITMAP bmp_Unit_Blue;		//蓝方主角图像资源
HBITMAP bmp_StageButton;    //选择按钮图像资源
HBITMAP bmp_stage1;         //场景一图像资源
HBITMAP bmp_stopbutton;     //暂停键
HBITMAP bmp_opening;        //开屏辉夜
HBITMAP bmp_right;          //辉夜向右走
HBITMAP bmp_left;           //辉夜向左走
HBITMAP bmp_chose;          //选择
HBITMAP bmp_chose1button;
HBITMAP bmp_chose2button;
HBITMAP bmp_chose3button;
HBITMAP bmp_chose4button;
HBITMAP bmp_spring;
HBITMAP bmp_summer;
HBITMAP bmp_autumn;
HBITMAP bmp_winter;
HBITMAP bmp_stop;
HBITMAP bmp_huiyewalk;
HBITMAP bmp_restartbutton;
HBITMAP bmp_continuebutton;
HBITMAP bmp_menubutton;
HBITMAP bmp_helpbutton;
HBITMAP bmp_duck;
HBITMAP bmp_ghost;
HBITMAP bmp_mushroom;
HBITMAP bmp_ground1_1;
HBITMAP bmp_ground1_2;
HBITMAP bmp_boom;
HBITMAP bmp_life;
HBITMAP bmp_speed;
HBITMAP bmp_ground2_1;
HBITMAP bmp_victory;
HBITMAP bmp_defeat;
HBITMAP bmp_tryagainbutton;
HBITMAP bmp_money;
HBITMAP bmp_star;
HBITMAP bmp_mirror;
HBITMAP bmp_danger;
HBITMAP bmp_police;
HBITMAP bmp_girl;
HBITMAP bmp_diamond;
HBITMAP bmp_next;
HBITMAP bmp_helpstage;
HBITMAP bmp_ok;



Stage* currentStage = NULL; //当前场景状态
vector<Unit*> units;		//单位
vector<Button*> buttons;	//按钮
vector<Enemy*>enemys;
vector<Ground*>grounds;
vector<Bullet*>bullets;
vector<Prop*>props;

int mouseX = 0;
int mouseY = 0;
bool mouseDown = false;
bool keyUpDown = false;
bool keyDownDown = false;
bool keyLeftDown = false;
bool keyRightDown = false; 
bool keyBdown = false;			//攻击
bool keyEscdown = false;



//帧
int FRAMES_HOLD[] = { 0 };
int FRAMES_HOLD_COUNT = 1;
int FRAMES_WALK[] = { 0,0,1,1,1,2,2,2,3,3,3,4,4,5,5,6,6,6,7,7,7,8,8,8,9,9};
int FRAMES_WALK_COUNT = 26;
int FRAMES_ATTACK[] = { 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
int FRAMES_ATTACK_COUNT = 24;

int FRAMES1_WALK[] = { 0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3 };
int FRAMES1_WALK_COUNT = 28;

int FRAMES2_WALK[] = { 0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3 };
int FRAMES2_WALK_COUNT = 40;

int FRAMESGROUND_STILL[] = { 0 };
int FRAMESGROUND_STILL_COUNT = 1;

int FRAMESBULLET[] = { 0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6 };
int FRAMESBULLET_COUNT = 21;


// TODO: 在此添加其它全局变量

bool flag = true;
bool left0 = true;
bool left1 = false;
bool left2 = true;
bool left3 = false;
bool left4 = false;
bool defeat = false;
bool victory = false;
bool up = true;
bool left5 = false;
int stage1 = 0;
int stage2 = 0;
int stage3 = 0;
int stage4 = 0;
bool c0ntinue = false;
bool speed = true;
bool money = true;
bool diamond = true;
bool danger = true;

int life = 3;


double const PI = acos(double(-1));


#pragma endregion


#pragma region Win32程序框架



// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CONTRAGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CONTRAGAME));

	MSG msg;

	// 主消息循环: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CONTRAGAME);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindow(szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 设置窗口样式，不可改变大小，不可最大化,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_WIDTH,
		WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT,
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		// 初始化游戏窗体
		InitGame(hWnd, wParam, lParam);
		break;
	case WM_KEYDOWN:
		// 键盘按下事件
		KeyDown(hWnd, wParam, lParam);
		break;
	case WM_KEYUP:
		// 键盘松开事件
		KeyUp(hWnd, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		// 鼠标移动事件
		MouseMove(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		// 鼠标左键按下事件
		LButtonDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		// 鼠标左键松开事件
		LButtonUp(hWnd, wParam, lParam);
		break;
	case WM_TIMER:
		// 定时器事件
		if (currentStage != NULL && currentStage->timerOn) TimerUpdate(hWnd, wParam, lParam);
		break;
	case WM_PAINT:
		// 绘图
		Paint(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


#pragma endregion


#pragma region 事件处理函数

// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	//加载图像资源
	bmp_StartButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_startbutton));
	bmp_Unit_Red = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RED));
	bmp_Unit_Blue = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BLUE));
	bmp_opening= LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_opening));
	bmp_right= LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_right));
	bmp_left= LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_left));
	bmp_chose= LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_chose));
	bmp_chose1button = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_chose1button));
	bmp_chose2button = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_chose2button));
	bmp_chose3button = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_chose3button));
	bmp_chose4button = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_chose4button));
	bmp_spring = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_spring));
	bmp_summer = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_summer));
	bmp_autumn = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_autumn));
	bmp_winter = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_winter));
	bmp_stopbutton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_stopbutton));
	bmp_stop = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_stop));
	bmp_huiyewalk = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_huiyewalk));
	bmp_restartbutton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_restart));
	bmp_continuebutton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_continue));
	bmp_menubutton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_menu));
	bmp_helpbutton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_helpbutton));
	bmp_mushroom = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_mushroom));
	bmp_duck = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_duck));
	bmp_ghost = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_ghost));
	bmp_ground1_1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_stage1ground1));
	bmp_ground1_2 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_ground1_2));
	bmp_boom = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_boom));
	bmp_life = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_life));
	bmp_speed= LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_speed));
	bmp_ground2_1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_ground2_1));
	bmp_victory = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_victory));
	bmp_defeat = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_defeat));
	bmp_tryagainbutton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_tryagain));
	bmp_money = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_money));
	bmp_star = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_star));
	bmp_mirror = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_mirror));
	bmp_danger = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_danger));
	bmp_police = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_police));
	bmp_girl = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_girl));
	bmp_diamond = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_diamond));
	bmp_next = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_next));
	bmp_helpstage = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_helpstage));
	bmp_ok = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_ok));

	//添加按钮

	Button* startButton = CreateButton(BUTTON_STARTGAME, bmp_StartButton, BUTTON_STARTGAME_WIDTH, BUTTON_STARTGAME_HEIGHT,
		620, 420);
	buttons.push_back(startButton);

	Button* chose1Button = CreateButton(BUTTON_CHOSE1, bmp_chose1button, BUTTON_CHOSE1_WIDTH, BUTTON_CHOSE1_HEIGHT,
		400, 200);
	buttons.push_back(chose1Button);

	Button* chose2Button = CreateButton(BUTTON_CHOSE2, bmp_chose2button, BUTTON_CHOSE2_WIDTH, BUTTON_CHOSE2_HEIGHT,
		750, 200);
	buttons.push_back(chose2Button);

	Button* chose3Button = CreateButton(BUTTON_CHOSE3, bmp_chose3button, BUTTON_CHOSE3_WIDTH, BUTTON_CHOSE2_HEIGHT,
		400, 400);
	buttons.push_back(chose3Button);

	Button* chose4Button = CreateButton(BUTTON_CHOSE4, bmp_chose4button, BUTTON_CHOSE4_WIDTH, BUTTON_CHOSE2_HEIGHT,
		750, 400);
	buttons.push_back(chose4Button);

	Button* stopButton = CreateButton(BUTTON_STOP, bmp_stopbutton, BUTTON_STOP_WIDTH, BUTTON_STOP_HEIGHT,
		1125, 5);
	buttons.push_back(stopButton);

	Button* reatartButton = CreateButton(BUTTON_RESTART, bmp_restartbutton, BUTTON_RESTART_WIDTH, BUTTON_RESTART_HEIGHT,
		200, 250);
	buttons.push_back(reatartButton);

	Button* continueButton = CreateButton(BUTTON_CONTINUE, bmp_continuebutton, BUTTON_CONTINUE_WIDTH, BUTTON_CONTINUE_HEIGHT,
		200, 50);
	buttons.push_back(continueButton);

	Button*menuButton = CreateButton(BUTTON_MENU, bmp_menubutton, BUTTON_MENU_WIDTH, BUTTON_MENU_HEIGHT,
		200, 450);
	buttons.push_back(menuButton);

	

	Button* tryagainButton = CreateButton(BUTTON_TRYAGAIN, bmp_tryagainbutton, BUTTON_TRYAGAIN_WIDTH, BUTTON_TRYAGAIN_HEIGHT,
		200,400);
	buttons.push_back(tryagainButton);

	Button* nextButton = CreateButton(BUTTON_NEXT, bmp_next, BUTTON_NEXT_WIDTH, BUTTON_NEXT_HEIGHT,
		750, 400);
	buttons.push_back(nextButton);

	Button* okButton = CreateButton(BUTTON_OK, bmp_ok, BUTTON_OK_WIDTH, BUTTON_OK_HEIGHT,
		950, 530);
	buttons.push_back(okButton);

	//添加子弹
	Bullet* bullet1 = CreateBullet(bmp_boom,100,100);
	bullets.push_back(bullet1);

	

	//初始化开始场景
	InitStage(hWnd, STAGE_STARTMENU);

	//初始化主计时器
	SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);
}

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_UP:
	case 'w':
	case 'W':
		keyUpDown = true;
		break;
	case VK_DOWN:
	case 's':
	case 'S':
		keyDownDown = true;
		break;
	case VK_LEFT:
	case 'a':
	case 'A':
		keyLeftDown = true;
		break;
	case VK_RIGHT:
	case 'd':
	case 'D':
		keyRightDown = true;
		break;
	case VK_SPACE:
		keyBdown = true;
		break;
	case VK_ESCAPE:
		keyEscdown = true;
		if (keyEscdown == true) {
			units.erase(units.begin(), units.end());
			enemys.erase(enemys.begin(), enemys.end());
			InitStage(hWnd, STAGE_STARTMENU);
		}
		break;
	default:
		break;
	}
}

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// TODO
	switch (wParam)
	{
	case VK_UP:
	case 'w':
	case 'W':
		keyUpDown = false;
		break;
	case VK_DOWN:
	case 's':
	case 'S':
		keyDownDown = false;
		break;
	case VK_LEFT:
	case 'a':
	case 'A':
		keyLeftDown = false;
		break;
	case VK_RIGHT:
	case 'd':
	case 'D':
		keyRightDown = false;
		break;
	case VK_SPACE:
		keyBdown = false;
		break;
	case VK_ESCAPE:
		keyEscdown = false;
	default:
		break;
	}
}

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
}

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = true;


	
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			if (button->x <= mouseX
				&& button->x + button->width >= mouseX
				&& button->y <= mouseY
				&& button->y + button->height >= mouseY)
			{
				if (button->buttonID == BUTTON_STARTGAME) {
					InitStage(hWnd, STAGE_HELP);
					victory = false;
					defeat = false;
					life = 3;
					c0ntinue = false;
					speed = true;
					enemys.erase(enemys.begin(), enemys.end());
					units.erase(units.begin(), units.end());
					props.erase(props.begin(), props.end());
					grounds.erase(grounds.begin(), grounds.end());
					break;
				}
				else if (button->buttonID == BUTTON_OK) {
					InitStage(hWnd, STAGE_CHOSE);
					break;
				}
				else if (button->buttonID == BUTTON_CHOSE1) {
					stage1 = 1;
					InitStage(hWnd, STAGE_1);
					break;
				}
				else if (button->buttonID == BUTTON_CHOSE2) {
					stage2 = 1;
					InitStage(hWnd, STAGE_2);
					break;
				}
				else if (button->buttonID == BUTTON_CHOSE3) {
					stage3 = 1;
					InitStage(hWnd, STAGE_3);
					break;
				}
				else if (button->buttonID == BUTTON_CHOSE4) {
					stage4 = 1;
					InitStage(hWnd, STAGE_4);
					break;
				}
				else if (button->buttonID == BUTTON_STOP) {
					InitStage(hWnd, STAGE_STOP);
					//props.erase(props.begin(), props.end());
					break;

				}
				else if (button->buttonID == BUTTON_MENU) {
					units.erase(units.begin(), units.end());
					enemys.erase(enemys.begin(), enemys.end());
					props.erase(props.begin(), props.end());
					defeat = false;
					victory = false;
					c0ntinue = false;
					InitStage(hWnd, STAGE_STARTMENU);
					break;
				}
				else if (button->buttonID == BUTTON_NEXT) {
					victory = false;
					defeat = false;
					life = 3;
					enemys.erase(enemys.begin(), enemys.end());
					units.erase(units.begin(), units.end());
					props.erase(props.begin(), props.end());
					grounds.erase(grounds.begin(), grounds.end());
					if (stage1 == 1) {
						stage1 = 0;
						stage2 = 1;
						InitStage(hWnd, STAGE_2);
						
					}
					else if (stage2 == 1) {
						stage2 = 0;
						stage3 = 1;
						InitStage(hWnd, STAGE_3);
						
					}
					else if (stage3 == 1) {
						stage3 = 0;
						stage4 = 1;
						InitStage(hWnd, STAGE_4);
						
					}
					else if (stage4 == 1) {
						stage4 = 0;
						InitStage(hWnd, STAGE_STARTMENU);
						
					}
					
					break;
				}
				else if (button->buttonID == BUTTON_TRYAGAIN) {
					victory = false;
					defeat = false;
					life = 3;
					c0ntinue = false;
					speed = true;
					enemys.erase(enemys.begin(), enemys.end());
					units.erase(units.begin(), units.end());
					props.erase(props.begin(), props.end());
					grounds.erase(grounds.begin(), grounds.end());
					if (stage1 == 1) {
						InitStage(hWnd, STAGE_1);
					}
					else if (stage2 == 1) {
						InitStage(hWnd, STAGE_2);
					}
					else if (stage3 == 1) {
						InitStage(hWnd, STAGE_3);
					}
					else if (stage4 == 1) {
						InitStage(hWnd, STAGE_4);
					}
					
					break;
				}
				else if (button->buttonID == BUTTON_RESTART) {
					victory = false;
					defeat = false;
					life = 3;
					enemys.erase(enemys.begin(), enemys.end());
					units.erase(units.begin(), units.end());
					props.erase(props.begin(), props.end());
					grounds.erase(grounds.begin(), grounds.end());
					if (stage1 == 1) {
						InitStage(hWnd, STAGE_1);
						stage1 = 1;
					}
					else if (stage2 == 1) {
						InitStage(hWnd, STAGE_2);
						stage2 = 1;
					}
					else if (stage3 == 1) {
					InitStage(hWnd, STAGE_3);
					stage3 = 1;
				}
					else if (stage4 == 1) {
					InitStage(hWnd, STAGE_4);
					stage4 = 1;
				}
				
					break;
				}
				else if (button->buttonID == BUTTON_CONTINUE) {
				c0ntinue = true;
				
				if (stage1 == 1) {
					InitStage(hWnd, STAGE_1);
					stage1 = 1;
				}
				else if (stage2 == 1) {
					InitStage(hWnd, STAGE_2);
					stage2 = 1;
				}
				else if (stage3 == 1) {
					InitStage(hWnd, STAGE_3);
					stage3 = 1;
				}
				else if (stage4 == 1) {
					InitStage(hWnd, STAGE_4);
					stage4 = 1;
				}
				//c0ntinue = false;
				break;
				}
			}
		}
	}

}

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = false;
}

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	
	UpdateUnits(hWnd);
	UpdateEnemy(hWnd);
	UpdateGround(hWnd);
	UpdateBullet(hWnd);
	UpdateProp(hWnd);
	if (defeat == true) {
		InitStage(hWnd, STAGE_DEFEAT);
	}
	if (victory == true) {
		InitStage(hWnd, STAGE_VICTORY);
	}
	
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}





#pragma endregion


#pragma region 其它游戏状态处理函数
//碰撞检测
int collision(Unit* unit)
{
	int c = 0;
	for (int i = 0; i < grounds.size(); i++) {
		Ground* ground = grounds[i];
		if (ground->visible)
		{
			if ((unit->x-10)>=ground->x
				&&(unit->x+10)<=(ground->x+ground->width)
				&&ground->y-(unit->y+75)<=10
				&& ground->y - (unit->y + 75) >=-10) {//从上碰撞
				c = 1;
			}
			
			if ((unit->x+23) >= ground->x
				&& (unit->x-23 ) <= (ground->x + ground->width)
				&& (unit->y - 75)-(ground->y+40) <= 10
				&& (unit->y - 75)-(ground->y+40) >= -10) {//从下碰撞
				c = 2;
			}

			if ((unit->y + 75) >= (ground->y + 40)
				&& (unit->y - 75) <= ground->y
				&& ground->x - (unit->x + 43) <= 10
				&& ground->x - (unit->x + 43) >= -10) {//从左碰撞
				c = 3;
			}
			if ((unit->y + 75) >= (ground->y + 40)
				&& (unit->y - 75) <= ground->y
				&& (unit->x -43)-(ground->x+ground->width) <= 10
				&&(unit->x + 43-(ground->x+ground->width) >= -10)) {//从右碰撞
				c = 4;
				}
			if (ground->groundID == GROUND2_1) {
				if ((unit->x - 43) >= ground->x
					&& (unit->x + 43) <= (ground->x + ground->width)
					&& ground->y - (unit->y + 75) <= 20
					&& ground->y - (unit->y + 75) >= -20) {//从上碰撞
					c = 5;
				}
			}
			if (ground->groundID == GROUND3_4) {
				if ((unit->x+unit->xx/2)>=ground->x
					&&unit->y>=ground->y
					&&unit->y<=(ground->y+160)) {
					c = 6;
				}
			}
			if (ground->groundID == GROUND3_5) {
				if ((unit->x-unit->xx/2)<=(ground->x)
					&& unit->y >= ground->y
					&& unit->y <= (ground->y + 160)) {
					c = 7;
				}
			}
			if (ground->groundID == GROUND3_2||ground->groundID==GROUND4_2) {
				if ((unit->x - 10) >= ground->x
					&& (unit->x + 10) <= (ground->x + ground->width)
					&& ground->y - (unit->y + 75) <= 10
					&& ground->y - (unit->y + 75) >= -10) {//从上碰撞
					c = 8;
				}
			}
			if (ground->groundID == GROUND4_3) {
				if ((unit->x - 43) >= ground->x
					&& (unit->x + 43) <= (ground->x + ground->width)
					&& ground->y - (unit->y + 75) <= 20
					&& ground->y - (unit->y + 75) >= -20) {//从上碰撞
					c = 9;
				}
			}
			if (ground->groundID == GROUND4_5) {
				if ((unit->x - 10) >= ground->x
					&& (unit->x + 10) <= (ground->x + ground->width)
					&& ground->y - (unit->y + 75) <= 10
					&& ground->y - (unit->y + 75) >= -10) {//从上碰撞
					c = 10;
				}
			}
		}
	}
	if (c == 1) {
		return 1;
	}
	if (c == 2) {
		return 2;
	}
	if (c == 3) {
		return 3;
	}
	if (c == 4) {
		return 4;
	}
	if (c == 5) {
		return 5;
	}
	if (c == 6) {
		return 6;
	}
	if (c == 7) {
		return 7;
	}
	if (c == 8) {
		return 8;
	}
	if (c == 9) {
		return 9;
	}
	if (c == 10) {
		return 10;
	}
	else {
		return 0;
	}
}

int collisionenemy(Unit* unit) {
	int ce = 0;
	for (int i = 0; i < enemys.size(); i++) {
		Enemy* enemy = enemys[i];
		if (enemy->visible==true) {
			if ((abs(unit->y-(enemy->y1+enemy->yy)))<=(unit->yy+enemy->yy)/2
				&&((enemy->x1+enemy->xx/2)-unit->x)<=(unit->xx+enemy->xx)/2
				&& ((enemy->x1 + enemy->xx / 2) - unit->x)>=0) {//从左碰撞
				ce = 1;
			}
			
			if ((abs(unit->y - (enemy->y1 + enemy->yy))) <= (unit->yy + enemy->yy) / 2
				&& (-(enemy->x1 + enemy->xx / 2) + unit->x) <= (unit->xx + enemy->xx) / 2+100
				&& ((enemy->x1 + enemy->xx / 2) - unit->x) <= 0) {
				ce = 2;
			}
			if (enemy->enemyID == ENEMY_GIRL) {
				if ((abs(unit->y - (enemy->y1 + enemy->yy))) <= (unit->yy + enemy->yy) / 2
					&& (-(enemy->x1 + enemy->xx / 2+150) + unit->x) <= (unit->xx + enemy->xx) / 2 + 100
					&& ((enemy->x1 + enemy->xx / 2+150) - unit->x) <= 0) {
					ce = 3;
				}
				if ((abs(unit->y - (enemy->y1 + enemy->yy))) <= (unit->yy + enemy->yy) / 2
					&& unit->x - enemy->x1 + unit->xx / 2 >= -20
					&& unit->x - enemy->x1 + unit->xx / 2 < 0) {
					ce = 4;
				}
			}
		}
		
	}
	if (ce == 1) {
		return 1;
	}
	if (ce == 2)
	{
		return 2;
	}
	if (ce == 3)
	{
		return 3;
	}
	if (ce == 4)
	{
		return 4;
	}
	else
		return 0;
}

int collisionprop(Unit* unit)
{
	for (int i = 0; i < props.size(); i++) {
		Prop* prop = props[i];
		if(prop->visible==true){
			if (abs((unit->x-(prop->x+prop->width/2)))<=((unit->xx+prop->width))/2
				&& abs((unit->y - (prop->y + prop->height / 2))) <= ((unit->yy + prop->height)) / 2) {
				if (prop->propID == SPEED) {
					return 1;
				}
				if (prop->propID == MONEY) {
					return 2;
				}
				if (prop->propID == STAR) {
					return 3;
				}
				if (prop->propID == DIAMOND) {
					return 4;
				}
			}

			
			
		}
	}
}

int collisionbullet(Enemy* enemy)
{
	int co = 0;
	Unit* unit = units[0];
	for (int i = 0; i < bullets.size(); i++) {
		Bullet* bullet = bullets[i];
		if (bullet->visible == true) {
			if (bullet->x >= enemy->x1
				&&bullet->x<=enemy->x1+50
				&&unit->direction==UNIT_DIRECT_LEFT
				&&bullet->y>=enemy->y1-200
				&&(bullet->y+bullet->height)<=(enemy->y1+enemy->yy)+200) {
				co = 1;
			}
			if (bullet->x >= enemy->x1 
				&& bullet->x <= enemy->x1 + 50
				&& unit->direction == UNIT_DIRECT_RIGHT
				&& bullet->y >= enemy->y1-200
				&& (bullet->y + bullet->height) <= (enemy->y1 + enemy->yy)+200) {
				co = 2;
			}
			if (bullet->x >= enemy->x1-200
				&& bullet->x <= enemy->x1 + 350
				&& unit->direction == UNIT_DIRECT_LEFT
				&& bullet->y >= enemy->y1 - 200
				&& (bullet->y + bullet->height) <= (enemy->y1 + enemy->yy) + 200) {
				co = 3;
			}
			if (bullet->x >= enemy->x1-200
				&& bullet->x <= enemy->x1 + 350
				&& unit->direction == UNIT_DIRECT_RIGHT
				&& bullet->y >= enemy->y1 - 200
				&& (bullet->y + bullet->height) <= (enemy->y1 + enemy->yy) + 200) {
				co = 3;
			}
		}
	}
	if (co == 1) {
		return 1;
	}
	if (co == 2) {
		return 2;
	}
	if (co == 3) {
		return 3;
	}
	else {
		return 0;
	}
}


//TODO: 添加游戏需要的更多函数

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int width, int height, int x, int y)
{
	Button* button = new Button();
	button->buttonID = buttonID;
	button->img = img;
	button->width = width;
	button->height = height;
	button->x = x;
	button->y = y;

	button->visible = true;
	return button;
}

Prop* CreateProp(int propID, HBITMAP img, int width, int height, int x, int y)
{
	Prop* prop = new Prop();
	prop->propID = propID;
	prop->img = img;
	prop->width = width;
	prop->height = height;
	prop->x = x;
	prop->y = y;

	prop->visible = true;
	return prop;
}


// 添加主角函数
Unit* CreateUnit(int side, int type, int x, int y,int health)
{
	Unit* unit = new Unit();
	unit->side = side;
	if (side == UNIT_SIDE_RED) {
		unit->img = bmp_Unit_Red;
		unit->direction = UNIT_DIRECT_LEFT;
	}
	if (side == UNIT_SIDE_BLUE) {
		unit->img = bmp_huiyewalk;
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	

	unit->type = 0;
	unit->state = UNIT_STATE_HOLD;


	unit->frame_row = 0;
	unit->frame_column = UNIT_LAST_FRAME * unit->direction;

	unit->frame_sequence = FRAMES_HOLD;
	unit->frame_count = FRAMES_HOLD_COUNT;
	unit->frame_id = 0;

	unit->x = x;
	unit->y = y;
	unit->vx = 0;
	unit->vy = 0;
	unit->health = health;
	unit->xx = UNIT_SIZE_X;
	unit->yy = UNIT_SIZE_Y;
	
	return unit;
}


// 添加敌人函数
Enemy* CreateEnemy(int side, int type, int x1, int y1, int health1)
{
	
	Enemy* enemy = new Enemy();
	enemy->side = side;
	if (side == ENEMY_SIDE_GHOST) {
		enemy->img = bmp_ghost;
		enemy->direction = UNIT_DIRECT_LEFT;
		enemy->type = ENEMY_TYPE_FLY;

		enemy->frame1_row = 0;
		enemy->frame1_column = GHOST_LAST_FRAME * enemy->direction;

		enemy->frame1_sequence = FRAMES2_WALK;
		enemy->frame1_count = FRAMES2_WALK_COUNT;
		enemy->frame1_id = 0;
		enemy->visible = true;

		enemy->x1 = x1;
		enemy->y1 = y1;
		enemy->vx1 = ENEMY_SPEED;
		enemy->vy1 = 0;
		enemy->health1 = health1;
		return enemy;
	}
	if (side == ENEMY_SIDE_DUCK) {
		enemy->img = bmp_duck;
		enemy->direction = UNIT_DIRECT_LEFT;
		enemy->type = ENEMY_TYPE_COMMEN2;
		enemy->state = ENEMY_WALK;


		enemy->frame1_row = 0;
		enemy->frame1_column = MUSHROOM_LAST_FRAME * enemy->direction;

		enemy->frame1_sequence = FRAMES1_WALK;
		enemy->frame1_count = FRAMES1_WALK_COUNT;
		enemy->frame1_id = 0;

		enemy->x1 = x1;
		enemy->y1 = y1;
		enemy->vx1 = ENEMY_SPEED;
		enemy->vy1 = 0;
		enemy->health1 = health1;
		enemy->visible = true;
		return enemy;

	}

	if (side == ENEMY_SIDE_DUCK1) {
		enemy->img = bmp_duck;
		enemy->direction = UNIT_DIRECT_LEFT;
		enemy->type = ENEMY_TYPE_COMMEN3;
		enemy->state = ENEMY_WALK;


		enemy->frame1_row = 0;
		enemy->frame1_column = MUSHROOM_LAST_FRAME * enemy->direction;

		enemy->frame1_sequence = FRAMES1_WALK;
		enemy->frame1_count = FRAMES1_WALK_COUNT;
		enemy->frame1_id = 0;

		enemy->visible = true;
		enemy->x1 = x1;
		enemy->y1 = y1;
		enemy->vx1 = ENEMY_SPEED;
		enemy->vy1 = 0;
		enemy->health1 = health1;
		return enemy;
	}
	if(side==ENEMY_SIDE_MUSHROOM) {
		enemy->img = bmp_mushroom;
		enemy->direction = UNIT_DIRECT_LEFT;
		enemy->type = ENEMY_TYPE_COMMEN;
		enemy->state = ENEMY_WALK;


		enemy->frame1_row = 0;
		enemy->frame1_column = MUSHROOM_LAST_FRAME * enemy->direction;

		enemy->frame1_sequence = FRAMES1_WALK;
		enemy->frame1_count = FRAMES1_WALK_COUNT;
		enemy->frame1_id = 0;

		enemy->x1 = x1;
		enemy->y1 = y1;
		enemy->vx1 = ENEMY_SPEED;
		enemy->vy1 = 0;
		enemy->health1 = health1;
		enemy->visible = true;
		return enemy;
	}

	if (side == ENEMY_SIDE_MUSHROOM1) {
		enemy->img = bmp_mushroom;
		enemy->direction = UNIT_DIRECT_LEFT;
		enemy->type = ENEMY_TYPE_COMMEN1;
		enemy->state = ENEMY_WALK;


		enemy->frame1_row = 0;
		enemy->frame1_column = MUSHROOM_LAST_FRAME * enemy->direction;

		enemy->frame1_sequence = FRAMES1_WALK;
		enemy->frame1_count = FRAMES1_WALK_COUNT;
		enemy->frame1_id = 0;

		enemy->visible = true;
		enemy->x1 = x1;
		enemy->y1 = y1;
		enemy->vx1 = ENEMY_SPEED;
		enemy->vy1 = 0;
		enemy->health1 = health1;
		return enemy;
	}

	if(side==ENEMY_SIDE_GIRL)
	{
		enemy->img = bmp_girl;
		enemy->direction = UNIT_DIRECT_LEFT;
		enemy->type = ENEMY_TYPE_GIRL;
		enemy->state = ENEMY_WALK;


		enemy->frame1_row = 0;
		enemy->frame1_column = GIRL_LAST_FRAME * enemy->direction;

		enemy->frame1_sequence = FRAMES_WALK;
		enemy->frame1_count = FRAMES_WALK_COUNT;
		enemy->frame1_id = 0;

		enemy->visible = true;
		enemy->x1 = x1;
		enemy->y1 = y1;
		enemy->vx1 = ENEMY_SPEED;
		enemy->vy1 = 0;
		enemy->health1 = health1;
		return enemy;
	}
}

//添加地砖函数
Ground* CreateGround(int groundID, HBITMAP img, int width, int height, int x, int y,int type)
{
	Ground* ground = new Ground();
	ground->groundID = groundID;
	ground->img = img;
	ground->width = width;
	ground->height = height;
	ground->x = x;
	ground->y = y;
	ground->type = type;

	ground->visible = true;
	return ground;
}

//添加子弹函数
Bullet* CreateBullet(HBITMAP img,int width,int height)
{
	Bullet* bullet = new Bullet();
	bullet->img = img;
	bullet->width = width;
	bullet->height = height;
	
	bullet->visible = false;

	return bullet;
}

// 初始化游戏场景函数
void InitStage(HWND hWnd, int stageID)
{
	// 初始化场景实例
	if (currentStage != NULL) delete currentStage;
	currentStage = new Stage();
	currentStage->stageID = stageID;


	if (stageID == STAGE_STARTMENU) {
		PlaySound((LPCTSTR)IDR_WAVE2, NULL, SND_RESOURCE | SND_ASYNC);
		currentStage->bg = bmp_opening;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		defeat = false;
		life = 3;
		victory = false;
		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STARTGAME|| button->buttonID == BUTTON_HELP)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}

	else if (stageID == STAGE_1) //TODO：添加多个游戏场景
	{
		PlaySound((LPCTSTR)IDR_WAVE1, NULL, SND_RESOURCE | SND_ASYNC);
		currentStage->bg = bmp_spring;
		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;

		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];

			if (button->buttonID == BUTTON_STOP
				|| button->buttonID == BUTTON_HELP) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}

		for (int i = 0; i < grounds.size(); i++)
		{
			Ground* ground = grounds[i];

			if (ground->groundID == GROUND1_1|| ground->groundID == GROUND1_2  ) //TODO：加载游戏界面需要的按钮
			{
				ground->visible = true;
			}
			else
			{
				ground->visible = false;
			}
		}

		for (int i = 0; i < props.size(); i++) {
			Prop* prop = props[i];
			if (prop->propID == SPEED && speed == true) {
				prop->visible = true;
			}
			if (prop->propID == STAR) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE3  && life == 3) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE2 && life == 3) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE1 && life == 3) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE2 &&life == 2) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE1 && life == 2) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE1 && life == 1) {
				prop->visible = true;
			}
		}
	}

	else if (stageID == STAGE_HELP) {
		currentStage->bg = bmp_helpstage;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		defeat = false;
		//显示选择界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID ==BUTTON_OK)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
		for (int i = 0; i < grounds.size(); i++)
		{
			Ground* ground = grounds[i];
			ground->visible = false;
		}

	}

	else if (stageID == STAGE_CHOSE) {
		currentStage->bg = bmp_chose;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;
		defeat = false;
		//显示选择界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_CHOSE1|| button->buttonID == BUTTON_CHOSE2|| button->buttonID == BUTTON_CHOSE3|| button->buttonID == BUTTON_CHOSE4 || button->buttonID == BUTTON_HELP)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
		for (int i = 0; i < grounds.size(); i++)
		{
			Ground* ground = grounds[i];
				ground->visible = false;
		}
		
	}

	else if (stageID == STAGE_2) {
		PlaySound((LPCTSTR)IDR_WAVE1, NULL, SND_RESOURCE | SND_ASYNC);
		currentStage->bg = bmp_summer;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = true;

		//显示选择界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STOP 
				|| button->buttonID == BUTTON_HELP)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}

		for (int i = 0; i < grounds.size(); i++)
		{
			Ground* ground = grounds[i];

			if (ground->groundID == GROUND2_1 || ground->groundID == GROUND2_2|| ground->groundID == GROUND2_3|| ground->groundID == GROUND2_5) //TODO：加载游戏界面需要的按钮
			{
				ground->visible = true;
			}
			if (ground->groundID == GROUND2_4 && money == true) {
				
				ground->visible = true;
			}
		}

		for (int i = 0; i < props.size(); i++) {
			Prop* prop = props[i];
			if (prop->propID == MONEY && money == true) {
				prop->visible = true;
			}
			if (prop->propID == STAR) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE3 && life == 3) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE2 && life == 3) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE1 && life == 3) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE2 && life == 2) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE1 && life == 2) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE1 && life == 1) {
				prop->visible = true;
			}
		}
	}

	else if (stageID == STAGE_3) {
		PlaySound((LPCTSTR)IDR_WAVE1, NULL, SND_RESOURCE | SND_ASYNC);
		currentStage->bg = bmp_autumn;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = true;

		//显示选择界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STOP 
				|| button->buttonID == BUTTON_HELP)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}

		for (int i = 0; i < grounds.size(); i++)
		{
			Ground* ground = grounds[i];

			if (ground->groundID == GROUND3_1 
				|| ground->groundID == GROUND3_3 
				|| ground->groundID == GROUND3_4
				|| ground->groundID == GROUND3_5
				|| ground->groundID == GROUND3_6) //TODO：加载游戏界面需要的按钮
			{
				ground->visible = true;
			}
			if (ground->groundID == GROUND3_2 && danger == true) {
				ground->visible = true;
			}
		}

		for (int i = 0; i < props.size(); i++) {
			Prop* prop = props[i];
			
			if (prop->propID == STAR) {
				prop->visible = true;
			}
			if (prop->propID == SPEED && speed == true) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE3 && life == 3) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE2 && life == 3) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE1 && life == 3) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE2 && life == 2) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE1 && life == 2) {
				prop->visible = true;
			}
			if (prop->propID == BUTTON_LIFE1 && life == 1) {
				prop->visible = true;
			}
		}
	}

	else if (stageID == STAGE_4) {
	PlaySound((LPCTSTR)IDR_WAVE1, NULL, SND_RESOURCE | SND_ASYNC);
	currentStage->bg = bmp_winter;
	currentStage->timeCountDown = 0;
	currentStage->timerOn = true;

	//显示选择界面的按钮
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->buttonID == BUTTON_STOP 
			|| button->buttonID == BUTTON_HELP)
		{
			button->visible = true;
		}
		else
		{
			button->visible = false;
		}
	}
	for (int i = 0; i < grounds.size(); i++)
	{
		Ground* ground = grounds[i];

		if (ground->groundID == GROUND4_1
			|| ground->groundID == GROUND4_3
			|| ground->groundID == GROUND4_4
			|| ground->groundID == GROUND4_5
			|| ground->groundID == GROUND4_6) //TODO：加载游戏界面需要的按钮
		{
			ground->visible = true;
		}
		if (ground->groundID == GROUND4_2 && danger == true) {
			ground->visible = true;
		}
		if (ground->groundID == GROUND4_5 && diamond == true) {
			ground->visible = true;
		}

	}
	for (int i = 0; i < props.size(); i++) {
		Prop* prop = props[i];

		if (prop->propID == STAR) {
			prop->visible = true;
		}
		if (prop->propID == DIAMOND && diamond == true) {
			prop->visible = true;
		}
		if (prop->propID == BUTTON_LIFE3 && life == 3) {
			prop->visible = true;
		}
		if (prop->propID == BUTTON_LIFE2 && life == 3) {
			prop->visible = true;
		}
		if (prop->propID == BUTTON_LIFE1 && life == 3) {
			prop->visible = true;
		}
		if (prop->propID == BUTTON_LIFE2 && life == 2) {
			prop->visible = true;
		}
		if (prop->propID == BUTTON_LIFE1 && life == 2) {
			prop->visible = true;
		}
		if (prop->propID == BUTTON_LIFE1 && life == 1) {
			prop->visible = true;
		}
	}
	}

	else if (stageID == STAGE_STOP) //TODO：添加多个游戏场景
	{
	currentStage->bg = bmp_stop;
	currentStage->timeCountDown = 0;
	currentStage->timerOn = false;

	//显示游戏界面的按钮
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];

		if (button->buttonID == BUTTON_RESTART|| button->buttonID == BUTTON_CONTINUE|| button->buttonID == BUTTON_MENU || button->buttonID == BUTTON_HELP) //TODO：加载游戏界面需要的按钮
		{
			button->visible = true;
		}
		else
		{
			button->visible = false;
		}
	}
		for (int i = 0; i < grounds.size(); i++)
		{
			Ground* ground = grounds[i];
			ground->visible = false;
		}

		for (int i = 0; i < props.size(); i++) {
			Prop* prop = props[i];
			prop->visible = false;
		}
	}

	else if(stageID==STAGE_DEFEAT){
	currentStage->bg = bmp_defeat;
	currentStage->timeCountDown = 0;
	currentStage->timerOn = false;

	for (int i = 0; i < buttons.size(); i++) {
		Button* button = buttons[i];
		if (button->buttonID == BUTTON_TRYAGAIN) {
			button->visible = true;
		}
	}
	for (int i = 0; i < props.size(); i++) {
		Prop* prop = props[i];
		prop->visible = false;
	}
	for (int i = 0; i < bullets.size(); i++) {
		Bullet* bullet = bullets[i];
		bullet->visible = false;
	}
}

	else if (stageID == STAGE_VICTORY) {
		currentStage->bg = bmp_victory;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;

		for (int i = 0; i < buttons.size(); i++) {
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_NEXT) {
				button->visible = true;
			}
		}
		for (int i = 0; i < props.size(); i++) {
			Prop* prop = props[i];
			prop->visible = false;
		}
		for (int i = 0; i < bullets.size(); i++) {
			Bullet* bullet = bullets[i];
			bullet->visible = false;
		}
	
    }


	if (c0ntinue == false) {
		// 按场景初始化单位
		if (stageID == STAGE_1) {
			units.push_back(CreateUnit(UNIT_SIDE_BLUE, UNIT_TYPE_HOPLITE, 100, 500, 100));
			enemys.push_back(CreateEnemy(ENEMY_SIDE_MUSHROOM, ENEMY_TYPE_COMMEN, 1000, 450, 10));
			enemys.push_back(CreateEnemy(ENEMY_SIDE_MUSHROOM1, ENEMY_TYPE_COMMEN1, 200, 75, 10));
			props.push_back(CreateProp(SPEED, bmp_speed, SPEED_WIDTH, SPEED_HEIGHT,
				730, 320));
			props.push_back(CreateProp(BUTTON_LIFE1, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				10, 5));
			props.push_back(CreateProp(BUTTON_LIFE2, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				85, 5));
			props.push_back(CreateProp(BUTTON_LIFE3, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				160, 5));
			props.push_back(CreateProp(STAR, bmp_star, STAR_WIDTH, STAR_HEIGHT,
				130, 145));

			grounds.push_back(CreateGround(GROUND1_1, bmp_ground1_1, GROUND1_1_WIDTH, GROUND1_1_HEIGHT,
				0, 575, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND1_2, bmp_ground1_2, GROUND1_2_WIDTH, GROUND1_2_HEIGHT,
				600, 380, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND1_2, bmp_ground1_2, GROUND1_2_WIDTH, GROUND1_2_HEIGHT,
				100, 200, GROUND_TYPE_COMMEN));
			UNIT_SPEED = 4.0;


		}
		else if (stageID == STAGE_2) {
			units.push_back(CreateUnit(UNIT_SIDE_BLUE, UNIT_TYPE_HOPLITE, 100, 500, 3));
			enemys.push_back(CreateEnemy(ENEMY_SIDE_GHOST, ENEMY_TYPE_FLY, 1000, 100, 20));
			props.push_back(CreateProp(STAR, bmp_star, STAR_WIDTH, STAR_HEIGHT,
				1100, 520));
			props.push_back(CreateProp(BUTTON_LIFE1, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				10, 5));
			props.push_back(CreateProp(BUTTON_LIFE2, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				85, 5));
			props.push_back(CreateProp(BUTTON_LIFE3, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				160, 5));
			props.push_back(CreateProp(MONEY, bmp_money, MONEY_WIDTH, MONEY_HEIGHT,
				400, 95));

			grounds.push_back(CreateGround(GROUND2_1, bmp_ground2_1, 200, 40, 200, 355, GROUND_TYPE_MOVE));
			grounds.push_back(CreateGround(GROUND2_2, bmp_ground1_2, GROUND1_2_WIDTH, GROUND1_2_HEIGHT,
				0, 575, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND2_3, bmp_ground1_2, GROUND1_2_WIDTH, GROUND1_2_HEIGHT,
				1000, 575, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND2_4, bmp_ground1_2, GROUND1_2_WIDTH, GROUND1_2_HEIGHT,
				900, 455, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND2_5, bmp_ground2_1, 200, 40,
				325, 155, GROUND_TYPE_COMMEN));

			UNIT_SPEED = 4.0;
		}
		else if (stageID == STAGE_3) {
			units.push_back(CreateUnit(UNIT_SIDE_BLUE, UNIT_TYPE_HOPLITE, 100, 500, 100));
			enemys.push_back(CreateEnemy(ENEMY_SIDE_DUCK, ENEMY_TYPE_COMMEN2, 1000, 400, 30));
			enemys.push_back(CreateEnemy(ENEMY_SIDE_DUCK1, ENEMY_TYPE_COMMEN3, 300, 50, 30));
			grounds.push_back(CreateGround(GROUND3_6, bmp_ground1_1, GROUND1_1_WIDTH, GROUND1_1_HEIGHT,
				0, 200, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND3_1, bmp_ground1_2, GROUND1_2_WIDTH, GROUND1_2_HEIGHT,
				0, 575, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND3_2, bmp_danger, 200, 40, 470, 500, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND3_3, bmp_ground1_2, GROUND1_2_WIDTH, GROUND1_2_HEIGHT,
				800, 550, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND3_4, bmp_mirror, 30, 160,
				1155, 390, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND3_5, bmp_mirror, 30, 160,
				0, 42, GROUND_TYPE_COMMEN));
			props.push_back(CreateProp(SPEED, bmp_speed, SPEED_WIDTH, SPEED_HEIGHT,
				550, 445));
			props.push_back(CreateProp(BUTTON_LIFE1, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				10, 5));
			props.push_back(CreateProp(BUTTON_LIFE2, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				85, 5));
			props.push_back(CreateProp(BUTTON_LIFE3, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				160, 5));
			props.push_back(CreateProp(STAR, bmp_star, STAR_WIDTH, STAR_HEIGHT,
				1100, 142));
			UNIT_SPEED = 4.0;
		}
		else if (stageID == STAGE_4) {
			units.push_back(CreateUnit(UNIT_SIDE_BLUE, UNIT_TYPE_HOPLITE, 100, 500, 50));
			UNIT_SPEED = 4.0;
			props.push_back(CreateProp(STAR, bmp_star, STAR_WIDTH, STAR_HEIGHT,
				1110, 315));
			props.push_back(CreateProp(BUTTON_LIFE1, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				10, 5));
			props.push_back(CreateProp(BUTTON_LIFE2, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				85, 5));
			props.push_back(CreateProp(BUTTON_LIFE3, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				160, 5));
			props.push_back(CreateProp(DIAMOND, bmp_diamond, DIAMOND_WIDTH, DIAMOND_HEIGHT,
				40, 150));

			enemys.push_back(CreateEnemy(ENEMY_SIDE_GIRL, ENEMY_TYPE_GIRL, 200, 55, 50));

			grounds.push_back(CreateGround(GROUND4_1, bmp_ground1_2, GROUND1_2_WIDTH, GROUND1_2_HEIGHT,
				-200, 575, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND4_2, bmp_danger, 200, 40, 300, 500, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND4_3, bmp_ground2_1, 200, 40, 630, 550, GROUND_TYPE_UP));
			grounds.push_back(CreateGround(GROUND4_4, bmp_ground1_2, GROUND1_2_WIDTH, GROUND1_2_HEIGHT,
				900, 375, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND4_5, bmp_police, GROUND1_2_WIDTH, GROUND1_2_HEIGHT,
				900, 375, GROUND_TYPE_COMMEN));
			grounds.push_back(CreateGround(GROUND4_6, bmp_ground1_1, GROUND1_1_WIDTH, GROUND1_1_HEIGHT,
				-600, 200, GROUND_TYPE_COMMEN));
		}
	}

	
	/*if (c0ntinue == true) {
		if (stageID == STAGE_1) {

			props.push_back(CreateProp(SPEED, bmp_speed, SPEED_WIDTH, SPEED_HEIGHT,
				730, 320));
			props.push_back(CreateProp(BUTTON_LIFE1, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				10, 5));
			props.push_back(CreateProp(BUTTON_LIFE2, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				85, 5));
			props.push_back(CreateProp(BUTTON_LIFE3, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				160, 5));
			props.push_back(CreateProp(STAR, bmp_star, STAR_WIDTH, STAR_HEIGHT,
				130, 145));




		}
		else if (stageID == STAGE_2) {

			props.push_back(CreateProp(STAR, bmp_star, STAR_WIDTH, STAR_HEIGHT,
				1100, 520));
			props.push_back(CreateProp(BUTTON_LIFE1, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				10, 5));
			props.push_back(CreateProp(BUTTON_LIFE2, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				85, 5));
			props.push_back(CreateProp(BUTTON_LIFE3, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				160, 5));
			props.push_back(CreateProp(MONEY, bmp_money, MONEY_WIDTH, MONEY_HEIGHT,
				400, 95));


		}
		else if (stageID == STAGE_3) {

			props.push_back(CreateProp(SPEED, bmp_speed, SPEED_WIDTH, SPEED_HEIGHT,
				550, 445));
			props.push_back(CreateProp(BUTTON_LIFE1, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				10, 5));
			props.push_back(CreateProp(BUTTON_LIFE2, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				85, 5));
			props.push_back(CreateProp(BUTTON_LIFE3, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				160, 5));
			props.push_back(CreateProp(STAR, bmp_star, STAR_WIDTH, STAR_HEIGHT,
				1100, 142));

		}
		else if (stageID == STAGE_4) {

			props.push_back(CreateProp(STAR, bmp_star, STAR_WIDTH, STAR_HEIGHT,
				1110, 315));
			props.push_back(CreateProp(BUTTON_LIFE1, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				10, 5));
			props.push_back(CreateProp(BUTTON_LIFE2, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				85, 5));
			props.push_back(CreateProp(BUTTON_LIFE3, bmp_life, BUTTON_LIFE_WIDTH, BUTTON_LIFE_HEIGHT,
				160, 5));
			props.push_back(CreateProp(DIAMOND, bmp_diamond, DIAMOND_WIDTH, DIAMOND_HEIGHT,
				40, 150));


		}
	}*/
	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}


// 刷新单位状态函数
void UpdateUnits(HWND hWnd)
{
	for (int i = 0; i < units.size(); i++) {
		Unit* unit = units[i];

		//根据单位类型选择行为函数
		switch (unit->type) {
		case UNIT_TYPE_CASTER:
			UnitBehaviour_1(unit);
			break;
		case UNIT_TYPE_REAPER:
		case UNIT_TYPE_SABER:
		case UNIT_TYPE_SHIELDER:
		case UNIT_TYPE_HOPLITE:
			UnitBehaviour_2(unit);
			break;
		}
	}
}

//刷新敌人状态函数
void UpdateEnemy(HWND hWnd)
{
	for (int i = 0; i < enemys.size(); i++) {
		Enemy* enemy = enemys[i];

		//根据敌人类型选择行为函数
		if (enemy->type == ENEMY_TYPE_COMMEN) {
			EnemyBehaviour_1(enemy);
		}
		if (enemy->type == ENEMY_TYPE_FLY) {
			EnemyBehaviour_2(enemy);
		}
		if (enemy->type == ENEMY_TYPE_COMMEN1) {
			EnemyBehaviour_3(enemy);
		}
		if (enemy->type == ENEMY_TYPE_COMMEN2) {
			EnemyBehaviour_4(enemy);
		}
		if (enemy->type == ENEMY_TYPE_COMMEN3) {
			EnemyBehaviour_5(enemy);
		}
		if (enemy->type == ENEMY_TYPE_GIRL) {
			EnemyBehaviour_6(enemy);
		}
	}
}

//刷新地砖状态函数
void UpdateGround(HWND hWnd)
{
	for (int i = 0; i < grounds.size(); i++) {
		Ground* ground = grounds[i];

		//根据敌人类型选择行为函数
		if (ground->type == GROUND_TYPE_COMMEN) {
			GroundBehaviour_1(ground);
		}
		if (ground->type == GROUND_TYPE_MOVE) {
			GroundBehaviour_2(ground);
		}
		if (ground->type == GROUND_TYPE_UP) {
			GroundBehaviour_3(ground);
		}
	}
}

//刷新子弹状态函数
void UpdateBullet(HWND hWnd)
{
	for (int i = 0; i < bullets.size(); i++) {
		Bullet* bullet = bullets[i];
		bullet->frame_sequence = FRAMESBULLET;
		bullet->frame_count = FRAMESBULLET_COUNT;

		bullet->frame_id++;
		bullet->frame_id = bullet->frame_id % bullet->frame_count;

		int column = bullet->frame_sequence[bullet->frame_id];
		bullet->frame_column = column;

		bullet->x = bullet->x + bullet->vx;
	}
}

//刷新道具状态函数
void UpdateProp(HWND hWnd)
{
	for (int i = 0; i < props.size(); i++) {
		Prop* prop = props[i];
		if (prop->visible == false) {
			prop->visible = false;
		}
	}
}

//单位行为函数
void UnitBehaviour_1(Unit* unit) {

	double dirX = mouseX - unit->x;
	double dirY = mouseY - unit->y;
	double dirLen = sqrt(dirX * dirX + dirY * dirY) + 0.0001;


	if (dirX > 0) {
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else {
		unit->direction = UNIT_DIRECT_LEFT;
	}


	//判断当前状态, 以及判断是否需要状态变化
	int next_state = unit->state;
	switch (unit->state) {
	case UNIT_STATE_HOLD:
		if (dirLen < 400) {
			next_state = UNIT_STATE_WALK;
		}
		break;
	case UNIT_STATE_WALK:
		if (dirLen >= 400) {
			next_state = UNIT_STATE_HOLD;
		}
		else if (dirLen < 200) {
			next_state = UNIT_STATE_ATTACK;
		}
		else {
			unit->vx = dirX / dirLen * UNIT_SPEED;
			unit->vy = dirY / dirLen * UNIT_SPEED;
		}
		break;
	case UNIT_STATE_ATTACK:
		if (dirLen >= 200) {
			next_state = UNIT_STATE_WALK;
		}
		break;
	};

	if (next_state != unit->state) {
		//状态变化
		unit->state = next_state;
		unit->frame_id = -1;

		switch (unit->state) {
		case UNIT_STATE_HOLD:
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		case UNIT_STATE_WALK:
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = UNIT_SPEED;
			unit->vy = UNIT_SPEED;
			break;
		case UNIT_STATE_ATTACK:
			unit->frame_sequence = FRAMES_ATTACK;
			unit->frame_count = FRAMES_ATTACK_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		case UNIT_STATE_JUMP:
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			unit->vy = UNIT_SPEED;
		};
	}

	//动画运行到下一帧
	unit->x += unit->vx;
	unit->y += unit->vy;

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);


}

void UnitBehaviour_2(Unit* unit) {

	
	//判断当前状态, 以及判断是否需要状态变化
	int next_state = unit->state;

	if (keyLeftDown == true) {
		unit->direction = UNIT_DIRECT_LEFT;
		next_state = UNIT_STATE_WALK;
	}
	if (keyRightDown == true) {
		unit->direction = UNIT_DIRECT_RIGHT;
		next_state = UNIT_STATE_WALK;
	}
	if (keyUpDown == true) {
		next_state = UNIT_STATE_JUMP;
		flag = true;
	}
	if (keyDownDown == true) {
		next_state = UNIT_STATE_HOLD;
		
	}
	if (keyBdown == true) {
		for (int i = 0; i < bullets.size(); i++) {
			Bullet*bullet = bullets[i];
			if (bullet->visible == false) {
				next_state = UNIT_STATE_ATTACK;
			}
		}
		
		
	}
	if(keyLeftDown == false && keyRightDown == false  && keyDownDown == false && keyBdown == false&& keyUpDown == false&& keyUpDown == false)
	{
		next_state = UNIT_STATE_HOLD;
	}
	
	if (keyUpDown == false)
	{
		//flag = true;
	}
	
	


	if (collision(unit)==1) {
		unit->vy = 0;
	}
	if (collision(unit) == 2 ) {
		unit->vy = 0;
		unit->vy = unit->vy + 3.0;
	}
	if (collision(unit) == 3) {
		unit->vx = 0;
	}
	if (collision(unit) == 4) {
		unit->vx = 0;
	}
	if (collision(unit) == 5) {
		for (int i = 0; i < grounds.size(); i++) {
			Ground* ground = grounds[i];
			if (ground->groundID == GROUND2_1) {
				if (ground->direction == UNIT_DIRECT_LEFT) {
					unit->x = unit->x - 2;
				}
				if (ground->direction == UNIT_DIRECT_RIGHT) {
					unit->x = unit->x + 2;
				}
			}
		}
	}
	if (collision(unit) == 6) {
		unit->y = 135;
		unit->x = 50;
	}
	if (collision(unit) == 7) {
		unit->y = 480;
		unit->x = 1110;
	}
	if (collision(unit) == 8) {
		for (int i = 0; i < grounds.size(); i++) {
			Ground* ground = grounds[i];
			if (ground->groundID == GROUND3_2||ground->groundID==GROUND4_2) {
				ground->visible = false;
				danger = false;
			}
		}
	}
	if (collision(unit) == 9) {
		if (up == true) {
			unit->y = unit->y - 2;
		}
		if (up == false) {
			unit->y = unit->y + 2;
		}
	}
	if (collision(unit) == 10) {
		defeat = true;
	}
	if (collision(unit) == 0) {
		unit->vy = unit->vy + 1.0;
	}

	
	if (collisionenemy(unit) == 1) {
		unit->x = unit->x - 80;
		Prop* prop = props[life];
		prop->visible = false;
		life--;
	}
	if (collisionenemy(unit) == 2) {
		unit->x = unit->x + 80;
		Prop* prop = props[life];
		prop->visible = false;
		life--;
	}
	if (collisionenemy(unit) == 3) {
		unit->x = unit->x + 80;
		Prop* prop = props[life];
		prop->visible = false;
		life--;
	}
	if (collisionenemy(unit) == 4) {
		unit->x = unit->x + 80;
		Prop* prop = props[life];
		prop->visible = false;
		life--;
	}
	if (life == 0) {
		defeat = true;
	}


	if (collisionprop(unit) == 1) {
		UNIT_SPEED = 8.0;
		speed = false;
		for (int i = 0; i < props.size(); i++) {
			Prop* prop = props[i];
			if (prop->propID == SPEED) {
				prop->visible = false;
			}
		}
	
	}
	if (collisionprop(unit) == 2) {
		
		for (int i = 0; i < grounds.size(); i++) {
			Ground* ground = grounds[i];
			if (ground->groundID == GROUND2_4) {
				ground->visible = false;
				danger = false;
			}
		}
		for (int i = 0; i < props.size(); i++) {
			Prop* prop = props[i];
			if (prop->propID == MONEY) {
				money = false;
				prop->visible = false;
			}
		}
	}
	if (collisionprop(unit) == 3) {
		for (int i = 0; i < props.size(); i++) {
			Prop* prop = props[i];
			if (prop->propID == STAR) {
				prop->visible = false;
			}
		}
		victory = true;
	}

	if (collisionprop(unit) == 4) {
		for (int i = 0; i < grounds.size(); i++) {
			Ground* ground = grounds[i];
			if (ground->groundID == GROUND4_5) {
				ground->visible = false;
			}
		}
		for (int i = 0; i < props.size(); i++) {
			Prop* prop = props[i];
			if (prop->propID == DIAMOND) {
				prop->visible = false;
				diamond = false;
			}
		}
	}


	
	
	if (next_state != unit->state) {
		//状态变化
		unit->state = next_state;
		unit->frame_id = -1;

		//unit->vy = -UNIT_SPEED;


		if (unit->state == UNIT_STATE_HOLD) {
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			unit->vy = 0;
		}
		if (unit->state == UNIT_STATE_WALK) {
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			if (unit->direction == UNIT_DIRECT_RIGHT) {
				unit->vx = UNIT_SPEED;
			}
			else {
				unit->vx = (-1) * UNIT_SPEED;
			}
		}
		if (unit->state == UNIT_STATE_ATTACK) {
			unit->frame_sequence = FRAMES_ATTACK;
			unit->frame_count = FRAMES_ATTACK_COUNT;
			Bullet* bullet = CreateBullet(bmp_boom, 100, 100);
			bullets.push_back(bullet);
			
			bullet->visible = true;
			Unit* unit = units[0];
			bullet->frame_row = 0;
			bullet->frame_column = BULLET_LAST_FRAME * bullet->direction;

			bullet->frame_sequence = FRAMESBULLET;
			bullet->frame_count = FRAMESBULLET_COUNT;
			bullet->frame_id = 0;


			
			bullet->y = unit->y-50;
			//bullet->direction = unit->direction;
			if (unit->direction == UNIT_DIRECT_LEFT) {
				bullet->x = unit->x-100;
				bullet->vx =- 10;
			}
			if (unit->direction == UNIT_DIRECT_RIGHT) {
				bullet->x = unit->x+20;
				bullet->vx = 10;
			}
			bullet->x = bullet->x + bullet->vx;

			bullet->frame_id++;
			bullet->frame_id = bullet->frame_id % bullet->frame_count;

			int column = bullet->frame_sequence[bullet->frame_id];
			bullet->frame_column = column;

			


		}
		if (unit->state == UNIT_STATE_JUMP) {
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->ay = UNIT_a;
	
			if (flag == true) {
				unit->vy = -20;
				flag = false;
			}
			unit->vy = unit->vy + 1.0;
		}
	}
	for (int i = 0; i < bullets.size(); i++) {
		Bullet* bullet = bullets[i];
		if (abs(bullet->x - unit->x) >= 200) {
		bullet->visible=false;
		}
	}

	//动画运行到下一帧
	unit->x += unit->vx;
	unit->y += unit->vy;

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);

	if (unit->x >= 1150 ) {
		unit->x = 1150;
	}
	if (unit->x <= 35) {
		unit->x = 35;
	}
	if (unit->y <= 70) {
		unit->y = 70;
	}
	if (unit->y >= 620) {
		defeat = true;
	}
	
}

//敌人行为函数
void EnemyBehaviour_1(Enemy* enemy)
{
	if (enemy->x1 < 100) {
		left0 = false;
	}
	if (enemy->x1 == 1150) {
		left0 = true;
	}
	if (enemy-> state== ENEMY_WALK) {
		enemy->frame1_sequence = FRAMES1_WALK;
		enemy->frame1_count = FRAMES1_WALK_COUNT;
		if (left0 == true) {
			enemy->vx1 = (-1) * ENEMY_SPEED;
			enemy->vy1 = 0;
			enemy->direction = UNIT_DIRECT_LEFT;
		
		}
		if(left0 ==false) {
			enemy->vx1 = ENEMY_SPEED;
			enemy->vy1 = 0;
			enemy->direction = UNIT_DIRECT_RIGHT;

		}

	}
	
	//动画运行到下一帧
	enemy->x1 += enemy->vx1;
	enemy->y1 += enemy->vy1;

	enemy->frame1_id++;
	enemy->frame1_id = enemy->frame1_id % enemy->frame1_count;

	int column = enemy->frame1_sequence[enemy->frame1_id];
	enemy->frame1_column = column + enemy->direction * (MUSHROOM_LAST_FRAME - 2 * column);

	Unit* unit = units[0];
	if (collisionbullet(enemy)==1) {
		enemy->health1--;
		enemy->x1 = enemy->x1 - 10;
	}
	if (collisionbullet(enemy) == 2) {
		enemy->health1--;
		enemy->x1 = enemy->x1 + 10;
	}
	if (enemy->health1 == 0) {
		enemy->visible = false;
	}
}

void EnemyBehaviour_2(Enemy* enemy) {
	Unit* unit = units[0];
	double dirX = unit->x - enemy->x1;
	double dirY = unit->y - enemy->y1;
	double dirLen = sqrt(dirX * dirX + dirY * dirY) + 0.1;

	if (dirX > 150) {
		enemy->direction = UNIT_DIRECT_RIGHT;
	}
	if(dirX<-80){
		enemy->direction = UNIT_DIRECT_LEFT;
	}

	if (dirLen <= 1000) {
		enemy->vx1 = dirX/dirLen*3;
		enemy->vy1 = dirY/dirLen*3;

	}
	if(dirLen<=150) {
		enemy->vx1 = 0;
		enemy->vy1 = 0;
	}
	enemy->x1 += enemy->vx1;
	enemy->y1 += enemy->vy1;

	enemy->frame1_id++;
	enemy->frame1_id = enemy->frame1_id % enemy->frame1_count;

	int column = enemy->frame1_sequence[enemy->frame1_id];
	enemy->frame1_column = column + enemy->direction * (MUSHROOM_LAST_FRAME - 2 * column);


	if (enemy->x1 >= 1150) {
		enemy->x1= 1150;
	}
	if (enemy->x1<= 35) {
		enemy->x1= 35;
	}
	if (enemy->y1<= 70) {
		enemy->y1= 70;
	}
	if (enemy->y1>= 500) {
		enemy->y1= 500;
	}
	if (collisionbullet(enemy) == 1) {
		enemy->health1--;
		enemy->x1 = enemy->x1 - 10;
	}
	if (collisionbullet(enemy) == 2) {
		enemy->health1--;
		enemy->x1 = enemy->x1 + 10;
	}
	if (enemy->health1 == 0) {
		enemy->visible = false;
	}
}

void EnemyBehaviour_3(Enemy* enemy)
{
	//enemy->state = ENEMY_WALK;
	//bool left = true;
	if (enemy->x1 < 140) {
		left1 = false;
	}
	if (enemy->x1 >= 400) {
		left1 = true;
	}
	if (enemy->state == ENEMY_WALK) {
		enemy->frame1_sequence = FRAMES1_WALK;
		enemy->frame1_count = FRAMES1_WALK_COUNT;
		if (left1 == true) {
			enemy->vx1 = (-1) * ENEMY_SPEED;
			enemy->vy1 = 0;
			enemy->direction = UNIT_DIRECT_LEFT;

		}
		if (left1 == false) {
			enemy->vx1 = ENEMY_SPEED;
			enemy->vy1 = 0;
			enemy->direction = UNIT_DIRECT_RIGHT;

		}

	}


	//动画运行到下一帧
	enemy->x1 += enemy->vx1;
	enemy->y1 += enemy->vy1;

	enemy->frame1_id++;
	enemy->frame1_id = enemy->frame1_id % enemy->frame1_count;

	int column = enemy->frame1_sequence[enemy->frame1_id];
	enemy->frame1_column = column + enemy->direction * (MUSHROOM_LAST_FRAME - 2 * column);

	if (collisionbullet(enemy) == 1) {
		enemy->health1--;
		enemy->x1 = enemy->x1 - 10;
	}
	if (collisionbullet(enemy) == 2) {
		enemy->health1--;
		enemy->x1 = enemy->x1 + 10;
	}
	if (enemy->health1 == 0) {
		enemy->visible = false;
	}
}

void EnemyBehaviour_4(Enemy* enemy)
{
	
	if (enemy->x1 < 870) {
		left3 = false;
	}
	if (enemy->x1 >= 1100) {
		left3 = true;
	}
	if (enemy->state == ENEMY_WALK) {
		enemy->frame1_sequence = FRAMES1_WALK;
		enemy->frame1_count = FRAMES1_WALK_COUNT;
		if (left3 == true) {
			enemy->vx1 = (-1) * ENEMY_SPEED;
			enemy->vy1 = 0;
			enemy->direction = UNIT_DIRECT_LEFT;

		}
		if (left3 == false) {
			enemy->vx1 = ENEMY_SPEED;
			enemy->vy1 = 0;
			enemy->direction = UNIT_DIRECT_RIGHT;

		}

	}


	//动画运行到下一帧
	enemy->x1 += enemy->vx1;
	enemy->y1 += enemy->vy1;

	enemy->frame1_id++;
	enemy->frame1_id = enemy->frame1_id % enemy->frame1_count;

	int column = enemy->frame1_sequence[enemy->frame1_id];
	enemy->frame1_column = column + enemy->direction * (MUSHROOM_LAST_FRAME - 2 * column);

	if (collisionbullet(enemy) == 1) {
		enemy->health1--;
		enemy->x1 = enemy->x1 - 10;
	}
	if (collisionbullet(enemy) == 2) {
		enemy->health1--;
		enemy->x1 = enemy->x1 + 10;
	}
	if (enemy->health1 == 0) {
		enemy->visible = false;
	}
}

void EnemyBehaviour_5(Enemy* enemy)
{
	
	if (enemy->x1 < 200) {
		left4 = false;
	}
	if (enemy->x1 >= 1100) {
		left4 = true;
	}
	if (enemy->state == ENEMY_WALK) {
		enemy->frame1_sequence = FRAMES1_WALK;
		enemy->frame1_count = FRAMES1_WALK_COUNT;
		if (left4 == true) {
			enemy->vx1 = (-1) * ENEMY_SPEED;
			enemy->vy1 = 0;
			enemy->direction = UNIT_DIRECT_LEFT;

		}
		if (left4 == false) {
			enemy->vx1 = ENEMY_SPEED;
			enemy->vy1 = 0;
			enemy->direction = UNIT_DIRECT_RIGHT;

		}

	}


	//动画运行到下一帧
	enemy->x1 += enemy->vx1;
	enemy->y1 += enemy->vy1;

	enemy->frame1_id++;
	enemy->frame1_id = enemy->frame1_id % enemy->frame1_count;

	int column = enemy->frame1_sequence[enemy->frame1_id];
	enemy->frame1_column = column + enemy->direction * (MUSHROOM_LAST_FRAME - 2 * column);

	if (collisionbullet(enemy) == 1) {
		enemy->health1--;
		enemy->x1 = enemy->x1 - 10;
	}
	if (collisionbullet(enemy) == 2) {
		enemy->health1--;
		enemy->x1 = enemy->x1 + 10;
	}
	if (enemy->health1 == 0) {
		enemy->visible = false;
	}
}

void EnemyBehaviour_6(Enemy* enemy)
{
	//enemy->state = ENEMY_WALK;
	//bool left = true;
	if (enemy->x1 < 100) {
		left5 = false;
	}
	if (enemy->x1 >= 380) {
		left5 = true;
	}
	if (enemy->state == ENEMY_WALK) {
		enemy->frame1_sequence = FRAMES_WALK;
		enemy->frame1_count = FRAMES_WALK_COUNT;
		if (left5 == true) {
			enemy->vx1 = (-1) * ENEMY_SPEED;
			enemy->vy1 = 0;
			enemy->direction = UNIT_DIRECT_LEFT;

		}
		if (left5 == false) {
			enemy->vx1 = ENEMY_SPEED;
			enemy->vy1 = 0;
			enemy->direction = UNIT_DIRECT_RIGHT;

		}

	}


	//动画运行到下一帧
	enemy->x1 += enemy->vx1;
	enemy->y1 += enemy->vy1;

	enemy->frame1_id++;
	enemy->frame1_id = enemy->frame1_id % enemy->frame1_count;

	int column = enemy->frame1_sequence[enemy->frame1_id];
	enemy->frame1_column = column + enemy->direction * (GIRL_LAST_FRAME - 2 * column);

	if (collisionbullet(enemy) == 1) {
		enemy->health1--;
		enemy->x1 = enemy->x1-10;
	}
	if (collisionbullet(enemy) == 2) {
		enemy->health1--;
		enemy->x1 = enemy->x1-10;
	}
	if (collisionbullet(enemy) == 3) {
		enemy->health1--;
		enemy->x1 = enemy->x1 - 10;
	}
	if (enemy->health1 == 0) {
		enemy->visible = false;
	}
}

//地砖行为函数
void GroundBehaviour_1(Ground* ground) {//stop
	if (ground->state == UNIT_STATE_HOLD) {
		ground->frame_sequence = FRAMES_HOLD;
		ground->frame_count = FRAMES_HOLD_COUNT;	
	}

	ground->frame_id++;
	ground->frame_id = ground->frame_id % ground->frame_count;

	int column = ground->frame_sequence[ground->frame_id];
	ground->frame_column = column + (0 - 2 * column);
}

void GroundBehaviour_2(Ground* ground) {
	if (ground->x < 100) {
		left2 = false;
	}
	else if (ground->x > 600) {
		left2 = true;
	}

	ground->frame_sequence = FRAMES_HOLD;
	ground->frame_count = FRAMES_HOLD_COUNT;
	if (left2 == true) {
		ground->vx = -2;
		ground->vy = 0;
		ground->direction = UNIT_DIRECT_LEFT;
	}
	else {
		ground->vx = 2;
		ground->vy = 0;
		ground->direction = UNIT_DIRECT_RIGHT;
	}
	ground->x += ground->vx;
	//ground->y += ground->vy;

	ground->frame_id++;
	ground->frame_id = ground->frame_id % ground->frame_count;

	int column = ground->frame_sequence[ground->frame_id];
	ground->frame_column = column + ground->direction * (0 - 2 * column);

}

void GroundBehaviour_3(Ground* ground) {
	if (ground->y < 150) {
		up = false;
	}
	else if (ground->y > 600) {
		up = true;
	}

	ground->frame_sequence = FRAMES_HOLD;
	ground->frame_count = FRAMES_HOLD_COUNT;
	if (up == true) {
		ground->vy = -2;
		ground->vx = 0;
		
	}
	else {
		ground->vy = 2;
		ground->vx = 0;
		
	}
	
	ground->y += ground->vy;

	ground->frame_id++;
	ground->frame_id = ground->frame_id % ground->frame_count;

	int column = ground->frame_sequence[ground->frame_id];
	ground->frame_column = column + ground->direction * (0 - 2 * column);

}

#pragma endregion


#pragma region 绘图函数
// 绘图函数
void Paint(HWND hWnd)
{

	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, blankBmp);

	

	// 按场景分类绘制内容到缓存
	if (currentStage->stageID == STAGE_STARTMENU) {
		// 绘制背景到缓存
		SelectObject(hdc_loadBmp, currentStage->bg);
		SelectObject(hdc_loadBmp, bmp_opening);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
	}

	else if (currentStage->stageID == STAGE_1) //TODO：添加多个游戏场景
	{
		// 绘制背景到缓存
		SelectObject(hdc_loadBmp, currentStage->bg);
		SelectObject(hdc_loadBmp, bmp_stage1);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
		
		// 绘制单位到缓存
		for (int i = 0; i < units.size(); i++) {
			Unit* unit = units[i];
			SelectObject(hdc_loadBmp, unit->img);
			TransparentBlt(
				hdc_memBuffer, unit->x - 0.5 * UNIT_SIZE_X, unit->y - 0.5 * UNIT_SIZE_Y,
				UNIT_SIZE_X, UNIT_SIZE_Y,
				hdc_loadBmp, UNIT_SIZE_X * unit->frame_column, UNIT_SIZE_Y * unit->frame_row, UNIT_SIZE_X, UNIT_SIZE_Y,
				RGB(255, 255, 255)
			);
		}

		//绘制敌人到缓存
		for (int i = 0; i < enemys.size(); i++) {
			Enemy* enemy = enemys[i];
			if (enemy->visible == true) {
				SelectObject(hdc_loadBmp, enemy->img);
				TransparentBlt(
					hdc_memBuffer, enemy->x1, enemy->y1,
					MUSHROOM_SIZE_X, MUSHROOM_SIZE_Y,
					hdc_loadBmp, MUSHROOM_SIZE_X * enemy->frame1_column, MUSHROOM_SIZE_Y * enemy->frame1_row, MUSHROOM_SIZE_X, MUSHROOM_SIZE_Y,
					RGB(255, 255, 255)
				);
			}
		}

		//绘制地砖到缓存
		for (int i = 0; i < grounds.size(); i++)
		{
			Ground* ground = grounds[i];
			if (ground->visible)
			{
				SelectObject(hdc_loadBmp, ground->img);
				TransparentBlt(
					hdc_memBuffer, ground->x, ground->y,
					ground->width, ground->height,
					hdc_loadBmp, 0, 0, ground->width, ground->height,
					RGB(255, 255, 255)
				);
			}
		}

	}
	
	else if (currentStage->stageID == STAGE_CHOSE) {
		
			// 绘制背景到缓存
			SelectObject(hdc_loadBmp, currentStage->bg);
			SelectObject(hdc_loadBmp, bmp_chose);

			BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
		
	}

	else if (currentStage->stageID == STAGE_HELP) {

		// 绘制背景到缓存
		SelectObject(hdc_loadBmp, currentStage->bg);
		SelectObject(hdc_loadBmp, bmp_helpstage);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

	}

	else if (currentStage->stageID == STAGE_2) {

		// 绘制背景到缓存
		SelectObject(hdc_loadBmp, currentStage->bg);
		SelectObject(hdc_loadBmp, bmp_summer);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

		//绘制单位到缓存
		for (int i = 0; i < units.size(); i++) {
			Unit* unit = units[i];
			SelectObject(hdc_loadBmp, unit->img);
			TransparentBlt(
				hdc_memBuffer, unit->x - 0.5 * UNIT_SIZE_X, unit->y - 0.5 * UNIT_SIZE_Y,
				UNIT_SIZE_X, UNIT_SIZE_Y,
				hdc_loadBmp, UNIT_SIZE_X * unit->frame_column, UNIT_SIZE_Y * unit->frame_row, UNIT_SIZE_X, UNIT_SIZE_Y,
				RGB(255, 255, 255)
			);
		}

		//绘制敌人到缓存
		for (int i = 0; i < enemys.size(); i++) {
			Enemy* enemy = enemys[i];
			if (enemy->visible == true) {
				SelectObject(hdc_loadBmp, enemy->img);
				TransparentBlt(
					hdc_memBuffer, enemy->x1, enemy->y1,
					GHOST_SIZE_X, GHOST_SIZE_Y,
					hdc_loadBmp, GHOST_SIZE_X * enemy->frame1_column, GHOST_SIZE_Y * enemy->frame1_row, GHOST_SIZE_X, GHOST_SIZE_Y,
					RGB(255, 255, 255)
				);
			}
		}

		//绘制地砖到缓存
		for (int i = 0; i < grounds.size(); i++)
		{
			Ground* ground = grounds[i];
			if (ground->visible)
			{
				SelectObject(hdc_loadBmp, ground->img);
				TransparentBlt(
					hdc_memBuffer, ground->x, ground->y,
					ground->width, ground->height,
					hdc_loadBmp, 0, 0, ground->width, ground->height,
					RGB(255, 255, 255)
				);
			}
		}
	}

	else if (currentStage->stageID == STAGE_3) {

		// 绘制背景到缓存
		SelectObject(hdc_loadBmp, currentStage->bg);
		SelectObject(hdc_loadBmp, bmp_autumn);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

		for (int i = 0; i < units.size(); i++) {
			Unit* unit = units[i];
			SelectObject(hdc_loadBmp, unit->img);
			TransparentBlt(
				hdc_memBuffer, unit->x - 0.5 * UNIT_SIZE_X, unit->y - 0.5 * UNIT_SIZE_Y,
				UNIT_SIZE_X, UNIT_SIZE_Y,
				hdc_loadBmp, UNIT_SIZE_X * unit->frame_column, UNIT_SIZE_Y * unit->frame_row, UNIT_SIZE_X, UNIT_SIZE_Y,
				RGB(255, 255, 255)
			);
		}

		//绘制地砖到缓存
		for (int i = 0; i < grounds.size(); i++)
		{
			Ground* ground = grounds[i];
			if (ground->visible)
			{
				SelectObject(hdc_loadBmp, ground->img);
				TransparentBlt(
					hdc_memBuffer, ground->x, ground->y,
					ground->width, ground->height,
					hdc_loadBmp, 0, 0, ground->width, ground->height,
					RGB(255, 255, 255)
				);
			}
		}
		//绘制敌人到缓存
		for (int i = 0; i < enemys.size(); i++) {
			Enemy* enemy = enemys[i];
			if (enemy->visible == true) {
				SelectObject(hdc_loadBmp, enemy->img);
				TransparentBlt(
					hdc_memBuffer, enemy->x1, enemy->y1,
					DUCK_SIZE_X, DUCK_SIZE_Y,
					hdc_loadBmp, DUCK_SIZE_X * enemy->frame1_column, DUCK_SIZE_Y * enemy->frame1_row, DUCK_SIZE_X, DUCK_SIZE_Y,
					RGB(255, 255, 255)
				);
			}
		}
	}

	else if (currentStage->stageID == STAGE_4) {

		// 绘制背景到缓存
		SelectObject(hdc_loadBmp, currentStage->bg);
		SelectObject(hdc_loadBmp, bmp_winter);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

		for (int i = 0; i < units.size(); i++) {
			Unit* unit = units[i];
			SelectObject(hdc_loadBmp, unit->img);
			TransparentBlt(
				hdc_memBuffer, unit->x - 0.5 * UNIT_SIZE_X, unit->y - 0.5 * UNIT_SIZE_Y,
				UNIT_SIZE_X, UNIT_SIZE_Y,
				hdc_loadBmp, UNIT_SIZE_X * unit->frame_column, UNIT_SIZE_Y * unit->frame_row, UNIT_SIZE_X, UNIT_SIZE_Y,
				RGB(255, 255, 255)
			);
		}
		//绘制敌人到缓存
		for (int i = 0; i < enemys.size(); i++) {
			Enemy* enemy = enemys[i];
			if (enemy->visible == true) {
				SelectObject(hdc_loadBmp, enemy->img);
				TransparentBlt(
					hdc_memBuffer, enemy->x1, enemy->y1,
					GIRL_SIZE_X, GIRL_SIZE_Y,
					hdc_loadBmp, GIRL_SIZE_X * enemy->frame1_column, GIRL_SIZE_Y * enemy->frame1_row, GIRL_SIZE_X, GIRL_SIZE_Y,
					RGB(255, 255, 255)
				);
			}
		}

		//绘制地砖到缓存
		for (int i = 0; i < grounds.size(); i++)
		{
			Ground* ground = grounds[i];
			if (ground->visible)
			{
				SelectObject(hdc_loadBmp, ground->img);
				TransparentBlt(
					hdc_memBuffer, ground->x, ground->y,
					ground->width, ground->height,
					hdc_loadBmp, 0, 0, ground->width, ground->height,
					RGB(255, 255, 255)
				);
			}
		}
	}

	else if (currentStage->stageID == STAGE_STOP) {

		// 绘制背景到缓存
		SelectObject(hdc_loadBmp, currentStage->bg);
		SelectObject(hdc_loadBmp, bmp_stop);

		BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);

	}

	else if (currentStage->stageID == STAGE_DEFEAT) {
	SelectObject(hdc_loadBmp, currentStage->bg);
	SelectObject(hdc_loadBmp, bmp_defeat);

	BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
}
	else if (currentStage->stageID == STAGE_VICTORY) {
	SelectObject(hdc_loadBmp, currentStage->bg);
	SelectObject(hdc_loadBmp, bmp_victory);

	BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
}


	// 绘制按钮到缓存
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			SelectObject(hdc_loadBmp, button->img);
			TransparentBlt(
				hdc_memBuffer, button->x, button->y,
				button->width, button->height,
				hdc_loadBmp, 0, 0, button->width, button->height,
				RGB(255, 255, 255)
			);
		}
	}
	
	//绘制子弹到缓存
	for (int i = 0; i < bullets.size(); i++)
	{
		Bullet* bullet = bullets[i];
		if (bullet->visible)
		{
			SelectObject(hdc_loadBmp, bullet->img);
			TransparentBlt(
				hdc_memBuffer, bullet->x, bullet->y,
				bullet->width, bullet->height,
				hdc_loadBmp, 0, 0, bullet->width, bullet->height,
				RGB(255, 255, 255)
			);
		}
	}
	//绘制道具到缓存
	for (int i = 0; i < props.size(); i++)
	{
		Prop* prop = props[i];
		if (prop->visible)
		{
			SelectObject(hdc_loadBmp, prop->img);
			TransparentBlt(
				hdc_memBuffer, prop->x, prop->y,
				prop->width, prop->height,
				hdc_loadBmp, 0, 0, prop->width, prop->height,
				RGB(255, 255, 255)
			);
		}
	}


	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);
}



// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src) {

	srand(time(NULL));
	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	bmp_output = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, bmp_output);

	//加载资源
	SelectObject(hdc_loadBmp, bmp_src);


	for (int i = 0; i < BG_ROWS; i++) {

		int src_row = 1;
		if (i >= BG_ROWS_SKY)
			src_row = 0;

		for (int j = 0; j < BG_COLUMNS; j++) {
			int src_column = rand() % BG_SRC_COUNT;

			TransparentBlt(
				hdc_memBuffer, j*BG_CELL_WIDTH, i*BG_CELL_HEIGHT,
				BG_CELL_WIDTH, BG_CELL_HEIGHT,
				hdc_loadBmp, src_column * BG_CELL_WIDTH, src_row * BG_CELL_HEIGHT,
				BG_CELL_WIDTH, BG_CELL_HEIGHT,
				RGB(255, 255, 255)
			);

		}
	}

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);

	return bmp_output;
}

#pragma endregion