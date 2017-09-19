#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define NumberOfFiles 200
#define NL 728 //numberoflines

main(){

  char name[30];
  FILE *ar;
  int i,time,line;
  float susc[NL],lat[NL],asym[NL],sym[NL],symiso[NL],rec[NL],a1,a2,a3,a4,a5,a6;
  
  for(line=0;line<NL;line++) susc[line]=lat[line]=asym[line]=sym[line]=symiso[line]=rec[line]=0;
  
  for(i=0;i<NumberOfFiles;i++){
    sprintf(name,"files/teer%d.dat",i);
    ar=fopen(name,"r");

    for(line=0;line<NL;line++){

      fscanf(ar,"%d %f %f %f %f %f %f",&time,&a1,&a2,&a3,&a4,&a5,&a6);

      susc[line]+=a1;
      lat[line]+=a2;
      asym[line]+=a3;
      sym[line]+=a4;
      symiso[line]+=a5;
      rec[line]+=a6;
      

    }

    fclose(ar);
  }

  ar=fopen("result.dat","w");
  for(line=0;line<NL;line++){

    susc[line]/=NumberOfFiles;
    lat[line]/=NumberOfFiles;
    asym[line]/=NumberOfFiles;
    sym[line]/=NumberOfFiles;
    symiso[line]/=NumberOfFiles;
    rec[line]/=NumberOfFiles;

    fprintf(ar,"%f %f %f %f %f %f %f\n",line/7.,susc[line],lat[line],asym[line],sym[line],symiso[line],rec[line]);
    
    
  }

  
}
