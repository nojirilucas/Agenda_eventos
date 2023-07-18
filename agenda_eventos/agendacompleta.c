#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define M 100
#define N 365
#define O 12

int id_unico = 1;

typedef enum STATUS_COMPROMISSO {
	A_SER_CUMPRIDO,
	ADIVAVEL,
	CANCELADO

} STATUS_COMPROMISSO;

typedef struct TDATA {
	int dia, mes, ano;
	int hora, minuto;
} TDATA;

typedef struct TCOMPROMISSO {
	char nome_do_compromisso[M];
	int identificador;
	int tipo_compromisso;
	bool adiavel;
	TDATA data;
	int duracao;
	STATUS_COMPROMISSO status;
	struct TCOMPROMISSO* prox_TCOMPROMISSO;
} TCOMPROMISSO;

typedef struct TAGENDA {
	char nome_professor[M];
	int ano;
	int id_agenda;
	TCOMPROMISSO* eventos;
	struct TAGENDA* prox_TAGENDA;
} TAGENDA;

void criaAgenda(TAGENDA* agenda, int idProf, char* nome, int ano);
int inicializa_compromisso(TCOMPROMISSO* comp, int tipo_compromisso, TDATA data, int duracao, char* nome);
void insereCompromisso(TAGENDA* agenda, int tipo_compromisso, TDATA data, int duracao, char* nome);
int showmenu();
void removeCompromisso(TAGENDA* agenda, int id);
void imprimeCompromisso(TCOMPROMISSO* comp);
void imprimeAgenda(TAGENDA* agenda);
int buscarAgenda(TAGENDA* Agenda,int id_agenda,int tipo_compromisso,TDATA data,int duracao,char* nome);
void imprimeCompromissosAdiados(TAGENDA* agenda);
//void imprimeCompromissosCancelados(TAGENDA* agenda);
//void imprimeCompromissosACumprir(TAGENDA agenda);
int retornaNcompromissos(TAGENDA* agenda);
int recuperaAgenda(TAGENDA *agenda, TDATA data);
void altera_prioridade(TCOMPROMISSO* comp);
void converte_duracao(int tempo_total, int* Duracao);
int retorna_prioridade(TCOMPROMISSO* comp);
void atribuiStatus(TCOMPROMISSO* comp, int novoStatus);
int retornaStatus(TCOMPROMISSO* comp);
bool Eadiavel(TCOMPROMISSO c, bool adiavel);
char* tipo_de_compromisso_string(int tipo_compromisso);
int temConflito(TCOMPROMISSO prim, TCOMPROMISSO novo);
float converte_hora_dia_minuto(float duracao, int tipo_compromisso);
int main();

#endif

int inicializa_compromisso(TCOMPROMISSO* comp, int tipo_compromisso, TDATA data, int duracao, char* nome) {
	strcpy(comp->nome_do_compromisso, nome);
	comp->tipo_compromisso = tipo_compromisso;
	comp->data = data;
	comp->duracao = duracao;
	comp->status = A_SER_CUMPRIDO;
	comp->adiavel = false;
	printf("Sucesso ao salvar compromisso:%d\n",++comp->identificador);
	return 1;
}

void insereCompromisso(TAGENDA* agenda, int tipo_compromisso, TDATA data, int duracao, char* nome) {
	TCOMPROMISSO* aux_compromisso = agenda->eventos;
	int id = 0;
	while (aux_compromisso->prox_TCOMPROMISSO != NULL) {
		id = aux_compromisso->identificador;
		aux_compromisso = aux_compromisso->prox_TCOMPROMISSO;
	}
	if (id == 0) {
		aux_compromisso->identificador = id;
	} else {
		aux_compromisso->identificador = id;
	}
	/*	printf("Digite o identificador da sua agenda:\n");
		int id_agenda;
		scanf("%d",&id_agenda);
		printf("buscando...\n");
		if(buscarAgenda(agenda,id_agenda, aux_compromisso->tipo_compromisso,aux_compromisso->data,aux_compromisso->duracao,agenda->nome_professor)==1){
	 		printf("inicializacao do compromisso.....\n");
	 		inicializa_compromisso(aux_compromisso,aux_compromisso->tipo_compromisso,aux_compromisso->data,aux_compromisso->duracao,nome); 
		}*/
	aux_compromisso->prox_TCOMPROMISSO = malloc(sizeof(TCOMPROMISSO));
	aux_compromisso = aux_compromisso->prox_TCOMPROMISSO;
	aux_compromisso->prox_TCOMPROMISSO = NULL;
}

void altera_prioridade(TCOMPROMISSO* comp) {
	while (1) {
		int novaPri;
		printf("DIGITE UMA OPCAO:\n");
		scanf("%d", &novaPri);
		if (novaPri <= 0 || novaPri >= 5) {
			printf(" Prioridade inexistente ;) \n");
		} else {
			comp->tipo_compromisso = novaPri;
			return;
		}
	}
}

int retorna_prioridade(TCOMPROMISSO* comp) {  // retornando mesma coisa que retornaStatus
	return comp->status;
}
int retornaStatus(TCOMPROMISSO* comp) {	 // retornando mesma coisa que retornaPrioridade
	return comp->status;
}

void atribuiStatus(TCOMPROMISSO* comp, int novoStatus) {
	if (comp->tipo_compromisso == 2 || comp->tipo_compromisso == 4) {
		printf(" Aulas e eventos nao podem ser adiados\n");
		return;
	} else {
		comp->status = novoStatus;
	}
}

/*ordem identificador, tipo, data, hora, duracao, nome de disciplina/aluno/reuniao/evento (ou razao), adiavel, status.*/
void imprimeCompromisso(TCOMPROMISSO* comp) {
	TDATA* dat;
	*dat = comp->data;

	printf(" Identificador do compromisso : %d \n", comp->identificador);
	printf(" Compromisso : %s \n", tipo_de_compromisso_string(comp->tipo_compromisso));
	printf(" Data : %d / %d / %d \n", dat->dia, dat->mes, dat->ano);
	printf(" Hora :  %d:%d\n", dat->hora, dat->minuto);
	printf(" Nome : %s \n", comp->nome_do_compromisso);

	int* Duracao = malloc(sizeof(int) * 3);
	converte_duracao(comp->duracao, Duracao);
	printf(" Duracao de dias : %d , horas : %d , minutos %d :  \n", Duracao[0], Duracao[1], Duracao[2]);

	// bool a= Eadiavel(comp->adiavel);

	printf(" Pode ser adiado? %s:\n", comp->adiavel ? "sim" : "não");
}

void imprimeCompromissosAdiados(TAGENDA* agenda) {
	TCOMPROMISSO* eventos = agenda->eventos;
	while (eventos->prox_TCOMPROMISSO != NULL) {
		if (eventos->status == 1)
			imprimeCompromisso(eventos);
	}
	eventos = eventos->prox_TCOMPROMISSO;
}

// void imprimeCompromissosCancelados(TAGENDA* agenda) {
// 	TCOMPROMISSO* eventos = agenda->eventos;
// 	while (eventos->prox_TCOMPROMISSO != NULL) {
// 		if (eventos->status == 2)
// 			imprimeCompromisso(eventos);
// 	}
// 	eventos = eventos->prox_TCOMPROMISSO;
// }

// void imprimeCompromissosACumprir(TAGENDA* agenda) {
// 	TCOMPROMISSO* eventos = agenda->eventos;
// 	while (eventos->prox_TCOMPROMISSO != NULL) {
// 		if (eventos->status == 0){
// 			imprimeCompromisso(eventos);
// 		}
// 	}
// 	eventos = eventos->prox_TCOMPROMISSO;
// }

int retornaNcompromissos(TAGENDA* agenda) {
	int numero_de_compromissos = 0;
	TCOMPROMISSO* eventos = agenda->eventos;
	while (eventos->prox_TCOMPROMISSO != NULL) {
			imprimeCompromisso(eventos);
			numero_de_compromissos++;
	}
	eventos = eventos->prox_TCOMPROMISSO;
	return numero_de_compromissos;
}

int retornaNadiamentos(TAGENDA* agenda){
	int numero_de_compromissos = 0;
	TCOMPROMISSO* eventos = agenda->eventos;
	while (eventos->prox_TCOMPROMISSO != NULL) {
		if (eventos->status == 1){
			numero_de_compromissos++;
		}
	}
	eventos = eventos->prox_TCOMPROMISSO;
	return numero_de_compromissos;
}

int retornaNcancelamentos(TAGENDA* agenda){
	int numero_de_compromissos = 0;
	TCOMPROMISSO* eventos = agenda->eventos;
	while (eventos->prox_TCOMPROMISSO != NULL) {
		if (eventos->status == 2){
			numero_de_compromissos++;
		}
	}
	eventos = eventos->prox_TCOMPROMISSO;
	return numero_de_compromissos;
}

/*ordem identificador, tipo, data, hora, duracao, nome de disciplina/aluno/reuniao/evento (ou razao), adiavel, status.*/
void converte_duracao(int tempo_total, int* Duracao) {
	Duracao[0] = tempo_total / 1440;
	tempo_total = (tempo_total - (1440 * Duracao[0]));
	Duracao[1] = tempo_total / 60;
	Duracao[2] = tempo_total % 60;
}

bool Eadiavel(TCOMPROMISSO c, bool adiavel) {
	if (c.tipo_compromisso == 2 || c.tipo_compromisso == 4) {  // ser for aula ou evento não podera ser adiado, outros compromisso podem ser adiados.
		printf("NAO E ADIVAVEL\n");
		adiavel = false;
		return adiavel;
	} else {
		printf("ADIVAVEL\n");  //status tem que mudar para true;
		adiavel = true;
		return adiavel;
	}
}

char* tipo_de_compromisso_string(int tipo_compromisso) {
	switch (tipo_compromisso) {
	case 1:
		return "ORIENTACÃO";
	case 2:
		return "AULA";
		// return "COMPROMISSO PARTICULAR";
	case 3:
		return "EVENTO";
	case 4:
		return "REUNIÃO";
	default:
		return "TIPO INVALIDO";
	}
}

//printf("Tipo de compromisso: %s",tipo_de_compromisso_string(t));
int temConflito(TCOMPROMISSO prim, TCOMPROMISSO novo) {
	if (prim.tipo_compromisso != 4 && novo.tipo_compromisso != 4) {
		float novo_duracao;	 //(float)novo.duracao;
		float prim_duracao;	 //(float)prim.duracao;
		if (prim.data.dia == novo.data.dia && prim.data.mes == novo.data.mes) {
			prim_duracao = converte_hora_dia_minuto((float)prim.duracao, prim.tipo_compromisso);
			novo_duracao = converte_hora_dia_minuto((float)novo.duracao, novo.tipo_compromisso);
			if (((prim.data.hora <= novo.data.hora) && (prim.data.hora + prim_duracao >= novo.data.hora) || (novo.data.hora <= prim.data.hora) && (novo.data.hora + novo_duracao) >= prim.data.hora)) {
				return printf("Conflito;\n");
			} else {
				return printf("Sem conflito\n");
			}
		} else {
			printf("Sem conflito\n");
		}
	}
	if (prim.tipo_compromisso == 4 || novo.tipo_compromisso == 4) {
		float dias_duracao;
		if (prim.tipo_compromisso == 4) {
			dias_duracao = converte_hora_dia_minuto(prim.duracao, prim.tipo_compromisso);  // recebe duracao em dias
			if (novo.data.dia >= prim.data.dia && prim.data.dia + dias_duracao >= novo.data.dia && prim.data.mes == novo.data.mes) {
				return printf("Conflito;\n");
			} else {
				printf(" Sem conflito\n");
			}
		} else {
			dias_duracao = converte_hora_dia_minuto(novo.duracao, novo.tipo_compromisso);
			if (prim.data.dia >= novo.data.dia && novo.data.dia + dias_duracao >= prim.data.dia && prim.data.mes == novo.data.mes) {
				return printf("Conflito;\n");
			} else {
				printf(" Sem conflito\n");
			}
		}
	}
}

float converte_hora_dia_minuto(float duracao, int tipo_compromisso) {
	if (tipo_compromisso == 4) {
		float dia, dia_horas = 24.00;
		return duracao / dia_horas;
	} else {
		float hora_minutos = 60.00;
		return duracao / hora_minutos;
	}
}

int showmenu() {
  int op;
  while (op < 1 || op > 13) {
    printf(" ---Bem Vindo a agenda, digite o numero da acao a ser tomada---\n \n");
    printf("  1-Criar Agenda\n");
    printf("  2-Inserir Compromisso\n");
    printf("  3-Recuperar Agenda\n");
    printf("  4-Inicializa compromisso\n");
    printf("  5-Remover Compromisso\n");
    printf("  6-Numero de adiados\n");
    printf("  7-Numero de cancelados\n");
    printf("  8-Total de compromissos\n");
    printf("  9-Visualizar cancelados\n");
    printf("  10-Visualizar adiados\n");
    printf("  11-Visualizar a cumprir\n");
    printf("  12-Imprimir Agenda\n");
    printf("  13-Sair\n");
    scanf("%d", &op);
    if (op < 1 || op > 13) {
      printf("Opçao Incorreta!!");
    }
  }
  return op;
}

void criaAgenda(TAGENDA* agenda, int idProf, char* nome, int ano) {
  agenda = malloc(sizeof(TAGENDA));
  agenda->prox_TAGENDA = NULL;
  agenda->eventos = malloc(sizeof(TCOMPROMISSO));
  agenda->eventos->prox_TCOMPROMISSO = NULL;
  agenda->id_agenda = idProf;
  strcpy(agenda->nome_professor, nome);
  agenda->ano = ano;
  printf("Seu ID:%d\n",agenda->id_agenda);
}

void imprimeAgenda(TAGENDA* agenda) {
  TCOMPROMISSO* eventos = agenda->eventos;
      int i, j, min,k;
          TCOMPROMISSO comp;
          for (i = 0;eventos!=NULL; i++) {
              min = i;
              for (j = i + 1;eventos!=NULL; j++) {
                if( agenda->eventos[j].data.mes == agenda->eventos[min].data.mes ){
                  if( agenda->eventos[j].data.dia < agenda->eventos[min].data.dia ){
                    comp = agenda->eventos[min];
                    agenda->eventos[min] = agenda->eventos[j];
                    agenda->eventos[j] = comp;
                    min = j;
                  }
                  if( agenda->eventos[j].data.dia == agenda->eventos[min].data.dia ){
                    if (agenda->eventos[j].tipo_compromisso == agenda->eventos[min].tipo_compromisso) {
                      if(agenda->eventos[j].tipo_compromisso < agenda->eventos[min].tipo_compromisso){
                        comp = agenda->eventos[min];
                        agenda->eventos[min] = agenda->eventos[j];
                        agenda->eventos[j] = comp;
                        min = j;
                      }
                    }
                  }
                }
              }
          }
  while (eventos->prox_TCOMPROMISSO != NULL) {
    imprimeCompromisso(eventos);
}
  eventos = eventos->prox_TCOMPROMISSO;
}

int recuperaAgenda(TAGENDA *agenda, TDATA data) {
  int numero_de_compromissos = 0;
  for (int i = 0;agenda->eventos != NULL;i++){
      if (agenda->eventos[i].data.mes <= 12 && agenda->eventos[i].data.mes >= 1) {
        if (data.mes == agenda->eventos[i].data.mes) {
          if (data.dia < agenda->eventos[i].data.dia) {
            numero_de_compromissos++;
          }
        }
        if (data.mes < agenda->eventos[i].data.mes) {
          numero_de_compromissos++;
        }
      } 
      else {
         printf("SEM COMRPOMISSOS APOS %d/%d \n", data.dia, data.mes);
         break;
    }
  }
  printf("\nProfessor:%s\nAno:%d\nNumero de compromissos apos a data:%d\n",
       agenda->nome_professor, agenda->ano,numero_de_compromissos);
}

int buscarAgenda(TAGENDA* Agenda,int id_agenda,int tipo_compromisso,TDATA data,int duracao,char* nome){
  TAGENDA* aux_agenda=Agenda->prox_TAGENDA;
    while (aux_agenda!=NULL){
      printf("Comparando IDs...\n");
        if(id_agenda == aux_agenda->id_agenda){
            printf("ID Encotrado!\n");
            return 1;
        }
    }
     printf("ID INVALIDO\n");
}

int main() {
  TAGENDA* Agenda = malloc(sizeof(TAGENDA));
  Agenda->eventos = malloc(sizeof(TCOMPROMISSO));
  Agenda->prox_TAGENDA = NULL;
  Agenda->eventos->prox_TCOMPROMISSO = NULL;  //inicializacao de agenda e evento
  TDATA data;
  int tipo_compromisso, duracao, ano;
  char nome[50];
  int op = -1;

  while (1) {
    op = showmenu();
    switch (op) {
      case 1: 
        printf("Nome do professor:\n");
        getchar();
        gets(aux_agenda->nome_professor);
        printf("Ano:\n");
        scanf("%d",&aux_agenda->ano);
        criaAgenda(Agenda,id_unico,Agenda->nome_professor,Agenda->ano);
        id_unico++;
        break;

      case 2:
        printf("Digite o tipo de compromisso:\n");
        fflush(stdin);
        scanf("%d", &tipo_compromisso);
        printf("Digite a data dia/mes:\n");
        fflush(stdin);
        scanf("%d%d", &data.dia, &data.mes);
        printf("Digite a hora marcada:\n");
        fflush(stdin);
        scanf("%d%d", &data.hora, &data.minuto);
        printf("Digite a duracao:\n");
        fflush(stdin);
        scanf("%d", &duracao);
        printf("Digite o nome do compromisso:\n");
        getchar();
        gets(nome);

        insereCompromisso(Agenda, tipo_compromisso, data, duracao, nome);
          break;

      case 3:
        printf("Digite uma data...Dia e Mes\n");
        scanf("%d%d",&data.dia,&data.mes);
        recuperaAgenda(Agenda,data);
          break;

      case 4:
        printf("Digite o identificador da sua agenda:\n");
        scanf("%d",&aux_agenda->id_agenda);
        printf("buscando...\n");
          if(buscarAgenda(Agenda,aux_agenda->id_agenda, tipo_compromisso, data, duracao,Agenda->nome_professor)==1){
            printf("inicializacao do compromisso.....\n");
            inicializa_compromisso(Agenda->eventos,Agenda->eventos->tipo_compromisso,Agenda->eventos->data,Agenda->eventos->duracao,Agenda->eventos->nome_do_compromisso);
          }
            break;

      case 5:
        removeCompromisso(Agenda,Agenda->id_agenda);
        break;

      case 6:
        printf("Numero:%d\n",retornaNadiamentos(Agenda));
        break;
          
      case 7:
        printf("Numero:%d\n",retornaNcancelamentos(Agenda));
        break;
          
      case 8:
        printf("Numero:%d\n",retornaNcompromissos(Agenda));
        break;
          
      case 9:
        imprimeCompromissosCancelados(Agenda);;
        break;
          
      case 10:
        imprimeCompromissosAdiados(Agenda);
        break;
          
      case 11:
        imprimeCompromissosACumprir(Agenda);
        break;
          
      case 12:
        imprimeAgenda(Agenda);
        break;
          
      case 13:
        return 0;
    }
  }
}