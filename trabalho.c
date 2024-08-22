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
int done = 0;
int games = 0;
long offset = 0;
int x, y;
FILE *fd = NULL;
FILE *fp = NULL;
char star;
char mat_in[4][4], sum_in[2][8], cor_in[4][4];
char mat_in2[5][5], sum_in2[5][5], cor_in2[5][5];
char mat_it[6][6], sum_it[2][12], cor_it[6][6];
char mat_ad[7][7], sum_ad[2][14], cor_ad[7][7];

int initialScreen();
void load_m(FILE *fp, int size, char correct[size][size], char matriz[size][size], char sum[2][2 * size], char *file);
void begingame();
void game_loop(int size, char correct[size][size], char matriz[size][size], char sum[2][2 * size]);
void displayconfig();
void displayranking();
void rankingUpdate();
int compare(const void *a, const void *b);
int main()
{
    char temp;
    // perguntar o nome do usuário
    if (first)
    {
        printf("Digite Seu Nome: ");
        scanf("%[^\n]", player.nome);
        scanf("%c", &temp);
        player.pontuacao = 0;
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
        {
            if (fp != NULL)
                fclose(fp);
            if (fd != NULL)
                fclose(fd);
            exit(0);
        }
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
    if (games == 4)
    {
        games = 0;
        fclose(fp);
        DIFICULDADE++;
    }
    if (DIFICULDADE == 1)
    {
        char *name = "iniciante.txt";
        int size = (games == 3) ? 5 : 4;
        if (games == 3)
            load_m(fp, 5, cor_in2, mat_in2, sum_in2, name);
        else
            load_m(fp, 4, cor_in, mat_in, sum_in, name);
        game_loop(size, cor_in, mat_in, sum_in);
    }
    else if (DIFICULDADE == 2)
    {
        char *name = "intermediario.txt";
        load_m(fp, 6, cor_it, mat_it, sum_it, name);
        game_loop(6, cor_it, mat_it, sum_it);
    }
    else if (DIFICULDADE == 3)
    {
        char *name = "avancado.txt";
        load_m(fp, 7, cor_ad, mat_ad, sum_ad, name);
        game_loop(7, cor_ad, mat_ad, sum_ad);
    }
    else
    {
        printf("Parabens!! Voce zerou o jogo!\nPressione [Enter]...\n");
        scanf("%c", &star);
        exit(0);
    }
}

void game_loop(int size, char correct[size][size], char matriz[size][size], char sum[2][2 * size])
{
    char conf;
    int scores = 0;
    int aux;
    while(vidas > 0)
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
            correct[x][y] = ' ';
            scanf("%c", &conf);
            matriz[x][y] = ' ';
            // checar por linhas completas
            for (int i = 0; i < size; i++)
            {
                if (correct[x][i] == '0')
                    scores++;
            }
            if (scores == 0)
            {
                printf("\nParabens, voce fechou uma linha!\n");
                done++;
                sum[1][(x * 2)] = ' ';
                sum[1][(x * 2) + 1] = ' ';
            }
            scores = 0;
            // checar por colunas completas
            for (int i = 0; i < size; i++)
            {
                if (correct[i][y] == '0')
                    scores++;
            }
            if (scores == 0)
            {
                printf("\nParabens, voce fechou uma coluna!\n");
                done++;
                sum[0][(y * 2)] = ' ';
                sum[0][(y * 2) + 1] = ' ';
            }
            scores = 0;
            printf("Pressione [Enter]...");
            scanf("%c", &conf);
        }
        else
        {
            printf("Errou! Tente de novo...\n");
            printf("Pressione [Enter]...\n");
            scanf("%c", &conf);
            scanf("%c", &conf);
            vidas--;
        }
        // checar condição de vitoria
        if (done == (size * 2))
        {
            printf("Parabens, Voce ganhou o jogo!\nPressione [Enter]...");
            scanf("%c", &conf);
            // salvar a pontuação no struct do usuario
            player.pontuacao += (DIFICULDADE * 50);
            games++;
            done = 0;
            break;
        }
        // continuar o jogo
    }
    if (vidas == 0)
    {
        printf("As vidas acabaram... tente de novo outra vez\nPressione [Enter]...");
        scanf("%c", &conf);
    }
    vidas = 5;
    rankingUpdate();
    initialScreen();
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
        printf("\nDificuldade: ");
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
            games = 0;
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

void load_m(FILE *arquivo, int size, char correct[size][size], char matriz[size][size], char sum[2][2 * size], char* name)
{
    if (arquivo == NULL)
    {
        arquivo = fopen(name, "r");
        offset = 0;
    }
    else
        fseek(arquivo, offset, SEEK_SET);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fread(&matriz[i][j], sizeof(char), 1, arquivo);
            offset++;
        }
        fread(&star, sizeof(char), 1, arquivo);
        offset++;
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < size * 2; j++)
        {
            fread(&sum[i][j], sizeof(char), 1, arquivo);
            offset++;
        }
        fread(&star, sizeof(char), 1, arquivo);
        offset++;
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fread(&correct[i][j], sizeof(char), 1, arquivo);
            offset++;
        }
        fread(&star, sizeof(char), 1, arquivo);
        offset++;
    }
    fread(&star, sizeof(char), 1, arquivo);
    fread(&star, sizeof(char), 1, arquivo);
    offset += 2;
}

void rankingUpdate()
{
    Jogador a;
    int plrnumber = 0, found = 0;
    if (fd != NULL)
        fclose(fd);
    fd = fopen("ranking.txt", "r");
    while(fread(&a, sizeof(Jogador), 1, fd) != EOF)
    {
        plrnumber++;
        if (strcmp(a.nome, player.nome) == 0)
            plrnumber--;
    }
    plrnumber++;
    Jogador current[plrnumber];
    fclose(fd);
    fd = fopen("ranking.txt", "r");
    for (int i = 0; i < plrnumber; i++)
    {
        fread(&current[i], sizeof(Jogador), 1, fd);
        if (strcmp(current[i].nome, player.nome) == 0)
        {
            found = 1;
            current[i].pontuacao += player.pontuacao;
        }
    }
    if (!found)
        current[plrnumber - 1] = player;
    else
        found = 0;
    fclose(fd);
    // ordenar o ranking
    qsort(&current[0], plrnumber, sizeof(Jogador), compare);
    fd = fopen("ranking.txt", "w");
    for (int i = 0; i < plrnumber; i++)
    {
        fwrite(&current[i], sizeof(Jogador), 1, fd);
    }
    // fechar o ranking e voltar para tela inicial
    fclose(fd);
    return;
}

int compare(const void *a, const void *b)
{
    int p1 = ((Jogador*)a)->pontuacao;
    int p2 = ((Jogador*)b)->pontuacao;
    if (p1 < p2)
        return 1;
    return -1;
}
