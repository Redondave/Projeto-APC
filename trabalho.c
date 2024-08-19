#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Jogador {
    char nome[20];
    int pontuacao;
} Jogador;

int DIFICULDADE = 1;
int first = 1;

int initialScreen();
void begingame();
void displayconfig();
void displayranking();
int main()
{
    Jogador player;
    char temp;
    // perguntar o nome do usuário
    if (first)
    {
        printf("Digite Seu Nome: ");
        scanf("%[^\n]", player.nome);
        scanf("%c", &temp);
        first = 0;
    }
    initialScreen();
    return 0;
}

int initialScreen()
{
    system("cls");
    int escolha;
    char c;
    // mostrar o display da tela inicial
    printf("*** BEM VINDO ***\n");
    printf("\n1 - Jogar\n2 - Configuracoes\n3 - Ranking\n4 - Sair\n");
    printf("\nDigite a opcao desejada: ");
    while (1)
    {
    // obter o input do usuário para começar o jogo
        scanf("%i", &escolha);
        if (escolha == 4)
            exit(0);
        else if (escolha == 3)
            displayranking();
        else if (escolha == 2)
            displayconfig();
        else if (escolha == 1)
            begingame();
        else
        {   
            printf("Digite uma opcao existente!\n");
            printf("\nDigite a opcao desejada: ");
        }
    }
    return 0;
}

void begingame()
{
    // dar display da matriz (guardar numeros em uma matriz, acertos e erros em outra, e soma das linhas e colunas em vetores de char)
    // fazer o apagamento / erro
    // checar por linhas completas
    // checar por colunas completas
    // dar o clear na tela
    // continuar o jogo
    // salvar a pontuação no struct do usuario
    // ordenar o ranking
    // fechar o ranking e voltar para tela inicial
}

void displayconfig()
{
    system("cls");
    int escolha;
    char confirm;
    printf("*** CONFIGURACOES ***\n");
    printf("\n1 - Zerar ranking\n2 - Modo de dificuldade\n3 - Voltar ao menu\n");
    printf("\nDigite a opcao desejada: ");
    scanf("%i", &escolha);
    scanf("%c", &confirm);
    if (escolha == 3)
        initialScreen();
    else if (escolha == 2)
    {
        printf("Selecione o modo de dificuldade\n\n1 - Iniciante\n2 - Intermediario\n3 - Dificil\n");
        scanf("%i", &escolha);
        scanf("%c", &confirm);
        if (escolha < 1 || escolha > 3)
        {
            printf("Escolha uma dificuldade existente!\nPressione [Enter]...\n");
            scanf("%c", &confirm);
            displayconfig();
        }  
        else
        {
            DIFICULDADE = escolha;
            printf("Dificuldade alterada com sucesso!\nPressione [Enter]...\n");
            scanf("%c", &confirm);
            displayconfig();
        }
    }
    else if (escolha == 1)
    {
        printf("Voce quer apagar o ranking? [y/n]\n");
        scanf("%c", &confirm);
        scanf("%c", &confirm);
        if (tolower(confirm) == 'y')
        {
            FILE *fd = fopen("ranking.txt", "w");
            fclose(fd);
            printf("Ranking apagado com sucesso!\nPressione [Enter]...\n");
            scanf("%c", &confirm);
            displayconfig();
        }
        else if (tolower(confirm) == 'n')
            displayconfig();
        else
        {
            printf("Digite um caracter válido (y/n)!\nPressione [Enter]...\n");
            scanf("%c", &confirm);
            displayconfig();
        }
    }
    else 
    {
        printf("Escolha uma opcao existente!\nPressione [Enter]...\n");
        scanf("%c", &confirm);
        displayconfig();
    }
}

void displayranking()
{

}