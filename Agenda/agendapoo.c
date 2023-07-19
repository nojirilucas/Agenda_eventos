#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define M 50

int id_unico = 0;

typedef struct
{
  char *assunto;
  char *local;
  char *nomeniver;
  int prioridade, grau;
  int horaini, horafim;
  int tipo;
  int obg;
}EVENTO;

typedef struct USUARIO
{
	char *nome;
	char *email;
  EVENTO eventos[24];
}USUARIO;

USUARIO usuarios[M];

int menuPrincipal(int opt)
{
  printf("Digite um opcao:\n 1 - cria usuario\n 2 - listar usuarios\n 3 - acessa agenda\n0 - sair\n\t");
  scanf("%d",&opt);
  return opt;
}

int menuAgenda(int opt)
{
  printf("Digite um opcao:\n 1 - criar niver\n 2 - criar tarefa\n 3 - criar reuniao\n 4 - show agenda\n"
         " 0 - sair\n\t");
  scanf("%d",&opt);
  return opt;
}

USUARIO cria_usuario()
{
  USUARIO novo;
  novo.nome = (char*) malloc(sizeof(char) * M);
  novo.email = (char*) malloc(sizeof(char) * M);
  printf("Digite o nome: \n");
  setbuf(stdin,NULL);
  fgets(novo.nome, M, stdin);
  printf("Digite o email: \n");
  setbuf(stdin,NULL);
  fgets(novo.email, M, stdin);
  for(int i = 0; i < 24; i++)
  {
    novo.eventos[i].tipo = 0;
  }
  return novo;
}

EVENTO criareuniao()
{
  EVENTO novo;
  novo.local = (char*) malloc(sizeof(char) * M);
  novo.assunto = (char*) malloc(sizeof(char) * M);
  printf("Digite sobre qual assunto: \n");
  setbuf(stdin,NULL);
  fgets(novo.assunto, M, stdin);
  printf("Digite o horario inicial: \n");
  scanf("%d", &novo.horaini);
  printf("Digite o horario final: \n");
  scanf("%d", &novo.horafim);
  printf("Digite 1 - obrigatorio ou 0 - nao obrigatorio: \n");
  scanf("%d", &novo.obg);
  return novo;
}

EVENTO criatarefa()
{
  EVENTO novo;
  novo.assunto = (char*) malloc(sizeof(char) * M);
  novo.local = (char*) malloc(sizeof(char) * M);
  printf("Digite o grau de prioridade: \n");
  scanf("%d", &novo.prioridade);
  printf("Digite o grau de esforco: \n");
  scanf("%d", &novo.grau);
  printf("Digite sobre qual assunto: \n");
  setbuf(stdin,NULL);
  fgets(novo.assunto, M, stdin);
  printf("Digite o horario inicial: \n");
  scanf("%d", &novo.horaini);
  printf("Digite o horario final: \n");
  scanf("%d", &novo.horafim);
  printf("Digite o local: \n");
  setbuf(stdin,NULL);
  fgets(novo.local, M, stdin);
  return novo;
}

EVENTO crianiver()
{
  EVENTO novo;
  novo.nomeniver = (char*) malloc(sizeof(char) * M);
  novo.local = (char*) malloc(sizeof(char) * M);
  novo.assunto = (char*) malloc(sizeof(char) * M);
  printf("Digite sobre qual assunto: \n");
  setbuf(stdin,NULL);
  fgets(novo.assunto, M, stdin);
  printf("Digite o nome do aniversariante: \n");
  setbuf(stdin,NULL);
  fgets(novo.nomeniver, M, stdin);
  printf("Digite o horario inicial: \n");
  scanf("%d", &novo.horaini);
  printf("Digite o horario final: \n");
  scanf("%d", &novo.horafim);
  printf("Digite o local: \n");
  setbuf(stdin,NULL);
  fgets(novo.local, M, stdin);
  return novo;
}

void listar_usuarios()
{
  if (id_unico == 0)
  {
    printf("nenhum usuario registrado\n");
    return;
  }
  for (int i = 0; i < id_unico ; i++)
  {
    printf("usario %d\n",i);
    printf("nome: %s\n", usuarios[i].nome);
    printf("email: %s\n", usuarios[i].email);
  }
}

int verificarHorario(int id_usuario,EVENTO evento)
{
    if(evento.horaini<0 || evento.horaini>23 || evento.horafim<0 || evento.horafim>23)
    {
        printf("Horario Invalido\n");
        return 0;
    }
    if(usuarios[id_usuario].eventos[evento.horaini].tipo != 0)
    {
        printf("Horario Ocupado\n");
        return 0;
    }
    return 1;
}

int verificargrau(int id_usuario,EVENTO evento)
{
    if(evento.grau<1 || evento.grau>5)
    {
        printf("Grau invalido, favor digite um grau entre 1 a 5\n");
        return 0;
    }
    return 1;
}

int verificarPrioridade(int id_usuario,EVENTO evento)
{
    if(evento.prioridade<0 || evento.prioridade>10)
    {
        printf("Prioridade Invalida, favor digite uma prioridade entre 1 a 10\n");
        return 0;
    }
    return 1;
}

void showAgenda(int id_usuario){
     printf("\nAGENDA:\n\n");
     for (int i = 0; i < 24 ; i++)
  {
         if(usuarios[id_usuario].eventos[i].tipo != 0)
         {
             printf("Assunto: %s\n", usuarios[id_usuario].eventos[i].assunto);
             printf("Hora inicio: %d\n", usuarios[id_usuario].eventos[i].horaini);
             printf("Hora fim: %d\n", usuarios[id_usuario].eventos[i].horafim);

             //niver
             if (usuarios[id_usuario].eventos[i].tipo == 1)
             {
                 printf("Local: %s", usuarios[id_usuario].eventos[i].local);
                 printf("Nome do aniverariante: %s", usuarios[id_usuario].eventos[i].nomeniver);
             }

             //tarefa
             if (usuarios[id_usuario].eventos[i].tipo == 2)
             {
                 printf("Prioridade: %d", usuarios[id_usuario].eventos[i].prioridade);
                 printf("Grau de esforco: %d", usuarios[id_usuario].eventos[i].grau);
             }

             //reuniao
             if (usuarios[id_usuario].eventos[i].tipo == 3)
             {
                 printf("Local: %s", usuarios[id_usuario].eventos[i].local);
                 printf("1 (obrigatorio) 0 (nao obrigatorio), %d", usuarios[id_usuario].eventos[i].obg);
             }
         }
  }
}

void agenda(int id_usuario)
{
    EVENTO novo;
    int opt = -1;
    int verificador = 1;
  while(opt != 0)
  {
    opt = menuAgenda(opt);
    switch (opt)
    {
      case 1:
          novo = crianiver();
          verificador = verificarHorario(id_usuario,novo);
          if(verificador == 1)
          {
              usuarios[id_usuario].eventos[novo.horaini] = novo;
          }
          break;
      case 2:
          novo = criatarefa();
          verificador = verificarHorario(id_usuario,novo);
          if(verificador == 1)
          {
              verificador = verificarPrioridade(id_usuario,novo);
              if(verificador == 1)
              {
                  verificador = verificargrau(id_usuario,novo);
                  if(verificador == 1){
                usuarios[id_usuario].eventos[novo.prioridade] = novo;
                  }
              }
          }
          break;
      case 3:
          novo = criareuniao();
          verificador = verificarHorario(id_usuario,novo);
          if(verificador == 1)
          {
              usuarios[id_usuario].eventos[novo.horaini] = novo;
          }
          break;
      case 4:
        showAgenda(id_usuario);
            break;
      case 0:
            break;
      default:
          printf("opcao invalida\n");
            break;
    }
  }
}

void acessagenda()
{
  char *nome = (char*) malloc(sizeof(char) * M);
  printf("Digite o nome: \n");
  setbuf(stdin,NULL);
  fgets(nome, M, stdin);
   for (int i = 0; i < id_unico ; i++)
   {
    if (strcmp(nome, usuarios[i].nome) == 0)
    {
      agenda(i);
      return;
    }
   }
  printf("Usuario Nao Encontrado\n");
  return;

}

void main() 
{
  int opt = -1;
  while(opt != 0)
  {
    opt = menuPrincipal(opt);
    switch (opt) 
    {
      case 1:
        usuarios[id_unico] = cria_usuario();
        id_unico++;
        break;
      case 2:
        listar_usuarios();
          break;
      case 3:
        acessagenda();
          break;
      case 0:
            break;
      default:
          printf("opcao invalida\n");
            break;
    }
  }
}
