#include "FinalPacman.h"//Fix bugs and add documentation!!!
class timer {
public: int time;
	int tick(int c) {
		Sleep(0x3E8 * c);
		time -= c;
		return time;
}	};
timer clock, ghostTimer;
int ghostsEaten = 0, Round = 0, lives = 2, eatNum = 1, score = 0, G1P = -1, G2P = -2, G3P = -1, G4P = -1, FRZINC = 10;
bool lost = false, immune = false, doingPacMan = false;
wchar_t szWindowClass[100];
long __stdcall WndProc(HWND__* hWnd, unsigned int message, unsigned int wParam, long lParam);
vector<HDC__*> object_DCs = { CreateCompatibleDC(0), CreateCompatibleDC(0x0), CreateCompatibleDC(0), CreateCompatibleDC(0), CreateCompatibleDC(0x0), CreateCompatibleDC(0) };
tagPOINT pos = { 365, 460 };
vector<tagPOINT> ghostPosList = { {310, 225}, {345, 225}, {330, 225}, {415, 225} };
char DIRECTION = 'A';
vector<char> lastGhostMoves[4] = { {'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A'} };
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
		SelectObject(object_DCs[0], pacBmp);
}	};
vector<Pellet> pellets_list, pac_pellets_list;
void doPellet(int x, int y) {
	Pellet cur;
	cur.init(x, y);
	pellets_list.push_back(cur);
}
void reset(int liveInc = lives - 0x1, int roundInc = Round) {
	G1P = -0x1, G2P = -0x2, G3P = -0x1, G4P = -0x1, eatNum = 0x1, lives = liveInc, Round = roundInc;
	pos = { 365, 460 };
	ghostPosList = { {310, 225}, {345, 225}, {330, 225}, {415, 225} };
	for (vector<char>& move : lastGhostMoves) move = { 'A', 'A', 'A', 'A' };
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
	HGDIOBJ temp = SelectObject(object_DCs[0], pacBmp), bT = SelectObject(object_DCs[1], bBmp), c1 = SelectObject(object_DCs[2], bmp), c2 = SelectObject(object_DCs[3], bmp2), c3 = SelectObject(object_DCs[4], bmp3), c4 = SelectObject(object_DCs[5], bmp4);
	while (GetMessageW(&msg, nullptr, 0x0, 0x0)) {
		if (!TranslateAcceleratorW(msg.hwnd, hAccelTable, &msg)) {
			pos.x = (pos.x + 700) % 700;
			for (int i = 0; i < 4; i++) ghostPosList[i].x = (ghostPosList[i].x + 700) % 700;
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
}	}	}
bool validMove(HDC__ *hdc, char move, tagPOINT cpos) {
	vector<tagPOINT> ghostPList;
	if (cpos.x == ghostPosList[0].x && cpos.y == ghostPosList[0].y) ghostPList = { ghostPosList[1], ghostPosList[2], ghostPosList[3] };
	else if (cpos.x == ghostPosList[1].x && cpos.y == ghostPosList[1].y) ghostPList = { ghostPosList[0], ghostPosList[2], ghostPosList[3] };
	else if (cpos.x == ghostPosList[2].x && cpos.y == ghostPosList[2].y) ghostPList = { ghostPosList[0], ghostPosList[1], ghostPosList[3] };
	else if (cpos.x == ghostPosList[3].x && cpos.y == ghostPosList[3].y) ghostPList = { ghostPosList[0], ghostPosList[1], ghostPosList[2] };
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
	const char moves[0x4] = { 'U', 'D', 'R', 'L' };
	for (tagPOINT cur : ghostPosList) {
		vector<char> curValidMoves;
		for (char curChar : moves) if (validMove(hdc, curChar, cur) == true) curValidMoves.push_back(curChar);
		ghostMoveLists.push_back(curValidMoves);
	}
	for (auto i = 0; i < ghostMoveLists.size(); i++) {
		if (ghostMoveLists[i].size() > 0x0) {
			if (ghostMoveLists[i].size() == 0x1) {
				if (i == 0x0) ghostPosList[0] = MoveGhost(ghostPosList[0], ghostMoveLists[i][0x0]);
				else if (i == 0x1) ghostPosList[1] = MoveGhost(ghostPosList[1], ghostMoveLists[i][0x0]);
				else if (i == 0x2) ghostPosList[2] = MoveGhost(ghostPosList[2], ghostMoveLists[i][0x0]);
				else ghostPosList[3] = MoveGhost(ghostPosList[3], ghostMoveLists[i][0x0]);
			}
			else {
				vector<char> priority, lastMoveList;
				if (i == 0 && G1P == -1) GT = { 365, 180 };
				else if (i == 0 && G1P == 0) GT = { 700, 25 };
				else if ((i == 0 && G1P == 1) || (i == 2 && G3P == 1 && sqrt((ghostPosList[2].x - pos.x) ^ 2 + (ghostPosList[2].y - pos.y) ^ 2) > 8)) GT = pos;
				else if (i == 1 && G2P == -2) GT = { 375, 165 };
				else if (i == 1 && G2P == -1) GT = { 445, 165 };
				else if (i == 1 && G2P == 0) GT = { 50, 25 };
				else if (i == 1 && G2P == 1) GT = { pos.x + 20, pos.y + 20 };
				else if (i == 2 && G3P == -1) GT = { 380, 175 };
				else if ((i == 2 && G3P == 0) || (i == 2 && G3P == 1 && !(sqrt((ghostPosList[2].x - pos.x) ^ 2 + (ghostPosList[2].y - pos.y) ^ 2) > 8))) GT = { 50, 469 };
				else if (i == 3 && G4P == -1) GT = { 415, 175 };
				else if (i == 3 && G4P == 0) GT = { 700, 469 };
				else if (i == 3 && G4P == 1) GT = { ghostPosList[0].x + 2 * abs(ghostPosList[0].x - pos.x), ghostPosList[0].y + 2 * abs(ghostPosList[0].y - pos.y) };
				cur = ghostPosList[i];
				lastMoveList = lastGhostMoves[i];
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
							vector<char> temp = { ghostMoveLists[i][j], lastMoveList[0], lastMoveList[1], lastMoveList[2] };
							lastMoveList = temp;
							broken = true;
							break;
				}	}	}
				if (broken == false) {
					cur = MoveGhost(cur, priority[0]);
					flip(lastMoveList);
					vector<char> temp = { priority[0], lastMoveList[0], lastMoveList[1], lastMoveList[2] };
					lastMoveList = temp;
				}
				if (i == 0) {
					ghostPosList[0] = cur;
					lastGhostMoves[0] = lastMoveList;
					if (ghostPosList[0].x == GT.x && ghostPosList[0].y == GT.y) G1P++;
				}
				else if (i == 1) {
					ghostPosList[1] = cur;
					lastGhostMoves[1] = lastMoveList;
					if (ghostPosList[1].x == GT.x && ghostPosList[1].y == GT.y) G2P++;
				}
				else if (i == 2) {
					ghostPosList[2] = cur;
					lastGhostMoves[2] = lastMoveList;
					if (ghostPosList[2].x == GT.x && ghostPosList[2].y == GT.y) G3P++;
				}
				else {
					ghostPosList[3] = cur;
					lastGhostMoves[3] = lastMoveList;
					if (ghostPosList[3].x == GT.x && ghostPosList[3].y == GT.y) G4P++;
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
	tagPAINTSTRUCT ps;
    switch (message) {
	case 0xF: {
		string msg = "Your Score Was: " + to_string(score), Msg = "You Ate " + to_string(ghostsEaten) + " Ghosts!", rd = "You Made It To Round " + to_string(Round) + "!", scoreStr = "Score: " + to_string(score), pathReal = "D:\\PacMan2.bmp";
		HDC__* hdc2 = BeginPaint(hWnd, &ps), * hdc = CreateCompatibleDC(0), * menuDC = CreateCompatibleDC(0);
		HANDLE menuImg = LoadImageW(0, wstring(pathReal.begin(), pathReal.end()).c_str(), 0, 0, 0, 0x10);
		HBITMAP__ *drawBmp = CreateCompatibleBitmap(hdc2, 750, 502);
		HGDIOBJ pacmanSELECT = SelectObject(hdc, drawBmp), H = SelectObject(menuDC, menuImg);
		InvalidateRect(hWnd, 0, false);
		if (doingPacMan == true) {
			vector<tagPOINT> ghostPos[4] = { { ghostPosList[0], {310, 225} } , { ghostPosList[1], {345, 225} } , { ghostPosList[2], {380, 225} } , { ghostPosList[3], {415, 225} } };
			BitBlt(hdc, 0, 0, 750, 502, object_DCs[1], 0, 0, (unsigned long)0xCC0020);
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
				POINT freezePelletArray[4] = { {50, 0x19}, {700, 0x19}, {50, 469 }, {700, 469} };
				for (POINT pelletPos : freezePelletArray) {
					Pellet cur;
					cur.init(pelletPos.x, pelletPos.y);
					pac_pellets_list.push_back(cur);
				}
				reset(lives, Round + 1);
			}
			if (lost == true) TextOutW(hdc, 0x0, 0x0, L"You died :(", 12), TextOutW(hdc, 0, 20, wstring(msg.begin(), msg.end()).c_str(), msg.length()), TextOutW(hdc, 0, 40, wstring(Msg.begin(), Msg.end()).c_str(), Msg.length()), TextOutW(hdc, 0, 60, wstring(rd.begin(), rd.end()).c_str(), rd.length());
			else {
				BitBlt(hdc, pos.x, pos.y, 0x19, 0x19, object_DCs[0], 0x0, 0x0, (unsigned long)0x00CC0020);
				for (auto i = 0x0; i < pellets_list.size(); i++) if (pellets_list[i].display == true) BitBlt(hdc, pellets_list[i].pos.x, pellets_list[i].pos.y, 5, 5, pellets_list[i].DC, 0, 0, (unsigned long)0xCC0020);
				for (auto i = 0x0; i < pac_pellets_list.size(); i++) if (pac_pellets_list[i].display == true) BitBlt(hdc, pac_pellets_list[i].pos.x, pac_pellets_list[i].pos.y, 7, 7, pac_pellets_list[i].DC, 0, 0, (unsigned long)0xCC0020);
				TextOutW(hdc, 0x0, 0x0, wstring(scoreStr.begin(), scoreStr.end()).c_str(), scoreStr.length());
				for (auto i = 0x0; i < lives; i++) BitBlt(hdc, 35 * i + 620, 270, 0x19, 0x19, object_DCs[0], 0x0, 0x0, (unsigned long)0xCC0020);
				if (DIRECTION == 'U') pos.y -= 0x5;
				else if (DIRECTION == 'D') pos.y += 0x5;
				else if (DIRECTION == 'L') pos.x -= 0x5;
				else if (DIRECTION == 'R') pos.x += 0x5;
				if (checkPos(hdc) == true && DIRECTION == 'U') pos.y += 0x5;
				else if (checkPos(hdc) == true && DIRECTION == 'D') pos.y -= 0x5;
				else if (checkPos(hdc) == true && DIRECTION == 'L') pos.x += 0x5;
				else if (checkPos(hdc) == true && DIRECTION == 'R') pos.x -= 0x5;
				vector<tagPOINT> ghostPos = { ghostPosList[0], ghostPosList[1], ghostPosList[2], ghostPosList[3] };
				for (auto i = 0; i < 4; i++) BitBlt(hdc, ghostPos[i].x, ghostPos[i].y, 0x19, 0x19, object_DCs[i+2], 0x0, 0x0, (unsigned int)0xCC0020);
		}	}
		else BitBlt(hdc, 0x0, 0x0, 0x2EE, 0x1F6, menuDC, 0x0, 0x0, (unsigned long)0xCC0020), TextOutW(hdc, 0x0, 0x0, L"Press Any Key to play Pacman!!! Warning: It does take a little while to load.", 78);
		BitBlt(hdc2, 0x0, 0x0, 0x2EE, 0x1F6, hdc, 0x0, 0x0, (unsigned long)0xCC0020);
		EndPaint(hWnd, &ps);
		break;
	}
	case 0x102:
		if (doingPacMan == false) {
			InvalidateRect(hWnd, 0, true);
			doingPacMan = true;
		}
		else {
			tagPOINT add = { 0, 0 };
			char d;
			if (toupper(wParam) == 'A') add = { -0x5, 0x0 };
			else if (toupper(wParam) == 'W') add = { 0x0, -0x5 };
			else if (toupper(wParam) == 'S') add = { 0x0, 0x5 };
			else if (toupper(wParam) == 'D') add = { 0x5, 0x0 };
			if (add.x == -5 && add.y == 0) d = 'L';
			else if (add.x == 0 && add.y == -5) d = 'U';
			else if (add.x == 0 && add.y == 5) d = 'D';
			else d = 'R';
			pos.x += add.x, pos.y += add.y;
			if (checkPos(GetDC(hWnd)) == false) DIRECTION = d;
			pos.x -= add.x, pos.y -= add.y;
		}
		break;
	case 0x2: PostQuitMessage(0);
    default: return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}
