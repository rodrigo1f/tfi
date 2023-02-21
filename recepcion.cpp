#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para almacenar la información del socio
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

// Estructura para almacenar la información del turno de un socio en una actividad
typedef struct {
    int num_socio;
    char actividad[20];
    char entrenador[50];
    char horario[20];
} Turno;

// Estructura para almacenar la información del usuario para iniciar sesión
typedef struct {
    char usuario[11];
    char clave[33];
    char nombre[50];
} Usuario;

// Prototipos de funciones
void iniciar_sesion();
void registrar_socio();
void registrar_actividad();
void listar_participantes();
void listar_fecha_pago();
void escribir_rutina();
void limpiar_buffer();
int ultimo_socio = 0;

int main() {
    int opcion;
    do {
        // Mostrar el menú y leer la opción seleccionada
        printf("\n--- Menú de opciones ---\n");
        printf("1. Iniciar Sesión\n");
        printf("2. Registrar Socios\n");
        printf("3. Registrar Actividades de Socios\n");
        printf("4. Listado de participantes de una actividad por horario y entrenador\n");
        printf("5. Listado de fecha de pago\n");
        printf("6. Registrar Rutina para un socio\n");
        printf("7. Cerrar la aplicación\n");
        printf("Ingrese una opción: ");
        scanf("%d",&opcion);

        switch (opcion) {
            case 1:
                iniciar_sesion();
                escribir_rutina();
                system("pause");
                system("cls");
                break;
            case 2:
                registrar_socio();
                system("pause");
                system("cls");
                break;
            case 3:
                registrar_actividad();
                system("pause");
                system("cls");
                break;
            case 4:
                listar_participantes();
                system("pause");
                system("cls");
                break;
            case 5:
                listar_fecha_pago();
                system("pause");
                system("cls");
                break;
            case 6:
               iniciar_sesion();
                escribir_rutina();
                system("pause");
                system("cls");
                break;
            case 7:
                printf("Cerrando la aplicación...\n");
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 7);

    return 0;
}
void iniciar_sesion() {
    char usuario[11];
    char clave[33];
    limpiar_buffer();
    printf("Ingrese el usuario: ");
    fgets(usuario, 11, stdin);
    usuario[strcspn(usuario, "\n")] = '\0';
    
    
    printf("Ingrese la clave: ");
    fgets(clave, 33, stdin);
    clave[strcspn(clave, "\n")] = '\0';
    

    FILE *archivo_entrenador = fopen("entrenador.dat", "rb");
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
void registrar_socio() {
    FILE *archivo;
    Socio nuevo_socio;
limpiar_buffer();
    // Abrir el archivo en modo lectura binaria
    archivo = fopen("socios.dat", "rb");

    // Comprobar si el archivo se abrió correctamente
    if (archivo == NULL) {
        // Si el archivo no existe, establecer el número de socio en 1
        strcpy(nuevo_socio.num_socio, "001");
    } else {
        // Si el archivo existe, buscar el último número de socio y asignarle uno más
        Socio socio_leido;
        fseek(archivo, -sizeof(Socio), SEEK_END);
        fread(&socio_leido, sizeof(Socio), 1, archivo);
        int ultimo_socio = atoi(socio_leido.num_socio);
        sprintf(nuevo_socio.num_socio, "%03d", ultimo_socio + 1);
        fclose(archivo);
    }
limpiar_buffer();
    // Pedir al usuario que ingrese los datos del socio
    printf("Ingrese el nombre del socio:\n");
    scanf("%s", nuevo_socio.nombre);

    printf("Ingrese el apellido del socio:\n");
    scanf("%s", nuevo_socio.apellido);

    printf("Ingrese el DNI del socio:\n");
    scanf("%s", nuevo_socio.dni);

    printf("Ingrese la edad del socio:\n");
    scanf("%d", &nuevo_socio.edad);

    printf("Ingrese el peso del socio:\n");
    scanf("%f", &nuevo_socio.peso);

    printf("Ingrese las indicaciones médicas del socio:\n");
    scanf("%s", nuevo_socio.indicaciones_medicas);

    printf("Ingrese la altura del socio:\n");
    scanf("%f", &nuevo_socio.altura);

    printf("Ingrese la dirección del socio:\n");
    scanf("%s", nuevo_socio.direccion);
limpiar_buffer();
    printf("Ingrese el teléfono del socio:\n");
    scanf("%s", nuevo_socio.telefono);

    printf("Ingrese la fecha de ingreso del socio (dd/mm/aaaa):\n");
    scanf("%s", nuevo_socio.fecha_ingreso);

    // Abrir el archivo en modo de escritura binaria
    archivo = fopen("socios.dat", "ab");

    // Comprobar si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Escribir el socio en el archivo
    fwrite(&nuevo_socio, sizeof(Socio), 1, archivo);

    // Cerrar el archivo
    fclose(archivo);

    printf("El socio se ha registrado correctamente en el archivo 'socios.bin'.\n");
    printf("Su número de socio es: %s\n", nuevo_socio.num_socio);

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
// Función para listar el listado de fecha de pago
void listar_fecha_pago() {
    char fecha[11];
    limpiar_buffer();
    printf("Ingrese la fecha (DD/MM/AAAA): ");
    fgets(fecha, 11, stdin);
    fecha[strcspn(fecha, "\n")] = '\0';

    FILE *archivo_socio = fopen("socios.dat", "rb");
    if (archivo_socio == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Socio socio_leido;
    while (fread(&socio_leido, sizeof(Socio), 1, archivo_socio)) {
        if (strcmp(socio_leido.fecha_ingreso, fecha) == 0) {
            printf("Número de socio: %d\n", socio_leido.num_socio);
            printf("Nombre y Apellido: %s %s\n", socio_leido.nombre, socio_leido.apellido);
            printf("DNI: %s\n", socio_leido.dni);
            printf("Edad: %d\n", socio_leido.edad);
            printf("Peso: %.2f kg\n", socio_leido.peso);
            limpiar_buffer();
            printf("Altura: %.2f m\n", socio_leido.altura);
            printf("Indicaciones médicas: %s\n", socio_leido.indicaciones_medicas);
            printf("Dirección: %s\n", socio_leido.direccion);
            printf("Teléfono: %s\n", socio_leido.telefono);
            printf("Fecha de ingreso: %s\n", socio_leido.fecha_ingreso);
            printf("Fecha de pago: %s\n", socio_leido.fecha_ingreso);
            printf("\n");
        }
    }

    fclose(archivo_socio);
}

// Función para escribir la rutina de un socio
void escribir_rutina() {
    int num_socio;
    limpiar_buffer();
    printf("Ingrese el número de socio: ");
    scanf("%d", &num_socio);
    limpiar_buffer();

    char nombre_archivo[25];
    sprintf(nombre_archivo, "rutina_%d.txt", num_socio);
    FILE *archivo_rutina = fopen(nombre_archivo, "w");
    if (archivo_rutina == NULL) {
        printf("No se pudo crear el archivo.\n");
        return;
    }

    char ejercicio[100];
    printf("Ingrese el ejercicio (o 'FIN' para terminar): ");
    fgets(ejercicio, 100, stdin);
    ejercicio[strcspn(ejercicio, "\n")] = '\0';
    while (strcmp(ejercicio, "FIN") != 0) {
        char repeticiones[11];
        printf("Ingrese las repeticiones: ");
        fgets(repeticiones, 11, stdin);
        repeticiones[strcspn(repeticiones, "\n")] = '\0';
        fprintf(archivo_rutina, "%s\t%s\n", ejercicio, repeticiones);

        printf("Ingrese el ejercicio (o 'FIN' para terminar): ");
        fgets(ejercicio, 100, stdin);
        ejercicio[strcspn(ejercicio, "\n")] = '\0';
    }

    fclose(archivo_rutina);
    printf("Rutina guardada exitosamente.\n");
}

// Función para limpiar el buffer de entrada
void limpiar_buffer() {
    while (getchar() != '\n');
}
void listar_participantes() {
	limpiar_buffer();
    FILE *archivo_socios = fopen("socios.dat", "rb");
    if (archivo_socios == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    Socio socio_leido;
    printf("Num Socio  Nombre                          Apellido                       DNI        Edad  Altura  Peso   Indicaciones Medicas\n");
    while (fread(&socio_leido, sizeof(Socio), 1, archivo_socios)) {
        printf("%-10d%-32s%-32s%-11s%-6d%-8.2f%-7.2f%-100s\n", socio_leido.num_socio, socio_leido.nombre, socio_leido.apellido, socio_leido.dni, socio_leido.edad, socio_leido.altura, socio_leido.peso, socio_leido.indicaciones_medicas);
    }
    fclose(archivo_socios);
}

