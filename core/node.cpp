#include "node.hpp"
#include "scene.hpp"

Node::Node(
    std::weak_ptr<Scene> _scene,
    std::shared_ptr<Context> _context,
    const std::string_view &_name,
    ImVec2 _pos)
    :scene(std::move(_scene)),context(_context),name(_name),pos(_pos)
{
    this->id = _context->genId();
    fmt::print("node get{}\n",this->id);
}

void Node::setSocketsNum(int _input_sockets_num, int _output_sockets_num){
    this->input_sockets_num = _input_sockets_num;
    this->ouput_sockets_num = _output_sockets_num;
}

void Node::setNodeSize(int _size_x, int _size_y){
    this->size = ImVec2(_size_x, _size_y);
}

void Node::init(){}

void Node::draw() {
    
    auto draw_list = ImGui::GetWindowDrawList();
    auto im_id = ImGui::GetID(this->id.c_str());
    ImGuiIO& io = ImGui::GetIO();

    auto node_start_pos = this->pos + this->context->vp_trans;

    /*
        virtual add content
        custom view
        @todo
    */
    draw_list->ChannelsSetCurrent(3);
    ImGui::SetCursorScreenPos(node_start_pos + ImVec2(5,5));
    ImGui::BeginGroup();
    this->drawContent();
    ImGui::EndGroup();

    // resize Item Rect by Group-content
    // if (this->is_resize)
    //     this->size = ImGui::GetItemRectSize() + ImVec2(10,10);


    /// draw Node body View
    draw_list->ChannelsSetCurrent(1);
    /// draw Node head
    draw_list->AddRectFilled(
        node_start_pos,
        node_start_pos + ImVec2(this->size.x, this->node_head_height),
        node_head_color
    );

    /// draw Node body
    draw_list->AddRectFilled(
        node_start_pos + ImVec2(0, this->node_head_height),
        node_start_pos + ImVec2(0, this->node_head_height) + this->size,
        node_body_color
    );

    /// add Node body Item
    auto whole_size = this->size + ImVec2(0, this->node_head_height);
    ImVec2 size = ImGui::CalcItemSize(whole_size, 0.0f, 0.0f);
    ImRect bb(node_start_pos, node_start_pos + size);
    ImGui::ItemSize(size);
    ImGui::ItemAdd(bb ,im_id);

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, im_id, &hovered, &held);
    
    // response Node basic event
    // @test
    if(ImGui::IsItemHovered())
    {
        auto test_size = ImGui::GetItemRectSize();
        draw_list->AddRectFilled(
            node_start_pos,
            node_start_pos + test_size,
            node_body_color
        );
    }
    if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0))
    {
        fmt::print("DEBUG: click Node:{}\n", this->id);
        this->context->last_selected_node_id = this->id;
    }
    // move node
    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
    {
        this->pos = this->pos + io.MouseDelta;
    }

}