//https://iudex.io/problem/63e163178216f900013be1a5/statement

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//timestamp - T, IP - C

/* O que precisa fazer:
NEW T C - vai dar um timestamp e um ip novo, ai tem que organizar em um vetor dinamico
QRY T procura esse timestamp, se tiver, da o IP e a posicao, se nao, -1 -1*/

struct Data{
    int ts;
    long long int ip;
};

void NEW(Data* &dados, int timestamp, long long int ip, int num) {
    dados = (Data*) realloc(dados, num * sizeof(Data));
    dados[num-1].ip = ip;
    dados[num-1].ts = timestamp;
}

void QRY(Data* dados, int timestamp, int num) {
    int menor = 0;
    int maior = num - 1;
    int flag = -1;

    while (menor <= maior) { //conferir pra ver se nao sai do intervalo
        int meio = menor + (maior - menor) / 2;

        if (dados[meio].ts == timestamp) {
            flag = meio;
            break;
        } else if (dados[meio].ts < timestamp) { //timestamp ta mais na direita
            menor = meio + 1;
        } else { //ts > timestamp, ou seja, timestamp ta mais na esquerda
            maior = meio - 1;
        }
    }

    if (flag != -1) {
        cout << dados[flag].ip << " " << flag << endl;
    } else {
        cout << "-1 -1" << endl;
    }
}

int main () {
    string linha;

    Data *dados = NULL;
    int qtd = 0;

    while(getline(cin, linha) && linha != "END") {      
        stringstream ss(linha);
        string comando;
        ss >> comando;
        int timestamp;
        ss >> timestamp;

        if (comando == "NEW") {
            qtd++;
            long long int ip;
            ss >> ip;
            NEW(dados, timestamp, ip, qtd);

            //teste
            //cout << qtd << endl; 
            //cout << dados[qtd-1].ts << " " << dados[qtd-1].ip << endl;
        }

        else if(comando == "QRY") {
            QRY(dados, timestamp, qtd);
        }
    }

    free(dados);

    return 0;
}
