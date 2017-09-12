void set_up_mosquito(struct Mosquito M[NM]){

  for(i=0;i<N;i++) {//H[i]={1,0,-1,-1,1,999,-1,-1,-1};
    M[i].health=1;
    M[i].infectionfrom=0;
    M[i].age=-1;
    M[i].ageofdeath=-1;
    M[i].statetime=999;
    M[i].timeinstate=999;
    M[i].partner=-1;
    M[i].numberofbites=-1;
    M[i].bitesdistribuition=-1;
  }
  
}//close function
