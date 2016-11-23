
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include <unordered_set>
#include "maze.hpp"

sf::Sprite player;
sf::Sprite backgroud;
sf::Texture wallTexture;
sf::Texture pathTexture;
sf::RenderWindow window;
Maze *maze;

void drawMaze();
void drawPath();
int main(int, char const**)
{
    maze=new(Maze);
    // Create the main window
    window.create(sf::VideoMode(1024,768),L"MAZE");
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile(resourcePath()+"player.png")) {
        return EXIT_FAILURE;
    }
    player.setTexture(playerTexture);
    Position *pos=maze->getPos();
    player.setPosition(60*pos->x, 60*pos->y);
    
    sf::Texture bg;
    if (!bg.loadFromFile(resourcePath()+"white.png")) {
        return EXIT_FAILURE;
    }
    backgroud.setTexture(bg);
    if (!wallTexture.loadFromFile(resourcePath()+"wall.png")) {
        EXIT_FAILURE;
    }
    if (!pathTexture.loadFromFile(resourcePath()+"path.png")) {
        EXIT_FAILURE;
    }
    
    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();


    maze->autoFindPath();
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                maze->run('a');
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                maze->run('d');
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                maze->run('w');
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                maze->run('s');
            }
            
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(backgroud);
        drawMaze();
        drawPath();

        window.display();
    }

    return EXIT_SUCCESS;
}

void drawMaze(){
    for (int i=0; i<HEIGHT; i++) {
        for (int j=0; j<WIDTH; j++) {
            if (maze->map[i][j]=='#') {
                sf::Sprite wall(wallTexture);
                wall.setPosition(j*60, i*60);
                window.draw(wall);
            }
            if (maze->map[i][j]=='o') {
                player.setPosition(j*60, i*60);
                window.draw(player);
            }
        }
    }
}

void drawPath(){
    for (int i=1; i<100; i++) {
        Path *findPath=maze->array[i];
        if (findPath) {
            sf::Sprite path(pathTexture);
            path.setPosition(findPath->x*60, findPath->y*60);
            window.draw(path);
        }else{
            break;
        }
    }
}


