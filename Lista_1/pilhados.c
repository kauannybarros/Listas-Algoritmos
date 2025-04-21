//https://iudex.io/problem/654ccbdfe0c9bd0001fd509f/statement

#include <stdio.h>
#include <stdlib.h>

int paridade(int a, int b) {
    return ((a % 2 == 0 && b % 2 == 0) || (a % 2 != 0 && b % 2 != 0));
}

int main() {
    int t;
    scanf("%d", &t);
    
    int respostas[t][2];
    
    for (int i = 0; i < t; i++) {
        int valor;
        int flag = 0;
        int *pilha = NULL;

        while (scanf("%d", &valor) && valor != 0) {
            flag++;
            int *nova_pilha = realloc(pilha, flag * sizeof(int));
            if (nova_pilha == NULL) {
                free(pilha);
                return 1;
            }
            pilha = nova_pilha;
            pilha[flag - 1] = valor;

            while (flag > 1 && paridade(pilha[flag - 1], pilha[flag - 2])) {
                int subs = abs(pilha[flag - 1] - pilha[flag - 2]);

                if (subs == 0) {
                    flag -= 2;
                } else {
                    pilha[flag - 2] = subs;
                    flag--;
                }
            }
        }

        if (flag == 0) {
            respostas[i][1] = -1;
            respostas[i][0] = 0;
        } else {
            respostas[i][1] = pilha[flag - 1]; // topo da pilha
            respostas[i][0] = flag; // quantidade de elementos
        }

        free(pilha);
    }

    for (int i = 0; i < t; i++) {
        printf("Pilha %d: %d %d\n", i + 1, respostas[i][0], respostas[i][1]);
    }

    return 0;
}
