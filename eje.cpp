#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERNAME_LENGTH 10
#define MAX_PASSWORD_LENGTH 32
#define MAX_USUARIOS 100

void iniciar_sesion();
int es_unica(char *usuario);
int es_valido_usuario(char *usuario);
int es_valida_clave(char *clave);
void crear_usuario();
void limpiar_buffer();
void registrar_actividad();
void calcularEntrenadorConMayorCargaHoraria();
void calcularPagoEntrenadores();

typedef struct {
    char num_socio[5];
    char nombre[50];
    char apellido[50];
    char dni[9];
    int edad;
    float peso;
    char indicaciones_medicas[100];
    float altura;
    char direccion[100];
    char telefono[20];
    char fecha_ingreso[11];
} Socio;

struct HorarioEntrenador {
  char nombre[50];
  int horaInicio;
  int horaFin;
  int cantidadAlumnos;
};

struct DatosEntrenador {
  char nombre[50];
  int pagoPorAlumno;
  int cantidadPersonasACargo;
};

typedef struct {
    int num_socio;
    char actividad[20];
    char entrenador[50];
    char horario[20];
} Turno;

typedef struct {
    char usuario[11];
    char clave[33];
    char nombre[51];
    int legajo;
} Usuario;
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} UserAccount;

Usuario usuarios[MAX_USUARIOS];
int num_usuarios = 0;

int main() {
    int opcion;
    char username[11];
    char password[33];
    
    FILE *archivo_entrenador = fopen("entrenador.bin", "rb");
    if (archivo_entrenador != NULL) {
        Usuario usuario_leido;
        while (fread(&usuario_leido, sizeof(Usuario), 1, archivo_entrenador) == 1) {
            usuarios[num_usuarios] = usuario_leido;
            num_usuarios++;
        }
        fclose(archivo_entrenador);
    }
    do {
        printf("Modulo Gym\n");
        printf("1.- Iniciar Sesion.\n");
        printf("2.- registrar entrenador. \n");
        printf("3.- registrar actividad \n");
        printf("4.- calcular pago a los entrenadores\n");
        printf("5.- Entrenador con mayor carga horaria\n");
        printf("6.- Cerrar la aplicacion.\n");
        printf("Ingrese una opcion: ");

        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
            iniciar_sesion();
            system("pause");
            system("cls");
    break;
            case 2:
                crear_usuario();
                system("pause");
                system("cls");
                break;
            case 3:
                registrar_actividad();
                 system("pause");
                 system("cls");
                 break;
            case 4: 
                 calcularPagoEntrenadores();
                 system("pause");
                 system("cls");
                 break;
            case 5: 
                 calcularEntrenadorConMayorCargaHoraria();
                 system("pause");
                 system("cls");
                 break;
            case 6: 
                 printf("Cerrando la aplicacion...\n");
                break;
            default:
                printf("Opcion invalida. Por favor ingrese una opcion valida.\n");
                break;
        }
    } while (opcion != 6);

    return 0;
}

void iniciar_sesion() {
    char usuario[11];
    char clave[33];
    printf("Ingrese el usuario: ");
    fgets(usuario, 11, stdin); 
    usuario[strcspn(usuario, "\n")] = '\0';
    limpiar_buffer();
    printf("Ingrese la clave: ");
    fgets(clave, 33, stdin);
    clave[strcspn(clave, "\n")] = '\0';

    FILE *archivo_entrenador = fopen("entrenador.bin", "rb");
    if (archivo_entrenador == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Usuario usuario_leido;
    while (fread(&usuario_leido, sizeof(Usuario), 1, archivo_entrenador)) {
        if (strcmp(usuario_leido.usuario, usuario) == 0 && strcmp(usuario_leido.clave, clave) == 0) {
            printf("Bienvenido, %s.\n", usuario_leido.nombre);
            fclose(archivo_entrenador);
            return;
        }
    }

    printf("El usuario o la clave son incorrectos.\n");
    fclose(archivo_entrenador);
}
int es_unica(char *usuario) {
    int i;
    for (i = 0; i < num_usuarios; i++) {
        if (strcmp(usuario, usuarios[i].usuario) == 0) {
            return 0;
        }
    }
    return 1;
}

int es_valido_usuario(char *usuario) {
    int i;
    int num_digitos = 0;
    int num_mayusculas = 0;
    if (strlen(usuario) < 6 || strlen(usuario) > 10) {
        return 0;
    }
    if (!islower(usuario[0])) {
        return 0;
    }
    for (i = 1; i < strlen(usuario); i++) {
        if (!isalnum(usuario[i]) && usuario[i] != '_' && usuario[i] != '-') {
            return 0;
        }
        if (isdigit(usuario[i])) {
            num_digitos++;
            if (num_digitos > 3) {
                return 0;
            }
        }
        if (isupper(usuario[i])) {
            num_mayusculas++;
        }
    }
    if (num_mayusculas != 2) {
        return 0;
    }
    if (!es_unica(usuario)) {
        return 0;
    }
    return 1;
}

int es_valida_clave(char *clave) {
    int i;
    int num_mayusculas = 0;
    int num_minusculas = 0;
    int num_digitos = 0;
    if (strlen(clave) < 6 || strlen(clave) > 32) {
        return 0;
    }
    for (i = 0; i < strlen(clave); i++) {
        if (!isalnum(clave[i])) {
            return 0;
        }
        if (isdigit(clave[i])) {
            num_digitos++;
        }
        if (islower(clave[i])) {
            num_minusculas++;
        }
        if (isupper(clave[i])) {
            num_mayusculas++;
        }
    }
    if (num_mayusculas < 1 || num_minusculas < 1 || num_digitos < 1) {
        return 0;
    }
    return 1;
}

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void crear_usuario() {
    char usuario[11];
    char clave[33];
    char nombre[51];
    int legajo;
    limpiar_buffer();
    printf("Ingrese el usuario: ");
    fgets(usuario, 11, stdin);
    usuario[strcspn(usuario, "\n")] = '\0';
    if (!es_valido_usuario(usuario)) {
        printf("El usuario no cumple los requisitos.\n");
        return;
    }
    printf("Ingrese la clave: ");
    fgets(clave, 33, stdin);
    clave[strcspn(clave, "\n")] = '\0';
    if (!es_valida_clave(clave)) {
        printf("La clave no cumple los requisitos.\n");
        return;
    }
    printf("Ingrese el nombre: ");
fgets(nombre, 51, stdin);
nombre[strcspn(nombre, "\n")] = '\0';

printf("Ingrese el usuario (de 6 a 10 caracteres): ");
fgets(usuario, 12, stdin);
usuario[strcspn(usuario, "\n")] = '\0';

printf("Ingrese la clave (de 6 a 32 caracteres): ");
fgets(clave, 34, stdin);
clave[strcspn(clave, "\n")] = '\0';

if (es_valido_usuario(usuario) && es_valida_clave(clave)) {
    printf("Ingrese el nombre y el número de legajo:\n");
    printf("Nombre: ");
    fgets(nombre, 51, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';
    printf("Legajo: ");
    scanf("%d", &legajo);
    getchar();

    Usuario nuevo_usuario;
    strcpy(nuevo_usuario.nombre, nombre);
    strcpy(nuevo_usuario.usuario, usuario);
    strcpy(nuevo_usuario.clave, clave);
    nuevo_usuario.legajo = legajo;

    FILE *archivo_entrenador = fopen("entrenador.dat", "ab");
    if (archivo_entrenador == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    fwrite(&nuevo_usuario, sizeof(Usuario), 1, archivo_entrenador);
    fclose(archivo_entrenador);

    printf("El usuario ha sido creado con éxito.\n");
} else {
    printf("El nombre de usuario o la clave no cumplen los requisitos.\n");
}
 printf("Ingrese el legajo: ");
    scanf("%d", &legajo);
    getchar();
    Usuario usuario_nuevo;
    strcpy(usuario_nuevo.usuario, usuario);
    strcpy(usuario_nuevo.clave, clave);
    strcpy(usuario_nuevo.nombre, nombre);
    usuario_nuevo.legajo = legajo;
    usuarios[num_usuarios] = usuario_nuevo;
    num_usuarios++;
    FILE *archivo_entrenador = fopen("entrenador.bin", "ab");
    if (archivo_entrenador == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    fwrite(&usuario_nuevo, sizeof(Usuario), 1, archivo_entrenador);
    fclose(archivo_entrenador);
    printf("El usuario ha sido creado con éxito.\n");
}
// Función para registrar la actividad de un socio
void registrar_actividad() {
    int num_socio;
    limpiar_buffer();
    printf("Ingrese el número de socio: ");
    scanf("%d", &num_socio);
    limpiar_buffer();

    // Abrir el archivo de socios en modo lectura
    FILE *archivo_socios = fopen("Socios.dat", "rb");
    if (archivo_socios == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Socio socio_leido;
    int encontrado = 0;
    while (fread(&socio_leido, sizeof(Socio), 1, archivo_socios)) {
        if (atoi(socio_leido.num_socio) == num_socio) {
 
            encontrado = 1;
            break;
        }
    }
    fclose(archivo_socios);

    if (!encontrado) {
        printf("No se encontró un socio con el número de socio ingresado.\n");
        return;
    }

    // Leer el turno de la actividad
    Turno turno;
    printf("Ingrese la actividad: ");
    fgets(turno.actividad, 20, stdin);
    turno.actividad[strcspn(turno.actividad, "\n")] = '\0';
    printf("Ingrese el nombre del entrenador: ");
    fgets(turno.entrenador, 50, stdin);
    turno.entrenador[strcspn(turno.entrenador, "\n")] = '\0';
    printf("Ingrese el horario (Ej: Lunes de 9:00 a 10:00): ");
    fgets(turno.horario, 20, stdin);
    turno.horario[strcspn(turno.horario, "\n")] = '\0';
    turno.num_socio = num_socio;

    // Abrir el archivo de turnos en modo agregar
    FILE *archivo_turnos = fopen("turno.dat", "ab");
    if (archivo_turnos == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Escribir el turno en el archivo de turnos
    fwrite(&turno, sizeof(Turno), 1, archivo_turnos);

    fclose(archivo_turnos);
    printf("Se registró el turno con éxito.\n");
}
void calcularEntrenadorConMayorCargaHoraria() {
  FILE *archivoTurno = fopen("turno.dat", "rb");
  if (archivoTurno == NULL) {
    printf("Error al abrir el archivo de turnos\n");
    return;
  }

  FILE *archivoEntrenadores = fopen("entrenadores.bin", "rb");
  if (archivoEntrenadores == NULL) {
    printf("Error al abrir el archivo de entrenadores\n");
    return;
  }

  struct HorarioEntrenador horario;
  struct DatosEntrenador datosEntrenador;
  char nombreEntrenadorConMayorCargaHoraria[50];
  int mayorCargaHoraria = 0;

  while (fread(&horario, sizeof(struct HorarioEntrenador), 1, archivoTurno)) {
    while (fread(&datosEntrenador, sizeof(struct DatosEntrenador), 1, archivoEntrenadores)) {
      if (strcmp(horario.nombre, datosEntrenador.nombre) == 0) {
        int cargaHoraria = horario.horaFin - horario.horaInicio;
        if (cargaHoraria > mayorCargaHoraria) {
          mayorCargaHoraria = cargaHoraria;
          strcpy(nombreEntrenadorConMayorCargaHoraria, horario.nombre);
        }
      }
    }
    rewind(archivoEntrenadores);
  }

  fclose(archivoTurno);
  fclose(archivoEntrenadores);

  if (strlen(nombreEntrenadorConMayorCargaHoraria) == 0) {
    printf("No se encontraron horarios de entrenadores en el archivo\n");
  } else {
    printf("El entrenador con mayor carga horaria es %s, con %d horas de trabajo\n", nombreEntrenadorConMayorCargaHoraria, mayorCargaHoraria);

    archivoEntrenadores = fopen("entrenadores.bin", "rb");
    while (fread(&datosEntrenador, sizeof(struct DatosEntrenador), 1, archivoEntrenadores)) {
      if (strcmp(datosEntrenador.nombre, nombreEntrenadorConMayorCargaHoraria) == 0) {
        printf("Datos del entrenador:\n");
        printf("Nombre: %s\n", datosEntrenador.nombre);
        printf("Cantidad de personas a cargo: %d\n", datosEntrenador.cantidadPersonasACargo);
        break;
      }
    }
    fclose(archivoEntrenadores);
  }
}
void calcularPagoEntrenadores() {
  FILE *archivoTurno = fopen("turno.dat", "rb");
  if (archivoTurno == NULL) {
    printf("Error al abrir el archivo de turnos\n");
    return;
  }

  struct HorarioEntrenador horario;
  struct DatosEntrenador datosEntrenador;
  int pagoTotal;
  char nombreAnterior[50] = "";
  
  printf("Ingrese el pago por alumno: ");
  int pagoPorAlumno;
  scanf("%d", &pagoPorAlumno);

  while (fread(&horario, sizeof(struct HorarioEntrenador), 1, archivoTurno)) {
    if (strcmp(nombreAnterior, horario.nombre) != 0) {
      if (strlen(nombreAnterior) != 0) {
        printf("El entrenador %s recibirá un pago total de %d\n", nombreAnterior, pagoTotal);
      }
      strcpy(nombreAnterior, horario.nombre);
      pagoTotal = 0;
      FILE *archivoEntrenador = fopen("entrenadores.bin", "rb");
      if (archivoEntrenador == NULL) {
        printf("Error al abrir el archivo de entrenadores\n");
        return;
      }
      while (fread(&datosEntrenador, sizeof(struct DatosEntrenador), 1, archivoEntrenador)) {
        if (strcmp(datosEntrenador.nombre, horario.nombre) == 0) {
          pagoTotal += datosEntrenador.pagoPorAlumno * horario.cantidadAlumnos * (horario.horaFin - horario.horaInicio);
          break;
        }
      }
      fclose(archivoEntrenador);
    } else {
      pagoTotal += datosEntrenador.pagoPorAlumno * horario.cantidadAlumnos * (horario.horaFin - horario.horaInicio);
    }
  }

  if (strlen(nombreAnterior) != 0) {
    printf("El entrenador %s recibirá un pago total de %d\n", nombreAnterior, pagoTotal);
  }

  fclose(archivoTurno);
}
