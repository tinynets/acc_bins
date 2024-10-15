#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h> // Include unistd.h for chdir

int main(int argc, char *argv[]) {

    char *project_name;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (argc < 2) {
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d-%H-%M-%S", &tm);
        project_name = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(project_name, buffer);
    } else {
        project_name = argv[1];
    }

    printf("Creating a new Vite project named %s\n", project_name);

    char project_path[256];
    snprintf(project_path, sizeof(project_path), "%s/projects/", getenv("HOME"));

    if (chdir(project_path) != 0) {
        perror("chdir() to ~/projects failed");
        return 1;
    }

    // Construct the command to create a new Vite project
    char create_command[256];
    snprintf(create_command, sizeof(create_command), "npm create vite@latest %s", project_name); 
    strcat(create_command, " -- --template vanilla");   
    system(create_command);
    
    if (chdir(project_name) != 0) {
        perror("chdir() to project failed");
        return 1;
    }

    system("code .");
    system("npm install");

    return 0;
}