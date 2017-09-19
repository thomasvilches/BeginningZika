#include"heading.h"
#include"log_normal.c"
#include"popStruc.c"
#include"parameters.c"
#include"interaction.c"
#include"mosqStruc.c"
#include"ProbDist.c"
#include"functions.c"

main(){

  //struct Human *H;
  //struct Mosquito *M;
  int i,maximumDays,j,controlSeason,timecount,d,rn,susc,latent,symp,asymp,sympiso,rec,numberofseason,sim,bites;
  float dist[2][60],rd,distAge[60],soma;
  FILE *ar,*arq;
  char name[20];
  
  struct Human *H=malloc(N*sizeof(struct Human));//Hvector(0,N-1);
  struct Mosquito *M=malloc(NM*sizeof(struct Mosquito));//Mvector(0,NM-1);
  
  ar=fopen("summer.txt","r");
  arq=fopen("winter.txt","r");
  
  for(i=0;i<60;i++) fscanf(ar,"%f",&dist[0][i]);
  for(i=0;i<30;i++) fscanf(arq,"%f",&dist[1][i]);
  fclose(arq);
  fclose(ar);
  srand(time(NULL));
  
  
  /////starting simulations


  for(sim=0;sim<NumberofSimulations;sim++){
    
    printf("simulacao=%d\n",sim);

    for(i=0;i<60;i++) distAge[i]=0;
    
    for(i=0;i<NM;i++){
      set_up_mosquito(M,i,dist);
      distAge[M[i].ageofdeath-1]+=1.0;//create initial age
      //rd=(float)rand()/RAND_MAX;
      //M[i].age=rd*(M[i].ageofdeath-1)+1;
    }
    ///CREATING THE INITIAL AGE OF THE MOSQUITOS
    distAge[0]/=NM;
    for(i=1;i<60;i++){
      distAge[i]/=NM;
      distAge[i]+=distAge[i-1];
      //printf("%f\n",distAge[i]);
    }
    //getchar();
    for(i=0;i<NM;i++){
      rd=(float)rand()/(RAND_MAX+1.);
      for(j=0;j<60;j++) if(rd<distAge[j]) break;
      M[i].age=j+1;
    }
    /////////////////////////////////////////////////////////////////
    // getchar();

    /*
     for(i=0;i<NM;i++){
       printf("%d %d %d %d\n",M[i].age,M[i].ageofdeath,M[i].health,M[i].numberofbites);
       for(j=0;j<M[i].ageofdeath;j++) printf("%d\n",M[i].bitesdistribuition[j]);
       getchar();
       }*/
    /*-------------------------------*/
    
    
    set_up_humans(H);
    sexual_tree(H);
    
    ///Setting up the random latent person;
    
    for(i=0;i<initial_latent;i++){
      
      
      
      rn=N*((float)rand()/(RAND_MAX+1.));
      //printf("initial latent=%d %d\n",N,rn);
      H[rn].health=2;
      
      d=log_normal_sample(h_lognormal_latent_scale,h_lognormal_latent_shape,rand());
      //printf("d=%d\n",d);
      H[rn].statetime=max(4,min(d,h_latency_max));
      H[rn].timeinstate=0;
      H[rn].swap=-1;
    }
    
    /* for(i=0;i<N;i++){printf("%d %d %d %d %d %d\n",i,H[i].health,H[i].partner,H[i].age,H[i].gender,H[i].statetime);
    
       getchar();}*/
    
    
    sprintf(name,"files/teer%d.dat",sim);
    ar=fopen(name,"w");
    season=0;
    controlSeason=1;
    
    /////////Here the loop for time must begin
    for(numberofseason=0;numberofseason<4;numberofseason++){
      
      for(timecount=0;timecount<182;timecount++){
	//printf("%d\n",timecount);
	susc=latent=symp=asymp=sympiso=rec=0;
	for(i=0;i<N;i++){
	  
	  if(H[i].health==1) susc++;
	  else{
	    if(H[i].health==2) latent++;
	    else{
	      if(H[i].health==3) asymp++;
	      else{
		if(H[i].health==4) symp++;
		else{
		  if(H[i].health==5) sympiso++;
		  else rec++;
		}//close 4th else
	      }//close 3rd else
	    }//close second else
	  }//close first else
	  
	}//close for i
	
	fprintf(ar,"%d %d %d %d %d %d %d\n",182*numberofseason+timecount,susc,latent,asymp,symp,sympiso,rec);
	
	//printf("ok5\n");
	BiteTransmission(H,M);
	
	Sexual_interaction(H);
	
	increase_timestateH(H);
	
	update_human(H);
	
	increase_timestateM(M);
	
	update_mosquito(M);
	
	increase_mosquito_age(M,dist);
	
      }//close time
      
      season=season+controlSeason;
      printf("%d\n",season);
      controlSeason*=-1;
      
    }//close season
    fclose(ar);
  }//close sim
  
   
}



void nrerror(char error_text[])
/* Numerical Recipes standard error handler */

{
  fprintf(stderr,"Numerical Recipes run-time error...\n");
  fprintf(stderr,"%s\n",error_text);
  fprintf(stderr,"...now exiting to system...\n");
  exit(1);
}
