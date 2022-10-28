#include "scene.hpp"
#include "utils.hpp"

Scene::Scene() {
    this->context = std::make_shared<Context>();
}

void Scene::init(){
    auto lambda = [](std::shared_ptr<Node> node){
        node->setSocketsNum(2,5);
        node->setNodeSize(140, 60);
        node->setPos({100,200});
        node->node_body_color = IM_COL32(200, 200, 150, 200);
    };
    auto node = this->addNode(lambda);
}

void Scene::addLink(){

}

auto Scene::addNode(const std::function<void(std::shared_ptr<Node>)>& init_func) -> std::shared_ptr<Node>
{
    auto node = std::make_shared<Node>(this->weak_from_this(), this->context);
    auto temp_id = node->id; 

    // lambda to define the node properties
    init_func(node);
    node->init();
    
    // scene control the nodes
    this->map_nodes.insert({std::move(temp_id), node});
    return std::move(node);
}

void Scene::drawBackground(){
    auto draw_list = ImGui::GetWindowDrawList();
    
    ImVec2 win_pos = ImGui::GetCursorScreenPos();
    ImVec2 canvas_sz = ImGui::GetWindowSize();

    for (float x = fmodf(this->context->vp_trans.x, scene_grid_sz); x < canvas_sz.x; x += scene_grid_sz)
        draw_list->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, canvas_sz.y) + win_pos, scene_grid_color);
    for (float y = fmodf(this->context->vp_trans.y, scene_grid_sz); y < canvas_sz.y; y += scene_grid_sz)
        draw_list->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(canvas_sz.x, y) + win_pos, scene_grid_color);

}

void Scene::drawNodes(){
    auto draw_list = ImGui::GetWindowDrawList();
    ImGuiIO& io = ImGui::GetIO();

    for(auto &[node_id, node] : map_nodes) {

        if(node->is_enable == false)
            continue;

        ImGui::PushID(ImGui::GetID(node_id.c_str()));

        // draw socket first to response the event
        // draw_list->ChannelsSetCurrent(3);
        // this->drawNodeInputSockets(node);
        // this->drawNodeOuputSockets(node);
        
        // draw nodes
        draw_list->ChannelsSetCurrent(2);
        node->draw();

        ImGui::PopID();
    }
}

void Scene::handleEvent() {
    ImGuiIO& io = ImGui::GetIO();

    if (ImGui::IsMouseClicked(1)){
        for(auto i=0;i<100;i++){
            auto lambda = [i](std::shared_ptr<Node> node){
                node->setName("hello");
                node->setPos(ImGui::GetMousePos()+ImVec2(i*1,i*1));
            };
            this->addNode(std::bind_front(lambda));
        }
        // this->open_menu = !this->open_menu;
    }

    /// adjust viewport zoom
    if(ImGui::IsMouseDown(1) && io.MouseWheel != 0) {
        this->context->changeViewportScale(io.MouseWheel * 0.1);

        //@todo change all node&socket pos&size
        // this->adjustNodesView()
        fmt::print("{}\n",this->context->vp_scale);
    }

    // adjust viewport translate
    if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f)){
        this->context->vp_trans = this->context->vp_trans + io.MouseDelta;
    }
}

void Scene::show(){
    ImGui::Begin("hello");
    {

        ImGui::Text("Icarus average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Icraus Scene Node nums:%ld", this->map_nodes.size());

        auto draw_list = ImGui::GetWindowDrawList();

        auto cursor_global_pos = ImGui::GetCursorPos();
        auto cursor_screen_pos = ImGui::GetCursorScreenPos();
        draw_list->AddCircle(cursor_screen_pos, 5.0f, IM_COL32_WHITE);


        /// draw Layer: 5 forward / 0 background
        /// back 0
        /// link 1
        /// node 2
        /// cont 3
        /// sock 4
        this->handleEvent();

        //@todo trans to outside to avoid splice/merge lost
        draw_list->ChannelsSplit(5);
        {
            draw_list->ChannelsSetCurrent(0);
            this->drawBackground();

            draw_list->ChannelsSetCurrent(2);
            this->drawNodes();



        }
        draw_list->ChannelsMerge();

    }
    ImGui::End();
}