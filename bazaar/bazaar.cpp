#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define cin infile
#define INTEGER_MAX 1000000001
#define MAX_M 1501

vector <pair<int, int> > A1, A2, A3, B1, B2, B3, C1, C2, C3;
int A[MAX_M] = {0}, B[MAX_M] = {0}, C[MAX_M] = {0}, Set1[MAX_M] = {0}, Set2[MAX_M] = {0}, Set3[MAX_M] = {0};
int N, M;

void knapsack(int *dp, vector <pair<int, int> > costs){

    int totalQuantity = 0;

    for (int i = 1; i <= M; i++) dp[i] = INTEGER_MAX;

    for (int i = 0; i < costs.size(); i++){
        int currQuantity = costs[i].first, currPrice = costs[i].second;
        totalQuantity += currQuantity;
        for (int j = min(N, totalQuantity); j >= 1; j--) 
            dp[j] = min(dp[j], dp[max(j - currQuantity, 0)] + currPrice);
    }

}

void completeSet(int Set[]){ 
    for (int i = 0; i <= M; i++)
        (A[i] == INTEGER_MAX || B[i] == INTEGER_MAX || C[i] == INTEGER_MAX) ? Set[i] = INTEGER_MAX : Set[i] = A[i] + B[i] + C[i];
}

int main(){

    ifstream infile("lab02/bazaar/input0.txt");

    int quantity, price, minPrice = INTEGER_MAX;
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

    for (int i = 0; i <= M; i++)
        for (int j = M - i; j >= 0; j--){
            if (Set1[i] == INTEGER_MAX || Set2[i] == INTEGER_MAX || Set3[i] == INTEGER_MAX) continue;
            if (minPrice > Set1[i] + Set2[j] + Set3[M - j - i]) minPrice = Set1[i] + Set2[j] + Set3[M - j - i];
        }

    (minPrice == INTEGER_MAX) ? cout << "-1" << endl : cout << minPrice << endl;
}
