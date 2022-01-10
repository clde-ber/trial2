#include "Stack.hpp"
#include "Vector.hpp"

void printVector(char it)
{
    std::cout << it << std::endl;
}

int main( void )
{
    unsigned long n = 10;
    unsigned long k = 1;
    unsigned long size = 5;

    std::cout << "*** stack ***" << std::endl;
    try
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
    }
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
        for (unsigned long i = 0; i < vectorCopy.size(); i++)
            vectorCopy[i] = 'a';
        for (unsigned long i = 0; i < vectorCopy.size(); i++)
            std::cout << vectorCopy[i] << std::endl;
        std::cout << "*************" << std::endl;
        for (unsigned long i = 0; i < vectorAssign.size(); i++)
            vectorAssign[i] = 'b';
        for (unsigned long i = 0; i < vectorAssign.size(); i++)
            std::cout << vectorAssign[i] << std::endl;
        std::for_each(vectorAssign.begin(), vectorAssign.end(), printVector);
        std::cout << "*************" << std::endl;
        std::cout << vectorCopy.size() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << vectorCopy.empty() << std::endl;
        vectorAssign.push_back('x');
        vectorCopy.push_back('y');
        std::cout << "*************" << std::endl;
        std::for_each(vectorAssign.rend(), vectorAssign.rbegin(), printVector);
        std::cout << "*************" << std::endl;
        std::for_each(vectorCopy.rend(), vectorCopy.rbegin(), printVector);
        std::cout << "*************" << std::endl;
        std::cout << vectorAssign.back() << std::endl;
        std::cout << "*************" << std::endl;
        std::cout << vectorCopy.back() << std::endl;
        vectorAssign.pop_back();
        vectorCopy.pop_back();
        std::cout << "*************" << std::endl;
        std::for_each(vectorAssign.rend(), vectorAssign.rbegin(), printVector);
        std::cout << "*************" << std::endl;
        std::for_each(vectorCopy.rend(), vectorCopy.rbegin(), printVector);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}