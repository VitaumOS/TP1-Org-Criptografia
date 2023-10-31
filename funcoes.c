#include "funcoes.h"

const char ALFABETO[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
Quadgrams* inicializa_quadgrams(int quantidade_quad, Quadgrams* quadgrams){

    FILE *arquivo = fopen("quadgrams.txt", "r");
    for (int i = 0; i < quantidade_quad; i++){
        fscanf(arquivo, "%5s %d", quadgrams[i].quadgrams, &quadgrams[i].afinidade);
    }
    fclose(arquivo);
    return quadgrams;
}

float afinidade_quad(char *quad, Quadgrams *quadgrams, int n){
    float soma = 0.0;

    for(int i=0; i<n; i++){
        if (!strcmp(quadgrams[i].quadgrams, quad)) {
            soma = log((quadgrams[i].afinidade * 1.0) / TOTAL);
            return soma;
        }
    }

    return 0.0;
}

float qualidade_cifra(int tamanhoCifra, char* fraseCifrada, Quadgrams *quadgrams, int quads){
    char quad_selecionado[5];
    float valor_quad = 0.0;
    float soma = 0.0;
    for (int i = 0; i + 4 <= tamanhoCifra; i++){
        for (int j = 0; j < 4; j++){
            quad_selecionado[j] = fraseCifrada[i + j];
        }
        quad_selecionado[4] = '\0';
        valor_quad = afinidade_quad(quad_selecionado, quadgrams, quads);
        soma += valor_quad;
    }
    return soma;
}

float quantidade_quads(){
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

char binParaChar(char *bin){
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

Quadgrams* coloca_quad(int n, Quadgrams *quad){

    FILE *arq=fopen("quadgrams.txt", "r");
    for(int i=0; i<n; i++)
        fscanf(arq, "%5s %d", quad[i].quadgrams, &quad[i].afinidade);

    fclose(arq);

    return quad;
}

int binParaInt(char *bin){
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

int conta_Espacos(FILE *arquivo_binario){
    char t;
    int space = 0;
    while ((t = fgetc(arquivo_binario)) != EOF){
        if(t == ' '){
            space++;
        } else {
            break;
        }
    }
    return space;
}

int traducao_binaria(FILE *arquivo_binario){
    char letra_temporaria = ' ';
    char palavra_binaria[8];
    char temp;
    int posicao_selecionada = 0;
    int tamanho_sem_espacos = 0;

    FILE *arquivo_ascii = NULL;
    arquivo_ascii = fopen("ascii.txt", "w");

    while (letra_temporaria != EOF){
        for(int i = 0; i < 8; i++){
            palavra_binaria[i] = 0;
        }
        posicao_selecionada = conta_Espacos(arquivo_binario);
        palavra_binaria[posicao_selecionada] = '1';
        posicao_selecionada++;
        while (((letra_temporaria = fgetc(arquivo_binario)) != EOF) && (letra_temporaria != ' ')){
            palavra_binaria[posicao_selecionada] = letra_temporaria;
            posicao_selecionada++;
        }
        if(letra_temporaria != EOF){
            temp = binParaChar(palavra_binaria);
            fprintf(arquivo_ascii, "%c", temp);
            if(temp != ' '){
                tamanho_sem_espacos++;
            }
        }
        
    }
    fclose(arquivo_ascii);
    return tamanho_sem_espacos;
}

float valor_zero_a_umX(){
    srand(time(NULL));
    float num = rand() % 9998 + 1;
    num = num / 10000.0;

    return num;
}

float valor_zero_a_umY(){
    srand(time(NULL));
    float num = (float) rand() / RAND_MAX;

    return num;
} 

void frequencia_global(float* frequencia){
    double soma = 0.0;
    FILE* arquivo = fopen("gabarito.txt", "r");
    for (int i = 0; i < 26; i++){
        fscanf(arquivo, "%f", &frequencia[i]);
        soma += frequencia[i];
    }
    for(int i = 0; i < 26; i++){
        frequencia[i] = frequencia[i] / soma;
    }
    fclose(arquivo);
}

void frase_Inicial(char* frase, int tamanhoFrase){
    char temp = ' ';
    FILE* arquivo = fopen("ascii.txt", "r");

    for(int i = 0; i < tamanhoFrase; i++){
        if((temp = fgetc(arquivo)) != ' '){
            frase[i] = temp;
        } else {
            i--;
        }
    }

    fclose(arquivo);
}

void primeira_chave(char* chave){
    srand(time(NULL));
    char temp;
    int x, y, forca;
    for (int i = 0; i < 26; i++){
        chave[i] = 65 + i;
    }
    chave[26] = '\0';
    forca = rand() % 100 + 123;
    for (int i = 0; i < forca; i++){
        x = rand() % 26;
        y = rand() % 26;
        temp = chave[x];
        chave[x] = chave[y];
        chave[y] = temp;
    }
}

void tradutor_chaves(char* resultado, char* chave, char* cifra, int tamanhoCifra){
    int* troca = malloc(tamanhoCifra * sizeof(int));
    for (int i = 0; i < tamanhoCifra; i++){
        troca[i] = 0;
    }  
    
    for (int i = 0; i < 26; i++){
        for(int j = 0; j < tamanhoCifra; j++){
            if((cifra[j] == ALFABETO[i]) && (troca[j] == 0)){
                resultado[j] = chave[i];
                troca[j] = 1;
            }
        }
    }
    free(troca);
}

void escolha_aleatoria(float* frequencias, int* y, int* x, int par){
    srand(time(NULL));
                               
    float soma = 0;
    float a;
    float n1, n2;

    switch (par){
    case 0:
        n1 = (float) rand() / RAND_MAX;
        n2 = (float) rand() / RAND_MAX;
        break;
    case 1:
        n1 = rand() % 9998 + 1;
        n1 = n1 / 10000.0;
        n2 = rand() % 9998 + 1;
        n2 = n2 / 10000.0;
        break;
    case 2:
        n1 = rand() % 99998 + 1;
        n1 = n1 / 100000.0;
        n2 = rand() % 99998 + 1;
        n2 = n2 / 100000.0;
        break;
    default:
        break;
    }

    for (int i = 0; i < 26; i++){
        a = soma + frequencias[i];
        if((a > n1) && (n1 >= soma)){
            *x = i;
            i = 26;
        }
        soma = a;
    }

    soma = 0;
    for (int i = 0; i < 26; i++){
        a = soma + frequencias[i];
        if((a > n2) && (n2 >= soma)){
            *y = i;
            i = 26;
        }
        soma = a;
    }
}

void normalizador(float* frequencia_percentual, float* frequencia_Traducao, float* frequencia_alfabeto){
    float soma = 0;
    for (int i = 0; i < 26; i++){
        frequencia_percentual[i] = frequencia_Traducao[i] - frequencia_alfabeto[i];
        if(frequencia_percentual[i] < 0){
            frequencia_percentual[i] *= -1;
        }
        soma += frequencia_percentual[i];
    }
    for (int i = 0; i < 26; i++){
        frequencia_percentual[i] = frequencia_percentual[i] / soma;
    }
    
}

void pequena_mudanca(char* chave, float* frequencia_Traducao, float* frequencia_alfabeto){
    float frequencia_percentual[26];
    char troca;
    int x, y;
    srand(time(NULL));
    
    normalizador(frequencia_percentual, frequencia_Traducao, frequencia_alfabeto);

    for(int i = 0; i < 3; i++){
        escolha_aleatoria(frequencia_percentual, &y, &x, i);

        troca = chave[x];
        chave[x] = chave[y];
        chave[y] = troca;
    }
    x = rand() % 26;
    y = rand() % 26;

    troca = chave[x];
    chave[x] = chave[y];
    chave[y] = troca;
}

void calcula_frequencia(float* frequencia, char* cifra, int tamanho){
    int j = 0;
    for(int i = 0; i < tamanho; i++){
        while(cifra[i] != ALFABETO[j]){
            j++;
        }
        frequencia[j]++;
        j = 0;
    }
    for(int i = 0; i < 26; i++){
        frequencia[i] = frequencia[i] / tamanho;
    }
}

void descriptografia(int tamanho_cifra){
    int quads = quantidade_quads();
    Quadgrams *quadgrams = malloc(quads * sizeof(Quadgrams));
    char chave_principal[26];
    char chave_variante[26];
    char* primeira_frase = malloc(tamanho_cifra * sizeof(char));
    char* frase_principal = malloc(tamanho_cifra * sizeof(char));
    char* frase_variante = malloc(tamanho_cifra * sizeof(char));
    float qualidade_principal, qualidade_variante, frequencia_traducao[26], frequencia_alfabeto_ingles[26];

    frequencia_global(frequencia_alfabeto_ingles);
    quadgrams = inicializa_quadgrams(quads, quadgrams);
    frase_Inicial(primeira_frase, tamanho_cifra);
    primeira_chave(chave_principal);
    strcpy(chave_variante, chave_principal);

    tradutor_chaves(frase_principal, chave_principal, primeira_frase, tamanho_cifra);
    qualidade_principal = qualidade_cifra(tamanho_cifra, frase_principal, quadgrams, quads);
    calcula_frequencia(frequencia_traducao, primeira_frase, tamanho_cifra);
    
    printf("\nPrimeira Chave: %s\n", chave_principal);
    printf("Frase: %s   || Qualidade: %f", frase_principal, qualidade_principal);

    for (int i = 0; i < 10000; i++){
        pequena_mudanca(chave_variante, frequencia_traducao, frequencia_alfabeto_ingles);
        tradutor_chaves(frase_variante, chave_variante, primeira_frase, tamanho_cifra);
        qualidade_variante = qualidade_cifra(tamanho_cifra, frase_variante, quadgrams, quads);

        if(qualidade_variante > qualidade_principal){

            printf("\nChave: %s\n", chave_variante);
            printf("Frase: %s   || Qualidade: %f\n", frase_variante, qualidade_variante);

            calcula_frequencia(frequencia_traducao, frase_variante, tamanho_cifra);
            strcpy(frase_principal, frase_variante);
            strcpy(chave_principal, chave_variante);
            qualidade_principal = qualidade_variante;

        } else {
            strcpy(chave_variante, chave_principal);
        }
    
    }
    
    free(quadgrams);
    free(frase_principal);
    free(frase_variante);
    free(primeira_frase);
}