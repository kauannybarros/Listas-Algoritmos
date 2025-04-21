//https://iudex.io/problem/62e444b2f485b80001381e27/statement

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/* OQ PRECISA FAZER:
hashtable-> funcao de dispersao: h(T) T mod M
T -> timestamp, M -> tamanho da tabela
cada posicao armazena uma lisa de pares (T,C) (open hashing)
antes de inserir na hashtable, conferir o fator de carga limite e ver se ele eh maior que o Lmax
se for, faz um rehashing e coloca a nova hashtable como 2*M + 1 e ordena tudo dnv
*/

struct Data{
    int ts;
    long long int ip;
};

void insertionSort(Data* dado, int tam) {
    //insertion sort p ordenar cada indice
    for (int i = 1; i < tam; i++) {
        Data aux = dado[i];
        int j = i - 1;

        while (j >= 0 && dado[j].ts > aux.ts) {
            dado[j + 1] = dado[j];
            j--;
        }
        dado[j + 1] = aux;
    }
}

Data** REHASHING(Data **dados, int &tam_a, int* &quantidades) {

    int tam_n = (2 * tam_a) + 1; //tamanho novo da hashtable

    Data **aux_dados = (Data**) calloc(tam_n, sizeof(Data*));

    int *aux_qtds = (int*) calloc(tam_n, sizeof(int));

    for (int i=0; i < tam_a; i++) {
        //ir transferindo os elementos
        for (int j=0; j < quantidades[i]; j++) {
            int pos = dados[i][j].ts % tam_n;
            aux_dados[pos] = (Data*) realloc(aux_dados[pos], (aux_qtds[pos] + 1) * sizeof(Data));
            aux_dados[pos][aux_qtds[pos]].ts = dados[i][j].ts;
            aux_dados[pos][aux_qtds[pos]].ip = dados[i][j].ip;
            aux_qtds[pos]++;
        }
        
    }
    
    //conferir a ordenacao
    for (int i = 0; i < tam_n; i++) {
        if (aux_qtds[i] > 1) {
            insertionSort(aux_dados[i], aux_qtds[i]);
        }
    }

    free(quantidades);
    quantidades = aux_qtds;

    for (int i=0; i < tam_a; i++) {
        free(dados[i]);
    }
    free(dados);

    tam_a = tam_n;

    return aux_dados;

}

void NEW(Data** &dados, int timestamp, long long int ip, int num, int *&quantidades) {
   int pos = timestamp % num;
    dados[pos] = (Data*) realloc(dados[pos], (quantidades[pos] + 1) * sizeof(Data));
    dados[pos][quantidades[pos]].ts = timestamp;
    dados[pos][quantidades[pos]].ip = ip;
    quantidades[pos]++;
    cout << pos << " " << quantidades[pos] << endl;
}

void QRY(Data** dados, int timestamp, int num, int *quantidades) {
    int pos = timestamp % num;
    int menor = 0;
    int maior = quantidades[pos] - 1;
    int flag = -1;

    while (menor <= maior) { //conferir pra ver se nao sai do intervalo
        int meio = menor + (maior - menor) / 2;

        if (dados[pos][meio].ts == timestamp) {
            flag = meio;
            break;
        } else if (dados[pos][meio].ts < timestamp) { //timestamp ta mais na direita
            menor = meio + 1;
        } else { //ts > timestamp, ou seja, timestamp ta mais na esquerda
            maior = meio - 1;
        }
    }

    if (flag != -1) {
        cout << dados[pos][flag].ip << " " << flag << endl;
    } else {
        cout << "-1 -1" << endl;
    }
}

int main () {
    int tam;
    float fcl;
    cin >> tam;
    cin >> fcl;
    cin.ignore();

    string linha;

    Data **dados = (Data**) calloc(tam, sizeof(Data*));
    int *quantidades = (int*) calloc(tam, sizeof(int));

    int qtd = 0;

    while(getline(cin, linha) && linha != "END") {      
        stringstream ss(linha);
        string comando;
        ss >> comando;
        int timestamp;
        ss >> timestamp;

        if (comando == "NEW") {
            long long int ip;
            ss >> ip;
            if( (float)qtd / (float)tam > fcl) dados = REHASHING (dados, tam, quantidades);
            NEW(dados, timestamp, ip, tam, quantidades);
            qtd++;
            //imprimir uma linha I S, I = h(T) que eh a posicao na hashtable e S a quantidade de pares da lista
        }

        else if(comando == "QRY") {
            QRY(dados, timestamp, tam, quantidades);
            //imprimir uma linha C J, C=ip do T e J a posicao. se nao tiver, -1 -1
        }

        //teste p saber oq ta dando errado
        /*else if(comando == "TAM") {
            cout << tam << endl;
        }*/
    }

    for (int i=0; i < tam; i++) {
        free(dados[i]);
    }
    free(dados);
    free(quantidades);

    return 0;
}
