#ifndef TRACKFILE_H
#define TRACKFILE_H

#include <string>

using namespace std;

class Trackfile
{
public:
    Trackfile();

    string getName();

    string getLocation();

    void setName(string name);

    void setLocation(string location);

private:
    string name = "";

    string location = "";
};

#endif // TRACKFILE_H
