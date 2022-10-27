#include<fmt/core.h>
#include<memory>
#include"imgui.h"
#include"core/scene.hpp"
#include"core/handle.cpp"

struct Test
{
    void Show() {
        ImGui::Begin("test");

        // ImGui::Selectable
        auto draw_list = ImGui::GetWindowDrawList();
        draw_list->AddRectFilled(ImVec2(100,100), ImVec2(300,300), IM_COL32_WHITE);
        ImGui::PushID(1);

        ImGui::PopID();
        float a;
        ImGui::InputFloat("test1",&a);

        ImGui::End();
    }
};


int main() {
    fmt::print("start\n");

    auto scene_ptr = std::make_shared<Scene>();
    auto test_ptr = std::make_unique<Test>();
    scene_ptr->init();
    handle(std::move(scene_ptr));

    return 0;
}

/*
    the lost of channelSetCurrent
*/