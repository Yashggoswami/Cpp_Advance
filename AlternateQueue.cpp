#include <iostream>
#include "stack.cpp"

using namespace std;

/*
Queue Implementation using two stacks
*/
template <typename T>
class AltQueue
{
private:
    STK::DStack<T> _input;
    STK::DStack<T> _output;
    void _refillOutputStack()
    {
        if (!_output.empty())
            return;
        while (!_input.empty())
        {
            _output.push(_input.top());
            _input.pop();
        }
    }

public:
    void push(T val)
    {
        _input.push(val);
    }
    void pop()
    {
        _refillOutputStack();
        _output.pop();
    }
    const T &front()
    {
        _refillOutputStack();
        if (_output.empty())
        {
            throw runtime_error("invalid front(): queue is empty\n");
        }
        return _output.top();
    }
};

int main()
{
    AltQueue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    cout << queue.front() << endl;
    queue.pop();
    cout << queue.front() << endl;
    queue.pop();
    cout << queue.front() << endl;
    queue.pop();
    queue.push(5);
    queue.push(6);
    cout << queue.front() << endl;
    queue.pop();
    cout << queue.front() << endl;
    queue.pop();
    cout << queue.front() << endl;
    queue.pop();
    return 0;
}