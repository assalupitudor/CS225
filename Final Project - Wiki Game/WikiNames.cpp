#include <fstream>
#include <iostream>
#include "WikiNames.h"

using namespace std;

WikiNames::WikiNames() { }

WikiNames::WikiNames(string inputfile)
{
    ifstream file(inputfile);
    vector<string> lines;
    string line;
    if (file.is_open())
        while(getline(file, line))
            lines.push_back(line);
    articles_file = lines[0];
    edges_file = lines[1];
    start_point = lines[2];
    end_point = lines[3];
    out_file = lines[4];
    init_names(articles_file);
    init_edges(edges_file);
}


WikiNames::WikiNames(string names_file, string edges_file) : articles_file(names_file), edges_file(edges_file)
{
    init_names(names_file);
    init_edges(edges_file);
}

void WikiNames::init_names(string names_file)
{
    ifstream file(names_file);
    string line;
    if (file.is_open())
        while(getline(file, line))
        {
            size_t space_loc = line.find(" ");
            if (space_loc != string::npos)
            {
                string name = line.substr(space_loc + 1);
                string number = line.substr(0, space_loc);
                int index = stoi(number);
                name_to_index.insert(make_pair(name, index));
                names.push_back(name);
            }
        }
    else
        std::cout << "Could not open the names file." << std::endl;
}

void WikiNames::init_edges(string edges_file)
{
    ifstream edges_ifs(edges_file);
    string line;
    if (edges_ifs.is_open())
        while(getline(edges_ifs, line))
        {
            size_t space_loc = line.find(" ");
            if (space_loc != string::npos)
            {
                int dest = stoi(line.substr(space_loc + 1));
                int source = stoi(line.substr(0, space_loc));
                edges.insert(make_pair(source, dest));
            }
        }
    else
        std::cout << "Could not open the edges file." << std::endl;
}

void WikiNames::print()
{
    for (auto pair : name_to_index)
        std::cout << pair.first << ": " << pair.second << std::endl;
}

vector<pair<string, size_t>> WikiNames::searchSuggestions(string input)
{   
    vector<pair<string, size_t>> answers;
    for (auto pair : name_to_index){
        if (pair.first.rfind(input)!=string::npos) {
            answers.push_back(pair);
        }
    }
    return answers; 

}

void WikiNames::run()
{
    ofstream output;
    output.open(out_file);
    
    Graph wiki(false, true);
    for (size_t i = 0; i < num_articles(); ++i)
        wiki.insertVertex(to_string(i));        // Vertices are keyed by index, aka a vertex looks like "1718"

    for (auto edge : edges)
        wiki.insertEdge(to_string(edge.first), to_string(edge.second)); // edges go from number to number

    if (names.size() == 0 || edges.size() == 0)
        output << "The files provided were invalid or did not exist.\n";
    else if (name_to_index.find(start_point) == name_to_index.end() || name_to_index.find(end_point) == name_to_index.end())
        output << "Either the start or end point did not exist in the provided graph, so the game was stopped.\n";
    else
    {
        Vertex startV = to_string(get(start_point));
        Vertex endV = to_string(get(end_point));
        auto route = wiki.shortestRoute(startV, endV);
        std::vector<Vertex> route_vector{ std::begin(route), std::end(route) };
        for (size_t i = 0; i < route_vector.size() - 1; i++)
        {
            output << route_vector[i] << " --> ";
        } 
        output << route_vector[route_vector.size() - 1] << "\n";
    }
    output.close();
}