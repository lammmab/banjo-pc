#!/bin/bash
set -e

# === Config ===
BUILD_DIR=build
BIN_DIR=bin
CONFIG=Debug
EXE_NAME=banjo

# === Clean previous build folder ===
if [ -d "$BUILD_DIR" ]; then
    echo "Removing old build folder..."
    rm -rf "$BUILD_DIR"
fi

# === Create bin folder if it doesn't exist ===
mkdir -p "$BIN_DIR"

# === Create build directory ===
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# === Configure project with CMake ===
echo "Configuring project..."
cmake -DCMAKE_BUILD_TYPE=$CONFIG ..

# === Build project ===
echo "Building project..."
cmake --build . --config $CONFIG

# === Copy final executable to bin folder ===
if [ -f "$EXE_NAME" ]; then
    echo "Copying executable to $BIN_DIR..."
    cp "$EXE_NAME" "../$BIN_DIR/$EXE_NAME"
elif [ -f "$CONFIG/$EXE_NAME" ]; then
    echo "Copying executable from $CONFIG to $BIN_DIR..."
    cp "$CONFIG/$EXE_NAME" "../$BIN_DIR/$EXE_NAME"
else
    echo "Executable not found!"
    exit 1
fi

cd ..
echo "Build complete! Executable is in $BIN_DIR/$EXE_NAME"
