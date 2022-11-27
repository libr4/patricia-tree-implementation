#include <iostream>
#include <map>
#include <string>

using namespace std;

extern string fromAlphaToBin(string palavra) {
    map<char, string> converter;
    converter['a'] = "00001";
    converter['b'] = "00010";
    converter['c'] = "00011";
    converter['d'] = "00100";
    converter['e'] = "00101";
    converter['f'] = "00110";
    converter['g'] = "00111";
    converter['h'] = "01000";
    converter['i'] = "01001";
    converter['j'] = "01010";
    converter['k'] = "01011";
    converter['l'] = "01100";
    converter['m'] = "01101";
    converter['n'] = "01110";
    converter['o'] = "01111";
    converter['p'] = "10000";
    converter['q'] = "10001";
    converter['r'] = "10010";
    converter['s'] = "10011";
    converter['t'] = "10100";
    converter['u'] = "10101";
    converter['v'] = "10110";
    converter['w'] = "10111";
    converter['x'] = "11000";
    converter['y'] = "11001";
    converter['z'] = "11010";
    string binary;
    for(int i = 0; i < palavra.size(); i++) {
        char letra = palavra[i];
        binary += converter[letra];
    }
    return binary;
}