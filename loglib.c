#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "log.h"

typedef struct list_struct {
    data_t item;
    struct list_struct *next;
} log_t;

static log_t endlist;
static log_t *headptr = NULL;
static log_t *tailptr = NULL;

int addmsg(data_t *data) {   /* allocate node for data and add to end of log */
    log_t *newnode;
    int nodesize;

    nodesize = sizeof(log_t) + strlen(data->string) +1;  // making the size of the node my taking the size of log_t and the size of data +1 for \0
    if ((newnode = (log_t *)(malloc(nodesize))) == NULL) // if newnode failed to be allocated in memory
    {
        perror ("Failed to make newnode");
        return -1;
    }

    newnode -> item.time = data->time; // getting the current time of the statement
    newnode -> item.string = (char *)newnode + sizeof(log_t);
    strcpy(newnode -> item.string, data->string); // copying
    newnode -> next = NULL; // setting the next to be null so when new data needs to be aded to the list
    if(headptr == NULL)
    {
        headptr = newnode;
    }
    else tailptr->next = newnode; // moving to the tailptr to add more data
    tailptr = newnode;

    return 0;
}

void clearlog(void) {
    log_t *node = headptr; // starting at the dead
    while(node != NULL) // clearing up the memory untill tail hits NULL
    {
        node = headptr->next; // setting up next when the head is cleared
        free(headptr);
        headptr = node; //moving to the next
    }
}

char* getlog(char *argv, int x) {
    log_t *node;  //making for head
    node = headptr; // starting at head

    char *logCopy = (char *)malloc(sizeof(char));
    int newSize;

    while(node)
    {
        char *temp = (char *)malloc(256 * sizeof(char));
        sprintf(temp, "%s: %d: nvalue = %d - %s\n", argv, node->item.time, x, node->item.string);
        temp = (char *)realloc(temp, strlen(temp) + 1);
        newSize = strlen(logCopy) + strlen(temp) + 1;
        logCopy = (char*)realloc(logCopy, newSize);
        strcat(logCopy, temp);
        free(temp);
        node = node -> next;
    }

    return strdup(logCopy);
}

int savelog(char *argv, int x, char *filename) {
    FILE *fp;
    fp = fopen(filename, "w");

    if (fp == NULL) {
        errno = EBADFD;
        return -1;
    }

    int  i = 0;
    fprintf(fp, "%s\n", getlog(argv, x));

    fclose(fp);

    return 0;
}
