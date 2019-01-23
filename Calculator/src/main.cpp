# include <iostream>
#include "std_lib_facilities.h"

using namespace std;

int main()
{
    //cout<<":) Please enter an expression (we can handle + and -): ";
    int lval = 0; // left value
    int rval = 32; // right value

    char op = '+'; // operator
    int res; // result

    //cin>> lval >> op >> rval; // reading something like 1 + 2

    if(op == '+')
        res = lval + rval;
    else if(op == '-')
        res = lval - rval;

    cout << "Result: " << res << "\n";
    //keep_window_open();

    return 0;

}