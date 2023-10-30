#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define TOTAL 8448255824.0 

typedef struct{

    char quadgrams[5];
    int afinidade;
}Quadgrams;

float afinidade_quad(char *, Quadgrams*, int);
int cont_quad();
Quadgrams* coloca_quad(int, Quadgrams*);

int main() {
    char quad_selecionado[5], frase[] = "XIWPHQTTCHPXSIWPIPHIGDCDBNXHPWJBQAXCVPCSRWPGPRITGQJXASXCVTMETGXTCRTIWTGTXHETGWPEHCDQTIITGSTBDCHIGPIXDCDUIWTUDAANDUWJBPCRDCRTXIHIWPCIWXHSXHIPCIXBPVTDUDJGIXCNLDGASIDBTXIJCSTGHRDGTHDJGGTHEDCHXQXAXINIDSTPABDGTZXCSANLXIWDCTPCDIWTGPCSIDEGTHTGKTPCSRWTGXHWIWTEPATQAJTSDIIWTDCANWDBTLTWPKTTKTGZCDLC";
    float afinidade, soma = 0.0, valor_quad, maiorAfini=-9999;
    int len = strlen(frase);
    char *fraseoriginal=malloc(len*sizeof(char));
    int n=cont_quad();
    Quadgrams *quadgrams=malloc(n*sizeof(Quadgrams));

    quadgrams=coloca_quad(n, quadgrams);
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

Quadgrams* coloca_quad(int n, Quadgrams *quad){

    FILE *arq=fopen("quadgrams.txt", "r");
    for(int i=0; i<n; i++)
        fscanf(arq, "%5s %d", quad[i].quadgrams, &quad[i].afinidade);

    fclose(arq);

    return quad;
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
