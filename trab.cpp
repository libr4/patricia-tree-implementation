#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int GRAU_MINIMO_INDICE = 3;
int ALTURA_ARVORE;
struct No {
    chave* inicio;
    chave* fim;
    int size = 0;
    int altura = 0;
    bool is_leaf;
};
struct chave {
    int* left;
    int* right;
    int valor;
    chave* ant;
    chave* prox;
};
class Btree {
    No* raiz; 

    public:
        Btree() {
            raiz = NULL;
        }
        No* getRaiz();
        void insert(int);
};
void Btree::insert(int registro) {
    if(raiz == NULL) {
        No* novo;
        chave* c = new chave;
        c->valor = registro;
        novo->inicio = c;
        novo->size++; 
        novo->is_leaf = true;
        cout << registro << " inserido\n";
        raiz = novo;
        return;
    }
    //se o no nao estiver em seu valor maximo
    else if (raiz->size < (2*GRAU_MINIMO_INDICE) - 1) {
        No* aux_no = raiz;
        chave* aux_c = aux_no->inicio;
        chave* aux = new chave;
        
            while(aux_c) {
                if (registro < aux_c->valor) {
                    //insercao no inicio
                    if (aux_c == aux_no->inicio) {
                        aux->valor = registro;
                        aux->prox = aux_c;
                        aux_no->inicio = aux;
                        aux_no->size++;
                        cout << registro << " inserido\n";
                        return;
                    }
                    //insercao no meio
                    else {
                        aux->valor = registro;
                        aux->ant = aux_c->ant;
                        aux_c->ant->prox = aux;
                        aux_c->ant = aux;
                        aux->prox = aux_c;
                        aux_no->size++;
                        cout << registro << " inserido\n";
                        return;
                    }
                    aux_c = aux_c->prox;
                } 
            }
            //inserção ao final
            if(aux_c == NULL) {
                aux->valor = registro;
                aux_no->fim->prox = aux;
                aux->ant = aux_no->fim;
                aux_no->fim = aux;
                aux_no->size++;
            }

    }

}

int main() {
    ofstream f;
    f.open("test.bin", ios::binary);
    f.close();
}