# Geometry Dash Clone 
<img width="645" alt="Screenshot 2022-10-27 at 20 06 30" src="https://user-images.githubusercontent.com/84919282/198377124-1cdf45a4-e9eb-437d-b4f3-5e67c2022019.png">
<img width="632" alt="Screenshot 2022-10-27 at 20 07 28" src="https://user-images.githubusercontent.com/84919282/198377306-52116b4b-0b95-4f87-bcac-e9acde19a046.png">

## Supported Platforms
Windows

## Overview
A geometry dash clone built with OpenGL, glad, glfw and C++. Supports basic functionality of the real game. This is my first big attempt at making a game following modern game-dev standrads.

## Development
I used Agile methodolgy with 2 week long sprints. Trello Progress board - https://trello.com/b/hYyOTNNf/gd-progress

## Controls
Game starts in level editor so most of the controls in there. 
- `left mouse button` click and hold - move around level editor
- `left mouse button` click - select objects
- `right mouse button` click - place objects into a scene
- `1` - save level
- `2` - load level
- `3` - swith to playing the level

## Most interseting features
- Multifunctional Level Editor
- Uses *a sort of* ECS
- Traingale collisions are implemented through broad/narrow phase collision detections. Narrowphase is using Cohen Sutherland pollygon clipping algorithm.
- Infinite backgrounds
- Serialisation and deserialisation from JSON file
- Correct Git workflow with branches and PRs
