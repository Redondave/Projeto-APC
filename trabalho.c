#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Jogador {
    char nome[20];
    int pontuacao;
} Jogador;

Jogador player;
int DIFICULDADE = 1;
int first = 1;
int vidas = 5;
int victory = 0;
int done = 0;
int x, y;
FILE *fd = NULL;
FILE *fp = NULL;
char star;
char mat_in[4][4], sum_in[2][8], cor_in[4][4];
char mat_it[6][6], sum_it[2][12], cor_it[6][6];
char mat_ad[7][7], sum_ad[2][14], cor_ad[7][7];

int initialScreen();
void load_m(FILE *fp, int size, char correct[size][size], char matriz[size][size], char sum[2][2 * size], char *file);
void begingame();
void game_loop(int size, char correct[size][size], char matriz[size][size], char sum[2][2 * size]);
void displayconfig();
void displayranking();
int main()
{
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
    //(guardar numeros em uma matriz, corretos, e soma das linhas e colunas em vetores de char)
    if (DIFICULDADE == 1)
    {
        char *name = "iniciante.txt";
        load_m(fp, 4, cor_in, mat_in, sum_in, name);
        game_loop(4, cor_in, mat_in, sum_in);
    }
    else if (DIFICULDADE == 2)
    {
        char *name = "intermediario.txt";
        load_m(fp, 6, cor_it, mat_it, sum_it, name);
        game_loop(6, cor_it, mat_it, sum_it);
    }
    else
    {
        char *name = "avancado.txt";
        load_m(fp, 7, cor_ad, mat_ad, sum_ad, name);
        game_loop(7, cor_ad, mat_ad, sum_ad);
    }
    // salvar a pontuação no struct do usuario
    // ordenar o ranking
    // fechar o ranking e voltar para tela inicial
}

void game_loop(int size, char correct[size][size], char matriz[size][size], char sum[2][2 * size])
{
    char conf;
    int points;
    char aux[3];
    while(vidas > 0 || victory == 0)
    {
        // dar o clear na tela
        system("cls");
        int index = 0;
        // dar display da matriz
        for (int i = 0; i < size; i++)
        {
            if (i == 0)
            {
                printf("  *  ");
                for (int j = 0; j < (size * 2); j += 2)
                    printf(" %c%c", sum[0][j], sum[0][j + 1]);
                printf("\n");
                printf("      ");
                for (int j = 0; j < size; j++)
                    printf("__ ");
                printf("\n");
            }
            printf("%c%c |", sum[1][index], sum[1][index + 1]);
            for (int j = 0; j < size; j++)
            {
                printf("  %c", matriz[i][j]);
            }
            printf("\n");
            index += 2;
        }
        printf("\n** VIDAS: %i **\n", vidas);
        printf("Escolha a linha e coluna a serem apagadas: ");
        scanf("%i %i", &x, &y);
        x--;
        y--; 
        // fazer o apagamento / erro
        if (correct[x][y] == '0')
        {
            printf("Parabens, voce apagou um numero certo!\n");
            scanf("%c", &conf);
            matriz[x][y] = ' ';
            // checar por linhas completas
            for (int i = 0; i < size; i++)
            {
                if (matriz[x][i] != ' ')
                    points += (matriz[x][i] - 48);
            }
            aux[0] = sum[1][y];
            aux[1] = sum[1][y + 1];
            aux[2] = '\0';
            if (points == (atoi(aux)))
            {
                printf("\nParabens, voce fechou uma linha!\n");
                done++;
                sum[1][y] = ' ';
                sum[1][y + 1] = ' ';
            }
            // checar por colunas completas
            for (int i = 0; i < size; i++)
            {
                if (matriz[i][y] != ' ')
                    points += (matriz[x][i] - 48);
            }
            aux[0] = sum[0][x];
            aux[1] = sum[0][x + 1];
            aux[2] = '\0';
            if (points == (sum[0][x] + sum[0][x + 1] - 96))
            {
                printf("\nParabens, voce fechou uma coluna!\n");
                done++;
                sum[1][x] = ' ';
                sum[1][x + 1] = ' ';
            }
            printf("Pressione [Enter]...");
            scanf("%c", &conf);
        }
        else
        {
            printf("Errou! Tente de novo...\n");
            printf("Pressione [Enter]...");
            scanf("%c", &conf);
            vidas--;
        }
        // checar condição de vitoria
        if (done == (size * 2))
        {
            printf("Parabéns, Voce ganhou o jogo!\nPressione [Enter]...");
            scanf("%c", &conf);
            player.pontuacao += (DIFICULDADE * 50);
        }
        points = 0;
        // continuar o jogo
    }
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
            if (fp != NULL)
                fclose(fp);
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
            fd = fopen("ranking.txt", "w");
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
    printf("*** RANKING ***\n\n");
    char confirm, nome[20];
    int pont;
    fd = fopen("ranking.txt", "r");
    while (fscanf(fd, "%s %i", nome, &pont) != EOF)
    {
        printf("%s %i\n", nome, pont);
    }
    scanf("%c", &confirm);
    fclose(fd);
    printf("\nPressione [Enter]...\n");
    scanf("%c", &confirm);
    initialScreen();
}

void load_m(FILE *fp, int size, char correct[size][size], char matriz[size][size], char sum[2][2 * size], char* name)
{
    if (fp == NULL)
        fp = fopen(name, "r");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            fscanf(fp, "%c", &matriz[i][j]);
        fscanf(fp, "%c", &star);
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
            fscanf(fp, "%c", &sum[i][j]);
        fscanf(fp, "%c", &star);
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            fscanf(fp, "%c", &correct[i][j]);
        fscanf(fp, "%c", &star);
    }
    fscanf(fp, "%c", &star);
}