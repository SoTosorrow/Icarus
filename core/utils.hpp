#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS // allow math op for ImVec
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include "imgui.h"
#include "imgui_internal.h"

using Idtype = std::string;

template<typename T>
using Vec = std::vector<T>;

template<typename T1, typename T2>
using Umap = std::unordered_map<T1, T2>;

template<typename T>
using Sharp = std::shared_ptr<T>;

template<typename T>
using Weakp = std::weak_ptr<T>;

template<class T>
concept ShowAble = requires(T a) {
    a.show();
};

struct Context{

    // offset of scene
    ImVec2 vp_trans = ImVec2(0.0f, 0.0f);
    float vp_scale = 1.0;

    Idtype id = std::to_string(1);
    Idtype input_socket_id = std::to_string(-1);
    Idtype ouput_socket_id = std::to_string(-1);
    Idtype last_selected_node_id = std::to_string(-1);
    bool is_in_linking = false;


    Idtype genId(){
        auto id = std::stoi(this->id);
        id += 1;
        auto new_id = std::to_string(id);
        this->id = new_id;
        return new_id;
    }

    void changeViewportScale(float _value){
        this->vp_scale += _value;
    }

    void setViewportScale(float _scale){
        this->vp_scale = _scale;
    }

    void resetViewportScale(){
        this->vp_scale = 1.0f;
    }

    bool ouputNotEmpty(){
        return (this->ouput_socket_id != std::to_string(-1));
    }

    bool selectIsEmpty(){
        return (this->last_selected_node_id == std::to_string(-1));
    }

    void clearSelected(){
        this->last_selected_node_id = std::to_string(-1);
    }

    void clear(){
        this->input_socket_id = std::to_string(-1);
        this->ouput_socket_id = std::to_string(-1);
        this->last_selected_node_id = std::to_string(-1);
    }

};

enum class SocketType{
    Input,
    Ouput,
};

enum class ElementType{
    ElementNode,
    ElementSocket,
    ElementLink,
};

enum class MouseType{
    MouseMoving,
    MouseDown,
    MouseUp,
    MouseDragingLink,
};
