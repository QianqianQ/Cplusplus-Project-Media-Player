#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "QStringList"
#include "vector"
#include "trackfile.h"


class Playlist
{
public:
    Playlist();

    ~Playlist(){}

    void add(int current_row, QStringList files);

    void remove(int index);

    void save();

    QStringList getFileList();

    std::vector<Trackfile> tracks;

private:

};

#endif // PLAYLIST_H
