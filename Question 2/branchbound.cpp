// C++ program to solve knapsack problem using 
// branch and bound 
#include <bits/stdc++.h> 
using namespace std; 
  
struct Item 
{ 
    float weight; 
    int value; 
}; 
  
/*We use this node structure to store information of decision 
tree */
struct Node 
{ 
    int level, profit, bound; 
    float weight; 
}; 
  
// Comparison function to sort Item
bool cmp(Item a, Item b) 
{ 
    double r1 = (double)a.value / a.weight; 
    double r2 = (double)b.value / b.weight; 
    return r1 > r2; 
} 
   
int bound(Node u, int n, int W, Item arr[]) 
{ 
    // if weight overcomes the knapsack capacity, return 
    // 0 as expected bound 
    if (u.weight >= W) 
        return 0; 
  
    int profit_bound = u.profit; 
  
    // start including items from index 1 more to current 
    // item index 
    int j = u.level + 1; 
    int totweight = u.weight; 
  
    while ((j < n) && (totweight + arr[j].weight <= W)) 
    { 
        totweight    += arr[j].weight; 
        profit_bound += arr[j].value; 
        j++; 
    } 
  
    // If k is not n, include last item partially for 
    // upper bound on profit 
    if (j < n) 
        profit_bound += (W - totweight) * arr[j].value / 
                                         arr[j].weight; 
  
    return profit_bound; 
} 
  
int knapsack(int W, Item arr[], int n) 
{ 
    // sorting Item on basis of value per unit 
    // weight. 
    sort(arr, arr + n, cmp); 
  
    // make a queue for traversing the node 
    queue<Node> Q; 
    Node u, v; 
  
    u.level = -1; 
    u.profit = u.weight = 0; 
    Q.push(u); 
  
    /*One by one extract an item from decision tree 
    *compute profit of all children of extracted item 
    *and keep saving maxProfit */
    int maxProfit = 0; 
    while (!Q.empty()) 
    { 
        // Dequeue a node 
        u = Q.front(); 
        Q.pop(); 
  
        // If it's starting node, assign level 0 
        if (u.level == -1) 
            v.level = 0; 
  
        //If there is nothing on next level 
        if (u.level == n-1) 
            continue; 
   
        v.level = u.level + 1; 
  
        //Taking current level's item add current 
        //level's weight and value to node u's 
        //weight and value 
        v.weight = u.weight + arr[v.level].weight; 
        v.profit = u.profit + arr[v.level].value; 
  
        if (v.weight <= W && v.profit > maxProfit) 
            maxProfit = v.profit; 
   
        v.bound = bound(v, n, W, arr); 
  
        if (v.bound > maxProfit) 
            Q.push(v); 
  
        v.weight = u.weight; 
        v.profit = u.profit; 
        v.bound = bound(v, n, W, arr); 
        if (v.bound > maxProfit) 
            Q.push(v); 
    } 
  
    return maxProfit; 
} 
  
//program to test 
int main() 
{ 
    int W = 50;   // Weight of knapsack 
    Item arr[] = {{10, 60}, {20, 100}, {30, 120}}; 
    int n = sizeof(arr) / sizeof(arr[0]); 
  
    cout << "Maximum possible value = "
         << knapsack(W, arr, n);

    cout << endl;
  
    system("pause");
    cout << endl;
    return 0; 
} 