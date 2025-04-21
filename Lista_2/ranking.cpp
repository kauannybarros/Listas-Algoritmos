//https://iudex.io/problem/6167437897713f0001036f42/statement

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct no_arvore {
    string nome;
    int pontuacao;
    no_arvore *pai;
    no_arvore *esq;
    no_arvore *dir;
};

no_arvore *adicionar_no(no_arvore *raiz, string nome, int pontuacao, int *flag) {
    no_arvore *novo = new no_arvore;
    novo->nome = nome;
    novo->pontuacao = pontuacao;
    novo->pai = NULL;
    novo->esq = NULL;
    novo->dir = NULL;

    if (raiz == NULL) {
        return novo;
    }

    no_arvore *atual = raiz;
    no_arvore *anterior = NULL;

    while (atual != NULL) {
        anterior = atual;
        if (pontuacao < atual->pontuacao) {
            atual = atual->esq;
        } 
        else if (pontuacao > atual->pontuacao) {
            atual = atual->dir;
        }

        else {
            cout << nome << " ja esta no sistema." << endl;
           *flag = 1;
            delete novo;
            return raiz;
        }

    }

    novo->pai = anterior;

    if (pontuacao < anterior->pontuacao) {
        anterior->esq = novo;
    } else {
        anterior->dir = novo;
    }

    return raiz;
}

//funcao pra saber o sucessor
no_arvore *sucessor(no_arvore *no) {
    if (no->dir != NULL) {
        no_arvore *atual = no->dir;
        while (atual->esq != NULL) {
            atual = atual->esq;
        }
        return atual;
    } else {
        no_arvore *atual = no;
        no_arvore *pai = no->pai;
        while (pai != NULL && atual == pai->dir) {
            atual = pai;
            pai = pai->pai;
        }
        return pai;
    }
}

//funcao pra saber o antecessor
no_arvore *antecessor(no_arvore *no) {
    if (no->esq != NULL) {
        no_arvore *atual = no->esq;
        while (atual->dir != NULL) {
            atual = atual->dir;
        }
        return atual;
    } else {
        no_arvore *atual = no;
        no_arvore *pai = no->pai;
        while (pai != NULL && atual == pai->esq) {
            atual = pai;
            pai = pai->pai;
        }
        return pai;
    }
}


no_arvore *buscar_no(no_arvore *raiz, int pontuacao) {
    no_arvore *atual = raiz;
    while (atual != NULL && atual->pontuacao != pontuacao) {
        if (pontuacao < atual->pontuacao) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    return atual;
}

void liberar_arvore(no_arvore *raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esq);
        liberar_arvore(raiz->dir);
        delete raiz;
    }
}


int main() {
    int K;
    cin >> K;
    cin.ignore();

    no_arvore *raiz = NULL;

    for (int i = 0; i < K; i++) {
        int flag_suc = 0;
        int flag_ant = 0;
        int flag_rep = 0;

        string linha;
        getline(cin, linha);

        string nome;
        int pontuacao;

        if (linha.substr(0, 3) == "ADD") {
            stringstream ss(linha);
            string comando;
            ss >> comando;
            ss >> nome;
            ss >> pontuacao;

            raiz = adicionar_no(raiz, nome, pontuacao, &flag_rep);
            if (flag_rep == 0) cout << nome << " inserido com sucesso!" << endl;

        } else if (linha.substr(0, 4) == "PROX") {
            stringstream ss(linha);
            string comando;
            ss >> comando;
            ss >> pontuacao;

            no_arvore *atual = buscar_no(raiz, pontuacao);

                no_arvore *suc = NULL, *ant = NULL;
                suc = sucessor(atual);
                ant = antecessor(atual);

                if (suc != NULL) {
                    flag_suc = 1;
                }
                if (ant != NULL) {
                    flag_ant = 1;
                }

                if (!flag_ant && !flag_suc) {
                    cout << "Apenas " << atual->nome << " existe no sistema..." << endl;
                } else if (!flag_ant && flag_suc) {
                    cout << atual->nome << " e o menor! e logo apos vem " << suc->nome << endl;
                } else if (flag_ant && !flag_suc) {
                    cout << atual->nome << " e o maior! e logo atras vem " << ant->nome << endl;
                } else if (flag_ant && flag_suc) {
                    cout << atual->nome << " vem apos " << ant->nome << " e antes de " << suc->nome << endl;
                }
        }
    }
    liberar_arvore(raiz);
    return 0;
}

