//https://iudex.io/problem/639e63568200550001708dd4/statement

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct fila {
    int id;
    string carta;
    fila *prox;
};

void adicionar_carta(fila *&jogador, string carta) {
    fila *nova_carta = new fila;
    nova_carta->carta = carta;
    nova_carta->prox = NULL;

    if (jogador == NULL) { //se tiver vazio
        jogador = nova_carta;
    }
    else {
        fila *aux = jogador;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = nova_carta;
    }
}

void DEAL(fila *jogadores, int n_jogadores, string jogada) {
    int flag_j = 0;

    for (int i = 4; i < jogada.length(); i += 3) {
        string carta = jogada.substr(i, 2);
        adicionar_carta(jogadores[flag_j].prox, carta); // adicionar a carta na fila do jogador atual
        flag_j++; // passa para o próximo jogador
    }
}

int ROUND(fila *jogadores, int n_jogadores, string *cuscuz) {

    //dar clean no cuscuz antes de iniciar a rodada
    for (int i = 0; i < n_jogadores; i++) {
        cuscuz[i] = "";
    }
    
    for (int i = 0; i < n_jogadores; i++) {
        cuscuz[i] = jogadores[i].prox->carta;
        fila *temp = jogadores[i].prox;
        jogadores[i].prox = jogadores[i].prox->prox;
        delete temp; // Remove a carta da fila do jogador
    }

    int flag_ganhador = 0, flag_empate = 0;
    for (int i = 1; i < n_jogadores; i++) {
        if ((cuscuz[i][0] > cuscuz[flag_ganhador][0]) || (cuscuz[i][0] == cuscuz[flag_ganhador][0] && cuscuz[i][1] > cuscuz[flag_ganhador][1]))  {
            flag_ganhador = i;
            flag_empate = 0;
        }


        else if (cuscuz[i][0] == cuscuz[flag_ganhador][0] && cuscuz[i][1] == cuscuz[flag_ganhador][1]) {
            flag_empate = 1;
        }

    }
    if (flag_empate) return flag_ganhador = -1;
    else return flag_ganhador;
}

int main() {
    int n_jogadores; //numero de jogadores
    cin >> n_jogadores;
    cin.ignore();

    string jogada; //saber qual a jogada
    string cuscuz[n_jogadores]; //vetor para armazenar todas as cartas

    fila *jogadores = new fila[n_jogadores]; //cada jogador vai ter uma fila de cartas
    
    int rodada = -1;

    while (getline(cin, jogada) && jogada[0] != 'E') { //enquanto nao for END
        int ganhador = -1;
        
        if (jogada[0] == 'D') { //se a jogada for DEA
            DEAL(jogadores, n_jogadores, jogada);
        }

        else if (jogada[0] == 'R') { //se for RND
            rodada++;
            ganhador = ROUND(jogadores, n_jogadores, cuscuz);
            cout << rodada << " " << ganhador << endl; //printa quem ganhou
        }

        else if (jogada[0] == 'P') { //se for PRT
            // Imprime todas as cartas do cuscuz, do topo para a base
            for (int i = n_jogadores - 1; i >= 0; i--) {
                if (i == 0) cout << cuscuz[i] << endl;
                else cout << cuscuz[i] << " ";
            }
        }
    }

    //deleta tudo
    for (int i = 0; i < n_jogadores; i++) {
        while (jogadores[i].prox != NULL) {
            fila *temp = jogadores[i].prox;
            jogadores[i].prox = jogadores[i].prox->prox;
            delete temp;
        }
    }
    delete[] jogadores;

    return 0;
}
