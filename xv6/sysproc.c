#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"


int sys_set_limit( void) {  
  int cpu_quota;
  int memory_quota;
 
    if (argint(0, &cpu_quota) < 0) {  
        return -1; 
    } 


    if (cpu_quota < 0 || cpu_quota > 100) {  
        return -1; 
    }  
    if (argint(1, &memory_quota) < 0) {  
        return -1; 
    } 

    if(memory_quota<0){
      return -2;
    }
    struct proc *pr =myproc();
    pr->cpu_limit = cpu_quota;  
    pr->memory_limit=memory_quota;
    return 0; 
}
int sys_increase_memory_usage(void)
{
  int amount;
  if (argint(0, &amount) < 0) {  
      return -1; 
  } 
  
  struct proc *pr =myproc();
  int temp=myproc()->current_memory_usage+amount;
  if(temp>pr->memory_limit || temp<0)
  {
    cprintf("this process is out of memory limit.\n");
    return -1;
  }
  pr->current_memory_usage=temp+amount;
  return 0;
}

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
