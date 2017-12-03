#include "trackfile.h"

Trackfile::Trackfile()
{

}

string Trackfile::getName()
{
    return name;
}
string Trackfile::getLocation()
{
    return location;
}

void Trackfile::setName(string name)
{
    this->name = name;
}

void Trackfile::setLocation(string location)
{
    this->location = location;
}
