#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

struct No {
    No* left;
    No* right;
    bool ehIndice;
    // bool ehInterno;
    int indice;
    string registro;
    vector<string> traducao;
};

struct folha {
    string palavra;
    string traducao;
};

struct ArvPat {
    No* raiz = NULL;
    int indx;
    bool isIndice;

};

// ArvPat* root = new ArvPat;

// string comparaPalavra() {

// }

string fromAlphaToBin(string palavra) {
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

//essa funcao tem unica finalidade de criar um registro
//atribuindo a palavra, as traducoes e a prop ehIndice = false
No* cria_registro(string palavra, vector<string> traducao) {
    No* no = new No;
    no->registro = palavra;
    no->traducao = traducao;
    no->ehIndice = false;
    return no;
}

//cria no percorre a raiz desde o inicio PARA a criacao de um no.
//ela se difere de insereRegistro, pois 
void cria_no(No* no, int indx, string valor, vector<string> traducao, ArvPat* head, string insercao_binario, int i = 0) {
    //os indices da arvore sao em indice 1
    //os de string sao indice 0, portanto,
    //sempre precisam ser convertidos
    i++;
    int strPos = indx - 1;
    // char sentido = insercao_binario[strPos];
    //indx eh o indice em que o registro sera inserido
    char sentido_folha = (strPos >= insercao_binario.size() ? '0' : insercao_binario[strPos]);
    No* novo = new No;
    novo->indice = indx;
    novo->ehIndice = true;

    int indx_no_atual = no->indice - 1;
    //sentido_folha eh a direcao para 
    char sentido = (indx_no_atual >= insercao_binario.size() ? '0' : insercao_binario[indx_no_atual]);
    // indx_no_atual--;

    No* nova_folha = cria_registro(valor, traducao);
    //se essa condicao for verdadeira, o no atual eh a raiz
    //e o no a ser inserido deve se posicionar acima da raiz
    if(no->ehIndice == false || indx < no->indice) {
        No* antigo_no = head->raiz; //pega o no da raiz para substitui-lo
        head->raiz = novo;
        head->indx = indx; //essa atribuicao eh desnecessaria
        if (sentido_folha == '0') {
            novo->left = nova_folha;
            novo->right = antigo_no;
        }
        else if(sentido_folha == '1') {
            novo->right = nova_folha;
            novo->left = antigo_no;
        }
        cout << "cria_no primeiro if -> sentido: " << sentido << "valor: " << nova_folha->registro << "indx: " << novo->indice << endl;
        cout << "no->indice: " << no->indice << endl;
        cout << "no->left->indice" << no->left->indice << endl;
        cout << "antigo_no->ehIndice: " << antigo_no->ehIndice;
        if(antigo_no->ehIndice) {
            cout << "antigo_no->indice: " << antigo_no->indice << endl;
        }
        else {
            cout << "antigo_no->registro: " << antigo_no->registro << endl;
        }
        // cout << "no->left->registro" << no->left->registro << endl;
        // cout << "no->right->indice" << no->right->indice << endl;
        // cout << "no->right->registro" << no->right->registro << endl;

        cout << "cria_no no->ehIndice" << (novo->ehIndice) << endl;
        cout << "raiz eh indice: " << (head->raiz->ehIndice) << endl;
        cout << "condicoes: no->ehIndice == false: " << (no->ehIndice == false) << " indx < no->indice: " << (indx < no->indice) << endl;
    }
    //se a direcao do registro for esquerda e o indice do prox no for maior
    //eh depois do no atual em q se deve inserir o novo no-indice
    else if (no->left != NULL && sentido == '0' && (indx < no->left->indice || no->left->ehIndice == false)) {
        //a esquerda do novo, neste caso, insere-se a nova folha a ser inserida
        No* aux = no->left;
        no->left = novo;
        // novo->right = 
        if(sentido_folha == '0') {
            novo->left = nova_folha;
            novo->right = aux;
            cout << "insercao_binario esquerda indx no atual: " << sentido_folha << endl;
        }
        else if(sentido_folha == '1') {
            novo->right = nova_folha;
            novo->left = aux;
            cout << "insercao_binario esquerda indx no atual: " << sentido_folha << endl;
        }
        //se a direcao do registro no no eh a esquerda,
        //entao qualquer coisa q estava no no antes vai pra direita
        //e a vida continua
        cout << "cria_no segundo if -> sentido: " << sentido << "valor: " << nova_folha->registro << "indx: " << novo->indice << endl;
        cout << "sentido_folha" << sentido_folha << endl;
        cout << "no->left->indice" << no->left->indice << endl;
        cout << "no->left->registro" << no->left->registro << endl;
        cout << "no->right->indice" << no->right->indice << endl;
        cout << "no->right->registro" << no->right->registro << endl;
        cout << (indx < no->right->indice) << " " << (no->right->ehIndice == false) << endl;
    }
    else if (no->right != NULL && sentido == '1' && (indx < no->right->indice || no->right->ehIndice == false)) {
        //a esquerda do novo, neste caso, insere-se a nova folha a ser inserida
        No* aux = no->right;
        no->right = novo;
        // novo->right = 
        if(sentido_folha == '0') {
            novo->left = nova_folha;
            novo->right = aux;
            cout << "insercao_binario esquerda indx no atual: " << sentido_folha << endl;
        }
        else if(sentido_folha == '1') {
            novo->right = nova_folha;
            novo->left = aux;
            cout << "insercao_binario esquerda indx no atual: " << sentido_folha << endl;
        }

        //se a direcao do registro no no eh a direita,
        //entao qualquer coisa q estava no no antes vai pra esquerda
        //e a vida continua
        cout << "cria_no terceiro if -> sentido: " << sentido << "valor: " << nova_folha->registro << "indx: " << novo->indice << endl;
        cout << "sentido_folha" << sentido_folha << endl;
        cout << "no->left->indice" << no->left->indice << endl;
        cout << "no->left->registro" << no->left->registro << endl;
        cout << "no->right->indice" << no->right->indice << endl;
        cout << "no->right->registro" << no->right->registro << endl;
    }
    //caso o sentido seja a esquerda, mas o indice do valor ainda seja maior do q o proximo valor,
    //ou se o proximo valor ainda nao for uma folha
    else if(no->left != NULL && sentido == '0') {
        cout << (indx < no->right->indice) << " " << (no->right->ehIndice == false) << endl;
        cout << "cria_no quarto if -> sentido: " << sentido << "valor: " << nova_folha->registro << "indx: " << novo->indice << endl;
        cout << "sentido_folha" << sentido_folha << endl;
        cout << "no->left->indice" << no->left->indice << endl;
        cout << "no->left->registro" << no->left->registro << endl;
        cout << "no->right->indice" << no->right->indice << endl;
        cout << "no->right->registro" << no->right->registro << endl;
        cria_no(no->left, indx, valor, traducao, head, insercao_binario, i);
    }

    else if(no->right != NULL && sentido == '1') {
        cout << "cria_no quinto if -> sentido: " << sentido << "valor: " << nova_folha->registro << "indx: " << novo->indice << endl;
        cria_no(no->right, indx, valor, traducao, head, insercao_binario, i);
    }
}


//percorre a arvore e cria um no quando necessario
//para inserir registro. Vale a pena manter a head da arvore
//como parametro, pois eventualmente pode ser necessario atualizar
//o valor da raiz. Na chamada inicial, o No* no deve ser head->raiz
void insere_registro(No* no, string valor, vector<string> traducao, ArvPat* head, string insercao_binario = "") {
    // cout << (head->raiz == NULL);
    //cria o primeiro elemento da raiz
    if (no != NULL) cout << "se o no atual eh indice " << no->ehIndice << endl;
    if (head->raiz == NULL) {
        No* raiz = cria_registro(valor, traducao);
        head->raiz = raiz;
        cout << "primeira insercao raiz eh indice: " << head->raiz->ehIndice << endl;
    }
    else {
        // cout << "outra pos head->raiz->ehIndice: " << head->raiz->ehIndice << endl;
    // cout << "oi";
        if (insercao_binario == "") {
            insercao_binario = fromAlphaToBin(valor);
        }
        if(no->ehIndice) {
            cout << "no->indice: " << no->indice << endl;

            int indice = no->indice - 1;
            // int i = 0;
            char direcao = (indice >= insercao_binario.size() ? '0' : insercao_binario[indice]);
            if(direcao == '0') {
                No* no_esquerda = no->left;
                insere_registro(no_esquerda, valor, traducao, head, insercao_binario);
            }
            else {
                No* no_direita = no->right;
                insere_registro(no_direita, valor, traducao, head, insercao_binario);
            }
        }
        //se for folha:
        else {
            string registro = no->registro;
            int tamanhoRegistro = registro.size();
            int tamanhoPalavra = valor.size();
            int dif_tamanho = abs(tamanhoPalavra - tamanhoRegistro);
            string complemento = "";
            string registroBinario = fromAlphaToBin(no->registro);
            for(int j = 0; j < dif_tamanho; j++) {
                complemento += "00000";
            }
            if(registro.size() < valor.size()) {
               registroBinario += complemento;
            }
            else if (valor.size() < registro.size()) {
                insercao_binario += complemento;
            }

            cout << "checando se as strings estao com tamanho igual para comparacao: " << endl << registroBinario << '\n' << insercao_binario << '\n';
            cout <<"tamanhos " << registroBinario.size() << " " << insercao_binario.size() << endl;


            //se eles forem diferentes numa posicao i, nao entra na condicao
            //se for 0, por ex, precisamos corrigir esse valor para 1
            //pois indexamos a arvore a partir de 1, entao qlqr posicao x na arvore
            //eh x - 1 na string
            int i = 0;
            while(i < registroBinario.size() && registroBinario[i] == insercao_binario[i]) {
                i++;
            }
            
            //se i for igual ao size, eh pq a comparacao foi igual ate a ultima posicao,
            //e incrementou uma ultima vez, logo, as strings sao iguais
            cout << "valor i: " << i << endl;
            if(i == insercao_binario.size()) {
                //linha de teste apagar
                cout << "palavra ja existente:" << " " << valor << '\n';
            }
            else {
                //i eh 0 indexed e a arvore eh 1 indexed, a linha abaixo corrige
                int idx_corrigido = i + 1;
                
                cria_no(head->raiz, idx_corrigido, valor, traducao, head, insercao_binario);
                //cout << "palavra inserida no dicionario:" << " " << valor << '\n';
            }


        }

    }

}


void leEntrada() {
    char acao;
    cin >> acao;
    if (acao == 'i') {
        vector<string> traducoes;
        char classe;
        cin >> classe;
        int n_traducoes;
        cin >> n_traducoes;
        cin.ignore();
        while(n_traducoes--) {
            string traducao;
            getline(cin, traducao);
            traducoes.push_back(traducao);
        }
        
        // insereRegistro();
    }
}

int main() {

    ArvPat* patricia = new ArvPat;
    // cout << (patricia->raiz == NULL);
    int n = 10;
    for(int i = 0; i < n; i++) {
        vector<string> traducoes;
        string traducao;
        string palavra;
        cin >> palavra;
        // cin >> traducao;
        traducao = "men";
        traducoes.push_back(traducao);
        insere_registro(patricia->raiz, palavra, traducoes, patricia);
    }
}