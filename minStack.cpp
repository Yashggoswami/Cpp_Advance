#include <iostream>
#include <string>
#include "stack.cpp"

using namespace std;

class minStack
{
private:
    STK::DStack<pair<int, int>> _stack;

public:
    void pop()
    {
        _stack.pop();
    }
    void push(int node)
    {
        int min_val = _stack.empty() ? node : min(_stack.top().second, node);
        _stack.push({node, min_val});
    }
    int top()
    {
        if (_stack.empty())
        {
            throw runtime_error("Invalid top(): _stack is empty \n");
        }
        return _stack.top().first;
    }

    void printTop()
    {
        cout << "top: " << this->top() << endl;
    }
    int getMin()
    {
        if (_stack.empty())
        {
            throw runtime_error("Invalid top(): _stack is empty \n");
        }
        return _stack.top().second;
    }
    void printMin()
    {
        cout << "min: " << this->getMin() << endl;
    }
};

int main()
{
    minStack stk;
    stk.push(1);
    stk.push(2);
    stk.printTop();
    stk.printMin();
    stk.push(-1);
    stk.printMin();
    stk.push(-2);
    stk.printMin();
    stk.push(3);
    stk.printTop();
    stk.printMin();
    stk.pop();
    stk.pop();
    stk.printTop();
    stk.printMin();
    stk.pop();
    stk.printTop();
    stk.printMin();
    return 0;
}
