extern "C" {
    int yylex();
}

#include "iostream"
using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "USING: mjc filename";
        return -1;
    }
    freopen(argv[1], "r", stdin);
    yylex();
}