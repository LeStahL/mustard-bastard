#pragma once

#include <vector>
#include <string>

class HighscoreListEntry {
    int _score;
    std::string _name;

    public:
    HighscoreListEntry(std::string name, int score);
    static bool compare(HighscoreListEntry a, HighscoreListEntry b);
    int score();
    std::string name();
};

class HighscoreList {
    std::vector<HighscoreListEntry> _entries;

    public:
    HighscoreList();
    void add(std::string name, int score);
    HighscoreListEntry entry(int index);

    static const std::string highscoreFileName;
    static const int nEntries;
};
