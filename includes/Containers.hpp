#ifndef CONTAINER_H
#define CONTAINER_H

#include "Stack.hpp"
#include "Vector.hpp"
#include "Map.hpp"

#include <iostream>
#include <string>
#include <memory>

namespace ft
{
    template< typename T >
    class stack< T >
    {
        public:
            stack( void )
            {
                std::allocator< T > alloc;

                alloc.allocate(0, T);
            }
            template< typename T >
            stack( const stack & rhs )
            {
                *this = rhs;
            }
            template< typename T >
            stack & operator=( stack const & rhs )
            {
                std::allocator< T > alloc;
                return new (this) stack(rhs);
            }
            template< typename T >
            ~stack( void )
            {
                std::allocator< T > alloc;
                alloc.deallocate(this, size());
            }
    };
    class Vector;
    class Map;
}

#endif