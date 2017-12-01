# Simple Audio Player built by SFML

## Functions: 

            1. Adding an audio file
            2. Play, Pause, Stop
            3. Fast Forward and Fast Backward
            4. Volume Adjustment


The supported audio file formats include: WAV, OGG/Vorbis and FLAC. 

**Note that due to licensing issues MP3 is not supported.**


## How to run:


Method 1:

            cmake .

            make

            ./sfml_project

Method 2:

            g++ -c main.cpp

            g++ main.o -o app -lsfml-audio -lsfml-window -lsfml-system -lsfml-graphics

            ./app

