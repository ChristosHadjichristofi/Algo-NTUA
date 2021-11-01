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
  
### _[teleports](https://github.com/BeenCoding/Algo-NTUA/blob/main/lab01.pdf)_
We need the maximum width of the narrowest portal that will be used so as each Morty go back to the Universe he belongs.
* In this problem the following form of input is given:
  * N,M - Where N is the number of Universes, M the number of portals.
  * The permutation c = (c<sub>1</sub>,...,c<sub>N</sub>), where c<sub>i</sub> shows the parallel universe that Morty of i<sub>th</sub> universe is.
  * K triplets of numbers a<sub>j</sub>, b<sub>j</sub>, w<sub>j</sub>, where a is the portal in one universe, b is the portal to the other universe and w is the width of the portal.

We think the problem as a graph problem. Universes are the nodes and portals are the edges. We want to create a final state where nodes are divided in coherent trees(one or more), so as each Morty at i<sub>th</sub> universe reach its own universe.

* **[SOLUTION - ONLY WITH UNION FIND:](https://github.com/BeenCoding/Algo-NTUA/blob/main/teleports/teleports.cpp)** 
  * Union find with ranking and path compression will be used. Sort portals by width in descending order because we want to use only the widest portals to reach the final state.
  * Every time we check if we reached the final state, using find(). We check for every element of the permutation given that Morty which is at universe i and universe i have the same ancestor. If every Morty of the permutation has the same ancestor with universe i (which he now is), then we reached our final state and the coherent tree/trees was/were constructed.
  * While we haven't reached the final state we continue to add edges(which are the portlas) to the graph. We get the i<sub>th</sub> triplet of portals and try to add the edge universeA - universeB. We want to add this edge only if portal a and portal b doesn't have the same ancestor.

* **[SOLUTION - BINARY SEARCH WITH UNION FIND:](https://github.com/BeenCoding/Algo-NTUA/blob/main/teleports/teleports-opt.cpp)**
  * Sort the portals by width in ascending order. Start a binary search from 0 to M.
  * Every time use middle of lower and upper to find the first portal we're going to use. Using that portal till the upper bound construct the union. If that union can reach final state, then initialize again the parent and rank attributes and keep searching on the (middle+1,M). If union cant reach final state, then leave the union as is and continue searching on the (lower,middle). Do this until lower == upper.

### _[chem](https://github.com/ChristosHadjichristofi/Algo-NTUA/blob/main/lab02.pdf)_ ([C++ Solution](https://github.com/ChristosHadjichristofi/Algo-NTUA/blob/main/chem/chem.cpp))
There are N chemical substances and we need to store them into K metal bottles. The substances are labeled from 1 to N and for safety reasons, the substances need to be stored with the right order. Each chemical substance needs to be stored in only one bottle (You can not store half of the chemical substance in one bottle and the other half in an other). Each metal bottle has enough capacity so as all the substances can be stored inside. 
However, there is a risk of a chemical reaction between the substances in the same bottle, at which time significant amounts of energy are attracted. Specifically for each pair (i, j) of substances in the same bottle, the chemical reaction between them produces energy equal to A[i, j] units.

* **SOLUTION:** 
  * Read the input and store them in an array named reactions.
  * Calculate the total costs when i to j substances exist in the same metal bottle. This is done so as in the next step I can have the total costs without the need to calculate anything.
  * This problem is solved with dynamic programming. The reccurance relation that is used to fill the dp array is: <br /> ```dp[i][j] = dp[x][j-1] + reactions[x][i-1], 2 ≤ i ≤ N, xStart ≤ x < i``` <br /> Every time we find a value that can be placed in dp[i][j] we need to save x in xStart, so as in next iteration we check only the necessary previous values.
  * Print the solution from ```DP[N][K]```.

### _[bazaar](https://github.com/ChristosHadjichristofi/Algo-NTUA/blob/main/lab02.pdf)_ ([C++ Solution](https://github.com/ChristosHadjichristofi/Algo-NTUA/blob/main/bazaar/bazaar.cpp))
The goal is to be able to buy N sets of equipment from the bazaar. The equipment is the set of armor, shield, sword. The armor is denoted by A, the sword by B and the shield by C. There are three dealers who sell this equipment (Denoted by numbers 1, 2 and 3 respectively). Each merchant can sell one or more items of any type.
Items sold by different merchants are not compatible and we can not complete a set from another merchant. Each set must be purchased exclusively from a dealer.
Each trader at the beginning of the bazaar, announces his offers, ie how many items of each type he sells and at what price. Usually the trader sells many different (foreign to each other) sets of the same item at a different price (eg trader 1 can sell 3 armors (1A) at a price of 100 and other 4 armors at a price of 800). The items mentioned in the offers are necessarily sold all together as a single. Finally, the minimum amount needed to purchase N total sets of equipment must be calculated.

* **SOLUTION:** 
  * Read the input and based on who is the trader and what item he sells, save in the corresponding vector. Totally exist 9 vectors that save pairs (quantity, price).
  * For every trader, execute knapsack for items A, B, C and combine them in a complete set for that trader.
    * The knapsack logic is implemented with a function that fills an array with knapsack logic. At first the array is filled with MAX_INT. Every time we get an element from costs vector, add currentQuantity to totalQuantity. If totalQuantity is more than N, then set j to N, else to totalQuantity. This is done so as we know how many items we have at that time. The reccurance relationship: <br/> ```dp[j] = min_{min(N, totalQuantity) >= j >= 1}(dp[j], dp[max(j - currentQuantity), 0] + currentPrice)```
  * When the previous step is completed, create all possible combinations from the 3 traders so as we get exactly N sets.


### _[distances](https://github.com/ChristosHadjichristofi/Algo-NTUA/blob/main/lab02.pdf)_ ([C++ Solution](https://github.com/ChristosHadjichristofi/Algo-NTUA/blob/main/distances/distances.cpp))
_TODO: Explain exercise and solution_
