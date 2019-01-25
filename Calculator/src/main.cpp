# include <iostream>
#include "std_lib_facilities.h"

using namespace std;

int main()
{
    cout<<"Please enter an expression (we can handle +,-,* and /)"<<"\n";
    cout<<"add an x to end expression (e.g., 1+2*3x): ";
    int lval = 0; // left value
    int rval = 0; // right value

    cin>>lval;

    if(!cin)
        error("no first opperand");

    for(char op; cin>>op;)
    {
        if(op != 'x')
            cin>>rval;

        if(!cin)
            error("no second opperand");
        
        switch(op)
        {
            case '+':
            {
                lval += rval;
                break;
            }

            case '-':
            {
                lval -= rval;
                break;
            }

            case '*':
            {
                lval *= rval;
                break;
            }

            case '/':
            {
                lval /= rval;
                break;
            }

            default:
            {
                cout << "Result: " << lval << "\n";
                return 0;
            }
        }
    }

    error("bad expression");

    return 0;

}