#include <iostream>
#include <stdlib.h>
#include <vector>
#include "list.h"

template <typename T>
bool cmp(const T *ar, long size, list<T> &list)
{
    long lsize = list.get_size();
    bool res = (lsize == size);
    long i = 0;
    for (auto elem : list)
    {
        if (!res)
            return res;
        res = (elem == ar[i++]);
    }

    return res;
}

void test_default_constructor()
{
    std::cout << "TEST DEFAULT CONSTRUCTOR" << std::endl;
    try
    {
        long *ar = nullptr;
        long size = 0;
        list<long> l;
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_constructor_with_init_list()
{
    std::cout << "TEST CONSTRUCTOR WITH INITIALIZER LIST" << std::endl;
    try
    {
        long ar[5] = {1, 2, 3, 4, 5};
        long size = 5;
        list<long> l {1, 2, 3, 4, 5};
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_constructor_with_array()
{
    std::cout << "TEST CONSTRUCTOR WITH ARRAY" << std::endl;
    try
    {
        long ar[5] = {1, 2, 3, 4, 5};
        long size = 5;
        list<long> l(ar, size);
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_constructor_with_iterator()
{
    std::cout << "TEST CONSTRUCTOR WITH ITERATORS" << std::endl;
    try
    {

        long ar[5] = {1, 2, 3, 4, 5};
        long size = 5;
        list<long> ltemp {1, 2, 3, 4, 5};
        std::vector<long> vec {1, 2, 3, 4, 5};
        list<long> l(vec.begin(), vec.end());
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_copy_constructor()
{
    std::cout << "TEST COPY CONSTRUCTOR" << std::endl;
    try
    {
        long ar[5] = {1, 2, 3, 4, 5};
        long size = 5;
        list<long> l(ar, size);
        list<long> l1(l);
        bool test = cmp<long>(ar, size, l1);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_pop_front()
{
    std::cout << "TEST POP FRONT" << std::endl;
    try
    {
        long ar[4] = {2, 3, 4, 5};
        long size = 4;
        list<long> l {1, 2, 3, 4, 5};
        l.pop_front();
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_pop_back()
{
    std::cout << "TEST POP BACK" << std::endl;
    try
    {
        long ar[4] = {1, 2, 3, 4};
        long size = 4;
        list<long> l {1, 2, 3, 4, 5};
        l.pop_back();
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_push_front()
{
    std::cout << "TEST PUSH FRONT" << std::endl;
    try
    {
        long ar[6] = {0, 1, 2, 3, 4, 5};
        long size = 6;
        list<long> l {1, 2, 3, 4, 5};
        l.push_front(0);
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_push_back()
{
    std::cout << "TEST PUSH BACK" << std::endl;
    try
    {
        long ar[6] = {1, 2, 3, 4, 5, 6};
        long size = 6;
        list<long> l {1, 2, 3, 4, 5};
        l.push_back(6);
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_push_list_front()
{
    std::cout << "TEST PUSH LIST FRONT" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        long size = 10;
        list<long> l1 {1, 2, 3, 4, 5};
        list<long> l2 {6, 7, 8, 9, 10};
        l2.push_front(l1);
        bool test = cmp<long>(ar, size, l2);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_push_list_back()
{
    std::cout << "TEST PUSH LIST BACK" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        long size = 10;
        list<long> l1 {1, 2, 3, 4, 5};
        list<long> l2 {6, 7, 8, 9, 10};
        l1.push_back(l2);
        bool test = cmp<long>(ar, size, l1);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_insert()
{
    std::cout << "TEST INSERT" << std::endl;
    try
    {
        long ar[6] = {1, 2, 3, 4, 5, 6};
        long size = 6;
        list<long> l {1, 2, 4, 5, 6};
        list_iterator<long> it = l.begin() + (long) 2;
        l.insert(it, 3);
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_insert_with_iterators()
{
    std::cout << "TEST INSERT WITH ITERATORS" << std::endl;
    try
    {
        long ar[6] = {1, 2, 3, 4, 5, 6};
        long size = 6;
        list<long> l {1, 2, 6};
        list_iterator<long> it = l.begin() + (long) 2;
        std::vector<long> vec {3, 4, 5};
        l.insert(it, vec.begin(), vec.end());
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_insert_list()
{
    std::cout << "TEST INSERT LIST" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        long size = 10;
        list<long> l1 {1, 2, 3, 4, 10};
        list<long> l2 {5, 6, 7, 8, 9};
        list_iterator<long> it = l1.begin() + (long) 4;
        l1.insert(it, l2);
        bool test = cmp<long>(ar, size, l1);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_remove()
{
    std::cout << "TEST REMOVE" << std::endl;
    try
    {
        long ar[5] = {1, 2, 4, 5, 6};
        long size = 5;
        list<long> l {1, 2, 3, 4, 5, 6};
        list_iterator<long> it = l.begin() + (long) 2;
        l.remove(it);
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_remove_count()
{
    std::cout << "TEST REMOVE COUNT" << std::endl;
    try
    {
        long ar[3] = {1, 2, 6};
        long size = 3;
        list<long> l {1, 2, 3, 4, 5, 6};
        list_iterator<long> it = l.begin() + (long) 2;
        l.remove(it, 3);
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_reverse()
{
    std::cout << "TEST REVERSE" << std::endl;
    try
    {
        long ar[5] = {1, 2, 3, 4, 5};
        long size = 5;
        list<long> l {5, 4, 3, 2, 1};
        l.reverse();
        bool test = cmp<long>(ar, size, l);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_merge_list_elem()
{
    std::cout << "TEST MERGE LIST WITH ELEM" << std::endl;
    try
    {
        long ar[6] = {1, 2, 3, 4, 5, 6};
        long size = 6;
        list<long> l {1, 2, 3, 4, 5};
        bool test = cmp<long>(ar, size, l.merge(6));
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_merge_list_list()
{
    std::cout << "TEST MERGE LIST WITH LIST" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        long size = 10;
        list<long> l1 {1, 2, 3, 4, 5};
        list<long> l2 {6, 7, 8, 9, 10};
        bool test = cmp<long>(ar, size, l1.merge(l2));
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_list_plus_elem()
{
    std::cout << "TEST LIST PLUS ELEM" << std::endl;
    try
    {
        long ar[6] = {1, 2, 3, 4, 5, 6};
        long size = 6;
        list<long> l {1, 2, 3, 4, 5};
        list<long> l1 = l + (long) 6;
        bool test = cmp<long>(ar, size, l1);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

void test_list_plus_list()
{
    std::cout << "TEST LIST PLUS LIST" << std::endl;
    try
    {
        long ar[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        long size = 10;
        list<long> l1 {1, 2, 3, 4, 5};
        list<long> l2 {6, 7, 8, 9, 10};
        list<long> l3 = l1 + l2;
        bool test = cmp<long>(ar, size, l3);
        if (test)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    catch (list_exception &error)
    {
        std::cout << error.what() << std::endl;
    }
}

int main()
{
    test_default_constructor();
    test_constructor_with_init_list();
    test_constructor_with_array();
    test_constructor_with_iterator();
    test_copy_constructor();
    test_pop_front();
    test_pop_back();
    test_push_front();
    test_push_back();
    test_push_list_front();
    test_push_list_back();
    test_insert();
    test_insert_with_iterators();
    test_insert_list();
    test_remove();
    test_remove_count();
    test_reverse();
    test_merge_list_elem();
    test_merge_list_list();
    test_list_plus_elem();
    test_list_plus_list();

    return EXIT_SUCCESS;
}
