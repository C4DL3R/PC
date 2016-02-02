
const DWORD LocalPlayer = 0x00A6D444;
const DWORD EntityList = 0x04A5B8F4;
const DWORD m_dwGlowObject = 0x04B70B9C;
const DWORD m_EntityLoopDistance = 0x10;
const DWORD m_iGlowIndex = 0x0000BF10;
const DWORD isDormant = 0x000000E9;
const DWORD m_iTeamNum = 0x000000F0;
const DWORD m_iHealth = 0x000000FC;
const DWORD m_iCrossHairID = 0x0000C550;
const DWORD m_bSpotted = 0x00000935;
const DWORD m_flFlashMaxAlpha = 0x0000BEF4;
const DWORD m_flSensitivity = 0x00A72C4C;
const DWORD m_fFlag = 0x00000100;
const DWORD jumpoffset = 0x04AF0464;



HWND TargetWindow;
DWORD tEntity;
DWORD Client;
DWORD LocalBase;
DWORD GlowPointer;
DWORD currentplayer;

float sensitivity;
float oldaim;
bool eInCH = false;
bool isSlow = false;
bool currentplayerdormant;
int MaxObjects;
int crosshair;
int triggerdelay;
int afterfire;
int MyTeam;
int tTeam;
int currentplayerteam;
int currentplayerglowindex;
int LocalPlayerTeam;
int HealthBasedESP;
int inCross;
int fflag;

