#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"CanstantParameters.h"
#define N 50 //Number of Humans
#define NM 40 //Number of Mosquitos


struct Human{

  int health;  //1-susc, 2-lat, 3- Asymp, 4- Symp, 5- SympIso, 6- Rec, 7- Dead
  int latentfrom; //1- bite, 2 - sexual
  int age; //years
  int agegroup;// 0-16
  int gender;//1- Male, 2- Female
  int statetime; //time in each state;
  int partner; //index to the partner in the lattice
  int sexfrequency;
  int cumulativesex;
  int cumulativedays;

};

struct Mosquito{

  int health;  //1-susc, 2-lat, 3-infec
  int infectionfrom; ///----
  int age;//days
  int ageofdeath;//
  int statetime;
  int timeinstate;//time in each state;
  int numberofbites;
  int bitesdistribuition;

};

int ParametersAge(float x,int *Age1,int *Age2);
void set_up_humans(struct Human H[N]);
int ParameterSex(int age,int gender,float dist_men[7][6],float dist_women[7][6]);

int season=1;//summer= 1 winter = -1
