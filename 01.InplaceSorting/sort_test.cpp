#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

// А вот тут collvalue.h не надо, берите просто инты
#include "sorting.h"


TEST(BubbleSortTest, SortsEmptyVector)
{
    std::vector<int> data;
    bubble_sort(data.begin(), data.end());
    EXPECT_TRUE(data.empty());
}

TEST(BubbleSortTest, SortsSingleElement)
{
    std::vector<int> data = {7};
    bubble_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({7}));
}

TEST(BubbleSortTest, SortsAlreadySorted)
{
    std::vector<int> data = {1, 2, 3, 4, 5};
    bubble_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({1, 2, 3, 4, 5}));
}

TEST(BubbleSortTest, SortsReverseSorted)
{
    std::vector<int> data = {5, 4, 3, 2, 1};
    bubble_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({1, 2, 3, 4, 5}));
}

TEST(BubbleSortTest, SortsWithDuplicates)
{
    std::vector<int> data = {8, 9, 4, 4, 7, 1, 1};
    bubble_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({1, 1, 4, 4, 7, 8, 9}));
}

TEST(BubbleSortTest, SortsNegativeNumbers)
{
    std::vector<int> data = {0, -1, 7, -1, 3};
    bubble_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({-1, -1, 0, 3, 7}));
}

TEST(QuickSortTest, SortsEmptyVector)
{
    std::vector<int> data;
    quick_sort(data.begin(), data.end());
    EXPECT_TRUE(data.empty());
}

TEST(QuickSortTest, SortsSingleElement)
{
    std::vector<int> data = {7};
    quick_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({7}));
}

TEST(QuickSortTest, SortsAlreadySorted)
{
    std::vector<int> data = {1, 2, 3, 4, 5};
    quick_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({1, 2, 3, 4, 5}));
}

TEST(QuickSortTest, SortsReverseSorted)
{
    std::vector<int> data = {5, 4, 3, 2, 1};
    quick_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({1, 2, 3, 4, 5}));
}

TEST(QuickSortTest, SortsWithDuplicates)
{
    std::vector<int> data = {8, 9, 4, 4, 7, 1, 1};
    quick_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({1, 1, 4, 4, 7, 8, 9}));
}

TEST(QuickSortTest, SortsNegativeNumbers)
{
    std::vector<int> data = {0, -1, 7, -1, 3};
    quick_sort(data.begin(), data.end());
    EXPECT_EQ(data, std::vector<int>({-1, -1, 0, 3, 7}));
}