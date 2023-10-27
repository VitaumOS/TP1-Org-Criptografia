#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

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

float afinidade_total(int tamanho, const char* fraseCifrada, Quadgrams *quadgrams, int quads){
    char quad_selecionado[5];
    float valor_quad = 0.0;
    float soma = 0.0;
    for (int i = 0; i + 4 <= tamanho; i++){
        for (int j = 0; j < 4; j++){
            quad_selecionado[j] = fraseCifrada[i + j];
        }
        quad_selecionado[4] = '\0';
        valor_quad = afinidade_quad(quad_selecionado, quadgrams, quads);
        soma += valor_quad;
    }
    return soma;
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

char* tradutor(const char* cifra, char* chave, const char* alfabeto, int tam){
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
    free(troca);
    return saida;
}

char* primeiraChave(){
    srand(time(NULL));
    char* n;
    char temp;
    int x, y;
    n = malloc(26 * sizeof(char));
    for (int i = 0; i < 26; i++){
        n[i] = 65 + i;
    }
    for (int i = 0; i < 412; i++){
        x = rand() % 26;
        y = rand() % 26;
        temp = n[x];
        n[x] = n[y];
        n[y] = temp;
    }

    return n;
}

void alittlechange(char *chave){
    srand(time(NULL));
    int x = rand() % 26;
    int y = rand() % 26;
    char temp;
    temp = chave[x];
    chave[x] = chave[y];
    chave[y] = temp;
}

int main(){

    char nomeArq[20];
    char palavra[8];
    char temp = '2';
    int letra = 0;
    int tamanho = 0;

    const char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* chaveN1;
    char* chaveN2;
    char* f1;
    char* f2;

    chaveN2 = malloc(26 * sizeof(char));

    int quads = cont_quad();
    float afinidade1, afinidade2;
    Quadgrams *quadgrams = malloc(quads * sizeof(Quadgrams));

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
            if(binToChar(palavra) != ' '){
                tamanho++;
            }
        }
    }

    fclose(entrada);
    fclose(ascii);

    FILE* cifra = NULL;
    cifra = fopen("ascii.txt", "r");
    const char* fraseCifrada = fraseInicial(cifra, tamanho);
    fclose(cifra);

    quadgrams = coloca_quad(quads, quadgrams);

    // ###################################################


    chaveN1 = primeiraChave();
    strcpy(chaveN2, chaveN1);

    f1 = tradutor(fraseCifrada, chaveN1, alfabeto, tamanho);
    afinidade1 = afinidade_total(tamanho, f1, quadgrams, quads);

    printf("\n1ra Chave: %s\n", chaveN1);
    printf("Frase: %s      || Qualidade: %f\n", f1, afinidade1);

    for(int i = 0; i < 10000; i++){
        alittlechange(chaveN2);
        f2 = tradutor(fraseCifrada, chaveN2, alfabeto, tamanho);
        afinidade2 = afinidade_total(tamanho, f2, quadgrams, quads);
        
        if(afinidade2 > afinidade1){
            printf("\n\nHOUVE MELHORA!!!!\n\n");
            printf("\nChave: %s\n", chaveN2);
            printf("Frase: %s      || Qualidade: %f\n", f2, afinidade2);
            strcpy(f1, f2);
            strcpy(chaveN1, chaveN2);
            afinidade1 = afinidade2;
        }else{
            strcpy(chaveN2, chaveN1);
        }
    }


    // ###################################################

    //free(fraseCifrada);
    free(chaveN1);
    free(quadgrams);
    return 0;
}