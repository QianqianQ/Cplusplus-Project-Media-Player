# Media Player

#### Features

  * Graphical user interface
  * Control the audio playback via GUI: Play, Pause, Stop, Next, Previous, Seeking(by the progresssbar), Volume adjustment
  * Audio browsing & loading from external directories
  * Playlist listing loaded audio files
  * Displaying audio information by reading metadata
  * Audio visualization
  * Support mutiple audio formats

#### How to run
```sh
$ cd src/qt-project/
$ make
$ ./player
```
### User guide
|          Widget          |                  Function                 |                                  Note                                 |
|:------------------------:|:-----------------------------------------:|:---------------------------------------------------------------------:|
|        Button Play       |               Play the audio              | A warning will be given under some invalid conditions                 |
|       Button Pause       |              Pause the audio              | Disabled when audio is stopped or has been paused                     |
|        Button Stop       |               Stop the audio              | Disabled when audio has been stopped                                  |
|        Button Next       |    Play the next audio in the  playlist   | Refers to the next one of the file <br> currently selected in the list|
|      Button Previous     |    Play the audio music in the playlist   | Refers to the previous one of the file<br> currently selected in the list|
|        Button Add        |     Add audio file(s) to the playlist     |                                                                       |
|       Button Remove      |   Remove the selected file<br> from the list  | the audio under playing could not be deleted                      |
|     Slider Progress_bar  |   Show the progress of the audio under playing. <br>Seek specific position |                                  |
|       Slider Volume      |      Move the slider to adjust volume     | The default value is 50/100.                                          |
|       Combobox Mode      |          Select the playback mode         | 5 modes: List loop, Single loop,<br> Play in order, Single once, Random|
| Listwidget Metadata_list | Display the metadata <br>of the current media | Information contains: Title, Album, Author,Genre                   |
|      Bar-group Specs     |  Visualize the music under <br>playing in real-time |                                                             |