#include <iostream>
#include <algorithm>

using namespace std;

struct universes {
	int morty;		// where morty is in each universe
	int parent;		// parent attribute to be used for union find
	int rank;		// added rank in order to be used for optimization of union find
};

struct portals {
	int a;
	int b;
	int width;
};

/*GLOBAL DECLARATIONS*/
#define MAX	1000003
universes u[MAX];
portals p[MAX];
long N, M;
/*END OF GLOBAL DECLARATIONS*/

bool ascWidth(portals p1,portals p2){ 
	return (p1.width < p2.width); 
}

int find(int i) 
{  
	if (u[i].parent != i) 
		u[i].parent = find(u[i].parent); 

	return u[i].parent; 
}

void Union(int x, int y) 
{
	int rx = find(x); 
	int ry = find(y); 

	if (rx != ry){
		if(u[rx].rank < u[ry].rank){
			u[rx].parent = ry;
			++u[rx].rank;
		}
		else{
			u[ry].parent = rx;
			++u[ry].rank;
		}
	}
}

// Checks if the state is final. The only state that is final is 
// when each morty can reach his world, using any combination of 
// the nodes that are a part of that specific connected tree.
bool completed(){
	for(int i = 1; i <= N; i++)
		if(!(find(i) == find(u[i].morty)))
			return false;
			
	return true;
}

// binary search through the portals.
// calculate every time the middle, and construct every time the union.
// when a union that is constructed reaches final state we're not sure
// if the nodes that constructed this union are all necessary. So we continue
// the binary search until it returns a value.
int binarySearch(int lower, int upper){

	if(lower == upper)
		return upper;

	int middle = lower + (upper - lower)/2;
	for(int i = middle; i <= upper; i++){
		if(find(p[i].a) != find(p[i].b))
			Union(p[i].a, p[i].b);
	}
	// As said if completed we're not sure if all nodes that constructed this 
	// union are necessary, so initialize parent and rank for all nodes, and 
	// search an answer on the upper part of the array.
	if(completed()){
		for(int i = 1; i <= N; i++){
			u[i].parent = i;
			u[i].rank = 0;
		}
		return binarySearch(middle+1, M);
	}
	// If not completed then we cant even reach the final state so we need
	// to use more nodes to construct the union.
	else
		return binarySearch(lower, middle);
}

int main(){

	int ans = 0;

	cin >> N >> M;

	u[0].morty = 0;
	u[0].parent = 0;

	for(int i = 1; i <= N; i++){
		cin >> u[i].morty;
		u[i].parent = i;
		u[i].rank = 0;
	}

	for(int i = 0; i < M; i++)
		cin >> p[i].a >> p[i].b >> p[i].width;

	// sort portals array by width in ascending in order to perform binary search.
	sort(p, p + M, ascWidth);

	ans = binarySearch(0,M);

	cout << p[--ans].width << endl;
}
