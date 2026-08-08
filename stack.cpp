#include <iostream>

using namespace std;

template <typename T>
class Node
{
private:
    T _val;
    Node *_next;
    Node *_prev;

public:
    explicit Node(T val) : _val(val), _next(nullptr), _prev(nullptr) {};

    Node<T> *next()
    {
        return _next;
    }
    void next(Node<T> *node)
    {
        _next = node;
    }
    Node<T> *prev()
    {
        return _prev;
    }
    void prev(Node<T> *node)
    {
        _prev = node;
    }
    void val(const T &val)
    {
        _val = val;
    }

    const T &val()
    {
        return _val;
    }
};

template <typename T>
class DStack
{
private:
    Node<T> *_top;
    int _size;

public:
    DStack() : _top(nullptr), _size(0) {};
    void push(T val)
    {
        Node<T> *node = new Node(val);
        if (_size == 0)
        {
            _top = node;
        }
        else
        {
            _top->next(node);
            node->prev(_top);
            _top = node;
        }
        _size++;
    }
    const T &top()
    {
        if (_size == 0)
        {
            throw runtime_error("Invalid top(): stack is empty\n");
        }
        return _top->val();
    }

    bool empty()
    {
        cout << "empty " << _size << endl;
        return _size <= 0;
    }

    void pop()
    {
        if (_size == 0)
            return;
        Node<T> *curr = _top;
        Node<T> *prev = _top->prev();
        _top = prev;
        if (_top != nullptr)
        {
            _top->next(nullptr);
        }
        delete curr;
        _size--;
    }
};

int main()
{
    DStack<int> stack;
    stack.push(10);
    stack.push(12);
    cout << stack.top() << endl;
    stack.pop();
    cout << stack.top() << endl;
    stack.pop();
    if (stack.empty())
    {
        cout << "stack is empty" << endl;
    }
    try
    {
        stack.top();
    }
    catch (runtime_error e)
    {
        cout << e.what() << endl;
    }
    return 0;
}