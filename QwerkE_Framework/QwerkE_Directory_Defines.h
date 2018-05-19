#ifndef _QwerkE_Directory_Defines_H_
#define _QwerkE_Directory_Defines_H_

//////////////////////////////
// QwerkE_Directory_Defines.h
// #defines directories to allow easy file loading
// throughout the framework and across projects.
//////////////////////////////

#ifdef QwerkE_Framework
#define AssetDir "../QwerkE_Common/Resources/"
#else
#define AssetDir "../QwerkE_FrameWork/QwerkE_Common/Resources/" // TEMP: Engine is 1 directory up
#endif // QwerkE_Engine

// Define "hardcoded" file names for null objects for ease of use
// but also to ensure consistency and prevent unintended changes.
// Any external files should have matching names for the same reasons.
// TODO: should macros express the file extension? Need to if the loader is looking for that file
#define null_mesh "null_model.obj"
#define null_shader "null_shader"
#define null_texture "null_texture.png"
#define null_material "null_material.mat"
#define null_model "null_model.obj"
#define null_font "null_font.ttf"

// Define paths to resource folders that can change easily from project
// to project using a preprocessor define. Paths can also change or be
// manipulated at runtime so be careful since this is a good and bad thing.
#define MeshFolderPath(a) StringAppend(AssetDir, "Models/", a) // TODO: Get rid of duplicate mesh path?
#define ShaderFolderPath(a) StringAppend(AssetDir, "Shaders/", a)
#define TextureFolderPath(a) StringAppend(AssetDir, "Textures/", a)
#define MaterialFolderPath(a) StringAppend(AssetDir, "Models/", a)
#define ModelFolderPath(a) StringAppend(AssetDir, "Models/", a)
#define FontFolderPath(a) StringAppend(AssetDir, "Fonts/", a)
// TODO: Change MaterialFolderPath to use a new material system

#endif // !_QwerkE_Directory_Defines_H_
