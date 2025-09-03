#pragma once
#include "header.h"
#include "DrawingSurface.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class GameEngine;



class Scoreboard 
{
public:
    Scoreboard(GameEngine*, int, int, int, int);

    ~Scoreboard() {
        delete scoreboardSurface;

    }

    //structure for store players taken from file
    struct Player {
        string name;
        string score;
    };


    void drawBoard();

    void drawText(int x, int y, const char* text, int colour);

    //Set text pos based on coords in grid
    void setText(int x, int y, const char*);

    void drawTitles();

    void drawNumbers();

    void drawLineAcross(double y);

    void drawLineVert(double x);

    void drawAllLines();

    void getScores();

    void drawScores();

private:
    int drawWidth;
    int drawHeight;
    int minX;
    int minY;
    int maxX;
    int maxY;

    double vertSplit;
    double gapAcross;

    vector<Player> playerList;
    
    Font* font;
    GameEngine* engine;
    DrawingSurface* scoreboardSurface;
};

