#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct{
    char nome[30];
    int idade;
    float altura;
}Pessoa;

int main()
{
    int escolha, contador = 0;
    Pessoa *agenda = NULL;
    int i;
    
    printf("Deseja incluir dados de uma pessoa na agenda? (1-SIM E 2-NÃO)\n");
    scanf("%d", &escolha);
	
	while(escolha < 1 || escolha > 2)
        {
            printf("Digite uma escolha válida!\n");
            printf("Deseja incluir dados de uma pessoa na agenda? (1-SIM E 2-NÃO)\n");
            scanf("%d", &escolha);
        }
	    
    while(escolha == 1)
    {
        if (contador == 0)
        {
            agenda = (Pessoa *)malloc(sizeof(Pessoa));
        }
        else
        {
            agenda = (Pessoa *)realloc(agenda, (contador + 1) * sizeof(Pessoa)); 
        }
        
        if (agenda == NULL)
        {
            printf("ERRO: Sem memória.\n");
            exit(1);
        }

        printf("Informe o nome da Pessoa: ");
        scanf("%s", agenda[contador].nome);
        printf("Informe a idade: ");
        scanf("%d", &agenda[contador].idade);
        printf("Informe a altura: ");
        scanf("%f", &agenda[contador].altura);
        contador++;
        
        getchar();
        
        printf("Deseja incluir dados de outra pessoa na agenda? (1-SIM E 2-NÃO)\n");
    	scanf("%d", &escolha);
	
		while(escolha < 1 || escolha > 2)
        {
            printf("Digite uma escolha válida!\n");
            printf("Deseja incluir dados de outra pessoa na agenda? (1-SIM E 2-NÃO)\n");
            scanf("%d", &escolha);
        }
	}
	
	if (contador == 0)
        {
         printf("Não havia pessoas cadastradas na agenda.\n");
        }
    else
    	{
		 printf("\nAGENDA:\n");
    	 for (i = 0; i < contador; i++)
            {
                printf("%d° USUÁRIO:\n", i + 1);
                printf("NOME: %s\n", agenda[i].nome);
                printf("IDADE: %d\n", agenda[i].idade);
                printf("ALTURA: %.2f\n", agenda[i].altura);
            }
            
         free(agenda);
        }    
    
    return 0;
}