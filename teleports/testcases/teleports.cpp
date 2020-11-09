#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

struct universes {
	int morty;		// where morty is in each universe
	int parent;		// parent attribute to be used for union find
	int rank;		// added rank in order to be used for optimization of union find
};

struct portals {
	int src;
	int dest;
	int width;
};

/*GLOBAL DECLARATIONS*/
#define MAX	1000003
universes u[MAX];
portals p[MAX];
long N, M;
/*END OF GLOBAL DECLARATIONS*/

bool decreasingWidth(portals p1,portals p2){ 
	return (p1.width > p2.width); 
}

int find(int i) 
{  
    if (u[i].parent != i) 
        u[i].parent = find(u[i].parent); 
  
    return u[i].parent; 
} 
  
void Union(int x, int y) 
{ 
    int xroot = find(x); 
    int yroot = find(y); 
  
    if (u[xroot].rank < u[yroot].rank) 
        u[xroot].parent = yroot; 
    else if (u[xroot].rank > u[yroot].rank) 
        u[yroot].parent = xroot; 
  
    else
    { 
        u[yroot].parent = xroot; 
        u[xroot].rank++; 
    } 
} 

bool completed(){
	for(int i = 1; i <= N; i++)
		if(!(find(i) == find(u[i].morty)))
			return false;
			
	return true;
}

int main(){
	
	int i = 0;
	
	ifstream infile("input21.txt");
	
	infile >> N >> M;
	
	u[0].morty = 0;
	u[0].parent = 0;
	
	for(int i = 1; i <= N; i++){
		infile >> u[i].morty;
		u[i].parent = i;
		u[i].rank = 0;
	}
	
	for(int i = 0; i < M; i++)
		infile >> p[i].src >> p[i].dest >> p[i].width;
		
	sort(p, p + M, decreasingWidth);
	
	while(!completed()){
		// if portal.source and portal.destination have different parents then we 
		if(find(p[i].src) != find(p[i].dest))
			Union(p[i].src, p[i].dest);
		
		i++;	
	}
	
	cout << p[--i].width << endl;
}
