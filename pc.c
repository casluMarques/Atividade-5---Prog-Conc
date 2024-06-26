#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//criando a struct que armazena os argumentos a serem utilizados pela thread
typedef struct
{
    int *end_vetor, indice;
} t_Args;

//função a ser executada pelas Threads
void *QuadradoVetor (void *arg){
	t_Args args = *(t_Args*) arg;
	args.end_vetor = args.end_vetor+args.indice;
	*args.end_vetor = *args.end_vetor * *args.end_vetor;
	//printf("Vetor na posição %d, com valor atualizado %d\n", args.indice, *args.end_vetor);
    pthread_exit(NULL);
}


//fluxo principal do programa

int main (int argc, char* argv[]){
    int nthreads; /*número de threads, passado como argumento na
    chamada do executável */
    if(argc<2){  //verificando se foram passados os parâmetros
        printf("--ERRO: A quantidade de threads não foi informada, <%s><nthreads>\n", argv[0]);
        exit(-1);
    }
    //passando so argumentos inseridos por linha de comando para int
    nthreads = atoi(argv[1]);  

	int vec[nthreads];//vetor a ser inicializado
	for(int i =0; i < nthreads; i++ ){ //loop para inicialização dos valores do vetor
		int val_user;
		printf("Valor do vetor na posição %d:\n", i);
		scanf("%d",&val_user);
		vec[i] = val_user;

	}



    pthread_t id_tds_sys[nthreads]; //criando lista com os identificadores das threads a serem criadas

    t_Args *args; //criando ponteiro para a variável que receberá os argumentos das threads 
    //criando as threads, por um loop for

    for(int i =0; i < nthreads; i++ ){ //loop para criação e incialização das threads
        printf("--Alocando e preenchendo argumentos para a thread %d\n", i);
        args = malloc(sizeof(t_Args));
        if (args == NULL){
            printf("Erro na alocação de memória\n");
            exit(-1);}
		//int val = vec[i];
        args->end_vetor = &vec;
		args->indice = i;
        printf("##Criando thread %d\n", i);
        if(pthread_create(&id_tds_sys[i], NULL, QuadradoVetor, (void *) args)){
            printf("Erro na criação da thread %d\n", i);
            exit(-1);
            }
    }
     //--espera todas as threads terminarem
  	for (int i=0; i<nthreads; i++) {
    	if (pthread_join(id_tds_sys[i], NULL)) {
         	printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  }
    printf("Fim da execução da thread MAIN\n");
	
	for(int i =0; i < nthreads; i++ ){ //loop para printar os valores atualizados do vetor
		printf("Novos valores no vetor:\n");
		printf("Posição no vetor:%d\nValor:%d\n",i, vec[i]);
	}
	
    pthread_exit(NULL);

	
    //}
    
    
    
    
    return 0;
}