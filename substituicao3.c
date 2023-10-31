#include "funcoes.h"

int main(){
    char nome_arquivo[20];
    int tamanho_cifra;

    FILE* arquivo_binario = NULL;
    
    do{
        printf("Digite o nome do arquivo: ");
        scanf("%s", nome_arquivo);
        arquivo_binario = fopen(nome_arquivo, "r");
    } while(arquivo_binario == NULL);
    
    tamanho_cifra = traducao_binaria(arquivo_binario);

    fclose(arquivo_binario);

    descriptografia(tamanho_cifra);

    return 0;
}
