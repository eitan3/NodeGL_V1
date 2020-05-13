#pragma once
#ifndef EDITORCONFIG_H
#define EDITORCONFIG_H
#include <memory>

class EditorConfig
{
public:

	EditorConfig()
	{

	}

	EditorConfig(EditorConfig const&) = delete;
	EditorConfig& operator=(EditorConfig const&) = delete;

	static std::shared_ptr<EditorConfig> instance()
	{
		static std::shared_ptr<EditorConfig> s{ new EditorConfig };
		return s;
	}


	bool showCreatePlaceholderWindow = false;
	bool showSelectPlaceholderWindow = false;
	bool showRenamePlaceholderWindow = false;
	bool showDeletePlaceholderWindow = false;
};

#endif
