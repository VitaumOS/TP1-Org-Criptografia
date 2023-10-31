
#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TOTAL 8448255824.0


typedef struct {
    char quadgrams[5];
    int afinidade;
}Quadgrams;

int cont_quad();
Quadgrams* coloca_quad(int, Quadgrams*);


// Funções usadas para calcular os quadgrams

Quadgrams* inicializa_quadgrams(int n, Quadgrams *quad); // Antigo coloca_quad
float afinidade_quad(char *quad, Quadgrams *quadgrams, int n);
float qualidade_cifra(int tamanhoCifra, char* fraseCifrada, Quadgrams *quadgrams, int quads); // Antigo afinidade_total
float quantidade_quads();    // Antigo cont_quad

// Funções para a conversão binário para ASCII


char binParaChar(char *bin);
int binParaInt(char *bin);
int conta_Espacos(FILE *arquivo_binario);    // Antigo Grabber()
int traducao_binaria(FILE *arquivo_binario);

// Funções usadas para descriptografar a cifra de substituição

float valor_zero_a_umX();
float valor_zero_a_umY();
void frequencia_global(float* frequencia); // Antigo inicializaFrequencia
void frase_Inicial(char* frase, int tamanhoFrase);
void primeira_chave(char* chave);
void tradutor_chaves(char* resultado, char* chave, char* cifra, int tamanhoCifra);
void escolha_aleatoria(float* frequencias, int* y, int* x, int par);
void normalizador(float* frequencia_percentual, float* frequencia_Traducao, float* frequencia_alfabeto);
void pequena_mudanca(char* chave, float* frequencia_Traducao, float* frequencia_alfabeto);
void calcula_frequencia(float* frequencia, char* cifra, int tamanho);
void descriptografia();




#endif