#include"heading.h"
#include"popStruc.c"
#include"parameters.c"
main(){

  struct Human H[N];
  struct Mosquito M[NM];
  int i;
  srand(time(NULL));
  set_up_humans(H);
  set_up_mosquitos(M);
  // for(i=0;i<N;i++) printf("%d\n",H[i]->health);
}
