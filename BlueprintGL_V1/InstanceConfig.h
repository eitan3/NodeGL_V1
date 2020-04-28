#pragma once
#ifndef INSTANCECONFIG_H
#define INSTANCECONFIG_H
#include <memory>
#include <vector>
#include <map>
#include <stack> 
#include <gl/gl3w.h>

#include "bp_structs.h"
#include "objects/texture_object.h"
#include "objects/renderbuffer_object.h"
#include "objects/framebuffer_object.h"

class InstanceConfig
{
public:

	InstanceConfig()
	{

	}

	InstanceConfig(InstanceConfig const&) = delete;
	InstanceConfig& operator=(InstanceConfig const&) = delete;

	static std::shared_ptr<InstanceConfig> instance()
	{
		static std::shared_ptr<InstanceConfig> s{ new InstanceConfig };
		return s;
	}

	bool InsertTexture(std::string name, std::shared_ptr<TextureObject> texture_obj)
	{
		if (texture_map.count(name) == 0)
		{
			texture_map.insert(std::pair<std::string, std::shared_ptr<TextureObject>>(name, texture_obj));
			return true;
		}
		return false;
	}

	bool InsertRenderBuffer(std::string name, std::shared_ptr<RenderBufferObject> renderbuffer_obj)
	{
		if (renderbuffer_map.count(name) == 0)
		{
			renderbuffer_map.insert(std::pair<std::string, std::shared_ptr<RenderBufferObject>>(name, renderbuffer_obj));
			return true;
		}
		return false;
	}

	bool InsertFrameBuffer(std::string name, std::shared_ptr<FrameBufferObject> framebuffer_obj)
	{
		if (framebuffer_map.count(name) == 0)
		{
			framebuffer_map.insert(std::pair<std::string, std::shared_ptr<FrameBufferObject>>(name, framebuffer_obj));
			return true;
		}
		return false;
	}

	std::shared_ptr<TextureObject> GetTexture(std::string name)
	{
		if (texture_map.count(name) > 0)
			return texture_map.at(name);
		return nullptr;
	}

	std::shared_ptr<RenderBufferObject> GetRenderBuffer(std::string name)
	{
		if (renderbuffer_map.count(name) > 0)
			return renderbuffer_map.at(name);
		return nullptr;
	}

	std::shared_ptr<FrameBufferObject> GetFrameBuffer(std::string name)
	{
		if (framebuffer_map.count(name) > 0)
			return framebuffer_map.at(name);
		return nullptr;
	}

	bool DeleteTexture(std::string name)
	{
		if (texture_map.count(name) > 0)
		{
			texture_map.erase(name);
		}
		return false;
	}

	bool DeleteRenderBuffer(std::string name)
	{
		if (renderbuffer_map.count(name) > 0)
		{
			renderbuffer_map.erase(name);
		}
		return false;
	}

	bool DeleteFrameBuffer(std::string name)
	{
		if (framebuffer_map.count(name) > 0)
		{
			framebuffer_map.erase(name);
		}
		return false;
	}

	std::vector<std::string>  GetTextureMapKeys()
	{
		std::vector<std::string> v;
		for (std::map<std::string, std::shared_ptr<TextureObject>>::iterator it = texture_map.begin(); it != texture_map.end(); ++it) {
			v.push_back(it->first);
		}
		return v;
	}

	std::vector<std::string>  GetRenderBufferMapKeys()
	{
		std::vector<std::string> v;
		for (std::map<std::string, std::shared_ptr<RenderBufferObject>>::iterator it = renderbuffer_map.begin(); it != renderbuffer_map.end(); ++it) {
			v.push_back(it->first);
		}
		return v;
	}

	std::vector<std::string>  GetFrameBufferMapKeys()
	{
		std::vector<std::string> v;
		for (std::map<std::string, std::shared_ptr<FrameBufferObject>>::iterator it = framebuffer_map.begin(); it != framebuffer_map.end(); ++it) {
			v.push_back(it->first);
		}
		return v;
	}

	std::vector< std::shared_ptr<Node>> s_Nodes;
	std::vector<std::shared_ptr<Link>> s_Links;

	std::string current_framebuffer = "";

	std::stack<std::string> framebuffer_stack;

private:
	std::map<std::string, std::shared_ptr<TextureObject>> texture_map;
	std::map<std::string, std::shared_ptr<RenderBufferObject>> renderbuffer_map;
	std::map<std::string, std::shared_ptr<FrameBufferObject>> framebuffer_map;
};

#endif