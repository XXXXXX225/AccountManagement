#include <iostream>
#include <windows.h>
#include "menu.h"

using namespace std;

int main()
{
    // 设置控制台输出为UTF-8编码
    SetConsoleOutputCP(CP_UTF8);

    // 启动计费管理系统
    startBillingSystem();
    return 0;
}
