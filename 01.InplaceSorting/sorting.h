#ifndef SORTING_H
#define SORTING_H

// Header-only

// Для swap
#include "collvalue.h"

#include <algorithm>
#include <iterator>


// ----------------------------- Пузырёк --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return;
    }

    for (Iterator last = end; last != begin; --last)
    {
        bool swapped = false;

        Iterator current = begin;
        Iterator next = current;
        ++next;

        for (; next != last; ++current, ++next)
        {
            if (*next < *current)
            {
                std::iter_swap(current, next);
                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }
}

// --------------------------- QuickSort ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    const auto size = std::distance(begin, end);
    if (size < 2)
    {
        return;
    }

    Iterator left = begin;
    Iterator right = end;
    --right;

    const auto pivot = *(begin + size / 2);

    while (left <= right)
    {
        while (*left < pivot)
        {
            ++left;
        }

        while (pivot < *right)
        {
            --right;
        }

        if (left <= right)
        {
            std::iter_swap(left, right);
            ++left;

            if (right == begin)
            {
                break;
            }
            --right;
        }
    }

    quick_sort(begin, right + 1);
    quick_sort(left, end);
}

#endif // SORTING_H
