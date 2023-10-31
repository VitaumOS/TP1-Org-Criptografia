
#include "funcoes.h"

int main() {
    char quad_selecionado[5];
    float afinidade, soma = 0.0, valor_quad, maiorAfini=-9999;
    
    int tamanho_cifra;
    

    int n=cont_quad();
    Quadgrams *quadgrams=malloc(n*sizeof(Quadgrams));
    quadgrams=coloca_quad(n, quadgrams);

    FILE* arquivo_binario = NULL;
    arquivo_binario = fopen("encoded_ces.txt", "r");
    tamanho_cifra = traducao_binaria(arquivo_binario);
    fclose(arquivo_binario);

    char *frase=malloc(tamanho_cifra*sizeof(char));

    FILE * arquivo = NULL;
    int i=0;
    char letra;
    arquivo = fopen("ascii.txt", "r");
    while(!feof(arquivo)){
        letra=fgetc(arquivo);
        if(letra!=' '){
            frase[i]=letra;
            i++;
        }
    }
    fclose(arquivo);
    int len = tamanho_cifra;
    char *fraseoriginal=malloc(len*sizeof(char));


   
    printf("Aguarde...\n");
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < len; j++) {
            frase[j] = ((frase[j] - 'A' + 1) % 26) + 'A';
        }


        /*##################*/
        for (int x = 0; x + 4 <= len; x++) {
            for (int k = 0; k < 4; k++) {
                quad_selecionado[k] = frase[x + k];
            }
            quad_selecionado[4] = '\0';
            valor_quad = afinidade_quad(quad_selecionado, quadgrams, n);
            soma += valor_quad;
        }
        afinidade = soma;
        soma = 0.0;


        if(afinidade>maiorAfini){
            maiorAfini=afinidade;
            strcpy(fraseoriginal,frase);
        }
        /*###################*/
    }

    printf("Frase Traduzida: %s\nAfinidade:%.1f", fraseoriginal, maiorAfini);
    return 0;
}

