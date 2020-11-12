# Algorithms and Complexity - NTUA

This repo has all the exercises given in this course. Problem definitions can be found by clicking the name of the problem (Greek).

### _[roadtrip2](https://github.com/BeenCoding/Algo-NTUA/blob/main/lab01.pdf)_ ([C++ Solution](https://github.com/BeenCoding/Algo-NTUA/blob/main/roadtrip2/roadtrip2.cpp))
We need to find the cheapest car that can do this distance D in time(less than or equal to T). Each car has two modes, eco and sport. Each mode has its own time and capacity needed to cover 1km.
* In this problem the following form of input is given:
  * N,K,D,T - Where N is the number of cars, K the number of stations, D the distance we want to cover, T the time we need to cover the distance.
  * N pairs of P<sub>i</sub>, C<sub>i</sub>.
  * K numbers which are the in between stations.
  * T<sub>s</sub>, C<sub>s</sub>, T<sub>f</sub>, C<sub>f</sub>, which are time-capacity for eco mode, time-capacity for sport mode respectively.
 
* **SOLUTION:** 
  * First sort station and car arrays. Create a distance array with i<sub>th</sub> element as stations[j+1] - stations[j].
  * Then find the biggest subdistance between two stations(longestSubdistance).
  * Each car to cover this distance must have at least Cs multiplied by longestSubdistance capacity, or at most Cf multiplied by longestSubdistance.
  * So these two numbers are the boundaries that we need in order to to a binary search and find the Ci<sub>min</sub> that a car needs to travel to the destination.
  * When Ci<sub>min</sub> found, check if it can reach the destination. If not then print -1, else find the first car with Ci ≥ Ci<sub>min</sub> and print it.
  
### _[teleports](https://github.com/BeenCoding/Algo-NTUA/blob/main/lab01.pdf)_ ([C++ Solution](https://github.com/BeenCoding/Algo-NTUA/blob/main/teleports/teleports-opt.cpp))
We need the maximum width of the narrowest portal that will be used so as each Morty go back to the Universe he belongs.
* In this problem the following form of input is given:
  * N,M - Where N is the number of Universes, M the number of portals.
  * The permutation c = (c<sub>1</sub>,...,c<sub>N</sub>), where c<sub>i</sub> shows the parallel universe that Morty of i<sub>th</sub> universe is.
  * K triplets of numbers a<sub>j</sub>, b<sub>j</sub>, w<sub>j</sub>, where a is the portal in one universe, b is the portal to the other universe and w is the width of the portal.

We think the problem as a graph problem. Universes are the nodes and portals are the edges. We want to create a final state where nodes are divided in coherent trees(one or more), so as each Morty at i<sub>th</sub> universe reach its own universe.

* **SOLUTION:** 
  * Union find with ranking and path compression will be used. Sort portals by width in descending order because we want to use only the widest portals to reach the final state.
  * Every time we check if we reached the final state, using find(). We check for every element of the permutation given that Morty which is at universe i and universe i have the same ancestor. If every Morty of the permutation has the same ancestor with universe i (which he now is), then we reached our final state and the coherent tree/trees was/were constructed.
  * While we haven't reached the final state we continue to add edges(which are the portlas) to the graph. We get the i<sub>th</sub> triplet of portals and try to add the edge universeA - universeB. We want to add this edge only if portal a and portal b doesn't have the same ancestor.
