#include <stdio.h>
#include <stdlib.h>

//#define NOMBRE_ARCHIVO "C:/Users/joyri/Desktop/examen3progra/p1/pacientes.bin"

typedef struct Usuario{
  char name[50];
  char password[30];
  int votado;
}usr;

int escribirArchivo(usr users[], int tam, const char *nombreArchivo); //pasamos de la memoria al archivo
int leerArchivo(usr users[], int tam, const char *nombreArchivo); //pasamos del archivo a la memoria
void imprimirusrs(usr users[], int tam);
void imprimirusr(usr *user);

int main () {
  usr usrsABinario[] = { 
    {"DescafiBb", "garinhogonzales34", 0},
    {"derdeivel", "deysi123", 0},
    {"MrAlmang", "aldoaldito1", 0},
    {"ElMataViejitas", "levoyalnecaxa1", 0},
    {"BatmanRegresa", "elcaballerooscuro17", 0},
    {"ManoPocha32", "cochiloco2", 0}
   };

  const int tam = sizeof(usrsABinario) / sizeof(usr);
  usr binarioAusrs[tam];
  imprimirusrs(usrsABinario, tam);

  if (!escribirArchivo(usrsABinario, tam, "users.bin")) {
    printf("\nError de escritura en archivo %s", "usrs.bin");
    return 1; //retorna 0 en error
  }
  printf("\nEscritura de memoria a archivo binario exitosa");

  if (!leerArchivo(binarioAusrs, tam, "users.bin")) {
    printf("\nError de lectura en archivo %s", "usrs.bin");
    return 2; //retorna 0 en error
  }
  printf("\nLectura de archivo binario a memoria exitosa\n");
  imprimirusrs(binarioAusrs, tam);

  return 0;
}

int escribirArchivo(usr users[], int tam, const char *nombreArchivo) {

  FILE * f;
  f = fopen(nombreArchivo, "wb"); //write binary
  if (f == NULL) {
    printf("Error de apertura en archivo %s", nombreArchivo);
    return 0; //retorna 0 en error
  }
  int i;
  for (i = 0; i < tam; i++) {
    fwrite(&users[i], sizeof(usr), 1, f);
  }
  fflush(f);
  fclose(f);
  return 1; //retorna 1 exitoso
}

int leerArchivo(usr users[], int tam, const char *nombreArchivo) {
  FILE * f;
  f = fopen(nombreArchivo, "rb");
  if (f == NULL) {
    printf("Error de apertura en archivo %s", nombreArchivo);
    return 0; //retorna 0 en error
  }
  int i;
  for (i = 0; i < tam; i++) {
    fread(&users[i], sizeof(usr), 1, f);
  }
  fclose(f);
  return 1; //retorna 1 exitoso
}

void imprimirusrs(usr user[], int tam) {

  int i;
  for (i = 0; i < tam; i++) {
    imprimirusr(&user[i]);
    printf("\n");
  }

}

void imprimirusr(usr *user) {
  printf("Name: %s\n",user->name);
  printf("Password: %s\n",user->password);
  printf("Ya votó? %d", user->votado);
}
