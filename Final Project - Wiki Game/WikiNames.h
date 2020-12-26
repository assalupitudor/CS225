#pragma once

#include <vector>
#include <map>
#include "graph.h"

using namespace std;

class WikiNames 
{

public:
    // The default constructor. Initializes the names and edges to be empty
    WikiNames();

    WikiNames(string inputfile);
    
    // Custom constructor, initializes the map from the text file provided.
    WikiNames(string names_file, string edges_file);

    // Runs the Wiki game on the input provided in the constructor.
    void run();

    // returns a list of the intended queries
    vector<pair<string, size_t>> searchSuggestions(string input);

    // Initialize the names map
    void init_names(string names_file);

    // Initialize the edges map
    void init_edges(string edges_file);

    // Print out all the items in the names map
    void print();

    // Get the article name for a given article index
    string get(size_t index) {  return names[index]; };

    size_t get(string name) {  return name_to_index[name]; };

    // Return the size of the names map.
    size_t num_articles() { return names.size(); };

    // Returns the size of the edges map.
    size_t num_edges() { return edges.size(); };

    string getStartPoint() { return start_point; };

    string getEndPoint() { return end_point; }

    string getArticlesFile() { return articles_file; }

    string getEdgesFile() {return edges_file; }

    string getOutFile() {return out_file; }

    map<string, size_t> name_to_index;
    vector<string> names;
    map<size_t, size_t> edges;

private:
    string articles_file;
    string edges_file;
    string start_point;
    string end_point;
    string out_file;
};