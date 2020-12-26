#include <iostream>
#include "WikiNames.h"
#include "graph.h"

using namespace std;

const string input_file = "data/test_input.txt";

bool graphTests()
{
    // Graph<Vertex, Edge> createGraph() { 

    // Graph<Vertex, Edge> g;
    // g.insertVertex("a");
    // g.insertVertex("b");
    // g.insertVertex("c");
    // g.insertVertex("d");
    // g.insertVertex("e");
    // g.insertVertex("f");
    // g.insertVertex("g");
    // g.insertVertex("h");

    // // add edges on `a`:
    // g.insertEdge("a", "d");
    // g.insertEdge("a", "f");
    // g.insertEdge("a", "b");

    // // add edges on `b`:
    // g.insertEdge("b", "e");
    

    // // add edges on `c`:
    // g.insertEdge("c", "g");
    

    // // add edges on `d`:
    // g.insertEdge("d", "f");


    // // Additional edges on `f`:
    // g.insertEdge("f", "e");
    // g.insertEdge("f", "h");

    // // Additional edges on `g`:
    // g.insertEdge("g", "h");

    // return g;
    // }

    // TEST_CASE("test1") {
    // Graph<Vertex, Edge> g = createGraph();

    // std::list<std::string> path = g.shortestRouteAlgo("b", "e");
    
    // REQUIRE( path.size() == 2 );
    // REQUIRE( path.front() == "b" );
    // REQUIRE( path.back() == "e" );
    // }

    // TEST_CASE("test2") {
    // Graph<Vertex, Edge> g = createGraph();

    // std::list<std::string> path = g.shortestRouteAlgo("b", "d");  
    // REQUIRE( path.size() == 3 );
    // }

    // TEST_CASE("test3") {
    // Graph<Vertex, Edge> g = createGraph();

    // std::list<std::string> path = g.shortestRouteAlgo("a", "g");
    // // a -> f -> h -> g
    // REQUIRE( path.size() == 4 );
    // }

    // TEST_CASE("test4") {
    // Graph<Vertex, Edge> g = createGraph();

    // std::list<std::string> path = g.shortestRouteAlgo("g", "a");
    // // g -> h -> f -> a
    // REQUIRE( path.size() == 4 );
    // }

    // TEST_CASE("tests5") {
    // Graph<Vertex, Edge> g = createGraph();

    // std::list<std::string> path = g.shortestRouteAlgo("c", "a");
    // // c -> g -> h -> f -> a
    // REQUIRE( path.size() == 5 );
    // }

    // TEST_CASE("test6") {
    // Graph<Vertex, Edge> g = createGraph();

    // std::list<std::string> path = g.shortestRouteAlgo("c", "d");
    // // c -> g -> h -> f -> [a/e] -> d
    // REQUIRE( path.size() == 6 );
    // }
    return true;
}


bool wikiTests()
{
    // Testing the graph implementation.
    Graph g(false, true);
    for (int i = 0; i < 6; i++)
        g.insertVertex(to_string(i));

    g.insertEdge("0", "1");
    g.insertEdge("0", "2");
    g.insertEdge("1", "3"); 
    g.insertEdge("2", "4");
    g.insertEdge("4", "5");
    vector<Vertex> dfs = g.DFS("0");
    std::cout <<"DFS: " <<std::endl;
    string ans1 = "";
    for (Vertex v : dfs){
        std::cout << v << ", " ;
        ans1.append(v);
    }
    if(ans1 != "013245"){
        return false;
    }
    std::cout << std::endl;

    //TEST 2
    Graph h(false, true);
    for (int i = 0; i < 10; i++)
        h.insertVertex(to_string(i));
    
    h.insertEdge("0", "1");
    h.insertEdge("0", "2");
    h.insertEdge("0", "4");
    h.insertEdge("0", "5");
    h.insertEdge("1", "3");
    h.insertEdge("3", "7");
    h.insertEdge("7", "6");
    h.insertEdge("6", "8");
    h.insertEdge("4", "9");
    h.insertEdge("5", "8");
    
    list<Vertex> route = h.shortestRoute("0", "8");
    // Expected: 0 --> 5 --> 8
    string ans = "";
    for (Vertex v : route){
        std::cout << v << " --> ";
        ans.append(v);
    }

    if(ans != "058"){
        std::cout << "Fails Test 2: shortestRoute" <<std::endl;
        return false;
    }

    Graph p(false, true);
    for (int i = 0; i < 4; i++)
        p.insertVertex(to_string(i));
    
    p.insertEdge("1", "0");
    p.insertEdge("1", "2");
    p.insertEdge("2", "0");
    p.insertEdge("3", "0");
    p.insertEdge("3", "1");
    p.insertEdge("3", "2");
    p.insertEdge("1", "3");
    
    vector<double> ans2;
    ans2.push_back(.0833333);
    ans2.push_back(.416667);
    ans2.push_back(.166667);
    ans2.push_back(.0833333);

    auto midpath = p.pageRank("1");
    for (auto v : midpath){
        std::cout << v.first << " : " << v.second << std::endl;
    }
    for (auto v : midpath){
        if(ans2[ans.size()] - v.second > 0.0005){ // .0005 testing for precision 
            std::cout << "Failed the page rank test." << std::endl;
            return false;
        }
        else{
            ans2.pop_back();
        }
    }
    
    std::cout << "Passed all test cases." << std::endl;
    return true;
}

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-test") == 0)
    {
        std::cout << argv[1] << std::endl;
        // Run tests here
        wikiTests();
    }
    else if (argc == 1)
    {
        WikiNames names(input_file);
        names.run();
    }
}
