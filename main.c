#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct arv {
  char info;
  struct arv* esq;
  struct arv* dir;
}TArv;

typedef TArv *PArv;

PArv cria(char c, PArv sae, PArv sad);
void imprimeIn (PArv a, int nivel);
PArv libera (PArv a);
PArv corta_string(char string_prefix[], char string_infix[], int num_no);


int main(void) {

  int num_no;

  printf("Digite o numero de nos que a arvore tera:\n");
  scanf("%d",&num_no);

  if(num_no > 100){ // COMO REQUERIDO, LIMITEI O NUMERO DE NOS
    printf("Numero de nós inválido. Limite-se a apenas 100 nós.\n");
    return 0;
  }
  
  // CRIACAO DAS STRINGS APOS SABER O NUMERO DE ELEMENTOS 
  char string_prefix[num_no];
  char string_infix[num_no];

  
  printf("Digite a sequencia dos nos em ordem pre-fixa:\n");
  scanf("%s",string_prefix);

  if(strlen(string_prefix) != num_no){ // VERIFICA CASO AS STRINGS NAO TEM O MESMO NUMERO DE ELEMENTOS, OU SEJA, AS ORDENS NAO PODEM CORRESPONDER A UMA ARVORE
    printf("Numero de elementos na string prefix nao condiz com o numero de nos.\n");
    return 0;
  }

  printf("Digite a sequencia dos nos em ordem infixa:\n");
  scanf("%s",string_infix);

  if(strlen(string_infix) != num_no){ // MESMO COMENTARIO ACIMA
    printf("Numero de elementos na string infixa nao condiz com o numero de nos.\n");
    return 0;
  }

  PArv arvore_binaria = corta_string(string_prefix, string_infix, num_no);

  imprimeIn(arvore_binaria, 0);

  libera(arvore_binaria);

  return 0;
}

PArv cria(char c, PArv sae, PArv sad) {
  PArv p = (PArv)malloc(sizeof(TArv)); // ALOCA DINAMICAMENTE O NO RAIZ DA ARVORE
  p->info = c;
  p->esq = sae;
  p->dir = sad;
return p;
}

void imprimeIn (PArv a, int nivel) {
  if (a!=NULL) {
    imprimeIn(a->esq, nivel+1); // IMPRIME SAE
    for(int i = 0; i < nivel; i++){
      printf("\t"); // SIMPLISMENTE USADA PARA IMPRIMIR DE ACORDO COM O PEDIDO
    }
    printf("%c\n", a->info); // IMPRIME EM UMA LINHA O NO ADEQUADO
    imprimeIn(a->dir, nivel+1); // IMPRIME SAD
  }
}

PArv libera (PArv a){
  if (a!=NULL) {
    libera(a->esq); // LIBERA SAE
    libera(a->dir); // LIBERA SAD
    free(a); // LIBERA RAIZ
  }
  return NULL;
}

PArv corta_string(char string_prefixa[], char string_infixa[], int num_no){

  PArv arvore_binaria = cria(string_prefixa[0], NULL, NULL);

  if(num_no > 1){ // VARIAVEIS P/ PERCORRER AS STRINGS
    int cont = 0;
    int i = 0;
    int j = 0;
    int chave=0; // A VARIAVEL CHAVE ESTA SENDO UTILIZADA PARA SABER SE ACRESCENTO A DIREITA OU A ESQUERDA DAS RAIZES

    while(string_prefixa[0] != string_infixa[cont]){ // LACO PARA DETERMINAR QUANDO ENCONTRAR RAIZ PRINCIPAL DA ARVORE
      cont++;
    }

    if(cont == 0){
      chave = 1;
    }
    else if(cont == num_no-1){
      chave = 2;
    }

    // STRINGS CRIADAS PARA AUXILIAR NO INCREMENTO DA ARVORE
    char prefixa_esq[cont];
    char prefixa_dir[num_no-cont-1];
    char infixa_esq[cont];
    char infixa_dir[num_no-cont-1];

    for(i = 0; i < num_no; i++){ // LACO PARA SEPARAR OS ELEMENTOS DA ARVORE PARA DEPOIS AS STRINGS SEREM INSERIDAS NA ARVORE

      if(i < cont && chave != 1){
        infixa_esq[j] = string_infixa[i];
        prefixa_esq[j] = string_prefixa[i+1];
        j++;
    }

      if(i == cont){ // ESSE IF ESTA SENDO USADO PARA IDENTIFICAR QUANDO EH LIDO TODOS OS ELEMENTOS A ESQUERDA DA RAIZ. ASSIM QUE ATINGIR A RAIZ NA PREFIXA, ZERAREI "J" PARA PERCORRER OS ELEMENTOS NA PREFIXA
        j=0;
      }

      if(i > cont && chave != 2){
        infixa_dir[j] = string_infixa[i];
        prefixa_dir[j] = string_prefixa[i];
        j++;
      }

    }

    if(chave != 1){ // CHAMADA DA FUNCAO corta_string DE FORMA RECURSIVA PARA INCREMENTO A ESQUERDA DOS NOS
      arvore_binaria->esq = corta_string(prefixa_esq, infixa_esq, cont);
    }

    if(chave != 2){ // CHAMADA DA FUNCAO corta_string DE FORMA RECURSIVA PARA INCREMENTO A DIREITA DOS NOS
      arvore_binaria->dir = corta_string(prefixa_dir, infixa_dir, num_no-cont-1); // O TERCEIRO PARAMETRO DESCONTA A RAIZ PRINCIPAL
    }

  }

    return arvore_binaria;
}