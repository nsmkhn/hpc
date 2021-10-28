#pragma once
#include <cstdint>

#define INTERVALS_TAG "root.intervals"
#define INTERVALS_LEFT_TAG "left_bound"
#define INTERVALS_RIGHT_TAG "right_bound"

struct Interval
{
    Interval(int64_t lb, int64_t rb)
        : left_bound(lb), right_bound(rb)
    {
    }

    int64_t left_bound;
    int64_t right_bound;
};
