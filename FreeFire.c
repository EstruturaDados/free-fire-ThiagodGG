#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


//------------------------------------
// NIVEL: MESTRE
//------------------------------------

#define MAX 20

// Struct do componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

int comparacoes = 0;

// reemove /n do fgets
void limparEnter(char *str){
    str[strcspn(str, "\n")] = 0;
}

// Mostrar componentes
void mostrarComponentes(Componente c[], int n){

    printf("\n--- LISTA DE COMPONENTES ---\n");

    for(int i = 0; i < n; i++){
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n",
               i+1, c[i].nome, c[i].tipo, c[i].prioridade);
    }
}

// Bubble Sort por nome
void bubbleSortNome(Componente c[], int n){

    comparacoes = 0;

    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-i-1; j++){

            comparacoes++;

            if(strcmp(c[j].nome, c[j+1].nome) > 0){

                Componente temp = c[j];
                c[j] = c[j+1];
                c[j+1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente c[], int n){

    comparacoes = 0;

    for(int i = 1; i < n; i++){

        Componente chave = c[i];
        int j = i - 1;

        while(j >= 0 && strcmp(c[j].tipo, chave.tipo) > 0){

            comparacoes++;

            c[j+1] = c[j];
            j--;
        }
        
        c[j+1] = chave;
    }
}

//  Selection Sort por prioridade
void selectionSortPrioridade(Componente c[], int n){

    comparacoes = 0;

    for(int i = 0; i < n-1; i++){

        int menor = i;

        for(int j = i+1; j < n; j++){

            comparacoes++;

            if(c[j].prioridade < c[menor].prioridade){
                menor = j;
            }

        }
        if(menor != i){
            Componente temp = c[i];
            c[i] = c[menor];
            c[menor] = temp;
        }
    }
}

// Busca binaria por nome
int buscaBinariaPorNome(Componente c[], int n, char chave[]){

    int inicio = 0;
    int fim = n - 1;

    while(inicio <= fim){

        int meio = (inicio + fim) / 2;

        int resultado = strcmp(c[meio].nome, chave);

        if(resultado == 0){
            return meio;
        }

        if(resultado < 0){
            inicio = meio + 1;
        }else{
            fim = meio - 1;
        }
    }

    return -1;
}

//  Medir tempo de execução
double medirTempo(void (*algoritmo)(Componente[], int), Componente c[], int n){

    clock_t inicio = clock();

    algoritmo(c, n);

    clock_t fim = clock();

    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// Função principal (main)

int main(){

    Componente componentes[MAX];

    int n;

    printf("Quantos componentes deseja cadastrar (max 20)? ");
    scanf("%d", &n);
    getchar();

    if(n > MAX){
        n = MAX;
    }

    //Cadastro
    for(int i = 0; i < n; i++){

        printf("\nComponente %d\n", i+1);

        printf("Nome: ");
        fgets(componentes[i].nome, 30, stdin);
        limparEnter(componentes[i].nome);

        printf("Tipo: ");
        fgets(componentes[i].tipo, 30, stdin);
        limparEnter(componentes[i].tipo);

        printf("prioridade (1-10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar();    
    }

    int opcao;

    do{

        printf("\n==== MENU ====\n");
        printf("1 - Ordenar por Nome (Bubble Sort)\n");
        printf("2 - Ordenar por Tipo (Insertion Sort)\n");
        printf("3 - Ordenar por Prioridade (Selection Sort)\n");
        printf("4 - Buscar componente por Nome\n");
        printf("5 - Mostrar componentes\n");
        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if(opcao == 1){

            double tempo = medirTempo(bubbleSortNome, componentes, n);

            printf("\nOrdenado por NOME\n");
            mostrarComponentes(componentes, n);

            printf("\nComparacoes: %d", comparacoes);
            printf("\nTempo: %f segundos\n", tempo);
        }


        else if(opcao == 2){

            double tempo = medirTempo(insertionSortTipo, componentes, n);

            printf("\nOrdenado por TIPO\n");
            mostrarComponentes(componentes, n);

            printf("\nComparacoes: %d", comparacoes);
            printf("\nTempo: %f segundos\n", tempo);
        }

        else if(opcao == 3){

            double tempo = medirTempo(selectionSortPrioridade, componentes, n);

            printf("\nOrdenado por PRIORIDADE\n");
            mostrarComponentes(componentes, n);

            printf("\nComparacoes: %d", comparacoes);
            printf("\nTempo: %f segundos\n", tempo);
        }
        
        else if(opcao == 4){

            char chave[30];

            printf("Digite o nome do componente: ");
            fgets(chave, 30, stdin);
            limparEnter(chave);

            int pos = buscaBinariaPorNome(componentes, n, chave);

            if(pos != -1){

                printf("\nComponente encontrado!\n");

                printf("Nome: %s\n", componentes[pos].nome);
                printf("Tipo: %s\n", componentes[pos].tipo);
                printf("Prioridade: %d\n", componentes[pos].prioridade);

            }else{
                printf("\nComponente não encontrado!\n");
            }
        }

        else if(opcao == 5){
            mostrarComponentes(componentes, n);
        }

    }while(opcao != 0);


    return 0;
}


//----------------------------------
// NIVEL: AVENTUREIRO
//----------------------------------
//#define MAX 100

//==================================
// DEFINIÇÃO DA STRUCT
//==================================

// Estrutura do Item
//typedef struct{
//    char nome[30];
//    char tipo[20];
//    int quantidade;
//} Item;

// Estrutura do Nó (lista encadeada)
//typedef struct No {
//    Item dados;
//    struct No* proximo;
//} No;

//==========================
// VARIAVEIS GLOBAIS
//==========================

//int comparacoesSequencial = 0;
//int comparacoesBinaria = 0;

//-------------------------
// VETOR
//-------------------------

//Item mochilaVetor[MAX];
//int totalVetor = 0;

// Inserir item no vetor
//void inserirItemVetor(){
//    if (totalVetor >= MAX){
//        printf("Mochila cheia!\n");
//        return;
//    }

//    printf("Nome: ");
//    scanf(" %[^\n]", mochilaVetor[totalVetor].nome);

//    printf("Tipo: ");
//    scanf(" %[^\n]", mochilaVetor[totalVetor].tipo);

//    printf("Quantidade: ");
//    scanf("%d", &mochilaVetor[totalVetor].quantidade);

//    totalVetor++;
//}

// Listar itens do vetor
//void listarVetor(){
//    for (int i = 0; i < totalVetor; i++){
//        printf("%d - %s | %s | %d\n",
//            i + 1,
//            mochilaVetor[i].nome,
//            mochilaVetor[i].tipo,
//            mochilaVetor[i].quantidade);
//    }
//}

// Remover item por nome no vetor
//void removerItemVetor(){
//    char nome[30];
//    printf("Nome do item a remover: ");
//    scanf(" %[^\n]", nome);

//    for (int i = 0; i < totalVetor; i++){
//        if (strcmp(mochilaVetor[i].nome, nome) == 0){
//            for (int j = i; j < totalVetor - 1; j++){
//                mochilaVetor[j] = mochilaVetor[j + 1];
//            }
//            totalVetor--;
//            printf("Item removido!\n");
//            return;
//        }
//    }
//    printf("Item não encontrado!\n");
//}

// Busca sequencial no vetor
//int buscarSequencialVetor(char nome[]){
//    comparacoesSequencial = 0;

//    for (int i = 0; i < totalVetor; i++){
//        comparacoesSequencial++;
//        if (strcmp(mochilaVetor[i].nome, nome) == 0){
//            return i;
//        }
//    }
//    return -1;
//}

// Ordenar vetor (Bubble Sort)
//void ordenarVetor(){
//    for (int i = 0; i < totalVetor - 1; i++){
//        for (int j = 0; j < totalVetor - i - 1; j++){
//            if (strcmp(mochilaVetor[j].nome,
//                       mochilaVetor[j + 1].nome) > 0){
                
//                Item temp = mochilaVetor[j];
//                mochilaVetor[j] = mochilaVetor[j + 1];
//                mochilaVetor[j + 1] = temp;        
//           }
//        }
//    }
//}

// Busca binariia (apenas no vetor)
//int buscarBinariaVetor(char nome[]){
//    comparacoesBinaria = 0;
//    int inicio = 0;
//    int fim = totalVetor - 1;

//    while (inicio <= fim){
//        int meio = (inicio + fim) / 2;
//        comparacoesBinaria++;

//        int resultado = strcmp(mochilaVetor[meio].nome, nome);

//        if (resultado == 0)
//            return meio;
//        else if (resultado < 0)
//            inicio = meio + 1;
//        else 
//            fim = meio - 1;
//    }
//    return -1;
//}

//--------------------------
// LISTA ENCADEADA
//--------------------------

//No* mochilaLista = NULL;

// Inserir na lista
//void inserirItemLista(){
//    No* novo = (No*) malloc(sizeof(No));

//    printf("Nome: ");
//    scanf(" %[^\n]", novo->dados.nome);

//    printf("Tipo: ");
//    scanf(" %[^\n]", novo->dados.tipo);

//    printf("Quantidade: ");
//    scanf("%d", &novo->dados.quantidade);

//    novo->proximo = mochilaLista;
//    mochilaLista = novo;
//}

// Listar lista
//void listarLista(){
//    No* atual = mochilaLista;
//    int i = 1;

//    while (atual != NULL){
//        printf("%d - %s | %s | %d\n",
//               i++,
//               atual->dados.nome,
//               atual->dados.tipo,
//               atual->dados.quantidade);

//        atual = atual->proximo;
//    }
//}

// Remover da lista
//void removerItemLista(){
//    char nome[30];
//    printf("Nome do item a remover: ");
//    scanf(" %[^\n]", nome);

//    No* atual = mochilaLista;
//    No* anterior = NULL;

//    while (atual != NULL){
//        if (strcmp(atual->dados.nome, nome) == 0){
//            if (anterior == NULL)
//                mochilaLista = atual->proximo;
//            else
//                anterior->proximo = atual->proximo;

//            free(atual);
//            printf("Item removido!\n");
//            return;
//        }
//        anterior = atual;
//        atual = atual->proximo;
//    }
//    printf("Item não encontrado!\n");
//}

// Busca sequencial na lista
//No* buscarSequencialLista(char nome[]){
//    comparacoesSequencial = 0;

//    No* atual = mochilaLista;

//    while (atual != NULL){
//        comparacoesSequencial++;
//        if (strcmp(atual->dados.nome, nome) == 0)
//            return atual;

//        atual = atual->proximo;
//    }
//    return NULL;
//}

//=================================
// FUNÇÃO PRINCIPAL
//=================================

//int main(){

//    int estrutura;
//    int opcao;
//    char  nomeBusca[30];

//    printf("Escolha a estrutura: \n1 - Vetor\n2 - Lista Encadeada\n");
//    scanf("%d", &estrutura);

//    do {
//        printf("\n1 - Inserir\n2 - Remover\n3 - Listar\n4 - Buscar\n5 - Ordenar (vetor)\n0 - Sair\n");
//        scanf("%d", &opcao);

//        switch (opcao){

//        case 1:
//            if (estrutura == 1)
//                inserirItemVetor();
//            else
//                inserirItemLista();
//            break;

//        case 2:
//            if (estrutura == 1)
//                removerItemVetor();
//            else
//                removerItemLista();
//            break;

//        case 3:
//            if (estrutura == 1)
//                listarVetor();
//            else
//                listarLista();
//            break;

//        case 4:
//            printf("Nome do Item: ");
//            scanf(" %[^\n]", nomeBusca);

//            if (estrutura == 1){
//                int pos = buscarSequencialVetor(nomeBusca);
//                if (pos != -1)
//                    printf("Encontrado! Comparacoes: %d\n", comparacoesSequencial);
//                else
//                    printf("Nao encontrado! Comparacoes: %d\n", comparacoesSequencial);
//            } else {
//                No* resultado = buscarSequencialLista(nomeBusca);
//                if (resultado != NULL)
//                    printf("Encontrado! Comparacoes: %d\n", comparacoesSequencial);
//                else
//                    printf("Nao encontrado! Comparacoes: %d\n", comparacoesSequencial);
//            }
//            break;

//        case 5: {
//            if (estrutura == 1){
//                ordenarVetor();
//                printf("Vetor ordenado!\n");

//                printf("Nome para busca binaria: ");
//                scanf(" %[^\n]", nomeBusca);

//                int pos = buscarBinariaVetor(nomeBusca);

//                if (pos != -1)
//                    printf("Encontrado! Comparacoes: %d\n", comparacoesBinaria);
//                else
//                    printf("Nao encontrado! Comparacoes %d\n", comparacoesBinaria);

//            } else {
//                printf("Ordenacao so disponivel para vetor!\n");
//            }
//            break;
//        }
//    }
//} while (opcao != 0);

//    return 0;
//}



//--------------------------
// NIVEL: NOVATO
//--------------------------

//================================
// DEFINIÇÃO DA STRUCT ITEM
//================================

//typedef struct {
//    char nome[30];
//    char tipo[20];
//    int quantidade;
//}Item;

// Vetor que representa a mochila (max de 10 itens)
//Item mochila[10];

// Variavel que controla quantos itens existem na mochila
//int totalItens = 0;



//==========================
// Função para listar itens
//==========================

//void listarItens(){
//    printf("\n====== ITENS NA MOCHILA =====\n");

//    if (totalItens == 0){
//        printf("Mochila vazia.\n");
//        return;
//    }

//   for (int i = 0; i < totalItens; i++){
//        printf("\nItem %d\n", i + 1);
//        printf("Nome: %s\n", mochila[i].nome);
//        printf("Tipo: %s\n", mochila[i].tipo);
//        printf("Quantidade: %d\n", mochila[i].quantidade);
//    }
//}

//==========================
// Função para inserir item
//==========================

//void inserirItem(){

//    if (totalItens >= 10){
//        printf("\nMochila cheia! Não é possivel adicionar mais itens.\n");
//        return;
//    }

//    printf("\nDigite o nome do item: ");
//    scanf(" %29[^\n]", mochila[totalItens].nome);

//    printf("Digite o tipo (arma, munição, cura...): ");
//    scanf(" %19[^\n]", mochila[totalItens].tipo);

//    printf("Digite a quantidade: ");
//    scanf("%d", &mochila[totalItens].quantidade);

//    totalItens++;

//    printf("\nItem adicionado com sucesso!\n");

//    listarItens();
//}

//===============================
// Função de busca sequencial
//===============================
//void buscarItem(){
//    if (totalItens == 0){
//        printf("\nMochila vazia.\n");
//        return;
//    }

//    char nomeBusca[30];
//    int encontrado = 0;

//  printf("\nDigite o nome do item a buscar: ");
//    scanf(" %29[^\n]", nomeBusca);

//    for (int i = 0; i < totalItens; i++){
//        if (strcmp(mochila[i].nome, nomeBusca) == 0){

//            printf("\nItem encontrado!\n");
//            printf("Nome: %s\n", mochila[i].nome);
//            printf("Tipo: %s\n", mochila[i].tipo);
//            printf("Quantidade: %d\n", mochila[i].quantidade);

//            encontrado = 1;
//            break;
//        }
//    }

//    if (!encontrado){
//        printf("\nItem não encontrado.\n");
//    }
//}

//============================
// Função para reover ietns
//============================

//void removerItem(){

//    if (totalItens == 0){
//        printf("\nMochhila vazia.\n");
//        return;
//    }

//    char nomeRemover[30];
//    int posicao = -1;

//    printf("\nDigite o nome do item a remover: ");
//    scanf(" %29[^\n]", nomeRemover);

    // Busca de item
//    for (int i = 0; i < totalItens; i++){
//      if (strcmp(mochila[i].nome, nomeRemover) == 0){
//            posicao = i;
//            break;
//        }
//    }

//    if (posicao == -1){
//        printf("\nItem não encontrado.\n");
//        return;
//    }

    // Desloca os itens para preencher o espaço removido
//    for (int i = posicao; i < totalItens - 1; i++){
//        mochila[i] = mochila[i + 1];
//    }

//    totalItens--;
//    printf("\nItem removido com sucesso!/n");
//    listarItens;
//}


//=============================
// Função principal
//=============================

//int main(){

//    int opcao;

//    do {
//        printf("\n=========== MOCHILA ============\n");
//        printf("1 - Inserir item\n");
//        printf("2 - Remover item\n");
//        printf("3 - Listar itens\n");
//        printf("4 - Buscar item\n");
//        printf("0 - Sair\n");
//        printf("Escolha uma opção: ");
//        scanf("%d", &opcao);

//        switch (opcao){
//            case 1:
//            inserirItem();
//            break;

//            case 2:
//            removerItem();
//            break;

//            case 3:
//            listarItens();
//            break;

//            case 4:
//          buscarItem();
//          break;
//
//            case 0:
//            printf("\nSaindo da Mochila...\n");
//            break;

//            default:
//            printf("Opção Inalida!\n");
//
//        }
//    } while (opcao != 0);


//    return 0;
//}
