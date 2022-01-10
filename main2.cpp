#include <vector>
#include <iostream>

int main( void )
{
    std::vector< int > vecteur1;
    std::vector< char > vecteur2;
    std::vector< char * > vecteur3;

    std::cout << vecteur1.max_size() << std::endl;
    std::cout << vecteur2.max_size() << std::endl;
    std::cout << vecteur3.max_size() << std::endl;
    return 0;
}