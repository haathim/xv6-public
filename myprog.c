#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
    // printf(1, "Our first user program in xv6, by Haathim %d\n", getyear());
    // printf(1, "My address space size is: %d\n", getmysize());

    // printf (1, "start of kernel = %p \n", getkernelstartaddr ());
    // printf (1, "end of kernel = %p \n", getkernelendaddr());
    // printf (1, "addr of kernel variable = %p \n", getkernelvariaddr ());
    // printf (1, "addr of fork sys call = %p \n", getsystemcalladdr());

    // printf (1, "I ’m running with ordinary priority \n");
    // printf (1, " setting priority to %d\n", setpriority (1));
    // sleep (2);
    // printf (1, "I ’m running with priority 1 \n");
    // printf (1, " setting priority to %d\n", setpriority (2));
    // sleep (2);
    // // below line should never work
    // printf (1, "I ’m running with priority 2 \n");

    printf (1, "Size of a given inode: %d \n", getinodesize("home/ucsc"));

    exit();
}