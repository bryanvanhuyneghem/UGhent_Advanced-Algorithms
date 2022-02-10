#include "regexp.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    string s;
    cout << "Geef regexp:\n";
    cin >> s;
    try
    {
        Regexp re(s);
        cout << s << '\n'
             << re << '\n';
    }
    catch (Taalexceptie &te)
    {
        cerr << te.what() << '\n';
    }
    return 0;
}