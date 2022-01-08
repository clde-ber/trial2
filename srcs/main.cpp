#include "Containers.hpp"

int main( void )
{
    int n = 10;
    int k = 1;
    try
    {
        ft::stack< int > stack1(5);
        for (int i = 0; i < 5; i++)
            stack1[i] = k++;
        ft::stack< int > stack2(stack1);
        for(int i = 0; i < 5; i++)
            std::cout << stack2[i] << std::endl;
        std::cout << "**********" << std::endl;
        for (int i = 0; i < 5; i++)
            stack2[i] += n;
        stack1 = stack2;
        for(int i = 0; i < 5; i++)
            std::cout << stack1[i] << std::endl;
        std::cout << "**********" << std::endl;
        std::cout << stack1.empty() << std::endl;
        std::cout << "**********" << std::endl;
        std::cout << stack1.size() << std::endl;
        std::cout << "**********" << std::endl;
        ft::stack< int > stackempty;
        std::cout << stack1.top() << std::endl;
        //std::cout << "**********" << std::endl;
        //std::cout << stackempty.top() << std::endl;
        std::cout << "**********" << std::endl;
        stack1.push(16);
        for(int i = 0; i < 6; i++)
            std::cout << stack1[i] << std::endl;
        std::cout << "**********" << std::endl;
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
        for(int i = 0; i < 1; i++)
            std::cout << stackempty[i] << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return FALSE;
}