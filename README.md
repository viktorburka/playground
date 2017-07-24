# playground
This repository is created to experiment with different technologies I've been looking at. Here is a short description of what's in it:

* [minesweeper](https://github.com/viktorburka/playground/tree/master/minesweeper) is [Qt/QML](http://doc.qt.io/qt-5/qtqml-index.html) implementation of a well known Windows game. The busindess logic is written with JavaScript which is a scripting language that QML uses. It emulates some classes via building them through JS [Object.prototype](https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Objects/Object_prototypes) therefore creating classes that can be instantiated and extended and not just dynamically enhancing current one off objects
<img src="https://github.com/viktorburka/playground/blob/master/minesweeper/doc/readme-md/minesweeper.png" width="320" height="280">

* [python-xml-build-script](https://github.com/viktorburka/playground/tree/master/python-xml-build-script) is just a very simple build system implemented in CSV and XML formats written in Python to work with [Microsoft Team Fundation Server](https://www.visualstudio.com/tfs). Its capable of comparing the changes of revision currently being checked in to TFS and if any, building the project and the dependencies which can be specified in either CSV or XML format

* [sine-qml-graphics-scene](https://github.com/viktorburka/playground/tree/master/sine-qml-graphics-scene) is an implementation of sin trigonometric function that renders it on the screen implemented via [Qt Quick Graphics Scene](http://doc.qt.io/qt-5/qtquick-visualcanvas-scenegraph.html) API. It is written in C++ can calls those APIs to render the image utilizing hardware accelerated rendering
<img src="https://github.com/viktorburka/playground/blob/master/sine-qml-graphics-scene/doc/readme-md/sine.png" width="180" height="120">
