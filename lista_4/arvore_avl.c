#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct No
{
    int valor;
    struct No *pEsquerda;
    struct No *pDireita;        
} No;

void Insere(No **ppRaiz, int valor);

int main()
{
    int quantidadeDeNos, cont, valor;
    cont = 0;
    No *ppRaiz = NULL;

    printf("Informe a quantidade de nós que deseja inserir: ");
    scanf("%d", &quantidadeDeNos);

    srand(time(0));

    while (cont < quantidadeDeNos)
    {
        valor = rand() % 100;
        printf("\nValor sorteado: %d\n", valor);
        Insere(&ppRaiz, valor);
        cont++;
    }

    if (ehArvoreAvl(ppRaiz))
    {
        printf("\n\nÉ uma árvore AVL.\n\n");
    }
    else
    {
        printf("\n\nNão é uma árvore AVL.\n\n");
    }

    return 0;
}

void Insere(No **ppRaiz, int valor)
{
    if (*ppRaiz == NULL)
    {
        *ppRaiz = (No *)malloc(sizeof(No));
        (*ppRaiz).valor = valor;
        (*ppRaiz).pEsquerda = NULL;
        (*ppRaiz).pDireita = NULL;
        
        return 1;
    }
    else if ((*ppRaiz).valor > valor)
    {
        if (Insere(&(*ppRaiz).pEsquerda, valor))
            {
                if (balance(ppRaiz))
                {
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
    }
    else
    {
        printf("\nValor já consta na árvore.\n");
        return 0;
    }
}

int Balanceamento(No **ppRaiz)
{
    int fb = fatorDeBalanceamento(*ppRaiz);

    if (fb > 1)
    {
        return balanceamentoAEsquerda(ppRaiz);
    }
    else if (fb < -1)
    {
        return balanceamentoADireita(ppRaiz);
    }
    else
    {
        return 0;
    }
}