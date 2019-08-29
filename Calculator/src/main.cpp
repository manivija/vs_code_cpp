# include <iostream>
#include "std_lib_facilities.h"
#include <cmath>

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

class Token_Stream
{
    public:
        Token_Stream();
        Token get();
        void putback(Token T);
    private:
        bool full;              // is there a token in the buffer?
        Token buffer;           // when putback .. is called, here is where we store it
};

// the class constructor
Token_Stream::Token_Stream(): full(false), buffer(0)
{}

void Token_Stream::putback(Token T)
{
    if(full)
        error("the buffer is already full");
    buffer = T;
    full = true;
}

const char number = '8';
const char quit = 'q';
const char print = ';';
const char prompt = '>>';
const string result = "=";

Token Token_Stream::get()
{
    if(full)
    {
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;

    switch(ch)
    {
        case ';': 
        case 'q':
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
            cin.putback(ch);
            double val;
            cin >> val;
            return Token(number, val);
        }

        default:
            error("bad token");
    }
}

Token_Stream TS;

double expression();

double term();

double primary()
{
    Token T = TS.get();

    switch(T.kind)
    {
        case '(':
        {
            double d = expression();
            T = TS.get();
            if(T.kind != ')')
                error("')' expected");
            return d;
        }
        break;

        case number:
        {
            return T.value;
        }

        case '-':
        {
            return -primary();
        }

        case '+':
        {
            return +primary();
        }

        default:
            error("primary expected");
    }
}

double expression()
{
    double left = term();           //read and evaluate a term
    Token T = TS.get();         //get the next token

    while(true)
    {
        switch(T.kind)
        {
            case '+':
                left += term();     // evaluate term and add
                T = TS.get();
                break;

            case '-':
                left -= term();     // evaluate term and subtract
                T = TS.get();
                break;

            default:
            TS.putback(T);
            return left;            // return the answer, if no more + or -
        }
    }
}

double term()
{
    double left = primary();
    Token T = TS.get();

    while(true)
    {
        switch(T.kind)
        {
            case '*':
            {
                left *= primary();
                T = TS.get();
                break;
            }

            case '/':
            {
                double d = primary();
                if(d == 0)
                    error("dividing by zero");
                left /= d;
                T = TS.get();
                break;
            }

            case '%':
            {
                double d = primary();
                if(d == 0)
                    error("dividing by zero");
                left = fmod(left,d);
                T = TS.get();
                break;
            }

            default:
                TS.putback(T);
                return left;
        }
    }
}

void exit_program()
{
    cout<<"Please enter the charachter ~ to close the windows\n";
    for (char ch; cin >> ch;)
        if(ch=='~')
            return;
    return;
}

void calculate()
{
        while (cin)
        {   
            cout << prompt;
            
            Token T = TS.get();

            while(T.kind == print)
                T = TS.get();
            if(T.kind == quit)
                return;

            TS.putback(T);
            cout<<result<<expression()<<"\n";
        }
}

int main()
{
    try
    {
        calculate();
        exit_program();
        return 0;
    }
    catch (exception& e)
    {
        cerr << e.what() << endl;
        exit_program();
        return 1;
    }
    catch (...)
    {
        cerr << "exception \n";
        exit_program();
        return 2;
    }

    return 0;

}