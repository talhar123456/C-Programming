#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <algorithm>
#include <iostream>
#include <list>
#include <set>
#include <stack>
#include <stdexcept>
#include <vector>

// an unweighted directed Graph whose vertex properties (e.g. int, Color,
// std::pair<int, Color>, etc.) can be passed as template parameter
// for simplicity vertices can only be added, but not removed
template <typename VertexProp>
class Graph {
   public:
    
    class dfs_iterator;
    class const_dfs_iterator;
    class dfsu_iterator;
    class const_dfsu_iterator;

    // builds an empty graph
    Graph();

    // builds a graph with num_vertices unconnected vertices
    explicit Graph(std::size_t num_vertices);

    // adds a vertex and returns its index
    std::size_t add_vertex(VertexProp &&prop);

    // creates and edge between two vertices and returns if the creation was
    // successful (e.g. the edge could already exist)
    bool add_edge(const std::size_t v_idx1, const std::size_t v_idx2);

    // removes an edge between two vertices and returns if the removal was
    // successful
    bool remove_edge(const std::size_t v_idx1, const std::size_t v_idx2);

    // returns if there is an edge between v_idx1 and v_idx2
    bool has_edge(const std::size_t v_idx1, const std::size_t v_idx2) const;

    // returns if a directed path exists between two nodes
    // in case of v_idx1==v_idx2 return true iff v_ifx is part of a directed cycle
    bool path_exists(const std::size_t v_idx, const std::size_t v_idx2) const;

    // returns the properties for a given vertex index
    VertexProp &get_vertex(const std::size_t v_idx);
    const VertexProp &get_vertex(const std::size_t v_idx) const;

    // returns the number of vertices
    std::size_t num_vertices() const;

    // returns the number of edges
    std::size_t num_edges() const;
    
    // returns the neighbors of a vertex
    std::list<std::size_t> get_neighbors(const std::size_t v_idx) const;

    // returns the neighbors of a vertex ignoring edge directions
    std::list<std::size_t> get_undirected_neighbors(
        const std::size_t v_idx) const;

    dfs_iterator dfs_begin(std::size_t vertex_idx);

    dfs_iterator dfs_end(std::size_t vertex_idx);

    const_dfs_iterator dfs_begin(std::size_t vertex_idx) const;
    
    const_dfs_iterator dfs_end(std::size_t vertex_idx) const;

    dfsu_iterator dfsu_begin(std::size_t vertex_idx);

    dfsu_iterator dfsu_end(std::size_t vertex_idx);

    const_dfsu_iterator dfsu_begin(
        std::size_t vertex_idx) const;

    const_dfsu_iterator dfsu_end(
        std::size_t vertex_idx) const;

   private:
    // stores the neighbors of each vertex
    std::vector<std::vector<bool>> adj_mat_;
    // stores the vertex properties
    std::vector<VertexProp> vertex_props_;
};


#endif  // GRAPH_HPP
