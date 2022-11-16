#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    long n;
    cin >> n;
    vector<string> livros;
    vector<long> entregue;

    for (long i = 0; i < n; i++){
        string livro;
        long devo;
        cin >> livro >> devo;
        livros.push_back(livro);
        entregue.push_back(devo);
    }
    long consultas;
    cin >> consultas;
    for (long i = 0; i < consultas; i++){
        string livro;
        cin >> livro;
        vector<string>::iterator achei = lower_bound(livros.begin(), livros.end(), livro);
        if (livros.size() > 0 && livros[achei - livros.begin()] == livro){
            if (entregue[achei - livros.begin()] == 1){
                cout << "Disponivel" << endl;
            }
            else{
                cout << "Emprestado" << endl;
            }
        }
        else{
            cout << "Nao encontrado" << endl;
        }
    }
}