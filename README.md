# Algorithms and Complexity - NTUA

This repo has all the exercises given in this course. Problem definitions can be found by clicking the name of the problem (Greek).

# Problems
### _[roadtrip2](https://github.com/BeenCoding/Algo-NTUA/blob/main/lab01.pdf)_ ([C++ Solution](https://github.com/BeenCoding/Algo-NTUA/blob/main/roadtrip2/roadtrip2.cpp))
* In this problem the following form of input is given:
  * N,K,D,T - Where N is the number of cars, K the number of stations, D the distance we want to cover, T the time we need to cover the distance.
  * We need to find the cheapest car that can do this distance D in time(less than or equal to T). 
* **SOLUTION:** 
  * First sort station and car arrays. Create a distance array with i<sub>th</sub> element as stations[j+1] - stations[j].
  * Then find the biggest subdistance between two stations(longestSubdistance).
  * Each car to cover this distance must have at least Cs multiplied by longestSubdistance capacity, or at most Cf multiplied by longestSubdistance.
  * So these two numbers are the boundaries that we need in order to to a binary search and find the Ci<sub>min</sub> that a car needs to travel to the destination.
  * When Ci<sub>min</sub> found, check if it can reach the destination. If not then print -1, else find the first car with Ci ≥ Ci<sub>min</sub> and print it.
