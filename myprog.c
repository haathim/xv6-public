#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
    printf(1, "Our first user program in xv6, by Haathim %d\n", getyear());
    printf(1, "My address space size is: %d\n", getmysize());
    exit();
}