# Project 1: On My Own? A Short Story #

<img src="https://github.com/sycrus/openframeworks/blob/master/Project_1/img/projection.JPG?raw=true" width=400>

## Project Concept ##
How does nature find a way to connect with us, when we are ensconced in our isolation chambers? 
How will we react, and how does nature react to us in this state?

A man tries to go about his peaceful day at home, but his attention is constantly drawn to a pigeon outside his window. Will he ever get to do the things he planned on doing, or will the pigeon have other plans for him?

## Realizing the concept ##
Initially, I envisioned a person interacting with nature in the context of a log cabin, where humanity is transplanted in the thick of nature. I imagined the possible activities within the log cabin, such as waking up, picking an apple, sitting by the porch. It was meant to be an idyllic narrative, punctuated by interruptions of nature, which the protagonist found intrusive, but ultimately ended up following the rhythm of nature, rather than rejecting it.

I found it hard to relate, in these times of social distancing in my apartment. However, nature finds ways to reach out to us. A pigeon on my window sill, for example, allowed me to once again get upclose and personal with the fauna of New York. At least for the foreseeable future, interactions like these will be rarer, more treasured.
One of my goals for this narrative project was to explore projection mapping, because of the possibilities of texturing a 3D surface. I wanted to explore how we could tell a story using more than one surface, and how the storytelling or attention aspects will change.

I decided to use a grey cardboard box, previously packaging which I flipped inside out. By projecting onto this surface, I hope to add extra dimensions to the experience.

## Target Audience ##
I imagine this to be in a museum/playspace setting, where people have access to projected spaces. At the same time, this would be most identifiable to bored social distancers.

## Sketches ##
<img src="https://github.com/sycrus/openframeworks/blob/master/Project_1/img/character_sketches.png?raw=true" width=400>
Character sketches

<img src="https://github.com/sycrus/openframeworks/blob/master/Project_1/img/bird_sketches.png?raw=true" width=400>
Bird sketches, with one from top view for top of apartment

<img src="https://github.com/sycrus/openframeworks/blob/master/Project_1/img/apartment_front.png?raw=true" width=400>
Apartment prototype, same as projection image

## Future Extensions ##
I am curious about the possibilities of each of these worlds interacting with each other. For example, how will neighbors react when they see each other opposite to each other? I could create, using two boxes, placed side by side, and have the story of the two neighbors told. It could be interactive as well, such as how would the interactions change if different combinations of neighbors were placed beside one another, or it could be told from the perspective of the pigeon, who flits from parapet to parapet. Or a dog or cat could react to this perceived invasion of a confined space.

## Process ##
These are the issues I have faced so far when conceptualizing and realizing this project:
- Importing SVG into OF and animating it: ofxSVG --> ofPolyline
- Projecting onto a box: ofxWarp, or via ofxSyphon --> MadMapper (rejected because of watermarks, and because I wanted it to be contained in OF
- Drawing to the surfaces of ofxWarp: still in progress. I suspect I will have to grab the screen image each frame
- Animation, and simplifying the process: still in progress. ofxAnimatable 

## Evaluation ##
I have to manage my own expectations between how I envision the story to be, and how well I can execute it in OF. This is an exercise on brevity, simplicity, and other (non-visual) modes of communicating emotion or telling as story.
