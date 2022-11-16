#include <iostream>
#include <fstream>
#include <map>
using namespace std;

void readLine(int line, ifstream file) {
    string n;
    int i = 0;
    while( file >> n ) {
        if(i == line) {
            cout << n << endl;
        }
        i++;
    }
}

string fromAlphaToBin(string palavra, map<char, string> converter) {
    string binary;
    for(int i = 0; i < palavra.size(); i++) {
        char letra = palavra[i];
        binary += converter[letra];
    }
    return binary;
}

struct info {
    string um;
    string dois;
    string tres;
};
map<char, string> l;
int main() {
    l['a'] = "00001";
    l['b'] = "00010";
    l['c'] = "00011";
    l['d'] = "00100";
    l['e'] = "00101";
    l['f'] = "00110";
    l['g'] = "00111";
    l['h'] = "01000";
    l['i'] = "01001";
    l['j'] = "01010";
    l['k'] = "01011";
    l['l'] = "01100";
    l['m'] = "01101";
    l['n'] = "01110";
    l['o'] = "01111";
    l['p'] = "10000";
    l['q'] = "10001";
    l['r'] = "10010";
    l['s'] = "10011";
    l['t'] = "10100";
    l['u'] = "10101";
    l['v'] = "10110";
    l['w'] = "10111";
    l['x'] = "11000";
    l['y'] = "11001";
    l['z'] = "11010";

    // string palavra;
    // cin >> palavra;
 
    ofstream file("text.dat",  ios::binary);
    info a;
    // a.um = "rapaz";
    // a.dois = "ola";
    // a.tres = "shableu";
    // cin >> a.um;
    // cin >> a.dois;
    // cin >> a.tres;
    //char* n;
    // char** n = new char*[32];
    // char n[];
    string palavra;
    cin >> palavra;
    // cout << fromAlphaToBin(palavra, l) << endl;

    
    // readLine(2, &file);
    // n = "hello\ngoodbye\nshablau";
    // file.read((char *)&n, sizeof(n));
    // file >> n;

    file.close();
    // cout << a.um << " " << a.dois << " " << a.tres;
}