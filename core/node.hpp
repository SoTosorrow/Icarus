#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include <type_traits>
#include <string_view>
#include <initializer_list>
#include "fmt/core.h"
#include "utils.hpp"
#include "graph.hpp"

struct Scene;
struct Node
{
    Idtype id;

    std::string_view name;
    std::weak_ptr<Scene> scene;
    std::shared_ptr<Context> context;
    std::unique_ptr<Graph> graph;

    ImVec2 pos = ImVec2{100,100};
    ImVec2 size = ImVec2{150, 60};

    bool is_enable = true;
    bool is_resize = false;
    bool is_update_data = false;
    bool is_debug_mode = true;

    int input_sockets_num = 0;
    int ouput_sockets_num = 0;
    int compute_input_dep = 0;

    std::vector<Idtype> input_socket_ids;
    std::vector<Idtype> ouput_socket_ids;

    float node_head_height = 20.0f;
    ImU32 node_head_color = IM_COL32(200, 100, 100, 255);
    ImU32 node_body_color = IM_COL32(100, 100, 100, 255);

    Node(std::weak_ptr<Scene> _scene, std::shared_ptr<Context> _context);
    virtual ~Node(){fmt::print("[DEBUG] node:{} destroy\n", this->id);}

    void setName(const std::string_view &_name);
    void setSocketsNum(int _input_sockets_num, int _output_sockets_num);
    void setNodeSize(int _size_x, int _size_y);
    void setPos(ImVec2 _pos);

    template<typename T>
    void setInput(std::initializer_list<T>);

    template<typename T>
    void setOuput(std::initializer_list<T>);

    ImVec2 getStartPos();

    // auto addSocket(
    //     const std::function<void(std::shared_ptr<Socket>)>& f = [](std::shared_ptr<Socket> node){}
    // ) -> std::shared_ptr<Socket>; 

    void init();
    void update();
    void transfer();

    /// the only func connect to View(ImGui)
    void draw();
    virtual void drawContent(){}
};

