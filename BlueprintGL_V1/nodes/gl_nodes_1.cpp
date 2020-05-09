#include "gl_nodes_1.h"

void GlMainLoop_Func::Initialize()
{
    object_prefix = "glMainLoop_" + std::to_string(parent_node->id.Get());
    output_width = GetInputPinValue<int>(parent_node, "width");
    output_height = GetInputPinValue<int>(parent_node, "height");
    SetupFrameBuffer();
}

void GlMainLoop_Func::Run()
{
    int new_width = GetInputPinValue<int>(parent_node, "width");
    int new_height = GetInputPinValue<int>(parent_node, "height");
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
    config->current_framebuffer = object_prefix;
    GLuint new_framebuffer_id = config->GetFrameBuffer(config->current_framebuffer)->object_id;
    glBindFramebuffer(GL_FRAMEBUFFER, new_framebuffer_id);

    std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<TextureObject>>>(parent_node->outputs.at("texture_out"));
    output_pin->value = config->GetTexture(object_prefix);

    // Run next node
    RunNextNodeFunc(parent_node, "next");

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

void GlMainLoop_Func::SetupFrameBuffer()
{
    auto config = InstanceConfig::instance();
    GLuint framebuffer_id;
    GLuint renderedTexture;
    GLuint depthrenderbuffer;

    glGenFramebuffers(1, &framebuffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

    glGenTextures(1, &renderedTexture);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, output_width, output_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

    // The depth buffer
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, output_width, output_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        parent_node->error = "Somehting went wrong with Gl Main Loop!!";
        return;
    }

    config->InsertTexture(object_prefix, std::make_shared<TextureObject>(object_prefix, renderedTexture, output_width, output_height));
    config->InsertRenderBuffer(object_prefix, std::make_shared<RenderBufferObject>(object_prefix, depthrenderbuffer, output_width, output_height));
    config->InsertFrameBuffer(object_prefix, std::make_shared<FrameBufferObject>(object_prefix, framebuffer_id));
    parent_node->info = "Texture name: 'glMainLoop_" + std::to_string(parent_node->id.Get())+"'";
}

void GlMainLoop_Func::DeleteFrameBuffer()
{
    auto config = InstanceConfig::instance();
    config->DeleteTexture(object_prefix);
    config->DeleteRenderBuffer(object_prefix);
    config->DeleteFrameBuffer(object_prefix);
}

std::shared_ptr<Node> GlMainLoop(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "GL Main Loop", ImColor(255, 128, 128)));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("width", new PinValue<int>("width", 0, GetNextId(), "Width", PinType::Int, 1920)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("height", new PinValue<int>("height", 1, GetNextId(), "Height", PinType::Int, 1080)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>>>("texture_out", new PinValue<std::shared_ptr<TextureObject>>("texture_out", 1, GetNextId(), "Texture Object", PinType::TextureObject, nullptr)));

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
    float r = GetInputPinValue<float>(parent_node, "r");
    float g = GetInputPinValue<float>(parent_node, "g");
    float b = GetInputPinValue<float>(parent_node, "b");
    float a = GetInputPinValue<float>(parent_node, "a");
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
    RunNextNodeFunc(parent_node, "next");
}

void GlClear_Func::Delete()
{
    parent_node = nullptr;
}

void GlClear_Func::NoFlowUpdatePinsValues()
{

}

std::shared_ptr<Node> GlClearNode(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "glClrear"));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("r", new PinValue<float>("r", 1, GetNextId(), "R", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("g", new PinValue<float>("g", 2, GetNextId(), "G", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("b", new PinValue<float>("b", 3, GetNextId(), "B", PinType::Float, 0)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<float>>>("a", new PinValue<float>("a", 4, GetNextId(), "A", PinType::Float, 0)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 0, GetNextId(), "Next", PinType::Flow)));

    s_Nodes.back()->inputs.at("r")->always_expose = false;
    s_Nodes.back()->inputs.at("g")->always_expose = false;
    s_Nodes.back()->inputs.at("b")->always_expose = false;
    s_Nodes.back()->inputs.at("a")->always_expose = false;

    s_Nodes.back()->node_funcs = std::make_shared<GlClear_Func>();
    std::dynamic_pointer_cast<GlClear_Func>(s_Nodes.back()->node_funcs)->parent_node = s_Nodes.back();

    s_Nodes.back()->node_funcs->Initialize();

    BuildNode(s_Nodes.back());

    return s_Nodes.back();
}





void GlRenderToTexture_Func::Initialize()
{
    object_prefix = "glRenderToTexture_" + std::to_string(parent_node->id.Get());
    output_width = GetInputPinValue<int>(parent_node, "width");
    output_height = GetInputPinValue<int>(parent_node, "height");
    SetupFrameBuffer();
}

void GlRenderToTexture_Func::Run()
{
    int new_width = GetInputPinValue<int>(parent_node, "width");
    int new_height = GetInputPinValue<int>(parent_node, "height");
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
    config->current_framebuffer = object_prefix;
    GLuint new_framebuffer_id = config->GetFrameBuffer(config->current_framebuffer)->object_id;
    glBindFramebuffer(GL_FRAMEBUFFER, new_framebuffer_id);

    // Run next node
    RunNextNodeFunc(parent_node, "render_body");

    // Return to previous viewport and framebuffer
    std::string prev_framebuffer = config->framebuffer_stack.top();
    config->current_framebuffer = prev_framebuffer;
    config->framebuffer_stack.pop();
    GLuint prev_framebuffer_id = config->GetFrameBuffer(prev_framebuffer)->object_id;
    glBindFramebuffer(GL_FRAMEBUFFER, prev_framebuffer_id);
    glViewport(0, 0, prev_viewport[2], prev_viewport[3]);

    std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>> output_pin = std::dynamic_pointer_cast<PinValue<std::shared_ptr<TextureObject>>>(parent_node->outputs.at("texture_out"));
    output_pin->value = config->GetTexture(object_prefix);

    // Run next node
    RunNextNodeFunc(parent_node, "next");
}

void GlRenderToTexture_Func::Delete()
{
    DeleteFrameBuffer();
    parent_node = nullptr;
}

void GlRenderToTexture_Func::NoFlowUpdatePinsValues()
{

}

void GlRenderToTexture_Func::SetupFrameBuffer()
{
    auto config = InstanceConfig::instance();
    GLuint framebuffer_id;
    GLuint renderedTexture;
    GLuint depthrenderbuffer;

    glGenFramebuffers(1, &framebuffer_id);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);

    glGenTextures(1, &renderedTexture);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, output_width, output_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

    // The depth buffer
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, output_width, output_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        parent_node->error = "Somehting went wrong with Gl Redner To Texture!!";
        return;
    }

    config->InsertTexture(object_prefix, std::make_shared<TextureObject>(object_prefix, renderedTexture, output_width, output_height));
    config->InsertRenderBuffer(object_prefix, std::make_shared<RenderBufferObject>(object_prefix, depthrenderbuffer, output_width, output_height));
    config->InsertFrameBuffer(object_prefix, std::make_shared<FrameBufferObject>(object_prefix, framebuffer_id));
    parent_node->info = "Texture name: 'glRenderToTexture_" + std::to_string(parent_node->id.Get())+"'";
}

void GlRenderToTexture_Func::DeleteFrameBuffer()
{
    auto config = InstanceConfig::instance();
    config->DeleteTexture(object_prefix);
    config->DeleteRenderBuffer(object_prefix);
    config->DeleteFrameBuffer(object_prefix);
}

std::shared_ptr<Node> GlRenderToTexture(std::vector<std::shared_ptr<Node>>& s_Nodes)
{
    s_Nodes.emplace_back(new Node(GetNextId(), "GL Render To Texture"));

    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("enter", new BasePin("enter", 0, GetNextId(), "Enter", PinType::Flow)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("width", new PinValue<int>("width", 1, GetNextId(), "Width", PinType::Int, 1920)));
    s_Nodes.back()->inputs.insert(std::pair<std::string, std::shared_ptr<PinValue<int>>>("height", new PinValue<int>("height", 2, GetNextId(), "Height", PinType::Int, 1080)));

    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("render_body", new BasePin("render_body", 0, GetNextId(), "Render Body", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<BasePin>>("next", new BasePin("next", 1, GetNextId(), "After Rendering", PinType::Flow)));
    s_Nodes.back()->outputs.insert(std::pair<std::string, std::shared_ptr<PinValue<std::shared_ptr<TextureObject>>>>("texture_out", new PinValue<std::shared_ptr<TextureObject>>("texture_out", 2, GetNextId(), "Texture Object", PinType::TextureObject, nullptr)));

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