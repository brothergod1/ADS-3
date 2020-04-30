#include <iostream>
#include "tstack.h"
using namespace std;

int getp(char ch)
{
    switch (ch)
    {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
    default: return -1;
    }
}

string infx2pstfx(string inf)
{
    TStack<char> stack;
    string st = "";
    for (int i = 0; i < inf.size(); i++) {
        char ch = inf[i];
        int priority = getp(ch);
        if (priority == -1)
            st.append(string(1, ch));
        else
            if (stack.isEmpty() || priority == 0 || priority > getp(stack.get()))
                stack.push(ch);
            else {
                if (ch == ')')
                    while (true) {
                        char last = stack.get();
                        stack.pop();
                        if (last != '(')
                            st.append(string(1, last));
                        else
                            break;
                    }
                else {
                    while (!stack.isEmpty()) {
                        char last = stack.get();
                        stack.pop();
                        if (getp(last) >= priority)
                            st.append(string(1, last));
                    }
                    stack.push(ch);
                }
            }
    }
    while (!stack.isEmpty()) {
        char last = stack.get();
        stack.pop();
        st.append(string(1, last));
    }
    return st;
}

int ops(int num1, int num2, char op)
{
    switch (op)
    {
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case '*': return num1 * num2;
    case '/': return num1 / num2;
    default: return -1;
    }
}

int eval(string pst)
{
TStack<int> stack;
for(int i = 0; i < pst.size(); i++) {
    char ch = pst[i];
    int priority = getp(ch);
        if (priority == -1)
            stack.push(ch - 48);
        else {
            int num1 = stack.get();
            stack.pop();
            int num2 = stack.get();
            stack.pop();
            int result = ops(num2, num1, ch);
            stack.push(result);
        }
    }
return stack.get();
}
