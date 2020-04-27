#include "gl_nodes_1.h"

void GlMainLoop_Func::Initialize()
{
    output_width = GetInputPinValue<int>(parent_node, 0);
    output_height = GetInputPinValue<int>(parent_node, 1);
    SetupFrameBuffer();
}

void GlMainLoop_Func::Run()
{
    int new_width = GetInputPinValue<int>(parent_node, 0);
    int new_height = GetInputPinValue<int>(parent_node, 1);
    if (new_width != output_width || new_height != output_height)
    {
        output_width = new_width;
        output_height = new_height;
        DeleteFrameBuffer();
        SetupFrameBuffer();
    }

    // Get previous viewport and set new viewport
    auto config = InstanceConfig::instance();
    GLint prev_viewport[4];
    glGetIntegerv(GL_VIEWPORT, prev_viewport);
    glViewport(0, 0, output_width, output_height);

    // Bind framebuffer
    config->current_framebuffer = "glMainLoop_" + std::to_string(parent_node->id.Get());
    GLuint new_framebuffer_id = config->GetFrameBuffer(config->current_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, new_framebuffer_id);

    // Run next node
    RunNextNodeFunc(parent_node, 0);

    // Unbind frambebuffer and return to previous viewport
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, prev_viewport[2], prev_viewport[3]);
}

void GlMainLoop_Func::Delete()
{
    DeleteFrameBuffer();
    parent_node = nullptr;
}

void GlMainLoop_Func::NoFlowUpdatePinsValues()
{

}

void GlMainLoop_Func::ChangePinType(PinKind kind, int index, PinType type)
{

}

void GlMainLoop_Func::SetupFrameBuffer()
{
    auto config = InstanceConfig::instance();
    GLuint FramebufferName;
    GLuint renderedTexture;
    GLuint depthrenderbuffer;

    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

    glGenTextures(1, &renderedTexture);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, output_width, output_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // The depth buffer
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, output_width, output_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        parent_node->error = "Somehting went wrong with Gl Main Loop!!";
        return;
    }

    config->InsertTexture("glMainLoop_" + std::to_string(parent_node->id.Get()), renderedTexture);
    config->InsertRenderBuffer("glMainLoop_" + std::to_string(parent_node->id.Get()), depthrenderbuffer);
    config->InsertFrameBuffer("glMainLoop_" + std::to_string(parent_node->id.Get()), FramebufferName);
    parent_node->info = "Texture name: 'glMainLoop_" + std::to_string(parent_node->id.Get())+"'";
}

void GlMainLoop_Func::DeleteFrameBuffer()
{
    auto config = InstanceConfig::instance();
    config->DeleteTexture("glMainLoop_" + std::to_string(parent_node->id.Get()));
    config->DeleteRenderBuffer("glMainLoop_" + std::to_string(parent_node->id.Get()));
    config->DeleteFrameBuffer("glMainLoop_" + std::to_string(parent_node->id.Get()));
}

std::shared_ptr<Node> GlMainLoop(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "GL Main Loop", ImColor(255, 128, 128)));
    s_Nodes.back()->inputs.emplace_back(new PinValue<int>(s_Nodes.back()->inputs.size(), GetNextId(), "Width", PinType::Int, 1920));
    s_Nodes.back()->inputs.emplace_back(new PinValue<int>(s_Nodes.back()->inputs.size(), GetNextId(), "Height", PinType::Int, 1080));
    s_Nodes.back()->outputs.emplace_back(new BasePin(s_Nodes.back()->outputs.size(), GetNextId(), "Next", PinType::Flow));

    s_Nodes.back()->node_funcs = std::make_shared<GlMainLoop_Func>();
    std::dynamic_pointer_cast<GlMainLoop_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void GlClear_Func::Initialize()
{
}

void GlClear_Func::Run()
{
    float r = GetInputPinValue<float>(parent_node, 1);
    float g = GetInputPinValue<float>(parent_node, 2);
    float b = GetInputPinValue<float>(parent_node, 3);
    float a = GetInputPinValue<float>(parent_node, 4);
    if (r < 0)
        r = 0;
    if (r > 1)
        r = 1;
    if (g < 0)
        g = 0;
    if (g > 1)
        g = 1;
    if (b < 0)
        b = 0;
    if (b > 1)
        b = 1;
    if (a < 0)
        a = 0;
    if (a > 1)
        a = r;
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
    RunNextNodeFunc(parent_node, 0);
}

void GlClear_Func::Delete()
{
    parent_node = nullptr;
}

void GlClear_Func::NoFlowUpdatePinsValues()
{

}

void GlClear_Func::ChangePinType(PinKind kind, int index, PinType type)
{

}

std::shared_ptr<Node> GlClearNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "glClrear"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(s_Nodes.back()->inputs.size(), GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "R", PinType::Float, 0));
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "G", PinType::Float, 0));
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "B", PinType::Float, 0));
    s_Nodes.back()->inputs.emplace_back(new PinValue<float>(s_Nodes.back()->inputs.size(), GetNextId(), "A", PinType::Float, 0));
    s_Nodes.back()->outputs.emplace_back(new BasePin(s_Nodes.back()->outputs.size(), GetNextId(), "Next", PinType::Flow));

    s_Nodes.back()->node_funcs = std::make_shared<GlClear_Func>();
    std::dynamic_pointer_cast<GlClear_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void GlRenderToTexture_Func::Initialize()
{
    output_width = GetInputPinValue<int>(parent_node, 1);
    output_height = GetInputPinValue<int>(parent_node, 2);
    SetupFrameBuffer();
}

void GlRenderToTexture_Func::Run()
{
    int new_width = GetInputPinValue<int>(parent_node, 1);
    int new_height = GetInputPinValue<int>(parent_node, 2);
    if (new_width != output_width || new_height != output_height)
    {
        output_width = new_width;
        output_height = new_height;
        DeleteFrameBuffer();
        SetupFrameBuffer();
    }

    // Get previous viewport and set new viewport
    auto config = InstanceConfig::instance();
    GLint prev_viewport[4];
    glGetIntegerv(GL_VIEWPORT, prev_viewport);
    glViewport(0, 0, output_width, output_height);

    // Bind framebuffer
    config->framebuffer_stack.push(config->current_framebuffer);
    config->current_framebuffer = "glRenderToTexture_" + std::to_string(parent_node->id.Get());
    GLuint new_framebuffer_id = config->GetFrameBuffer(config->current_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, new_framebuffer_id);

    // Run next node
    RunNextNodeFunc(parent_node, 0);

    // Return to previous viewport and framebuffer
    std::string prev_framebuffer = config->framebuffer_stack.top();
    config->framebuffer_stack.pop();
    GLuint prev_framebuffer_id = config->GetFrameBuffer(prev_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, prev_framebuffer_id);
    glViewport(0, 0, prev_viewport[2], prev_viewport[3]);

    // Run next node
    RunNextNodeFunc(parent_node, 1);
}

void GlRenderToTexture_Func::Delete()
{
    DeleteFrameBuffer();
    parent_node = nullptr;
}

void GlRenderToTexture_Func::NoFlowUpdatePinsValues()
{

}

void GlRenderToTexture_Func::ChangePinType(PinKind kind, int index, PinType type)
{

}

void GlRenderToTexture_Func::SetupFrameBuffer()
{
    auto config = InstanceConfig::instance();
    GLuint FramebufferName;
    GLuint renderedTexture;
    GLuint depthrenderbuffer;

    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

    glGenTextures(1, &renderedTexture);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, output_width, output_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // The depth buffer
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, output_width, output_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        parent_node->error = "Somehting went wrong with Gl Redner To Texture!!";
        return;
    }

    config->InsertTexture("glRenderToTexture_" + std::to_string(parent_node->id.Get()), renderedTexture);
    config->InsertRenderBuffer("glRenderToTexture_" + std::to_string(parent_node->id.Get()), depthrenderbuffer);
    config->InsertFrameBuffer("glRenderToTexture_" + std::to_string(parent_node->id.Get()), FramebufferName);
    parent_node->info = "Texture name: 'glRenderToTexture_" + std::to_string(parent_node->id.Get())+"'";
}

void GlRenderToTexture_Func::DeleteFrameBuffer()
{
    auto config = InstanceConfig::instance();
    config->DeleteTexture("glRenderToTexture_" + std::to_string(parent_node->id.Get()));
    config->DeleteRenderBuffer("glRenderToTexture_" + std::to_string(parent_node->id.Get()));
    config->DeleteFrameBuffer("glRenderToTexture_" + std::to_string(parent_node->id.Get()));
}

std::shared_ptr<Node> GlRenderToTexture(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "GL Render To Texture"));
    s_Nodes.back()->inputs.emplace_back(new BasePin(s_Nodes.back()->inputs.size(), GetNextId(), "Enter", PinType::Flow));
    s_Nodes.back()->inputs.emplace_back(new PinValue<int>(s_Nodes.back()->inputs.size(), GetNextId(), "Width", PinType::Int, 1920));
    s_Nodes.back()->inputs.emplace_back(new PinValue<int>(s_Nodes.back()->inputs.size(), GetNextId(), "Height", PinType::Int, 1080));
    s_Nodes.back()->outputs.emplace_back(new BasePin(s_Nodes.back()->outputs.size(), GetNextId(), "Render Body", PinType::Flow));
    s_Nodes.back()->outputs.emplace_back(new BasePin(s_Nodes.back()->outputs.size(), GetNextId(), "After Rendering", PinType::Flow));

    s_Nodes.back()->node_funcs = std::make_shared<GlRenderToTexture_Func>();
    std::dynamic_pointer_cast<GlRenderToTexture_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}



void GlNodes1_SearchSetup(std::vector<SearchNodeObj>& search_nodes_vector)
{
    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_1 = GlClearNode;
    std::vector<std::string> keywords_1{ "glClear", "Gl", "gl", "Clear" };
    search_nodes_vector.push_back(SearchNodeObj("GL Clear", keywords_1, func_1));

    std::function<std::shared_ptr<Node>(std::vector<std::shared_ptr<Node>>&)> func_2 = GlRenderToTexture;
    std::vector<std::string> keywords_2{ "glRenderToTexture", "Gl", "gl", "Render", "To", "Texture" };
    search_nodes_vector.push_back(SearchNodeObj("GL Render To Texture", keywords_2, func_2));
}