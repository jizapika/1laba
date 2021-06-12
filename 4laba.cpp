#include<vector>
#include<iostream>

#define pii pair<int,int>
#define vi vector<int>
#define f first
#define s second
#define pb push_back
using namespace std;

template <typename InputIterator, typename UnaryPredicate>
bool my_all_of(InputIterator it_begin, InputIterator it_end, UnaryPredicate func)
{
    for(; it_begin != it_end; it_begin++) if(!func(*it_begin)) return false;
    return true;
}

template <typename InputIterator, typename UnaryPredicate>
bool my_any_of(InputIterator it_begin, InputIterator it_end, UnaryPredicate func)
{
    for(; it_begin != it_end; it_begin++) if(func(*it_begin)) return true;
    return false;
}

template <typename InputIterator, typename UnaryPredicate>
bool my_none_of(InputIterator it_begin, InputIterator it_end, UnaryPredicate func)
{
    return !my_any_of(it_begin, it_end, func);
}

template <typename InputIterator, typename UnaryPredicate>
bool one_of(InputIterator it_begin, InputIterator it_end, UnaryPredicate func)
{
    int sum = 0;
    for(; it_begin != it_end; it_begin++) if(func(*it_begin)) sum++;
    if(sum == 1) return true;
    return false;
}

template <typename InputIterator, typename BinaryPredicate>
bool my_is_sorted(InputIterator it_begin, InputIterator it_end, BinaryPredicate func)
{
    if(it_begin == it_end) return true;
    InputIterator prev = it_begin;
    it_begin++;
    for(; it_begin != it_end; it_begin++)
    {
        if(!func(*it_begin, *prev)) return false;
        prev = it_begin;
    }
    return true;
}

template <typename InputIterator, typename UnaryPredicate>
bool my_is_partitioned(InputIterator it_begin, InputIterator it_end, UnaryPredicate func)
{
    if(it_begin == it_end) return true;
    InputIterator prev = it_begin;
    it_begin++;
    int sum = 0;
    for(; it_begin != it_end; it_begin++)
    {
        if(!func(*it_begin) && func(*prev) || func(*it_begin) && !func(*prev)) sum++;
        prev = *it_begin;
    }
    if(sum <= 1) return true;
    else return false;
}

template <typename InputIterator, typename object>
InputIterator my_find_not(InputIterator it_begin, InputIterator it_end, object equal)
{
    for(; it_begin != it_end; it_begin++)
    {
        if(*it_begin == equal) break;
    }
    return it_begin;
}

template <typename InputIterator, typename object>
InputIterator my_find_backward(InputIterator it_begin, InputIterator it_end, object equal)
{
    InputIterator ans = it_begin;
    for(; it_begin != it_end;)
    {
        it_begin++;
        if(*it_begin == equal) ans = it_begin;
    }
    return ans;
}

template <typename BidirectionalIterator>
bool my_is_palindrome(BidirectionalIterator it_begin, BidirectionalIterator it_end)
{
    while(it_begin != it_end)
    {
        it_end--;
        if(*it_begin != *it_end) return false;
        if(it_begin == it_end) return true;
        it_begin++;
    }
    return true;
}

template <typename T>
class cmp
{
public:
    bool operator() (T a, T b) {return a > b;}
};

template <typename T>
class segment
{
private:
    T first;
    T last;
public:
    explicit segment(T f, T l) : first(f), last(l) {};
    bool operator() (T a) {return a >= first && a <= last;}
};

int main()
{
    vector<int> v = {1, 2, 3, 4, 3, 2, 1};
    cout << "all_of: " << endl;
    cout << my_all_of(v.begin(), v.end(), segment<int>(1, 4)) << endl;
    cout << my_all_of(v.begin(), v.end(), segment<int>(1, 3)) << endl;
    cout << "is_sorted: " << endl;
    cout << my_is_sorted(v.begin(), v.end(), cmp<int>()) << endl;
    cout << my_is_sorted(v.begin(), v.end() - 3, cmp<int>()) << endl;
    cout << "find_backward: " << endl;
    cout << *my_find_backward(v.begin() + 1, v.end() - 2, 1) << endl;
    cout << "find_not: " << endl;
    cout << *my_find_not(v.begin() + 1, v.end() - 2, 2) << endl;
    cout << "is_palindrome: " << endl;
    cout << my_is_palindrome(v.begin(), v.end()) << endl;
}
