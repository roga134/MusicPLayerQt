#include "musicplayerqueue.h"

void MusicPlayerQueue::initialize(const std::list<QUrl>& playlist)
{
    std::vector<int> indices(playlist.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), std::mt19937{std::random_device{}()});

    while (!upcomingIndices.empty()) upcomingIndices.pop();
    while (!historyIndices.empty()) historyIndices.pop();

    for (int idx : indices)
        upcomingIndices.push(idx);
}

bool MusicPlayerQueue::moveToNext(int& currentIndex)
{
    if (upcomingIndices.empty())
        return false;

    historyIndices.push(currentIndex);
    currentIndex = upcomingIndices.front();
    upcomingIndices.pop();
    return true;
}

bool MusicPlayerQueue::moveToPrevious(int& currentIndex)
{
    if (historyIndices.empty())
        return false;

    std::queue<int> tempQueue;
    tempQueue.push(currentIndex);

    while (!upcomingIndices.empty())
    {
        tempQueue.push(upcomingIndices.front());
        upcomingIndices.pop();
    }
    std::swap(upcomingIndices, tempQueue);

    currentIndex = historyIndices.top();
    historyIndices.pop();
    return true;
}

bool MusicPlayerQueue::empty() const
{
    return upcomingIndices.empty();
}

bool MusicPlayerQueue::historyEmpty() const
{
    return historyIndices.empty();
}
