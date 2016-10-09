#include "TextObject.h"
#include "Camera.h"

TextObject::TextObject() :
_params(0, 0, 0, 0, 0)
{
}


TextObject::~TextObject()
{
}

void TextObject::init(LoaderParams& params, std::string& message){
	_params = params;
	_message = message;
}
void TextObject::setString(std::string& message){
	_message = message;
}
void TextObject::draw(){
	Camera::drawText(_params, _message);
}