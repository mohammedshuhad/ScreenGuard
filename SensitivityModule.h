#ifndef SENSITIVITYMODULE_H
#define SENSITIVITYMODULE_H
#include <windows.h>
#include <QRect>
#include <map>
#include <QDebug>
#include <QMutex>
#include <memory>

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
	winData(const winData& arg)
		:hwnd(arg.hwnd), showCmd(arg.showCmd), left(arg.left), right(arg.right), top(arg.top), bottom(arg.bottom)
	{
		strcpy_s(title, arg.title);
		strcpy_s(className, arg.className);
	}
} winData;

typedef struct winAssociation
{
    winData win;
    std::vector<QRect> boxes;
    winAssociation()
    {
        boxes.clear();
        memset(&win, 0, sizeof(win));
    }
	winAssociation(winData& arg)
	{
		memcpy(&win, &arg, sizeof(winData));
	}
}winAssociation;

struct ocrData
{
//private:
//	static std::shared_ptr<ocrData> prevInstance = nullptr;
//	static std::shared_ptr<ocrData> currInstance;
//public:
//	static std::shared_ptr<ocrData> getPrev()
//	{
//		if (!prevInstance)
//		{
//			prevInstance = std::make_shared<ocrData>(true);
//		}
//		return prevInstance;
//	}
//	static std::shared_ptr<ocrData> getCurr()
//	{
//		if (!currInstance)
//		{
//			currInstance = std::make_shared<ocrData>(true);
//		}
//		return currInstance;
//	}
    bool contains;
    bool classified;
    bool secondary;
    int cycleCount;
    int confidence;
    std::vector<QRect> uBoxes;
    std::vector<std::shared_ptr<winAssociation>> association;
	void classify();
	void clearAssociation();
	bool present(HWND hwnd);
	void updatePosition();

    ocrData(bool sec) : cycleCount(0), confidence(0), contains(false), classified(false), secondary(sec)
    {
        uBoxes.clear();
        association.clear();
    }

    ocrData(ocrData& arg) :cycleCount(arg.cycleCount), confidence(arg.confidence),
        contains(arg.contains), classified(arg.classified), secondary(arg.secondary)
    {
        uBoxes.clear();
        association.clear();
        for (auto& box : arg.uBoxes)
        {
            uBoxes.push_back(box);
        }
        for (auto& assn : arg.association)
        {
            association.push_back(assn);
        }
    }
};

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
	SensitivityModule(const SensitivityModule&) = delete;

	static SensitivityModule& Get()
	{
		static SensitivityModule mInstance;
		return mInstance;
	}
	std::map<HWND, winData> mMapWinInfo;
	void update(bool& secondary);
	bool updateRelative(bool& secondary);
	void getList(bool secondary, std::vector<QRect>& boxes);
	void fillAndClassify(bool& secondary, std::vector<QRect>& boxes);
	std::vector<winData> getWinList(bool prev, bool secondary);
	event trackEvent(winData& prev, winData& curr);
private:
	QMutex mutex;
	bool mReady;
	void makeList(std::vector<QRect>& boxes);
	std::map<HWND, winData> mPrevMapWinInfo;
	std::map<HWND, std::vector<QRect>> mMapBoxInfo;
	void updateWinInfo(bool& secondary);
	
};

#endif

