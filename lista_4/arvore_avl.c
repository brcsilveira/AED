#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct No
{
    int valor;
    struct No *pEsquerda;
    struct No *pDireita;        
} No;

int insere(No **ppRaiz, int valor);
int balanceamento(No **ppRaiz);
int fatorDeBalanceamento(No *pRaiz);
int altura(No *pRaiz);
void rotacaoSimplesEsquerda(No **ppRaiz);
void rotacaoSimplesDireita(No **ppRaiz);

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
        insere(&ppRaiz, valor);
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

int insere(No **ppRaiz, int valor)
{
    if (*ppRaiz == NULL)
    {
        *ppRaiz = (No *)malloc(sizeof(No));
        (*ppRaiz)->valor = valor;
        (*ppRaiz)->pEsquerda = NULL;
        (*ppRaiz)->pDireita = NULL;
        
        return 1;
    }
    else if ((*ppRaiz)->valor > valor)
    {
        if (insere(&(*ppRaiz)->pEsquerda, valor))//pq da erro com o "."
            {
                if (balanceamento(ppRaiz))
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

int balanceamento(No **ppRaiz)
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

int fatorDeBalanceamento(No *pRaiz)
{
    if (pRaiz == NULL)
    {
        return 0; 
    }

    return altura(pRaiz->pEsquerda) - altura(pRaiz->pDireita);
}

int altura(No *pRaiz)
{
    int direita, esquerda;

    if (pRaiz == NULL)
    {
        return 0;
    }

    esquerda = altura(pRaiz->pEsquerda);
    direita = altura(pRaiz->pDireita);

    if (esquerda > direita)
    {
        return esquerda + 1;
    }
    else
    {
        return direita + 1;
    }
}

void rotacaoSimplesEsquerda(No **ppRaiz)
{
    No *pAuxiliar;

    pAuxiliar = (*ppRaiz)->pDireita;
    (*ppRaiz)->pDireita = pAuxiliar->pEsquerda;
    pAuxiliar->pEsquerda = (*ppRaiz);
    (*ppRaiz) = pAuxiliar;
}

void rotacaoSimplesDireita(No **ppRaiz)
{
    No *pAuxiliar;

    pAuxiliar = (*ppRaiz)->pEsquerda;
    (*ppRaiz)->pEsquerda = pAuxiliar->pDireita;
    pAuxiliar->pDireita = (*ppRaiz);
    (*ppRaiz) = pAuxiliar;
}