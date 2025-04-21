//https://iudex.io/problem/6234ff9a3f99be0001bcf002/statement

//VERSAO COMPLETA COM RNK
#include <iostream>
#include <string>
#include <sstream> 

using namespace std;

/*
Oq precisa fazer:

ADD X W - Adiciona o no na arvore e imprime o total global (soma de todos os nos)
WEI X - imprime dois inteiros W D (WEI(X) e profundidade do no X) obs: se ainda nao tiver nada, imprime 0 -1
RNK X - imprime o total transmitidos por nos < X (pode nao ter um no X mas deve contabilizar do mesmo jeito)

*/

struct no_arvore{
    int id;
    int wei;
    int rnk;
    int altura;
    no_arvore *esq;
    no_arvore *dir;
};

no_arvore *criar_no(int id, int wei) {
    no_arvore *novo = new no_arvore;
    novo->id = id;
    novo->wei = wei;
    novo->rnk = 0;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->altura = 1;

    return(novo);
}


int altura_no(no_arvore *no) {
    if (no == NULL) return 0;
    else return no->altura;
}

int maior(int a, int b) {
    return (a > b) ? a : b;
}

int rnk(no_arvore *no) {
    if (no==NULL) return 0;
    return no->wei + no->rnk + rnk(no->dir);
}

int fatorB(no_arvore *no) {
    if(no == NULL) return 0;
    else return (altura_no(no->esq) - altura_no(no->dir)); //altura da sub esq - altura sub dir
}

no_arvore *rotacaoEsq (no_arvore *no) {
    no_arvore *x = no->dir;
    no_arvore *y = x->esq;

    x->esq = no;
    no->dir = y;

    no->altura = maior(altura_no(no->esq), altura_no(no->dir)) + 1;
    x->altura = maior(altura_no(x->esq), altura_no(x->dir)) + 1;

    no->rnk = rnk(no->esq);
    x->rnk = rnk(x->esq);


    return x;
}

no_arvore *rotacaoDir (no_arvore *no) {
    no_arvore *x = no->esq;
    no_arvore *y = x->dir;

    x->dir = no;
    no->esq = y;

    no->altura = maior(altura_no(no->esq), altura_no(no->dir)) + 1;
    x->altura = maior(altura_no(x->esq), altura_no(x->dir)) + 1;

    no->rnk = rnk(no->esq);
    x->rnk = rnk(x->esq);

    return x;
}
/*
Fazer q nem Pierre falou: armazenar o rnk das arvores a esquerda em cada no
Entao, a cada no que for adicionado, ir calculando*/
no_arvore *adicionar_no(no_arvore *no, int id, int wei) {
    if (no == NULL) {
        return(criar_no(id,wei));
    }

    if (id < no->id) {
       no->esq = adicionar_no(no->esq, id, wei); 
    } 
    else if(id > no->id) {
        no->dir = adicionar_no(no->dir, id, wei);
    } 
    else { //se for id igual
        no->wei += wei;
    }

    //ajeitar a altura
    no->altura = 1 + maior(altura_no(no->esq), altura_no(no->dir));
    //ajeitar rank
    no->rnk = rnk(no->esq);
    //ajeitar balanceamento
    int b = fatorB(no);

    if (b > 1 && id < no->esq->id) {
        return rotacaoDir(no);
    }

    if (b < -1 && id > no->dir->id) {
        return rotacaoEsq(no);
    }

    if (b > 1 && id > no->esq->id) {
        no->esq = rotacaoEsq(no->esq);
        return rotacaoDir(no);
    }

    if (b < -1 && id < no->dir->id) {
        no->dir = rotacaoDir(no->dir);
        return rotacaoEsq(no);
    }

    return no;
}

void WEI(no_arvore *raiz, int X) {
    //tem q imprimir o wei de x e a profundidade
    int prof = 0;
    int flag = 1; //flag pra saber se realmente tem 
    no_arvore *atual = raiz;
    //mesma coisa que uma busca mas tem q ver onde ta

    while(atual != NULL && atual->id != X && flag) {
        if (X < atual->id && atual->esq != NULL) {
            prof++;
            atual = atual->esq;
        } else if (X > atual->id && atual->dir != NULL) {
            prof++;
            atual = atual->dir;
        }
        
        else flag = 0; 
        //oq vai acontecer: se n for null, ainda nao for o id que procura, o no.esq ou no.dir for NULL, quer dizer q nao tem ainda essa maquina aqui. entao, flag vai pra 0 e quebra o loop
    }

    if(flag) {
        //se quebrou o loop e a flag continua como verdadeira, entao achou alguma coisa
        cout << atual->wei << " " << prof << endl;
    }

    else {
        //quebrou o loop e a flag = 0, nao tem esse numero na arvore ainda
        cout << "0 -1" << endl;
    }
}

int RNK (no_arvore *no, int id) {
    if (no == NULL) return 0;

    if (id <= no->id) return RNK(no->esq, id);
    return no->wei + no->rnk + RNK(no->dir, id);
}

int main () {

    string acao;
    int pont_global = 0;
    no_arvore *raiz = NULL;

    while (getline(cin, acao) && acao != "END") {
        int id;
        int wei;

        stringstream ss(acao);
        string comando;
        ss >> comando;
        
        if(comando == "ADD") {
            ss >> id;
            ss >> wei;

            raiz = adicionar_no(raiz, id, wei);

            pont_global += wei;
            
            cout << pont_global << endl;
        }

        else if(comando == "WEI") {
            ss >> id;

            WEI(raiz, id);
        }

        else if(comando == "RNK") {
            ss >> id;
            int resultado = RNK(raiz,id);
            cout << resultado << endl;
        }
    }

    return 0;
}
