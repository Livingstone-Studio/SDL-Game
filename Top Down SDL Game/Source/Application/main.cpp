#include "Game.h"

// Being away from this project for 2 years, a lot of poor programming choices have become 
// abundently clear from where I was still learning C++ fundamentals at the time of making this.
// So this is a to do list as to areas I want to improve upon at some point.

// TODO:
// 1. Rewrite any dodgey systems you can find:
//			- Debug Graphics: Replace debug graphics with SDL debug rects. Needlessly overcomplicated currently.
//			- Buttons: make use of function pointers, delete rest of classes - way too verbose.
//			- Tilemap: needs to be converted into a flyweight design - needlessly resource intensive at present.
//			- Rendering (z ordering): Every game object is ordered based on z placement,
//									  at most static objects only need it determined once,
//									  would reduce the amount being sorted from 100+ to <10 for
//									  current levels.
//			- Rendering (Tilemap): Not certain SDL supports this idea, but by compiling a texture
//								   of all map tiles, one draw call could be used to represent the map
//								   as opposed to a lot.
//			- GameObject vector: Convert to array, needlessly expenisve. One thought would be to let 
//								 the level file tell the game how much gameobject memory it needs with
//								 an integer count as to not extent into 'dead' gameobject memory. That
//								 could then have a certain amount allocated on top as wiggle room so it's 
//								 not strictly limited to the map size. e.g map: 200 go's, 100 wiggle = 300 total go's allowed.


int main(int argc, char* argv[])
{
	Game game;

	game.Execute();

	return 0;
}