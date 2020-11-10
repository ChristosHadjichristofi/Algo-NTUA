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

bool completed(){
	for(int i = 1; i <= N; i++)
		if(!(find(i) == find(u[i].morty)))
			return false;
			
	return true;
}

int main(){
	
	int i = 0;
	
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
	
	// sort portals array by width in descending order because we want to use only
	// the widest portals to reach our final state(each morty in its universe).	
	sort(p, p + M, decreasingWidth);
	
	// while we havent reached our final state, we try to add a new portal(edge).
	// the only way to add this portal(edge) is that it doesnt create a circle, so use find
	// to check if portal a and portal b have the same parent. If not union.
	while(!completed()){
		if(find(p[i].a) != find(p[i].b))
			Union(p[i].a, p[i].b);
		
		i++;	
	}
	
	cout << p[--i].width << endl;
}
