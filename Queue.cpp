#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include <cmath>
using namespace std;

#define ma 4 
#define mb 1
#define State pair<int,int> 
#define AVG pair<int,double>

int main(){
	
	int l, i, k;
	State state;
	//AVG avg_state;
	long int counter;	//counter for each step of simulation
	long int total_people, loss;	//total arrivals
	double event;
	double old_avgE;
	double new_avgE;	
	vector <AVG> avg_state;
	vector <AVG> thrA;
	vector <AVG> thrB;
	vector <AVG> G_total;
	//state = make_pair(0,0);

	//cout << "Enter value k\n";
	//cin >> k;
	cout << "Enter value l\n";
	cin >> l;

	printf("L=%d\n", l);
	for(k=1; k<10; k++){
		vector <long int> visited(20,0);
		vector <double> Probs(11, 0.0);
		double sumA=0.0, sumB=0.0;
		counter=0;
		printf("-----------------------K=%d: Total_people - AVG-------------------\n",k);
		old_avgE=0.0;
		new_avgE=0.0;
		state=make_pair(0,0);
		total_people=0;
		loss=0;		
		
		while(true){
			counter++;
			event =  (double) (rand()) /  (double) (RAND_MAX);
				
			/*Examine all possible situations of queueing system*/
			/*If there is client in server b*/
			if(state.first+ (state.second*10) > 10){ 

				if(state.first == 1){
					if(event <= (l*1.0)/(l+mb)){
						visited[state.first+state.second*10]++;
						state.first=state.first+1;
						if(k==1)
							state.second=0;
						else
							state.second =1;
						total_people++;
					}
					else{
						state.first=state.first-1;
						state.second = 0;
					}
				}
				else{
					if(event <= (l*1.0)/(l+ma+mb)){
						visited[state.first+state.second*10]++;
						if(state.first == k)
							state.second = 0;
						else
							state.second=1;
	
						state.first = state.first+1;
						total_people++;			
					}
					else if (event <= (l+ma)*1.0/(l+ma+mb)){
						state.first=state.first-1;
						state.second = 1;
					}
					else{
						state.first = state.first-1;
						state.second = 0;
					}
				}
				
					
			}/*If there are clients in server a and b*/
			else if(state.first+(state.second*10)> k){ 
				if(state.first == 10){
					if(event <= (l*1.0)/(ma+mb+l)){
						visited[state.first+state.second*10]++;
						total_people++;
						loss++;
					}
					else{
						state.first= state.first-1;
						state.second = 0;
					}
				}
				else if (state.first == (k+1)){
					if(event <= (l*1.0)/(ma+mb+l)){
						visited[state.first+state.second*10]++;
						total_people++;
						state.first= state.first+1;
						state.second = 0;
					}
					else if (event <=((l+ma)*1.0)/(ma+mb+l)){
						state.first = state.first-1;
						state.second = 1;
					}
					else{
						state.first = state.first-1;
						state.second = 0;
					}
			
				}
				else{
					if(event <= (l*1.0)/(ma+mb+l)){
						visited[state.first+state.second*10]++;
						total_people++;
						state.first = state.first+1;
						state.second = 0;
					}
					else{
						state.first=state.first-1;
						state.second = 0;
					}
				}

						
			}/*If there is clinet only in server a*/
			else{ 
				state.second = 0;
				if(state.first == 0){ //we have only arrival
					visited[state.first+state.second*10]++;
					state.first = state.first+1;		//(1,a) state
					total_people ++;
				}
				else{
					if(event <= (l*1.0)/(ma+l)){
						visited[state.first+state.second*10]++;
						state.first = state.first+1;
						total_people++;
					} 
					else
						state.first=state.first-1;		
				}
				
			}

		
			if(counter%1000==0){
				//printf("%li ",total_people);
				printf("%li ", counter);
				Probs[0]=visited[0]/(1.0*total_people);
				new_avgE=0;
				for(i=1; i<10; i++){
					Probs[i] = (visited[i]+visited[i+10])/(1.0*total_people);
					new_avgE = new_avgE + i*Probs[i];
				}
				Probs[10]=visited[10]/(1.0*total_people);
				new_avgE=new_avgE+10*Probs[10];
					
				printf("%f\n", new_avgE);
				//printf("old_avgE-new_avgE:%f-%f=%f\n", old_avgE, new_avgE, old_avgE-new_avgE);
				if(abs(new_avgE - old_avgE)< 0.0001){
						break;
				}else{
					old_avgE=new_avgE;
				}
				
			
			}

			if(counter == 800000)
				break;
		}
		//for(i=0; i<10+k+1; i++)
		//	printf("visited[%d]=%li\n", i, visited[i]);
		printf("loss=%li\n", loss);
		printf("Last Average: %f\n",new_avgE);
		avg_state.push_back(make_pair(k,new_avgE));
		for (i=1; i<(k+1); i++){
			sumA=sumA+ (visited[i]/(1.0*total_people));
			sumB=sumB+ (visited[10+i]/(1.0*total_people));
		}
		sumA=sumA+(visited[0]/(1.0*total_people));
		sumB=sumB+(visited[0]/(1.0*total_people));
		thrA.push_back(make_pair(k,ma*(1-sumB)));
		thrB.push_back(make_pair(k,mb*(1-sumA)));
		G_total.push_back(make_pair(k,l*(1-Probs[10])));		
}
	printf("EROTIMATA 2 kai 3 counter=%li\n", counter);			
	/*for(i=0; i<(int) thrA.size(); i++)
		printf("k=%d: gA+gb=%f+%f=%f G_total=%f and AVG=%f\n", thrA[i].first, thrA[i].second, thrB[i].second, thrA[i].second+thrB[i].second,G_total[i].second, avg_state[i].second);*/
	printf("K-GA-GB-AVG-Gtotal:\n");
	for(i=0; i<(int) thrA.size(); i++)
		printf("%d %f %f %f %f %f\n", thrA[i].first, thrA[i].second, thrB[i].second, thrA[i].second / thrB[i].second, avg_state[i].second, G_total[i].second);
		
	return 0;
}
