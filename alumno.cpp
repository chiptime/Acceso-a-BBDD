#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3

typedef struct{
    char nombre[30];
    unsigned short int edad;
    unsigned int telefono;
}Persona;

int menu(){
    int menuO;
    printf("Bienvenido,\nporfavor elige una de la opciones...\n\n");
    printf("    0. Ver todos los alumnos\n");    
    printf("    1. Insertar todos los alumnos\n");
    printf("    2. Insertar un alumno\n");
    printf("    3. Editar un alumno\n");
    printf("    4. Borrar todos los alumnos\n");
    printf("    5. Borrar un alumno\n");
    printf("    6. Guardar los alumnos en el fichero\n");
    printf("    7. Salir del programa\n");
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
    return persona;
}
void read(Persona persona, FILE *pipe, const char *path){        
    if(!(pipe = fopen(path,"r")))
        fprintf(stderr,"No he encontrado el archivo.\n");    
    while(fread(&persona, sizeof(Persona), 1, pipe)){

        printf("Nombre: %s,\nEdad: %hu,\nTelefono: %iu\n\n", persona.nombre, persona.edad, persona.telefono);        
    }
    printf("\n\n");
    fclose(pipe);    
}
void take(Persona lista[], int id){
    lista[id] = takePerson();
    printf("Los datos son: \nNombre: %s,\nEdad: %hu,\nTelefono: %u\n", lista[id].nombre,lista[id].edad,lista[id].telefono);
    printf("\n\nGuardando... en tiempo de ejecucion\n\n");
}
void save(Persona persona[], FILE *pipe, const char *path){
    if(!(pipe = fopen(path,"wb")))
       fprintf(stderr,"No he encontrado el archivo.\n");
    fwrite(persona,sizeof(Persona),N,pipe);
    printf("Se ha guardado el alumnno:\n");
    printf("%s,%hu,%iu\n", persona->nombre, persona->edad, persona->telefono);    
    fclose(pipe);
}
int selectId(int id){
    printf("Last ID = %i\n(0 is default)\n", id);
    printf("¿Que alumno deseas elegir?, dime su id\n");
    scanf("%i", &id);
    if(id>=N){
        printf("El id = %i no existe\n", id);
    }
    printf("El id seleccionado es: %i\n", id);
    return id;
}
int main(int argc, char const *argv[]){
    bool running = true;
    int option;
    enum {
        viewAll,        
        insertAll,
        insertOne,
        edit,
        delAll,
        delOne,
        saveF,
        list,
        exit
    };
    const char *filename = "a.txt";
    FILE *file = NULL;
    Persona lista[N];
    Persona alumnoLec;
    int id = 0;    
    char nullStr[30] = {"\0"};
    printf("Los alumnos hasta el momento son: \n\n");    
    read(alumnoLec,file,filename);    
    

    if(!(file = fopen(filename,"r")))
       fprintf(stderr,"No he encontrado el archivo.\n");
    fread(lista,sizeof(Persona),N,file);
    fclose(file);


    do{
        option = menu();
        switch(option){

            case viewAll:
                printf("    0. Has elegido VER todos los alumnos\n\n");
                read(alumnoLec,file,filename);
            break;

            case insertAll:
                printf("    1. Has elegido insertar todos los alumnos\n\n");
                for(id = 0; id<N; id++){
                take(lista,id);
                }
            break;

            case insertOne:
                printf("    2. Has elegido insertar un alumno\n\n");
                id = selectId(id);
                take(lista,id);
                //if(&lista[id].nombre != NULL){
                //take(lista,id);
                //}else{
                //    printf("El id de alumno ya esta en uso\n");
                //}
            break;
            case edit:
                printf("    3. Has elegido editar un alumno\n\n"); 
                id = selectId(id);  
                take(lista,id);               
            break;   
            case delAll:
                printf("    4. Has elegido borrar todos los alumnos\n\n"); 
                for(int i =0;i<N;i++){
                    strcpy( lista[i].nombre, nullStr);
                    lista[i].edad     = '\0';
                    lista[i].telefono = '\0';
                }                           
                int sn; 
                printf("¿Estas seguro que quieres borrar todos los alumnos?\n\n1(Si)/0(No)\n\n");               
                scanf("%i", &sn);                
                if(sn == 1){
                    save(lista, file, filename);
                    printf("La lista de alumnos ha sido borrada.\n\n");                    
                }else{
                    printf("Has cancelado el borrado de alumnos.\n\n");                    
                }
            break;  
            case delOne:
                printf("    5. Has elegido borrar un alumno\n\n");  
                selectId(id);
                strcpy( lista[id].nombre, nullStr);
                lista[id].edad     = '\0';
                lista[id].telefono = '\0';
            break; 
            case saveF:                
                printf("    6.Has elegido guardar en el fichero\n\n");                
                save(lista, file, filename);                
                printf("\n\nGuardando 2...\n\n");
            break;       
            case exit:
                printf("    Has elegido salir del programa\n\n");                
                return EXIT_SUCCESS;
            break;
            case list:
                printf("    Estos alumnos estan guardados en el PROGRAMA\n\n");  
                for(int i =0;i<N;i++){
                    printf("ID: %i, %s, %i, %i \n", i, lista[i].nombre,lista[i].edad,lista[i].telefono);
                }
                printf("\n");                
            break;
            default:
                printf("\n    Opción invalida, has sido expulsado\n\n");                
                return EXIT_FAILURE;
            break;
        }
    }while(running);    
    return EXIT_SUCCESS;
}
