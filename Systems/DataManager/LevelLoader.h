#ifndef __LevelLoader_H__
#define __LevelLoader_H__

/*
	Inherits from DataManager(). The code is still abstracted
	but the user has access to protected helpers.
*/
#include "../../Systems/DataManager/DataManager.h"

class Scene;
class Factory;

class LevelLoader : public DataManager
{
public:
	LevelLoader(Factory* factory);
    virtual ~LevelLoader();

	void SaveScene(Scene* scene, const char* fileDir);
	void LoadScene(Scene* scene, const char* fileDir);
};

#endif //!__LevelLoader_H__
