/*
Purpose: The purpose of this assignment to calculate the shortest path from YYC to various airports in Canada
Details: Reads from map.txt and stores the file into an adjacency array. The adjacency array is then passed into 
         Dijkstas algorithm and the shortest path from YYC is computed
Limitations and assumption: Can only start from YYC and only works for the cities hard coded
                            Assumes the map.txt is properly formatted and file exist in the same directory
Known bugs: None
**DIJKSTRAS ALGORITHM WAS TAKEN FROM https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/?ref=lbp
    dijkstra()
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
 
#define V 21
#define EDGES 78
#define MAX 99999

//Struct to hold information about the edges
struct Edge
{
    string  source;
    string  destination;
    int time;
};

string CITY[V]= { "YYC", "YEG", "YQR", "YXE", "YVR", "YWG", "YYZ", "YUL", "YYJ", "YOW"
                , "YQB", "YHZ", "YQM", "YFC", "YQX", "YYT", "YXY", "YZF", "YFB", "YXX"
                , "YXS" };
//Adjacency list
int adjGraph[V][V];

//Vector to hold all the edges
vector<Edge> edges;

/*
Function: printPath
Purpose: To print the paths
Method: Iterates through the array and adds the city to the front of the string to print the path
Input: Int array holding the paths and the current index of the vertex being printed
Output: void
*/
void printPath(int path[], int j)
{   
    string pathSTR;
    cout << CITY[0];
    while(path[j] > -1)
    {
        pathSTR = " -> " + CITY[j] + pathSTR;
        j = path[j];
    }
    cout << pathSTR;
}

/*
Function: printSolution
Purpose: This will print out the needed information
Method: Function will iterate through each vertex and print out its distance and corresponding path
Input: The array holding all the distances and an array holding all the paths
Output: void
*/
void printSolution(int time[], int path[])
{
    int i = 0;
    cout <<"\nDestination \tTime from " << CITY[0] << "\t Path " << endl;
    for (i = 0; i < V-1; i+=2)
    {
        cout  << CITY[i] << " \t\t" << time[i] << "\t\t ";
        printPath(path,i);
        cout << endl;
        cout  << CITY[i+1] << " \t\t" << time[i+1] << "\t\t ";
        printPath(path,i+1);
        cout << endl;
    }
    if(i == V-1)
    {
        cout  << CITY[i] << " \t\t" << time[i] << "\t\t ";
        printPath(path,i);
        cout << endl;
    }
}

/*
Function: fillAdjMatrix
Purpose: To fill an adjacency matrix 
Method: It will iterated through all the x and y componenets of the 2d array and fills it up with the corresponding time.
        The function will check all the edges to see if the edge exist between two cities and if it does, it will take the
        time for that city and inputs it into the correct index of the array. If the edge does not exist, it will put 0 into
        the array
Input: None
Output: void
*/
void fillAdjMatrix() 
{
    int time = 0; 
    for (int i = 0 ; i< V ; i++) 
    {
        for (int j = 0 ; j < V ; j++) 
        {   
            for (int x = 0; x < EDGES; x++)
            {
                Edge currEdge = edges[x];
                if(CITY[i] == currEdge.source && CITY[j] == currEdge.destination)
                {
                    time = currEdge.time;
                    break;
                }
            }
            if (time > 0)
            {
                adjGraph[i][j] = time;
                time = 0;
            }
            else
            {
                adjGraph[i][j] = 0;
            }
        }
    }
}

/*
Function: readInput
Purpose: Reads a file
Method: The function will read a file line by line and push the fields into the struct Edge.
        The function will push the two times with src being one of the times and dst being the other so
        the edges can be a two directional directed edge
Input: The file 
Output: void
*/
void readInput(ifstream &file) 
{
    string line;
    string src;
    string dst;
    int time;

     while(getline(file,line))
     {
        stringstream ss(line);
        ss >> src >> dst >> time;
        Edge currEdge;
        //directed edge from src to dst
        currEdge.source = src;
        currEdge.destination = dst;
        currEdge.time = time;
        edges.push_back(currEdge);
        //directed edge from dst to src
        currEdge.source = dst;
        currEdge.destination = src;
        currEdge.time = time;
        edges.push_back(currEdge);
     }
} 

/*
Function: dijkstra
Purpose: To find the shortest Path
Method: Stores the shortest path in the time array by going through the vertices and updating its distance by 
        adding the previously calculated distance and the current edge distance. This algorithm will traverse to
        every vertex from the source which will always be 0 (YYC).
Input: none
Output: void
** CODE REFERENCED FROM https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/?ref=lbp
*/
void dijkstra()
{
    int u;
    int time[V]; 
    int path[V];
    bool isIncluded[V]; 

    for (int i = 0; i < V; i++)
    {
        if(i == 0)
        {
            time[0] = 0;
        }
        else
        {
            time[i] = MAX;
        }
        isIncluded[i] = false;
        path[0] = -1;
    }

    for (int count = 0; count < V - 1; count++) 
    {    
        int min = MAX;
        for (int v = 0; v < V; v++)
        {
            if (isIncluded[v] == false && time[v] <= min)
            {
                min = time[v];
                u = v;
            }
        }   

        isIncluded[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (adjGraph[u][v] && (time[u] + adjGraph[u][v] < time[v]))
            {
                path[v] = u;
                time[v] = time[u] + adjGraph[u][v];                
            }
        }
    }
    printSolution(time,path);
}

int main()
{
    ifstream file;

    file.open("map.txt");
    readInput(file); 

    fillAdjMatrix();
    dijkstra();

    return 0;
}
