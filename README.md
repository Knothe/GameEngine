# GameEngine
Simple game system with main components for a GameEngine.
This is a school project, made for my own learning, not serious use.
## Summary
* [SDL2](https://www.libsdl.org/download-2.0.php) - Graphic incopororation and input management.
* [LUA](https://www.lua.org) - Scripting system for game logic.
## init.ini File
With the init file you can set your own values for initialization, you only need to put the id of the value and the value itself.
If any of the id's are not accepted by the engine, it will be replaced by an empty init and the engine will start with some default values.
The values you can edit are:
* x - Screen size in X.
* y - Screen size in Y.
* scale - Pixel scale.
* size - Allocation size.
* frameTime - Frames per second.
* name - Name displayed in the application.
* language - Debug language.
For the language to work, you need to create a file with the same name you put in the language section (language : english, uses english.json).
## Scripting system
To create a game here you need a minimum of 2 .lua files.
### GameManager.lua
This file only has 1 function, Start(pointer). This serves as an initialization file for images and scenes.
* AddState(pointer, state_id, state_file) - Adds a state to the list but doesn't initialize.
* AddFile(pointer, file_type, file_name, file_id,...) - Some files need extra definition.
* FirstState(pointer, state_id).
If you don't add a state and set it with FirstState the program won't run.
### Scene file
This file functions as a set for the scene, where you add all game objects and their respective components, you can even add your own components.
* AddGameObject(pointer, object_id, x_position, y_position).
* AddComponent(pointer, object_id, component_type, component_name, isActive, ...) - Each component needs different initialization values.
If you set component_type to New, you only need to add the nameFile after isActive.
### New Components
With this file you can call GameObject specific functions to allow movement and collision detection (if they have Colliders), check input and enter the Update loop.
