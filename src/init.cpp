#include "main.h"

#include "system/tsl/ordered_map.h"
#include "testconfig.hpp"
#include "userConfig/chicken.hpp"
#include <iostream>

// SystemData* sysData;
// Chassis* chassis;
// Generic* lift;
// Generic* intake;
// Generic* shoot;

void init()
{
    json j1 = json::parse(userConfig);
    //基于迭代器的rangFor
    for (auto it = j1["底盘"]["马达"].begin(); it != j1["底盘"]["马达"].end(); it++)
    {
        std::cout << it.key() << it.value()["端口"] << std::endl;
    }
    // ;
    for (auto &it : j1["底盘"]["马达"])
        std::cout << "= " << it["端口"] << std::endl;
    std::cout << "哈哈，登入啦！！1加1等于3" << std::endl;
    // std::cout << j1["底盘"]["马达"]["左前"].get<std::string>() << std::endl;

    // json j2 = {
    //     {"json版本号", 1.0},
    //     {"系统信息",
    //      {{"机型", "全能机"},
    //       {"队伍编号", "8982B"},
    //       {"用户名", "sheep"}}},
    //     {"底盘",
    //      {{"马达",
    //        {{"左前", {{"端口", 1}, {"正反", 0}, {"齿轮", 1}}}},
    //        {{"左后", {{"端口", 2}, {"正反", 1}, {"齿轮", 1}}}},
    //        {{"右前", {{"端口", 3}, {"正反", 1}, {"齿轮", 1}}}},
    //        {{"右后", {{"端口", 4}, {"正反", 0}, {"齿轮", 1}}}}},
    //       {"ADI",
    //        {{"陀螺仪", 1}}},
    //       {"参数",
    //        {{"陀螺仪", 1}}}}},

    //     {"object",
    //      {{"currency", "USD"},
    //       {"value", 42.99}}}};

    // std::cout << j2.dump(4) << std::endl;

    // tsl::ordered_map<std::string, int> m{{"陈老师", 100}, {"狗老鼠", 50}, {"大挂", 80}, {"薄薄", 60}};

    // for (auto &it : m)
    //     std::cout << it.first << " " << it.second << std::endl;
    // std::cout << m.find("大挂")->second << std::endl;
}