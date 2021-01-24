#include <iostream>
#include <fstream>
#include<bits/stdc++.h> 

using namespace std;

struct Edjes {
    int u; // src
    int v; // dest
    int w; // weight
};

class subset {
public:
    int parent;
    int rank;
};

#define MAX_N	1000001
#define MAX_M   2000001
int N, M;

subset s[MAX_N];
Edjes e[MAX_M], edjes_MST[MAX_M];
list<pair <int, int> > adjList_MST[MAX_N + 1];
int nodesInSubtree[MAX_N], appearances[2 * MAX_M];

// sort edjes of input by asc of width
bool ascWidth(Edjes e1,Edjes e2){ 
	return (e1.w < e2.w); 
}

// Union find for Kruskal
int find(subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
void Union(subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
// end of Union find for Kruskal

void KruskalMST(){

    int res_idx = 0, edj_idx = 0;

    for (int n = 0; n < N; n++) {
        s[n].parent = n;
        s[n].rank = 0;
    }

    while (res_idx < N - 1 && edj_idx < M) {
        Edjes next = e[edj_idx++];
        int x = find(s, next.u);
        int y = find(s, next.v);

        if (x != y) {
            edjes_MST[res_idx++] = next;
            Union(s, x, y);
        }

    }

    // construct adjacency list for MST    
    for (int i = 0; i < res_idx; i++){
        adjList_MST[edjes_MST[i].u].push_back(make_pair(edjes_MST[i].v, edjes_MST[i].w));
        adjList_MST[edjes_MST[i].v].push_back(make_pair(edjes_MST[i].u, edjes_MST[i].w));
    }
}

void numberOfNodesInSubtree(int s, int e) 
{ 
    list<pair<int, int> >::iterator it; 
    nodesInSubtree[s] = 1; 
    for (it = adjList_MST[s].begin(); it != adjList_MST[s].end(); it++) { 
          
        if (it -> first == e) continue; 
          
        numberOfNodesInSubtree(it -> first, s); 
        nodesInSubtree[s] += nodesInSubtree[it -> first]; 
    } 
} 

int main(int argc, char **argv){
    
    ifstream infile("distances/input11.txt");

    int u, v, w, j;

    infile >> N >> M;

    // read edjes and place them in an array of Edjes
    for (int i = 0; i < M; i++){
        infile >> u >> v >> w;
        e[i].u = u;
        e[i].v = v;
        e[i].w = w;
    }

    // sort array of Edjes to run Kruskal's Algorithm
    sort(e, e + M, ascWidth);

    KruskalMST();

    // find the number of nodes that belong in all subtrees of 
    // the tree that Kruskal returned
    numberOfNodesInSubtree(1, 0);

    // fill appearances array with the number of appearances of each edje in
    // shortest paths. 
    for (int i = 0; i < N - 1; i++) {
        u = edjes_MST[i].u;
        v = edjes_MST[i].v;
        w = edjes_MST[i].w;

        appearances[w] = (N - min(nodesInSubtree[u],nodesInSubtree[v]))*min(nodesInSubtree[u],nodesInSubtree[v]);
    }

    // create binary format for solution
    for (int i = 0; i < 2 * M; i++) {
        int mod = appearances[i] % 2;
        int div = appearances[i] / 2;
        appearances[i] = mod;
        appearances[i + 1] += div;
    }
    
    // cut extra zeros in front
    for (j = 2 * M; j > 0; --j) {
        if (appearances[j] == 0 && appearances[j - 1] == 0) continue;
        else break;
    }

    // print the result
    for (int i = --j; i >= 0; i--) cout << appearances[i];

    cout << endl;

}