#include "graph.h"

//Public constructor for our graph class, initializes distance to 0
Graph::Graph()
{
    traversalDistance = 0;
}

//Public destructor for our graph class
Graph::~Graph()
{

}

/******************************************************************************
 * METHOD getGraphSize
 * ----------------------------------------------------------------------------
 * Method getGraphSize will return the total size of the graph, which will be
 * the total number of edges that exist. Used as a helper function.
 * ----------------------------------------------------------------------------
 ******************************************************************************/
unsigned int Graph::getGraphSize()
{
    return graph.size();
}


/******************************************************************************
 * METHOD getVertex
 * ----------------------------------------------------------------------------
 * Method getVertex returns the index location in the graph that holds the
 * vertex of the starting city
 * ----------------------------------------------------------------------------
 ******************************************************************************/
unsigned int Graph::getVertex(string desiredCity)
{
    unsigned int index;
    bool found;

    index = 0;
    found = false;

    //Loops through the entire graph, will return the vertex where the city
    //was found(as an integer) or the total size of the graph if the vertex
    //does not exist
    while(index < graph.size() && !found)
    {
        //If found is true, we break out, else we loop again at new index
        if(graph.at(index).startingCity == desiredCity)
        {
            found = true;
        }
        else
        {
            index++;
        }
    }

    return index;
}

/******************************************************************************
 * METHOD insert
 * ----------------------------------------------------------------------------
 * Method insert will take two cities, one for the beginning location and
 * one for the end, as well as the distance between them. If the graph is empty,
 * it will create a vertex as well as an edge case. This will be the function
 * used in main to create our graph
 * ----------------------------------------------------------------------------
 ******************************************************************************/
void Graph::insert(string begin, string end, int distanceBetween)
{
    unsigned int index;
    bool found;

    index = 0;
    found = false;

    //Loops through the entire graph, will return the vertex where the city
    //was found(as an integer) or the total size of the graph if the vertex
    //does not exist
    while(index < graph.size() && !found)
    {
        //If found is true, we break out, else we loop again at new index
        if(graph.at(index).startingCity == begin)
        {
            found = true;
        }
        else
        {
            index++;
        }
    }

    unsigned int theIndex = index;

    //Make sure we are not at the end of the graph
    if(theIndex == graph.size())
    {
        //If we are(index == graph.size()), then we add a new vertex and insert it
        if(getVertex(begin) == graph.size())
        {
            vertex newVertex;

            newVertex.startingCity = begin;
            newVertex.isVisited = false;

            graph.push_back(newVertex);
        }

        insert(begin, end, distanceBetween);
    }
    else
    {
        //If we are not at the end of the graph, it simply becomes an edge
        //instead of a vertex
        edge newEdge;

        //Initialize our edge attributes to what was passed in
        newEdge.beginningLocation = begin;
        newEdge.endingLocation = end;
        newEdge.distanceBetween = distanceBetween;

        //Push it into our edge vector
        graph.at(theIndex).edgeVector.push_back(newEdge);
    }
}

/******************************************************************************
 * METHOD getDiscoveryEdges
 * ----------------------------------------------------------------------------
 * Method getDiscoveryEdges will return the number of discovery edges currently
 * visited for a specific vertex. Used as a helper function for the MST
 * and Dijkstra
 * ----------------------------------------------------------------------------
 ******************************************************************************/
unsigned int Graph::getDiscoveryEdges(int desiredVertex)
{
    int discoveryEdges;

    discoveryEdges = 0;

    //Loops through a specific vertex and counts how many edges in that vertex
    //have been marked as true for isDiscoveryEdge
    for(unsigned int i = 0; i < graph.at(desiredVertex).edgeVector.size(); i++)
    {
        if(graph.at(getVertex(graph.at(desiredVertex).edgeVector.at(i).endingLocation)).isVisited)
        {
            discoveryEdges++;
        }
    }

    return discoveryEdges;
}

/******************************************************************************
 * METHOD dijkstraAlgorithm
 * ----------------------------------------------------------------------------
 * Method dijkstraAlgorithm will perform the said algorithm from a desired
 * starting index, and output the shortest distance starting from dallas to
 * the cities on the map
 * ----------------------------------------------------------------------------
 ******************************************************************************/
void Graph::dijkstraAlgorithm(string         startVertex,
                              vector<string> &temp,
                              vector<int>            weight,
                              vector<int>            nextLocation)
{
    //Initialize our verticesReached
    unsigned int verticesReached = 0;

    //This iterator will start at the beginning of the graph
    vector<vertex>::iterator it = graph.begin();

    //Increments verticesReached depending on how many are already visited
    while(it != graph.end())
    {
        if(it->isVisited)
        {
            verticesReached++;
        }

        it++;
    }

    //If the vertices reached is the total size of the graph, remove all
    //discovery edges and isVisited booleans
    if(verticesReached == graph.size())
    {
        for (unsigned int i=0; i<graph.size(); i++)
        {
            graph[i].isVisited = false;

            for (unsigned int j=0; j< graph.at(i).edgeVector.size(); j++)
            {
                graph[i].edgeVector[j].isDiscoveryEdge = false;
            }
        }
    }

    //Get our current vertex
    int desiredVertex = getVertex(startVertex);

    //With our currentVertex, push back our graphs vertex into temp
    temp.push_back(graph[desiredVertex].startingCity);

    //Create arrays to determine the weight of each edge and the location of the
    //next vertex
    weight[desiredVertex] = 0;
    nextLocation[desiredVertex] = -1;

    //Mark the desired vertex as visited for next time
    graph[desiredVertex].isVisited = true;

    //Now we call our helper function to find the next vertex that is closest
    //and continue to add near vertices until we hit the size cap
    while(temp.size() != getGraphSize())
    {
        determineNearestVertex(temp, weight, nextLocation);
    }
}


/******************************************************************************
 * METHOD MST
 * ----------------------------------------------------------------------------
 * Method MST will be used to determine the minimum spannign tree given a
 * starting location. It will go through the entire graph and determine the
 * minimum distance that one could travel to reach all possible locations on
 * the entire graph
 * ----------------------------------------------------------------------------
 ******************************************************************************/
int Graph::MST(string startVertex, vector<string> &temp)
{
    //Initialize our verticesReached
    unsigned int verticesReached = 0;

    //This iterator will start at the beginning of the graph
    vector<vertex>::iterator it = graph.begin();

    //Increments verticesReached depending on how many are already visited
    while(it != graph.end())
    {
        if(it->isVisited)
        {
            verticesReached++;
        }

        it++;
    }

    //If the vertices reached is the total size of the graph, remove all
    //discovery edges and isVisited booleans
    if(verticesReached == getGraphSize())
    {
        for (unsigned int i=0; i<graph.size(); i++)
        {
            graph[i].isVisited = false;

            for (unsigned int j=0; j< graph.at(i).edgeVector.size(); j++)
            {
                graph[i].edgeVector[j].isDiscoveryEdge = false;
            }
        }

        traversalDistance = 0;
    }

    //Get our current vertex
    int desiredVertex = getVertex(startVertex);

    //Now we set that vertex as visited
    graph.at(desiredVertex).isVisited = true;

    //Push the startingVertex into temp
    temp.push_back(startVertex);

    //As long as we don't hit the size cap of the graph, continue adding more
    //of the closest vertices into the graph
    if(temp.size() != getGraphSize())
    {
        //Using our helper function we acquire our next vertex for the
        //recursive call
        int nextVertex = mstHelper(temp);

        //Call our function with our nextVertex
        MST(graph.at(nextVertex).startingCity, temp);
    }

    //Return the total distance traveled along the MST
    return traversalDistance;
}

/******************************************************************************
 * METHOD determineNearestVertex
 * ----------------------------------------------------------------------------
 * Method determineNearestVertex will assist the dijkstra algorithm by finding
 * the best possible vertex to travel to based on the distance between all of
 * its edges
 * ----------------------------------------------------------------------------
 ******************************************************************************/
void Graph::determineNearestVertex(vector<string> &temp,
                                   vector<int>            weight,
                                   vector<int>            nextLocation)
{
    //If the size is 1, then we can only find the one closest to the root which
    //will be the one that is passed in
    if(temp.size() == 1)
    {
        //Get the index of the front of the temp vector
        int startingVertex = getVertex(temp.front());

        //Set the vertex to compare to as the smallest edge connecting the two
        int connectingVertex = getSmallestEdge(startingVertex);

        //Make sure that we store the weight of the two
        weight[connectingVertex] =
        determineDistanceBetween(startingVertex, connectingVertex);

        //Make sure that we set the next location
        nextLocation[connectingVertex] = startingVertex;

        //Set the connecting vertex to visited
        graph[connectingVertex].isVisited = true;

        //Add the connecting vertex to our temp
        temp.push_back(graph[connectingVertex].startingCity);
    }
    else
    {
        //Create our two edge variables, we will also use distance and vertex
        //variables for comparison
        int smallestEdge = 0;
        int edgeToCompare = smallestEdge + 1;

        //Variables for our distance comparators
        int smallestDistance;
        int distanceToCompare;

        //Get the size of our temp vector
        int size = temp.size();

        //This while loop will check if the edge we are looking for is less than
        //all the sized currently stored into temp vector
        while(edgeToCompare < size)
        {
            //Get each vertex in temp to compare
            int smallVertex = getVertex(temp[smallestEdge]);
            int vertexToCompare = getVertex(temp[edgeToCompare]);

            //If all of the edges are marked as visited, we will move onto the
            //next edge
            if(graph[smallVertex].edgeVector.size() == getDiscoveryEdges(smallVertex))
            {
                smallestEdge++;
            }
            else
            {
                //If not all have been visited we must compare the distances
                //between each edge currently in the prim cloud
                if(graph[vertexToCompare].edgeVector.size() != getDiscoveryEdges(vertexToCompare))
                {
                    //Get our smallest distance variable of one edge
                    smallestDistance =
                    determineDistanceBetween(smallVertex,
                                             getSmallestEdge(smallVertex))

                    + determineStartingDistance(graph[smallVertex].startingCity,
                                                weight,
                                                nextLocation);

                    //Get our comparator distance for the edge to compare
                    distanceToCompare =
                    determineDistanceBetween(vertexToCompare,
                                             getSmallestEdge(vertexToCompare))

                    + determineStartingDistance(graph[vertexToCompare].startingCity,
                                                weight,
                                                nextLocation);

                    //If what we are comparing has a smaller edge, then we must
                    //replace it
                    if(smallestDistance > distanceToCompare)
                    {
                        smallestEdge = edgeToCompare;

                        smallestDistance = distanceToCompare;
                    }
                }
            }

            //Increment to the next edge if all else is false
            edgeToCompare++;
        }

        //Store into smallest vertex once we are done
        int smallestVertex = getSmallestEdge(getVertex(temp[smallestEdge]));

        //Store the weight and the next location of the closest vertex so our
        //mst can continue forward
        weight[smallestVertex] = smallestDistance;
        nextLocation[smallestVertex] = getVertex(temp[smallestEdge]);

        //Mark it as visited so our mst will not go through it again
        graph[smallestVertex].isVisited = true;

        //Add the vertex to temp for next time
        temp.push_back(graph[smallestVertex].startingCity);
    }

}

/******************************************************************************
 * METHOD determineStartingDistance
 * ----------------------------------------------------------------------------
 * Method determineStartingDistance is a helper function that aids the MST in
 * determining if there are any vertices that exist with a weight shorter than
 * the ones we currently have stored. We pass in the desired city and it will
 * return to the mst helper function the distance
 * ----------------------------------------------------------------------------
 ******************************************************************************/
int Graph::determineStartingDistance(string desiredCity,
                                     vector<int>    weight,
                                     vector<int>    nextLocation)
{
    //Our starting distance variable to return
    int totalDistance = 0;

    //Get the vertex for our city we passed in
    int desiredVertex = getVertex(desiredCity);

    //As long as we don't find the weight of the city we passed in, continue to
    //increment the total distance
    while(weight[desiredVertex] != 0)
    {
        totalDistance += determineDistanceBetween(desiredVertex,
        nextLocation[desiredVertex]);

        //Move on to the next location and continue to accumulate distance
        desiredVertex = nextLocation[desiredVertex];
    }

    return totalDistance;
}

/******************************************************************************
 * METHOD mstHelper
 * ----------------------------------------------------------------------------
 * Method mstHelper will aid our function MST in finding the next closest
 * vertex in the cloud for our algorithm. Once it finds the closest vertex it
 * will pass it back to the MST for it to recursively call itself again
 * ----------------------------------------------------------------------------
 ******************************************************************************/
int Graph::mstHelper(vector<string> &temp)
{
    //If the size of our vector is 1, then only the root exists, so find the
    //closest vertex that connects to the root
    if(temp.size() == 1)
    {
        //Get the smallest edge connecting to the root
        int smallestVertex = getSmallestEdge(getVertex(temp.front()));

        //Using the vertex we accumulate the distance
        traversalDistance +=
        determineDistanceBetween(getVertex(temp.front()), smallestVertex);

        //Format the output
        cout << temp.front() << "-->" << graph[smallestVertex].startingCity << "\n\n";

        //Returns the edge back for the MST to use
        return getSmallestEdge(getVertex(temp.front()));
    }
    else
    {
        //If there is not just the root, we must compare each vertex until
        //we find the shortest one
        int firstIndex = 0;
        int comparatorIndex = firstIndex + 1;

        int size = temp.size();

        //Checks if the index we're comparing to exists within the size of temp
        while(comparatorIndex < size)
        {
            //Get our vertex of the root from temp and our comparator vertex
            int smallVertex = getVertex(temp[firstIndex]);
            int comparatorVertex = getVertex(temp[comparatorIndex]);

            //If the number of edges in the vertex are all discovery, we move to
            //the next index
            if(graph[smallVertex].edgeVector.size() ==
               getDiscoveryEdges(smallVertex))
            {
                firstIndex++;
            }
            else
            {
                //If not all have been discovered(visited), then we determine
                //the shortest path to take
                if(graph[comparatorVertex].edgeVector.size() !=
                   getDiscoveryEdges(comparatorVertex))
                {
                    //Find the smallest distance of the shortest possible edge
                    //route
                    int smallestDistance =
                    determineDistanceBetween(smallVertex,
                    getSmallestEdge(smallVertex));

                    //Find the smallest distance of the shortest posssible edge
                    //route for the comparator
                    int comparatorDistance =
                    determineDistanceBetween(comparatorVertex,
                    getSmallestEdge(comparatorVertex));

                    //Only if the smallest distance is greater do we replace it
                    //with the comparatorIndex since that is smaller
                    if(smallestDistance > comparatorDistance)
                    {
                        firstIndex = comparatorIndex;
                    }
                }
            }

            //Increment to the next one since firstIndex has been changed
            comparatorIndex++;
        }

        //Get our new total distance
        traversalDistance += determineDistanceBetween(getVertex(temp[firstIndex]),
                             getSmallestEdge(getVertex(temp[firstIndex])));

        //Acquire our vertex to pass in for our MST
        int smallestVertex = getVertex(temp[firstIndex]);

        //Acquire the city name from our smallest vertex
        string nextCity = graph.at(getSmallestEdge(smallestVertex)).startingCity;

        //Print out the edge
        cout << temp[firstIndex] << "-->" << nextCity << "\n\n";

        //Get the index of the next city for the MST and return it
        firstIndex = getVertex(nextCity);

        return firstIndex;
    }
}

/******************************************************************************
 * METHOD getSmallestEdge
 * ----------------------------------------------------------------------------
 * Method getSmallestEdge is responsible for taking a vertex and returning
 * the smallest edge that connects to it
 * ----------------------------------------------------------------------------
 ******************************************************************************/
int Graph::getSmallestEdge(int desiredVertex)
{
    //Get our smallest index
    int smallestIndex = 0;

    //Once again we need a comparator set to one after the smallest index
    int comparatorIndex = smallestIndex + 1;

    //Get the size of our edge vector at the given vertex passed in
    int size = graph.at(desiredVertex).edgeVector.size();

    //As long as our comparator is less than the size of the edge vector we can
    //continue looping
    while(comparatorIndex < size)
    {
        //Store into smallestVertex the city we would like to compare next
        int smallestVertex =
        getVertex(graph.at(desiredVertex).edgeVector.at(smallestIndex).endingLocation);

        //Comparator vertex will be the following city that we would like to
        //compare(we will be checking the distance between both)
        int comparatorVertex =
        getVertex(graph.at(desiredVertex).edgeVector.at(comparatorIndex).endingLocation);

        //We must check if the vertex has been visited first
        if(graph.at(smallestVertex).isVisited)
        {
            smallestIndex++;
        }
        else
        {
            //As long as we have a vertex that has not been visited, we will
            //compare there distances, else we do nothing
            if(!(graph.at(comparatorVertex).isVisited))
            {
                if(graph.at(desiredVertex).edgeVector.at(smallestIndex).distanceBetween >=
                        graph.at(desiredVertex).edgeVector.at(comparatorIndex).distanceBetween)
                {
                    smallestIndex = comparatorIndex;
                }
            }
        }

        //Always move forward our comparator for the next comparison
        comparatorIndex++;
    }

    //Set our smallest index that was found for the helper functions and return
    smallestIndex = getVertex(graph.at(desiredVertex).edgeVector.at(smallestIndex).endingLocation);

    return smallestIndex;
}

/******************************************************************************
 * METHOD determineDistanceBetween
 * ----------------------------------------------------------------------------
 * Method determineDistanceBetween will be used to find the distance between one
 * edge and another given two vertices. The only condition is that secondVertex
 * must exist in firstVertex's edge vector(must be connected to it).
 * ----------------------------------------------------------------------------
 ******************************************************************************/
int Graph::determineDistanceBetween(int firstVertex, int secondVertex)
{
    //initilize our index to zero for while loop
    int index = 0;

    //Checks if the ending location of the first vertex edges does not equal
    //any of the second vertex's starting edges
    while(graph[firstVertex].edgeVector[index].endingLocation !=
          graph[secondVertex].startingCity)
    {
        index++;
    }

    //Return the distance between the two if it was found
    return graph[firstVertex].edgeVector[index].distanceBetween;
}

/******************************************************************************
 * METHOD determinePathVector
 * ----------------------------------------------------------------------------
 * Method determinePathVector will keep track of the path that we have taken
 * through the map and make sure we are still following the prim algorithm. It's
 * main goal is to be a helper function for the mst and reverse our path.
 * ----------------------------------------------------------------------------
 ******************************************************************************/
vector<string> Graph::determineTripVector(string start, string end, int next[])
{
    //Create our vector of strings for the cities
    vector<string> tempTripVec;

    //Our vertex will be set to the end location of our path
    int vertex = getVertex(end);

    //fill our path vector with all the vertices in our graph
    while(next[vertex] != -1)
    {
        tempTripVec.push_back(graph[vertex].startingCity);

        vertex = next[vertex];
    }

    tempTripVec.push_back(graph[vertex].startingCity);

    //Reverse the temp vector and return it
    reverse(tempTripVec.begin(), tempTripVec.end());

    return tempTripVec;
}
