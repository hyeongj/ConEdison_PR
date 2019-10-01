// ConEdison_PR.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ConEdison_PR.h"

#define MAX_LOADSTRING 100
 

//==================================================

ofstream outdata;


//VOID Thread(PVOID pvoid);
HANDLE myhandleA;
unsigned int __stdcall mythreadA(void* data);

wchar_t gstr[MAX_LOADSTRING];
wchar_t agstr[MAX_LOADSTRING];
wchar_t bgstr[MAX_LOADSTRING];
wchar_t cgstr[MAX_LOADSTRING];
wchar_t dgstr[MAX_LOADSTRING];

plot p;
plot pp;

int offset = 0;
MSG msg;


char sel = 'a';

static BOOL STOP = FALSE;
static BOOL saving = FALSE;
static BOOL saving2 = FALSE;
static BOOL showgraph = FALSE;

WPARAM wParam;


//initialized parameters
Usbut usbut;
double** ary;
double** auto_ary;
double* tm;
double* tof;

void AddMenus(HWND hWnd);
void AddControls(HWND hWnd);
DWORD signalsaving();

HWND hWnd, hEdit0, hEdit, hEdit1, hEdit2, hEdit3, hEdit4, hEdit5, hEdit6;
HWND sEdit3, sEdit4, sEdit5, sEdit6;

//==================================================

 

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CONEDISONPR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CONEDISONPR));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CONEDISONPR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CONEDISONPR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, L"GUI", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 500, 300, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	

	myhandleA = (HANDLE)_beginthreadex(0, 0, &mythreadA, 0, 0, 0);

	//_beginthreadex(0,0,Thread, 0, 0,0);

	//===========================================
	return TRUE;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_CREATE:
	{
		AddMenus(hWnd);
		AddControls(hWnd);

	}
	break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{

		case IDB_BUTTON1:
		{
			//run
			STOP = FALSE;
			showgraph = FALSE;
			//saving = FALSE;
			//drawgraph(hWnd);
			//_beginthread(Thread, 0, NULL);
			//Thread();
			//usbutfunc();
			//MessageBox(hWnd, L"Hello 1!", L"Warning", MB_OK);
			break;
		}

		case IDB_BUTTON2:
		{
			//Pause 
		   //STOP = TRUE;
			showgraph = FALSE;
			saving = FALSE;

			break;
		}

		case IDB_BUTTONa1:
		{
			//saving data
			saving = TRUE;


			//drawgraph(hWnd);

			break;
		}

		case IDB_BUTTONa2:
		{
			//show graph
			showgraph = TRUE;


			//drawgraph(hWnd);

			break;
		}

		case IDB_BUTTONa3:
		{
			//show graph
			//showgraph = FALSE;
			//_beginthread(realplot, 0, NULL);

			//drawgraph(hWnd);

			break;
		}




		case IDB_BUTTON3:
		{



			wchar_t text[100];
			GetWindowTextW(hEdit, text, 100);
			/*SetWindowTextW(hWnd, text);*/

			double myint1 = stod(text);
			double getn = myint1;

			usbut._time_in = getn;



			break;
		}
		case IDB_BUTTON4:
		{
			//stop

			STOP = TRUE;
			saving = FALSE;
			showgraph = FALSE;

			if (MessageBox(hWnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
			{

				DestroyWindow(hWnd);
			}
			//DestroyWindow(hWnd);
			break;
		}


		case IDB_BUTTON5:
		{


			wchar_t text2[100];

			/*SetWindowTextW(hWnd, text);*/

			GetWindowTextW(hEdit1, text2, 100);
			/*SetWindowTextW(hWnd, text);*/

			double myint1 = stod(text2);
			double getn = myint1;
			 

			usbut._maxth = getn;



			break;

		}
		case IDB_BUTTON6:
		{
			wchar_t text3[100];
			GetWindowTextW(hEdit2, text3, 100);
			/*SetWindowTextW(hWnd, text);*/

			int myint1 = stoi(text3);
			int getn = myint1;

			usbut._gain = getn;


			break;

		}

		case IDB_BUTTON7:
		{
			wchar_t text4[100];
			GetWindowTextW(hEdit0, text4, 100);
			/*SetWindowTextW(hWnd, text);*/

			int myint1 = stoi(text4);
			int getn = myint1;

			usbut._speed = getn;


			break;

		}
		 

		case IDB_BUTTON8:
		{
			
			saving2 = TRUE;
			break;

		}


		case IDB_RADIO1:
		{
			sel = 'a';
			//MessageBoxW(NULL, L"radio1 is checked", L"radio", MB_OK | MB_ICONERROR);
			
		}
		break;

		case IDB_RADIO2:
		{
			sel = 'b';
		//	MessageBoxW(NULL, L"radio2 is checked", L"radio", MB_OK | MB_ICONERROR);
		}
		break;


		case IDC_COMBOBOX_TEXT:
		{
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
					(WPARAM)0, (LPARAM)0);
				if (ItemIndex == 0) {

					usbut.setrate(0);

				}
				else if (ItemIndex == 1) {

					usbut.setrate(1);
				}
				else if (ItemIndex == 2) {
					usbut.setrate(2);
				}
			}
		}
		break;

		case IDC_COMBOBOX_TEXT2:
		{
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
					(WPARAM)0, (LPARAM)0);
				if (ItemIndex == 0) {

					//MessageBox(hWnd, L"500", L"Warning", MB_OK);
					usbut.setbuffer(500);

				}
				else if (ItemIndex == 1) {

					usbut.setbuffer(1000);
				}
				else if (ItemIndex == 2) {
					usbut.setbuffer(2000);
				}
			}
		}
		break;

		case IDC_COMBOBOX_TEXT3:
		{
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
					(WPARAM)0, (LPARAM)0);
				if (ItemIndex == 0) {

					usbut.setrectifier(0);



				}
				else if (ItemIndex == 1) {

					usbut.setrectifier(1);
				}
				else if (ItemIndex == 2) {
					usbut.setrectifier(2);
				}
				else if (ItemIndex == 3) {
					usbut.setrectifier(3);
				}
			}
		}
		break;




		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			STOP = TRUE;
			saving = FALSE;
			WaitForSingleObject(myhandleA, INFINITE);
			CloseHandle(myhandleA);

			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;


	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HFONT hFont, hTmp;

		//========================




		//MoveToEx(hdc, 0, 85, NULL);
		//LineTo(hdc, 500, 85);

		TCHAR greeting[] = _T("Measured height (mm)");
		hFont = CreateFont(15, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 2, 0, L"SYSTEM_FIXED_FONT");
		hTmp = (HFONT)SelectObject(hdc, hFont);
		SetTextColor(hdc, RGB(0, 0, 0));
		//SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc,
			320, 75,
			greeting, _tcslen(greeting));


		EndPaint(hWnd, &ps);


	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		/*if (MessageBox(hWnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
		{

			DestroyWindow(hWnd);
		}*/
		// Else: User canceled. Do nothing.
		DestroyWindow(hWnd);

		return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


void AddMenus(HWND hWnd)
{


	HWND hButton = CreateWindowEx(
		0,
		L"button", L"Run",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		20, 20 + offset,
		50, 20,
		hWnd,
		(HMENU)IDB_BUTTON1,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);

	HWND hButton1 = CreateWindowEx(
		0,
		L"button", L"SAVE",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		20 + 60, 20 + offset,
		50, 20,
		hWnd,
		(HMENU)IDB_BUTTONa1,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);


	HWND hButton2 = CreateWindowEx(
		0,
		L"button", L"Pause",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		20 + 60 * 3, 20 + offset,
		50, 20,
		hWnd,
		(HMENU)IDB_BUTTON2,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);

	HWND hButton3 = CreateWindowEx(
		0,
		L"button", L"Plot",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		20 + 60 * 2, 20 + offset,
		50, 20,
		hWnd,
		(HMENU)IDB_BUTTONa2,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);
	//HWND hButton3a = CreateWindowEx(
	//	0,
	//	L"button", L"R_Plot",
	//	WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
	//	20 + 60 * 4+20, 20 + offset,
	//	80, 20,
	//	hWnd,
	//	(HMENU)IDB_BUTTONa3,
	//	(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
	//	NULL);
	HWND rButton1 = CreateWindowEx(
		0,
		L"button", L"default",
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		20 + 60 * 4, 20 + offset,
		80, 20,
		hWnd,
		(HMENU)IDB_RADIO1,
		GetModuleHandle(NULL),
		NULL);
		SendMessage(rButton1, BM_SETCHECK, BST_CHECKED, 0);

	HWND rButton2 = CreateWindowEx(
		0,
		L"button", L"auto_corr",
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		20 + 60 * 5+10, 20 + offset,
		80, 20,
		hWnd,
		(HMENU)IDB_RADIO2,
		GetModuleHandle(NULL),
		NULL);
		//SendMessage(rButton2, BM_SETCHECK, BST_CHECKED, 0);

	HWND hButton4 = CreateWindowEx(
		0,
		L"button", L"QUIT",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		20 + 60 * 6+40, 20 + offset,
		50, 20,
		hWnd,
		(HMENU)IDB_BUTTON4,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);




	HWND wButton1 = CreateWindowEx(
		0,
		L"button", L"Time_in",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		100, 100 + offset,
		80, 20,
		hWnd,
		(HMENU)IDB_BUTTON3,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);


	HWND wButton2 = CreateWindowEx(
		0,
		L"button", L"Max",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		100, 100 + 30 + offset,
		80, 20,
		hWnd,
		(HMENU)IDB_BUTTON5,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);

	HWND wButton3 = CreateWindowEx(
		0,
		L"button", L"Gain",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		100, 100 + 30 * 2 + offset,
		80, 20,
		hWnd,
		(HMENU)IDB_BUTTON6,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);
	HWND wButton4 = CreateWindowEx(
		0,
		L"button", L"Speed",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		100, 100 + 30 * 3 + offset,
		80, 20,
		hWnd,
		(HMENU)IDB_BUTTON7,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);



	HWND sButton1 = CreateWindowEx(
		0,
		L"button", L"WaveForm",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		20, 100 + 30 * 4 + offset,
		80, 20,
		hWnd,
		(HMENU)IDB_BUTTON8,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);



	HWND hWndComboBox = CreateWindowEx(
		WS_EX_CLIENTEDGE, // extended window styles
		L"COMBOBOX",
		NULL,
		WS_VISIBLE | WS_CHILD | CBS_DROPDOWN,
		20,
		50 + offset,
		100,
		800,
		hWnd,
		(HMENU)IDC_COMBOBOX_TEXT,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);

	if (!hWndComboBox)
		MessageBox(NULL, L"ComboBox Failed.", L"Error", MB_OK | MB_ICONERROR);

	SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Fs 50 MHz");
	SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Fs 25 MHz");
	SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)L"Fs 12.5 MHz");

	SendMessage(hWndComboBox, CB_SETCURSEL, 0, 0); //highlight/select the first option

	HWND hWndComboBox2 = CreateWindowEx(
		WS_EX_CLIENTEDGE, // extended window styles
		L"COMBOBOX",
		NULL,
		WS_VISIBLE | WS_CHILD | CBS_DROPDOWN,
		20 + 100,
		50 + offset,
		100,
		800,
		hWnd,
		(HMENU)IDC_COMBOBOX_TEXT2,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);

	if (!hWndComboBox)
		MessageBox(NULL, L"ComboBox Failed.", L"Error", MB_OK | MB_ICONERROR);

	SendMessage(hWndComboBox2, CB_ADDSTRING, 0, (LPARAM)L"Buffer 500");
	SendMessage(hWndComboBox2, CB_ADDSTRING, 0, (LPARAM)L"Buffer 1000");
	SendMessage(hWndComboBox2, CB_ADDSTRING, 0, (LPARAM)L"Buffer 2000");

	SendMessage(hWndComboBox2, CB_SETCURSEL, 0, 0); //highlight/select the first option

	HWND hWndComboBox3 = CreateWindowEx(
		WS_EX_CLIENTEDGE, // extended window styles
		L"COMBOBOX",
		NULL,
		WS_VISIBLE | WS_CHILD | CBS_DROPDOWN,
		20 + 100 * 2,
		50 + offset,
		100,
		800,
		hWnd,
		(HMENU)IDC_COMBOBOX_TEXT3,
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);

	if (!hWndComboBox)
		MessageBox(NULL, L"ComboBox Failed.", L"Error", MB_OK | MB_ICONERROR);

	// RF wave rectify, 0 to 3 where 0=Full rectified, 1=+half, 2=-half, or 3=RF
	SendMessage(hWndComboBox3, CB_ADDSTRING, 0, (LPARAM)L"Full Rectified");
	SendMessage(hWndComboBox3, CB_ADDSTRING, 0, (LPARAM)L"+Half");
	SendMessage(hWndComboBox3, CB_ADDSTRING, 0, (LPARAM)L"-Half");
	SendMessage(hWndComboBox3, CB_ADDSTRING, 0, (LPARAM)L"RF");

	SendMessage(hWndComboBox3, CB_SETCURSEL, 0, 0); //highlight/select the first option



}

void AddControls(HWND hWnd)
{
	//time, gain, buffer
	//CreateWindowW(L"static", L"Enter text: ", WS_VISIBLE | WS_CHILD |WS_BORDER | SS_CENTER, 200, 100, 100, 20, hWnd, NULL, NULL, NULL);
	hEdit = CreateWindowW(L"Edit", L"3", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_MULTILINE | ES_AUTOVSCROLL, 20, 100 + offset, 60, 20, hWnd, NULL, NULL, NULL);
	hEdit1 = CreateWindowW(L"Edit", L"0.5", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_MULTILINE | ES_AUTOVSCROLL, 20, 100 + 30 + offset, 60, 20, hWnd, NULL, NULL, NULL);
	hEdit2 = CreateWindowW(L"Edit", L"700", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_MULTILINE | ES_AUTOVSCROLL, 20, 100 + 30 * 2 + offset, 60, 20, hWnd, NULL, NULL, NULL);
	hEdit0 = CreateWindowW(L"Edit", L"1500", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_MULTILINE | ES_AUTOVSCROLL, 20, 100 + 30 * 3 + offset, 60, 20, hWnd, NULL, NULL, NULL);


	hEdit3 = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_MULTILINE | ES_AUTOVSCROLL, 400, 100 + 30 * 0 + offset, 60, 20, hWnd, NULL, NULL, NULL);
	hEdit4 = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_MULTILINE | ES_AUTOVSCROLL, 400, 100 + 30 * 1 + offset, 60, 20, hWnd, NULL, NULL, NULL);
	hEdit5 = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_MULTILINE | ES_AUTOVSCROLL, 400, 100 + 30 * 2 + offset, 60, 20, hWnd, NULL, NULL, NULL);
	hEdit6 = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_MULTILINE | ES_AUTOVSCROLL, 400, 100 + 30 * 3 + offset, 60, 20, hWnd, NULL, NULL, NULL);

	sEdit3 = CreateWindowW(L"static", L"CH #1", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 320, 100 + 30 * 0 + offset, 60, 20, hWnd, NULL, NULL, NULL);
	sEdit4 = CreateWindowW(L"static", L"CH #2", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 320, 100 + 30 * 1 + offset, 60, 20, hWnd, NULL, NULL, NULL);
	sEdit5 = CreateWindowW(L"static", L"CH #3", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 320, 100 + 30 * 2 + offset, 60, 20, hWnd, NULL, NULL, NULL);
	sEdit6 = CreateWindowW(L"static", L"CH #4", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 320, 100 + 30 * 3 + offset, 60, 20, hWnd, NULL, NULL, NULL);


}

 

int cnt = 0;
int fcnt = 0;
int pfcnt = 0;
int wcnt = 0;

unsigned int __stdcall mythreadA(void* data)
{
	wchar_t gss[100];
	wchar_t filename[300];
	wsprintf(filename, L"datafile_%d.dat", fcnt);

	vector<double> xp, yp;

	//MessageBox(hWnd, L"Hello 1!", L"Warning", MB_OK);
	int j = 0;
	int div = 2;
	STOP = FALSE;
	
 
	outdata.open(filename);
	double amax[4] = { 0.0,0.0,0.0,0.0 };
	
	while (STOP == FALSE)
	{
		
		tm = usbut.timedata(usbut._rate, usbut._buffer);
		if (sel == 'a')
		{
			usbut.init();
			 
			ary = usbut.waveform(usbut._buffer);
			//auto_ary = usbut.autocorr(usbut._buffer, ary);
			tof = usbut.get_tof(tm, ary, usbut._time_in, usbut._maxth);
		
			if (showgraph == TRUE)
			{
					p.mplot_data(usbut._buffer, tm, ary, usbut._channel);
					for (int a = j; a < j + div; a++)
					{
						xp.push_back(a);
						yp.push_back(tof[0]);

						pp.rplot_data(xp, yp);
					}
					j = j + div;

				}
		}
		else
		{
            //run auto correlation function
			usbut.init();
			usbut.setrectifier(3);
			 
			ary = usbut.waveform(usbut._buffer);
			for (int jj = 0; jj < usbut._channel; jj++)
			{
				for (int kk = 0; kk < usbut._buffer; kk++)
				{
					ary[jj][kk] = ary[jj][kk] - 0.5;
					if (ary[jj][kk] <0.2 && ary[jj][kk] >-0.2)
								{
						ary[jj][kk] =0.0;
						 		}
				}
			}

			auto_ary = usbut.autocorr(usbut._buffer, ary);


			for (int jj = 0; jj < usbut._channel; jj++)
			{
				for (int kk = 20; kk < usbut._buffer; kk++)
				{

					//find max value from index 20, index/rate = time, 20/50e-6 = 0.4us, 0.4*us*1500/2= 0.3 mm
					if (auto_ary[jj][kk] > amax[jj])
					{
						amax[jj]= auto_ary[jj][kk];
					}
					
					
				}
			}
			for (int jj = 0; jj < usbut._channel; jj++)
			{
				for (int kk = 0; kk < usbut._buffer; kk++)
				{
					if (kk < 20 && kk >= 0)
					{
						auto_ary[jj][kk] = 0.0;
					}
					//normalized -0.5 to 0.5 then remove negative values
					auto_ary[jj][kk] = auto_ary[jj][kk] / amax[jj]/2;

					if (auto_ary[jj][kk] <0)
					{
						auto_ary[jj][kk] = 0.0;
					}
				}
			}

			for (int jj = 0; jj < usbut._channel; jj++)
			{
				for (int kk = 0; kk < usbut._buffer; kk++)
				{
					//normalized 0-1
					auto_ary[jj][kk] = auto_ary[jj][kk] / 0.5;

				}
			}

			tof = usbut.get_tof(tm, auto_ary, usbut._time_in, usbut._maxth);

			if (showgraph == TRUE)
			{
				p.mplot_data(usbut._buffer, tm, auto_ary, usbut._channel);

				for (int a = j; a < j + div; a++)
				{


					xp.push_back(a);
					yp.push_back(tof[0]);


					pp.rplot_data(xp, yp);
				}
				j = j + div;

			}

		}
	
		

	 

		//display results


		if (saving2 == TRUE)
		{

			ofstream wavedata;
			wchar_t wname[300];
			wsprintf(wname, L"awfile_%d.dat", wcnt);

			wavedata.open(wname);

			for (int i = 0; i < usbut._buffer; ++i)
			{

				wavedata << ary[0][i] << "\n";
			}


			wchar_t ggh[100];

			wsprintf(ggh, L"File Saved %d\n", wcnt);
			OutputDebugString(ggh);

			wcnt += 1;

			wavedata.close();

			saving2 = FALSE;

		}

		
		double dis[4];



		for (int i = 0; i < 4; i++)
		{
			if (saving == TRUE)
			{
				if (fcnt != pfcnt)
				{
					cnt = 0;
					pfcnt = fcnt;
				}

				outdata << cnt << " ";

				for (int i = 0; i < usbut._channel; ++i)
				{

					outdata << tof[i] << " ";
				}
				outdata << "\n";
				cnt += 1;

			}
			dis[i] = usbut._speed * tof[i] / 2000; //unit mm

		}
 
        //display values to Entry

		wchar_t tof1[100];
		wchar_t tof2[100];
		wchar_t tof3[100];
		wchar_t tof4[100];

		_stprintf_s(tof1, L"%f", dis[0]);
		_stprintf_s(tof2, L"%f", dis[1]);
		_stprintf_s(tof3, L"%f", dis[2]);
		_stprintf_s(tof4, L"%f", dis[3]);



		SetWindowTextW(hEdit3, tof1);s
		SetWindowTextW(hEdit4, tof2);
		SetWindowTextW(hEdit5, tof3);
		SetWindowTextW(hEdit6, tof4);






	}

	//MessageBox(hWnd, L"DONE", L"Warning", MB_OK);
	outdata.close();

	pfcnt = fcnt;
	fcnt += 1;

	wsprintf(gss, L"%d\n", fcnt);
	OutputDebugString(gss);

	return 0;
}



 