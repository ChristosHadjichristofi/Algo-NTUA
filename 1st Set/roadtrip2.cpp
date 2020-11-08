#include <iostream>
#include <algorithm>
using namespace std;

/*GLOBAL DECLARATIONS OF LISTS*/
#define MAX_N	4000001
#define MAX_K	2000001
pair<int,int> cars[MAX_N];
long N, K, D, T, Ts, Tf, Cs, Cf;
long stations[MAX_K+2];
long d[MAX_K+1];
/*END OF GLOBAL DECLARATIONS OF LISTS*/

bool canReachDest(int c){
	long long int time = 0;
	bool canReach = true;
	for(int i = 0; i <= K; i++){
		// if he cant even reach b from a using economic mode.
		if(d[i]*Cs > c){
			canReach = false;
			break;
		}
		// if he can reach b from a exclusively using sport mode.
		else if(d[i]*Cf <= c)
			time += d[i]*Tf;
		// if he can reach b from a using sport mode for some X and eco mode for some Y, or exclusively using eco mode.
		else
			time += d[i]*Ts + (Tf - Ts)*(c - d[i]*Cs)/(Cf - Cs);
	}

	return (time <= T && canReach) ? true : false;
}

int binarySearch(int lowerBound,int upperBound){
	
	if(lowerBound == upperBound) 
		return upperBound;
		
	int middle = lowerBound + (upperBound - lowerBound)/2;

	if(canReachDest(middle)) 
		return binarySearch(lowerBound, middle);
	else
		return binarySearch(middle + 1, upperBound);
}


int main(){
	
	long int Ci, Pi, i = 0, j, longestSubdistance = 0, lowerBound, upperBound, lowestCi, ans = -1;
	bool covers = false;
	
	cin >> N >> K >> D >> T;
	
	stations[0] = 0;
	stations[K+1] = D;
	
	for(int i = 0; i < N; i++){
		cin >> Pi >> Ci;
		cars[i] = make_pair(Pi,Ci);
	}
	
	for(int i = 1; i < K+1; i++)
		cin >> stations[i];
	
	cin >> Ts >> Cs >> Tf >> Cf;
	
	sort(stations, stations+K+2);
	sort(cars, cars+N);
	
	for(int i = 0; i <= K; i++)
		d[i] = stations[i+1] - stations[i];
	
	// find the longest sub-distance that we need to cover without refuel.
	for(int i = 0; i <= K; i++)
		if(d[i] > longestSubdistance)
			longestSubdistance = d[i];
	
	// now using the longest subdistance as low boundary we will check if at least one Ci 
	// can cover this distance using normal mode.
	lowerBound = longestSubdistance * Cs;
	for(int i = 0; i < N; i++)
		if(cars[i].second >= lowerBound){
			covers = true;
			break;
		}
	
	// if at least a car can complete the trip and if by using the sport mode has less or eq time than T
	// we need to set the upper bound so as we can use binary search to find the smallest Ci needed to complete
	// the trip.
	if(covers){
		upperBound = longestSubdistance * Cf;
		lowestCi = binarySearch(lowerBound, upperBound);
		if(!canReachDest(lowestCi)){
			cout << "-1" << endl;
			return 0;
		}
		for(int i = 0; i < N; i++)
			if(cars[i].second >= lowestCi){
				ans = cars[i].first;
				break;
			}		
	}
	cout << ans << endl;
	return 0;
}
