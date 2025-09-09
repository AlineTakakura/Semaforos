#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int tempo_utilizar_recurso;
    char estado[30];
}Processo;

void down(int * semaforo, Processo * processo_solicitante);
void up(int * semaforo, Processo * processo_solicitante, Processo * outro_processo);

//Possíveis estados: Em espera, Utilizando recurso , Bloqueado;
int main(){
    //semaforo 0 --  Utilizando recurso, semaforo 1 -- Recurso liberado
    int semaforo = 1;
    int vez_de = 1;
    int mudar_de_vez = 2;

    Processo p1;
    p1.tempo_utilizar_recurso =2;
    strcpy(p1.estado,"Em espera");

    Processo p2;
    p2.tempo_utilizar_recurso =5;
    strcpy(p2.estado,"Em espera");

    int isRunning =1;
    int contador_tempos = 0;
    int contador_execucao1 =0;
    int contador_execucao2 = 0;

    while(isRunning){
        if(contador_tempos == 0){
            char placeholder[20] = " ";
            printf("TEMPO %d (Estado inicial)\n", contador_tempos);
            printf("%-35s %-35s %-35s %-35s\n", "Processo 1", "Semaforo", "Vez de", "Processo 2");
            printf("%-35s %-35d %-35d %-35s\n", p1.estado, semaforo, vez_de, p2.estado);
            printf("Executando: %-57d %-37s Executando: %-12d\n\n",contador_execucao1,placeholder,contador_execucao2);
        }
        else{
            if(contador_execucao1 == p1.tempo_utilizar_recurso){
                up(&semaforo,&p1,&p2);
                contador_execucao1 =0;
            }
            if(contador_execucao2 == p2.tempo_utilizar_recurso){
                up(&semaforo,&p2,&p1);
                contador_execucao2 =0;
            }

            if(vez_de == 1 && strcmp(p1.estado,"Em espera")==0){
                down(&semaforo,&p1);
            }
            if (vez_de == 2 && strcmp(p2.estado,"Em espera")==0){
                down(&semaforo,&p2);
            }

            if(strcmp(p1.estado,"Utilizando recurso")==0){
                contador_execucao1++;
            }
            else if(strcmp(p2.estado,"Utilizando recurso")==0){
                contador_execucao2++;
            }
            
            if((contador_tempos%mudar_de_vez) == 0){
               if(vez_de == 1){
                    vez_de =2;
                }
                else if(vez_de == 2){
                    vez_de =1;
                } 
            }
           
            char placeholder[20] = " ";
            printf("TEMPO %d\n", contador_tempos);
            printf("%-35s %-35s %-35s %-35s\n", "Processo 1", "Semaforo", "Vez de", "Processo 2");
            printf("%-35s %-35d %-35d %-35s\n", p1.estado, semaforo, vez_de, p2.estado);
            printf("Executando: %-57d %-37s Executando: %-12d\n\n",contador_execucao1,placeholder,contador_execucao2);
        }
        
        char esperar;
        scanf("%c", &esperar);
        contador_tempos++;
    }


}

void down(int * semaforo, Processo * processo_solicitante){
    if(*semaforo>0){
        *semaforo = *semaforo -1;
        strcpy(processo_solicitante->estado,"Utilizando recurso"); 
    }
    else{
        strcpy(processo_solicitante->estado,"Bloqueado");
    }

}

void up(int * semaforo, Processo * processo_solicitante, Processo * outro_processo){

    strcpy(processo_solicitante->estado,"Em espera");
    *semaforo = *semaforo +1;
    if(strcmp(outro_processo->estado,"Bloqueado") == 0){
       down(semaforo,outro_processo);
    }

}

