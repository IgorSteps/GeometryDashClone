# Geometry Dash Clone 
<p align="center">
<img width="645" alt="Screenshot 2022-10-27 at 20 06 30" src="https://user-images.githubusercontent.com/84919282/198377124-1cdf45a4-e9eb-437d-b4f3-5e67c2022019.png">
<img width="632" alt="Screenshot 2022-10-27 at 20 07 28" src="https://user-images.githubusercontent.com/84919282/198377306-52116b4b-0b95-4f87-bcac-e9acde19a046.png">
</p>

## Supported Platforms
Windows

## Overview
A geometry dash clone built with OpenGL, glad, glfw and C++. Supports basic functionality of the real game.


## Features
- Multifunctional Level Editor
- Traingale collisions are implemented through broad/narrow phase collision detections. Narrowphase is using Cohen Sutherland pollygon clipping algorithm.
- Infinite backgrounds
- Serialisation and deserialisation from JSON file

## Controls
| Key               | Action                     |
|-------------------|----------------------------|
| MOUSE_LEFT        | Select object              |
| MOUSE_LEFT + DRAG | Select multiple objects    |
| MOUSE_LEFT + SHIFT| Select multiple objects    |
| MOUSE_RIGHT       | Place object               |
| MOUSE_MIDDLE      | Move around editor         |
| BACKSPACE         | Delete object(s)           |
| CTRL+D            | Duplicate selected object(s)|
| UP                | Move selected object up    |
| DOWN              | Move selected object down  |
| LEFT              | Move selected object left  |
| RIGHT             | Move selected object right |
| SHIFT + direction | Move by small increment    |
| Q                 | Rotate left                |
| E                 | Rotate right               |
| ESC               | Unselect                   |
| 1                 | Save level                 |
| 2                 | Load level                 |
| 3                 | Switch to level            |
| SPACE             | Jump                       |
