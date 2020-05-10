# Project 1: Boxed in: A Short Story #

<img src="https://github.com/sycrus/openframeworks/blob/master/Project_1/img/still4.png?raw=true" width=600> <br>
<img src="https://github.com/sycrus/openframeworks/blob/master/Project_1/img/still5.png?raw=true" width=600> <br>
<img src="https://github.com/sycrus/openframeworks/blob/master/Project_1/img/still6.png?raw=true" width=600> <br>

<img src="https://github.com/sycrus/openframeworks/blob/master/Project_1/img/still7.png?raw=true" height=400> <img src="https://github.com/sycrus/openframeworks/blob/master/Project_1/img/still8.png?raw=true" height=400> <br>


[![Video](http://img.youtube.com/vi/-obwAIszi1Y/0.jpg)](https://www.youtube.com/watch?v=-obwAIszi1Y "Video") <br>

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

## Future Extensions ##
I am curious about the possibilities of each of these worlds interacting with each other. For example, how will neighbors react when they see each other opposite to each other? I could create, using two boxes, placed side by side, and have the story of the two neighbors told. It could be interactive as well, such as how would the interactions change if different combinations of neighbors were placed beside one another, or it could be told from the perspective of the pigeon, who flits from parapet to parapet. Or a dog or cat could react to this perceived invasion of a confined space.

## Process ##
These are the issues I have faced so far when conceptualizing and realizing this project:
- Importing SVG into OF and animating it: ofxSVG --> ofPolyline
- Projecting onto a box: ofxWarp, or via ofxSyphon --> MadMapper (rejected because of watermarks, and because I wanted it to be contained in OF
- Drawing to the surfaces of ofxWarp: Drawing to surfaces and creating one fbo for each face of the box worked.
- Animation, and simplifying the process: I separated the animation into 6 scenes, with sequences each. I created points that the characters would stop at, and a path they would travel along. I then used ofGetFrameNum and used a percentage of each duration to calculate how far along the path the characters have traveled. To do so took a lot of planning, mapping out each scene and each point. Once the general movement was programmed, it was relatively straightforward.

## Evaluation ##
I have to manage my own expectations between how I envision the story to be, and how well I can execute it in OF. This is an exercise on brevity, simplicity, and other (non-visual) modes of communicating emotion or telling as story.

This is also a good chance to streamline animation flows, and to think about curved paths which could be accomplished by exporting from Illustrator. Once these processes are more streamlined, less time can be spent on technical issues and more towards storytelling.

