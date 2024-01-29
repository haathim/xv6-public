#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"


// extern struct {
//   struct spinlock lock;
//   struct proc proc[NPROC];
// } ptable;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// My new syscall
int
sys_getyear(void)
{
  return 1975;
}

int
sys_getmysize(void)
{
  return myproc()->sz;
}

int
sys_getkernelendaddr(void)
{
  return (int)(KERNBASE + PHYSTOP);
}

int
sys_getkernelstartaddr(void)
{
  return (int)(KERNBASE);
}

int
sys_getkernelvariaddr(void)
{
  int var = 7;
  int* add = &var;
  return (int)add;
  // return (int)&var;
}

int
sys_getsystemcalladdr(void)
{
  return (int)sys_fork;
}

int
sys_setpriority()
{
  int priority;
  argint(0, &priority);
  myproc()->priority = priority;

  return priority;
}

int
sys_mycall(void)
{
    // struct proc* procptr = getPTable();

    struct proc* proc = getPTable();

    static char *states[] = {
      [UNUSED]    "UNUSED",
      [EMBRYO]    "EMBRYO",
      [SLEEPING]  "SLEEPING ",
      [RUNNABLE]  "RUNNABLE",
      [RUNNING]   "RUNNING",
      [ZOMBIE]    "ZOMBIE"
    };

    int i;
    struct proc *p;
    char *state;

    int size;
    char *buf;
    char *s;

    if (argint(0, &size) <0){
        return -1;
    }

    if (argptr(1, &buf,size) <0){
        return -1;
    }

    s = buf;

    for(p = proc; p < &proc[NPROC] && (buf + size > s); p++){
      if(p->state == UNUSED)
        continue;
      if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
        state = states[p->state];
      else
        state = "???";
      
      *(int *)s = p->pid;
      s+=4;

      i = 0;

      while ((s[i] = state[i]) && i < 15){
        i++;
      }

      s+=16;

      i=0;
      while ((s[i] = p->name[i]) && i < 15){
        i++;
      }

      s+=16;

    }

    return 1;
}
