#include "SensitivityModule.h"

std::vector<std::string> ignoreList = { "ApplicationFrameWindow" , "Windows.UI.Core.CoreWindow" , "DummyDWMListenerWindow" , "EdgeUiInputTopWndClass" , "WorkerW" , "Shell_TrayWnd" };

bool compareIgnoreList(std::string str)
{
    bool flag = true;
    for (auto& entry : ignoreList)
    {
        if (str == entry)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

SensitivityModule::SensitivityModule()
{
	//mSensitiveBoxList
}

bool isBoxInWindow(QRect& rect, winData& window)
{
    return rect.left() >= window.left 
        && rect.top() >= window.top 
        && rect.right() <= window.right 
        && rect.bottom() <= window.bottom;
}

void SensitivityModule::update()
{
    mMapBoxInfo.clear();
	updateWinInfo();
    for (auto& box : mAllBoxes)
    {
        for (auto it = mMapWinInfo.begin(); it != mMapWinInfo.end(); ++it)
        {
            if (isBoxInWindow(box, it->second))
            {
                auto boxIt = mMapBoxInfo.find(it->first);
                if (boxIt == mMapBoxInfo.end())
                {
                    mMapBoxInfo[it->first] = {box};
                }
                else
                {
                    boxIt->second.push_back(box);
                }
                break;
            }
            mPrevMapWinInfo.insert(std::make_pair(it->first, it->second));
        }
    }
}
event SensitivityModule::trackEvent(winData& prev, winData& curr)
{
    event ret;
    //"Position: (" << rect.left << ", " << rect.top << ")" << std::endl;
    //std::cout << "Size: " << (rect.right - rect.left) << " x " << (rect.bottom - rect.top)
    long prev_hdim = prev.right - prev.left;
    long prev_vdim = prev.bottom - prev.top;

    long curr_hdim = curr.right - curr.left;
    long curr_vdim = curr.bottom - curr.top;

    if (prev_hdim == curr_hdim && prev_vdim == curr_hdim)
    {
        if (prev.left == curr.left && prev.top == curr.top)
        {
            ret = UNCHANGED;
        }
        else
        {
            ret = MOVED;
        }
    }
    else
    {
        // TODO : add rest of the cases here
        ret = UNKNOWN;
    }

    return ret;
}
void SensitivityModule::updateRelative()
{
    updateWinInfo();
    for (auto it = mMapWinInfo.begin(); it != mMapWinInfo.end(); ++it)
    {
        auto boxWindowIt = mMapBoxInfo.find(it->first);
        if (boxWindowIt != mMapBoxInfo.end())
        {
            auto prevWin = mPrevMapWinInfo.find(it->first)->second;
            if (trackEvent(prevWin, it->second) == MOVED)
            {
                for (auto& box : boxWindowIt->second)
                {
                    long dx = it->second.left - prevWin.left;
                    long dy = it->second.top - prevWin.top;
                    box.translate(dx, dy);
                }
            }
        }
    }
    updateBoxInfo();
}

void SensitivityModule::updateBoxInfo()
{
    mAllBoxes.clear();
    for (auto it = mMapBoxInfo.begin(); it != mMapBoxInfo.end(); ++it)
    {
        for (auto& box : it->second)
        {
            mAllBoxes.push_back(box);
        }
    }
}

BOOL CALLBACK getWindowInfo(HWND hwnd, LPARAM lParam)
{
    SensitivityModule& obj = (SensitivityModule&)lParam;

    if (IsWindowVisible(hwnd))
    {
        winData temp;
        if (GetClassNameA(hwnd, temp.className, sizeof(temp.className)))
        {
            RECT rect;
            WINDOWPLACEMENT placement;
            placement.length = sizeof(WINDOWPLACEMENT);
            if (compareIgnoreList(temp.className))
            {
                GetWindowRect(hwnd, &rect);
                GetWindowTextA(hwnd, temp.title, sizeof(temp.title));
                GetWindowPlacement(hwnd, &placement);
                temp.hwnd = hwnd;
                temp.showCmd = placement.showCmd;
                temp.left = rect.left;
                temp.right = rect.right;
                temp.top = rect.top;
                temp.bottom = rect.bottom;
                obj.mMapWinInfo.insert(std::pair{hwnd, temp});
            }
        }
    }
    return TRUE;
}

void SensitivityModule::updateWinInfo()
{
    mMapWinInfo.clear();
    EnumWindows(getWindowInfo, (LPARAM)this);
}

void SensitivityModule::copyWin(winData& obj)
{
	//memcpy(&mWinData, &obj, sizeof(obj));
}

void SensitivityModule::applyShift(long& xShift, long& yShift)
{
	// TODO redo  this
	//for (auto& rect : mSensitiveBoxList)
	//{
	//	rect.translate(xShift, yShift);
	//}
}