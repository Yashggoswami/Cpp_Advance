#include <iostream>
#include <unordered_map>
#include "stack.cpp"

using namespace std;
unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};

bool validParentheses(const string &expression)
{
    STK::DStack<char> stk;
    for (char value: expression)
    {   
        if (value == '[' || value == '(' || value == '{')
        {   
            stk.push(value);
        }
        const auto itr = pairs.find(value);
        if (itr != pairs.end())
        {
            if(stk.empty() || stk.top() != itr->second) return false;
            stk.pop();
        }
    }

    return stk.empty();
}



int main()
{
    string expr = "[12+10-(6-5/(12-4))*{12+5}]";
    string expr1 = "[12+10-(6-5/(12-4)*{12+5}]";
    if(validParentheses(expr)){
        cout << "is valid "<<endl;
    }else{
        cout << "invalid"<<endl;
    }
    return 0;
}
