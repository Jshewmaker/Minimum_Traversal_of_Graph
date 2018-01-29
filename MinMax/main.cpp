//
//  main.cpp
//  MinMax
//
//  Created by Joshua Shewmaker on 9/25/17.
//  Copyright © 2017 Joshua Shewmaker. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;

template <class Object>
class Matrix
{
public:
    Matrix( int rows=0, int cols=0 ) : array( rows )
    {
        for( int i = 0; i < rows; i++ )
            array[ i ].resize( cols );
            }
    void resize( int rows, int cols )
    {
        array.resize(rows);
        for( int i = 0; i < rows; i++ )
            array[ i ].resize( cols );
    }
    const vector<Object> & operator[]( int row ) const
    {
        return array[ row ];
    }
    vector<Object> & operator[]( int row )
    {
        return array[ row ];
    }
    int numrows( ) const{
        return array.size( );
    }
    int numcols( ) const{
        return numrows( ) ? array[ 0 ].size( ) : 0;
    }
    int numcols(int row){
        return array[row].size();
    }
    void orderArray(){
        sort(array.begin(), array.end());
    }
private:
    vector< vector<Object> > array;
};


class Graph
{
public:
    Graph (int size); // creates an empty graph with size vertices
    void fillGraph(); // fills in the graph from cin
    void printGraph(); // prints the graph (for debugging only)
    int maxCover( vector<char> order); // returns the maxCover for the
    // ordering order
    int cover( char vertex, vector<char> order); // returns the cover size for vertex
private:
    Matrix<char> adj;// or Matrix<int> adj;
};
// from Data Structures and Algorithm Analysis in C++ (Third Edition), by Mark Allen Weiss

Graph::Graph(int size){
    adj.resize(size,0);
}
void Graph::fillGraph(){
    char node;
    int listSize = 0;
    for(int i = 0; i < adj.numrows(); i++){
        cin >> node;
        adj[i].push_back(node);
        cin >> listSize;
        for(int j = 0; j < listSize; j++){
            cin >> node;
            adj[i].push_back(node);
        }
    }
}
//n^2
void Graph::printGraph(){
    for(int i = 0; i < adj.numrows(); i++){
        for(int j = 0; j < adj.numcols(i); j++){
            cout << adj[i][j];
        }
        cout << endl;
    }
   
}
int Graph::maxCover(vector<char> order){
    vector<char> testVec;
    string endString = "";
    int rowCover = 0, finalCover = 1000;
    adj.orderArray();
    for (int i = 0; i < adj.numrows(); i++){
        testVec.push_back(adj[i][0]);
    }
    do {
        for(int i = 0; i <adj.numrows(); i++){
            for(int j = 0; j < adj[i].size(); j++){
                int counter = 0;
                while(adj[i][0] != testVec[counter])
                    counter++;
                int tempCover = abs(cover(adj[i][j], testVec) - counter);
                if(rowCover < tempCover)
                    rowCover = tempCover;
                }
        }
        if(finalCover > rowCover){
            finalCover = rowCover;
            endString.clear();
            for (int i = 0; i < testVec.size(); i++){
                endString = endString + testVec[i] + ' ';
            }

            }
    rowCover = 0;
    } while (next_permutation(testVec.begin(), testVec.end()));
    cout << endString;
    return finalCover;
}
int Graph::cover(char vertex, vector<char> order){
    int coverSize = 0;
    
    while(vertex != order[coverSize])
        coverSize++;
    
    return coverSize;
}

int main(int argc, const char * argv[]) {
    int numberOfGraphs;
    int size;
    vector<char> diagram;
    
    cin >> numberOfGraphs;
    for(int i = 0; i < numberOfGraphs; i++){
        cin >> size;
    
        Graph Main(size);
        Main.fillGraph();
        cout << Main.maxCover(diagram) << endl;
    }
    return 0;
}
