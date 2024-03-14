Hello! And welcome to my satellite simulator!

This project started out when I had a thought while I was listening to a podcast on rocket launches, how does NASA, SpaceX, BlueOrigin, and other space companies keep track of their satellites? And how do they know in advance the routes they should take so they dont crash into other objects? This question turned into this project, where I aimed to create as realistic of a orbital simulation around the Earth as I could. It took alot of trial and error, but after gathering sufficient information of orbital physics, I managed to put out something that I can declare is an accurate simulation of a satellite as it orbits the Earth!

RESOURCES USED: http://www.braeunig.us/space/orbmech.htm

My simulation takes into account the following variables: Radius of the Earth, mass of the Earth, radius of the satellite, distance from Earth of satellite, semi-major axis of the satellite, and eccentricity of the orbit. I did not take into account atmospheric drag into this simulation. 

Zoom function is a little buggy because when zooming in, the precise numbers needed to keep the center the camera while zooming in thousands of times the actual screen go past the allowed characters for a float, which is the number that raylib graphics supports. I put in the zoom function mostly as a cool visual to show the disparity of the size of the satellite compared to the size of the Earth. 

This was a fun project to create, and I hope you find it interesting!