#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "log.h"

int main(int argc, char **argv)
{
    char *cvalue = NULL;
    cvalue = (char *)malloc(256 * sizeof(char));
    char *filename = "logfile.txt";

    int c, x = 37;

    while ((c = getopt(argc, argv, "hl:n:")) != -1)
        switch (c)
        {
            case 'h':
                printf("Command Line Argument Functions\n"
                               "-h: Display a useful message describing the function of all the command line arguments.\n"
                               "-l filename: Set the name of the log file. The default value for the name of the logfile is logfile.txt.\n"
                               "-n x: Set a variable in this program to the integer x.\n\n");
                break;
            case 'l':
                cvalue = optarg;
                filename = cvalue;
                break;
            case 'n':
                x = optarg;
                break;
            case '?':
                if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                break;
        }

    int i = 0;
    for (i; i < 2; ++i) {
        char *message = NULL;
        message = (char *)malloc(256 * sizeof(char));

        printf("Enter your message:\n");
        scanf("%s", message);

        data_t *userData = malloc(sizeof(data_t));
        if (userData == NULL) {
            perror("userData malloc failed");
            return -1;
        }

        userData->time = time(NULL);

        int size = strlen(message) + 1;
        userData->string = (char *)malloc(sizeof(char) * size);
        if (userData->string == NULL) {
            perror("userData malloc failed");
            return -1;
        }
        strcpy(userData->string, message);
        addmsg(userData);

        // Get log
        char *log;
        log = getlog(argv[0], x);
        if (log == NULL)
            perror("log is empty");
        else
            printf("%s", log);

    // Save log
        savelog(argv[0], x, filename);

    // Clear log
        clearlog();

        // Free memory
        free(message);
        free(userData->string);
        free(userData);
        free(log);
    }
    free(cvalue);

    return(0);
}