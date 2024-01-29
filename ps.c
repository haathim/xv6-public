#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_STRUCTS 10

struct mystruct {
    int pid;
    char state[16];
    char name[16];
};

int main(void) {

    struct mystruct struct_array[NUM_STRUCTS];
    struct mystruct *p;

    // printf(1, "Size of mystruct: %d\n", sizeof(struct mystruct));

    int return_val = mycall( NUM_STRUCTS*sizeof(struct mystruct), &struct_array);
    p = &struct_array[0];

    printf(1, "PID | STATE | NAME\n---------------------------------------\n");
    while(p != &struct_array[NUM_STRUCTS] && p->pid != 0){
        printf(1,"%d | %s | %s\n",p->pid, p->state, p->name);
        p++;
    }

    // printf(1, "Program %d \n", return_val);
    exit();
}

