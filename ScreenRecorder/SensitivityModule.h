#ifndef SENSITIVITYMODULE_H
#define SENSITIVITYMODULE_H
#include "WindowTracker.h"
#include <QRect>
#include <map>

typedef struct winData
{
	HWND hwnd;
	char title[256];
	char className[256];
	int showCmd;
	long left, right, top, bottom;
	winData()
		: hwnd(NULL), showCmd(-1), left(-100), right(-100), top(-100), bottom(-100)
	{
		strcpy_s(title, "");
		strcpy_s(className, "");
	}
} winData;

enum event
{
	MOVED = 0,
	RESIZED = 1,
	MINMIZED = 2,
	MAXIMIZED = 3,
	HIDDEN = 4,
	UNCHANGED = 5,
	UNKNOWN = 6
};

class SensitivityModule
{
public:
	SensitivityModule();
	void update();
	void updateRelative();
	std::map<HWND, winData> mMapWinInfo;
	std::vector<QRect> mAllBoxes;
private:
	//winData mWinData;
	std::map<HWND, winData> mPrevMapWinInfo;
	std::map<HWND, std::vector<QRect>> mMapBoxInfo;
	void copyWin(winData& obj);
	void applyShift(long& xShift, long& yShift);
	void updateBoxInfo();
	void updateWinInfo();
	event trackEvent(winData& prev, winData& curr);
};

#endif

