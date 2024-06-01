#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sysexits.h>
#include<stdbool.h>


void list(char* filepath) {
    FILE* todo = fopen(filepath, "r");
    char task_line[100];
    int counter = 1;
    while(fgets(task_line, 100, todo) != NULL) {
        printf("%d : %s", counter, task_line);
        counter++;
    }
    fclose(todo);
}



bool del(int line_num, char* filepath) {
    FILE* read_todo = fopen(filepath, "r");
    FILE* write_todo = fopen("temp_todo.txt", "w+");
    if (read_todo == NULL | write_todo == NULL ) {
        exit(EX_NOINPUT);      
    }
    int counter = 1;
    char buffer[100];
    bool flag = false;
    while(fgets(buffer, 100, read_todo) != NULL) {
        if (counter != line_num) {
            fprintf(write_todo,"%s", buffer);
        }
        else 
            flag = true;
        counter++;
    }
    fclose(read_todo);
    fclose(write_todo);
    remove(filepath);
    rename("temp_todo.txt", filepath);
    return flag;
}

int main(int argc, char *argv[]) {
    char *filepath = "todo.txt";


    if (argc == 1) {
        printf("NO arguments specified\nFor help do \"todo help\"\n");
    }
    else if (argc == 2) {
        if (strcmp(argv[1], "help") == 0) {
            printf("1. todo add Creating a new website -- Creating a new website will be added to todo.txt\n2. todo list -- List of all tasks will be displayed along with the task number\n3. todo del 3 -- Task specified by the number 3 will be deleted from the todo list\n4. todo done 3 -- Task specified by the number 3 will be marked as done and will be moved to done.txt\n");
        }
        else if (strcmp(argv[1], "list") == 0){
            list(filepath);
        }
        else {
            printf("Error in argument name\nFor help do \"todo help\"\n");
        }

    }    
    else if (argc >= 3) {
        if (argc == 3 && strcmp(argv[1], "del") == 0) {
            if (atoi(argv[2]) != 0) {
               if(!del(atoi(argv[2]), filepath)) {
                    printf("%d --- ", atoi(argv[2]));
                    printf("No task found to delete\n");
               }
            }
        }
        else if (argc > 3 && strcmp(argv[1], "del") == 0) {
            printf("Too many arguments with del\n");
        }
        else if (strcmp(argv[1], "add") == 0) {
            FILE* todo = NULL;
            if ((todo = fopen(filepath, "a+")) == NULL)
                exit(EX_NOINPUT);   
            for (int i = 2; i < argc; i++) {
                fprintf(todo, "%s ", argv[i]); 
            }            
            fprintf(todo, "\n");
            fclose(todo);
        }

    }
    else {
        printf("INVALID ARGUMENTS \n");
    }    
}
