#include "keten.hpp"
#include <vector>

using namespace std;


int main(int argc, char *argv[]){
    cout << "hello" << endl;
    vector<string> lijst;
    lijst.push_back("aalbessengelei");
    lijst.push_back("geleidehond");
    lijst.push_back("honderdmaal");
    Keten K(lijst);
    cout<<K<<std::endl;
    return 0;
}
