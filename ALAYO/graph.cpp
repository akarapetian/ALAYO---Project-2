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
                              vector<int>            &weight,
                              vector<int>            &nextLocation)
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
int Graph::MinimumSpanningTree(string startVertex, vector<string> &temp)
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
        MinimumSpanningTree(graph.at(nextVertex).startingCity, temp);
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
                                   vector<int>            &weight,
                                   vector<int>            &nextLocation)
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
                                     vector<int>    &weight,
                                     vector<int>    &nextLocation)
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
vector<string> Graph::determineTripVector(string start, string end, vector<int> &next)
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

//******** DFS METHODS ***********************************
int Graph::DepthFirstSearch(string beginLocation, vector<string> &theGraph)
{
    //Initializes currentVertex to our beginLocation variable
    int currentVertex;

    currentVertex = getVertex(beginLocation);

    //We must mark our beginning city as visited, this will be updated with
    //each new location visited during recursion
    graph.at(currentVertex).isVisited = true;

    //Create an iterator for our graph, starting at the first location passed in
    vector<string>::iterator it =
    find(theGraph.begin(), theGraph.end(), beginLocation);

    //If the desired location is at the end of the graph, simply push the
    //location into the graph
    if (it == theGraph.end())
    {
        theGraph.push_back(beginLocation);
    }

    unsigned int visitedLocations;

    visitedLocations = 0;

    vector<vertex>::iterator itLoc = graph.begin();

    while (itLoc != graph.end() && visitedLocations < graph.size())
    {
        if (itLoc->isVisited)
        {
            visitedLocations++;
        }

        itLoc++;
    }

    //As long as the number of visited locations does not equal the size of the
    //graph, continue searching for the next vertex and recursively call the
    //function again
    if (visitedLocations < graph.size())
    {
        int nextVertex = dfsHelper(currentVertex, theGraph);
        DepthFirstSearch(graph.at(nextVertex).startingCity, theGraph);
    }

    //Return our total distance traveled
    return traversalDistance;
}

/******************************************************************************
 * METHOD printDFSList
 * ----------------------------------------------------------------------------
 * Method printDFSList will print out our entire list after it has been sorted
 * as well as output the total distance
 * ----------------------------------------------------------------------------
 ******************************************************************************/
void Graph::printDFSList(int distance, vector<string> &theGraph)
{
    cout << "\n\nPrinting the DFS search to show the travel path:\n\n";;

    for (unsigned int index = 0; index < theGraph.size(); index++)
    {
        cout << theGraph.at(index) << endl;
    }
}

void Graph::clear()
{
    graph.clear();
}

/******************************************************************************
 * METHOD getSmallestEdge
 * ----------------------------------------------------------------------------
 * Method getSmallestEdge is a helper recursive function to assist the DFS
 * search in always choosing the shortest mileage when encountered with
 * multiple edges to choose from
 * ----------------------------------------------------------------------------
 ******************************************************************************/
int Graph::dfsHelper(int vertex, vector<string> &theGraph)
{
    unsigned int totalCitiesVisited = 0;

    //Checks our boolean value for each edge and increments a counter accordingly
    for (unsigned int i = 0; i < graph.at(vertex).edgeVector.size(); i++)
    {
        if (graph.at(getVertex(graph.at(vertex).edgeVector.at(i).endingLocation)).isVisited)
        {
            totalCitiesVisited++;
        }
    }

    if (totalCitiesVisited != graph.at(vertex).edgeVector.size())
    {
        //These index variables will be assist in comparing two vertices
        int firstIndex;
        int secondIndex;

        //Initialize to default values
        firstIndex = 0;
        secondIndex = firstIndex + 1;

        //Set the size to the size of the current edgeVector
        int size;

        size = graph.at(vertex).edgeVector.size();

        while (secondIndex < size)
        {
            //Our first vertex to check
            int firstVertex;

            //Set firstVertex equal to the first element of the edge vector in
            //our graph
            firstVertex =
            getVertex(graph.at(vertex).edgeVector.at(firstIndex).endingLocation);

            //Our second vertex to check and compare with first vertex
            int secondVertex;

            //Set secondVertex equal to the element immediately following the
            //firstIndex in edgeVector
            secondVertex =
            getVertex(graph.at(vertex).edgeVector.at(secondIndex).endingLocation);

            //Make sure that the next destination is not visited
            if (graph.at(firstVertex).isVisited)
            {
                //If it is, increment the first index to choose another possible
                //path
                firstIndex++;
            }
            else
            {
                //If the second location is not visited, then we can set our
                //firstIndex equal to the secondIndex
                if (!(graph.at(secondVertex).isVisited))
                {
                    if (graph.at(vertex).edgeVector.at(firstIndex).distanceBetween
                        >= graph.at(vertex).edgeVector.at(secondIndex).distanceBetween)
                    {
                        firstIndex = secondIndex;
                    }
                }
            }
            secondIndex++;
        }

        //Now the new location is a discovery edge, meaning we have visited it
        graph.at(vertex).edgeVector.at(firstIndex).isDiscoveryEdge = true;

        //Increment the new total distance
        traversalDistance += graph.at(vertex).edgeVector.at(firstIndex).distanceBetween;

        string nextCity;

        //Start our move to the next city
        nextCity=
        graph.at(vertex).edgeVector.at(firstIndex).endingLocation;

        //Set our firstIndex to our new city vertex
        firstIndex = getVertex(nextCity);

        //Check if any of the new firstIndex holds any discovered edges and
        //set them to true
        for (unsigned int i = 0; i < graph.at(firstIndex).edgeVector.size(); i++)
        {
            if (graph.at(vertex).startingCity
                    == graph.at(firstIndex).edgeVector.at(i).endingLocation)
            {
                graph.at(firstIndex).edgeVector.at(i).isDiscoveryEdge = true;
            }
        }

        return firstIndex;
    }
    //If all of the possible paths are discovery edges, then we must backtrack
    else
    {
        vector<string>::iterator it;

        it = find(theGraph.begin(), theGraph.end(),
                  graph.at(vertex).startingCity);
        it--;

        int backEdgeIndex;

        backEdgeIndex = getVertex(*it);

        return dfsHelper(backEdgeIndex, theGraph);
    }
}

int Graph::BreadthFirstSearch(string startingCity, vector<string> &bfs)
{
    // Reset the graph, this should be its own function
    for (unsigned int i=0; i<graph.size(); i++)
    {
        graph.at(i).isVisited = false;
        for (unsigned int j=0; j< graph.at(i).edgeVector.size(); j++)
        {
            graph.at(i).edgeVector.at(j).isDiscoveryEdge = false;
        }
    }

    // Get the graph index of the vertex being visited.
    int currVertex = getVertex(startingCity);

    // Visit the starting vertex
    graph.at(currVertex).isVisited = true;

    // Create a newLevel vector to hold the current level, containing only
    // the 1st vertex, and add the first vertex to the bfs vector
    vector<int> newLevel;
    newLevel.push_back(currVertex);
    bfs.push_back(startingCity);

    // Start recursion
    return bfsHelper(bfs, newLevel);
}

int Graph::bfsHelper(vector<string> &bfs, vector<int> previousLevel)
{
    vector<int> newLevel;
    vector<int> currLevel;
    int levelDistance = 0;

    vector<edge> * currEdgeList;
    vertex * startingVertex;
    vertex * currVertex;
    int currVertexID;

    // Iterate through the previous level
    for (unsigned int i=0; i<previousLevel.size(); i++)
    {
        startingVertex = &graph.at(previousLevel.at(i));
        currEdgeList = &startingVertex->edgeVector;

        // Iterate through the ith vertex's edge list
        for (unsigned int j=0; j<currEdgeList->size(); j++)
        {
            // Add all non-visited levels to the next level, in closest order
            currVertexID = getVertex(otherVertex(currEdgeList->at(j),startingVertex->startingCity));
            currVertex = &graph.at(currVertexID);
            if (!currVertex->isVisited)
            {
                // Add the edge length to the distance, including return trip
                levelDistance += currEdgeList->at(j).distanceBetween;

                // Mark the vertex as visited and the edge as a discovery edge
                currVertex->isVisited = true;
                currEdgeList->at(j).isDiscoveryEdge = true;

                // Also mark the reverse edge as a discovery edge
                for(unsigned int i = 0; i < currVertex->edgeVector.size(); i++)
                {
                    if(currVertex->edgeVector.at(i).endingLocation == startingVertex->startingCity)
                    {
                        currVertex->edgeVector.at(i).isDiscoveryEdge = true;
                    }
                }

                // Insert the current vertex in the sorted position
                bool inserted = false; // could do the same thing by changing the visited variable, but this is clearer
                for (unsigned int k=0; k<currLevel.size() && !inserted; k++)
                {
                    if (currEdgeList->at(j).distanceBetween < distance(startingVertex, &graph.at(currLevel.at(k))))
                    {
                        currLevel.insert(currLevel.begin()+k,currVertexID);
                        inserted = true;
                    }
                }
                if (!inserted)
                {
                    currLevel.push_back(getVertex(currVertex->startingCity));
                }
            }
        }
        // Add the current level vertices to the the end of the bfs vector
        for (unsigned int m=0; m<currLevel.size(); m++)
        {
            bfs.push_back(graph.at(currLevel.at(m)).startingCity);
        }

        // Add the current level vertices to the end of the newLevel vector
        newLevel.insert(newLevel.end(),currLevel.begin(),currLevel.end());
        currLevel.clear();
    }

    // If still has vertices, do recursive call
    if (newLevel.size() > 0)
    {
        return levelDistance + bfsHelper(bfs, newLevel);
    }
    else
    {
        return levelDistance;
    }
}

string Graph::otherVertex(edge currEdge, string startingCity)
{
    if (currEdge.beginningLocation == startingCity)
    {
        return currEdge.endingLocation;
    }
    else
    {
        return currEdge.beginningLocation;
    }
}

/******************************************************************************
 * METHOD printDiscoveryEdges
 * ----------------------------------------------------------------------------
 * Method printDiscoveryEdges will print out a list of all the discovery edges,
 * meaning the path that was taken during the trip and output them to the
 * console
 * ----------------------------------------------------------------------------
 ******************************************************************************/
void Graph::printDiscoveryEdges(vector<string> &theGraph)
{
    //Initialize another vector of edges for our discoveryEdge vector
    vector<edge> discoveryEdgeVec;

    for (unsigned int i = 0; i < graph.size(); i++)
    {
        int index;

        //Set index equal to the vertex of the current location in the graph
        index = getVertex(theGraph.at(i));

        //Here we will use our boolean for discovery edges and as long as the
        //boolean is true, we push those values into our discoveryVec
        for (unsigned int j = 0; j < graph.at(index).edgeVector.size(); j++)
        {
            if (graph.at(index).edgeVector.at(j).isDiscoveryEdge)
            {
                discoveryEdgeVec.push_back(graph.at(index).edgeVector.at(j));
            }
        }
    }

    //Create our iterator in order to move through our edge vector
    vector<edge>::iterator itDup = discoveryEdgeVec.begin();

    //Check and make sure we don't reach the end of the list
    while (itDup != discoveryEdgeVec.end())
    {
        //Create a second iterator to check the next element in the list
        vector<edge>::iterator nextIt = itDup + 1;

        bool deleted = false;

        while (nextIt != discoveryEdgeVec.end() && !deleted)
        {
            //If both beginning and ending locations for the first and second
            //iterators are matching, then delete them
            if (itDup->beginningLocation == nextIt->endingLocation
             && itDup->endingLocation    == nextIt->beginningLocation)
            {
                discoveryEdgeVec.erase(nextIt);

                deleted = true;
            }
            else
            {
                nextIt++;
            }
        }

        itDup++;
    }

    //This iterator will be used to find all our discovery edges
    vector<edge>::iterator it = discoveryEdgeVec.begin();

    //Create a vector for return
    vector<string> disEdgeVector;

    //This while loop will be used for formatting our output
    while (it != discoveryEdgeVec.end())
    {
        disEdgeVector.push_back(it->beginningLocation + "--->" + it->endingLocation);
        it++;
    }

    cout << "\nPrinting out a list of all discovery Edges...\n";
    cout << "Note that discovery edges with the same edge will be paired together\n\n";

    for (unsigned int index = 0; index < disEdgeVector.size(); index++)
    {
        cout << disEdgeVector.at(index) << endl;
    }

}

/******************************************************************************
 * METHOD printBackEdges
 * ----------------------------------------------------------------------------
 * Method printBackEdges will print a list of all of the back edges currently
 * encountered during execution
 * ----------------------------------------------------------------------------
 ******************************************************************************/
void Graph::printBackEdges(vector<string> &theGraph)
{
    //Initialize another vector of edges for our backEdge vector
    vector<edge> backEdgeVec;

    for (unsigned int i = 0; i < graph.size(); i++)
    {
        //Set index equal to the vertex of the current location in the graph
        int index;

        index = getVertex(theGraph.at(i));

        //Here we will use our boolean for discovery edges and as long as the
        //boolean is false, we push those values into our edgeVec
        for (unsigned int j = 0; j < graph.at(index).edgeVector.size(); j++)
        {
            if (!(graph.at(index).edgeVector.at(j).isDiscoveryEdge))
            {
                backEdgeVec.push_back(graph.at(index).edgeVector.at(j));
            }
        }
    }

    //Create our iterator in order to move through our edge vector
    vector<edge>::iterator itDup = backEdgeVec.begin();

    //Check and make sure we don't reach the end of the list
    while (itDup != backEdgeVec.end())
    {
        //Create a second iterator to check the next element in the list
        vector<edge>::iterator nextIt = itDup + 1;

        bool deleted = false;

        while (nextIt != backEdgeVec.end() && !deleted)
        {
            //If both beginning locations for the first and second iterators
            //are matching, then delete them
            if (itDup->beginningLocation == nextIt->endingLocation
             && itDup->endingLocation    == nextIt->beginningLocation)
            {
                backEdgeVec.erase(nextIt);

                deleted = true;
            }
            else
            {
                nextIt++;
            }
        }

        itDup++;
    }

    //This iterator will be used to find all our discovery edges
    vector<edge>::iterator it = backEdgeVec.begin();

    //Create a vector for return
    vector<string> backEdgeVector;

    //This while loop will be used for formatting our output
    while (it != backEdgeVec.end())
    {
        backEdgeVector.push_back(it->beginningLocation + "--->" + it->endingLocation);

        it++;
    }

    cout << "\nPrinting out a list of all back Edges...\n";
    cout << "Note that back edges with the same edge will be paired together\n\n";

    for (unsigned int index = 0; index < backEdgeVector.size(); index++)
    {
        cout << backEdgeVector.at(index) << endl;
    }
}

int Graph::distance(vertex * v1, vertex * v2)
{
    for (unsigned int i = 0; i < v1->edgeVector.size(); i++)
    {		// get connecting edge
        if (v1->edgeVector.at(i).beginningLocation == v2->startingCity
                || v1->edgeVector.at(i).endingLocation == v2->startingCity)
            return v1->edgeVector.at(i).distanceBetween;
    }
    return -1;
}

void Graph::reinitializeTraversalDistance()
{
    traversalDistance = 0;
}
