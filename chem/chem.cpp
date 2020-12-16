#include <iostream>
using namespace std;

#define INF     10000000
#define MAX_N   2500
#define MAX_K   700   

int reactions[MAX_N][MAX_N], DP[MAX_N+1][MAX_K+1], N, K;
int main(){

    cin >> N >> K;

    int min = INF, xStart = 1;

    // initialize array full of zeros
    for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) reactions[i][j] = 0;

    // read input
    for(int i = 0; i < N - 1; i++) for(int j = 0; j < N - 1 - i; j++) cin >> reactions[i][i+j+1];
    
    // calculate costs, so as i can have the (1,6) in O(1).
    for(int i = 0, jStart = 1, z; i < N - 1; i++,jStart++){
        z = 0;
        for(int j = jStart; j <= N - 1; j++,z++)
            reactions[z][j] = reactions[z][j] + reactions[z+1][j] + reactions[z][j-1] - reactions[z+1][j-1];
    }
    
    for (int i = 2; i <= N; i++){
        xStart = 1;
        for (int j = 1; j <= K; j++,min = INF){
            for (int x = xStart; x < i; x++){
                if (j == 1){
                    min = reactions[0][i-1];
                    break;
                }
                else (min > DP[x][j-1] + reactions[x][i-1]) ? (min = DP[x][j-1] + reactions[x][i-1], xStart = x) : (min = min);
            }
            DP[i][j] = min;
        }
    }
    cout << DP[N][K] << endl;
}
