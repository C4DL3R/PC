
/* HEADERS */
#include "ProcMem.h"
#include "offsets.h"
#include "Decrypt.h"
/* INCLUDE */
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <thread>
using namespace std;

float slowaim = 1.f; // THE "SLOW" SENSITIVITY
 // YOUR REGULAR SENSITIVITY


/* DEFINE FLAG'S */
#define Pressed 0x8000
#define FL_ON_GROUND 257

/* DEFINE MEMORY MANAGER */
ProcMem Meme;

/* PRE-CALL FUNCTION'S */
[swap_lines]
void data();
void start();
void keys();
void ESPRadar();
void triggerslow();
void NoFlash();
void bhop();
/* ACTIVATION BOOL */
bool eON = false;
bool tON = false;
bool rON = false;
bool fON = false;
bool sON = false;
bool bON = false;
[/swap_lines]



/* START CONSOLE */
int main()
{
	[add_junk /]
	/* FIND CSGO */
	Meme.Process("csgo.exe");
	cout << "Found csgo.exe" << endl;
	Sleep(2000);
	/* ATTACH CLIENT & RENAME CONSOLE */
	cout << "Hack made by C4DL3R" << endl;
	Sleep(500);
	[add_junk /]
	Client = Meme.Module("client.dll");
	[add_junk /]
	cout << boolalpha;// MAKES EVERYTHING SAY TRUE OR FALSE INSTEAD OF 1 or 0
	oldaim = Meme.Read<float>(Client + m_flSensitivity);
	start();
	while (true)
	{
		keys();
		data();
		if (eON || rON)
			ESPRadar();
		if (tON || sON)
			triggerslow();
		if (bON)
			bhop();
		NoFlash();
		Sleep(5);
	}
	return 0;
}

/* SYSTEM START SAYING */

void start() {
	system("cls");
	cout << "F1) ESP: " << eON << endl;
	cout << "F2) Trigger: " << tON << endl;
	cout << "F3) Radar: " << rON << endl;
	cout << "F4) NoFlash: " << fON << endl;
	cout << "F6) SlowAim: " << sON << endl;
	cout << "F7) Bunnyhop: " << bON << endl;
	cout << "Insert) Trigger Delay: " << triggerdelay << endl;
	/*cout << "Home) Trigger Afterfire: " << afterfire << endl;*/ //WIP
	Sleep(10);
}
/* --------------- */
/*     HOTKEYS     */
/* --------------- */
void keys()
{
	[add_junk /]

	if (GetAsyncKeyState(VK_F1) & Pressed) /* GET IF KEY: f1 IS PRESSED */
	{
		eON = !eON;
		start();
		Sleep(100);
	}
	
	if (GetAsyncKeyState(VK_F2) & Pressed)
	{
		tON = !tON;
		start();
		Sleep(100);
	}
	
	if (GetAsyncKeyState(VK_F3) & Pressed)
	{
		rON = !rON;
		start();
		Sleep(100);
	}
	
	if (GetAsyncKeyState(VK_F4) & Pressed)
	{
		fON = !fON;
		start();
		Sleep(100);
		
	}

	if (GetAsyncKeyState(VK_INSERT) & Pressed)
	{
		cout << "Enter Trigger Delay (ms): ";
		cin >> triggerdelay;
		start();
		Sleep(100);
	}
	if (GetAsyncKeyState(VK_F7) & Pressed)
	{
		bON = !bON;
		start();
		Sleep(100);
	}

	/*if (GetAsyncKeyState(VK_HOME) & Pressed)
	{
		cout << "Enter Trigger Afterdelay (ms): ";
		cin >> afterfire;
		start();
	}*/

	if (GetAsyncKeyState(VK_F6) & Pressed)
	{
		sON = !sON;
		start();
		Sleep(100);
	}

}

/* --------------- */
/*   LOCAL DATA    */
/* --------------- */
void data()
{

	LocalBase = Meme.Read<DWORD>(Client + LocalPlayer);/* CLIENT LOCAL BASE */
	[swap_lines]
	MyTeam = Meme.Read<int>(LocalBase + m_iTeamNum); /* GET LOCAL TEAM */
	MaxObjects = Meme.Read<int>(Client + EntityList + 0x4);
	sensitivity = Meme.Read<float>(Client + m_flSensitivity);
	crosshair = Meme.Read<int>(LocalBase + m_iCrossHairID);
	fflag = Meme.Read<int>(LocalBase + m_fFlag);
	[/swap_lines]
	tEntity = Meme.Read<DWORD>(Client + EntityList + ((crosshair - 1) * 16));
	tTeam = Meme.Read<int>(tEntity + m_iTeamNum);
	if (crosshair > 0 && crosshair < 64 && tTeam != MyTeam)
		eInCH = true;
	else
		eInCH = false;
}

/* --------------- */
/*    GLOW/RADAR   */
/* --------------- */

struct GlowStruct
{
	float r;    /* RED                  */ /* MAXIMUM 1.0f | MINIMUM 0.0f */
	float g;    /* GREEN                */ /* MAXIMUM 1.0f | MINIMUM 0.0f */
	float b;    /* BLUE                 */ /* MAXIMUM 1.0f | MINIMUM 0.0f */
	float a;    /* THICKNESS            */ /* MAXIMUM 1.0f | MINIMUM 0.0f */
	bool rwo;   /* RenderWhenOccluded   */
	bool rwuo;  /* RenderWhenUnoccluded */
};

void DrawGlow(int GlowIndex, GlowStruct Color)
{
	[swap_lines]
	Meme.Write<float>((GlowPointer + ((GlowIndex * 0x38) + 0x4)), Color.r);     /* SET FLOAT VALUE FOR RED       */
	Meme.Write<float>((GlowPointer + ((GlowIndex * 0x38) + 0x8)), Color.g);     /* SET FLOAT VALUE FOR GREEN     */
	Meme.Write<float>((GlowPointer + ((GlowIndex * 0x38) + 0xC)), Color.b);     /* SET FLOAT VALUE FOR BLUE      */
	Meme.Write<float>((GlowPointer + ((GlowIndex * 0x38) + 0x10)), Color.a);    /* SET FLOAT VALUE FOR THICKNESS */
	Meme.Write<bool>((GlowPointer + ((GlowIndex * 0x38) + 0x24)), Color.rwo);
	Meme.Write<bool>((GlowPointer + ((GlowIndex * 0x38) + 0x25)), Color.rwuo);
	[/swap_lines]

}
[swap_lines]
GlowStruct CGreen = { 0.f, 0.4f, 0.f, 1.f, true, false };
GlowStruct CYellow = { 0.4f, 0.4f, 0.f, 1.f, true, false };
GlowStruct CRed = { 0.4f, 0.f, 0.f, 1.f, true, false };
GlowStruct CBlue = { 0.f, 0.f, 0.4f, 1.f, true, false };
GlowStruct COrange = { 1.f, 0.5, 0.f, 1.f, true, false };
[/swap_lines]


void NoFlash() {
	float MaxFlash = Meme.Read<float>(LocalBase + m_flFlashMaxAlpha);
	if (fON && MaxFlash > 0.f) {
		Meme.Write<float>(LocalBase + m_flFlashMaxAlpha, 0.f);
	}
	if (!fON && MaxFlash != 225.f) {
		Meme.Write<float>(LocalBase + m_flFlashMaxAlpha, 225.f);
	}
}
/* ESP */
void ESPRadar(){

	for (int g = 0; g < MaxObjects; g++) /* LOOP START */
	{
		GlowPointer = Meme.Read<DWORD>(Client + m_dwGlowObject);	 /* POINTER TO LOCAL PLAYER GLOW VIEW */
		currentplayer = Meme.Read<DWORD>(Client + EntityList + ((g - 1) * 16)); /* READ ENTITY DATA FROM LOOP */
		currentplayerdormant = Meme.Read<bool>(currentplayer + isDormant); /* CHECK IF IS DORMANT */
		HealthBasedESP = Meme.Read<int>(currentplayer + m_iHealth); /* READ ENTITY HP */		
		if (rON){
			if (Meme.Read<int>(Client + m_bSpotted) != 1) {
				Meme.Write<int>(Client + m_bSpotted, 1);
			}
		}

		if (eON) {

			if (!currentplayerdormant) /* IF NOT DORMANT */
			{
				currentplayerglowindex = Meme.Read<int>(currentplayer + m_iGlowIndex); /* READ ENTITY GLOW INDEX */
				currentplayerteam = Meme.Read<int>(currentplayer + m_iTeamNum); /* READ ENTITY TEAM */											
				if (currentplayerteam != MyTeam)
				{
					if (HealthBasedESP <= 100 && HealthBasedESP > 75) /* LESS OR EQUAL 100 OR MORE THAN 75 */
					{
							DrawGlow(currentplayerglowindex, CGreen);
					}
					else if (HealthBasedESP <= 75 && HealthBasedESP > 50) /* LESS OR EQUAL 75 OR MORE THAN 50 */
					{
				
							DrawGlow(currentplayerglowindex, CYellow);
					}
					else if (HealthBasedESP <= 50 && HealthBasedESP > 25) /* LESS OR EQUAL 50 OR MORE THAN 25 */
					{
						
							DrawGlow(currentplayerglowindex, COrange);
					}
					else if (HealthBasedESP <= 25 && HealthBasedESP > 0) /* LESS OR EQUAL 25 OR MORE THAN 0 */
					{
					DrawGlow(currentplayerglowindex, CRed);
					}
				}
			
				}

			}

		}
	}





void bhop() {
	if (fflag == FL_ON_GROUND && (GetAsyncKeyState(VK_SPACE) & Pressed)) {
		Meme.Write<int>(Client + jumpoffset, 1);
		Sleep(10);
		Meme.Write<int>(Client + jumpoffset, 0);
	}
}



void triggerslow() {
	
	if (tON && eInCH) {
		if (GetAsyncKeyState(VK_MENU) & Pressed) {
			Sleep(triggerdelay);
			mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
			Sleep(2);
			mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
			Sleep(2);
		}
	
	}
	if (sON) {
		if (eInCH && Meme.Read<float>(Client + m_flSensitivity) != slowaim) {
			Meme.Write<float>(Client + m_flSensitivity, slowaim);
		}
		if (!eInCH && Meme.Read<float>(Client + m_flSensitivity) != oldaim) {
			Meme.Write<float>(Client + m_flSensitivity, oldaim);
		}
	}
}


