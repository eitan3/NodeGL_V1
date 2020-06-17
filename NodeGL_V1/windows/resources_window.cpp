#include "resources_window.h"


imgui_addons::ImGuiFileBrowser resource_file_dialog;
bool showFileBrowserWindow = false;

std::string FileReaderRawData()
{
    ImGui::OpenPopup("Open File");
    std::string ret_data = "";
    if (resource_file_dialog.showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".jpg,.jpeg,.fbx"))
    {
        //std::cout << resource_file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
        //std::cout << resource_file_dialog.selected_path << std::endl;    // The absolute path to the selected file

        std::string raw_file_data;
        std::ifstream file(resource_file_dialog.selected_path, std::ios::in);

        if (!file.good()) {
            std::cout << "Can't read file " << resource_file_dialog.selected_path.c_str() << std::endl;
            std::terminate();
        }

        file.seekg(0, std::ios::end);
        raw_file_data.resize((unsigned int)file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&raw_file_data[0], raw_file_data.size());
        file.close();

        ret_data = raw_file_data;

        showFileBrowserWindow = false;
    }
    else
    {
        if (resource_file_dialog.is_cancel)
        {
            showFileBrowserWindow = false;
        }
    }

    return ret_data;
}

void UtilsShowResourcesWindow()
{
    /*
    auto editor_config = EditorConfig::instance();
    auto config = InstanceConfig::instance();
    if (!ImGui::Begin("Resources", &editor_config->showResourcesWindow))
    {
        ImGui::End();
        return;
    }

    ImGui::SetWindowSize(ImVec2(512, 350));
    auto paneWidth = ImGui::GetContentRegionAvailWidth();

    ImGui::BeginHorizontal("##resources_buttons_panel", ImVec2(paneWidth, 0), 1.0f);
    if (ImGui::Button("Import"))
    {
        showFileBrowserWindow = true;
    }
    if (ImGui::Button("Rename"))
    {

    }
    if (ImGui::Button("Close"))
    {
        editor_config->showResourcesWindow = false;
    }
    ImGui::EndHorizontal();

    ImGui::BeginHorizontal("##resources_main_panel", ImVec2(paneWidth, 0), 1.0f);
    
    ImGui::EndHorizontal();

    if (showFileBrowserWindow)
        FileReaderRawData();

    ImGui::End();
    */
}