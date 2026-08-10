#include <iostream>
#include <string>
#include <memory>
#include <cmath>
#include <memory>

using namespace std;

namespace AdvanceCpp
{

    constexpr int DEFAULT_CAPACITY = 20;

    template <typename T>
    class DynamicArray
    {
    private:
        /*note: C++ initializes members in declaration order, not the order they appear in the initializer list*/
        int _size;
        int _capacity;
        unique_ptr<T[]> _p;

    public:
        /* default constructor */
        DynamicArray() : _size(0), _capacity(DEFAULT_CAPACITY), _p(make_unique<T[]>(DEFAULT_CAPACITY))
        {
        }
        /* parameterize constructors
        note: default to explicit for a constructor with 1 arg, otherwise it can cause issue as it allow object creation by assignment
            i.e. DynamicArray da = 5; // implicitly creates DynamicArray(5)
            problem: void myprocess(DynamicArray da) -> myprocess(5) // this will create DynamicArray with size as 5 and pass it in myprocess
            instead of giving an error or waring
        */

        explicit DynamicArray(const int sz) : _size(sz), _capacity(sz), _p(make_unique<T[]>(_capacity))
        {
        }

        DynamicArray(const int sz, const T val) : _size(sz), _capacity(sz), _p(make_unique<T[]>(_capacity))
        {
            for (int i = 0; i < _capacity; i++)
            {
                if (i >= _size)
                {
                    break;
                }
                _p[i] = val;
            }
        }

        /* copy constructor */
        DynamicArray(const DynamicArray &other) : _size(other._size), _capacity(other._capacity), _p(new T[_capacity])
        {
            for (int i = 0; i < _capacity; i++)
            {
                _p[i] = std::move(other._p[i]);
            }
        }

        /* copy assignment operator */
        DynamicArray &operator=(const DynamicArray &other)
        {
            if (this == &other)
                return *this;
            this->_size = other._size;
            this->_capacity = other._capacity;
            /*note: always delete the raw pointer before initializing*/
            this->_p = make_unique<T[]>(this->_capacity);
            for (int i = 0; i < this->_capacity; i++)
            {
                this->_p[i] = other._p[i];
            }
            return *this;
        }

        /* Move constructor
        && tell compiler that it's safe to steal the object as it's going to be deleted otherwise*/
        DynamicArray(DynamicArray &&other) noexcept : _size(other._size), _capacity(other._capacity), _p(std::move(other._p)) 
        {
            other._size = 0;
            other._capacity = 0;
        }

        /* Move Assignment */
        DynamicArray &operator=(DynamicArray &&other) noexcept
        {
            if (this == &other)
                return *this;
            this->_size = other._size;
            this->_capacity = other._capacity;
            this->_p = move(other._p);
            other._size = 0;
            other._capacity = 0;
            return *this;
        }

        void push_back(T val)
        {
            if (_size >= _capacity)
            {
                _capacity = _capacity * 2;
                unique_ptr<T[]> p = make_unique<T[]>(_capacity);
                for (int i = 0; i < _size; i++)
                {
                    p[i] = move(_p[i]);
                }
                _p = move(p);
            }
            _p[_size++] = val;
        }

        T pop_back()
        {
            if (_size == 0)
            {
                throw std::runtime_error("Invalid pop_back(): array is empty");
            }
            return _p[--_size];
        }

        bool empty() const
        {
            return _size == 0;
        }

        T at(int index) const
        {
            if (index < 0 || index >= _size)
            {
                throw std::out_of_range("Invalid at(): index out of bound");
            }
            return _p[index];
        }

        bool contains(T val) const
        {
            for (int i = 0; i < _size; i++)
            {
                if (_p[i] == val)
                    return true;
            }
            return false;
        }

        void clear()
        {
            _size = 0;
        }

        void reserve(int space)
        {
            if (_capacity >= space)
                return;
            unique_ptr<T[]> p = make_unique<T[]>(space);
            for (int i = 0; i < _size; i++)
            {
                p[i] = move(_p[i]);
            }
            _capacity = space;
            _p = move(p);
        }

        int size() const
        {
            return _size;
        }

        int capacity() const
        {
            return _capacity;
        }

        /*note: [] operator needs a value i.e. index*/
        const T &operator[](const int index) const
        {
            if (index < 0 || index >= _size)
            {
                throw std::out_of_range("invalid [] operation " + std::to_string(index) + "out of bound");
            }
            return _p[index];
        }

        T &operator[](const int index)
        {
            if (index < 0 || index >= _size)
            {
                throw std::out_of_range("invalid [] operation " + std::to_string(index) + "out of bound");
            }
            return _p[index];
        }

        T *begin()
        {
            return _p.get();
        }

        const T *cbegin() const
        {
            return _p.get();
        }

        T *end()
        {
            return _p.get() + _size;
        }

        const T *cend() const
        {
            return _p.get() + _size;
        }

        void reverse()
        {
            auto *left = _p.get();
            auto *right = _p.get() + _size - 1;
            while (left < right)
            {
                std::swap(*left, *right);
                left++;
                right--;
            }
        }

        void rotate(int k)
        {
            /*no element*/
            if (_size == 0)
                return;

            int newK = k % _size;
            /*if k is neg % newK will be neg*/
            if (newK < 0)
                newK += _size;
            /*if k is zero: early return as it's result in current order*/
            if (newK == 0)
                return;

            const auto swapInRange = [&](T *left, T *right)
            {
                while (left < right)
                {
                    std::swap(*left, *right);
                    left++;
                    right--;
                }
            };
            /* reverse left partition [0, newK) — left rotation by newK */
            swapInRange(_p.get(), _p.get() + newK - 1);

            /* reverse right partition [newK, _size) */
            swapInRange(_p.get() + newK, _p.get() + _size - 1);

            /*reverse the entire array*/
            this->reverse();
        }

        void print()
        {
            cout << "{ ";
            for (int i = 0; i < _size; i++)
            {
                cout << _p[i] << " ";
            }
            cout << "}" << endl;
        }
    };

}

int main()
{
    using namespace AdvanceCpp;
    DynamicArray<int> arr1(10);
    for (int i = 0; i < 10; i++)
    {
        arr1[i] = i;
    }
    arr1.print();
    arr1.rotate(3);
    arr1.print();
    arr1.reverse();
    arr1.print();
    DynamicArray<string> arr2(10, "val");
    arr2.print();
    arr2[3] = "name";
    cout << arr2.at(3) << endl;
    return 0;
}