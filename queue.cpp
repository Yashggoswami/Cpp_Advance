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
class DQueue
{
private:
    Node<T> *_front;
    Node<T> *_back;
    int _size;

public:
    DQueue() : _front(nullptr), _back(nullptr), _size(0) {};
    void push(T val)
    {
        Node<T> *node = new Node(val);
        if (_size == 0)
        {
            _back = node;
            _front = node;
        }
        else
        {
            _back->next(node);
            node->prev(_back);
            _back = node;
        }
        _size++;
    }
    const T &front()
    {
        if (_size == 0)
        {
            throw runtime_error("Invalid front(): queue is empty\n");
        }
        return _front->val();
    }

    bool empty()
    {
        return _size <= 0;
    }

    void pop()
    {
        if (_size == 0)
            return;
        Node<T> *curr = _front;
        Node<T> *next = _front->next();
        _front = next;
        if (_front != nullptr)
        {
            _front->prev(nullptr);
        }
        else
        {
            _back = nullptr;
        }
        delete curr;
        _size--;
    }
};

int main()
{
    DQueue<int> queue;
    queue.push(10);
    queue.push(12);
    cout << queue.front() << endl;
    queue.pop();
    cout << queue.front() << endl;
    queue.pop();
    if (queue.empty())
    {
        cout << "queue is empty" << endl;
    }
    try
    {
        queue.front();
    }
    catch (runtime_error e)
    {
        cout << e.what() << endl;
    }
    return 0;
}