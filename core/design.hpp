#include "node.hpp"

template<typename T>
concept NodeAble = std::is_base_of<Node, T>::value;

template<typename T>
concept View = requires(T t){
    { t.draw()        }-> std::convertible_to<void>;
    { t.drawContent() }-> std::convertible_to<void>;
};

template<typename T>
concept Apply = requires(T t){
    { t.apply() }-> std::convertible_to<bool>;
};

template<typename T>
concept Item = requires(T t){
    { t.pos }-> std::convertible_to<ImVec2>;
    { t.size }-> std::convertible_to<ImVec2>;
    { t.is_enable }-> std::convertible_to<bool>;
};

// std::function std::bind_front && std::invoke

struct NodeBase{

};

struct NodeView{
    void draw();
    virtual void drawContent(){}
};

struct NodeExec{
    void init();
    void update();
    void transfer();
};