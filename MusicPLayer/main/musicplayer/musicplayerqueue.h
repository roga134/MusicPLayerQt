#ifndef MUSICPLAYERQUEUE_H
#define MUSICPLAYERQUEUE_H

#include <list>
#include <vector>
#include <random>
#include <algorithm>
#include <stack>
#include <queue>
#include <QUrl>

class MusicPlayerQueue
{
public:
    std::queue<int> upcomingIndices;
    std::stack<int> historyIndices;

    void initialize(const std::list<QUrl>& playlist);

    bool moveToNext(int& currentIndex);

    bool moveToPrevious(int& currentIndex);

    bool empty() const ;

    bool historyEmpty() const ;
};

#endif
