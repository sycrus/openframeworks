# Project 2: Pingpongball #

<img src="https://github.com/sycrus/openframeworks/blob/master/Project_1/img/still3.jpg?raw=true" width=600> <br>
<img src="https://github.com/sycrus/openframeworks/blob/master/Project_1/img/still2.jpg?raw=true" width=600> <br>
<img src="https://github.com/sycrus/openframeworks/blob/master/Project_1/img/still1.jpg?raw=true" width=600> <br>

## Youtube Links ##
Gameplay video
Calibration video
Tangible portions

## Project Concept ##
How can pinball machines be quickly customizeable and prototypeable? 
How can the digital and physical combine to form playful experiences?

An early exploration into touchtable/projection interactions. I wanted to create an experience that anyone can quickly pick up and play around with, without much rules.

## Realizing the concept ##
The interactive experience consists of several components: 
- A projected playing surface ("touch table")
- Several retro reflective markers as game pieces
- Buttons to operate pinball machine, connected to an Arduino
- A IR camera and IR light source (in this case, a Kinect)
- A computer running Openframeworks

User flow:
1. Player places game pieces on the touch table.
2. If she is satisfied with the positions, she can press a button to create game objects at those locations.
3. If not, she can press cancel and rearrange them.
4. Once the game objects are created, she can press a button to launch the ball. She can use buttons to control the flipper. Points are recorded for hitting game objects.
5. Once the ball falls below the flippers, the score is reset.


## Target Audience ##
I imagine this to be in a museum/playspace setting, where people have access to interactive projected spaces. 

## Sketches ##
<img src="https://github.com/sycrus/openframeworks/blob/master/Project_2/img/character_sketches.png?raw=true" width=400>
Character sketches

<img src="https://github.com/sycrus/openframeworks/blob/master/Project_2/img/bird_sketches.png?raw=true" width=400>
Game screen

## Future Extensions ##
In the future I would wish to explore extending this system to a bigger space, and build more interesting interactive experiences. For example, allow children to build their own towns, or make their own games.

## Process ##

These are the processes and issues I have faced so far when conceptualizing and realizing this project:

- All custom illustrations are done in Illustrator and exported as pngs, which are inserted into the game as ofImages. 
I used the ofxBox2d library to create the physics components, using the edges, circles, boxes. For the flippers, I had to extend the ofxBox2d Joint class to include revolute joints, which enabled me to create objects that rotate about an axis. This was also added to the wheel axis. For the wheel and background colliders, I converted the svg tiny file into polylines, which I then converted into ofxBox2d edges.

- For triggering contact actions, I used the contact listener example from ofxBox2d, triggering sounds, changing images and recording scores.

- Due to lack of maker facilities, I made buttons out of tiny pushbuttons in a case made of Lego parts. Also, I had enough buttons to make the flippers move, but not enough for resetting the game, setting the pieces or activating the plunger.

- ofKinect: I had to experiment with the IR camera of Kinect, and how to recognize objects. Eventually I settled on using area of blobs (within a range for each shape), but changing values at different distances/angles from the Kinect affects the area substantially. I suspect it may be because of uneven IR lighting from the Kinect IR array, which can be avoided if I had a separate IR light source.

- ofxBox2d library: ofxBox2d had a different way of creating objects that took me some time to understand, which I started with from the flippers . This was a good opportunity to learn about vectors, both pushing to, iterating and retrieving from them. 

- ofxBox2d: Revolute Joints was missing in the class, which I had to go through in detail to locate which parts to extend. This was a good exercise to understand the Box2d framework, and how there are functions to translate C++ to Openframeworks.

- Importing SVG into OF: The key part wa having svg files saved as Tiny 1.2. This affected the size of the svg somewhat, and I had to manually adjust to fit.

- ofArduino: Initially I thought I could just send serial strings from Arduino to Openframeworks, but the parsing was off and the button presses were not being recorded, or recorded with unacceptable delay. I tried out the StandardFirmata solution and it worked much better, which also means Arduino can be controlled via Openframeworks, saving time without having to switch from OF to Arduino IDE.

- CV: The detection can be easily obscured since the user is in between the projector and the surface. The calibration process is also very tedious, but I am now more aware of the parameters to tweak in order to reduce noise.

## Evaluation ##
This was a good exploration into the libraries of OF, and a good start in terms of thinking about what can be done. In terms of technical success, I think this was an encouraging exercise, and the challenges open up new possibilities. In terms of design, the user experience is not an ideal one. I should reconsider where I place my Kinect and projector, and try to adjust for warping.
