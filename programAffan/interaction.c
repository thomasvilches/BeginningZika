void BiteTransmission(struct Human *H,struct Mosquito *M){

  int totalbitestoday,i,numberofNI,random;
  float rd,ProbBite;

  int *NonIsolated=malloc(N*sizeof(int));
  totalbitestoday=0;

  ////search for the isolated
  numberofNI=0;
  for(i=0;i<N;i++){
    if(H[i].health!=5){///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      NonIsolated[numberofNI]=i;
      numberofNI++;
    }
    // else getchar();
  }//close for
  //printf("num=%d\n",numberofNI);
  //getchar();
  
  for(i=0;i<NM;i++){
    //check if the mosquito will bite, it'll be implemented later
    //calculte ProbBite
    if(M[i].bitesdistribuition[M[i].age-1]){
     
      // printf("aaa %d %d %d %d\n",i,M[i].bitesdistribuition[M[i].age-1],M[i].age-1,M[i].ageofdeath);
      ProbBite=1;
      rd=(float)rand()/(RAND_MAX+1.);
      if(rd<ProbBite){//if it bites
	totalbitestoday++;
	
	//pick a random person in NonIsolated
	random=numberofNI*((float)rand()/(RAND_MAX+1.));
	
	//1- if person is susc and mosquito is symp
	if(M[i].health==3){
	  if(H[NonIsolated[random]].health==1){
	    //printf("ok2\n");
      	    rd=(float)rand()/(RAND_MAX+1.);
	    if(rd<prob_infection_MtoH){
	      H[NonIsolated[random]].swap=2;
	      H[NonIsolated[random]].latentfrom=1;
	    }//close if rand
	  }//close if person
	}  //close if mosquito
	
	//2- infected person, mosquito susc
	else{
	  if(M[i].health==1){
	    //printf("ok3 %d\n",H[NonIsolated[random]].health);
	    if(H[NonIsolated[random]].health==4){
	      //printf("ok4\n");
	      rd=(float)rand()/(RAND_MAX+1.);
	      if(rd<prob_infection_HtoM){
		M[i].swap=2;
	      }//close if rand
	      
	    }//close if person 4
	    else{
	      
	      if(H[NonIsolated[random]].health==3){
		//printf("ok5\n");
		rd=(float)rand()/(RAND_MAX+1.);
		if(rd<prob_infection_HtoM*reduction_factor){
		  M[i].swap=2;
		}//close if rand
	      }//close if person 3
	    }//close else person
	    
	  }//close if mosquito
	}
	
      }//close if bite
    }//close if bitesdist
  }//close for
  // getchar();
  free(NonIsolated);
}


void Sexual_interaction(struct Human *H){

  ///Find the person who have partners

  int i,numberofWHS;
  float rd,prob_have_sex,proboftransmission;
  
 
  for(i=0;i<N;i++){
    if(H[i].partner>-1){
      proboftransmission=0;
     
      if(H[H[i].partner].health==1){//if the partner is susc	  
	///testing the states of the sexual partners
	if(H[i].health==4){
	  prob_have_sex=(float)(H[i].sexfrequency-H[i].cumulativesex)/(7.0-H[i].cumulativedays);
	  
	  H[i].cumulativedays++;
	  
	  rd=(float)rand()/(RAND_MAX+1.);
	  if(rd<prob_have_sex){	//prob have sex
	    H[i].cumulativesex+=1;
	    proboftransmission=H[i].sexprobability*(1-condom_reduction);
	  }
	}//close if 4
	else{
	  if(H[i].health==5){
	    prob_have_sex=(float)(H[i].sexfrequency-H[i].cumulativesex)/(7.0-H[i].cumulativedays);
	    H[i].cumulativedays++;
	    
	    rd=(float)rand()/(RAND_MAX+1.);
	    if(rd<prob_have_sex){
	      H[i].cumulativesex+=1;
	      proboftransmission=H[i].sexprobability*(1-condom_reduction);
	      
	    }//close if
	  }//close if 5
	  else{
	    if(H[i].health==6){
	      
	      if(H[i].recoveredfrom==5){
		prob_have_sex=(float)(H[i].sexfrequency-H[i].cumulativesex)/(7.0-H[i].cumulativedays);
		H[i].cumulativedays++;
		
		rd=(float)rand()/(RAND_MAX+1.);
		if(rd<prob_have_sex){
		  H[i].cumulativesex+=1;
		  proboftransmission=H[i].sexprobability*(1-condom_reduction);
		  
		}
	      }//close if recovered from 5
	      else{
		if(H[i].recoveredfrom==3){
		  prob_have_sex=(float)(H[i].sexfrequency-H[i].cumulativesex)/(7.0-H[i].cumulativedays);
		  H[i].cumulativedays++;
		  
		  rd=(float)rand()/(RAND_MAX+1.);
		  if(rd<prob_have_sex){
		    H[i].cumulativesex+=1;
		    proboftransmission=H[i].sexprobability*reduction_factor;
		   
		  }
		}//close if recovered from 3
		else{
		  if(H[i].health==4){
		    prob_have_sex=(float)(H[i].sexfrequency-H[i].cumulativesex)/(7.0-H[i].cumulativedays);
		    
		    H[i].cumulativedays++;
		    
		    rd=(float)rand()/(RAND_MAX+1.);
		    if(rd<prob_have_sex){	//prob have sex
		      H[i].cumulativesex+=1;
		      proboftransmission=H[i].sexprobability*(1-condom_reduction);
		    }
		  }
		}//close else for 4
	      }//close else
	    }//close if 6
	    //-------------------------------------------------------------//
	    else{//asymp doesnt use condom
	      if(H[i].health==3){
		prob_have_sex=(float)(H[i].sexfrequency-H[i].cumulativesex)/(7.0-H[i].cumulativedays);
		H[i].cumulativedays++;
		
		rd=(float)rand()/(RAND_MAX+1.);
		if(rd<prob_have_sex){
		  H[i].cumulativesex+=1;
		  proboftransmission=H[i].sexprobability*reduction_factor;
		}
	      }//close if 3
	    }//close else after 6
	  }//close else after 5
	}//close else after 4
	
	
	rd=(float)rand()/(RAND_MAX+1.);
	if(rd<proboftransmission){
	  
	  //printf("partner=%d %d\n",H[i].partner,i);
	  // getchar();
	  H[H[i].partner].swap=2;
	  H[H[i].partner].latentfrom=2;
	}//close if transmission
	
      }
    }//close if partner it has partner
    
    
  }//close for
  //getchar();
}
