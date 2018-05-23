#ifndef _QwerkE_Directory_Defines_H_
#define _QwerkE_Directory_Defines_H_

//////////////////////////////
// QwerkE_Directory_Defines.h
// #defines directories to allow easy file loading
// throughout the framework and across projects.
//////////////////////////////

#ifdef QwerkE_Framework
#define AssetDir "../QwerkE_Common/Resources/"
#define FrameworkDataFolderPath(a) StringAppend("../QwerkE_Framework/Data/", a)
#elif defined(Qwerk_Engine)
#define AssetDir "../QwerkE_FrameWork/QwerkE_Common/Resources/" // 1 directory down
#define FrameworkDataFolderPath(a) StringAppend("../QwerkE_Framework/QwerkE_Framework/Data/", a)
#else
//USER: Set the offset from your project working directory
#define AssetDir "../QwerkE_FrameWork/QwerkE_Common/Resources/"
#endif // QwerkE_Engine

// Define "hardcoded" file names for null objects for ease of use
// but also to ensure consistency and prevent unintended changes.
// Any external files should have matching names for the same reasons.
// TODO: should macros express the file extension? Need to if the loader is looking for that file
// TODO: Procedurally generate null object to guarantee instantiation
#define null_mesh "null_model.obj"
#define null_shader "null_shader"
#define null_texture "null_texture.png"
#define null_material "null_material.msch"
#define null_model "null_model.obj"
#define null_font "null_font.ttf"
#define null_sound "null_sound.wav"

// Define paths to resource folders that can change easily from project
// to project using a preprocessor define. Paths can also change or be
// manipulated at runtime so be careful since this is a good and bad thing.
#define MeshFolderPath(a) StringAppend(AssetDir, "Models/", a) // TODO: Get rid of duplicate mesh path?
#define ShaderFolderPath(a) StringAppend(AssetDir, "Shaders/", a)
#define TextureFolderPath(a) StringAppend(AssetDir, "Textures/", a)
#define ModelFolderPath(a) StringAppend(AssetDir, "Models/", a)
#define FontFolderPath(a) StringAppend(AssetDir, "Fonts/", a)
#define SoundFolderPath(a) StringAppend(AssetDir, "Sounds/", a)
#define SchematicFolderPath(a) StringAppend(AssetDir, "BluePrints_Prefabs_Schematic/", a)
// TODO: Change MaterialFolderPath to use a new material system

// Recipes
#define object_schematic_ext ".osch"
#define material_schematic_ext ".msch"
#define shader_schematic_ext ".ssch"

// TODO: Null schematics
#define null_object_schematic "ObjectRecipe1.osch"
#define null_material_schematic "MaterialRecipe1.msch"
#define null_shader_schematic "LitMaterial.msch"

#endif // !_QwerkE_Directory_Defines_H_
