#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define MAX_INT 999999999
#define MAX_N 5001

vector <pair<int, int> > A1, A2, A3, B1, B2, B3, C1, C2, C3;
int A[MAX_N] = {0}, B[MAX_N] = {0}, C[MAX_N] = {0}, Set1[MAX_N] = {0}, Set2[MAX_N] = {0}, Set3[MAX_N] = {0};
int N, M;

void knapsack(int *dp, vector <pair<int, int> > costs){

    int totalQuantity = 0;

    for (int i = 1; i <= N; i++) dp[i] = MAX_INT;

    for (int i = 0; i < costs.size(); i++){
        int currQuantity = costs[i].first, currPrice = costs[i].second;
        totalQuantity += currQuantity;
        for (int j = min(N, totalQuantity); j >= 1; j--) 
            dp[j] = min(dp[j], dp[max(j - currQuantity, 0)] + currPrice);
    }

}

void completeSet(int Set[]){ 
    for (int i = 0; i <= N; i++)
        (A[i] == MAX_INT || B[i] == MAX_INT || C[i] == MAX_INT) ? Set[i] = MAX_INT : Set[i] = A[i] + B[i] + C[i];
}

int main(){

    int quantity, price, minPrice = MAX_INT;
    string itemTrader;
    cin >> N >> M;

    for (int i = 0; i < M; i ++){
        cin >> itemTrader >> quantity >> price;
        if (itemTrader[0] == '1'){
            if (itemTrader[1] == 'A') A1.push_back(make_pair(quantity, price));
            else if (itemTrader[1] == 'B') B1.push_back(make_pair(quantity, price));
            else C1.push_back(make_pair(quantity, price));
        }
        else if (itemTrader[0] == '2'){
                if (itemTrader[1] == 'A') A2.push_back(make_pair(quantity, price));
                else if (itemTrader[1] == 'B') B2.push_back(make_pair(quantity, price));
                else C2.push_back(make_pair(quantity, price)); 
        }
        else {
            if (itemTrader[1] == 'A') A3.push_back(make_pair(quantity, price));
            else if (itemTrader[1] == 'B') B3.push_back(make_pair(quantity, price));
            else C3.push_back(make_pair(quantity, price)); 
        }
    }
    
    knapsack(A, A1); knapsack(B, B1); knapsack(C, C1); completeSet(Set1);
    knapsack(A, A2); knapsack(B, B2); knapsack(C, C2); completeSet(Set2);
    knapsack(A, A3); knapsack(B, B3); knapsack(C, C3); completeSet(Set3);

    for (int i = 0; i <= N; i++)
        for (int j = N - i; j >= 0; j--){
            if (Set1[i] == MAX_INT || Set2[j] == MAX_INT || Set3[N - j - i] == MAX_INT) continue;
            if (minPrice > Set1[i] + Set2[j] + Set3[N - j - i]) minPrice = Set1[i] + Set2[j] + Set3[N - j - i];
        }

    (minPrice == MAX_INT) ? cout << "-1" << endl : cout << minPrice << endl;
}
