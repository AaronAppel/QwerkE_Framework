#pragma once

// Define libraries and systems to build
#define GLFW3
#define GLEW
#define OpenGL
#define OpenAL
#define dearimgui

// Define debug vs release macro
#ifdef _DEBUG
#define _QDebug
#elif defined(RELEASE)
#define _QRelease
#else
#pragma warning "Define Debug or Release mode!"
#endif // DEBUG

// Define API level for various functionality
// Currently not being used.
#define _QTesting // Enable testing features and suites

#define _QExample // Working example to show functionality

#ifndef _QAdvancedApi // Fully unlocked API
#define _QSimpleApi // Limited API for simpler usability off the start
#endif

#ifndef ProjectName
#define ProjectName "Qwerk"
#endif

#ifndef FrameworkDir
#define FrameworkStandAlone // #TODO Review Framework assets needs
#define FrameworkDir ""
#endif

#ifndef AssetsDir
#define AssetsDir FrameworkDir "Assets/" // TODO: Remove common assets
#endif

#ifndef LibrariesDir
#define LibrariesDir FrameworkDir "Libraries/"
#endif

#include "../Utilities/StringHelpers.h"

//USER: Set the offset from your project working directory
// You must #define AssetDir "Assets/" (path to assets)

#define FrameworkNullAssetsDir FrameworkDir "Assets/" // Framework null objects to use if user assets fail to load

// Define "hard coded" file names for handling null objects for ease of use
// but also to ensure consistency and prevent unintended changes.
// Any external files should have matching names for the same reasons.
// TODO: should macros express the file extension? Need to if the loader is looking for that file
// TODO: Procedurally generate null object to guarantee instantiation
// TODO: Use file extension as name consistently. Either everywhere, or no where
#define NullFolderPath(fullFileName) StringAppend(FrameworkNullAssetsDir, fullFileName) // TODO: What is this for?

// Define paths to resource folders that can change easily from project
// to project using a preprocessor define. Paths can also change or be
// manipulated at runtime so be careful since this is a good and bad thing.
// #define MeshFolder AssetDir "Meshes/"

#ifdef FrameworkStandAlone
#define MeshesFolderPath(fullFileName) StringAppend(AssetsDir, fullFileName)
#define ShadersFolderPath(fullFileName) StringAppend(AssetsDir, fullFileName)
#define TexturesFolderPath(fullFileName) StringAppend(AssetsDir, fullFileName)
#define FontsFolderPath(fullFileName) StringAppend(AssetsDir, fullFileName)
#define SoundsFolderPath(fullFileName) StringAppend(AssetsDir, fullFileName)
#define ScenesFolderPath(fullFileName) StringAppend(AssetsDir, fullFileName)
#define ConfigsFolderPath(fullFileName) StringAppend(AssetsDir, fullFileName)
#define ObjectSchematicsFolderPath(fullFileName) StringAppend(AssetsDir, fullFileName)
#else
#define MeshesFolderPath(fullFileName) StringAppend(AssetsDir, "Meshes/", fullFileName)
#define ShadersFolderPath(fullFileName) StringAppend(AssetsDir, "Shaders/", fullFileName)
#define TexturesFolderPath(fullFileName) StringAppend(AssetsDir, "Textures/", fullFileName)
#define FontsFolderPath(fullFileName) StringAppend(AssetsDir, "Fonts/", fullFileName)
#define SoundsFolderPath(fullFileName) StringAppend(AssetsDir, "Sounds/", fullFileName)
#define ScenesFolderPath(fullFileName) StringAppend(AssetsDir, "Scenes/", fullFileName)
#define ConfigsFolderPath(fullFileName) StringAppend(AssetsDir, "Configs/", fullFileName)
#define ObjectSchematicsFolderPath(fullFileName) StringAppend(AssetsDir, "BluePrints_Prefabs_Schematic/", fullFileName)
#endif

// Define "hard coded" file names for handling null objects for ease of use
// but also to ensure consistency and prevent unintended changes.
// TODO: should macros express the file extension? Need to if the loader is looking for that file
// TODO: Use file extension as name consistently. Either everywhere, or no where (probably use them everywhere)
#define null_mesh_filename "null_mesh.obj"
#define null_mesh "null_mesh"
#define null_shader "null_shader"
#define null_texture "null_texture.png"
#define null_material "null_material.msch"
#define null_font "null_font.ttf"
#define null_sound "null_sound.wav"
#define null_scene "null_scene.qscene"

// Null schematics
#define null_object_schematic "null_object.osch"
#define null_material_schematic "null_material.msch"
#define null_shader_schematic "null_shader.ssch" // TODO: Maybe use an enum for shader types
#define null_vert_component "null_shader.vert"
#define null_frag_component "null_shader.frag"
#define null_geo_component "null_shader.geo"

// Standardized file extensions
#define vertex_shader_ext "vert"
#define fragment_shader_ext "frag"
#define geometry_shader_ext "geo"
#define object_schematic_ext ".osch"
#define material_schematic_ext "msch"
#define shader_schematic_ext "ssch"
#define scene_ext "qscene"
#define configs_ext "qpref"
