#include "orderfile.h"

orderfile::orderfile()
{
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "预约文件打开失败！" << endl;
        return;
    }

    // 读取顺序：严格匹配 student.cpp 的写入顺序（日期→时间段→机房编号→学生学号→学生姓名→审核状态）
    string dateStr, timeStr, roomIdStr, stuIdStr, stuNameStr, stateStr;

    while (ifs >> dateStr >> timeStr >> roomIdStr >> stuIdStr >> stuNameStr >> stateStr)
    {
        map<string, string> tempMap;
        size_t pos = 0;

        // 1. 解析日期（用 dateStr 找冒号）
		pos = dateStr.find(":");
        if (pos != -1)
        {
            string key = dateStr.substr(0, pos);
            string value = dateStr.substr(pos + 1);
            tempMap["日期"] = value; // 直接赋值，确保插入成功
        }

        // 2. 解析时间段（用 timeStr 找冒号）
        pos = timeStr.find(":");
        if (pos != -1)
        {
            string key = timeStr.substr(0, pos);
            string value = timeStr.substr(pos + 1);
            tempMap["时间段"] = value;
        }

        // 3. 解析机房编号（用 roomIdStr 找冒号）
        pos = roomIdStr.find(":");
        if (pos != -1)
        {
            string key = roomIdStr.substr(0, pos);
            string value = roomIdStr.substr(pos + 1);
            tempMap["机房编号"] = value;
        }

        // 4. 解析学生学号（用 stuIdStr 找冒号，重点！）
        pos = stuIdStr.find(":");
        if (pos != -1)
        {
            string key = stuIdStr.substr(0, pos); // 键名：“学生学号”
            string value = stuIdStr.substr(pos + 1); // 值：学生学号（如“1”）
            tempMap["学生学号"] = value;
        }

        // 5. 解析学生姓名（用 stuNameStr 找冒号）
        pos = stuNameStr.find(":");
        if (pos != -1)
        {
            string key = stuNameStr.substr(0, pos);
            string value = stuNameStr.substr(pos + 1);
            tempMap["学生姓名"] = value;
        }

        // 6. 解析审核状态（用 stateStr 找冒号）
        pos = stateStr.find(":");
        if (pos != -1)
        {
            string key = stateStr.substr(0, pos);
            string value = stateStr.substr(pos + 1);
            tempMap["审核状态"] = value;
        }

        // 存入预约记录容器，记录数自增
        m_orderdata[m_size++] = tempMap;
    }

    ifs.close();
}

void orderfile::updateorder()
{
    if (m_size == 0)
    {
        return;
    }
    ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
    for (int i = 0; i < m_size; i++)
    {
        // 写入顺序与读取顺序一致，确保后续解析正常
        ofs << "日期:" << m_orderdata[i]["日期"]
            << "\t时间段:" << m_orderdata[i]["时间段"]
            << "\t机房编号:" << m_orderdata[i]["机房编号"]
            << "\t学生学号:" << m_orderdata[i]["学生学号"]
            << "\t学生姓名:" << m_orderdata[i]["学生姓名"]
            << "\t审核状态:" << m_orderdata[i]["审核状态"]
            << endl;
    }
    ofs.close();
}