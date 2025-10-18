#include "types.h"
#include "user.h"
#include "pstat.h"
#include "syscall.h"

#define N 10000

void
display(){
  struct pstat data;
  getpinfo(&data);
  
  // Print the ASCII Form Feed character to clear the screen
  printf(1, "\f"); 
  printf(1, "inuse\t tickets pid\t ticks \t\n");
  
  for (int i = 0; i < NPROC; i++){
    if(data.inuse[i] != 0) 
      printf(1, "%d\t %d\t %d\t %d \n", data.inuse[i], data.tickets[i], data.pid[i], data.ticks[i]);
  } 
  printf(1, "\n"); 
}

void 
dosomething(){ 
  int i, a[N], b[N], c[N];
  for (i = 0; i < N; i++) {
      a[i] = i;
      b[i] = N - i;
  }
  while(1){
    for (i = 0; i < N; i++) 
      c[i] = c[i] + a[i] * b[i]; 
  } 
}

int
main(int argc, char *argv[]) {
  int n = 100; 
  if (argc > 1){
    int iter = atoi(argv[1]);
    if (iter > 0) n = iter; 
  }
  int pids[3];
  // create three child process
  for (int i = 0; i < 3; i++){ 
    pids[i] = fork(); 
    if ( pids[i] == 0){
      settickets(10 * (i+1));
      dosomething();
    }
  }  

  for (int i = 0; i < n; i++){
    display();
    sleep(100);
  }
  for (int i = 0; i < 3; i++) {
    kill(pids[i]);
  }
  exit();
}
