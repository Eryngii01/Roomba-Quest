*******************************************************************************************
 Level Generator
*******************************************************************************************
All files to be generated as levels in the game are to be named "Level[number].txt".
-> Each file must a 16x16 matrix of data, where numbrs are separated by spaces.

The following numbers represent tiles in the game world:
0 -> Dirty tile to be cleaned by the player
1 -> An obstacle that the player collides with
2 -> An obstacle that moves horizontally along the defined length of the blocks
	e.g. 2 2 2 2 2 -> The obstacle will move between the 5 defined tiles
5 -> The starting position of the player