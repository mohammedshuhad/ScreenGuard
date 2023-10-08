#include "SensitivityModule.h"

bool isBoxInWindow(QRect& rect, winData& window, bool& secondary)
{
    if (!secondary)
    {
        return rect.left() >= window.left
            && rect.top() >= window.top
            && rect.right() <= window.right
            && rect.bottom() <= window.bottom;
    }
    else
    {
        return rect.left() >= window.left
            && rect.top() >= (window.top + 1080)
            && rect.right() <= window.right
            && rect.bottom() <= (window.bottom + 1080);
    }
}

void ocrData::classify()
{
    if (!classified && contains)
    {
        for (auto& assn : association)
        {
            for (auto& box : uBoxes)
            {
                if (isBoxInWindow(box, assn->win, secondary))
                {
                    assn->boxes.push_back(box);
                }
            }
        }
        classified = true;
    }
}
bool ocrData::present(HWND hwnd)
{
    bool ret = false;
    for (auto& assn : association)
    {
        if (assn->win.hwnd == hwnd)
        {
            ret = true;
            break;
        }
    }
    return ret;
}

void ocrData::updatePosition()
{
    if (classified)
    {
        uBoxes.clear();
        for (auto& assn : association)
        {
            if (IsWindowVisible(assn->win.hwnd))
            {
                RECT windowRect;
                char windowTitle[256];
                GetWindowRect(assn->win.hwnd, &windowRect);
                GetWindowTextA(assn->win.hwnd, windowTitle, sizeof(windowTitle));
                WINDOWPLACEMENT wp = { sizeof(WINDOWPLACEMENT) };
                GetWindowPlacement(assn->win.hwnd, &wp);
                winData temp;
                temp.hwnd = assn->win.hwnd;
                strcpy_s(temp.title, windowTitle);
                temp.showCmd = wp.showCmd;
                temp.left = windowRect.left;
                temp.right = windowRect.right;
                temp.top = windowRect.top;
                temp.bottom = windowRect.bottom;
                if (SensitivityModule::Get().trackEvent(assn->win, temp) == MOVED)
                {
                    for (auto& box : assn->boxes)
                    {
                        long dx = temp.left - assn->win.left;
                        long dy = temp.top - assn->win.top;
                        box.translate(dx, dy);
                        uBoxes.push_back(box);
                    }
                    qDebug() << "Move Event\n";
                }
                else
                {
                    for (auto& box : assn->boxes)
                    {
                        long dx = temp.left - assn->win.left;
                        long dy = temp.top - assn->win.top;
                        box.translate(dx, dy);
                        uBoxes.push_back(box);
                    }
                    qDebug() << "Unknown Event\n";
                }

            }
        }
    }
    else
    {
        qDebug() << "Not Classified\n";
    }
}
void ocrData::clearAssociation()
{
    association.clear();
}

SensitivityModule::SensitivityModule()
{
    mReady = false;
}
//BOOL CALLBACK EnumWindowsProcPrev(HWND hwnd, LPARAM lParam)
//{
//    RECT windowRect;
//    if (IsWindowVisible(hwnd))
//    {
//        char windowTitle[256];
//        GetWindowRect(hwnd, &windowRect);
//        GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
//        if (windowTitle[0] != '\0'
//            && strncmp(windowTitle, "Settings", sizeof(windowTitle)) != 0
//            && strncmp(windowTitle, "Program Manager", sizeof(windowTitle)) != 0)
//        {
//            HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
//            MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
//            WINDOWPLACEMENT wp = { sizeof(WINDOWPLACEMENT) };
//            GetWindowPlacement(hwnd, &wp);
//            if (GetMonitorInfo(hMonitor, &monitorInfo) && (wp.showCmd == 1 || wp.showCmd == 3))
//            {
//                winData temp;
//                if (monitorInfo.dwFlags & MONITORINFOF_PRIMARY)
//                {
//                    if (ocrData::getPrev()->secondary)
//                    {
//                        temp.hwnd = hwnd;
//                        strcpy_s(temp.title, windowTitle);
//                        temp.showCmd = wp.showCmd;
//                        temp.left = windowRect.left;
//                        temp.right = windowRect.right;
//                        temp.top = windowRect.top;
//                        temp.bottom = windowRect.bottom;
//                        if (!ocrData::getPrev()->present(hwnd))
//                        {
//                            ocrData::getPrev()->association.push_back(std::make_shared<winAssociation>(temp));
//                        }
//                        else
//                        {
//                            qDebug() << "Not present in : " << windowTitle << "\n";
//                        }
//                        //SensitivityModule::Get().mMapWinInfo.insert(std::pair{hwnd, temp});
//                    }
//                    return TRUE;
//                }
//
//                if (windowRect.left >= monitorInfo.rcMonitor.left &&
//                    windowRect.top >= monitorInfo.rcMonitor.top &&
//                    windowRect.right <= monitorInfo.rcMonitor.right &&
//                    windowRect.bottom <= monitorInfo.rcMonitor.bottom)
//                {
//                    if (ocrData::getPrev()->secondary)
//                    {
//                        temp.hwnd = hwnd;
//                        strcpy_s(temp.title, windowTitle);
//                        temp.showCmd = wp.showCmd;
//                        temp.left = windowRect.left;
//                        temp.right = windowRect.right;
//                        temp.top = windowRect.top;
//                        temp.bottom = windowRect.bottom;
//                        if (!ocrData::getPrev()->present(hwnd))
//                        {
//                            ocrData::getPrev()->association.push_back(std::make_shared<winAssociation>(temp));
//                        }
//                        else
//                        {
//                            qDebug() << "Not present in : " << windowTitle << "\n";
//                        }
//                        //SensitivityModule::Get().mMapWinInfo.insert(std::pair{hwnd, temp});
//                    }
//                }
//            }
//        }
//    }
//    return TRUE;
//}
std::vector<winData> tempList;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    RECT windowRect;
    bool secondary = *reinterpret_cast<bool*>(lParam);
    if (IsWindowVisible(hwnd))
    {
        char windowTitle[256];
        GetWindowRect(hwnd, &windowRect);
        GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
        if (windowTitle[0] != '\0'
            && strncmp(windowTitle, "Settings", sizeof(windowTitle)) != 0
            && strncmp(windowTitle, "Program Manager", sizeof(windowTitle)) != 0)
        {
            HMONITOR hMonitor = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
            MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
            WINDOWPLACEMENT wp = { sizeof(WINDOWPLACEMENT) };
            GetWindowPlacement(hwnd, &wp);
            if (GetMonitorInfo(hMonitor, &monitorInfo) && (wp.showCmd == 1 || wp.showCmd == 3))
            {
                winData temp;
                if (monitorInfo.dwFlags & MONITORINFOF_PRIMARY)
                {
                    if (!secondary)
                    {
                        temp.hwnd = hwnd;
                        strcpy_s(temp.title, windowTitle);
                        temp.showCmd = wp.showCmd;
                        temp.left = windowRect.left;
                        temp.right = windowRect.right;
                        temp.top = windowRect.top;
                        temp.bottom = windowRect.bottom;
                        tempList.push_back(temp);
                        //if (!ocrData::getCurr()->present(hwnd))
                        //{
                        //    ocrData::getCurr()->association.push_back(std::make_shared<winAssociation>(temp));
                        //}
                        //else
                        //{
                        //    qDebug() << "Not present in : " << windowTitle << "\n";
                        //}
                        //SensitivityModule::Get().mMapWinInfo.insert(std::pair{hwnd, temp});
                    }
                    return TRUE;
                }

                if (windowRect.left >= monitorInfo.rcMonitor.left &&
                    windowRect.top >= monitorInfo.rcMonitor.top &&
                    windowRect.right <= monitorInfo.rcMonitor.right &&
                    windowRect.bottom <= monitorInfo.rcMonitor.bottom)
                {
                    if (secondary)
                    {
                        temp.hwnd = hwnd;
                        strcpy_s(temp.title, windowTitle);
                        temp.showCmd = wp.showCmd;
                        temp.left = windowRect.left;
                        temp.right = windowRect.right;
                        temp.top = windowRect.top;
                        temp.bottom = windowRect.bottom;
                        tempList.push_back(temp);
                        //if (!ocrData::getCurr()->present(hwnd))
                        //{
                        //    ocrData::getCurr()->association.push_back(std::make_shared<winAssociation>(temp));
                        //}
                        //else
                        //{
                        //    qDebug() << "Not present in : " << windowTitle << "\n";
                        //}
                        //SensitivityModule::Get().mMapWinInfo.insert(std::pair{hwnd, temp});
                    }
                }
            }
        }
    }
    return TRUE;
}
std::vector<winData> SensitivityModule::getWinList(bool prev, bool secondary)
{
    tempList.clear();
    if (prev)
    {
        EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&secondary));
        return tempList;
    }
    else
    {
        EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&secondary));
        return tempList;
    }
}




void SensitivityModule::update(bool& secondary)
{
    mReady = false;
    mMapBoxInfo.clear();
	updateWinInfo(secondary);

    qDebug() << "Update : Win info map size : " << mMapWinInfo.size() << "\n";

}
void SensitivityModule::fillAndClassify(bool& secondary, std::vector<QRect>& boxes)
{
    mutex.lock();
    mPrevMapWinInfo.clear();
    for (auto it = mMapWinInfo.begin(); it != mMapWinInfo.end(); ++it)
    {
        mPrevMapWinInfo.insert(std::make_pair(it->first, it->second));
    }

    for (auto& box : boxes)
    {
        for (auto it = mMapWinInfo.begin(); it != mMapWinInfo.end(); ++it)
        {
            if (isBoxInWindow(box, it->second, secondary))
            {
                auto boxIt = mMapBoxInfo.find(it->first);
                if (boxIt == mMapBoxInfo.end())
                {
                    mMapBoxInfo[it->first] = { box };
                }
                else
                {
                    boxIt->second.push_back(box);
                }
                break;
            }
        }
    }

    qDebug() << "fillAndClassify : Map size : " << mMapWinInfo.size() << "\n";
    qDebug() << "fillAndClassify : Prev Map size : " << mPrevMapWinInfo.size() << "\n";
    qDebug() << "fillAndClassify : boxes size : " << boxes.size() << "\n";
    qDebug() << "fillAndClassify : boxe map size : " << mMapBoxInfo.size() << "\n";
    mutex.unlock();
}

void SensitivityModule::getList(bool secondary, std::vector<QRect>& boxes)
{
    mutex.lock();
    qDebug() << "getList : boxes size before : " << boxes.size() << "\n";
    updateRelative(secondary);
    makeList(boxes);
    mReady = true;
    qDebug() << "getList : Map size : " << mMapWinInfo.size() << "\n";
    qDebug() << "getList : Prev Map size : " << mPrevMapWinInfo.size() << "\n";
    qDebug() << "getList : boxes size : " << boxes.size() << "\n";
    qDebug() << "getList : boxe map size : " << mMapBoxInfo.size() << "\n";
    mutex.unlock();
}
void SensitivityModule::makeList(std::vector<QRect>& boxes)
{
    boxes.clear();
    for (auto it = mMapBoxInfo.begin(); it != mMapBoxInfo.end(); it++)
    {
        for (auto& box : it->second)
        {
            boxes.push_back(box);
        }
    }
}
event SensitivityModule::trackEvent(winData& prev, winData& curr)
{
    event ret;
    long prev_hdim = prev.right - prev.left;
    long prev_vdim = prev.bottom - prev.top;

    long curr_hdim = curr.right - curr.left;
    long curr_vdim = curr.bottom - curr.top;

    if (prev_hdim == curr_hdim && prev_vdim == curr_vdim)
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
        ret = UNKNOWN;
    }

    return ret;
}
bool SensitivityModule::updateRelative(bool& secondary)
{
    bool flag = false;
    for (auto it = mMapWinInfo.begin(); it != mMapWinInfo.end(); ++it)
    {
        auto boxWindowIt = mMapBoxInfo.find(it->first);
        if (boxWindowIt != mMapBoxInfo.end())
        {
            auto itPrevWin = mPrevMapWinInfo.find(it->first);
            if (itPrevWin != mPrevMapWinInfo.end())
            {
                winData prevWin = itPrevWin->second;
                if (trackEvent(prevWin, it->second) == MOVED)
                {
                    for (auto& box : boxWindowIt->second)
                    {
                        long dx = it->second.left - prevWin.left;
                        long dy = it->second.top - prevWin.top;
                        box.translate(dx, dy);
                        flag = true;
                    }
                }
            }
        }
    }
    return flag;
}


void SensitivityModule::updateWinInfo(bool& secondary)
{
    mMapWinInfo.clear();
    //EnumWindows(EnumWindowsProc, (LPARAM)&secondary);
}