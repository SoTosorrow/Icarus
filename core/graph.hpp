#pragma once
#include <memory>
#include "utils.hpp"

struct Graph{
    Idtype id;
    ImVec2 graph_start_pos;    
    std::unique_ptr<Graph> belong_graph;

    void draw();
    void resize(float resize_x, float resize_y);
    void findIncludeNodes();
};