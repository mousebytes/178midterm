My approach to the rocket midterm:

I had to create a game where a rocket is moving upwards with parallax automatically scrolling downward. There needed to be asteroids moving towards the rocket that bounced away upon contact. Most of what is provided in the base code will be omitted.

Structure:

Relevant classes will be labeled with "Name:" then a block of text describing its usage will follow. Some points will be omitted due to them being a part of the base code.

Art:

I drew spritesheets for the asteroid and rocket using a pixel art program, Aseprite. I used the same program to draw a static image for the parallax background.



Scene:

I created an instance of parallax with _parallax *parallax. I initialized it using initPrlx(), passing it the file name of the background. I drew it in drawScene() using a glPushMatrix() in order to change its size to fill the screen. I drew the background using drawBackground(), and passed the dim.x and dim.y to make it dynamically readjust if the screen is resized. I automatically scroll downward using the function scrollDown();

I created an instance of player with _player *player. I initialized it using initPlayer() and passed the number of frames, x and y, in my sprite sheet and the file name. I initialized the actionTrigger to STAND in initGL() in order to have the player idle in the beginning of the scene. I consistently draw the player using drawPlayer() and updated the actions with playerActions in drawScene()

I created an instance of inputs with _inputs *inputs. I sent the object the wParam, which reads the current key being pressed, via the winMsg() method. If a key is pressed then the player is updated accordingly. If a key is released then the wParam is updated and sent to the object. The object then calls the class method keyUP, sending a player instance. I will address more in a later section labeled "Inputs." 

I needed asteroids so I created an array of size MAX_ENEMY_COUNT, _enms enemies[MAX_ENEMY_COUNT], where MAX_ENEMY_COUNT is defined as 10, #define MAX_ENEMY_COUNT 10, just below the #includes. I initialized the first enemy, enemies[0], with its relevant sprite using initEnms(). Its speed was initialized using the class variable "speed" where it is set to a pseudo-random number by rand() which was populated by unix time, srand(time(NULL)) at the start of the initGL() function. The action trigger was then set to FALLING, with its behavior being defined in a later text paragraph. All 10 enemies, enemies[0 through 9], are then placed using a method from the _enms class, later described in detail, called placeEnms(). The function is given a vector with randomized x coordinates, and y / z coordinates being populated from the class constructor. The scale and fall speed is then set using a random number in order to randomize the size of the asteroids. The first enemy's texture is constantly drawn using a reference to its own texture. There is then a for loop which consistently iterates through all of the _enms objects. The for loop checks if the object has not collided, further clarification later. If such is the case, the texture is drawn using a reference to enemies[0]'s texture. The action trigger is set to FALLING in order to make sure that the object follows the correct falling behavior, more on that later. The actions() method is then called in order to make sure the appropriate behavior is being followed. If the object's is_collided flag has been triggered then the object's actionTrigger will not be set to FALLING. There is then a reference to the method move_enemy_towards_player(), which is self explanatory, which passes the player object.

I needed hit boxes, so I instanced _collisionCkeck *collide. The collision's method collide->isRadialCol() is passed several variables in order to track if two objects have collided. The first being the enemy's position, then the player's position, then the radius of hitbox 1 and 2 (enemy and player's circular hitbox in this case). Lastly is a threshold which states how closely they can be together. If the objects have collided then the is_collided flags are updated to true. If the enemy is to the right of the player then the enemy bounces rightward. Likewise with leftward. Each actionTrigger is set to its respective, MOVERIGHT or MOVELEFT based on the aforementioned condition.


Inputs:

The player needed movement, so in the method keyPressed() which takes in a player object, I checked which key was read and moved it appropriately. In this case only leftward and rightward movement were necessary. So if the player is holding down the left or right arrow key, the action trigger is set to LEFTWALK and RIGHTWALK respectively.

The player also needs its state to return to STANDING once the key is released. So in the keyUP() method which takes in a player object; it resets the actionTrigger of player to STANDING once the left or right arrow keys are released.




Parallax:

In the constructor, I initialized the class variable speed to 0.05. Outside of the functions from the base code, I added a scrollDown() method. Once 50 ticks elapse; it automatically scrolls downward at a pace predefined with the speed variable.



Player:

In playerActions() I read the actionTrigger, for STAND I set the sprite to the appropriate initial yMax, yMin, xMax, and xMin. I then incremented the frames by 1 every 70 ticks. For LEFTWALK and RIGHTWALK, I changed the vertice heights in order to match my sprite sheet appropriately. With LEFTWALK and RIGHTWALK allowing for the left and right thruster to power on appropriately. For left and right walk the movement is handled by increments of 0.05 in their respective directions. The movement is restricted at x -1.75 and 1.75 respectively.




Enemy:

For actions(), there is a switch case which reads the actionTrigger. If the actionTrigger is FALLING then the y-coordinate is decremented by fall_speed, which was defined by rand() in the scene class. Once the y-coordinate hits -1.5, the bottom of the screen, it is reset to the top of the screen at 1.5. The placement at the top of the screen is then randomized and the fall_speed is randomized. When the asteroid collides with the rocket, the actionTrigger is set to MOVERIGHT and MOVELEFT appropriately. Its x coordinate is incremented or decremented respectively by fall_speed every 60 ticks. If the asteroid hits the edge of the screen its is_collided flag is reset, and it is placed at the top of the screen at a random position and falling at a random fall_speed. The actionTrigger is then set to FALLING

For the method I added, move_enemy_towards_player(), it takes in a player object. If the asteroid is to the right of the player then it moves leftwards at fall_speed until it reaches the player. If the asteroid is to the left of the player and collides with the player then it moves rightwards.



Collision:

Collision is simple, in its method isRadialCol(), it takes in two vec3's, 2 radii, and a threshold. Where if the circles are close enough together then the function returns true, indicated they have collided.


