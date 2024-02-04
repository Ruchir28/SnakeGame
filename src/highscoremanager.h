#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H
#include <fstream>
#include <iostream>
#include <sstream>


class HighScoreManager {
    public:
        HighScoreManager();
        ~HighScoreManager();
        void addScore(std::string name,int score);
        void printHighScores();
        void saveHighScores();
        void loadHighScores();
    private:
        std::vector<std::pair<std::string, int>> m_highScores;
};

#endif