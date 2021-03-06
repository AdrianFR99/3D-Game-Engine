# Gear Engine

## Objectives

We are an  game development team formed by 2 students taking the bachelor's degree in Videogame design and development in the UPC.
The engine will be developed for the subject 3D Engines. We will be making a Unity like basic engine during the next 3 month.

## GitHub Repo

The proyect Source Code is available in the [Github Repository](https://github.com/AdrianFR99/3D-Game-Engine)

Here you may look at the [LICENCE](https://github.com/AdrianFR99/3D-Game-Engine/blob/master/LICENSE)
or Read it at the end of this document

As stated on the license, anyone can look at or modify the code of this project. 

## The team
   
The engine is developed in collaboration of 

- Andrés Ricardo Saladrigas Perez
   - [Andrés' GitHub Link](https://github.com/TheArzhel)
   
- Adrian Font Romero
   - [Adrian's GitHub Link](https://github.com/AdrianFR99)
   

### Downloading

Go tho the release tab on our GitHub Repository, or click [here](https://github.com/AdrianFR99/3D-Game-Engine/releases) 

Select the desired released file. Click on the Gear_Engine.zip.
Click to Save the file in your computer.
proceed to install.

### Installation 

Decompress the .zip file in any directory. Open the file directoy and double click on the executable Gear_Engine.exe . 
Download [here](https://github.com/AdrianFR99/3D-Game-Engine/releases) 

or download the desired release here and follow the same steps:
<https://github.com/AdrianFR99/3D-Game-Engine/releases>

### Execute

Once inside the Engine, you may refer to the manu tool bar to open windows to edit your prefferences, or drag and drop the meshes provided inside of the Folder "Assets" in the same dirrectory. You may also open the Console to the the Logs of the procceses beneath the UI of the engine.
       
## Libraries

The proyect is using a external open libraries. which are listed here:

- SDL: V2.0.10

- MathGeoLib: V2.0

- ImGui: V1.74

- JSON for Modern C++: V3.7.0

- OpenGl:V4.6.0

- Glew: V7.0

- DevIL: V1.8.0

- Assimp:V3.1.1

- mmgr

- Brofiler: V1.1.2

- Par_shapes


## Engine controls
### Controller
#### Main menu tool bar
- File collapsing menu
	- New Scene: Delete current meshes on screen
	- Save Settings: save variables changes to Config
	- Load: load settings from variables in the config
	- Exit: exit the application.
- Gameobject: Create the primitive specified
	- Cube
	- Sphere
	- Cylinder
	- Cone
	- Dodecaedrum
	- Tetraedrum
	- Octoedrum
	- Icosaedrum
	- Bottle
- Window collapsing menu
	- Console: open the developer console
		- Clear: clear the log History.
		- Copy: copy conole info into clipboard.
		- X: close Console
		- Console tab: click and drag to change position inside screen, and dock if wanted.
	- Settings: open Config menu where variables can be changed to the user desire.
		- Application:
			- App Name: display Engine name
			- Max FPS: change the framerate cab
			- Graph: display framerate, miliseconsd each frame, and memory consuption at the time.
			- Meory data: able to see stats about memory usage and consuption.
		- Window: 
			- Brightness Slide bar: slide to change window brightness level
			- Width Slide bar: slide to change window width level
			- Height Slide bar: slide to change window height level
			- Refresh rate: info
			- Check boxes: able to change window mode to Fullscreen, borderless, fullscreen brderless and resizable capability. click to turn on or off.
		- File system:
			- Display of the local folder where the executable s runnig.
		- Input:
			- Display: see mouse position on screen, mouse movement, and mouse wheel movement
			- Sensitivity: change the mouse sensityvity when looking around with the camera
			- Wheel Speed: change mouse wheel speed to zoom in or out.
		- Camera:
			- Camera speed Slider: slide to change the camera speed of movement.
		- Hardware: Display information od Cpus, Ram, Gpus, and Vram.
		- Software: Display SDL Version, OpenGl version and DevIL version.
		- Renderer Buttons: 
			- Poly configuration: Checkboxes to enable or disable backface cull, light. Checkboxes to anable wireframe view and to perform a dev test
			- Normals: Checkbox to display gameobjects vertex normals and face normals.
			- Materials: Checkboxes to enable or disable color of materials and 2D textures. display current ID of texture. Path of the texture. And Texture Configurations to change the properties with ambient, diffuse and specular. cliclk to open a color boz and decide the parameters.
		- X: close Console
		- Config Menu tab: click and drag to change position inside screen, and dock if wanted.
	- Hierarchy: View the GameObjects in a list. IMPORTANT: Each gameObject may contain multiple meshes. See the inspector to get more information and deactivate each one individually. Click the desired Gameobject to modify, drag and drop the desired texture, and press F to center the camera around it. Go to file>new scene or drag and drop other fbx to clear the scene.
	- Inspector:
		- Transform: Displays three coordinates(i,j,k) of the gameObjects position,rotation and scale.
		- Normals: Shows two checkboxes which enable/disables the debugdraw of the normal vertices and normal faces
		- Texture: Displays the current texture id, The path where the texture is loaded from, the size of the texture, And a preview for the texture loaded.
		- Material: Contains three checkboxes which enable/disable the material,the diffuse texture and the checkered texture
		- Mesh & Geometry: Checkboxes which Enables/disables the mesh/meshes of the gameobject and displays data about the polygon count(vertices,indices,normals...)
- Help collapsing menu
	- Gui Demo: enable disable by clicking the Imgui DEmo window to test IMGUI
	- Github Repo: click to see the proyects github repo
	- Documentation: click to see the githb wiki about the Engine (empty)
	- Download the Lastest: click to open the github tab of our releases
	- Report a Bug: click to open the github tab of our issues and submit it.
- About: click to open/close a floating windows that contains the information (on different tabs) of the Engine. Creators, Licence, Libraries with versions and Github button. Inside github, the proyect trello can be found. Click to open.


#### In-ViewPort Controls
To navegate the Scene
- During Right Click: anable world navigation.
	- WASD movement in the scene
	- Move mouse around to see your surronding. Free look.
- Alt+ Left Click: orbit the scene object.
- F: press F to center the camera at the object
- Mouse Wheel: Scroll the mouse wheel to zoom in or out
- Pressed Shift: While left shift is pressed the WASD movement is fastest.
## Version changelog

### **v0.05**
#### Implementations
- UI implementation:
	- Setting
	- About
	- Console
	- Theme ImGui 
- Load and Save
	- Automatic Load of Config file
	- Save button on File menu, saves changes to Config
- Mesh Loading
	- Drag and drop FBX files to open meshes and print them
- Camera
	- Unity like Camera Movement
- Docking
	- Windows Docking

### **v0.06**
#### Implementations
- Textures:
	
- Load and Save
	- Manual Save 
	- Manual Load
- ImGui
	- Theme and Colors
- Scene
	- Clear scene from meshes
- Bug Fixing
	- Config Menu bugs
	- Load and Save Bugs

### **v0.07**
#### Implementations
- Gameobjects
- Components
- Normal Display
	- vertex normals
	- Face Normals
- FBX and DDS load
- F in camera
- code rework

### **v0.08**
#### Implementations
- primitive
- Finish Components
- Hierarchy
- Inspector
- Bug Fixing

### **v1.00**
#### Implementations
- primitive
	- normals
	- textures
- Components
	- Gameobjects creates
- Mem leaks
- Hierarchy
	- Selection
- Inspector
	- Display options  
- Bug Fixing

(MEMBERS WORK)
### v2.00
#### Implementations
ADRIAN FONT
- Camera as a component
- Camera Culling
- Bounding Boxes (BBo, AABB)
- quatrees
ANDRES SALADRIGAS
- resource manager
- save own format
- load own format 
- hierarchy


## Disclosure 

```
We do not own any of the external libraries or FBX files.

Everything belongs to the creators of the original content.

Be sure to check out their sites or githubs to get more info about them.
```

## License

MIT License

Copyright (c) 2019 Adrián Font Romero & Andres Ricardo Saladrigas Perez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
