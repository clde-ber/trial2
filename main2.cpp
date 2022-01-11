#include <vector>
#include <iostream>
#include <algorithm>
void printVector(int it)
{
    std::cout << it << std::endl;
}

size_t ft_pow(size_t n, size_t pow)
{
    size_t i = 0;
    size_t res = 1;

    while (i < pow)
    {
        res = res * n;
        i++;
    }
    return res;
}


int main( void )
{
    std::vector< int > vecteur1;
    std::vector< char > vecteur2;
    std::vector< char * > vecteur3;
    size_t res = 0;

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
    std::cout << sizeof(char) << std::endl;
    //res = (ft_pow(2, 32) / sizeof(int)) - (size_t)1;
    res = (ft_pow(2, 32) / sizeof(int)) * ft_pow(2, 32) - 1;
    size_t res2 = (ft_pow(2, 64) / sizeof(char)) - (size_t)1;
    std::cout << res << std::endl;
    std::cout << res2 << std::endl;
    std::cout << vecteur2.max_size() << std::endl;
    std::cout << vecteur1.max_size() << std::endl;
    return 0;
}