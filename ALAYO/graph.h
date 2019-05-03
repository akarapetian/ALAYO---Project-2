#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/******************************************************************************
 * STRUCT edge
 * ----------------------------------------------------------------------------
 * This is a collection of data that will house all of the information relating
 * to a specific edge. The edge will include begin and end to connect one city
 * to another(string) as well as the distance between them(int). It will also
 * have a boolean value(initialized to false) to account for discovery edges
 ******************************************************************************/
struct edge
{
    string beginningLocation;	//The starting city for each edge

    string endingLocation;		//The destination that connects each edge

    bool   isDiscoveryEdge;		//Checks if the edge has been visited before

    int    distanceBetween;		//Logs the distance between the beginning and
                                //ending locations

    //Constructor for our edge attributes
    edge()
    {
        beginningLocation = "Not Specified";
        endingLocation    = "Not Specified";
        isDiscoveryEdge   = false;
        distanceBetween   = 0;
    }
};

/******************************************************************************
 * STRUCT vertex
 * ----------------------------------------------------------------------------
 * This is a collection of data that will house all of the information relating
 * to our vertex(the location that the program will begin its DFS algorithm. All
 * that is needed is the name of the starting city(string), a variable to check
 * if it has been visited or not(bool), as well as a vector of all of our edges
 * currently stored into the graph(vector<edge>). This will assist us in getting
 * information such as the discovery edges and back edges as well as outputting
 * the entire graph once the program has finished
 ******************************************************************************/
struct vertex
{
    string       startingCity; //The city for a given vertex

    bool         isVisited;    //Boolean value to check if its visited

    vector<edge> edgeVector;   //Vector containing a list of all of our edges
                               //connected to each iteration of a vertex

    //Constructor for the vertex attributes
    vertex()
    {
        startingCity = "Not Specified";
        isVisited    = false;
    }
};

/******************************************************************************
 * CLASS Graph
 * ----------------------------------------------------------------------------
 * Class graph holds operations necessary in order to insert our list of cities
 * into the graph as well as the distances between them. Methods will also
 * include printing out a vector of discovery edges and back edges per the
 * requirements of the assignment. Also, there will be a recursive method call
 * to perform the Depth First Search of our graph(DFS) which will move through
 * the graph and returns the total distance traveled for the graph.
 ******************************************************************************/
class Graph
{
    public:
        //Default constructor for our graph class
        Graph();

        //Default Destructor for our graph class
        ~Graph();

        //Inserts edges into the graph given a starting and ending location as
        //well as the distance between each city
        void insert(string begin,
                    string end,
                    int    distanceBetween);

        //Performs the dijkstras algorithm and finds the shortest distance
        //from dallas to other cities
        void dijkstraAlgorithm(string startVertex,
                               vector<string> &temp,
                               vector<int>    weight,
                               vector<int>    nextLocation);

        //Determines the minimum spanning tree and outputs total mileage and edges
        int MST(string         startVertex,
                vector<string> &temp);

        //Aids the MST method by calculating distance and finding the next
        //vertex
        int mstHelper(vector<string> &temp);

        //Returns the total size of the graph
        unsigned int getGraphSize();

        //Finds the location of the vertex given the name of the vertex
        unsigned int getVertex(string desiredCity);

        //Returns the next smallest edge for a specific vertex
        int getSmallestEdge(int desiredVertex);

        //Will return the number of discover edges within a specific vertex
        unsigned int getDiscoveryEdges(int desiredVertex);

        //Finds the closest vertex given the weight of all other edges
        void determineNearestVertex(vector<string> &temp,
                                    vector<int>    weight,
                                    vector<int>    nextLocation);
        //Returns the distance of a city to the starting location, used as a
        //helper function for dijkstra and mst
        int determineStartingDistance(string desiredCity,
                                      vector<int>    weight,
                                      vector<int>    nextLocation);

        //Returns the distance between one vertex and another
        int determineDistanceBetween(int firstVertex,
                                     int secondVertex);

        //Returns a vector of all the visited edges in the dijkstras algorithm
        vector<string> determineTripVector(string start, string end, int next[]);

    private:

        vector<vertex> graph;	//Our graph of vertices

        int traversalDistance;	//The total traversal distance
};

#endif // GRAPH_H
