#include <iostream>
using namespace std;

#define INF     10000000
#define MAX_N   1500
#define MAX_K   500   

int reactions[MAX_N][MAX_N], DP[MAX_N+1][MAX_K+1], N, K;

int main(){

    int min = INF;

    ios_base::sync_with_stdio(false);

    cin >> N >> K;

    // initialize array full of zeros
    for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) reactions[i][j] = 0;

    // read input
    for(int i = 0; i < N - 1; i++) for(int j = 0; j < N - 1 - i; j++) cin >> reactions[i][i+j+1];

    // calculate costs, so as i can have for example the cost of (3,6) in O(1).
    // (3,6) means the reactions of every single chemical in the pot with every other.
    // (3,4),(3,5),(3,6),(4,5),(4,6),(5,6) --> (3,6)
    for(int i = 0, jStart = 1, z; i < N - 1; i++,jStart++){
        z = 0;
        for(int j = jStart; j <= N - 1; j++,z++)
            reactions[z][j] = reactions[z][j] + reactions[z+1][j] + reactions[z][j-1] - reactions[z+1][j-1];
    }

    for (int i = 2; i <= N; i++)
        for (int j = 1; j <= K; j++,min = INF){
            for (int x = 1; x < i; x++){
                if (i < j || i == 0 || j == 0){
                    min = 0;
                    break;
                }
                else if (j == 1){
                    min = reactions[0][i-1];
                    break;
                }
                else (min < DP[x][j-1] + reactions[x][i-1]) ? min = min : min = DP[x][j-1] + reactions[x][i-1];
            }
            DP[i][j] = min;
        }

    cout << DP[N][K] << endl;
}