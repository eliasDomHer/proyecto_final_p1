#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct Usuario{
  char name[50];
  char password[30];
  int votado;
} usr;

typedef struct Candidato{
  char name[100];
  char team[50];
  int votes;
} cand;

void menu(usr * user);

void votar(cand * candidato);

int main () {
  usr user;
  int tamCand = 0, tamUsr = 0;
  int votacionesFinalizadas = 0;
  int numeroDeVotos = 0;

  cand ** candidatos = (cand **)malloc(sizeof(cand *));
  *candidatos = (cand *)malloc(sizeof(cand));

  usr ** usuarios = (usr **)malloc(sizeof(usr *));
  *usuarios = (usr *)malloc(sizeof(usr));

  do {
    menu(&user);
  /********************************Verificación de administrador*******************************/
    if (strcmp(user.name, "admin") == 0) {
      if (strcmp(user.password, "1234") == 0) {

        int opcAdmin;
        do {
          printf("Bienvenido administrador\n");
          printf("\n1.- Cargar candidatos");
          printf("\n2.- Cargar electores");
          printf("\n3.- Finalizar votación");
          printf("\n4.- Salir\n");
          scanf("%d", &opcAdmin);

          if (opcAdmin == 1) {
          /************************Cargar Candidatos**************************/
            char nomArchivoCand[20];
            printf("\nIngrese el nombre de su archivo con su extensión: ");
            scanf("%s", &nomArchivoCand);

            FILE * fCands = fopen(nomArchivoCand, "r");
            if (fCands == NULL) {
              printf("Error al abrir archivo %s", nomArchivoCand);
              return -1;
            }

            int i = 0;
            char nombreTemp[40];
            int temp;

            while (!feof(fCands)) {
              fgets(nombreTemp, 40, fCands);
              strtok(nombreTemp, "\n");
              strcpy(candidatos[i]->name, nombreTemp);

              fflush(stdin);
              fgets(nombreTemp, 40, fCands);
              strtok(nombreTemp, "\n");
              strcpy(candidatos[i]->team, nombreTemp);

              fscanf(fCands, "%d", &temp);
              candidatos[i]->votes = temp;
              fflush(stdin);

              fgets(nombreTemp, 40, fCands);

              i++;

              candidatos = (cand **)realloc(candidatos, sizeof(cand *)*(i+1));
              candidatos[i] = (cand *)malloc(sizeof(cand));
            }

            printf("\nCandidatos cargados exitosamente!\n\nLos candidatos son lo siguientes:");
            for (int j = 0; j < i; j++) {
              printf("\nCandidato %d: %s ", j+1, candidatos[j]->name);
              printf("| %s ", candidatos[j]->team);
              printf("| Votos: %d |\n", candidatos[j]->votes);
            }
            tamCand = i;
            fclose(fCands);

            printf("\nPresione una tecla para regresar al menu de administrador...");
            getch();
            system("cls");
          /************************Cargar Candidatos**************************/
          } else if (opcAdmin == 2) {
          /************************Cargar Usuarios**************************/
            char nomArchivoUsr[20];
            printf("\nIngrese el nombre de su archivo con su extensión: ");
            fflush(stdin);
            scanf("%s", &nomArchivoUsr);

            FILE * fUsers = fopen(nomArchivoUsr, "rb");
            if (fUsers == NULL) {
              printf("Error al abrir archivo %s", nomArchivoUsr);
              return -1;
            }
            
            int i = 0;
            char nombreTemp[40];
            int temp;

            while (!feof(fUsers)) {
              fread(usuarios[i], sizeof(usr), 1, fUsers);
              i++;
              usuarios = (usr **)realloc(usuarios, sizeof(usr *)*(i+1));
              usuarios[i] = (usr *)malloc(sizeof(usr));
            }

            printf("\nUsuarios cargados exitosamente!\n\nLos usuarios son lo siguientes:");
            for (int j = 0; j < i-1; j++) {
              printf("\nUsuario %d: %s ", j+1, usuarios[j]->name);
              printf("| %s ", usuarios[j]->password);
              printf("| Bandera de votación: %d", usuarios[j]->votado);
            }
            tamUsr = i-1;
            fclose(fUsers);

            printf("\nPresione una tecla para regresar al menu de administrador...");
            getch();
            system("cls");
          /************************Cargar Usuarios**************************/
          } else if (opcAdmin == 3) {
          /*********************Finalizar Votación*******************************/
            FILE * fResult = fopen("resultados.bin", "wb");
            if (fResult == NULL) {
              printf("Error al crear archivo %s", "resultados.bin");
              return -1;
            }

            for (int i = 0; i < tamCand; i++) {
              fwrite(candidatos[i], sizeof(cand), 1, fResult);
            }
            fclose(fResult);
            votacionesFinalizadas = 1;

            printf("\nPresione una tecla para regresar al menu de administrador...");
            getch();
            system("cls");
          /*********************Finalizar Votación*******************************/
          } else if (opcAdmin == 4) {
            printf("\nSaliendo...");

          } else printf("\nOpción incorrecta, favor de verificar");

        } while (opcAdmin != 4);

      } else printf("\nContraseña de administrador INCORRECTA");
    }
  /********************************Verificación de administrador*******************************/

  /********************************Verificación de usuario*******************************/

    int j = 0, login = 0, pass = 0;
    do { 
      if (strcmp(user.name, (usuarios[j])->name) == 0) {
        if (strcmp(user.password, (usuarios[j])->password) == 0) {
          login = 1;

          int opcUsr;
          do {
            printf("\nBienvenido %s", (usuarios[j])->name);
            printf("\n1.- Votar");
            printf("\n2.- Anular Voto");
            printf("\n3.- Ver resultados");
            printf("\n4.- Salir\n");
            scanf("%d", &opcUsr);

            if (opcUsr == 1) {
              int voto;
              if (usuarios[j]->votado == 1) {
                printf("\nEl usuario: %s ya ha emitido su voto, no puede votar dos veces", usuarios[j]->name);
              } else {
                if (votacionesFinalizadas == 1) {
                  printf("\nUsted ya no puede votar, la votación ha finalizado");
                } else {
                  for (int i = 0; i < tamCand; i++) {
                    printf("\nCandidato %d (%s, %s)", i+1, candidatos[i]->name, candidatos[i]->team);
                  }
                  printf("\nRegresar: -1\n");
                  scanf("%d", &voto);

                  if (voto != -1) {
                    votar(candidatos[voto-1]);
                    numeroDeVotos++;
                    printf("\nVoto exitoso por el candidato %s", candidatos[voto-1]->name);
                  }
                
                  usuarios[j]->votado = 1;
                }
              }

            } else if (opcUsr == 2) {
              printf("\nVoto anulado");
              usuarios[j]->votado = 1;
            } else if (opcUsr == 3) {

              if (votacionesFinalizadas == 1) {
                FILE * fResult = fopen("resultados.bin", "rb");
                if (fResult == NULL) {
                  printf("Error al abrir archivo %s", "resultados.bin");
                  return -1;
                }

                cand prueba[20];

                for (int i = 0; i < tamCand; i++) {
                  fread(&prueba[i], sizeof(cand), 1, fResult);
                  printf("\nCandidato %d: %s | %s | Votos: %d",i+1, prueba[i].name, prueba[i].team, prueba[i].votes);
                }

                printf("\nNumero de votos: %d",numeroDeVotos);
                for (int i = 0; i < tamCand; i++) {
                float porcentaje = (float)(prueba[i].votes*100)/numeroDeVotos;
                printf("\n%s: %.1f%%", prueba[i].name, porcentaje);
                }

                cand temp;
                for (int i = 1; i < tamCand; i++) {
                  for (int j = 0; j < tamCand-1; j++)
                  {
                    if (prueba[j].votes < prueba[j+1].votes) {
                      temp = prueba[j];
                      prueba[j] = prueba[j+1];
                      prueba[j+1] = temp;
                    }
                  }
                }

                if (prueba[0].votes == prueba[1].votes) {
                  printf("\nHubo un empate entre %s y %s\n", prueba[0].name, prueba[1].name);
                } else printf("\nEl ganador de las elecciones es: %s",prueba[0].name);

              } else printf("\nLa votación aún no ha finalizado, usted no puede ver los resultados todavía");
              
            } else if (opcUsr == 4) {
              printf("\nSaliendo...");

            } else printf("\nOpción incorrecta, favor de verificar");

          } while (opcUsr != 4);

        } else printf("\nContraseña de %s INCORRECTA", usuarios[j]->name);
      } else pass = 1;
      j++;
    } while (j < tamUsr);
    if (login == 0 && pass == 1) printf("\nEl usuario %s no existe", user.name);
  
  /********************************Verificación de usuario*******************************/
  } while (1==1);
  
  return 0;
}

void menu(usr * user) {
  int salir;
  fflush(stdin);
  printf("\n---------------------------------------------------------------------------");
  printf("\n|\t\t\tVotaciones FCC - BUAP");
  printf("\n|\t\t\tUsuario: ");
  gets(user->name);
  printf("|\t\t\tContraseña: ");
  gets(user->password);
  printf("---------------------------------------------------------------------------");
  printf("\nSi desea salir del programa, digite 0\n");
  printf("\nSi desea continuar, digite 1\n");
  fflush(stdin);
  scanf("%d", &salir);
  if (salir == 0) exit(0);
}

void votar(cand * candidato) {
  candidato->votes++;
}
