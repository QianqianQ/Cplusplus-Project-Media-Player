#include "playlist.h"
#include <fstream>
#include "string"

using namespace std;

string locationToName(string str)
{
    string s;
    int a;

    for(int i = str.size() - 1; i >= 0; i--)
    {
        if(str[i] == '/')
        {
            a = i + 1;
            i = -1;
        }
    }

    for(; a < str.size(); a++)
    {
        s.push_back(str[a]);
    }

    return s;
}

Playlist::Playlist()
{
    std::ifstream read("playlist");
    string loc;
    while(getline(read, loc)){
        Trackfile track;
        track.setLocation(loc);
        track.setName(locationToName(loc));
        tracks.push_back(track);
    }
}

void Playlist::add(QStringList files)
{
    for(int i = 0; i < files.size(); i++)
    {
        Trackfile track;
        track.setLocation(files[i].toStdString());
        track.setName(locationToName(files[i].toStdString()));
        tracks.push_back(track);
    }
}

void Playlist::remove(int a)
{
    tracks.erase(tracks.begin() + a);
}

void Playlist::save()
{
    std::ofstream write("playlist");
    for(int i = 0; i < tracks.size(); i++){
        write << tracks[i].getLocation() << std::endl;
    }
}

QStringList Playlist::getFileList()
{
    QStringList list;
    for(int i = 0; i < tracks.size(); i++)
    {
        QString qstr = QString::fromStdString(tracks[i].getName());
        list.push_back(qstr);
    }
    return list;
}
