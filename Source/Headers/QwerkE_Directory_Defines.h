#ifndef _QwerkE_Directory_Defines_H_
#define _QwerkE_Directory_Defines_H_

//////////////////////////////
// QwerkE_Directory_Defines.h
// #defines directories to allow easy file loading
// throughout the framework and across projects.
// Remove absolute file path dependency and easy
// folder path altering/moving.
//////////////////////////////

//USER: Set the offset from your project working directory
// You must #define AssetDir "Assets/" (path to assets)

#define FrameworkNullAssetsDir FrameworkDir "Assets/" // Framework null objects to use if user assets fail to load

// Define "hard coded" file names for handling null objects for ease of use
// but also to ensure consistency and prevent unintended changes.
// Any external files should have matching names for the same reasons.
// TODO: should macros express the file extension? Need to if the loader is looking for that file
// TODO: Procedurally generate null object to guarantee instantiation
// TODO: Use file extension as name consistently. Either everywhere, or no where
#define NullFolderPath(fullFileName) StringAppend(FrameworkNullAssetsDir, fullFileName) // TOD: What is this for?

// Define paths to resource folders that can change easily from project
// to project using a preprocessor define. Paths can also change or be
// manipulated at runtime so be careful since this is a good and bad thing.
// #define MeshFolder AssetDir "Meshes/"

#define MeshFolderPath(fullFileName) StringAppend(AssetsDir, "Meshes/", fullFileName) // TODO: Get rid of duplicate mesh path?
#define ShaderFolderPath(fullFileName) StringAppend(AssetsDir, "Shaders/", fullFileName)
#define TextureFolderPath(fullFileName) StringAppend(AssetsDir, "Textures/", fullFileName)
#define FontFolderPath(fullFileName) StringAppend(AssetsDir, "Fonts/", fullFileName)
#define SoundFolderPath(fullFileName) StringAppend(AssetsDir, "Sounds/", fullFileName)
#define ObjectSchematicFolderPath(fullFileName) StringAppend(AssetsDir, "BluePrints_Prefabs_Schematic/", fullFileName)
#define SceneFolderPath(fullFileName) StringAppend(AssetsDir, "Scenes/", fullFileName)
#define ConfigsFolderPath(fullFileName) StringAppend(AssetsDir, "Configs/", fullFileName)
// TODO: Change MaterialFolderPath to use a new material system

#endif // !_QwerkE_Directory_Defines_H_
