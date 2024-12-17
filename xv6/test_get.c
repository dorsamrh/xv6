#include "types.h"  
#include "stat.h"  
#include "user.h"  
#include "syscall.h"  

void cpu_intensive() {  
    volatile long long sum = 0;  
    for (long long i = 0; i < 10000000; i++) {  
        sum += i;   
    }  
    printf(1, "Computation finished with sum: %lld\n", sum);  
}  

int main(int argc, char *argv[]) {  


    printf(1,"cpu limit : 100%% \n");
    set_limit(100,1024);
    int current=uptime();
    cpu_intensive();
    int finish=uptime();
    int length=finish-current;
    printf(1,"time taken: %d .\n",length);
    printf(1,"cpu limit : 80%% \n");
    set_limit(100,1024);
    current=uptime();
    cpu_intensive();
    finish=uptime();
    length=finish-current;
    printf(1,"time taken: %d .\n",length);
    printf(1,"cpu limit : 50%% \n");
    set_limit(100,1024);
    current=uptime();
    cpu_intensive();
    finish=uptime();
    length=finish-current;
    printf(1,"time taken: %d .\n",length);
    printf(1,"cpu limit : 30%% \n");
    set_limit(100,1024);
    current=uptime();
    cpu_intensive();
    finish=uptime();
    length=finish-current;
    printf(1,"time taken: %d .\n",length);
    printf(1,"cpu limit : 10%% \n");
    set_limit(100,1024);
    current=uptime();
    cpu_intensive();
    finish=uptime();
    length=finish-current;
    printf(1,"time taken: %d .\n",length);


    exit();  
}