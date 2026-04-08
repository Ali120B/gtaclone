#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
ASSET_DIR="$ROOT_DIR/assets"
TMP_DIR="$ROOT_DIR/.tmp_assets"

mkdir -p "$ASSET_DIR" "$TMP_DIR"

fetch_zip() {
  local url="$1"
  local out="$2"
  echo "Downloading $url"
  curl -L "$url" -o "$TMP_DIR/$out"
}

extract_zip() {
  local zip="$1"
  local target="$2"
  mkdir -p "$ASSET_DIR/$target"
  unzip -o "$TMP_DIR/$zip" -d "$ASSET_DIR/$target" >/dev/null
}

# Kenney + Quaternius + Poly Pizza style open-licensed packs.
fetch_zip "https://opengameart.org/sites/default/files/Prototype%20Textures.zip" "textures.zip"
extract_zip "textures.zip" "textures"

fetch_zip "https://github.com/KhronosGroup/glTF-Sample-Assets/archive/refs/heads/main.zip" "gltf_samples.zip"
extract_zip "gltf_samples.zip" "raw"

mkdir -p "$ASSET_DIR/characters" "$ASSET_DIR/vehicles" "$ASSET_DIR/world" "$ASSET_DIR/audio"

cp -f "$ASSET_DIR/raw/glTF-Sample-Assets-main/Models/Fox/glTF-Binary/Fox.glb" "$ASSET_DIR/characters/player_rig.glb"
cp -f "$ASSET_DIR/raw/glTF-Sample-Assets-main/Models/CesiumMilkTruck/glTF-Binary/CesiumMilkTruck.glb" "$ASSET_DIR/vehicles/truck.glb"
cp -f "$ASSET_DIR/raw/glTF-Sample-Assets-main/Models/ToyCar/glTF-Binary/ToyCar.glb" "$ASSET_DIR/vehicles/sedan.glb"
cp -f "$ASSET_DIR/raw/glTF-Sample-Assets-main/Models/Sponza/glTF-Binary/Sponza.glb" "$ASSET_DIR/world/city_block.glb"

fetch_zip "https://freesound.org/data/previews/250/250629_4486188-lq.mp3" "ambient_city.mp3" || true
fetch_zip "https://freesound.org/data/previews/320/320181_5260872-lq.mp3" "engine_loop.mp3" || true
fetch_zip "https://freesound.org/data/previews/171/171104_2398403-lq.mp3" "pistol.mp3" || true

cp -f "$TMP_DIR/ambient_city.mp3" "$ASSET_DIR/audio/ambient_city.mp3" 2>/dev/null || true
cp -f "$TMP_DIR/engine_loop.mp3" "$ASSET_DIR/audio/engine_loop.mp3" 2>/dev/null || true
cp -f "$TMP_DIR/pistol.mp3" "$ASSET_DIR/audio/pistol.mp3" 2>/dev/null || true

echo "Assets prepared in $ASSET_DIR"
