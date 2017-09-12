
void set_up_humans(struct Human H[N]){

  float x;

    float dist_men[7][6]= {{0.167, 0.334, 0.563, 0.792, 0.896, 1},    //15-24  
			   {0.109,	0.572,	0.7575,	0.943,	0.9725,	1},//25-29
			   {0.201,	0.674,	0.808,	0.942,	0.971,	1},//30-39
			   {0.254,	0.764,	0.8635,	0.963,	0.9815,	1},//40-49
			   {0.456,	0.839,	0.914,	0.989,	0.9945,	1}, //50-59
			   {0.551, 0.905, 0.9525, 1, 1, 1},     //       60-69
			   {0.784, 0.934, 0.963, 0.992, 0.996, 1}} ;      //70+
  
  float dist_women[7][6] = { {0.265,0.412,	0.5885,	0.765,	0.8825,	1}, 
			     {0.151,0.628,	0.804,	0.98,	0.99,	1},
			     {0.228,0.73,	0.8395,	0.949,	0.9745,	1}, 
			     {0.298,0.764,	0.868,	0.972,	0.9855,	1},
			     {0.457,0.819,	0.9035,	0.988,	0.9935,	1}, 
			     {0.579,0.938,	0.969, 1, 1, 1},       
			     {0.789,0.972,	0.979,	0.986,	0.993,	1}};
  
   
  int i,AgeMax,AgeMin,a;
  
  for(i=0;i<N;i++) {//H[i]={1,0,-1,-1,1,999,-1,-1,-1};
    H[i].health=1;
    H[i].latentfrom=0;
    H[i].age=-1;
    H[i].agegroup=-1;
    H[i].gender=1;
    H[i].statetime=999;
    H[i].partner=-1;
    H[i].sexfrequency=-1;
    H[i].cumulativesex=-1;
    H[i].cumulativedays=-1;
  }
   
  for(i=0;i<N;i++){
    //randomizing the age acording to the distribuition
     x=(float)rand()/(RAND_MAX+1.);
     H[i].agegroup=ParametersAge(x,&AgeMax,&AgeMin);//Age group
     H[i].age=(float)rand()/(RAND_MAX+1.)*(AgeMax-AgeMin)+AgeMin;//age
     //printf("idade %d %d\n",H[i].age,H[i].agegroup);
     //----------------------------------------------------------------////
     
     x=(float)rand()/(RAND_MAX+1.);
     if(x<0.5) H[i].gender=2;//gender
     
     /////////////////////////////////////////////////////////////////////////
     
     //number of sexual contacts
     if(H[i].age<15) H[i].sexfrequency=0;
     else{
       H[i].sexfrequency=ParameterSex(H[i].age,H[i].gender,dist_men,dist_women);
       //printf("aa %d %d\n",H[i].sexfrequency,H[i].age);
     }
     
   }//close for
}//main


