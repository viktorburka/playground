#ifndef WT_H
#define WT_H

namespace Wt {

template<typename T>
T boundary(T value, T min, T max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}

}

#endif
