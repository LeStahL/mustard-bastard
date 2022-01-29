#include "HighscoreList.hpp"

#include <fstream>
#include <algorithm>
#include <iostream>

const std::string HighscoreList::highscoreFileName = "assets/highscore.ini";
const int HighscoreList::nEntries = 10;

HighscoreList::HighscoreList()
{
    std::ifstream t(HighscoreList::highscoreFileName);
    std::string data;
    while(t.peek() != EOF)
    {
        getline(t, data, ':');
        std::string name;
        if(data[0] == '\n')
            name = data.substr(1, std::string::npos);
        else
            name = data;

        getline(t, data, ';');
        int score = std::stoi(data);

        _entries.push_back(HighscoreListEntry(name, score));
    }

    std::sort(_entries.begin(), _entries.end(), HighscoreListEntry::compare);
}

void HighscoreList::add(std::string name, int score)
{
    _entries.push_back(HighscoreListEntry(name, score));
    std::sort(_entries.begin(), _entries.end(), HighscoreListEntry::compare);
    _entries.pop_back();

    std::ofstream t(HighscoreList::highscoreFileName);
    for (int i=0; i<_entries.size(); ++i) {
        t << _entries.at(i).name() << ":" << _entries.at(i).score() << ";\n";
    }
}

HighscoreListEntry::HighscoreListEntry(std::string name, int score)
    : _name(name)
    , _score(score)
{
}

int HighscoreListEntry::score()
{
    return _score;
}

std::string HighscoreListEntry::name()
{
    return _name;
}

bool HighscoreListEntry::compare(HighscoreListEntry a, HighscoreListEntry b)
{
    return a.score() > b.score();
}

HighscoreListEntry HighscoreList::entry(int index)
{
    return _entries.at(index);
}
