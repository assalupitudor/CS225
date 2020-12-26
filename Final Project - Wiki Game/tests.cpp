//#define CATCH_CONFIG_MAIN

//#include <catch2/catch.hpp>
#include "graph.h"
#include "edge.h"
//#include "vertex.h"

Graph createGraph() {
  Graph g(false);
  g.insertVertex("a");
  g.insertVertex("b");
  g.insertVertex("c");
  g.insertVertex("d");
  g.insertVertex("e");
  g.insertVertex("f");
  g.insertVertex("g");
  g.insertVertex("h");

  // add edges on `a`:
  g.insertEdge("a", "d");
  g.insertEdge("a", "f");
  g.insertEdge("a", "b");

  // add edges on `b`:
  g.insertEdge("b", "e");
  

  // add edges on `c`:
  g.insertEdge("c", "g");
  

  // add edges on `d`:
  g.insertEdge("d", "f");


  // Additional edges on `f`:
  g.insertEdge("f", "e");
  g.insertEdge("f", "h");

  // Additional edges on `g`:
  g.insertEdge("g", "h");

  return g;
}

TEST_CASE("test1") {
  Graph<Vertex, Edge> g = createGraph();

  std::list<std::string> path = g.shortestRouteAlgo("b", "e");
  
  REQUIRE( path.size() == 2 );
  REQUIRE( path.front() == "b" );
  REQUIRE( path.back() == "e" );
}

TEST_CASE("test2") {
  Graph<Vertex, Edge> g = createGraph();

  std::list<std::string> path = g.shortestRouteAlgo("b", "d");  
  REQUIRE( path.size() == 3 );
}

TEST_CASE("test3") {
  Graph<Vertex, Edge> g = createGraph();

  std::list<std::string> path = g.shortestRouteAlgo("a", "g");
  // a -> f -> h -> g
  REQUIRE( path.size() == 4 );
}

TEST_CASE("test4") {
  Graph<Vertex, Edge> g = createGraph();

  std::list<std::string> path = g.shortestRouteAlgo("g", "a");
  // g -> h -> f -> a
  REQUIRE( path.size() == 4 );
}

TEST_CASE("tests5") {
  Graph<Vertex, Edge> g = createGraph();

  std::list<std::string> path = g.shortestRouteAlgo("c", "a");
  // c -> g -> h -> f -> a
  REQUIRE( path.size() == 5 );
}

TEST_CASE("test6") {
  Graph<Vertex, Edge> g = createGraph();

  std::list<std::string> path = g.shortestRouteAlgo("c", "d");
  // c -> g -> h -> f -> [a/e] -> d
  REQUIRE( path.size() == 6 );
}
