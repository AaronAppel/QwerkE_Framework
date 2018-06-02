#ifndef _QwerkE_Directory_Defines_H_
#define _QwerkE_Directory_Defines_H_

//////////////////////////////
// QwerkE_Directory_Defines.h
// #defines directories to allow easy file loading
// throughout the framework and across projects.
//////////////////////////////

#define FrameworkDataFolderPath(a) StringAppend(FrameworkDir, "QwerkE_Framework/Data/", a)
//USER: Set the offset from your project working directory
// You must #define AssetDir "Resources/" (path to assets)

// Define "hardcoded" file names for null objects for ease of use
// but also to ensure consistency and prevent unintended changes.
// Any external files should have matching names for the same reasons.
// TODO: should macros express the file extension? Need to if the loader is looking for that file
// TODO: Procedurally generate null object to guarantee instantiation
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
#define null_shader_schematic "LitMaterial.ssch"
#define null_vert_component "null_shader.vert"
#define null_frag_component "null_shader.frag"
#define null_geo_component "null_shader.geo"

// Schematic file extensions
#define object_schematic_ext ".osch"
#define material_schematic_ext ".msch"
#define shader_schematic_ext ".ssch"
#define scene_ext ".qscene"

// Define paths to resource folders that can change easily from project
// to project using a preprocessor define. Paths can also change or be
// manipulated at runtime so be careful since this is a good and bad thing.
#define MeshFolderPath(a) StringAppend(AssetDir, "Meshes/", a) // TODO: Get rid of duplicate mesh path?
#define ShaderFolderPath(a) StringAppend(AssetDir, "Shaders/", a)
#define TextureFolderPath(a) StringAppend(AssetDir, "Textures/", a)
#define FontFolderPath(a) StringAppend(AssetDir, "Fonts/", a)
#define SoundFolderPath(a) StringAppend(AssetDir, "Sounds/", a)
#define SchematicFolderPath(a) StringAppend(AssetDir, "BluePrints_Prefabs_Schematic/", a)
#define SceneFolderPath(a) StringAppend(AssetDir, "Scenes/", a)
// TODO: Change MaterialFolderPath to use a new material system



#endif // !_QwerkE_Directory_Defines_H_
