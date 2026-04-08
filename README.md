# Open City Clone (Custom C++ Engine)

A modular, custom-engine 3D sandbox inspired by GTA-style gameplay.

## Stack
- OpenGL (rendering)
- GLFW (window/input)
- GLM (math)
- Assimp (GLTF/FBX loading)
- Bullet (physics integration scaffold)
- OpenAL (3D audio)

## Features Implemented
- Custom engine loop with modular systems.
- World chunk streaming manager with dynamic chunk activation.
- Third-person style player movement (walk/run/jump).
- Vehicle enter/exit and vehicle driving model.
- NPC crowd simulation + flee behavior when threatened.
- Shooting/hit detection + ammo + health state model.
- Start menu state and in-game state switching.
- Asset downloader script that fetches open 3D models, textures, and audio.

## Controls
- `Enter`: start from main menu
- `WASD`: movement / driving
- `Shift`: run
- `Space`: jump
- `F`: shoot
- `E`: enter/exit vehicle
- `M`: return to menu
- `Esc`: quit

## Build
```bash
cmake -S . -B build
cmake --build build -j
```

## Download all assets
```bash
./scripts/download_assets.sh
```

## Run
```bash
./build/open_city
```

## Project Layout
- `src/engine/core` – app loop / bootstrap
- `src/engine/render` – OpenGL renderer
- `src/engine/physics` – Bullet setup
- `src/engine/world` – chunk streaming
- `src/engine/gameplay` – player/vehicle/npc/combat/hud-state logic
- `src/engine/assets` – Assimp-based asset loading + cache
- `src/engine/audio` – OpenAL listener setup
- `src/engine/input` – keyboard input handling

