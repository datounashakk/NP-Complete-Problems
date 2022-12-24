#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "item.h"
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdlib>


using namespace std;

// Reads in the vector of strings that is actually vector of lines from the file.
// Then it parses the line and creates an item object and sets the profit, weight and original position. 
vector<Item> setItemsUp(ifstream &file, int numItems){
    vector<Item> myItems;
        for (int i = 1; i <= numItems; i++){
            Item curItem;
            int curProfit;
            int ss;
            file >> ss;
            curProfit = ss;
            file >> ss;
            int curWeight;
            curWeight = ss;
            curItem.setProfit(curProfit);
            curItem.setWeight(curWeight);
            curItem.setOriginalPos(i);
            myItems.push_back(curItem);
        }
    return myItems;
}   


//sort items by profit/weight ratio in descending order
vector<Item> sortItems(vector<Item> myItems){
    for (int i = 0; i < myItems.size(); i++){
        for (int j = i + 1; j < myItems.size(); j++){
            if ((myItems[i].getProfit() / myItems[i].getWeight()) < (myItems[j].getProfit() / myItems[j].getWeight())){
                Item temp = myItems[i];
                myItems[i] = myItems[j];
                myItems[j] = temp;
            }
        }
    }
return myItems;
}




//max profit function that takes vector of items, i, starting weight, capacity, and memoization table
int maxProfit(vector<Item> myItems, int i, int startingWeight, int capacity, vector<vector<int> > &memo, int timeCounter){
    //base case
    if (timeCounter == 1000000){
       return memo[i][startingWeight];
        return 0;
    }
    if (i == myItems.size()){
        timeCounter++;
        return 0;
        
    }
    //if the value is already in the memoization table, return it
    if (memo[i][startingWeight] != -1){
        timeCounter++;
        return memo[i][startingWeight];
    }
    //if the weight of the item is greater than the remaining capacity, return the max profit of the next item
    if (myItems[i].getWeight() > capacity){
    
        return maxProfit(myItems, i + 1, startingWeight, capacity, memo, timeCounter+1);
    }
    //if the weight of the item is less than the capacity, return the max of the next item or the profit of the current item plus the max profit of the next item
    else{
        timeCounter++;
        memo[i][startingWeight] = max(maxProfit(myItems, i + 1, startingWeight, capacity, memo, timeCounter+1), myItems[i].getProfit() + maxProfit(myItems, i + 1, startingWeight + myItems[i].getWeight(), capacity - myItems[i].getWeight(), memo, timeCounter+1));
        return memo[i][startingWeight];
    }
}



int main (){

    //Read in the file
    string fileName = "ks_40_0.txt";
    ifstream file;
    file.open(fileName);
    

    if(file.fail()){
        cout << "Error opening file" << endl;
        exit(1);
    }
   
   int ss;
   file >> ss;
   int item_number;
   item_number = ss;
   file >> ss;
   int capacity;
   capacity = ss;


vector<Item> myItems = setItemsUp(file, item_number);
myItems = sortItems(myItems);

//initialize memoization table
vector<vector<int> > memo(item_number, vector<int>(capacity + 1, -1));


int maxProfitValue = maxProfit(myItems, 0, 0, capacity, memo, 0);
//cout << maxProfitValue << endl;



// determine how to decide which items to take depending on the memoization table
vector<Item> itemsTaken;
// start at the first item
int i = 0;
// start at the first weight
int j = 0;
// while you are not at the last item
while (i < myItems.size() - 1){
    // if the current item is the same as the next item, then you did not take the current item
    if (memo[i][j] == memo[i + 1][j]){
        i++;
    }
    // if the current item is not the same as the next item, then you took the current item
    else{
        itemsTaken.push_back(myItems[i]);
        j = j + myItems[i].getWeight();
        i++;
    }
}
// if the last item is not the same as the previous item, then you took the last item
if (memo[i][j] != memo[i - 1][j]){
    itemsTaken.push_back(myItems[i]);
}

// save the output to a file
ofstream myfile;
myfile.open("ks_39_0_output");
myfile << maxProfitValue << endl;

for (int i = 0; i < myItems.size(); i++){
    int found = 0;
    for (int j = 0; j < itemsTaken.size(); j++){
        if (myItems[i].getOriginalPos() == itemsTaken[j].getOriginalPos()){
            myfile << "1 ";
            found = 1;
        }
    }
    if (found == 0){
        myfile << "0 ";
    }
}

myfile.close();


return 0;
}