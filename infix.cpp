#include<iostream>
#include <stack>
using namespace std;
int precedence(char op)
{
    if(op == '+'||op == '-')
    return 1;
    if(op == '*'||op == '/')
    return 2;
    return 0;
}
int applyOp(int a, int b, char op)
{
    switch(op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
}
int InfixEval(string infix)
{
    int i;
    stack <int> values;
    stack <char> ops; 
    for(i = 0; i < infix.length(); i++)
    {
        if(infix[i] == ' ')
        continue;
        else if(infix[i] == '(')
        {
            ops.push(infix[i]);
        }
        else if(isdigit(infix[i]))
        {
            int val = 0;
            while(i < infix.length() && isdigit(infix[i]))
            {
                val = (val*10) + (infix[i]-'0');
                i++;
            }
            values.push(val);
            i--;
        }
        else if(infix[i] == ')')
        {
            while(!ops.empty() && ops.top() != '(')
            {
                int val2 = values.top();
                values.pop();
                 
                int val1 = values.top();
                values.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                values.push(applyOp(val1, val2, op));
            }
            if(!ops.empty())
            ops.pop();
        }
        else
        {
            while(!ops.empty() && precedence(ops.top()) >= precedence(infix[i]))
            {
                int val2 = values.top();
                values.pop();
                 
                int val1 = values.top();
                values.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                values.push(applyOp(val1, val2, op));
            }
            ops.push(infix[i]);
        }
    }
    while(!ops.empty())
    {
        int val2 = values.top();
        values.pop();
                 
        int val1 = values.top();
        values.pop();
                 
        char op = ops.top();
        ops.pop();
                 
        values.push(applyOp(val1, val2, op));
    }
    return values.top();
}
 
int main() 
{   
    string post = "5 * ( 2 + 4 ) / 14";
    cout<<"\n****************************************";
    cout<<"\n         ***Infix Evalution***         ";
    cout<<"\n****************************************";
    cout<<"\nThe Arihtmetic Expression Given is:\n"<<post;
    cout<<"\n****************************************";
    cout<<"\nSolution:- "<<InfixEval(post);
    cout<<"\n****************************************";
    return 0;
}