#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <Windows.h>

const std::string dataFile = "data.txt";  // 数据文件的路径
std::vector<std::string> lines;  // 存储所有行的向量
std::random_device rd;
std::mt19937 generator(rd());
std::uniform_int_distribution<int> distribution;

void loadLinesFromFile()
{
    std::ifstream file(dataFile);
    if (file)
    {
        lines.clear();
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
}

void copyRandomLineToClipboard()
{
    if (lines.empty())
    {
        std::cout << "数据文件为空." << std::endl;
        return;
    }

    int randomIndex = distribution(generator);
    std::string randomLine = lines[randomIndex];

    // 将数据转换为 UTF-8 编码
    int utf8Size = MultiByteToWideChar(CP_UTF8, 0, randomLine.c_str(), -1, nullptr, 0);
    if (utf8Size > 0)
    {
        std::vector<wchar_t> utf8Buffer(utf8Size);
        MultiByteToWideChar(CP_UTF8, 0, randomLine.c_str(), -1, utf8Buffer.data(), utf8Size);

        // 复制到剪贴板
        if (OpenClipboard(nullptr))
        {
            EmptyClipboard();
            HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, utf8Size * sizeof(wchar_t));
            if (hClipboardData != nullptr)
            {
                wchar_t* pszData = static_cast<wchar_t*>(GlobalLock(hClipboardData));
                if (pszData != nullptr)
                {
                    memcpy(pszData, utf8Buffer.data(), utf8Size * sizeof(wchar_t));
                    GlobalUnlock(hClipboardData);
                    SetClipboardData(CF_UNICODETEXT, hClipboardData);
                }
            }
            CloseClipboard();
        }
    }

    std::cout << "已复制随机行到剪贴板: " << randomLine << std::endl;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "按下 F2 键选择一行复制到剪贴板，按下 F10 键退出..." << std::endl;

    loadLinesFromFile();
    distribution = std::uniform_int_distribution<int>(0, lines.size() - 1);

    while (true)
    {
        if (GetAsyncKeyState(VK_F2) & 0x8000)
        {
            copyRandomLineToClipboard();
            Sleep(200);  // 等待一段时间以避免连续复制
        }

        if (GetAsyncKeyState(VK_F10) & 0x8000)
        {
            break;
        }
    }

    return 0;
}