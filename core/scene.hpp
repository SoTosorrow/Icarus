#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <queue>
#include <any>
#include <fmt/core.h>

#include "utils.hpp"
#include "node.hpp"
// #include "link.hpp"
// #include "socket.hpp"

struct Scene: public std::enable_shared_from_this<Scene> {
    
    std::shared_ptr<Context> context;
    std::unordered_map<Idtype, std::shared_ptr<Node>> map_nodes;
    // Umap<Idtype, Sharp<Socket>> map_sockets;
    // Umap<Idtype, Sharp<Link>> map_links;
    // Umap<Idtype, std::any> map_datas;

    bool is_open_menu = false;

    ImU32 scene_grid_color = IM_COL32(200, 200, 200, 40);
    ImU32 scene_link_color = IM_COL32(200, 200, 100, 255);
    float scene_grid_sz = 64.0f;


    Scene();
    void init();

    /// background of scene means line-grid now
    void drawBackground();

    /// key&mouse event handler
    void handleEvent();

    /// add node for map_nodes and create dep sockets
    /*
        add Node to Scene map
        @param f to set node properties and execute before node init
        @old template<class F>
             auto addNode(F const& f=[](std::shared_ptr<Node> node){}, const std::string& name="hello", ImVec2 pos=ImVec2(300,300))-> std::shared_ptr<Node>;
    */
    auto addNode(
        const std::function<void(std::shared_ptr<Node>)>& f = [](std::shared_ptr<Node> node){}, 
        const std::string& name = "hello", 
        ImVec2 pos=ImVec2(300,300)
    ) -> std::shared_ptr<Node>; 

    /// add link for socket&map_links
    void addLink();

    /// ImGui Begin/End interface
    void show();

    void drawNodes();
};