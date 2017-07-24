# playground
This repository is created to experiment with different technologies I've been looking at. Here is a short description of what's in it:

* [torus](https://github.com/viktorburka/playground/tree/master/torus) demostrates OpenGL/ES and C++/Qt and has several subprojects:
  
  1. [torus_mesh](https://github.com/viktorburka/playground/tree/master/torus/torus_mesh) is a 3D drawing of a torus geometrical object displayed in wireframes and perspective projection. The example also has rotation implemented in 3D space
  <img src="https://github.com/viktorburka/playground/blob/master/torus/torus_mesh/doc/readme-md/torus_mesh.png" width="640" height="480">
  
  2. [torus_texture](https://github.com/viktorburka/playground/blob/master/torus/torus_texture/doc/readme-md/torus_texture.png) is a 3D drawing of a torus geometrical object wrapped in a simple texture to demostrate texture drawing. Because of lack of source of light, the picture looks very plain and in fact not 3D. In the next example I added a source of light that made this same figure look much different
  <img src="https://github.com/viktorburka/playground/blob/master/torus/torus_texture/doc/readme-md/torus_texture.png" width="640" height="480">
  
  3. [torus_diffuse_light](https://github.com/viktorburka/playground/blob/master/torus/torus_diffuse_light/doc/readme-md/diffuse_light.png) is a 3D drawing of a torus geometrical object with where a mathematical model of a diffuse light has been implemented. It is based on a calculation of a reflected light angle coefficient given by a doc product of 2 vectors. The coefficient is then pocessed in a [fragment shader](https://www.khronos.org/opengl/wiki/Fragment_Shader) to calculate the right fragment color
  <img src="https://github.com/viktorburka/playground/blob/master/torus/torus_diffuse_light/doc/readme-md/diffuse_light.png" width="640" height="480">

* [minesweeper](https://github.com/viktorburka/playground/tree/master/minesweeper) is [Qt/QML](http://doc.qt.io/qt-5/qtqml-index.html) implementation of a well known Windows game. The busindess logic is written with JavaScript which is a scripting language that QML uses. It emulates some classes via building them through JS [Object.prototype](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Objects/Object_prototypes) therefore creating classes that can be instantiated and extended and not just dynamically enhancing current one off objects
<img src="https://github.com/viktorburka/playground/blob/master/minesweeper/doc/readme-md/minesweeper.png" width="320" height="280">

* [python-xml-build-script](https://github.com/viktorburka/playground/tree/master/python-xml-build-script) is just a very simple build system implemented in CSV and XML formats written in Python to work with [Microsoft Team Fundation Server](https://www.visualstudio.com/tfs). Its capable of comparing the changes of revision currently being checked in to TFS and if any, building the project and the dependencies which can be specified in either CSV or XML format

* [sine-qml-graphics-scene](https://github.com/viktorburka/playground/tree/master/sine-qml-graphics-scene) is an implementation of sin trigonometric function that renders it on the screen implemented via [Qt Quick Graphics Scene](http://doc.qt.io/qt-5/qtquick-visualcanvas-scenegraph.html) API. It is written in C++ can calls those APIs to render the image utilizing hardware accelerated rendering
<img src="https://github.com/viktorburka/playground/blob/master/sine-qml-graphics-scene/doc/readme-md/sine.png" width="180" height="120">

* [ticktactoe-angular](https://github.com/viktorburka/playground/tree/master/ticktactoe-angular) is a TicTacToe game that runs in a browser and is implemented in [TypeScript](https://www.typescriptlang.org/) and [Angular](https://angular.io) framework. TypeScript here transpiles to JavaScript
<img src="https://github.com/viktorburka/playground/blob/master/ticktactoe-angular/doc/readme-md/tictactoe-angular.png" width="300" height="300">

* [tictacserver](https://github.com/viktorburka/playground/tree/master/tictacserver) is a very besic implementation of what is going to be TicTacToe multiplayer server. It only has some setup code and is written with [Spring](https://spring.io/) framework and Java. Currently only Spring XML setup is done as well as few beans and dependency injection
