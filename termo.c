#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define NORMAL  "\x1b[0m"
#define PALAVRINHA 5

static char manga[PALAVRINHA + 1];

static const char *DICIONARIO[] = 
{
    "abaco","abalo","abana","abate","abuso",
    "acaba","acaso","acima","acude","adaga",
    "adota","afeto","afina","agudo","agora",
    "aguas","alado","aluno","amigo","amora",
    "amado","amena","anexo","antes","apito",
    "apego","apolo","aroma",
    "artes","asilo","astro","atual","atuar",
    "audio","aulas","autor","aviso","azedo",
    "bacon","banco","barco","beijo","belas",
    "betas","bicho","bolas","bolso","bonus",
    "brisa","broto","bruto","bucha","burro",
    "caixa","calor","campo","canal","canto",
    "capaz","capim","carro","carta","casal",
    "casas","casco","cesta","chave","chefe",
    "chuva","claro","coisa","cofre","corpo",
    "corte","coral","criar","crime","crise",
    "curva","custo","dado","dança","deixa",
    "delta","dente","dolar","drama","dupla",
    "edito","elite","emite","exame",
    "exito","falar","favor","feira","festa",
    "fluir","folha","força","forma","gesto",
    "forte","frota","fruta","fugir","funil",
    "fundo","fúria","galho","ganha","garra",
    "gasto","gente","girar","globo","gozar",
    "grito","grupo","guapo","gueto","guiar",
    "haver","hotel","humor","ideal",
    "igual","irmão","jogar",
    "jovem","juizo","lados","lambo","lança",
    "largo","lazer","leite","legal","lento",
    "lerdo","leste","livro","local","longo",
    "louro","luzes","macro","malha","malta",
    "manga","manto","mapas","marca","marco",
    "marte","massa","matiz","meiga","meigo",
    "melão","meios","menos","mesas","metro",
    "miolo","moeda","molha","monte","morro",
    "motim","mover","mundo","musas","museu",
    "muita","muito","mutua","natal","naval",
    "navio","negro","nesta","nivel","nobre",
    "noite","nomes","norte","plano","pombo",
    "porta","ponto","prato","preto","primo",
    "quase","quilo","ramos","rapaz",
    "renda","repor","risco","rocha","rolar",
    "rosas","roupa","ruido","salto","santo",
    "sabor","serra","serto","setor",
    "sinal","sorte","suaço","suave",
    "tarde","tarso","tenta","termo","tigre",
    "tinta","torre","trama","trevo","trigo",
    "troca","trono","trufa","tumor","turma",
    "úmido","vacas","valer","valor","vapor",
    "vasto","velas","velho","vento","verbo",
    "verde","vigor","visto","viver","vozes"
};

enum { tamanho = sizeof(DICIONARIO)/sizeof(DICIONARIO[0]) };


static void iniciarSorteio(void)
{
    static int algumaCoisa = 0;
    if (!algumaCoisa)
    {
        srand((unsigned) time(NULL));
        algumaCoisa = 1;
    }
}

static void palavraPorQual(int qual)
{
    strncpy(manga, DICIONARIO[qual], PALAVRINHA);
    manga[PALAVRINHA] = '\0';
}

void sorteiaPalavra(void)
{
    iniciarSorteio();
    int qual;
    qual = (int)(rand() %tamanho);
    palavraPorQual(qual);
}

static int verAmarelo (int j, const char comparacao[6])
{
    int i;
    for (i = 0; i < PALAVRINHA; i++)
    {
        if (comparacao[j] == manga[i])
        {
            return 1;
        } 
    }
    return 0;
}

static int verErros(char palavra[6])
{
    int i, flag = 0;

    for (i = 0; i < 5; i++)
    {

        if (palavra[i] == manga[i])     //palavra aqui, comparacao no main
        {
            printf(GREEN "%c" NORMAL, palavra[i]);
            flag++;
        }

        else if (verAmarelo(i, palavra) == 1) 
        {
            printf(YELLOW "%c" NORMAL, palavra[i]);
        }

        else
        {
            printf(RED "%c" NORMAL, palavra[i]);
        }
    }
    printf("\n");

    if (flag == 5)
    {
        return 1;
    }
    
    else 
    {
        return 0;
    }
} 


int main()
{
    setlocale(LC_ALL, "Portuguese");

    sorteiaPalavra();

    int flag = 5, acertou = 0, i;
    char palavra [PALAVRINHA + 1], comparacao[PALAVRINHA + 1];
    printf("\nTERMO\n");
    printf("Regras:\n");
    printf(GREEN "Verde para letra correta no lugar correto\n");
    printf(RED "Vermelho para letra errada\n" NORMAL);
    printf(YELLOW "Amarelo para posição errada da letra\n\n");
    printf(GREEN "SEM " RED "ACENTOS\n\n" NORMAL);
    printf("Você tem 5 tentativas\n");
    system("pause");
    system("cls");
    printf("Digite uma palavra de 5 letras:\n");

    do
    {
        printf("Você tem %d tentativas\n", flag);
        fflush(stdin);
        scanf("%5s", palavra);
        for (i = 0; i < PALAVRINHA; i++)
        {
            comparacao[i] = (char) tolower((unsigned char) palavra[i]);
        }

        if (verErros(comparacao) == 1)
        {
            acertou = 1;
            break;
        }

        flag --;

    } while (flag > 0);

    if (acertou == 1)
    {
        printf("ACERTOU! \n");
    }
    else
    {
        printf("JUMENTO ANIMAL BURRÃO\n");
    }
    system("pause");

    return 0;
}