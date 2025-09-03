#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    string d[26];
    d[0] = "@";
    d[1] = "8";
    d[2] = "(";
    d[3] = "|)";
    d[4] = "3";
    d[5] = "#";
    d[6] = "6";
    d[7] = "[-]";
    d[8] = "|";
    d[9] = "_|";
    d[10] = "|<";
    d[11] = "1";
    d[12] = "[]\\/[]";
    d[13] = "[]\\[]";
    d[14] = "0";
    d[15] = "|D";
    d[16] = "(,)";
    d[17] = "|Z";
    d[18] = "$";
    d[19] = "\'][\'";
    d[20] = "|_|";
    d[21] = "\\/";
    d[22] = "\\/\\/";
    d[23] = "}{";
    d[24] = "`/";
    d[25] = "2";

    string l;
    getline(cin, l);
    for (char c: l) {
        if (!isalpha(c))
            cout << c;
        else
            cout << d[tolower(c) - 'a'];
    }

    return 0;
}
