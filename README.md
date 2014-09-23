Tetris366--complete--
=====================

This is a tetris clone I made with the 2D game engine of mine (using SDL2 in C++);

Some of the features are:

- High score list
  -- This list is sorted automatically whenever the screen is loaded. The top 10 highest scores are saved.
  
- Controls screen
  -- Displays all of the controls for the game and shows which effects can be toggled.
  
- Ghost blocks
  -- "Ghost blocks" that show where the block will land can be toggled on and off
  
- Hold blocks
  -- The player can "hold" a block with the spacebar which can be swapped out with the current block.
     The current block must then hit the ground before a swap can be made again.
     
- T-Spins
  
- Soft dropping
  -- The player can hold the down arrow to accelerate the block, and this will score more points
  
- Scoring system
  -- This project uses the same scoring system as the NES tetris game did, and gives more points for
     scoring multiple lines at once, and for soft dropping.
     
- Sounds
  -- I recorded all the sounds for the game myself, and used audacity to edit them accordingly.
     The block noises were made by making popping noises with my headset microphone and the music and sound effects
     were made with my casio wk-200 piano keyboard. I played the public domain tetris theme and improvised a bass
     accompaniment. Each of the effects can be toggled.
     
- Enter name screen
  -- After the game ends, you are presented with the option to enter your name. After entering your name,
     your name is saved to the highscore list which is then sorted when the highscore screen is opened again.
     The file is persistent throughout multiple uses.
     
- Level and difficulty system
  -- The game displays the score, number of lines cleared, which blocks are being held,
     
- Interesting background
  -- The background is a snowy particle effect I made with the updated particle system in the 2D engine.
     
- Difficulty scaling
  -- As more lines are cleared, the line clear count will go up. Every 10 lines, 1 level is completed. Every few levels,
     the color changes to match the faster pace as the game progresses. The game gets progressively harder with every 
     line that's cleared, in the same proportion that the NES tetris game did.
