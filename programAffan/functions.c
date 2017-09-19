void increase_timestateH(struct Human *H){

  int i;
  float rd,rn;
  
  for(i=0;i<N;i++){
    H[i].timeinstate++;

    if(H[i].timeinstate>H[i].statetime){
      
      if(H[i].health==2){
	rd=(float)rand()/RAND_MAX;
	rn=rd*(ProbLatentToASymptomaticMax-ProbLatentToASymptomaticMin)+ProbLatentToASymptomaticMin;
	rd=(float)rand()/RAND_MAX;
	if(rd<rn) H[i].swap=3;
	else{
	  //lets check if it will be isolated
	  rd=(float)rand()/RAND_MAX;
	  if(rd<ProbIsolationSymptomatic) H[i].swap=5;
	  else H[i].swap=4;	    
	}//close else
      }//close if latent

      else{
	if(H[i].health==3){
	  H[i].swap=6;
	}
	else{
	  if(H[i].health==4) H[i].swap=6;
	  else if(H[i].health==5) H[i].swap=6;
	}//close else if 3
      }//close else
      
    }//close if timein>statetime
  }//close for i

}

/*void start_sex(struct Human *H){

  int i;
  float rd;
  
  for(i=0;i<N;i++){

    if(H[i].sexfrequency>=0){
      if(H[i].age>=15){
	if(H[i].partner>-1){

	  H[i].cumulativedays=0;
	  H[i].cumulativesex=0;
	  rd=(float)rand()/RAND_MAX;
	  
	  H[i].sexprobability=rd*(0.05-0.01)+0.01;
	}//close if partner
      }//close if age
    }//close if freq

  }//close for
  }*/

void increase_timestateM(struct Mosquito *M){

  int i;

  for(i=0;i<NM;i++){
    M[i].timeinstate++;
    if(M[i].timeinstate>M[i].statetime){
      if(M[i].health==2) M[i].swap=3;
    }//close if instate>statetime
  }//close for i
  
}


void update_human(struct Human *H){

  int i,d;
  float rd;
  
  for(i=0;i<N;i++){

    if(H[i].swap==2){

      H[i].health=2;
      d=5;//log_normal_sample(h_lognormal_latent_scale,h_lognormal_latent_shape,time(NULL));
      H[i].statetime=max(4,min(d,h_latency_max));
      H[i].timeinstate=0;
      H[i].swap=-1;

    }//close if swap 2
    else{

      if(H[i].swap==3){
	H[i].health=3;
	d=log_normal_sample(h_lognormal_symptomatic_scale,h_lognormal_symptomatic_shape,time(NULL));
	H[i].statetime=max(3,min(d,h_symptomatic_max));
	H[i].cumulativedays=0;
	H[i].cumulativesex=0;
	rd=(float)rand()/RAND_MAX;
	
	H[i].sexprobability=rd*(0.05-0.01)+0.01;
	H[i].timeinstate=0;
	H[i].swap=-1;
      }//close if
      else{
	if(H[i].swap==4){
	  H[i].health=4;
	  d=log_normal_sample(h_lognormal_symptomatic_scale,h_lognormal_symptomatic_shape,time(NULL));
	  H[i].statetime=max(3,min(d,h_symptomatic_max));
	  H[i].cumulativedays=0;
	  H[i].cumulativesex=0;
	  rd=(float)rand()/RAND_MAX;
	  
	  H[i].sexprobability=rd*(0.05-0.01)+0.01;
	  H[i].timeinstate=0;
	  H[i].swap=-1;
	}//close if
	else{
	  if(H[i].swap==5){
	    H[i].health=5;
	    d=log_normal_sample(h_lognormal_symptomatic_scale,h_lognormal_symptomatic_shape,time(NULL));
	    H[i].statetime=max(3,min(d,h_symptomatic_max));
	    H[i].cumulativedays=0;
	    H[i].cumulativesex=0;
	    rd=(float)rand()/RAND_MAX;
	    
	    H[i].sexprobability=rd*(0.05-0.01)+0.01;
	    H[i].timeinstate=0;
	    H[i].swap=-1;
	  }//close if
	  else{
	    if(H[i].swap==6){

	      H[i].recoveredfrom=H[i].health;
	      H[i].health=6;
	      H[i].statetime=999;
	      H[i].timeinstate=0;
	      H[i].swap=-1;
	      
	    }//close if
	  }//close 4th else
	}//close 3rd else
      }//close 2nd else
    }//close 1st else
  }//close for i

}

int max(int a,int b){
  int max1;
  if(a>=b) max1=a;
  else max1=b;

  return(max1);
}

int min(int a,int b){
int min1;
  if(a<=b) min1=a;
  else min1=b;

  return(min1);
}


void update_mosquito(struct Mosquito *M){

  int i,d;

  for(i=0;i<NM;i++){
    if(M[i].swap==2){

      M[i].health=2;
      d=log_normal_sample(m_lognormal_latent_scale,m_lognormal_latent_shape,time(NULL));
      M[i].statetime=max(m_latency_min,min(d,m_latency_max));
      M[i].timeinstate=0;
      M[i].swap=-1; 
    }//close if
    else{
      if(M[i].swap==3){
	M[i].health=3;
	M[i].statetime=M[i].ageofdeath+1;
	M[i].timeinstate=0;
	M[i].swap=-1; 
      }
    }//close else

      
  }//close for
  
}

void increase_mosquito_age(struct Mosquito *M,float dist[2][60]){

  int i;

  for(i=0;i<NM;i++){

    M[i].age++;
    if(M[i].age>M[i].ageofdeath)
      set_up_mosquito(M,i,dist);
  }
  
}
