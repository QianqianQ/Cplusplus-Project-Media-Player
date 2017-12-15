# Media Player

#### Features

  * Graphical user interface
  * Control the audio playback via GUI: Play, Pause, Stop, Next, Previous, Seeking(by the progresssbar), Volume adjustment
  * Audio browsing & loading from external directories
  * Playlist listing loaded audio files
  * 5 playback modes: List loop, Single loop,Play in order, Single once, Random
  * Displaying audio information by reading metadata
  * Audio visualization
  * Support mutiple audio formats

#### How to compile
```sh
$ cd src/qt-project/
$ make
```
### User Guide

* Button "add"
  - Adding  audio file(s) to the playlist
  - If the playlist is not empty, the file(s) will be added below the file currently selected in the list
  - If the file has been added, an warning will be given
* Button "remove" 
  - Removing the selected file from the playlist. 
  - An warning will be given if the file is under playing
  - An warning will be given if the file can not be found (e.g. the file has been deleted from local machine or changed its path)
* Button "Play" 
  - Playing the current selected file in the playlist 
  - If the selected file is not playing, the file will be played soon
  - If the selected file is under playing, there is no effect
* Button "Pause" 
  - The audio under playing is paused
  - It is disabled when the file has been paused or stopped
* Button "Stop" 
  - The audio under playing is stopped 
  - It is disabled when the file has been stopped
* Button "Next" 
  - Playing the next one file of the file currently selected
  - If the selected file is the last in the playlist, the first file in the list will be played
* Button "Previous"
  - Playing the previous one file of the file currently selected
  - If the selected file is the first in the playlist, the last file in the list will be played
* Slider Volume
  - Moving the slider to adjust volume
  - The default value is 50/100
* Slider Progress_bar
  - Showing the progress of the audio under playing
  - Moving it to seek position
* Combobox Mode
  - Select one among 5 playback modes: List loop, Single loop, Play in order, Single once, Random
  - The default mode is List loop 
* Listwidget Metadata_list
  - Display the metadata of the current audio
  - The displayed information includes: Title, Album, Author,Genre  
* Progress_bar group
  - Visualize the audio under playing in real-time