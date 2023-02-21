#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERNAME_LENGTH 10
#define MAX_PASSWORD_LENGTH 32
#define MAX_USUARIOS 100

void iniciar_sesion();
void mostrar_socios();
void escribir_rutina();
int es_unica(char *usuario);
int es_valido_usuario(char *usuario);
int es_valida_clave(char *clave);
void crear_usuario();
void limpiar_buffer();

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
        printf("3.- Visualizar listado de Socios y actividad que desarrolla.\n");
        printf("4.- Registrar rutinas de gimnasia.\n");
        printf("5.- Cerrar la aplicacion.\n");
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
                mostrar_socios();
                system("pause");
                system("cls");
                break;
            case 4:
            escribir_rutina();
            system("pause");
            system("cls");
                break;
            case 5:
                printf("Cerrando la aplicacion...\n");
                break;
            default:
                printf("Opcion invalida. Por favor ingrese una opcion valida.\n");
                break;
        }
    } while (opcion != 5);

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
void mostrar_socios() {
    FILE *archivo;
    char linea[100];

    // Abrir el archivo en modo de lectura
    archivo = fopen("socios", "r");

    // Comprobar si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Leer el archivo línea por línea y mostrar los datos de cada socio
    while (fgets(linea, 100, archivo) != NULL) {
        printf("%s", linea);
    }

    // Cerrar el archivo
    fclose(archivo);
}
void escribir_rutina() {
    FILE *archivo;
    char rutina[380];

    // Pedir al usuario que ingrese la rutina de gimnasio
    limpiar_buffer();
    printf("Ingrese la rutina de gimnasio (no más de 380 caracteres):\n");
    fgets(rutina, sizeof(rutina), stdin);

    // Abrir el archivo en modo de escritura
    archivo = fopen("rutinas.txt", "a");
    limpiar_buffer();

    // Comprobar si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Escribir la rutina en el archivo
    fprintf(archivo, "%s\n", rutina);

    // Cerrar el archivo
    fclose(archivo);

    printf("La rutina se ha guardado correctamente en el archivo 'rutinas.txt'.\n");
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
