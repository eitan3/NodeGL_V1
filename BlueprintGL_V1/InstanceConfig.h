#pragma once
#ifndef INSTANCECONFIG_H
#define INSTANCECONFIG_H
#include <memory>
#include <vector>
#include <map>
#include <stack> 
#include <gl/gl3w.h>
#include "bp_structs.h"

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

	bool InsertTexture(std::string name, GLuint id)
	{
		if (texture_map.count(name) == 0)
		{
			texture_map.insert(std::pair<std::string, GLuint>(name, id));
			return true;
		}
		return false;
	}

	bool InsertRenderBuffer(std::string name, GLuint id)
	{
		if (renderbuffer_map.count(name) == 0)
		{
			renderbuffer_map.insert(std::pair<std::string, GLuint>(name, id));
			return true;
		}
		return false;
	}

	bool InsertFrameBuffer(std::string name, GLuint id)
	{
		if (framebuffer_map.count(name) == 0)
		{
			framebuffer_map.insert(std::pair<std::string, GLuint>(name, id));
			return true;
		}
		return false;
	}

	GLuint GetTexture(std::string name)
	{
		if (texture_map.count(name) > 0)
			return texture_map.at(name);
		return 0;
	}

	GLuint GetRenderBuffer(std::string name)
	{
		if (renderbuffer_map.count(name) > 0)
			return renderbuffer_map.at(name);
		return 0;
	}

	GLuint GetFrameBuffer(std::string name)
	{
		if (framebuffer_map.count(name) > 0)
			return framebuffer_map.at(name);
		return 0;
	}

	bool DeleteTexture(std::string name)
	{
		if (texture_map.count(name) > 0)
		{
			GLuint texture_id = GetTexture(name);
			glDeleteTextures(1, &texture_id);
			texture_map.erase(name);
		}
		return false;
	}

	bool DeleteRenderBuffer(std::string name)
	{
		if (renderbuffer_map.count(name) > 0)
		{
			GLuint renderbuffer_id = GetRenderBuffer(name);
			glDeleteRenderbuffers(1, &renderbuffer_id);
			renderbuffer_map.erase(name);
		}
		return false;
	}

	bool DeleteFrameBuffer(std::string name)
	{
		if (framebuffer_map.count(name) > 0)
		{
			GLuint framebuffer_id = GetFrameBuffer(name);
			glDeleteFramebuffers(1, &framebuffer_id);
			framebuffer_map.erase(name);
		}
		return false;
	}

	std::vector<std::string>  GetTextureMapKeys()
	{
		std::vector<std::string> v;
		for (std::map<std::string, GLuint>::iterator it = texture_map.begin(); it != texture_map.end(); ++it) {
			v.push_back(it->first);
		}
		return v;
	}

	std::vector<std::string>  GetRenderBufferMapKeys()
	{
		std::vector<std::string> v;
		for (std::map<std::string, GLuint>::iterator it = renderbuffer_map.begin(); it != renderbuffer_map.end(); ++it) {
			v.push_back(it->first);
		}
		return v;
	}

	std::vector<std::string>  GetFrameBufferMapKeys()
	{
		std::vector<std::string> v;
		for (std::map<std::string, GLuint>::iterator it = framebuffer_map.begin(); it != framebuffer_map.end(); ++it) {
			v.push_back(it->first);
		}
		return v;
	}

	std::vector< std::shared_ptr<Node>> s_Nodes;
	std::vector<std::shared_ptr<Link>> s_Links;

	std::string current_framebuffer = "";

	std::stack<std::string> framebuffer_stack;

private:
	std::map<std::string, GLuint> texture_map;
	std::map<std::string, GLuint> renderbuffer_map;
	std::map<std::string, GLuint> framebuffer_map;
};

#endif