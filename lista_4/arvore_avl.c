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
int balanceamentoAEsquerda(No **ppRaiz);
int balanceamentoADireita(No **ppRaiz);
int ehArvoreAvl(No *ppRaiz);
void limpaArvore(No *ppRaiz);
void printArvore(No *ppRaiz);

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

    limpaArvore(ppRaiz);

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

int balanceamentoAEsquerda(No **ppRaiz)
{
    int FB = fatorDeBalanceamento((*ppRaiz)->pEsquerda);

    if (FB >= 0)
    {
        rotacaoSimplesDireita(ppRaiz);
        printf("\nRotação simples à direita efetuada.\n");
        
        return 1;
    }
    else if (FB < 0)
    {
        rotacaoSimplesEsquerda(&((*ppRaiz)->pEsquerda));
        rotacaoSimplesDireita(ppRaiz);
        printf("\nRotação dupla à direita efetuada.\n");

        return 1;
    }

    return 0;
}

int balanceamentoADireita(No **ppRaiz)
{
    int FB = fatorDeBalanceamento((*ppRaiz)->pDireita);

    if (FB <= 0)
    {
        rotacaoSimplesEsquerda(ppRaiz);
        printf("\nRotação simples à esquerda efetuada.\n");

        return 1;
    }
    else if (FB > 0)
    {
        rotacaoSimplesDireita(&((*ppRaiz)->pDireita));
        rotacaoSimplesEsquerda(ppRaiz);
        printf("\nRotação dupla à esquerda efetuada.\n");

        return 1;
    }

    return 0;
}

int ehArvoreAvl(No *ppRaiz)
{
    int FB;
    FB = fatorDeBalanceamento(ppRaiz);

    if (ppRaiz == NULL)
    return 1;

    if (!ehArvoreAvl(ppRaiz->pEsquerda))
    return 0;

    if (!ehArvoreAvl(ppRaiz->pDireita))
    return 0;

    if ((FB > 1) || (FB < -1))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void limpaArvore(No *ppRaiz)
{
    if (ppRaiz == NULL)
    return;

    limpaArvore(ppRaiz->pEsquerda);
    limpaArvore(ppRaiz->pDireita);

    free(ppRaiz);
}

/*Para o segundo cenário. De acordo com o conteúdo da pagina:
https://stackoverflow.com/questions/3955680/how-to-check-if-my-avl-tree-implementation-is-correct*/

void segundoCenario()
{
    printf("\nCaso 1A:\n");
    primeiroCasoA();
    printf("\n\t--CASO 2A--\n");
    segundoCasoA();
    printf("\n\t--CASO 3A--\n");
    terceiroCasoA();
    printf("\n\t--CASO 1B--\n");
    primeiroCasoB();
    printf("\n\t--CASO 2B--\n");
    segundoCasoB();
    printf("\n\t--CASO 3B--\n");
    terceiroCasoB();
}

void primeiroCasoA()
{
    No *ppRaiz = NULL;
    int valor;

    valor = 20;
    insere(&ppRaiz, valor);
    valor = 4;
    insere(&ppRaiz, valor);
    
    printArvore(ppRaiz);
    
    if (ehArvoreAvl(ppRaiz))
    {
        printf("\nÉ uma árvore AVL.\n");
    }
    else
    {
        printf("\nNão é uma árvore AVL.\n");
    }

    printf("\n\n");

    valor = 15;
    insere(&ppRaiz, valor);

    printArvore(ppRaiz);

    if (ehArvoreAvl(ppRaiz))
    {
        printf("\nÉ uma árvore AVL.\n");
    }
    else
    {
        printf("\nNão é uma árvore AVL.\n");
    }

    limpaArvore(ppRaiz);
}

void segundoCasoA() 
{
  No *ppRaiz = NULL;
  int valor;

  valor = 20;  
  insere(&ppRaiz, valor);
  valor = 4;
  insere(&ppRaiz, valor);
  valor = 26;
  insere(&ppRaiz, valor);
  valor = 3;
  insere(&ppRaiz, valor);
  valor = 9;
  insert(&ppRaiz, valor);

  printArvore(ppRaiz);
  
  if (ehArvoreAvl(ppRaiz)) 
  {
    printf("\nÉ uma Árvore AVL.\n");
  } 
  else 
  {
    printf("\nNão é uma Árvore AVL.\n");
  }
  
  printf("\n\n");
  
  valor = 15;
  insere(&ppRaiz, valor);
  
  printArvore(ppRaiz);
  
  if (ehArvoreAvl(ppRaiz)) 
  {
    printf("\nÉ uma Árvore AVL.\n");
  } 
  else 
  {
    printf("\nNão é uma Árvore AVL.\n");
  }

  limpaArvore(ppRaiz);
}

void terceiroCasoA() 
{
  No *ppRaiz = NULL;
  int valor;

  valor = 20;
  insere(&ppRaiz, valor);
  valor = 4;
  insere(&ppRaiz, valor);
  valor = 26;
  insere(&ppRaiz, valor);
  valor = 3;
  insere(&ppRaiz, valor);
  valor = 9;
  insere(&ppRaiz, valor);
  valor = 2;
  insere(&ppRaiz, valor);
  valor = 7;
  insere(&ppRaiz, valor);
  valor = 11;
  insere(&ppRaiz, valor);
  valor = 21;
  insere(&ppRaiz, valor);
  valor = 30;
  insere(&ppRaiz, valor);
  
  printArvore(ppRaiz);
  
  if (ehArvoreAvl(ppRaiz)) 
  {
    printf("\nÉ uma Árvore AVL.\n");
  } 
  else 
  {
    printf("\nNão é uma Árvore AVL.\n");
  }
  
  printf("\n\n");
  
  valor = 15;
  insere(&ppRaiz, valor);
  
  printArvore(ppRaiz);
  
  if (ehArvoreAvl(ppRaiz)) 
  {
    printf("\nÉ uma Árvore AVL.\n");
  } 
  else 
  {
    printf("\nNão é uma Árvore AVL.\n");
  }
  
  limpaArvore(ppRaiz);
}

void primeiroCasoB() 
{
  No *ppRaiz = NULL;
  int valor;

  valor = 20;
  insere(&ppRaiz, valor);
  valor = 4;
  insere(&ppRaiz, valor);
  
  printArvore(ppRaiz);
  
  if (ehArvoreAvl(ppRaiz)) 
  {
    printf("\nÉ uma Árvore AVL.\n");
  } 
  else 
  {
    printf("\nNão é uma Árvore AVL.\n");
  }
  
  printf("\n\n");
  
  valor = 8;
  insere(&ppRaiz, valor);
  
  printArvore(ppRaiz);
  
  if (ehArvoreAvl(ppRaiz)) 
  {
    printf("\nÉ uma Árvore AVL.\n");
  } 
  else 
  {
    printf("\nNão é uma Árvore AVL.\n");
  }
  
  limpaArvore(ppRaiz);
}

void segundoCasoB() 
{
  No *ppRaiz = NULL;
  int valor;
 
  valor = 20;
  insere(&ppRaiz, valor);
  valor = 4;
  insere(&ppRaiz, valor);
  valor = 26;
  insere(&ppRaiz, valor);
  valor = 3;
  insere(&ppRaiz, valor);
  valor = 9;
  insere(&ppRaiz, valor);
 
  printArvore(ppRaiz);
 
  if (ehArvoreAvl(ppRaiz)) 
  {
    printf("\nÉ uma Árvore AVL.\n");
  } 
  else 
  {
    printf("\nNão é uma Árvore AVL.\n");
  }
  
  printf("\n\n");
  
  valor = 8;
  insere(&ppRaiz, valor);
  
  printArvore(ppRaiz);
  
  if (ehArvoreAvl(ppRaiz)) 
  {
    printf("\nÉ uma Árvore AVL.\n");
  } 
  else 
  {
    printf("\nNão é uma Árvore AVL.\n");
  }

  limpaArvore(ppRaiz);
}

void terceiroCasoB() 
{
  No *ppRaiz = NULL;
  int valor;

  valor = 20;
  insere(&ppRaiz, valor);
  valor = 4;
  insere(&ppRaiz, valor);
  valor = 26;
  insere(&ppRaiz, valor);
  valor = 3;
  insere(&ppRaiz, valor);
  valor = 9;
  insere(&ppRaiz, valor);
  valor = 2;
  insere(&ppRaiz, valor);
  valor = 7;
  insere(&ppRaiz, valor);
  valor = 11;
  insere(&ppRaiz, valor);
  valor = 21;
  insere(&ppRaiz, valor);
  valor = 30;
  insere(&ppRaiz, valor);
 
  printArvore(ppRaiz);
 
  if (ehArvoreAvl(ppRaiz)) 
  {
    printf("\nÉ uma Árvore AVL.\n");
  } 
  else 
  {
    printf("\nNão é uma Árvore AVL.\n");
  }
  
  printf("\n\n");
  
  valor = 8;
  insere(&ppRaiz, valor);
  
  printArvore(ppRaiz);
  
  if (ehArvoreAvl(ppRaiz)) 
  {
    printf("\nÉ uma Árvore AVL.\n");
  } 
  else 
  {
    printf("\nNão é uma Árvore AVL.\n");
  }
  
  limpaArvore(ppRaiz);
}

void printArvore(No *ppRaiz)
{
    if (ppRaiz != NULL)
    {
        printf("%d(", ppRaiz->valor);
        printArvore(ppRaiz->pEsquerda);
        printArvore(ppRaiz->pDireita);
        printf(")");
    }
}