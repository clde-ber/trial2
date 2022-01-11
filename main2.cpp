#include <vector>
#include <iostream>
#include <algorithm>
void printVector(int it)
{
    std::cout << it << std::endl;
}

int main( void )
{
    std::vector< int > vecteur1;
    std::vector< char > vecteur2;
    std::vector< char * > vecteur3;

    vecteur1.push_back(0);
    vecteur1.push_back(5);
    vecteur1.push_back(10);
    vecteur1.push_back(15);
    vecteur1.push_back(20);
    for_each(vecteur1.begin(), vecteur1.end(), printVector);
    vecteur2.push_back(10);
    vecteur2.push_back(15);
    vecteur2.push_back(20);
    for_each(vecteur2.begin(), vecteur2.end(), printVector);
    std::cout << vecteur1.size() << std::endl;
    std::cout << vecteur1.capacity() << std::endl;
    std::cout << vecteur2.size() << std::endl;
    std::cout << vecteur2.capacity() << std::endl;
    std::cout << sizeof(int) << std::endl;
    return 0;
}