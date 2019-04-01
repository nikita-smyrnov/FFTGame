# Project Proposal

  My project proposal is to make a game similar to [Audio-Surf](http://www.audio-surf.com/). In summary, my game is one where you can use the A and D keys (or left and right arrows) to switch between 3 different lanes while moving along a course. Special blocks - such as points or power-ups that make boost you while doubling your points collected during that boost - are placed in one of the 3 lanes. You would then try to collect the most amount of points possible (by switching lanes and hitting blocks) for the duration of a specific song that would be played in the background.
  
  However, these blocks are not simply placed at random. They are placed according to various features of the song currently playing in the background. Each game/round consists of the player getting to choose a song (that would be loaded from an mp3 from a specific directory inside the project), and that song would then be analyzed using the Fast Fourier Transform algorithm to generate a spectrum of sound. I would use the built-in OF library for this algorithm as coding it myself would take too much time (and would probably be terribly worse in performance).
  
  After the song has been analyzed, I can pick out specific features of the song/spectrum such as frequency, beat clicks, volume, etc. in order to write an algorithm to place special blocks on the course. Not only that, but I could also experiment with making the player move faster or slower based on the tempo of the music. I would generate the course in advance (allowing me to observe more trends in sound data) and then load it into the game. Perhaps I could also save the last 5 or so courses as files in a directory that could be loaded if the user would like to play the course again without having to analyze the sound and generate the course again.
  
  I do not have any background in analyzing sound, but I'm interested in the idea of turning sound visualization into an interactive game. I have implemented basic side-scrolling games in Java before so I can use that knowledge for this game.
  
The built-in libraries I would use:
- ofxGui
- core sound libraries (ofSoundPlayer come to mind)
- maybe other graphics/game libraries? (ofxVectorGraphics)

Any outside libraries I would use:
- [ofxBox2d](https://github.com/vanderlin/ofxBox2d/) to handle game functionality such as collisions and movement
