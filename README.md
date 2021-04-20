<p align="center">
	<img width="370" height="165" src="https://imgur.com/AwjurNw.png">
	<img src="https://media.giphy.com/media/hL5qjOYP2FmpXxBKYp/giphy.gif" alt="animated">
</p>  

# About
Snake game written in C++ using modern OpenGL for graphics rendering.

Dependencies:  
* GLFW
* GLAD
* Dear ImGui
* stb_image
* FreeType
* Premake5  

References:  
* [docs.gl](https://docs.gl "docs.gl")
* [learnopengl.com](https://learnopengl.com "learnopengl.com")
* [TheCherno's Hazel game engine repository](https://github.com/TheCherno/Hazel "Hazel")
* [TheCherno's OpenGL series](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2 "OpenGL series")
* [TheCherno's game engine series](https://www.youtube.com/watch?v=JxIZbV_XjAs&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT "Game engine series")

Assets:  
* [Kenney's assets](https://www.kenney.nl/assets/simple-space "Simple space")
* [OpenGameArt](https://opengameart.org/ "OpenGameArt")
* [itch.io](https://itch.io/game-assets "itch.io")

# Controls
Turn left | Turn right
--------- | ----------
A         | D

# Building the project
Start by cloning the repository with `git clone --recursive https://github.com/rafalmaziejuk/Snake`.  
If you cloned the repository without `--recursive` option, use `git submodule update --init`.

### Windows
Open `scripts` folder and run `genWindows.bat` for Visual Studio 2019 project generation, launch *.sln file and build Solution.

### Linux
Open `scripts` folder, run `sh genLinux.sh build` and then `sh genLinux.sh run`.

# TODO
* 2D batch renderer
* Refactor Singleton classes (TextRenderer, InputManager)
* Events handling
* Texture atlasses loading
* Particles
* Post-processing effects
* Sounds