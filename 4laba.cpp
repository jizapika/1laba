#include<bits/stdc++.h>
#include<string>
#include<iostream>

#define pii pair<int,int>
#define vi vector<int>
#define f first
#define s second
#define pb push_back
using namespace std;

template <typename iterator, typename predicate>
bool all_of(iterator it_begin, iterator it_end, predicate func)
{
    for(; it_begin != it_end; it_begin++) if(!func(*it_begin)) return false;
    return true;
}

template <typename iterator, typename predicate>
bool any_of(iterator it_begin, iterator it_end, predicate func)
{
    for(; it_begin != it_end; it_begin++) if(func(*it_begin)) return true;
    return false;
}

template <typename iterator, typename predicate>
bool none_of(iterator it_begin, iterator it_end, predicate func)
{
    return !any_of(it_begin, it_end, func);
}

template <typename iterator, typename predicate>
bool one_of(iterator it_begin, iterator it_end, predicate func)
{
    int sum = 0;
    for(; it_begin != it_end; it_begin++) if(func(*it_begin)) sum++;
    if(sum == 1) return true;
    return false;
}

template <typename iterator, typename predicate>
bool is_sorted(iterator it_begin, iterator it_end, predicate func)
{
    iterator prev = it_begin;
    it_begin++;
    for(; it_begin != it_end; it_begin++)
    {
        if(!func(*it_begin, *prev)) return false;
        prev = it_begin;
    }
    return true;
}

template <typename iterator, typename predicate>
bool is_partitioned(iterator it_begin, iterator it_end, predicate func)
{
    iterator prev = it_begin;
    it_begin++;
    int sum = 0;
    for(; it_begin != it_end; it_begin++)
    {
        if(!func(*it_begin) && func(*prev) || func(*it_begin) && !func(*prev)) sum++;
        prev = it_begin;
    }
    if(sum <= 1) return true;
    else return false;
}

template <typename iterator, typename object>
iterator find_not(iterator it_begin, iterator it_end, object equal)
{
    for(; it_begin != it_end; it_begin++)
    {
        if(*it_begin != equal) break;
    }
    return it_begin;
}

template <typename iterator, typename object>
iterator find_backward(iterator it_begin, iterator it_end, object equal)
{
    for(; it_end != it_begin; it_end--)
    {
        if(*it_end != equal) break;
    }
    return it_end;
}

template <typename iterator, typename predicate>
bool is_palindrome(iterator it_begin, iterator it_end, predicate func)
{
    while(it_begin != it_end)
    {
        if(!func(*it_begin, *it_end)) return false;
        it_begin++;
        if(it_begin == it_end) return true;
        it_end--;
    }
    return true;
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 3, 2, 1};
    cout << is_palindrome(v.begin(), v.end())
}
