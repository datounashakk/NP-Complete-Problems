#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>

using namespace std;

//Read in file for traveling salesman problem
vector<vector<double> > readInFile(int& numCities, string fileName){
    vector<vector<double> > cities;
    ifstream file(fileName.c_str());
    string line;
    if(file.is_open()){
        getline(file, line);
        numCities = atoi(line.c_str());
        for(int i = 0; i < numCities; i++){
            vector<double> city;
            getline(file, line);
            stringstream ss(line);
            string x;
            string y;
            getline(ss, x, ' ');
            getline(ss, y, ' ');
            city.push_back(atof(x.c_str()));
            city.push_back(atof(y.c_str()));
            cities.push_back(city);
        }
    }
    return cities;
}


//Prints out the cities in the vector of vectors of doubles
void printCities(vector<vector<double> > cities){
    for(int i = 0; i < cities.size(); i++){
        cout << cities[i][0] << " " << cities[i][1] << endl;
    }
}


vector<int> travelingSalesmanGreedy(vector<vector<double> > cities, double& totalDistance, int& startCity){
//find the distance between every pair of cities
//store the distances in a vector of vectors of doubles
vector<vector<double> > distances;
for(int i = 0; i < cities.size(); i++){
    vector<double> distance;
    for(int j = 0; j < cities.size(); j++){
        double x = cities[i][0] - cities[j][0];
        double y = cities[i][1] - cities[j][1];
        double d = sqrt(x*x + y*y);
        distance.push_back(d);
    }
    distances.push_back(distance);
}

//starting from whatever city, visit the next city that is closest to the current city
//then mark the city as visited
//repeat until all cities have been visited
//return the path and the total distance
totalDistance = 0;
vector<int> path;
vector<bool> visited;
for(int i = 0; i < cities.size(); i++){
    visited.push_back(false);
}

//randomize the starting city
//srand(time(NULL));


//choose the starting city as the city with the lowest cost to get to all other cities
double minDistance = 1000000;
for(int i = 0; i < cities.size(); i++){
    double distance = 0;
    for(int j = 0; j < cities.size(); j++){
        distance += distances[i][j];
    }
    if(distance < minDistance){
        minDistance = distance;
        startCity = i;
    }
}

visited[startCity] = true;
path.push_back(startCity);
int currentCity = startCity;
for(int i = 0; i < cities.size() - 1; i++){
    double minDistance = 1000000;
    int nextCity = 0;
    for(int j = 0; j < cities.size(); j++){
        if(!visited[j] && distances[currentCity][j] < minDistance){
            minDistance = distances[currentCity][j];
            nextCity = j;
        }
    }
    path.push_back(nextCity);
    visited[nextCity] = true;
    currentCity = nextCity;
    totalDistance += minDistance;
}
totalDistance += distances[currentCity][startCity];
return path;
}

//Prints out the path
void printPath(vector<int> path){
    for(int i = 0; i < path.size(); i++){
        cout << path[i] << " ";
    }
    cout << endl;
}


int main(){

    int numCities;
    vector<string> filenames;
    ifstream fin("fileNames2.txt");
    string line;
    while (getline(fin, line)){
        stringstream ss(line);
        ss >> line;
        filenames.push_back(line);
    }
    fin.close();

    //display vector of filenames   
    //for(int i = 0; i < filenames.size(); i++){
    //    cout << filenames[i] << endl;
    //}


//int k = 0; 
//while (k < filenames.size()){
//string fileName = filenames[k];  
string fileName = "tsp_33810_1";
    vector<vector<double> > cities = readInFile(numCities, fileName);
    
    

    //sort all cities to then select the starting city as the city with the lowest cost 
    //to get to all other cities
    //sort the cities by x coordinate
    for(int i = 0; i < cities.size(); i++){
        for(int j = i + 1; j < cities.size(); j++){
            if(cities[i][0] > cities[j][0]){
                vector<double> temp = cities[i];
                cities[i] = cities[j];
                cities[j] = temp;
            }
        }
    }
    //sort the cities by y coordinate
    for(int i = 0; i < cities.size(); i++){
        for(int j = i + 1; j < cities.size(); j++){
            if(cities[i][1] > cities[j][1]){
                vector<double> temp = cities[i];
                cities[i] = cities[j];
                cities[j] = temp;
            }
        }
    }
    //print out the cities
    //printCities(cities);
    //cout << endl;

    double totalDistance = 0;
    int startCity = 0;
    vector<int> path = travelingSalesmanGreedy(cities, totalDistance, startCity);
    //save the output to a file 
    ofstream file(fileName + "_output");
    if(file.is_open()){
        file << totalDistance << " " << startCity << endl;
        for(int i = 0; i < path.size(); i++){
            file << path[i] << " ";
        }
        file << endl;
    }
    //cout << totalDistance <<  " " << startCity << endl;        
    //printPath(path);

//k++;
//}

return 0;
}
