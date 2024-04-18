#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
/*Você deve implementar um jogo “parecido” com o jogo da forca. No
jogo, o usuário irá escolher uma palavra existente em uma base de
dados (fornecida pelo professor) e o programa deverá “adivinhar”
qual é a palavra escolhida.*/

//variaveis globais
int contadordetentativa = 0, Tamanhopalavra, erros = 0, quantidadeParquivo = 0, QtdLetrasPalavras = 0, QtdChutes = 0, *posLetra;
char voga[5] = {'a', 'e', 'i', 'o', 'u'}, alfabeto[21] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'}; //vogal e alfabeto
char **matriz, palavra, ChuteVogal, *palavraSecreta;//,matriz com duplo ponteiro,porque ela vai ter um vetor de ponetiro,e cada ponteiro vai apontar para uma string
char *GuardaChute;
int pesoDasVogais[5], pesoDasConsoantes[21];
int Achei_a_Vogal[5], Achei_a_Consoantel[21];
void palavraSorteada(char letraChute);

void LerArquivo() //abri e ler o arquivo,como nao pode mudar nada nele e nem criar outro,entao vamos usar o r,so pra ler o arquivo
{
    char PalavraSelecionada[46]; //Maior palavra do mundo do tem 46 letras
    int TamanhopalavraAtual;     //tamanho da palavra no momento atual
    FILE *arq;
    arq = fopen("br-sem-acentos.txt", "r"); //abrindo o aquivo
    if (arq == NULL)                        //se nao exixte o arquivo
    {
        printf("===================================================================\n");
        printf("Erro no arquivo\n");
        printf("===================================================================\n");
    }
    while (!feof(arq)) //feof serve pra pecorre ate o fim do arquivo
    {
        fscanf(arq, "%s",PalavraSelecionada);          //lendo a primeira palavra
        TamanhopalavraAtual = strlen(PalavraSelecionada); //tamanho da palavra igual srtlen que e igual o tamnho da palavra seleicona
        if (TamanhopalavraAtual == Tamanhopalavra)        //Vai entra aqui se o tamanho da palavra for igual o tamanho selecionado
        {
            if (quantidadeParquivo == 0) //so vai entra se nao existir,ai vai criar
            {
                matriz = (char **)malloc((quantidadeParquivo + 1) * sizeof(char *));  //criando o comeco da matriz,com o primeiro ponteiro que vai apontar para a primeira linha
                matriz[quantidadeParquivo] = malloc((Tamanhopalavra) * sizeof(char)); //alocando de acordo com o tamanho da palavra que o usuario escolheu,pegando a quantidade de caracter
                strcpy(matriz[quantidadeParquivo], PalavraSelecionada);               //enchendo a string com a palavra selcionada de acordo com a quantidade de caracter
                quantidadeParquivo++;                                                 //acrescentando no numero da palavra
            }
            else
            {
                matriz = (char **)realloc(matriz, (quantidadeParquivo + 1) * sizeof(char *)); //realocando para poder aumentar o tamanho da matriz,acrescentando novas palavras
                matriz[quantidadeParquivo] = malloc((Tamanhopalavra) * sizeof(char));         //alocando a quantidade de espaco para a string
                strcpy(matriz[quantidadeParquivo], PalavraSelecionada);
                quantidadeParquivo++;
            }
        }
    }
}
void tracoPalavra(char PalavracomTraco[Tamanhopalavra]) //traco da focar,para o usuario ir informando a posicao da palavra e ir troca pelo traco
{
    int i;
    for (i = 0; i < Tamanhopalavra; i++) //for para pecorre
    {
        PalavracomTraco[i] = '-'; //trocando o numero de caracter por traco
    }
    PalavracomTraco[Tamanhopalavra] = '\0';
}

int comeco() //fiz em int para retorna o tamanho da palavra
{
    printf("===================================================================================\n"); //formatacao do programa
    printf("\t\t  ||JOGO DA FORCA||\n");
    printf("\t\t**Escolha a palavra**\n"); //indicando para o usuario escolher a palavra no arquivo
    printf("**|Presione enter para abrir o arquivo base...");
    getchar();                                                                                         //para nao abrir o arquivo direto
    system("call br-sem-acentos.txt");                                                                 //abri o arquivo para pessoa escolher a palavra,para ficar um progama mais funciona e bonito
    printf("**|Qual o tamanho da palavra selecionada: ");                                              //tamanho da palavra selecionada
    scanf("%d", &Tamanhopalavra);                                                                      //pegando a quantidade de letra que a palavra tem
    palavraSecreta = calloc(Tamanhopalavra + 1, sizeof(char));                                         //calloc para forma ela depois
    printf("\n===================================================================================\n"); //formatacao do programa
    return Tamanhopalavra;                                                                             //retornando o tamanho da palavra
}

void menu() //menu da forca,e void pois ira aparecer ate a maquina advinha a palavra
{
    printf("\t\t  ||JOGO DA FORCA||");
    printf("\n===================================================================================\n"); //formatacao do programa
    printf("**|Numero de tentativas\t\t-> %d\n", contadordetentativa);                                 //contador de numeros de tentativas da maquina,em todos os chutes
    printf("**|Erros\t\t\t-> %d\n", erros);                                                            //contador de erros,so ira contabilizar quando a maquina chuta uma palavra que nao tem
    printf("**|Quantidade de palavras\t-> %d\n", quantidadeParquivo);                                  //contador de palavras que tem no arquivo do professor
    printf("**|Palavra secreta\t\t-> %s \n", palavraSecreta);                                          //puxar os tracos,formatacao
}

int Verifica_Letra_Palavra(int tamanhoPalavra, int posPalavra, int *posLetra, char l) //verifica letra palavra
{
    for (int k = 0; k < tamanhoPalavra; k++) //pecorrer o tamanho da palavra
    {
        if (tolower(matriz[posPalavra][posLetra[k] - 1]) == l) //pega a matriz na posicao da palavra e na posicao critica
        {
            continue;
        }
        else
        {
            return 0;
        }
    }

    return 1; //se for veridico retorna 1
}

//inicio dos chutes da maquinas,so pode sair daqui quando encontrar uma vogal
//vogais,a maquina tem que comeca os chutes pelas vogais,ate acerta uma que esteja na palavra que o usuario escolheu do arquivo do professor(a,e,i,o,u)nessa ordem

void vogais()
{
    int i = 0, l = 0, j = 0, z = 0, Verificada = 0;
    char v;                                         //volgal escolhida
    posLetra = calloc(Tamanhopalavra, sizeof(int)); //caloc no tamanho palavra,para ajuadar no chute das vogais
    do
    {
        printf("**|Tem a letra | %c | na palavra,se sim,quantas vezes ela aparece: ", voga[i]); //chute e perguntando se tem letra e quantas vezes ela aparece
        scanf(" %d", &QtdLetrasPalavras);
        v = voga[i];
        ChuteVogal = v;               //chamando o primeiro procedimento,para chutar vogal
        contadordetentativa++;        //contador de tentativa
        erros++;                      //contador de erro
        i++;                          //proxima vogal
    }
    while (QtdLetrasPalavras == 0);   //enquanto nao encontrar a vogal

    if (QtdLetrasPalavras != 0) //diferente de 0
    {
        for (i = 0; i < QtdLetrasPalavras; i++) //pecorrer as quantidade de letra da palavras
        {
            printf("Qual a posicao da letra na palavra: %c\n", v); //posicao da letre na palavra,informada pelo numero
            scanf(" %d", &posLetra[i]);
            palavraSecreta[posLetra[i] - 1] = v;
            palavraSorteada(v);
        }

        for (l = 0; l < quantidadeParquivo; l++) //Percorre as palavras na matriz
        {
            int col = posLetra[z++] - 1;      // Pegamos do vetor de posicoes criticas a posicao das vogais nas palavras
            if (tolower(matriz[l][col]) == v) //col = coluna
            {
                if (Verifica_Letra_Palavra(QtdLetrasPalavras, l, posLetra, v)) //verifica  a letra da palavra,com quantidade de letra o for do l,pos e v
                {
                    strcpy(matriz[Verificada], matriz[l]); //copiando a string na matriz as palavras verificada
                    Verificada++;                          //adicionada a palavra verificada
                    continue;
                }
            }
            else
            {
                z = 0; //zerando o z e continuando
                continue;
            }
        }
        quantidadeParquivo = Verificada; //se quantidade palavra arquivo for igual verificado
        erros--;
    }
    Verificada = 0;
    for (z = 0; z < quantidadeParquivo; z++) //verificando as posicao para eliminar mais palavra
    {
        l = 0;                               //zerando o l q foi usado no for la em cima
        for (j = 0; j < Tamanhopalavra; j++) //for para percorrer o tamanho da palavra
        {
            if (towlower(matriz[z][j]) == v) //matriz na posiçao z e j for igual v
            {
                l++;
            }
        }
        if (l == QtdLetrasPalavras)
        {
            strcpy(matriz[Verificada], matriz[z]); //copiando a matriz
            Verificada++;//adionando verificada
        }
    }
    quantidadeParquivo = Verificada;
    free(posLetra); //zerando a posletra,para nao ficar pesado,calloc ele la em cima
}

void limpa(int pesoDasVogais[], int tamanho) //funcao para limpa,e utilizei tamanho para poder usar em vetores diferentes
{
    int i;
    for (i = 0; i < tamanho; i++)
    {
        pesoDasVogais[i] = 0;
    }
}
void palavraSorteada(char letraChute)
{
    if (QtdChutes == 0)
    {
        GuardaChute = (char *)malloc(2 * sizeof(char));
        GuardaChute[0] = tolower(letraChute);
        //GuardaChute[QtdChutes + 1] = '\0'; //organizacao da string
    }
    else
    {
        GuardaChute = (char *)realloc(GuardaChute, (QtdChutes + 2) * sizeof(char));
        GuardaChute[QtdChutes] = tolower(letraChute);
    }
    GuardaChute[QtdChutes + 1] = '\0'; //organizacao da string
    QtdChutes++;
}

bool verificaJaChutados(char letra)
{
    for (int i = 0; i < QtdChutes; i++)
    {
        if (GuardaChute[i] == tolower(letra))
        {
            return false;
        }
    }
    return true;
}

//verificar o tamanho para o proximo chute,o proximo chute deve ser a letra que mais aparecer nas palavras,para eliminar o maximo de palavra por chute
//chuter direcionado a letra que mais no arquivo
void PensandoChute() //chute que vai eliminar o maior numero de palavra
{
    int i, j, g;
    char frase[(quantidadeParquivo * Tamanhopalavra) + quantidadeParquivo], aux, *aux1; //transformando a matriz em uma unica linha/frase,para verificar a maior ocorrencia de letra,para um chute certeiro
    aux1 = (char *)malloc(Tamanhopalavra + 1 * sizeof(char));
    for (i = 0; i < quantidadeParquivo; i++) //for para pecorrer as palavras verificas do arquivo
    {
        strcpy(aux1, matriz[i]);
        strcat(aux1, "/");
        if (i == 0)
        {
            strcpy(frase, aux1);
        }
        else
        {
            strcat(frase, aux1); //strcat junta as strings
        }
    }
    for (i = 0; i < strlen(frase) - 1; i++) //pecorrendo a strig frase
    {
        for (j = 0; j < strlen(frase) - i - 1; j++)
        {
            if (frase[j] == '/' || frase[j + 1] == '/') //adicionado uma barra no final de cada palavra organizada ja
            {
                continue;
            }
            if (frase[j] > frase[j + 1]) //organizando a matriz
            {
                aux = frase[j];
                frase[j] = frase[j + 1];
                frase[j + 1] = aux;
            }
        }
    }
    int quantidadeVogais = sizeof(pesoDasVogais) / sizeof(pesoDasVogais[0]);
    //inicilizando o vetor que armanzena a quantidade de Vogais
    for (int j = 0; j < quantidadeVogais; j++)
    {
        pesoDasVogais[j] = 0;
    }

    int flagVogaisPorPalavra = sizeof(Achei_a_Vogal) / sizeof(Achei_a_Vogal[0]);
    //inicilizando o vetor de flags para nao contar a mesma vogal duas vezes
    for (int j = 0; j < flagVogaisPorPalavra; j++)
    {
        Achei_a_Vogal[j] = 0;
    }

    g = sizeof(frase) / sizeof(frase[0]); //saber o tamanho do vetor sem ter estipulado o tamanho do vetor na declaracao
    limpa(pesoDasVogais, 5);
    limpa(pesoDasConsoantes, 21);
    for (int r = 0; r < g; r++)
    {
        {
            switch (tolower(frase[r]))
            {
            case 'a': // conta a frequencia de letra em letra a medida que acha na palavra
                if (Achei_a_Vogal[0] == 0 && verificaJaChutados(frase[r]))
                    pesoDasVogais[0]++;
                Achei_a_Vogal[0] = 1;
                break;
            case 'e':
                if (Achei_a_Vogal[1] == 0 && verificaJaChutados(frase[r]))
                    pesoDasVogais[1]++;
                Achei_a_Vogal[1] = 1;
                break;
            case 'i':
                if (Achei_a_Vogal[2] == 0 && verificaJaChutados(frase[r]))
                    pesoDasVogais[2]++;
                Achei_a_Vogal[2] = 1;
                break;
            case 'o':
                if (Achei_a_Vogal[3] == 0 && verificaJaChutados(frase[r]))
                    pesoDasVogais[3]++;
                Achei_a_Vogal[3] = 1;
                break;
            case 'u':
                if (Achei_a_Vogal[4] == 0 && verificaJaChutados(frase[r]))
                    pesoDasVogais[4]++;
                Achei_a_Vogal[4] = 1;
                break;
            case 'b':
                if (Achei_a_Consoantel[0] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[0]++;
                Achei_a_Consoantel[0] = 1;
                break;
            case 'c':
                if (Achei_a_Consoantel[1] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[1]++;
                Achei_a_Consoantel[1] = 1;
                break;
            case 'd':
                if (Achei_a_Consoantel[2] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[2]++;
                Achei_a_Consoantel[2] = 1;
                break;
            case 'f':
                if (Achei_a_Consoantel[3] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[3]++;
                Achei_a_Consoantel[3] = 1;
                break;
            case 'g':
                if (Achei_a_Consoantel[4] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[4]++;
                Achei_a_Consoantel[4] = 1;
                break;
            case 'h':
                if (Achei_a_Consoantel[5] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[5]++;
                Achei_a_Consoantel[5] = 1;
                break;
            case 'j':
                if (Achei_a_Consoantel[6] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[6]++;
                Achei_a_Consoantel[6] = 1;
                break;
            case 'k':
                if (Achei_a_Consoantel[7] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[7]++;
                Achei_a_Consoantel[7] = 1;
                break;
            case 'l':
                if (Achei_a_Consoantel[8] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[8]++;
                Achei_a_Consoantel[8] = 1;
                break;
            case 'm':
                if (Achei_a_Consoantel[9] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[9]++;
                Achei_a_Consoantel[9] = 1;
                break;
            case 'n':
                if (Achei_a_Consoantel[10] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[10]++;
                Achei_a_Consoantel[10] = 1;
                break;
            case 'p':
                if (Achei_a_Consoantel[11] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[11]++;
                Achei_a_Consoantel[12] = 1;
                break;
            case 'q':
                if (Achei_a_Consoantel[12] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[12]++;
                Achei_a_Consoantel[12] = 1;
                break;
            case 'r':
                if (Achei_a_Consoantel[13] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[13]++;
                Achei_a_Consoantel[13] = 1;
                break;
            case 's':
                if (Achei_a_Consoantel[14] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[14]++;
                Achei_a_Consoantel[14] = 1;
                break;
            case 't':
                if (Achei_a_Consoantel[15] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[15]++;
                Achei_a_Consoantel[15] = 1;
                break;
            case 'v':
                if (Achei_a_Consoantel[16] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[16]++;
                Achei_a_Consoantel[16] = 1;
                break;
            case 'w':
                if ((Achei_a_Consoantel[17] = 0) && (verificaJaChutados(frase[r])))
                    pesoDasConsoantes[17]++;
                Achei_a_Consoantel[17] = 1;
                break;
            case 'x':
                if (Achei_a_Consoantel[18] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[18]++;
                Achei_a_Consoantel[18] = 1;
                break;
            case 'y':
                if (Achei_a_Consoantel[19] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[19]++;
                Achei_a_Consoantel[19] = 1;
                break;
            case 'z':
                if (Achei_a_Consoantel[20] == 0 && verificaJaChutados(frase[r]))
                    pesoDasConsoantes[20]++;
                Achei_a_Consoantel[20] = 1;
                break;
            } //FIM SWITCH

        } //FIM FOR INTERNO
        limpa(Achei_a_Vogal, 5);
        limpa(Achei_a_Consoantel, 21);
    } //FIM FOR EXTERNO
    //free(aux1);
}

void retirarPalavras(char ultimoChute, bool tipoRetirada) //tipoRetirada == true : Tira palavras que não contém a letra, tipoRetirada == false : Tira palavras que contém a letra
{
    int Verificada = 0, qtdLetra = 0;

    for (int i = 0; i < quantidadeParquivo; i++)
    {
        qtdLetra = 0;
        for (int j = 0; j < Tamanhopalavra; j++)
        {
            if (tolower(matriz[i][j]) == ultimoChute)
            {
                qtdLetra++;
            }
        }
        if (tipoRetirada == 1)
        {
            if (qtdLetra == 0)
            {
                strcpy(matriz[Verificada], matriz[i]); //copiando a string na matriz as palavras verificada
                Verificada++;                          //adicionada a palavra verificada
            }
        }
        else
        {
            if (qtdLetra > 0)
            {
                strcpy(matriz[Verificada], matriz[i]); //copiando a string na matriz as palavras verificada
                Verificada++;                          //adicionada a palavra verificada
            }
        }
    }

    quantidadeParquivo = Verificada;
}

void Chutando()
{
    //int tamanhoPeso = (sizeof(pesoDasVogais) / sizeof(pesoDasVogais[0]));
    int maiorPesoV = pesoDasVogais[0], maiorPesoC = pesoDasConsoantes[0];
    char maiorVogal = voga[0], maiorConsoante = alfabeto[0];
    for (int h = 0; h < 5; h++)
    {
        if (pesoDasVogais[h] > maiorPesoV)
        {
            maiorVogal = voga[h];
            maiorPesoV = pesoDasVogais[h];
        }
    }

    for (int k = 0; k < 21; k++)
    {
        if (pesoDasConsoantes[k] > maiorPesoC)
        {
            maiorConsoante = alfabeto[k];
            maiorPesoC = pesoDasConsoantes[k];
        }
    }

    if (maiorPesoC > maiorPesoV)
    {
        printf("**|Tem a letra | %c | na palavra,se sim,quantas vezes ela aparece: ", maiorConsoante); //chute com o peso maior de consante
        scanf(" %d", &QtdLetrasPalavras);
        contadordetentativa++; //contador de tentativa
        // erros++;//contador de erro
        if (QtdLetrasPalavras != 0) //diferente de 0
        {
            for (int i = 0; i < QtdLetrasPalavras; i++) //pecorrer as quantidade de letra da palavras
            {
                printf("Qual a posicao da letra na palavra: %c\n", maiorConsoante); //posicao da letre na palavra,informada pelo numero
                scanf(" %d", &posLetra[i]);
                palavraSecreta[posLetra[i] - 1] = maiorConsoante;
            }
        }
        else
        {
            erros++;
        }
    }
    else if (maiorPesoV >= maiorPesoC)
    {
        printf("**|Tem a letra | %c | na palavra,se sim,quantas vezes ela aparece: ", maiorVogal); //chute com o peso maior de consante
        scanf(" %d", &QtdLetrasPalavras);
        contadordetentativa++; //contador de tentativa
        // erros++;//contador de erro
        if (QtdLetrasPalavras != 0) //diferente de 0
        {
            for (int k = 0; k < QtdLetrasPalavras; k++) //pecorrer as quantidade de letra da palavras
            {
                printf("Qual a posicao da letra na palavra: %c\n", maiorVogal); //posicao da letre na palavra,informada pelo numero
                scanf(" %d", &posLetra[k]);
                palavraSecreta[posLetra[k] - 1] = maiorVogal;
            }
        }
        else
        {
            erros++;
        }
    }
    palavraSorteada(maiorPesoC > maiorPesoV ? maiorConsoante : maiorVogal);
    retirarPalavras(maiorPesoC > maiorPesoV ? maiorConsoante : maiorVogal, QtdLetrasPalavras > 0 ? false : true);
    limpa(pesoDasVogais, 5);
    limpa(pesoDasConsoantes, 21);
}
void acabou(){
    printf("Palavra: %s\nParabens!\n Voce acertou!!\nObrigado por jogar nosso jogo, sua divida eh de 100 pontos na especial!", matriz[0]);
    printf("\n\t       ___________        ");
    printf("\n\t      '._==_==_=_.'       ");
    printf("\n\t     .-\\:      /-.       ");
    printf("\n\t     | (|:.     |) |      ");
    printf("\n\t      '-|:.     |-'       ");
    printf("\n\t       \\::.    /         ");
    printf("\n\t         '::. .'          ");
    printf("\n\t           ) (            ");
    printf("\n\t         _.' '._          \n");
}
int main() //Programa principal,so chamando as funcoes e procedimentos,nao pode implemnetar funcionalidade dentro
{
    FILE *arq;
    int Tamanhopalavra = comeco(); //chamando o inicio do programa,que pega o tamanho da palavra pra iniciar o jogo,e ja comecar a eliminar palavras
    LerArquivo(Tamanhopalavra);    //chamando o procedimento para abrir e ler o arquivo fornecido pelo professor
    tracoPalavra(palavraSecreta);
    menu();   //menu que mostra as tentativas e erros,menu principal
    system("cls");
    vogais(); //chamando a funçao de chute de vogais
    system("cls");

    while (quantidadeParquivo > 1) //vai rodar enquanto nao tiver 1 palavra no arquivo,que vai ser quando a maquina acerta a palavra
    {
        menu();          //menu que mostra as tentativas e erros,menu principal
        PensandoChute(); //chuter certo e a funcao que vai tirar o maior numero de palavras
        Chutando();
        system("pause"); //para pausar o menu
        system("cls");   //para limpar
    }
    acabou();
    free(matriz);//liberar o espaco utilizado pela matriz
    free(palavraSecreta); //liberar o espaco
    system("pause");//para pausar o menu
    fclose(arq);
    return 0;
}
