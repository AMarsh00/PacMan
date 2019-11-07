#include "FinalPacman.h"//Fix bugs and add documentation!!!
class timer {
public: int time;
	int tick(int c) {
		Sleep(0x3E8 * c);
		time -= c;
		return time;
}	};
timer clock, ghostTimer;
tagPOINT defaultPos = { 365, 460 }, defaultGPos = { 310, 225 }, defaultG2Pos = { 345, 225 }, defaultG3Pos = { 380, 225 }, defaultG4Pos = { 415, 225 };
int ghostsEaten = 0, Round = 0, lives = 2, eatNum = 1, score = 0, G1P = -1, G2P = -2, G3P = -1, G4P = -1, FRZINC = 10;
bool lost = false, immune = false, doingPacMan = false, onMenu = true;
wchar_t szWindowClass[100];
long __stdcall WndProc(HWND__* hWnd, unsigned int message, unsigned int wParam, long lParam);
HDC__* background_DC = CreateCompatibleDC(0x0), * pacmanDC = CreateCompatibleDC(0x0);
vector<HDC__*> ghostDCs = { CreateCompatibleDC(0x0), CreateCompatibleDC(0x0), CreateCompatibleDC(0x0), CreateCompatibleDC(0x0) };
tagPOINT pos = defaultPos, gpos = defaultGPos, g2pos = defaultG2Pos, g3pos = defaultG3Pos, g4pos = defaultG4Pos;
char lastGM = 'A', lastG2M = 'A', lastG3M = 'A', lastG4M = 'A', lastlastGM = 'A', lastlastG2M = 'A', lastlastG3M = 'A', lastlastG4M = 'A', lastlastlastGM = 'A', lastlastlastG2M = 'A', lastlastlastG3M = 'A', lastlastlastG4M = 'A', lastlastlastlastGM = 'A', lastlastlastlastG2M = 'A', lastlastlastlastG3M = 'A', lastlastlastlastG4M = 'A', DIRECTION = 'A';
class Pellet {
protected: string path = "C:\\Line.bmp";
public: POINT pos;
	HDC__ *DC;
	bool display;
	void init(int x, int y) {
		display = true;
		pos = { x, y };
		DC = CreateCompatibleDC(0x0);
		HANDLE pacBmp = LoadImageW(0x0, wstring(path.begin(), path.end()).c_str(), 0x0, 0x0, 0x0, 0x10);
		HGDIOBJ c = SelectObject(DC, pacBmp);
		SelectObject(pacmanDC, pacBmp);
}	};
vector<Pellet> pellets_list, pac_pellets_list;
void doPellet(int x, int y) {
	Pellet cur;
	cur.init(x, y);
	pellets_list.push_back(cur);
}
void reset(int liveInc = lives - 0x1, int roundInc = Round) {
	G1P = -0x1, G2P = -0x2, G3P = -0x1, G4P = -0x1, eatNum = 0x1, lives = liveInc, Round = roundInc;
	pos = defaultPos, gpos = defaultGPos, g2pos = defaultG2Pos, g3pos = defaultG3Pos, g4pos = defaultG4Pos;
	lastGM = 'A', lastG2M = 'A', lastG3M = 'A', lastG4M = 'A', lastlastGM = 'A', lastlastG2M = 'A', lastlastG3M = 'A', lastlastG4M = 'A', lastlastlastGM = 'A', lastlastlastG2M = 'A', lastlastlastG3M = 'A', lastlastlastG4M = 'A', lastlastlastlastGM = 'A', lastlastlastlastG2M = 'A', lastlastlastlastG3M = 'A', lastlastlastlastG4M = 'A';
}
int WINAPI wWinMain(_In_ HINSTANCE__ *hInstance, _In_opt_ HINSTANCE__ *hPrevInstance, _In_ WCHAR *lpCmdLine, _In_ int nCmdShow) {
	ghostTimer.time = .01, clock.time = 0x0;
	srand(0x0);
    LoadStringW(hInstance, 109, szWindowClass, 100);
	tagWNDCLASSEXW wcex;
	wcex.cbSize = sizeof(tagWNDCLASSEXW), wcex.style = 0x2 | 0x1, wcex.lpfnWndProc = WndProc, wcex.cbClsExtra = 0, wcex.cbWndExtra = 0, wcex.hInstance = hInstance, wcex.hIcon = LoadIconW(hInstance, ((LPCWSTR)((ULONG_PTR)((WORD)((107)))))), wcex.hCursor = LoadCursorW(nullptr, ((LPCWSTR)((ULONG_PTR)((WORD)(((32512))))))), wcex.hbrBackground = (HBRUSH)(6), wcex.lpszMenuName = ((LPCWSTR)((ULONG_PTR)((WORD)((109))))), wcex.lpszClassName = szWindowClass, wcex.hIconSm = LoadIconW(wcex.hInstance, ((LPCWSTR)((ULONG_PTR)((WORD)((108))))));
	RegisterClassExW(&wcex);
	string title = "Pacman!", pacPathReal = "D:\\PacMan.bmp", backgroundPath = "D:\\PacBack.bmp", gP = "D:\\GhostOne.bmp", g2P = "D:\\GhostTwo.bmp", g3P = "D:\\GhostThree.bmp", g4P = "D:\\GhostFour.bmp";
	HWND__ *hWnd = CreateWindowExW(0L, szWindowClass, wstring(title.begin(), title.end()).c_str(), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX, CW_USEDEFAULT, 0, 750, 532, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd) return 0x0;
	ShowWindow(hWnd, nCmdShow);
    HACCEL__ *hAccelTable = LoadAcceleratorsW(hInstance, ((wchar_t*)((unsigned long)((unsigned short)((109))))));
	HANDLE pacBmp = LoadImageW(0, wstring(pacPathReal.begin(), pacPathReal.end()).c_str(), 0, 0, 0, 0x10), bBmp = LoadImageW(0, wstring(backgroundPath.begin(), backgroundPath.end()).c_str(), 0, 0, 0, 0x00000010), bmp = LoadImageW(0, wstring(gP.begin(), gP.end()).c_str(), 0, 0, 0, 0x00000010), bmp2 = LoadImageW(0, wstring(g2P.begin(), g2P.end()).c_str(), 0, 0, 0, 0x00000010), bmp3 = LoadImageW(0, wstring(g3P.begin(), g3P.end()).c_str(), 0, 0, 0, 0x00000010), bmp4 = LoadImage(0, wstring(g4P.begin(), g4P.end()).c_str(), 0, 0, 0, 0x00000010);
	tagMSG msg;
	HGDIOBJ temp = SelectObject(pacmanDC, pacBmp), bT = SelectObject(background_DC, bBmp), c1 = SelectObject(ghostDCs[0], bmp), c2 = SelectObject(ghostDCs[1], bmp2), c3 = SelectObject(ghostDCs[2], bmp3), c4 = SelectObject(ghostDCs[3], bmp4);
	while (GetMessageW(&msg, nullptr, 0x0, 0x0)) {
		if (!TranslateAcceleratorW(msg.hwnd, hAccelTable, &msg)) {
			pos.x = (pos.x + 700) % 700, gpos.x = (gpos.x + 700) % 700, g2pos.x = (g2pos.x + 700) % 700, g3pos.x = (g3pos.x + 700) % 700, g4pos.x = (g4pos.x + 700) % 700;
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
}	}	}
bool validMove(HDC__ *hdc, char move, tagPOINT cpos) {
	vector<tagPOINT> ghostPList;
	if (cpos.x == gpos.x && cpos.y == gpos.y) ghostPList = { g2pos, g3pos, g4pos };
	else if (cpos.x == g2pos.x && cpos.y == g2pos.y) ghostPList = { gpos, g3pos, g4pos };
	else if (cpos.x == g3pos.x && cpos.y == g3pos.y) ghostPList = { gpos, g2pos, g4pos };
	else if (cpos.x == g4pos.x && cpos.y == g4pos.y) ghostPList = { gpos, g2pos, g3pos };
	if (move == 'U') cpos.y -= 0x5;
	else if (move == 'D') cpos.y += 0x5;
	else if (move == 'L') cpos.x -= 0x5;
	else cpos.x += 0x5;
	for (auto i = 0x0; i < 0x10; i++) if ((((unsigned char)(((unsigned long)((GetPixel(hdc, cpos.x + i + 6, cpos.y) >> 0x10))) & 0xff)) > 75 || ((unsigned char)(((unsigned long)((GetPixel(hdc, cpos.x + i + 6, cpos.y + 24) >> 16))) & 0xff)) > 75 || ((unsigned char)(((unsigned long)((GetPixel(hdc, cpos.x, cpos.y + i + 6) >> 16))) & 0xff)) > 75 || ((unsigned char)(((unsigned long)((GetPixel(hdc, cpos.x + 24, cpos.y + i + 6) >> 16))) & 0xff)) > 75)) return false;
	return true;
}
tagPOINT MoveGhost(tagPOINT cur_pos, char moveChar) {
	if (moveChar == 'U') return { cur_pos.x, cur_pos.y - 0x5 };
	else if (moveChar == 'D') return { cur_pos.x, cur_pos.y + 0x5 };
	else if (moveChar == 'L') return { cur_pos.x - 0x5, cur_pos.y };
	else return { cur_pos.x + 0x5, cur_pos.y };
}
void flip(vector<char>& list) {
	for (char& item : list) {
		if (item == 'U') item = 'D';
		else if (item == 'D') item = 'U';
		else if (item == 'L') item = 'R';
		else item = 'L';
}	}
void updateGhosts(HDC__ *hdc, int c, tagPOINT GT = { 0x0, 0x0 }, tagPOINT cur = { 0x0, 0x0 }) {
	ghostTimer.time = .1;
	vector<vector<char>> ghostMoveLists;
	vector<int> validGhosts;
	tagPOINT GhostPos[0x4] = { gpos, g2pos, g3pos, g4pos };
	const char moves[0x4] = { 'U', 'D', 'R', 'L' };
	for (tagPOINT cur : GhostPos) {
		vector<char> curValidMoves;
		for (char curChar : moves) if (validMove(hdc, curChar, cur) == true) curValidMoves.push_back(curChar);
		ghostMoveLists.push_back(curValidMoves);
	}
	for (auto i = 0; i < ghostMoveLists.size(); i++) {
		if (ghostMoveLists[i].size() > 0x0) {
			if (ghostMoveLists[i].size() == 0x1) {
				if (i == 0x0) gpos = MoveGhost(gpos, ghostMoveLists[i][0x0]);
				else if (i == 0x1) g2pos = MoveGhost(g2pos, ghostMoveLists[i][0x0]);
				else if (i == 0x2) g3pos = MoveGhost(g3pos, ghostMoveLists[i][0x0]);
				else g4pos = MoveGhost(g4pos, ghostMoveLists[i][0x0]);
			}
			else {
				vector<char> priority, lastMoveList;
				if (i == 0x0) {
					if (G1P == -1) GT = { defaultGPos.x + 55, defaultGPos.y - 45 };
					else if (G1P == 0) GT = { 700, 25 };
					else if (G1P == 1) GT = pos;
					cur = gpos;
					lastMoveList = { lastGM, lastlastGM, lastlastlastGM, lastlastlastlastGM };
				}
				else if (i == 0x1) {
					if (G2P == -2) GT = { defaultG2Pos.x + 30, defaultG2Pos.y - 60 };
					else if (G2P == -1) GT = { defaultG2Pos.x + 100, defaultG2Pos.y - 60 };
					else if (G2P == 0) GT = { 50, 25 };
					else if (G2P == 1) GT = { pos.x + 20, pos.y + 20 };
					cur = g2pos;
					lastMoveList = { lastG2M, lastlastG2M, lastlastlastG2M, lastlastlastlastG2M };
				}
				else if (i == 0x2) {
					if (G3P == -1) GT = { defaultG3Pos.x, defaultG3Pos.y - 50 };
					else if (G3P == 0) GT = { 50, 469 };
					else if (G3P == 1 && sqrt((g3pos.x - pos.x) ^ 2 + (g3pos.y - pos.y) ^ 2) > 8) GT = pos;
					else GT = { 50, 469 };
					cur = g3pos;
					lastMoveList = { lastG3M, lastlastG3M, lastlastlastG3M, lastlastlastlastG3M };
				}
				else {
					if (G4P == -1) GT = { defaultG4Pos.x, defaultG4Pos.y - 50 };
					else if (G4P == 0) GT = { 700, 469 };
					else if (G4P == 1) GT = { gpos.x + 2 * abs(gpos.x - pos.x), gpos.y + 2 * abs(gpos.y - pos.y) };
					cur = g4pos;
					lastMoveList = { lastG4M, lastlastG4M, lastlastlastG4M, lastlastlastlastG4M };
				}
				if (abs(GT.x - cur.x) > abs(GT.y - cur.y) && cur.x < GT.x && (cur.y < GT.y || (cur.y == GT.y && c == 1))) priority = { 'R', 'D', lastMoveList[0], 'U', 'L' };
				else if (abs(GT.x - cur.x) > abs(GT.y - cur.y) && cur.x < GT.x && !(cur.y < GT.y || (cur.y == GT.y && c == 1))) priority = { 'R', 'U', lastMoveList[0], 'D', 'L' };
				else if (abs(GT.x - cur.x) > abs(GT.y - cur.y) && cur.x == GT.x && cur.y < GT.y && c == 0) priority = { 'D', 'R', lastMoveList[0], 'L', 'U' };
				else if (abs(GT.x - cur.x) > abs(GT.y - cur.y) && cur.x == GT.x && cur.y < GT.y && c == 1) priority = { 'D', 'L', lastMoveList[0], 'R', 'U' };
				else if (abs(GT.x - cur.x) > abs(GT.y - cur.y) && cur.x == GT.x && cur.y >= GT.y && c == 0) priority = { 'U', 'R', lastMoveList[0], 'L', 'D' };
				else if (abs(GT.x - cur.x) > abs(GT.y - cur.y) && cur.x == GT.x && cur.y >= GT.y && c == 1) priority = { 'U', 'L', lastMoveList[0], 'R', 'D' };
				else if (abs(GT.x - cur.x) > abs(GT.y - cur.y) && cur.x >= GT.x && (cur.y == GT.y && c == 1)) priority = { 'R', 'D', lastMoveList[0], 'U', 'L' };
				else if (abs(GT.x - cur.x) > abs(GT.y - cur.y)) priority = { 'R', 'U', lastMoveList[0], 'D', 'L' };
				else if (!(abs(GT.x - cur.x) > abs(GT.y - cur.y)) && cur.y < GT.y && (cur.x < GT.x || (cur.x == GT.x && c == 0))) priority = { 'D', 'R', lastMoveList[0], 'L', 'U' };
				else if (!(abs(GT.x - cur.x) > abs(GT.y - cur.y)) && cur.y < GT.y && !(cur.x < GT.x || (cur.x == GT.x && c == 0))) priority = { 'D', 'L', lastMoveList[0], 'R', 'U' };
				else if (!(abs(GT.x - cur.x) > abs(GT.y - cur.y)) && cur.y == GT.y && cur.x < GT.x && c == 0) priority = { 'R', 'U', lastMoveList[0], 'D', 'L' };
				else if (!(abs(GT.x - cur.x) > abs(GT.y - cur.y)) && cur.y == GT.y && cur.x < GT.x && c == 1) priority = { 'R', 'D', lastMoveList[0], 'U', 'L' };
				else if (!(abs(GT.x - cur.x) > abs(GT.y - cur.y)) && cur.y == GT.y && cur.x >= GT.x && c == 0) priority = { 'L', 'U', lastMoveList[0], 'D', 'R' };
				else if (!(abs(GT.x - cur.x) > abs(GT.y - cur.y)) && cur.y == GT.y && cur.x >= GT.x && c == 1) priority = { 'L', 'D', lastMoveList[0], 'U', 'R' };
				else if (!(abs(GT.x - cur.x) > abs(GT.y - cur.y)) && cur.x < GT.x || (cur.x == GT.x && c == 0)) priority = { 'U', 'R', lastMoveList[0], 'L', 'D' };
				else priority = { 'U', 'L', lastMoveList[0], 'R', 'D' };
				flip(lastMoveList);
				bool broken = false;
				for (char highestPriority : priority) {
					for (auto j = 0; j < ghostMoveLists[i].size(); j++) {
						if (highestPriority != lastMoveList[0] && highestPriority != lastMoveList[1] && highestPriority != lastMoveList[2] && highestPriority != lastMoveList[3] && highestPriority == ghostMoveLists[i][j] && broken == false) {
							cur = MoveGhost(cur, ghostMoveLists[i][j]);
							flip(lastMoveList);
							lastMoveList[3] = lastMoveList[2];
							lastMoveList[2] = lastMoveList[1];
							lastMoveList[1] = lastMoveList[0];
							lastMoveList[0] = ghostMoveLists[i][j];
							broken = true;
							break;
				}	}	}
				if (broken == false) {
					cur = MoveGhost(cur, priority[0]);
					flip(lastMoveList);
					lastMoveList[3] = lastMoveList[2];
					lastMoveList[2] = lastMoveList[1];
					lastMoveList[1] = lastMoveList[0];
					lastMoveList[0] = priority[0];
				}
				if (i == 0) {
					gpos = cur;
					lastlastlastlastGM = lastMoveList[3];
					lastlastlastGM = lastMoveList[2];
					lastlastGM = lastMoveList[1];
					lastGM = lastMoveList[0];
					if (gpos.x == GT.x && gpos.y == GT.y) G1P++;
				}
				else if (i == 1) {
					g2pos = cur;
					lastlastlastlastG2M = lastMoveList[3];
					lastlastlastG2M = lastMoveList[2];
					lastlastG2M = lastMoveList[1];
					lastG2M = lastMoveList[0];
					if (g2pos.x == GT.x && g2pos.y == GT.y) G2P++;
				}
				else if (i == 2) {
					g3pos = cur;
					lastlastlastlastG3M = lastMoveList[3];
					lastlastlastG3M = lastMoveList[2];
					lastlastG3M = lastMoveList[1];
					lastG3M = lastMoveList[0];
					if (g3pos.x == GT.x && g3pos.y == GT.y) G3P++;
				}
				else {
					g4pos = cur;
					lastlastlastlastG4M = lastMoveList[3];
					lastlastlastG4M = lastMoveList[2];
					lastlastG4M = lastMoveList[1];
					lastG4M = lastMoveList[0];
					if (g4pos.x == GT.x && g4pos.y == GT.y) G4P++;
}	}	}	}	}
bool checkPos(HDC__ *hdc) {
	for (auto i = 0; i < 0x8; i++) if (GetBValue(GetPixel(hdc, pos.x + 2 * i + 5, pos.y)) > 75 || GetBValue(GetPixel(hdc, pos.x + 2 * i + 5, pos.y + 21)) > 75 || GetBValue(GetPixel(hdc, pos.x, pos.y + 2 * i + 5)) > 75 || GetBValue(GetPixel(hdc, pos.x + 21, pos.y + 2 * i + 5)) > 75) return true;
	return false;
}
void doRemoval(vector<Pellet>& pList, int scoreInc) {
	loop: for (auto i = 0; i < pList.size(); i++) {
		Pellet cur = pList[i];
		if (cur.display == true && cur.pos.x <= pos.x + 25 && cur.pos.x >= pos.x - 0xA && cur.pos.y >= pos.y - 0xA && cur.pos.y <= pos.y + 25) {
			score += scoreInc;
			if (scoreInc == 50) clock.time = FRZINC;
			vector<Pellet> temp;
			for (auto j = 0x0; j < pList.size(); j++) if (j != i) temp.push_back(pList[j]);
			pList = temp;
			goto loop;
}	}	}
long __stdcall WndProc(HWND__ *hWnd, unsigned int message, unsigned int wParam, long lParam) {
    switch (message) {
	case 0xF: {
		string msg = "Your Score Was: " + to_string(score), Msg = "You Ate " + to_string(ghostsEaten) + " Ghosts!", rd = "You Made It To Round " + to_string(Round) + "!", scoreStr = "Score: " + to_string(score), pathReal = "D:\\PacMan2.bmp";
		tagPAINTSTRUCT ps;
		HDC__ *hdc2 = BeginPaint(hWnd, &ps), *hdc = CreateCompatibleDC(0), *menuDC = CreateCompatibleDC(0);
		HANDLE menuImg = LoadImageW(0, wstring(pathReal.begin(), pathReal.end()).c_str(), 0, 0, 0, 0x10);
		HBITMAP__ *drawBmp = CreateCompatibleBitmap(hdc2, 750, 502);
		HGDIOBJ pacmanSELECT = SelectObject(hdc, drawBmp), H = SelectObject(menuDC, menuImg);
		InvalidateRect(hWnd, 0, false);
		if (doingPacMan == true) {
			vector<tagPOINT> ghostPos[4] = { { gpos, defaultGPos } , { g2pos, defaultG2Pos } , { g3pos, defaultG3Pos } , { g4pos, defaultG4Pos } };
			BitBlt(hdc, 0, 0, 750, 502, background_DC, 0, 0, (unsigned long)0xCC0020);
			if (ghostTimer.tick(.01) <= 0) updateGhosts(hdc, rand() % 2);
			Sleep(25);
			if (clock.tick(.01) > 0x0) immune = true;
			else immune = false;
			doRemoval(pellets_list, 10), doRemoval(pac_pellets_list, 50);
			for (vector<tagPOINT>& cur : ghostPos) if (cur[0].x <= pos.x + 25 && pos.x <= cur[0x0].x + 25 && cur[0].y <= pos.y + 25 && pos.y <= cur[0].y + 25) {
				if (immune == false && lives > 0x0) reset();
				else if (immune == false && lives <= 0x0) lost = true;
				else {
					cur[0x0] = cur[0x1];
					score += 100 * pow(0x2, eatNum), eatNum++, ghostsEaten++;
					G1P = -1, G2P = -2, G3P = -1, G4P = -1;
			}	}
			if (pac_pellets_list.size() == 0x0 && pellets_list.size() == 0x0) {
				vector<int> pelletInitList[31] = { {5, 36, 25}, {40, 71, 25}, {0, 27, 230}, {48, 74, 230}, {5, 71, 469}, {4, 71, 87}, {4, 19, 138}, {25, 32, 138}, {41, 50, 138}, {57, 71, 138}, {4, 34, 325}, {41, 71, 325}, {4, 11, 371}, {17, 58, 371}, {64, 71, 371}, {17, 19, 185}, {25, 50, 185}, {57, 59, 185}, {4, 7, 55}, {17, 19, 55}, {33, 36, 55}, {40, 44, 55}, {56, 59, 55}, {68, 71, 55}, {17, 20, 279}, {24, 50, 279}, {55, 59, 279}, {4, 19, 416}, {24, 35, 416}, {40, 51, 416}, {56, 71, 416} };
				for (vector<int> curList : pelletInitList) for (auto i = curList[0]; i < curList[1]; i++) doPellet(10 * i, curList[2]);
				Pellet p, q, r, s;
				p.init(50, 0x19);
				q.init(700, 0x19);
				r.init(50, 469);
				s.init(700, 469);
				pac_pellets_list = { p, q, r, s };
				(lives, Round + 1);
			}
			if (lost == true) TextOutW(hdc, 0x0, 0x0, L"You died :(", 12), TextOutW(hdc, 0, 20, wstring(msg.begin(), msg.end()).c_str(), msg.length()), TextOutW(hdc, 0, 40, wstring(Msg.begin(), Msg.end()).c_str(), Msg.length()), TextOutW(hdc, 0, 60, wstring(rd.begin(), rd.end()).c_str(), rd.length());
			else {
				BitBlt(hdc, pos.x, pos.y, 0x19, 0x19, pacmanDC, 0x0, 0x0, (unsigned long)0x00CC0020);
				for (auto i = 0x0; i < pellets_list.size(); i++) if (pellets_list[i].display == true) BitBlt(hdc, pellets_list[i].pos.x, pellets_list[i].pos.y, 5, 5, pellets_list[i].DC, 0, 0, (unsigned long)0xCC0020);
				for (auto i = 0x0; i < pac_pellets_list.size(); i++) if (pac_pellets_list[i].display == true) BitBlt(hdc, pac_pellets_list[i].pos.x, pac_pellets_list[i].pos.y, 7, 7, pac_pellets_list[i].DC, 0, 0, (unsigned long)0xCC0020);
				TextOutW(hdc, 0x0, 0x0, wstring(scoreStr.begin(), scoreStr.end()).c_str(), scoreStr.length());
				for (auto i = 0x0; i < lives; i++) BitBlt(hdc, 35 * i + 620, 270, 0x19, 0x19, pacmanDC, 0x0, 0x0, (unsigned long)0xCC0020);
				if (DIRECTION == 'U') pos.y -= 0x5;
				else if (DIRECTION == 'D') pos.y += 0x5;
				else if (DIRECTION == 'L') pos.x -= 0x5;
				else if (DIRECTION == 'R') pos.x += 0x5;
				if (checkPos(hdc) == true && DIRECTION == 'U') pos.y += 0x5;
				else if (checkPos(hdc) == true && DIRECTION == 'D') pos.y -= 0x5;
				else if (checkPos(hdc) == true && DIRECTION == 'L') pos.x += 0x5;
				else if (checkPos(hdc) == true && DIRECTION == 'R') pos.x -= 0x5;
				vector<tagPOINT> ghostPos = { gpos, g2pos, g3pos, g4pos };
				for (auto i = 0; i < ghostDCs.size(); i++) BitBlt(hdc, ghostPos[i].x, ghostPos[i].y, 0x19, 0x19, ghostDCs[i], 0x0, 0x0, (unsigned int)0xCC0020);
		}	}
		else if (onMenu == true) {
			BitBlt(hdc, 0x0, 0x0, 0x2EE, 0x1F6, menuDC, 0x0, 0x0, (unsigned long)0xCC0020);
			TextOutW(hdc, 0x0, 0x0, L"Press Any Key to play Pacman!!!", 0x20);
		}
		BitBlt(hdc2, 0x0, 0x0, 0x2EE, 0x1F6, hdc, 0x0, 0x0, (unsigned long)0xCC0020);
		EndPaint(hWnd, &ps);
		break;
	}
	case 0x102: {
		if (doingPacMan == true) {
			tagPOINT add;
			char d;
			switch (toupper(wParam)) {
			case 'A':
				add = { -0x5, 0x0 };
				d = 'L';
				break;
			case 'W':
				add = { 0x0, -0x5 };
				d = 'U';
				break;
			case 'S':
				add = { 0x0, 0x5 };
				d = 'D';
				break;
			case 'D':
				add = { 0x5, 0x0 };
				d = 'R';
				break;
			default: return 0x0;
			}
			pos.x += add.x, pos.y += add.y;
			if (checkPos(GetDC(hWnd)) == false) DIRECTION = d;
			pos.x -= add.x, pos.y -= add.y;
		}
		else if (onMenu == true) {
			InvalidateRect(hWnd, 0, true);
			onMenu = false;
			doingPacMan = true;
		}
		break;
	}
	case 0x2: PostQuitMessage(0);
    default: return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}
