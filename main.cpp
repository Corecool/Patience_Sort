#include <QtCore/QCoreApplication>

#include <vector>
#include <algorithm>
#include <stack>
#include <iterator>
#include <iostream>
using namespace std;

template<typename PileType>
bool pile_less(const PileType& x, const PileType& y)
{
    return x.top() < y.top();
}

// reverse less predicate to turn max-heap into min-heap
template<typename PileType>
bool pile_more(const PileType& x, const PileType& y)
{
    return pile_less(y, x);
}

template<typename Iterator>
void patience_sort(Iterator begin, Iterator end)
{
    typedef typename std::iterator_traits<Iterator>::value_type DataType;
    typedef std::stack<DataType> PileType;
    std::vector<PileType> piles;

    for (Iterator it = begin; it != end; it++)
    {
        PileType new_pile;
        new_pile.push(*it);
        typename std::vector<PileType>::iterator insert_it =
            std::lower_bound(piles.begin(), piles.end(), new_pile,
                             pile_less<PileType>);
        if (insert_it == piles.end())
            piles.push_back(new_pile);
        else
            insert_it->push(*it);
    }
    // sorted array already satisfies heap property for min-heap

    for (Iterator it = begin; it != end; it++)
    {
        std::pop_heap(piles.begin(), piles.end(), pile_more<PileType>);
        *it = piles.back().top();
        piles.back().pop();
        if (piles.back().empty())
            piles.pop_back();
        else
            std::push_heap(piles.begin(), piles.end(), pile_more<PileType>);
    }
}

int main(int argc, char *argv[])
{
    int arr[] = {7, 2, 3, 1, 5, 8, 9, 6};
    patience_sort(arr,arr + sizeof(arr) / sizeof(int));
    copy(arr,arr + sizeof(arr) / sizeof(int),ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}
