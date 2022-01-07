#include "Containers.hpp"

int main( void )
{
    ft::stack< int > stack1;
    ft::stack< int > stack2(stack1);
    stack2 = stack1;

    return 0;
}