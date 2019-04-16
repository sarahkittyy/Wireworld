# Wireworld

A wireworld cellular automata simulator in C++.

## Building

### Dependencies

* SFML

```bash
mkdir build
cd build
cmake ..
make

cd ..
./build/Wireworld
# Make sure that `resource/` is in the working directory of Wireworld!
```

## Controls

| Key | Function |
|-|-|
|Space| Pause/Play. |
|R| Reset the grid. |
|Middle Click|Pan the grid|
|Scroll| Zoom in/out.|
|Left/Right Click| Change cell state. (empty/wire/head/tail) |
|+ / -| Increase/Decrease simulation speed. |