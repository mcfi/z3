/*++
Copyright (c) 2017 Arie Gurfinkel

Module Name:

    min_cut.h

Abstract:
    min cut solver

Author:
    Bernhard Gleiss

Revision History:


--*/

#ifndef MIN_CUT_H_
#define MIN_CUT_H_

#include "ast/ast.h"
#include "util/vector.h"


class min_cut {
public:
    min_cut();

    unsigned new_node();
    /*
      \brief add an edge (with unit capacity)
    */
    void add_edge(unsigned i, unsigned j);

    void compute_min_cut(unsigned_vector& cut_nodes);
    
private:

    typedef svector<bool> bool_vector;
    struct edge { unsigned node; unsigned weight; edge(unsigned n, unsigned w): node(n), weight(w) {} edge(): node(0), weight(0) {} };
    typedef svector<edge> edge_vector;
        
    vector<edge_vector> m_edges; // map from node to all outgoing edges together with their weights (also contains "reverse edges")
    unsigned_vector m_d;    // approximation of distance from node to sink in residual graph
    unsigned_vector m_pred; // predecessor-information for reconstruction of augmenting path
    
    void compute_initial_distances();
    unsigned get_admissible_edge(unsigned i);
    void augment_path();
    void compute_distance(unsigned i);
    void compute_reachable_nodes(bool_vector& reachable);
    void compute_cut_and_add_lemmas(bool_vector& reachable, unsigned_vector& cut_nodes);
};

#endif
