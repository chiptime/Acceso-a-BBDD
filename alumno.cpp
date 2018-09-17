#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct{
    char nombre[30];
    unsigned short int edad;
    unsigned int telefono;
}Persona;

int menu(){
    int menuO;
    printf("Bienvenido,\nporfavor elige una de la opciones...\n\n");
    printf("    0. Ver todos los alumnos\n");
    printf("    1. Ver un alumno\n");
    printf("    2. Insertar todos los alumnos\n");
    printf("    3. Insertar un alumno\n");
    printf("    4. Editar un alumno\n");
    printf("    5. Borrar todos los alumnos\n");
    printf("    6. Borrar un alumno\n");
    printf("    7. Guardar los alumnos en el fichero\n");
    printf("    8. Salir del programa\n");
    scanf("%i", &menuO);
    return menuO;
}
Persona takePerson(){
    Persona persona;
    printf("Introduce los datos:\n\nNombre: \n");
    scanf("%s", persona.nombre);
    printf("Edad:\n");
    scanf("%hu", &persona.edad);
    printf("Telefono:\n");
    scanf("%iu", &persona.telefono);
    //printf("Los datos son: %s, %hu, %hu", persona.nombre,persona.edad,persona.telefono);
    return persona;
}
void take(Persona lista[], int id){
    lista[id] = takePerson();
    printf("Los datos son: %s, %hu, %u", lista[id].nombre,lista[id].edad,lista[id].telefono);
    printf("\n\nGuardando... en tiempo de ejecucion\n\n");
}
void save(Persona *persona, FILE *pipe, const char *path){
    if(!(pipe = fopen(path,"wb")))
       fprintf(stderr,"No he encontrado el archivo.\n");
    fwrite(persona,sizeof(Persona),1,pipe);
    fclose(pipe);
}
int selectId(int id){
    printf("Last ID = %i\n(0 is default)\n", id);
    printf("¿Que alumno deseas elegir?, dime su id\n");
    scanf("%i", &id);
    return id;
}
int main(int argc, char const *argv[]){
    bool running = true;
    int option;
    enum {
        viewAll,
        viewOne,
        insertAll,
        insertOne,
        edit,
        delAll,
        delOne,
        saveF,
        exit
    };
    const char *filename = "a.txt";
    FILE *file = NULL;
    Persona lista[N];
    Persona alumnoLec;
    int id = 0;    

    do{
        option = menu();
        switch(option){

            case viewAll:
                printf("    0. Has elegido VER todos los alumnos\n\n");
                if(!(file = fopen(filename,"r")))
                    fprintf(stderr,"No he encontrado el archivo.\n");    
                while(fread(&alumnoLec, sizeof(Persona), N, file)){                
                printf("%s,%hu,%iu\n", alumnoLec.nombre,alumnoLec.edad,alumnoLec.telefono);
                }
                fclose(file);
            break;

            case viewOne:
                printf("    1. Has elegido VER un alumno\n\n");
                if(!(file = fopen(filename,"r")))
                    fprintf(stderr,"No he encontrado el archivo.\n");    
                while(fread(&alumnoLec, sizeof(Persona), 1, file)){                
                printf("%s,%hu,%iu\n", alumnoLec.nombre,alumnoLec.edad,alumnoLec.telefono);
                }
                fclose(file);
            break;

            case insertAll:
                printf("    2. Has elegido insertar todos los alumnos\n\n");
                for(id = 0; id<N; id++){
                take(lista,id);
                }
            break;

            case insertOne:
                //printf("    1. Has elegido editar un alumno\n");
                printf("    3. Has elegido insertar un alumno\n\n");
                selectId(id);
                take(lista,id);
            break;
            case edit:
                printf("    4. Has elegido editar un alumno\n\n");                
            break;   
            case delAll:
                printf("    5. Has elegido borrar un alumno\n\n");                
                return EXIT_SUCCESS;
            break;  
            case delOne:
                printf("    6. Has elegido editar todos los alumnos\n\n");                
                return EXIT_SUCCESS;
            break; 
            case saveF:
                //printf("    2. Has elegido borrar un alumno\n");
                printf("    7.Has elegido guardar en el fichero\n\n");
                save(lista, file, filename);
                printf("\n\nGuardando 2...\n\n");
            break;       
            case exit:
                printf("    Has elegido salir del programa\n\n");                
                return EXIT_SUCCESS;
            break;
            default:
                printf("\n    Opción invalida, has sido expulsado\n\n");                
                return EXIT_FAILURE;
            break;
        }
    }while(running);    
    return EXIT_SUCCESS;
}
