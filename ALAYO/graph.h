/*
 *  Baseball Trip Project
 *  Spring 2019
 *
 *  Oscar Lopez <olopez23@saddleback.edu>
 *  Anthony Karapetian <akarapetian1@saddleback.edu>
 *  Alek Peratoner <aperatoner0@saddleback.edu>
 *  Luke Schrezenmeier <lschrezenmeier0@saddleback.edu>
 *  Yuchen Yao <yyao7@ivc.edu>
 *
 *  Descr: Baseball Project for Spring 2019 CS1D
 *  Professor: Jerry Lebowitz
 *
 *  This program is an application in which a baseball
 *  can view information regarding any major league
 *  baseball team as well as take a dream trip and
 *  visit any stadium wanted.
 *
 **/
/*
    File: graph.h
    Class holding the key algorithms of the program.
    Dijkstra, BFS, DFS, MST
*/

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

/**
 * @brief Struct edge - struct that holds the location of start and finish, as well
 * as the discovery edges and distances between
 */
struct edge
{
    string beginningLocation;	/**<The starting city for each edge*/

    string endingLocation;		/**<The destination that connects each edge*/

    bool   isDiscoveryEdge;		/**<Checks if the edge has been visited before*/

    int    distanceBetween;		/**<Logs the distance between the beginning and ending locations*/

    /**
    * @brief Restaurant - default constructor for edge data
    */
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

/**
* @brief Struct vertex - struct for the vertrex
*/
struct vertex
{
    string       startingCity; /**<The city for a given vertex*/

    bool         isVisited;    /**<Boolean value to check if its visited*/

    vector<edge> edgeVector;   /**<Vector containing a list of all of our edges connected to each iteration of a vertex*/

    /**
    * @brief Default constructor vertex
    */
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

/**
* @brief Struct vertex - struct for the vertrex
*/
class Graph
{
    public:
        /**
        * @brief Default constructor for our graph class
        */
        Graph();

        /**
        * @brief Default Destructor for our graph class
        */
        ~Graph();

        /**
        * @brief Inserts edges into the graph given a starting
        *        and ending location as well as the distance
        *        between each city
        * @param begin - beginning city
        * @param end   - ending city
        * @param distanceBetween - weight of the edges
        */
        void insert(string begin,
                    string end,
                    int    distanceBetween);


        /**
        * @brief erases all entries in the graph
        */
        void clear();

        /**
        * @brief Dijkstras Algorithm. Finds the shortest path
        * @param startVertex - starting location
        * @param temp - vectorList
        * @param weight   - vector holding weights
        * @param nextLocation - vector holding the next location
        */
        void dijkstraAlgorithm(string startVertex,
                               vector<string> &temp,
                               vector<int>    &weight,
                               vector<int>    &nextLocation);

        /**
        * @brief MST - determins the minimum spanning tree as well
        *              as displaying the total distance
        * @param startVertex - start vertex
        * @param weight   - vector holding weights
        * @param nextLocation - vector holding the next location
        * @return distance - returns total distance
        */
        int MinimumSpanningTree(string startVertex,
                                vector<string> &temp);

        /**
        * @brief Aids the MST method by calculating distance and finding the next vertex
        * @param temp - temporary vector
        * @return distance - distance traveled
        */
        int mstHelper(vector<string> &temp);

        /**
        * @brief Returns the total size of the graph
        * @return size - size of the graph
        */
        unsigned int getGraphSize();

        /**
        * @brief Finds the location of the vertex given the name of the vertex
        * @param desiredCity - city they would like to find
        * @return returns the vertex
        */
        unsigned int getVertex(string desiredCity);

        /**
        * @brief Returns the next smallest edge for a specific vertex
        * @param desiredVertex - vertex they would like to find
        * @return returns the smallest edge
        */
        int getSmallestEdge(int desiredVertex);

        /**
        * @brief Will return the number of discover edges within a specific vertex
        * @param desiredVertex - vertex they would like to find
        * @return returns the Discovery edges
        */
        unsigned int getDiscoveryEdges(int desiredVertex);

        /**
        * @brief Finds the closest vertex given the weight of all other edges
        * @param temp - temporary vector
        * @param weight - vector holding weights
        * @param nextLocation - vector holding next location
        */
        void determineNearestVertex(vector<string> &temp,
                                    vector<int>    &weight,
                                    vector<int>    &nextLocation);

        /**
        * @brief Returns the distance of a city to the starting location, used as a
        *        helper function for dijkstra and mst
        * @param desiredCity - city to start
        * @param weight - vector holding weights
        * @param nextLocation - vector holding next location
        * @return distance
        */
        int determineStartingDistance(string desiredCity,
                                      vector<int>    &weight,
                                      vector<int>    &nextLocation);

        /**
        * @brief Returns the distance between one vertex and another
        * @param firstVertex - start vertex
        * @param secondVertex - end vertex
        * @return returns the weight
        */
        int determineDistanceBetween(int firstVertex,
                                     int secondVertex);

        /**
        * @brief Returns a vector of all the visited edges in the dijkstras algorithm
        * @param start - starting city
        * @param end - ending city
        * @param next - vector holding the next
        * @return returns the vector of all the visited edges
        */
        vector<string> determineTripVector(string start, string end, vector<int> &next);

        //DFS,BFS***********************************************************************

        /**
        * @brief Performs the DFS search and returns the total distance traveled to main
        * @param begin - beginning location
        * @param theGraph - vector holding all locations found in order
        * @return returns the distance traveled
        */
        int DepthFirstSearch(string begin, vector<string> &theGraph);

        /**
        * @brief Helper function for method DFS that finds the smallest possible
        *        distance between each edge
        * @param vertex - vertex to start
        * @param theGraph - vector holding all locations found
        * @return distance
        */
        int dfsHelper(int vertex, vector<string> &theGraph);

        /**
        * @brief Performs the BFS search and returns the total distance traveled to mainwindow.cpp
        * @param begin - beginning location
        * @param theGraph - vector holding all locations found
        * @return returns the distance traveled
        */
        int BreadthFirstSearch(string begin, vector<string> &theGraph);

        /**
        * @brief Recursion to run through BFS search
        * @param bfs - bfs algorithm
        * @param previousLevel - vector holding the level before
        * @return returns distance
        */
        int bfsHelper(vector<string> &bfs, vector<int> previousLevel);

        /**
        * @brief returns the opposite location from the starting city
        * @param desiredVertex - vertex they would like to find
        * @return returns the opposite location from startin city
        */
        string otherVertex(edge currEdge, string startingCity);

        /**
        * @brief Will return the distance between vertex 1 and 2
        * @param v1 - first vertex
        * @param v2 - second vertex
        * @return returns the distance
        */
        int distance(vertex * v1, vertex * v2);

        /**
        * @brief Reinitializes traversal distance back to 0
        */
        void reinitializeTraversalDistance();

    private:

        vector<vertex> graph;	/** <Our graph of vertices*/

        int traversalDistance;	/** <The total traversal distance*/
};

#endif // GRAPH_H
