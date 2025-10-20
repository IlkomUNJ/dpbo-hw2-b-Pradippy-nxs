#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <ctime>
using namespace std;

const time_t one_day = 86400;
const time_t one_week = 7 * one_day;

const time_t one_month = 30 * one_day;

namespace TimeUtil
{

    inline bool isLastKDays(time_t timestamp, int k)
    {
        time_t now = time(0);
        return difftime(now, timestamp) <= (k * one_day);
    }

    inline bool isToday(time_t timestamp)
    {
        return isLastKDays(timestamp, 1);
    }

    inline bool isLastWeek(time_t timestamp)
    {
        return isLastKDays(timestamp, 7);
    }

    inline bool isLastMonth(time_t timestamp)
    {
        return isLastKDays(timestamp, 30);
    }

    inline string a_time_t_to_string(time_t timestamp)
    {
        char buffer[20];
        strftime(buffer, 20, "%Y-%m-%d", localtime(&timestamp));
        return string(buffer);
    }
}

#endif