# include <iostream>
#include "std_lib_facilities.h"

using namespace std;

class Token
{
    public:
        char kind;      // what kind of Token
        double value;   // the value of the Token
        Token(char ch) 
            :kind(ch), value(0) {}
        Token(char ch, double vl)
            :kind(ch), value(vl) {}
};

Token get_Token()               // read a Token from cin
{
    char ch;
    cin >> ch;                  // Note: cin skips whitespaces, /n, spaces and \t etc

    switch (ch)
    {
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
            return Token(ch);
        
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            cin.putback(ch);        // put the char, back into the stream
            double val;
            cin >> val;
            return Token('8', val);
        }

        default:
            error("Bad Token");
    }
}

double expression();

double term();

double primary()
{
    Token T = get_Token();

    switch(T.kind)
    {
        case '(':
        {
            double d = expression();
            T = get_Token();
            if(T.kind != ')')
                error("')' expected");
            return d;
        }
        break;

        case '8':
        {
            return T.value;
        }

        default:
            error("primary expected");
    }
}

double expression()
{
    double left = term();           //read and evaluate a term
    Token T = get_Token();          //get the next token

    while(true)
    {
        switch(T.kind)
        {
            case '+':
                left += term();     // evaluate term and add
                T = get_Token();
                break;

            case '-':
                left -= term();     // evaluate term and subtract
                T = get_Token();
                break;

            default:
            return left;            // return the answer, if no more + or -
        }
    }
}

double term()
{
    double left = primary();
    Token T = get_Token();

    while(true)
    {
        switch(T.kind)
        {
            case '*':
            {
                left *= primary();
                T = get_Token();
                break;
            }

            case '/':
            {
                double d = primary();
                if(d == 0)
                    error("dividing by zero");
                left /= d;
                T = get_Token();
                break;
            }

            default:
                return left;
        }
    }
}

int main()
{
    try
    {
        while (cin)
            cout << "=" << expression() << endl;
    }
    catch (exception& e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "exception \n";
        return 2;
    }

    return 0;

}