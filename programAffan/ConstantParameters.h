//# general parameters
#define sim_time  100       //## time of simulation - 2 years in days
#define grid_size_human  100000
#define grid_size_mosq  500000
#define initial_latent 5  

    //# mosquito lifetime parameters
#define winterlifespan_max 30
#define winterlifespan_min 1
#define summerlifespan_max 60
#define summerlifespan_min 1 

    //# mosquito hazard function parameters
#define aSummer 0.0018;
#define bSummer 0.3228;
#define sSummer 2.1460;
#define aWinter 0.0018;
#define bWinter 0.8496;
#define sWinter 4.2920;

//# disease dynamics- human and mosquitos
#define h_latency_max 8   
#define h_latency_min 4
#define m_latency_max 14
#define m_latency_min 7
#define h_symptomatic_max 6
#define h_symptomatic_min 3

#define ProbLatentToASymptomaticMax 0.8
#define ProbLatentToASymptomaticMin 0.4

#define m_lognormal_latent_shape 2.28 // ## mean 10
#define m_lognormal_latent_scale 0.21 
#define h_lognormal_latent_shape 1.72 // ## mean 5.7
#define h_lognormal_latent_scale 0.21 
#define h_lognormal_symptomatic_shape 1.54 // ## mean 4.7
#define h_lognormal_symptomatic_scale 0.12     

#define prob_infection_MtoH 0.3
#define prob_infection_HtoM 0.3
#define ProbIsolationSymptomatic 0.
#define reduction_factor 0.5

#define condom_reduction 0.

#define NR_END 1
