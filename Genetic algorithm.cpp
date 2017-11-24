/*
AUTHOR: ABHISHEK V
TITLE OF THE PROGRAM: Genetic Algorithm designed for cognitive radio spectrum allocation
*/
#include<iostream>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
#include<cstdio>
#define CROSSOVER_RATE 0.7
#include<fstream>
#define MUTATION_RATE 0.01
#define MAX_GENERATIONS 100
#define POP_SIZE 100

//generates float between 0 and 1
#define RANDOM_NUM ((float)rand()/(RAND_MAX+1))

int v,k;
int pop_n;
struct individual
{
	float fitness;
	string bits[1000];
	int prim[100][100];
	individual(): fitness(0.0){};
};

int cr_c=0,mt_c=0;
int odd=0;
//  -------------------------   LIST OF FUNCTIONS USED----------------------------//
/*
1.FITNESS FUNCTION
2.ROULETTE WHEEL FUNCTION
3.CROSSOVER FUNCTION
4.MUTATION FUNCTION
5.DISPLAY OPTIMAL INDIVIDUAL(SOLUTION)
*/
//-------------------------------------------------------------------------------//



//---------------------FUNCTION PROTOTYPE DECLARATIONS--------------------------//
int assignfitness(string);
void roulettewheel(int,individual[],int,individual &);
void crossover(individual,individual,individual &,individual &);
void mutation(individual &);
void findOptimalIndividual(individual [],int);
//-----------------------------------------------------------------------------//


//--------------------BEGINNING OF MAIN FUNCTION-------------------------------//
int main()
{
	int sol_found=0;
	srand((int)time(NULL));
	char op;
	//cout<<"Read input from file? Y/n: ";
	//cin>>op;
	//if(op=='Y'||op=='y')
	cout<<"fe";
	freopen("input.txt","r",stdin);
	//freopen ("myfile.txt","w",stdout);
	cout<<"Enter number of secondary users and channels(VxK): ";
	cin>>v>>k;
	
	float totalfitness=0;
	individual pop[1000];
    cout<<"Enter number of individuals in initial population: ";
    cin>>pop_n;
    cout<<"(ensure chromosome length is equal to "<<v<<"):"<<endl;
    for(int i=0;i<pop_n;i++)
    {  
    	for(int j=0;j<k;j++)
    	{
    		cout<<"Enter chromosome "<<j+1<<" for individual "<<i+1<<": ";
    		cin>>pop[i].bits[j];
    	}
    }
    //clock_t startTime;
    bool bfound=false;
    int no_of_generations=0;
    //LOOP BEGINS
     clock_t startTime;
    while(!bfound)
    {
	    startTime= clock();
    	totalfitness=0;
    	int factor=0;
    	//assign fitness to population
    	for(int i=0;i<pop_n;i++)
    	{
    		pop[i].fitness=v*k;
    		factor=0;
    		int temp;
    		//second loop assigns fitness score to one individual in the population
    		for(int j=0;j<k;j++)
    		{
    			temp=0;
		       temp+=assignfitness(pop[i].bits[j]);
		       if(temp==10000)
		          factor++;
		       else
		       pop[i].fitness+=temp;
		    }
		    if(factor!=0)
		    pop[i].fitness/=factor;
		    pop[i].fitness=pop[i].fitness/(v*k);
		    //cout<<pop[i].fitness;
		    //cout<<"Fitness of individual "<<i<<" "<<pop[i].fitness<<endl;
			totalfitness+=pop[i].fitness;
	    }
	    //-----------------DISPLAY FITNESS OF POPULATION---------------------------
    	/*for(int i=0;i<pop_n;i++)
    	{
		       cout<<"Fitness of individual "<<i<<": "<<pop[i].fitness<<endl;
	    }*/
	    //-----------------------------------------------------------------------
	    
	    
	    //select two individual for crossover using roulette wheel
	    //create temporary storage for new population
	    int pop_new=0;
	    int i=0;
	    individual parent1; 
	    individual parent2;
	    individual offspring[1000];
		while(pop_new<POP_SIZE)
		{
			 roulettewheel(totalfitness,pop,pop_n,parent1);
			 roulettewheel(totalfitness,pop,pop_n,parent2);
			 //crossover
			 if (RANDOM_NUM < CROSSOVER_RATE)
             {
			 crossover(parent1,parent2,offspring[i],offspring[i+1]);
		     }
		     else
		     {
		     	offspring[i]=parent1;
		     	offspring[i+1]=parent2;
		     }
			 //mutation
			 
			  if(RANDOM_NUM<MUTATION_RATE)
              {
   	             mutation(offspring[i]);
			     mutation(offspring[i+1]); 
              }
			 pop_new+=2;
			 i=pop_new;
		}
	    
	     //replace current population with new population
	    for(int i=0;i<pop_new;i++)
	    {
	    	pop[i]=offspring[i];
	    	pop[i].fitness=0;
	    }
	    pop_n=pop_new;
	    /*for(int i=0;i<pop_new;i++)
	    {
	    	for(int j=0;j<v;j++)
	    	{cout<<pop[i].bits[j];
	    	cout<<endl;
	        }
	    cout<<endl;
	    }*/
	    
	    if(no_of_generations==MAX_GENERATIONS)
	    {
	       sol_found=1;
	       break;
	    }
	    cout<<no_of_generations<<endl;
	    no_of_generations++;
    }
    cout<<"-----------------------------------------------------------------------\n";
    cout<<"                  PROGRAM EXECUTION STATISTICS                         \n\n";
    cout<<"Optimal individual after "<<no_of_generations<<" generations: "<<endl;
    cout<<endl;
    if(sol_found==1)
    {
    	findOptimalIndividual(pop,pop_n);
    }
    cout<< "Execution time: "<< double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    cout<<"Number of crossovers: "<<cr_c<<endl;
    cout<<"Number of mutations: "<<mt_c<<endl;
    cout<<"ODD: "<<odd;
    cout<<"-----------------------------------------------------------------------\n";
    cout<<"\nPress any key to terminate program";
    getch();
    cout<<"\rPress any key to close the window ";
    //--------------------END OF MAIN FUNCTION --------------------------------//
}

//---------------------FITNESS ASSIGNMENT FUNCTION-----------------------------//
int assignfitness(string individual)
{
	
	//cout<<"Entered assignfitness"<<endl;
	int score_init=0;
	int flag=0;
	int no=0;
      for(int i=0;i<individual.length();i++)
	  {
	  	 if(individual[i]=='1')
	  	 {
	  	 	no++;
	  	 	if(flag==0)
	  	 	{
	  	    flag=1;
	  	    }
	  	    else
	  	      score_init-=1;
	  	 }
	  }
	  if(no==0)
	  {
	  	return 10000;
	  }
	  if(flag==1)
	  return score_init;
	  else return 0;	
}
//------------------------END OF FITNESS FUNCTION----------------------------------//




//------------------------ROULETTE WHEEL FUNCTION----------------------------------//
void roulettewheel(int totalfitness,individual population[],int pop_n,individual &p1)
{
	int r=rand();
	//	cout<<"random number: "<<r<<" ";
	float slice=(float)(r%totalfitness);
	float fitness_t=totalfitness;
	//cout<<totalfitness;
	//cout<<"Slice: "<<slice<<endl;
	for(int i=0;i<pop_n;i++)
	{
		fitness_t-=population[i].fitness;
		if(fitness_t<slice)
		{
	    //cout<<"Individual "<<i<<" is returned!"<<endl;
	      p1=population[i];
	      break;
	    }
	}
}
//------------------------END OF ROULETTE WHEEL FUNCTION--------------------------//



//---------------------------CROSSOVER FUNCTION------------------------------------//

//Crossover method used here is a conflict based crossover//

void crossover(individual parent1,individual parent2,individual &offspring1,individual &offspring2)
{
	cr_c++;
	//cout<<"Entered crossover"<<endl;
	int conf1=0;
	int conf2=0;
	int flag=0;
    for(int i=0;i<k;i++)
    {
    	conf1=conf2=0;
    	flag=0;
    	//checking conflict for ith column(ith chromosome) of parent1
    	for(int j=0;j<v;j++)
    	{
    		if(parent1.bits[i][j]=='1')
    		{
    			if(flag==0)
    			  flag=1;
    			else
    			{
    				conf1++;
    			}
    		}
    	}
    	flag=0;
    	//checking conflict for ith column(ith chromosome) of parent2
    	for(int j=0;j<v;j++)
    	{
    		if(parent2.bits[i][j]=='1')
    		{
    			if(flag==0)
    			  flag=1;
    			else
    			{
    				conf2++;
    			}
    		}
    	}
    	//based on conflict, crossover the chromosome to offsprings 1 and 2
    	if(conf1>=1&&conf2==0)
    	{
    	   offspring1.bits[i]=parent2.bits[i];
    	   offspring2.bits[i]=parent2.bits[i];
        }
        else if(conf1==0&&conf2>=1)
        {
        offspring1.bits[i]=parent1.bits[i];
    	offspring2.bits[i]=parent1.bits[i];
        }
        else
        {
        	int r=rand()%v; 
        	// r unipoint
        	odd++;
       	   offspring1.bits[i]=parent1.bits[i].substr(0,r)+parent2.bits[i].substr(r,v-r);
    	   offspring2.bits[i]=parent2.bits[i].substr(0,r)+parent1.bits[i].substr(r,v-r);
        }
    }
  
}
//--------------------END OF CROSSOVER FUNCTION-----------------------------------//




//---------------------------MUTATION FUNCTION------------------------------------//

void mutation(individual &offspring)
{
	mt_c++;
	//cout<<"Entered mutation"<<endl;
	   int flag=0;
      //find conflict and improve score of individual
      int r2=rand()%v;
      for(int i=0;i<k;i++)
      {
      if(offspring.bits[r2][i]=='1')
         offspring.bits[r2][i]='0';
      else
         offspring.bits[r2][i]='1';
      }
}

//--------------------END OF MUTATION FUNCTION-----------------------------------//




//----------------------FINDING OPTIMAL INDIVIDUAL------------------------------------//

void findOptimalIndividual(individual pop[],int pop_n)
{
	
	cout<<"Optimal solution:"<<endl;
	int flag=0;
    int status=0;
    	for(int i=0;i<pop_n;i++)
    	{
    		pop[i].fitness=v*k;
    		int temp;
    		int factor=0;
    		//second loop assigns fitness score to one individual in the population
    		int assigned=v*k;
    		for(int j=0;j<k;j++)
    		{
    			temp=0;
		       temp+=assignfitness(pop[i].bits[j]);
		       if(temp==10000)
		       {
		       	  assigned--;
		          factor++;
		       }
		       else
		       pop[i].fitness+=temp;
		    }
		    if(factor!=0)
		    pop[i].fitness=pop[i].fitness/factor;
		    pop[i].fitness=pop[i].fitness/(v*k);
	    }
	    int index_max=0;
	    float fitness_max=0;
	    //--
	    for(int i=0;i<pop_n;i++)
	    {
	    	if(pop[i].fitness>fitness_max)
	    	{
	    	   index_max=i;
	    	   fitness_max=pop[i].fitness;
	        }
	    }
	    
	    //display individual with maximum fitness
	    for(int i=0;i<k;i++)
	    {
	    	cout<<"Chromosome "<<i<<": "<<pop[index_max].bits[i]<<endl;
	    }
	    cout<<"Fitness score: ";
	    cout<<fitness_max*100<<"%"<<endl;
	   ofstream output;
       output.open("fitness_runs.txt",std::ios_base::app);
	    output<<fitness_max*100<<endl;
	   output.close();
    
}
//--------------------END OF OPTIMAL INDIVIDUAL FUNCTION-----------------------------------//


//OTHER CODE//


	/*cout<<"\n Parent 1: "<<endl;
    	for(int j=0;j<k;j++)
    	{
    		cout<<parent1.bits[j];
    		cout<<endl;
    	}
    	cout<<"Parent 2; "<<endl;
    		for(int j=0;j<k;j++)
    	{
    		cout<<parent2.bits[j];
    		cout<<endl;
    	}
    	cout<<"Offspring 1: "<<endl;
    		for(int j=0;j<k;j++)
    	{
    		cout<<offspring1.bits[j];
    		cout<<endl;
    	}
    		cout<<"Offspring 2: "<<endl;
    		for(int j=0;j<k;j++)
    	{
    		cout<<offspring2.bits[j];
    		cout<<endl;
    	}*/
    	
    	
//-----//
