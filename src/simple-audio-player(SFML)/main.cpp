#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// add audio file to wait for playing
std::string add_file()
{
    std::string filename;
    std::cin>>filename;
    return filename;
}

int main()
{
    std::cout<<std::endl<<"Audio Player using SFML"<<std::endl<<std::endl;
    std::cout<<"Command:"<<std::endl;
    std::cout<<"N: Add new audio file(Only available when the exist music is stopped)"<<std::endl<<"P: Play the music"<<std::endl<<"White Space: Pause the music"<<std::endl<<"S: Stop the music"<<std::endl;
    std::cout<<"Up: Increase the volume"<<std::endl<<"Down: Reduce the volume"<<std::endl;
    std::cout<<"Left: Fast backward"<<std::endl<<"Right: Fast forward"<<std::endl<<std::endl;
    std::string filename;
    std::cout<<"Please enter the file name: "<<std::endl;
    filename =add_file();
    sf::Music music;
    while (!music.openFromFile(filename)){
                std::cout << "can't find sound file" << std::endl;
                std::cout<<"Please enter the file name: "<<std::endl;
                filename = add_file();
               }
    std::cout << " " << music.getDuration().asSeconds() << " seconds"<< std::endl; // get the duration
    sf::RenderWindow Window(sf::VideoMode(200,100), "Audio Player",sf::Style::Default); // Create the main window

    // Load a sprite to display
    /*sf::Texture texture;
        if (!texture.loadFromFile("giphy.gif"))
            return EXIT_FAILURE;
    sf::Sprite sprite(texture);*/

    while (Window.isOpen()){
        sf::Event event;

        // Music at Stopped State
        while(music.getStatus() == sf::Music::Stopped)
        {
             while (Window.pollEvent(event)){

                 // THe window is closed
                 if (event.type == sf::Event::Closed)
                 {
                     music.stop();
                     Window.close();
		     std::cout<<std::endl;
                     return 0;
                 }

                 if(event.type==sf::Event::KeyPressed){

                     // Add audio file
                      if (event.key.code == sf::Keyboard::N)
                      {
                          std::cout<<std::endl;
                          std::cout<<"Please enter the file name:"<<std::endl;
                          filename =add_file();
                          while (!music.openFromFile(filename)){
                                      std::cout << "can't find sound file" << std::endl;
                                      std::cout<<"Please enter the file name: "<<std::endl;
                                      filename = add_file();
                                     }
                          std::cout << " " << music.getDuration().asSeconds() << " seconds"<< std::endl; // get the duration
                      }
                     // Play the music
                    if (event.key.code == sf::Keyboard::P)
                         music.play();

                    // Control volume
                    if (event.key.code == sf::Keyboard::Down)
                      music.setVolume(music.getVolume() - 5);
                    if (event.key.code == sf::Keyboard::Up)
                      music.setVolume(music.getVolume() + 5);
                }
           }
        }

        // Music at Play State
        while (music.getStatus() == sf::Music::Playing)
        {
            //sf::sleep(sf::milliseconds(100)); // Leave some CPU time for other processes

            // Display the playing position
            std::cout << "\rPlaying... " << music.getPlayingOffset().asSeconds()<<" sec ";
            std::cout << std::flush;

            while (Window.pollEvent(event)){

                if (event.type == sf::Event::Closed)
                     {
                         music.stop();
                         Window.close();
 			 std::cout<<std::endl;
                         return 0;
                     }

                if (event.type == sf::Event::KeyPressed){

                    // Up and down to control volume
                    if (event.key.code == sf::Keyboard::Down)
                         music.setVolume(music.getVolume() - 5);
                    if (event.key.code == sf::Keyboard::Up)
                         music.setVolume(music.getVolume() + 5);


                    // Left and right to control tracking position
                    if (event.key.code == sf::Keyboard::Right){
                         sf::Time newPos = music.getPlayingOffset() + sf::seconds(2);
                         music.setPlayingOffset(sf::Time(newPos));
                    }

                    if (event.key.code == sf::Keyboard::Left){
                         sf::Time newPos = music.getPlayingOffset() - sf::seconds(2);
                    if (newPos.asSeconds() <= 0.0f) newPos = sf::seconds(0);
                         music.setPlayingOffset(sf::Time(newPos));
                    }

                    // Pause the music
                    if(event.key.code == sf::Keyboard::Space){
                           music.pause();
                    }
                    // Stop the music
                    if(event.key.code == sf::Keyboard::S){
                           music.stop();
                    }
                }
          }
      }

      // Music at Paused State
      while(music.getStatus() == sf::Music::Paused)
      {
         while (Window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            {
                 music.stop();
                 Window.close();
		 std::cout<<std::endl;
                 return 0;
            }

           if (event.type == sf::Event::KeyPressed){

                // Up and down to control volume
                if (event.key.code == sf::Keyboard::Down)
                    music.setVolume(music.getVolume() - 5);
                if (event.key.code == sf::Keyboard::Up)
                    music.setVolume(music.getVolume() + 5);


                // Left and right to control tracking position
                if (event.key.code == sf::Keyboard::Right){
                    sf::Time newPos = music.getPlayingOffset() + sf::seconds(2);
                    music.setPlayingOffset(sf::Time(newPos));
                }

                if (event.key.code == sf::Keyboard::Left){
                    sf::Time newPos = music.getPlayingOffset() - sf::seconds(2);
                    if (newPos.asSeconds() <= 0.0f) newPos = sf::seconds(0);
                    music.setPlayingOffset(sf::Time(newPos));
                }
                if(event.key.code == sf::Keyboard::P){
                      music.play();
                }
                if(event.key.code == sf::Keyboard::S){
                      music.stop();
                }
            }
        }
     }
     Window.clear(sf::Color::White); // clean creen
      //Window.draw(sprite);
     sf::Text text;
     sf::Font font;
     font.loadFromFile("arial.ttf");
     text.setFont(font);
     text.setStyle(sf::Text::Bold | sf::Text::Underlined);
     text.setColor(sf::Color::Black);
     text.setCharacterSize(25);
     text.setString("Audio Player");
     Window.draw(text);
     Window.display();
   }
    return EXIT_SUCCESS;
}



