#include "Containers.hpp"

int main( void )
{
    try
    {
        ft::stack< int > stack1(5);
        for (int i = 0; i < 5; i++)
            stack1[i] = 3;
        ft::stack< int > stack2(stack1);
        for(int i = 0; i < 5; i++)
            std::cout << stack2[i] << std::endl;
        std::cout << "**********" << std::endl;
        for (int i = 0; i < 5; i++)
            stack2[i] = 5;
        stack1 = stack2;
        for(int i = 0; i < 5; i++)
            std::cout << stack1[i] << std::endl;
        std::cout << "**********" << std::endl;
        std::cout << stack1.empty() << std::endl;
        std::cout << "**********" << std::endl;
        std::cout << stack1.size() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return FALSE;
}