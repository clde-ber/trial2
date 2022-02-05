#include "Stack.hpp"
#include "Vector.hpp"
#include "Map.hpp"
#include <algorithm>
#include <vector>
#include <list>
#include <map>

void printVector(char it)
{
    std::cout << it << std::endl;
}

void printFloat(float it)
{
    std::cout << it << std::endl;
}

void printInt(int it)
{
    std::cout << it << std::endl;
}

int main( void )
{
    //unsigned long n = 10;
    //unsigned long k = 1;
    unsigned long size = 5;

    std::cout << "*** stack ***" << std::endl;
   /* try
    {
        ft::stack< int > stack1(size);
        for (unsigned long i = 0; i < 5; i++)
            stack1[i] = k++;
        ft::stack< int > stack2(stack1);
        for(unsigned long i = 0; i < 5; i++)
            std::cout << stack2[i] << std::endl;
        std::cout << "*************" << std::endl;
        for (unsigned long i = 0; i < 5; i++)
            stack2[i] += n;
        stack1 = stack2;
        for(unsigned long i = 0; i < 5; i++)
            std::cout << stack1[i] << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << stack1.empty() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << stack1.size() << std::endl;
        std::cout << "*************" << std::endl;
        ft::stack< int > stackempty;
        std::cout << stack1.top() << std::endl;
        //std::cout << "**********" << std::endl;
        //std::cout << stackempty.top() << std::endl;
        std::cout << "*************" << std::endl;
        stack1.push(16);
        for(unsigned long i = 0; i < 6; i++)
            std::cout << stack1[i] << std::endl;
        std::cout << "*************" << std::endl;
        stackempty.push(1);
        //for(int i = 0; i < 1; i++)
            //std::cout << stackempty[i] << std::endl;
        //std::cout << "**********" << std::endl;
        stack1.pop();
        //for(int i = 0; i < 6; i++)
            //std::cout << stack1[i] << std::endl;
        //std::cout << "**********" << std::endl;
        stackempty.pop();
        stackempty.pop();
        for(unsigned long i = 0; i < 1; i++)
            std::cout << stackempty[i] << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }*/
    std::cout << "*** vector **" << std::endl;
   try
    {
        ft::vector< char > vector1(size);
        for (unsigned long i = 0; i < vector1.size(); i++)
            vector1[i] = '@';
        for (unsigned long i = 0; i < vector1.size(); i++)
            std::cout << vector1[i] << std::endl;

        ft::vector< char > vectorCopy(vector1);
        ft::vector< char > vectorAssign;
        vectorAssign = vector1;
        for (unsigned long i = 0; i < vectorCopy.capacity(); i++)
            vectorCopy[i] = 'a';
        for (unsigned long i = 0; i < vectorCopy.capacity(); i++)
            std::cout << vectorCopy[i] << std::endl;
        std::cout << "*************" << std::endl;
        for (unsigned long i = 0; i < vectorAssign.capacity(); i++)
            vectorAssign[i] = 'b';
        for (unsigned long i = 0; i < vectorAssign.capacity(); i++)
            std::cout << vectorAssign[i] << std::endl;
        std::for_each(vectorAssign.begin(), vectorAssign.end(), printVector);
        std::cout << "*************" << std::endl;
        std::cout << vectorCopy.size() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << vectorCopy.empty() << std::endl;
        vectorAssign.push_back('x');
        vectorCopy.push_back('y');
        std::cout << "*************" << std::endl;
        std::cout << vectorCopy.size() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << vectorAssign.size() << std::endl;
        std::cout << "*************" << std::endl;
        //std::cout << vectorAssign.at(5) << std::endl;
        //std::cout << "*************" << std::endl;
        std::cout << vectorCopy.at(5) << std::endl;
        std::cout << "*************" << std::endl;
        //std::for_each(vectorAssign.rend(), vectorAssign.rbegin(), printVector);
        std::cout << "*************" << std::endl;
        //std::for_each(vectorCopy.rend(), vectorCopy.rbegin(), printVector);
        std::cout << "*************" << std::endl;
        std::cout << vectorAssign.back() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << vectorCopy.back() << std::endl;
        vectorAssign.pop_back();
        vectorCopy.pop_back();
        std::cout << "*************" << std::endl;
       //std::for_each(vectorAssign.rend(), vectorAssign.rbegin(), printVector);
        std::cout << "*************" << std::endl;
        //std::for_each(vectorCopy.rend(), vectorCopy.rbegin(), printVector);
        std::cout << "*************" << std::endl;
        std::cout << vectorAssign.front() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << vectorCopy.front() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << *vectorAssign.data() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << *vectorCopy.data() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << vectorAssign.size() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << vectorAssign.capacity() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << vectorAssign.max_size() << std::endl;
        std::cout << "*************" << std::endl;
        ft::vector<int *> vectorNb(5);
        std::vector<int *> realVector(5);
        std::cout << vectorNb.max_size() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << realVector.max_size() << std::endl;
        std::cout << "*************" << std::endl;
        vectorAssign.resize(3, '0');
        std::for_each(vectorAssign.begin(), vectorAssign.end(), printVector);
        std::cout << "*************" << std::endl;
        vectorCopy.resize(15, '*');
        std::for_each(vectorCopy.begin(), vectorCopy.end(), printVector);
        std::cout << "*************" << std::endl;
        //vectorAssign.assign(vectorCopy.rend(), vectorCopy.rbegin());
        std::for_each(vectorAssign.begin(), vectorAssign.end(), printVector);
        std::cout << "*************" << std::endl;
        vectorCopy.assign(7, '$');
        std::for_each(vectorCopy.begin(), vectorCopy.end(), printVector);
        std::cout << "*************" << std::endl;
        vectorCopy.insert(vectorCopy.begin() + 3, '0');
        vectorCopy.insert(vectorCopy.begin() + 8, vectorAssign.begin(), vectorAssign.end());
        vectorCopy.insert(vectorCopy.begin() + 4, 3, '0');
        std::for_each(vectorCopy.begin(), vectorCopy.end(), printVector);
        std::cout << "*************" << std::endl;
        std::cout << *vectorCopy.erase(vectorCopy.begin() + 3, vectorCopy.begin() + 7) << std::endl;
        std::cout << "*************" << std::endl;
        std::for_each(vectorCopy.begin(), vectorCopy.end(), printVector);
        std::cout << "*************" << std::endl;
        std::cout << *vectorCopy.erase(vectorCopy.begin()) << std::endl;
        std::cout << "*************" << std::endl;
        std::for_each(vectorCopy.begin(), vectorCopy.end(), printVector);
        ft::vector< float > swapf;
        ft::vector< float > swapc;
        swapf.assign(5, 0.02f);
        swapc.assign(6, 0.15f);
        swapf.swap(swapc);
        ft::vector< int > int1;
        ft::vector< int > int2;
        int1.assign(5, 2);
        int2.assign(6, 5);
        std::cout << "*************" << std::endl;
        std::for_each(swapf.begin(), swapf.end(), printFloat);
        std::cout << "*************" << std::endl;
        std::for_each(swapc.begin(), swapc.end(), printFloat);
        swapc.clear();
        //std::cout << swapc.at(0) << std::endl;
        std::list< int > list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        ft::vector< int > listV(list.begin(), list.end());
        std::cout << "*************" << std::endl;
        std::for_each(listV.begin(), listV.end(), printInt);
        ft::map<int, int > maps;
        ft::Node< int, int > pair1(4, 80);
        ft::Node< int, int > pair2(7, 50);
        ft::map< int, int > mapp;
        ft::Node< int, int > pair3(5, 10);
        ft::Node< int, int > pair4(1, 20);
        ft::Node< int, int > pair5(2, 30);
        ft::Node< int, int > pair6(3, 40);
        mapp.insert(pair1);
        mapp.print();
        mapp.insert(pair3);
        mapp.print();
        mapp.insert(pair4);
        mapp.print();
        mapp.insert(pair5);
        mapp.print();
        mapp.insert(pair6);
        mapp.print();
        mapp.insert(mapp.begin()++, pair2);
        maps.print();
        maps.insert(mapp.begin(), mapp.end());
        maps.print();
        maps.erase(maps.begin(), maps.end());
        std::cout << "****" << std::endl;
        maps.print();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}