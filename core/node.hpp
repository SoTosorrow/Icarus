#pragma once
#include "utils.hpp"
#include <memory>
#include <unordered_map>
#include <vector>
#include <type_traits>
#include <string_view>

struct Scene;
struct Node
{
    Idtype id;

    std::string_view name;
    std::weak_ptr<Scene> scene;
    std::shared_ptr<Context> context;

    ImVec2 pos;
    ImVec2 size = ImVec2(150, 60);

    bool is_enable = true;
    bool is_resize = false;
    bool is_write_data = false;
    bool is_debug_mode = true;

    int input_sockets_num = 0;
    int ouput_sockets_num = 0;
    int compute_input_dep = 0;

    std::vector<Idtype> input_socket_ids;
    std::vector<Idtype> ouput_socket_ids;

    float node_head_height = 20.0f;
    ImU32 node_head_color = IM_COL32(200, 100, 100, 255);
    ImU32 node_body_color = IM_COL32(100, 100, 100, 255);

    Node(std::weak_ptr<Scene> _scene, std::shared_ptr<Context> _context, const std::string_view &_name, ImVec2 _pos);

    void setSocketsNum(int _input_sockets_num, int _output_sockets_num);
    void setNodeSize(int _size_x, int _size_y);

    // auto addSocket(
    //     const std::function<void(std::shared_ptr<Socket>)>& f = [](std::shared_ptr<Socket> node){}, 
    //     const std::string& name = "hello", 
    //     ImVec2 pos=ImVec2(300,300)
    // ) -> std::shared_ptr<Socket>; 

    void init();

    /// the only func connect to View(ImGui)
    void draw();
    virtual void drawContent(){}
};

template<class T>
concept NodeAble = std::is_base_of<Node, T>::value;