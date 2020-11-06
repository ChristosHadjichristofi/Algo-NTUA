#include <iostream>
using namespace std;

int main(){
	
	int N, K, D, T, Ts, Tf, Cs, Cf;
	
	cin >> N >> K >> D >> T;
	int cars[N][2], stations[K+2];
	
	stations[0] = 0;
	stations[K+1] = D;
	
	for(int i = 0; i < N; i++)
		cin >> cars[i][0] >> cars[i][1];
	
	for(int i = 1; i < K+1; i++)
		cin >> stations[i];
	
	cin >> Ts >> Cs >> Tf >> Cf;

	return 0;
}
