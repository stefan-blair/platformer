#include <string>
#include "LoaderParams.h"

#pragma once
class TextObject
{
public:
	TextObject();
	~TextObject();

	void init(LoaderParams&, std::string&);
	void setString(std::string&);
	void draw();
private:
	LoaderParams _params;
	std::string _message;
};

