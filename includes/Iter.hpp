#ifndef ITER_H
#define ITER_H

namespace ft
{
    template< typename T >
    class iter
    {
        T* p;
        public:
            iter(int* x) :p(x) {}
            iter(const iter& mit) : p(mit.p) {}
            iter& operator++() {++p;return *this;}
            iter operator++(int) {iter tmp(*this); operator++(); return tmp;}
            iter& operator+(int x) {return this + x;}
            bool operator==(const iter& rhs) const {return p==rhs.p;}
            bool operator!=(const iter& rhs) const {return p!=rhs.p;}
            int& operator*() {return *p;}
    };
}

#endif