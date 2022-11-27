#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <functional>

#define endline '\n';

using namespace std;
struct No {
    No* left;
    No* right;
    bool ehIndice;
    // bool ehInterno;
    int indice;
    string registro;
    int file_position;
    vector<string> traducao;
};

// struct folha {
//     string palavra;
//     string traducao;
// };

//just to mark a reference
//to the beginning of the trie
struct ArvPat {
    No* raiz = NULL;
    int indx;

};


string fromAlphaToBin(string palavra, string separator = "", string end = "") {
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
        binary += separator;
    }
    binary += end;
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

struct Record {
    string word;
    int n_translations;
    vector<string> translations;
    string tipo;
};

void add_reference(int file_position) {
    ofstream fileIn("load_refs.dat",  ios::binary | ios::app | ios::ate);
    fileIn << file_position << endline;
    fileIn.close();
}

int add_record(Record r) {
    ofstream fileIn("text.dat",  ios::binary | ios::app | ios::ate  );
    int insertion_pos = fileIn.tellp();
    add_reference(insertion_pos);
    fileIn << r.word << endline;
    fileIn << r.tipo << endline;
    fileIn << r.n_translations << endline;
    for (int i = 0; i < r.n_translations; i++) {
        fileIn << r.translations[i] << endline;
    }
    fileIn.close();
    return insertion_pos;
}

//cria no percorre a raiz desde o inicio PARA a criacao de um no.
//ela se difere de insereRegistro, pois 
void cria_no(No* no, int indx, Record record, ArvPat* head, string insercao_binario, string mode="", int load_position = -1) {
    //os indices da arvore sao em indice 1
    //os de string sao indice 0, portanto,
    //sempre precisam ser convertidos
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

    // No* nova_folha = cria_registro(record.word, record.translations);
    No* nova_folha = new No;
    nova_folha->ehIndice = false;
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

        if(mode != "load") {
            int position = add_record(record);
            nova_folha->file_position = position;
            cout << "palavra inserida no dicionario: " << record.word << endline;
        } 
        else {
            nova_folha->file_position = load_position;
        }
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
        }
        else if(sentido_folha == '1') {
            novo->right = nova_folha;
            novo->left = aux;
        }

        if(mode != "load") {
            int position = add_record(record);
            nova_folha->file_position = position;
            cout << "palavra inserida no dicionario: " << record.word << endline;
        } 
        else {
            nova_folha->file_position = load_position;
        }
        //se a direcao do registro no no eh a esquerda,
        //entao qualquer coisa q estava no no antes vai pra direita
        //e a vida continua
    }
    else if (no->right != NULL && sentido == '1' && (indx < no->right->indice || no->right->ehIndice == false)) {
        //a esquerda do novo, neste caso, insere-se a nova folha a ser inserida
        No* aux = no->right;
        no->right = novo;
        // novo->right = 
        if(sentido_folha == '0') {
            novo->left = nova_folha;
            novo->right = aux;
        }
        else if(sentido_folha == '1') {
            novo->right = nova_folha;
            novo->left = aux;
        }
        

        if(mode != "load") {
            int position = add_record(record);
            nova_folha->file_position = position;
            cout << "palavra inserida no dicionario: " << record.word << endline;
        } 
        else {
            nova_folha->file_position = load_position;
        }
        //se a direcao do registro no no eh a direita,
        //entao qualquer coisa q estava no no antes vai pra esquerda
        //e a vida continua
    }
    //caso o sentido seja a esquerda, mas o indice do valor ainda seja maior do q o proximo valor,
    //ou se o proximo valor ainda nao for uma folha
    else if(no->left != NULL && sentido == '0') {
        cria_no(no->left, indx, record, head, insercao_binario, mode, load_position);
    }

    else if(no->right != NULL && sentido == '1') {
        cria_no(no->right, indx, record, head, insercao_binario, mode, load_position);
    }
}

string get_word(int file_position) {
    ifstream file("text.dat", ios::binary);
    file.seekg(file_position);
    string word;
    getline(file, word);
    file.close();
    return word;
}
string get_cls(int file_position) {
    ifstream file("text.dat", ios::binary);
    file.seekg(file_position);
    string word;
    getline(file, word);
    string cls;
    getline(file, cls);
    file.close();
    return cls;
}

vector<string> get_translations(int file_position) {
    vector<string> translations;
    ifstream file("text.dat", ios::binary);
    file.seekg(file_position);
    string word;
    getline(file, word);
    getline(file, word);
    string sn_translations;
    getline(file, sn_translations);
    int n_translations = stoi(sn_translations, nullptr, 10);
    for(int i = 0; i < n_translations; i++) {
        string translation;
        getline(file, translation);
        translations.push_back(translation);
    }
    file.close();
    return translations;
}

//percorre a arvore e cria um no quando necessario
//para inserir registro. Vale a pena manter a head da arvore
//como parametro, pois eventualmente pode ser necessario atualizar
//o valor da raiz. Na chamada inicial, o No* no deve ser head->raiz
void insere_registro(No* no, Record record, ArvPat* head,  string insercao_binario = "", string mode = "", int load_position = -1) {
    //cria o primeiro elemento da raiz
    if (head->raiz == NULL) {
        No* raiz = new No;
        raiz->ehIndice = false;
        head->raiz = raiz;
        if(mode != "load") {
            int position = add_record(record);
            raiz->file_position = position;
            cout << "palavra inserida no dicionario: " << record.word << endline;
        } 
        else {
            raiz->file_position = load_position;
        }
    }
    else {
        if (insercao_binario == "") {
            insercao_binario = fromAlphaToBin(record.word);
        }
        if(no->ehIndice) {

            int indice = no->indice - 1;
            // int i = 0;
            char direcao = (indice >= insercao_binario.size() ? '0' : insercao_binario[indice]);
            if(direcao == '0') {
                No* no_esquerda = no->left;
                insere_registro(no_esquerda, record, head, insercao_binario, mode, load_position);
            }
            else {
                No* no_direita = no->right;
                insere_registro(no_direita, record, head, insercao_binario, mode, load_position);
            }
        }
        //se for folha:
        else {
            //aqui vai ser diferente, eu preciso ter, aqui uma referencia a um registro, e pegar
            int file_position = no->file_position;
            string registro = get_word(file_position);

            int tamanhoRegistro = registro.size();
            int tamanhoPalavra = record.word.size();
            int dif_tamanho = abs(tamanhoPalavra - tamanhoRegistro);
            string complemento = "";
            string registroBinario = fromAlphaToBin(registro);
            for(int j = 0; j < dif_tamanho; j++) {
                complemento += "00000";
            }
            if(registro.size() < record.word.size()) {
               registroBinario += complemento;
            }
            else if (record.word.size() < registro.size()) {
                insercao_binario += complemento;
            }

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
            if(i == insercao_binario.size()) {
                //linha de teste apagar
                cout << "palavra ja existente:" << " " << record.word << '\n';
            }
            else {
                //i eh 0 indexed e a arvore eh 1 indexed, a linha abaixo corrige
                int idx_corrigido = i + 1;
                cria_no(head->raiz, idx_corrigido, record, head, insercao_binario, mode, load_position);
                //cout << "palavra inserida no dicionario:" << " " << valor << '\n';
            }
        }
    }
}

int find_record(No* no, string word, ArvPat* head, string insercao_binario = "") {
    if (head->raiz == NULL) {
        return -1;
    }
    else {
        if (insercao_binario == "") {
            insercao_binario = fromAlphaToBin(word);
        }
        if(no->ehIndice) {
            //gets index from index node
            int indice = no->indice - 1;
            //gets direction
            char direction = (indice >= insercao_binario.size() ? '0' : insercao_binario[indice]);
            //redirects to proper nodes
            if(direction == '0') {
                No* no_esquerda = no->left;
                return find_record(no_esquerda, word, head, insercao_binario);
            }
            else {
                No* no_direita = no->right;
                return find_record(no_direita, word, head, insercao_binario);
            }
        }

        //if it's leaf
        else {
            //gets position of record in file
            int file_position = no->file_position;
            string registro = get_word(file_position);
            if (registro == word) {
                 return file_position;
            }
                return -1;
        }
    }
}

string create_cls(char c) {
    map<char, string> converter;
    converter['a'] = "adjetivo";
    converter['s'] = "substantivo";
    converter['v'] = "verbo";
    return converter[c];
}

void print_record_bin(No* no, char cls) {
        int file_position = no->file_position;
        string word = get_word(file_position);
        string word_bin = fromAlphaToBin(word, " ", "00000");
        cout << word << " " << word_bin << endline;
}

void print_by_cls(No* no, char cls) {
    int file_position = no->file_position;
    string word = get_word(file_position);

    string word_cls = get_cls(file_position);
    string str_cls = create_cls(cls);
    if (str_cls == word_cls) {
        cout << word << endline;
    }
}

void print_record(No* no, char cls) {
        int file_position = no->file_position;
        string registro = get_word(file_position);
        cout << registro << endline;
}

void print_tree(No* no,  function<void(No*, char)> map, char cls = 's', char mode = 'c') {
    if (no == NULL) {
        return;
    }
    else if (no->ehIndice == true) {
        if (mode == 'c') {
            print_tree(no->left, map, cls, mode);
            print_tree(no->right, map, cls, mode);
        }
        else {
            print_tree(no->right, map, cls, mode);
            print_tree(no->left, map, cls, mode);
        }
    }
    else if(no->ehIndice == false) {
        map(no, cls);
    }
}

void print_cls(ArvPat* head) {
    string word;
    getline(cin, word);
    int file_position = find_record(head->raiz, word, head);
    if(file_position == -1) {
        cout << "palavra inexistente no dicionario: " << word << endline;
    }
    else {
        string cls = get_cls(file_position);
        cout << "classe da palavra: " << word << ": " << cls << endline;
    }
}

Record read_record(int file_position) {
    ifstream file("text.dat", ios::binary);
    file.seekg(file_position);
    string word;
    getline(file, word);
    string type;
    getline(file, type);
    string sn_translations;
    getline(file, sn_translations);
    int n_translations = stoi(sn_translations, nullptr, 10);

    vector<string> translations;
    for(int i = 0; i < n_translations; i++) {
        string translation;
        getline(file, translation);
        translations.push_back(translation);
    }

    Record record;
    record.word = word;
    record.n_translations = n_translations;
    record.translations = translations;
    record.tipo = type;

    file.close();
    return record;
}

void print_translations(ArvPat* head) {
    string word;
    cin >> word;
    int file_position = find_record(head->raiz, word, head);
    if(file_position == -1) {
        cout << "palavra inexistente no dicionario: " << word << endline;
    }
    else {
        Record record = read_record(file_position);
        vector<string> translations = record.translations;
        int n_translations = translations.size();
        cout << "traducoes da palavra: " << word << endline;
        for(int i = 0; i < n_translations; i++) {
            cout << translations[i] << endline;
        }
    }
}

void show_tree(No* no, char mode = 'c') {
    if (no == NULL) {
        return;
    }
    else if (no->ehIndice == true) {
        cout << "bit: " << no->indice; 
        if(no->left->ehIndice) {
            // cout << "no->left->ehIndice" << no->left->ehIndice << endline;
            cout << " fesq: " << no->left->indice;
        }
        else {
            // cout << "no->left->ehIndice" << no->left->ehIndice << endline;
            int file_position = no->left->file_position;
            string word = get_word(file_position);
            cout << " fesq: " << word;
        }
        if(no->right->ehIndice) {
            // cout << "no->right->ehIndice" << no->right->ehIndice << endline;
            cout << " fdir: " << no->right->indice;
        }
        else {
            // cout << "no->right->ehIndice" << no->right->ehIndice << endline;
            int file_position = no->right->file_position;
            string word = get_word(file_position);
            cout << " fdir: " << word;
        }
        cout << endline;
        // if (mode == 'c') {
        show_tree(no->left, mode);
        show_tree(no->right, mode);
        // }
    }
    else if(no->ehIndice == false) {
        int file_position = no->file_position;
        string registro = get_word(file_position);
        cout << registro << endline;
    }
}

void delete_node(string binary_word, No* no, No* spared_node, ArvPat* head, No* previous_node) {
    delete no;
    //essa condicao soh eh vdd
    //se a posicao for a raiz
    if (previous_node == NULL) {
        head->raiz = spared_node;
    } 
    else {
    
        int converted_index = previous_node->indice - 1;
        char direction = (converted_index >= binary_word.size() ? '0' : binary_word[converted_index]);
        if (direction == '0') {
            previous_node->left = spared_node;
        }
        else {
            previous_node->right = spared_node;
        }
    }
}

void erase_ref(string erase_line) {
    std::string line;
    std::ifstream fin;
    
    string path = "load_refs.dat";
    fin.open(path);
    // contents of path must be copied to a temp file then
    // renamed back to the path file
    std::ofstream temp;
    temp.open("temp.dat");

    while (getline(fin, line)) {
        // write all lines to temp other than the line marked for erasing
        if (line != erase_line)
            temp << line << std::endl;
    }

    temp.close();
    fin.close();

    // required conversion for remove and rename functions
    const char * p = path.c_str();
    cout << p << endline;
    remove(p);
    rename("temp.dat", p);
}

void delete_leaf(No* no, string word, ArvPat* head, string insercao_binario = "", No* previous_node = NULL) {

    if (head->raiz->ehIndice == false && head->raiz == no) {
        cout << "entrou aqui" << word << endline;

        int file_position = no->file_position;
        Record record = read_record(file_position);
        cout << "palavra removida: " << word << endline;
        string sfile_position = to_string(file_position);
        erase_ref(sfile_position);
        delete no;
        return;
    }
    else {
        if (insercao_binario == "") {
            insercao_binario = fromAlphaToBin(word);
        }
        if(no->ehIndice) {
        cout << "entrou aqui2" << word << endline;
            //gets index from index node
            int indice = no->indice - 1;
            //gets direction
            char direction = (indice >= insercao_binario.size() ? '0' : insercao_binario[indice]);
            //redirects to proper nodes
            if(direction == '0') {
                
                No* no_esquerda = no->left;
                if(no_esquerda->ehIndice) {
                    return delete_leaf(no_esquerda, word, head, insercao_binario, no);
                }
                int file_position = no_esquerda->file_position;
                Record record = read_record(file_position);
                string registro = record.word;
                if (registro == word) {
                    delete no_esquerda;
                    delete_node(insercao_binario, no, no->right, head, previous_node);
                    string sfile_position = to_string(file_position);
                    erase_ref(sfile_position);
                    cout << "palavra removida: " << word << endline;
                    return;
                }
                cout << "palavra inexistente no dicionario: " << word << endline;
                return;
            }
            else {
                No* no_direita = no->right;
                if(no_direita->ehIndice) {
                    return delete_leaf(no_direita, word, head, insercao_binario, no);
                }
                int file_position = no_direita->file_position;
                string registro = get_word(file_position);
                if (registro == word) {
                    delete no_direita;
                    delete_node(insercao_binario, no, no->left, head, previous_node);
                    string sfile_position = to_string(file_position);
                    erase_ref(sfile_position);
                    cout << "palavra removida: " << word << endline;
                    return;
                }
                cout << "palavra inexistente no dicionario: " << word << endline;
                return;
            }
        }
    }
}

int main() {

    ifstream loadTree("load_refs.dat", ios::binary);
    ArvPat* patricia = new ArvPat;
    string sfile_position;
    while(getline(loadTree, sfile_position)) {
        cout << sfile_position << endline;
        int load_position = stoi(sfile_position, nullptr, 10);
        cout << load_position << endline;
        Record record = read_record(load_position);
        insere_registro(patricia->raiz, record, patricia, "", "load", load_position);
    }
    loadTree.close();

    while(true) {
        string action;
        getline(cin, action);
        if(action == "e") {
            break;
        }
        else if(action == "i") {
            vector<string> translations;
            string translation;
            string word;
            getline(cin, word);
            string scls;
            getline(cin, scls);
            char cls = scls[0];
            string sn_translations;
            getline(cin, sn_translations);
            int n_translations = stoi(sn_translations, nullptr, 10);
            for(int i = 0; i < n_translations; i++) {
                getline(cin, translation);
                translations.push_back(translation);
            }
            Record record;
            record.word = word;
            record.n_translations = n_translations;
            record.translations = translations;
            record.tipo = create_cls(cls);
            insere_registro(patricia->raiz, record, patricia);
        }
        else if(action == "l") {
            string order;
            getline(cin, order);
            char o = order[0];
            print_tree(patricia->raiz, print_record, 's', o);
        }
        else if(action == "t") {
            print_translations(patricia);
        }
        else if(action == "a") {
            string scls;
            getline(cin, scls);
            char cls = scls[0];
            string order;
            getline(cin, order);
            char o = order[0];
            print_tree(patricia->raiz, print_by_cls, cls, o);
        }
        else if(action == "c") {
            print_cls(patricia);
            // print_tree_cls(patricia->raiz, 'v');
        }
        else if(action == "p") {
            show_tree(patricia->raiz);
            print_tree(patricia->raiz, print_record_bin);
        }
        else if(action == "r") {
            string word;
            getline(cin, word);
            delete_leaf(patricia->raiz, word, patricia);
        }
    }
}