#pragma once
#include "header.h"
#include "BaseButton.h"

class TextInputBox
{
public:
    TextInputBox();
    
    //draw current string onto screen
    const char* GetText();

    void addKey(int keyCode);


    void backspace();

private:
    std::string text;

    int currLen = 0;
    int maxLen = 8;
    int minLen = 0;

};

