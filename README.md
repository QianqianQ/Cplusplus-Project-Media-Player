# Media Player

#### Features

  * Graphical user interface
  * Control the audio playback via GUI
  * Audio browsing & loading from external directories
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
|       Button Pause       |              Pause the audio              | Disabled when media is stopped or has been paused                     |
|        Button Stop       |               Stop the audio              | Disabled when media has been stopped                                  |
|        Button Next       |    Play the next audio in the  playlist   | Refers to the next one of the file currently<br> selected in the list     |
|      Button Previous     |    Play the audio music in the playlist   | Refers to the previous one of the file currently selected in the list |
|        Button Add        |     Add audio file(s) to the playlist     |                                                                       |
|       Button Remove      |   Remove the selected file from the list  | Could not remove the audio under playing                              |
|       Slider Volume      |      Move the slider to adjust volume     | The default value is 50/100.                                          |
|       Combobox Mode      |          Select the playback mode         | 5 modes: List loop, Single loop, Play in order,Single once, Random    |
| Listwidget Metadata_list | Display the metadata of the current media | Information contains: Title, Album, Author,Genre                      |
|      Bar-group Specs     |  Visualize the music playing in real-time |                                                                       |

