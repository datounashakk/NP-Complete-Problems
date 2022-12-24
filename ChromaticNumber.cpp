//implementing the chromatic number algorithm using the greedy algorithm and the backtracking algorithm 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

//reading in the file and setting up the graph
//first line in the file has number of vertices and edges
//the rest of the lines have the edges(which vertices are connected)
void readInFile(string fileName, int &numVertices, int &numEdges, vector<vector<int> > &myGraph){
    ifstream file(fileName);
    string line;
    int lineNum = 0;
    while (getline(file, line))
    {
        if (lineNum == 0)
        {
            stringstream ss(line);
            ss >> numVertices;
            ss >> numEdges;
            myGraph.resize(numVertices);
        }
        else
        {
            stringstream ss(line);
            int vertexA;
            int vertexB;
            ss >> vertexA;
            ss >> vertexB;
            myGraph[vertexA].push_back(vertexB);
            myGraph[vertexB].push_back(vertexA);
        }
        lineNum++;
    }
}

//printing out the graph
void printGraph(vector<vector<int> > myGraph){
    for (int i = 0; i < myGraph.size(); i++)
    {
        cout << i << ": ";
        for (int j = 0; j < myGraph[i].size(); j++)
        {
            cout << myGraph[i][j] << " ";
        }
        cout << endl;
    }
}


int chromaticNumber (vector<vector<int> > my_graph, vector<vector<bool> > &color_assignment, vector<bool>& assigned_or_not){
    // LOOP THROUGH ALL THE VERTICES
    // LOOK AT NEIGHBORING VERTICES
    // IF THE NEIGHBORING VERTICES ARE NOT ASSIGNED, ASSIGN CURRENT VERTEX TO THE FIRST AVAILABLE COLOR
    // IF THE NEIGHBORING VERTICES ARE ASSIGNED, CHECK THE FIRST AVAILABLE COLOR THAT IS NOT ASSIGNED TO ANY OF THE NEIGHBORING VERTICES AND ASSIGN IT TO THE CURRENT VERTEX
    int chromaticNumber = 0;
    for (int i = 0; i<my_graph.size(); i++){
            //extract the vector of the neighboring vertices
            vector<int> neighbors = my_graph[i];
            //get the vector of the neighboring vertices that are assigned
            vector<int> assigned_neighbors; 
            for (int k = 0; k<neighbors.size(); k++){
                if (assigned_or_not[neighbors[k]] == true){
                    assigned_neighbors.push_back(neighbors[k]);
                }
            }
            
            //if the neighboring vertices are not assigned, assign the current vertex to the first available color
            if (assigned_neighbors.size() == 0){
                color_assignment[i][0] = true;
                assigned_or_not[i] = true;
                if (chromaticNumber == 0){
                    chromaticNumber = 1;
                }
                //cout << "vertex " << i << " is assigned to color 0" << endl;
            }
            //if the neighboring vertices are assigned, check the first available color that is not assigned to any of the neighboring vertices and assign it to the current vertex
            else{
                int count = 0;
                int goalCount = assigned_neighbors.size();
                // if color_assignment[0][0] == color_assignment[2][0] == color_assignment[3][0] == true
                // then count = 3
                // if count == goalCount, then all the colors are assigned to the neighboring vertices  
                int c = 0;
                    while(count < goalCount && c < color_assignment.size()){
                        
                        for (int l = 0; l<assigned_neighbors.size(); l++){
                            if (color_assignment[assigned_neighbors[l]][c] == false){
                                count++;
                            }
                        }
                        
                        if (count == goalCount){
                            color_assignment[i][c] = true;
                            assigned_or_not[i] = true;
                            if (chromaticNumber < c+1){
                                chromaticNumber = c+1;
                            }
                            //cout << "vertex " << i << " is assigned to color " << c << endl;
                        }
                        else{
                            count = 0;
                        }
                        c++;
                        
                    }
            }

    }
return chromaticNumber;
}

int main(){

vector<string> filenames;
ifstream fin("fileNames.txt");
string line;
while (getline(fin, line)){
stringstream ss(line);
ss >> line;
filenames.push_back(line);
}
fin.close();

string fileName;
int k = 0; 
while (k < filenames.size()){



    int numVertices;
    int numEdges;
    vector<vector<int> > myGraph;
    readInFile("gc_" + filenames[k], numVertices, numEdges, myGraph);
    //printGraph(myGraph);


vector<bool> assignedOrNot;
assignedOrNot.resize(numVertices, false);

vector<vector<bool> > colorAssignment;
colorAssignment.resize(numVertices);
for (int i = 0; i < numVertices; i++)
{
    colorAssignment[i].resize(numVertices, false);
}

vector<int> colorsAssigned;
colorsAssigned.resize(numVertices, -1);

int chromaticNum = chromaticNumber(myGraph, colorAssignment, assignedOrNot);

/*
//print colorAssignment vector
for (int i = 0; i < colorAssignment.size(); i++)
{
    for (int j = 0; j < colorAssignment[i].size(); j++)
    {
        cout << colorAssignment[i][j] << " ";
    }
    cout << endl;
}
*/

//create a vector of the colors assigned to each vertex
for (int i = 0; i < colorAssignment.size(); i++)
{
    for (int j = 0; j < colorAssignment[i].size(); j++)
    {
        if (colorAssignment[i][j] == true)
        {
            colorsAssigned[i] = j;
        }
    }
}


cout << chromaticNum << endl;

//print the colors assigned to each vertex
for (int i = 0; i < colorsAssigned.size(); i++)
{
    cout << colorsAssigned[i] << " ";
}

        //save output to a file
        ofstream fout;
        string outputFileName = "gc_"+filenames[k] + "_output";
        fout.open(outputFileName);
        fout << chromaticNum << endl;

        //print the colors assigned to each vertex
        for (int i = 0; i < colorsAssigned.size(); i++){
        fout << colorsAssigned[i] << " ";
        }
        fout.close();



k++;
}

return 0;
}
