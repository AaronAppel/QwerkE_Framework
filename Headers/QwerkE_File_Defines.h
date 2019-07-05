#ifndef _QwerkE_File_Defines_H_
#define _QwerkE_File_Defines_H_

//////////////////////////////
// QwerkE_File_Defines.h
// #defines files to allow easy, standardized, file referencing
// throughout the framework and across projects.
//////////////////////////////

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

// Standardized file names
#define no_file "None"

#endif // !_QwerkE_File_Defines_H_
