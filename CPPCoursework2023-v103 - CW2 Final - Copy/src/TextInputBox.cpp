#include "TextInputBox.h"

TextInputBox::TextInputBox()
{
}

//Draw current string to screen
const char* TextInputBox::GetText()
{
	return text.c_str();
}


//take in keycode, convert to character, then add to string
void TextInputBox::addKey(int keyCode)
{
	//Don't add past max length
	if (currLen == maxLen) {
		return;
	}
	text += char(keyCode);
	currLen++;
}


//if key taken in is backspace, remove last character from string
void TextInputBox::backspace()
{
	//if at min length, don't try remove more
	if (currLen == minLen) {
		return;
	}
	text.pop_back();
	currLen--;
}


