#include "highscoremanager.h"
#include <algorithm>
HighScoreManager::HighScoreManager()
{
    // Load high scores from file
    std::ifstream file("../scores/high_score.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string name;
            int score;
            iss >> name >> score;
            m_highScores.push_back(std::make_pair(name, score));
        }
        file.close();
    }
    else
    {
        std::cerr << "Failed to open highscores.txt" << std::endl;
    }
}

HighScoreManager::~HighScoreManager()
{
    saveHighScores();
}

void HighScoreManager::addScore(std::string name,int score)
{
    m_highScores.push_back(std::make_pair(name, score));
    std::sort(m_highScores.begin(), m_highScores.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });
    printHighScores();
}

void HighScoreManager::printHighScores()
{
    std::cout << "High Scores" << std::endl;
    for (auto &score : m_highScores)
    {
        std::cout << score.first << " " << score.second << std::endl;
    }
}

void HighScoreManager::saveHighScores()
{
    std::ofstream file("../scores/high_score.txt");
    std::sort(m_highScores.begin(), m_highScores.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });
    if (file.is_open())
    {
        for (int i=0;i<std::min(5,(int)m_highScores.size());i++)
        {
            file << m_highScores[i].first << " " << m_highScores[i].second << std::endl;
        }
        file.close();
    }
    else
    {
        std::cerr << "Failed to open highscores.txt" << std::endl;
    }
}