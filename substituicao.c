#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TOTAL 8448255824.0

typedef struct{
    char quadgrams[5];
    int afinidade;
}Quadgrams;

Quadgrams* coloca_quad(int n, Quadgrams *quad){

    FILE *arq=fopen("quadgrams.txt", "r");
    for(int i=0; i<n; i++)
        fscanf(arq, "%5s %d", quad[i].quadgrams, &quad[i].afinidade);

    fclose(arq);

    return quad;
}

float afinidade_quad(char *quad, Quadgrams *quadgrams, int n) {
    float soma = 0.0;

    for(int i=0; i<n; i++){
        if (!strcmp(quadgrams[i].quadgrams, quad)) {
            soma = log((quadgrams[i].afinidade * 1.0) / TOTAL);
            return soma;
        }
    }

    return 0.0;
}

int cont_quad(){

    int num=0, a;
    char q[5];
    FILE *arq=fopen("quadgrams.txt", "r");
    while(!feof(arq)){

        fscanf(arq, "%5s %d", q, &a);
        num++;
    }
    fclose(arq);
    return num;
}

char binToChar(char *bin){
    int saida = 0;
    int potencia = 1;

    for (int i = 7; i >= 0; i--){
        if(bin[i] == '1'){
            saida += potencia;
        }
        potencia *= 2;
    }
    return (char) saida;
}

int binToInt(char *bin){
    int saida = 0;
    int potencia = 1;

    for (int i = 7; i >= 0; i--){
        if(bin[i] == '1'){
            saida += potencia;
        }
        potencia *= 2;
    }
    return saida;
}

int grabber(FILE* arq){
    char t;
    int space = 0;
    while ((t = fgetc(arq)) != EOF){
        if(t == ' '){
            space++;
        } else {
            break;
        }
    }
    return space;
}

char* fraseInicial(FILE* arq, int tam){
    char* frase = malloc(tam * sizeof(char));
    char temp = ' ';
    for (int i = 0; i < tam; i++){
        if((temp = fgetc(arq)) != ' '){
            frase[i] = temp;
        } else {
            i--;
        }
    }
    return frase;
}

char* tradutor(char* cifra, char* chave, char* alfabeto, int tam){
    char* saida = malloc(tam * sizeof(char));
    int* troca = malloc(tam * sizeof(int));
    for (int i = 0; i < tam; i++){
        troca[i] = 0;
    }
    
    for (int i = 0; i < 26; i++){
        for(int j = 0; j < tam; j++){
            if((cifra[j] == alfabeto[i]) && (troca[j] == 0)){
                saida[j] = chave[i];
                troca[j] = 1;
            }
        }
    }
    printf("\n");
    free(troca);
    return saida;
}

int main(){

    char nomeArq[20];
    char palavra[8];
    char temp = '2';
    int letra = 0;
    int tamanho = 0;

    char* fraseCifrada;

    int frequencia[26];
    char alfabeto[26];
    char gabarito[26];
    char chave[26];

    /*QuadGrams*/
    int quads = cont_quad();
    float afinidade, valor_quad, soma = 0.0;
    char quad_selecionado[5];
    Quadgrams *quadgrams = malloc(quads * sizeof(Quadgrams));




    FILE *arquivoGabarito = NULL;
    arquivoGabarito = fopen("gabarito.txt", "r");

    for(int i = 0; i < 26; i++){
        frequencia[i] = 0;
        alfabeto[i] = 65 + i;
        gabarito[i] = fgetc(arquivoGabarito);
        chave[i] = ' ';
    }

    fclose(arquivoGabarito);

    FILE *entrada = NULL;
    do{
        printf("Digite o nome do arquivo: ");
        scanf("%s", nomeArq);
        entrada = fopen(nomeArq, "r");
    } while (entrada == NULL);
    
    FILE *ascii = NULL;
    ascii = fopen("ascii.txt", "w");

    while (temp != EOF){
        for (int i = 0; i < 8; i++){
            palavra[i] = 0;
        }
        letra = grabber(entrada);
        palavra[letra] = '1';
        letra++;
        while ((temp = fgetc(entrada)) != EOF){
            if (temp == ' '){
                break;
            }
            palavra[letra] = temp;
            letra++;
        }
        if(temp != EOF){
            fprintf(ascii, "%c", binToChar(palavra));
            frequencia[binToInt(palavra) - 65]++;
            if(binToChar(palavra) != ' '){
                tamanho++;
            }
        }
    }

    fclose(entrada);
    fclose(ascii);
    
    int trocaI = 0;
    char trocaC = ' ';
    for (int i = 25; i > 0; i--){
        for (int j = 0; j < i; j++){
            if(frequencia[j] < frequencia[j+1]){
                trocaC = alfabeto[j];
                trocaI = frequencia[j];

                alfabeto[j] = alfabeto[j+1];
                frequencia[j] = frequencia[j+1];

                alfabeto[j+1] = trocaC;
                frequencia[j+1] = trocaI;

            }
        }
    }
    
    /*#################################*/

    quadgrams = coloca_quad(tamanho, quadgrams);


    for(int i = 0; i < 4; i++){
        chave[i] = gabarito[i];
        chave[26 - i] = gabarito[26 - i]; // !!!!!!!!!!!!!!!!!!!!!!!!
    }
        
    FILE* cifra = NULL;
    cifra = fopen("ascii.txt", "r");

    fraseCifrada = fraseInicial(cifra, tamanho);    
    printf("%s\n", fraseCifrada);
    fraseCifrada = tradutor(fraseCifrada, gabarito, alfabeto, tamanho);
    printf("%s\n", fraseCifrada);

    /*Quad-gram - INICIO*/
    for (int i = 0; i + 4 <= tamanho; i++){
        for (int j = 0; j < 4; j++){
            quad_selecionado[j] = fraseCifrada[i + j];
        }
        quad_selecionado[4] = '\0';
        valor_quad = afinidade_quad(quad_selecionado, quadgrams, quads);
        soma += valor_quad;
    }
    afinidade = soma;
    soma = 0.0;
    printf("Afinidade: %f\n", afinidade);
    
    /*Quad-gram - FIM*/
    
    fclose(cifra);
    free(fraseCifrada);
    /*#################################*/
    
    return 0; 
}