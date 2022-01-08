#ifndef STACK_H
#define STACK_H

class stack
{
    private:
        size_t _n;
    public:
        template< typename T >
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

#endif


    // empty : Test whether container is empty 
    // size : Return size
    // top : Access next element
    // push_back
    // pop_back
    // push : Insert element
    // pop : Remove top element 
    // back
    // push_back
    // pop_back
