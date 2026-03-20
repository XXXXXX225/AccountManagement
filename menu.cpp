#define _CRT_SECURE_NO_WARNINGS

#include "menu.h"
#include "tool.h"
#include "card_service.h"
#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <limits>

using namespace std;

// 系统标题
void printTitle()
{
    cout << "=================================" << endl;
    cout << "      欢迎使用计费管理系统 v1.0       " << endl;
    cout << "=================================" << endl;
    cout << "===============菜单===============" << endl;
}

// 输出菜单选项
void outputMenu()
{
    cout << "1. 新增卡" << endl;
    cout << "2. 查询卡" << endl;
    cout << "3. 上机" << endl;
    cout << "4. 下机" << endl;
    cout << "5. 充值" << endl;
    cout << "6. 退费" << endl;
    cout << "7. 查询统计" << endl;
    cout << "8. 注销卡" << endl;
    cout << "0. 退出" << endl;
    cout << "-------------------------------" << endl;
}

// 根据选择显示对应的菜单名称
void showSelectedOption(int choice)
{
    string optionName = "";
    switch (choice)
    {
    case 1:
        optionName = "新增卡";
        break;
    case 2:
        optionName = "查询卡";
        break;
    case 3:
        optionName = "上机";
        break;
    case 4:
        optionName = "下机";
        break;
    case 5:
        optionName = "充值";
        break;
    case 6:
        optionName = "退费";
        break;
    case 7:
        optionName = "查询统计";
        break;
    case 8:
        optionName = "注销卡";
        break;
    case 0:
        optionName = "退出";
        break;
    default:
        optionName = "未知选择";
        break;
    }
    cout << ">> 您选择的菜单功能是: [" << optionName << "]" << endl;
}

// 获取用户选择并验证
int getUserChoice()
{
    int choice;
    while (true)
    {
        cout << "请选择菜单选项 (0-8): ";
        if (cin >> choice)
        {
            if (choice >= 0 && choice <= 8)
            {
                return choice;
            }
            else
            {
                cout << "选择的菜单选项范围错误，请重新输入!\n"
                     << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else
        {
            cout << "输入无效，请输入数字!\n"
                 << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// 模糊查询卡
void fuzzyQueryCard()
{
    char keyword[18];
    cout << "请输入卡号关键字: ";
    cin.ignore();
    cin.getline(keyword, 18);

    int count = 0;
    Card *result = queryCards(keyword, &count);

    cout << "=================================" << endl;
    cout << "模糊查询结果: " << endl;
    cout << "=================================" << endl;

    if (count == 0)
    {
        cout << "没有找到匹配的卡!" << endl;
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            cout << "卡号: " << result[i].aName << endl;
            cout << "状态: ";
            switch (result[i].nStatus)
            {
            case 0:
                cout << "未上机" << endl;
                break;
            case 1:
                cout << "正在上机" << endl;
                break;
            case 2:
                cout << "已注销" << endl;
                break;
            case 3:
                cout << "失效" << endl;
                break;
            }
            cout << "余额: " << result[i].fBalance << " 元" << endl;
            cout << "-------------------------------" << endl;
        }
        cout << "共找到 " << count << " 张匹配的卡" << endl;
        delete[] result; // 释放内存
    }
    cout << "=================================" << endl;
}

// 新增卡
void addCard()
{
    char cardNumber[18];
    char password[8];
    float balance;

    cout << "请输入卡号: " << endl;
    cout << "提示: 卡号长度不超过17位" << endl;
    cin.ignore();
    cin.getline(cardNumber, 18);
    cout << "请输入密码: " << endl;
    cout << "提示: 密码长度不超过7位" << endl;
    cin.getline(password, 8);
    cout << "请输入开卡金额: " << endl;
    cin >> balance;

    int result = addCard(cardNumber, password, balance);
    if (result == 0)
    {
        cout << "新增卡成功!" << endl;
    }
    else if (result == -1)
    {
        cout << "内存分配失败!" << endl;
    }
    else if (result == -2)
    {
        cout << "卡号已存在!" << endl;
    }
    else if (result == -3)
    {
        cout << "卡号或密码无效!" << endl;
    }
    else
    {
        cout << "新增卡失败!" << endl;
    }
}

// 查询卡
void queryCard()
{
    int queryType;
    cout << "请选择查询方式: " << endl;
    cout << "1. 精确查询(输入完整卡号)" << endl;
    cout << "2. 模糊查询(输入卡号关键字)" << endl;
    cout << "请选择: ";
    cin >> queryType;

    if (queryType == 1)
    {
        char cardNumber[18];
        cout << "请输入卡号: " << endl;
        cin.ignore();
        cin.getline(cardNumber, 18);

        Card *card = queryCard(cardNumber);
        if (card == nullptr)
        {
            cout << "卡不存在!" << endl;
            return;
        }

        cout << "=================================" << endl;
        cout << "卡号: " << card->aName << endl;
        cout << "卡状态: ";
        switch (card->nStatus)
        {
        case 0:
            cout << "未上机" << endl;
            break;
        case 1:
            cout << "正在上机" << endl;
            break;
        case 2:
            cout << "已注销" << endl;
            break;
        case 3:
            cout << "失效" << endl;
            break;
        }
        cout << "余额: " << card->fBalance << " 元" << endl;
        cout << "累计使用金额: " << card->fTotalUse << " 元" << endl;
        cout << "使用次数: " << card->nUseCount << endl;
        cout << "最后使用时间: " << formatTime(card->tLast) << endl;
        cout << "=================================" << endl;
    }
    else if (queryType == 2)
    {
        fuzzyQueryCard();
    }
    else
    {
        cout << "选择错误!" << endl;
    }
}

// 注销卡
void cancelCard()
{
    char cardNumber[18];
    cout << "请输入卡号: " << endl;
    cin.ignore();
    cin.getline(cardNumber, 18);

    int result = cancelCard(cardNumber);
    if (result == 0)
    {
        cout << "注销卡成功!" << endl;
    }
    else if (result == -1)
    {
        cout << "卡不存在!" << endl;
    }
    else if (result == -2)
    {
        cout << "卡正在使用中，无法注销!" << endl;
    }
    else
    {
        cout << "注销卡失败!" << endl;
    }
}

// 系统主循环
void startBillingSystem()
{
    // 初始化链表
    if (initCardList() != 0)
    {
        cout << "初始化卡管理系统失败!" << endl;
        return;
    }

    int choice = -1;
    while (true)
    {
        printTitle();
        outputMenu();
        choice = getUserChoice();

        // 验证选择范围
        if (choice < 0 || choice > 8)
        {
            cout << "选择的菜单选项范围错误\n"
                 << endl;
            continue;
        }

        showSelectedOption(choice);

        // 选择为 0 时退出循环
        if (choice == 0)
        {
            cout << ">> 系统即将退出，感谢使用!" << endl;
            break;
        }

        // 根据选择执行相应功能
        switch (choice)
        {
        case 1:
            addCard();
            break;
        case 2:
            queryCard();
            break;
        case 8:
            cancelCard();
            break;
        default:
            cout << "该功能暂未实现!" << endl;
            break;
        }

        // 暂停一下让用户看到结果，然后再显示菜单
        cout << "\n按回车键继续..." << endl;
        cin.ignore();
        cin.get();
        system("cls"); // 清屏
    }

    // 释放链表
    releaseCardList();
}
