#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

#define DT 1
#define NPRE 100
#define NPOST 20
#define NSPIKE 60
#define VTHRESH 350
#define VRESET -5
#define MASTER 0

//Returns the greater value between a and b
float max(float a, float b){
  return (a<b) ? b: a;
}

//Returns the lesser value between a and b
float min(float a, float b){
  return (a<b) ? a: b;
}

//Returns a value m<v<M
float clamp(float v, float m, float M){
  return max(min(v,M),m);
}

//Integrate x0 using the Rotter-Deismann method
float solveRD(float x0, float a, float b){
  return x0*exp(-a*DT)+b;
}

//Generate the artificial data set used during simulation
int genData (int size, int rank, int *timings, float *weights, float v){
  int i, j;              //Loop Variables
  int sSum, max=0;       //Cumulative sum and max
  float R, lam, jitter;  //Random, rate, and jitter

  //Convert rate to milliseconds
  lam = (1/v)*1000.0;

  //Seed the random value
  srand((unsigned)time(0));

  //For each neuron
  for (i=0;i<size;i++){
    sSum=0;
    //For each synthetic spike
    for (j=0;j<NSPIKE;j++){
      R=rand()/(float)(RAND_MAX); //R [0,1]
      sSum+=(int)(-1*lam*log(R)); //Exponential variate, discretized to grid
      timings[i*NSPIKE+j]=sSum;   //Fill timings array
    }
    //Initialize weights
    for (j=0;j<NPOST;j++)
      weights[i*NPOST+j]=rand()/(float)(RAND_MAX);
    
    //update max
    if (sSum>max) max = sSum;
  }
 
  return max;
}

//jitter our previously generated spike timings
int jitter(int size, int *timings, int sigma, int rank){
  int i,j;
  float R1,R2, jit;

 //We want to jitter uniquely on each core
  srand((unsigned)time(0)+rank);

  //For each neuron
  for (i=0;i<size;i++)
    //For each synthetic spike
    for (j=0;j<NSPIKE;j++){
      R1=rand()/(float)(RAND_MAX);
      R2=rand()/(float)(RAND_MAX);
      jit=sqrt(-2*log(R1))*cos(2*M_PI*R2); //Use Box-Muller transform to generate jitter
      timings[i*NSPIKE+j]+=jit*sigma;      //Update timings
    }
}

/*
  Main method, which generates synthetic spiking network, jitters it by core rank,
  and solves the system through time
 */
int main(int argc, char *argv[]){

  int 
    rank,                   //Current core rank
    size,                   //Number of available cores
    localSize;              //Neurons per core
    
  //Initialize MPI
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  //Master picks up the slack
  localSize = NPRE/size+(rank==MASTER)*NPRE%size;

  FILE *output,*weightData; //Output files for voltages and weights
  double start,end;         //Used for timing

  int 
    tMax=0,             //Time of last spike
    tmp=0,              //Temporary variable
    count=0,            //Number of post-synaptic spikes
    i,j,time;           //Loop and timing variables

  float 
    v=5.0,              //Spiking rate
    nu=0.2,             //Learning rate
    mu=0.02,            //mu (used in power rule)
    wMax=1.0,           //Max weight value
    A=0.050,            //Pre-synaptic decay rate
    B=1.0,              //Spike amplitude
    C=0.0,              //Pre-synaptic spike dampener
    D=0.020;            //Voltage decay

  float 
    Apost=0.025,       //Post-synaptic decay rate
    Cpost=1.0,         //Post-synaptic spike dampener
    tauM=50.0,         //Membrane time constant
    tauS=20.0,         //synaptic time constant
    tau,               //Total time constant
    inhib;             //Inhibition term

  float //Our float arrays
    *xCum=calloc(NPOST,sizeof(float)),        //Cumulative voltage entering pre-synaptic neurons
    *V=calloc(NPOST,sizeof(float)),           //Pre-Synaptic Voltage
    *hostCum=malloc(NPOST*sizeof(float)),     //Cumulative voltage on host core
    *dW=calloc(NPOST*localSize,sizeof(float)),//Change in weights
    *W=calloc(NPOST*localSize,sizeof(float)), //Weights
    *xPre=calloc(localSize,sizeof(float)),x,y,//Pre-synaptic voltage
    *xPost=calloc(NPOST,sizeof(float));       //Post-synaptic voltage

  int //Our integer arrays 
    *weights=calloc(25,sizeof(int)),          //Weights
    *weightBin=calloc(25,sizeof(int)),        //Weight bins
    timings[localSize*NSPIKE],                //Spike timings
    sPre[localSize],                          //Pre-synaptic spikes
    sPost[NPOST];                             //Post-synaptic spikes
    
    
  //Open the data file on master core
  if (rank==MASTER)
    output = fopen("dat.out","w");

  tau = (tauM*tauS)/(tauM-tauS);

  //Wait for all cores, then initialize timing variable
  MPI_Barrier(MPI_COMM_WORLD);
  start=MPI_Wtime();

  tmp=genData(localSize,rank,timings,W,v);
  jitter(localSize,timings,3,rank);
     
  //Find the max time across all cores
  MPI_Allreduce(&tmp,&tMax,1,MPI_INT,MPI_MAX,MPI_COMM_WORLD);
  
  if (rank==MASTER)
    printf("The last spike occurs at %d\n",tMax);
  
  //Now start the time loop; go a little extra to allow decay
  for (time=0;time<tMax+200;time++){
    //This is for data output
    x=W[0];
    y=xPre[0];
    if (rank==1) MPI_Send(&x,1,MPI_FLOAT,MASTER,13,MPI_COMM_WORLD);
    if (rank==0) MPI_Recv(&x,1,MPI_FLOAT,1,13,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    if (rank==1) MPI_Send(&y,1,MPI_FLOAT,MASTER,13,MPI_COMM_WORLD);
    if (rank==0) MPI_Recv(&y,1,MPI_FLOAT,1,13,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    
    if (rank==MASTER)
      fprintf(output,"%d\t%lf\t%lf\t%lf\n",time,x,y,xPost[0]);

    //Reset cumulative voltage
    for (j=0;j<NPOST;j++)
      xCum[j]=0;
 
    //Determine the presence of a spike at this time
    for (i=0;i<localSize;i++){
      for (j=0;j<NSPIKE;j++){
	sPre[i] = (timings[i*NSPIKE+j] == time);
	if (sPre[i]) break;
      }
      //Calculate change in weights
      for (j=0;j<NPOST;j++)
	dW[NPOST*i+j] = nu*(pow((1.0-W[i*NPOST+j]),mu)*xPre[i]*sPost[j] - 
			    pow(W[i*NPOST+j],mu)*xPost[j]*sPre[i]);
      //Solve pre-synaptic voltage
      xPre[i] = solveRD(xPre[i],A,sPre[i]*(B-C*xPre[i]));
      
      //Calculate cumulative voltage to post-synaptic cell
      for (j=0;j<NPOST;j++)
	xCum[j] += xPre[i]*W[NPOST*i+j];
    }
    
    //Reduce all cumulative voltages to a single (host stored) array
    MPI_Reduce(xCum,hostCum,NPOST,MPI_FLOAT,MPI_SUM,MASTER,MPI_COMM_WORLD);
   
    //Update the weights
    for (i=0;i<localSize;i++)
      for (j=0;j<NPOST;j++)
	W[i*NPOST+j]=clamp((W[i*NPOST+j]+dW[i*NPOST+j]),(float)0,(float)1);
    
    //Begin pre-synaptic calculations
    if (rank==MASTER){
      //Initialize inhibition, subtract when we need to
      inhib=0;
      for (i=0;i<NPOST;i++)
	inhib+=xPost[i];

      //Calculate post-synaptic voltage
      for (j=0;j<NPOST;j++){
	inhib-=xPost[j];
	hostCum[j]*=2;
	V[j]=solveRD(V[j],D,(hostCum[j]-inhib)*
		     tau*(solveRD(1,D,0)-solveRD(1,A,0)));
	//Determine the presence of a spike
	sPost[j] = (V[j]>VTHRESH);
	if (sPost[j]){
	  V[j]=VRESET;
	  count++;
	}
	inhib+=xPost[j];
      }

      //Integrate post-synaptic voltage
      for (j=0;j<NPOST;j++)
	xPost[j]=solveRD(xPost[j],Apost,
			 sPost[j]*(B-Cpost*xPost[j]));
    }

    //Send post-synaptic spikes/voltages to other cores
    MPI_Bcast(sPost,NPOST,MPI_INT,MASTER,MPI_COMM_WORLD);
    MPI_Bcast(xPost,NPOST,MPI_FLOAT,MASTER,MPI_COMM_WORLD);
  }
  
  //Close the output file
  if (rank==MASTER) 
    fclose(output);

  //Bin the weights on each core
  for (i=0;i<localSize;i++)
    for (j=0;j<NPOST;j++){
      weights[((int)(W[NPOST*i+j]*100.0))/4]++;
     }
  
  //Reduce the bins down to the master core
  MPI_Reduce(weights,weightBin,25,MPI_INT,MPI_SUM,MASTER,MPI_COMM_WORLD);
  
  //Output weight bins to file, then close it
  if (rank==MASTER){
    weightData=fopen("weight.out","w");
    for (i=0;i<25;i++)
      fprintf(weightData,"%lf\t%d\n",((float)i*4.0)/100.0,weightBin[i]);
    fclose(weightData);
  }

  //Wait for all cores to finish up and find the end time
  MPI_Barrier(MPI_COMM_WORLD);
  end=MPI_Wtime();
  
  //Print the runtime
  if (rank==MASTER)
    printf("Runtime = %lf\n Count is %d\n", end-start,count/NPOST);
  
  //Close up MPI and return
  MPI_Finalize();
  return 1;
}
