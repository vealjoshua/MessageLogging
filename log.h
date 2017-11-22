#include <time.h>

typedef struct data_struct {
    time_t time;
    char *string;
} data_t;

int addmsg(data_t *data);
int savelog(char *argv, int x);
void clearlog(void);
char *getlog(char *argv, int x, char* filename);
