#include "QwerkE_AssimpLoading.h"
#include "Graphics/Mesh/Mesh.h"
#include "Graphics/Mesh/MeshData.h"
#include "Graphics/DataTypes/Material.h"
#include "Graphics/DataTypes/Texture.h"
#include "Systems/Resources/Resources.h"
#include "Graphics/GraphicsUtilities/GraphicsHelpers.h"
#include "../../Utilities/StringHelpers.h"
#include "../../Systems/FileSystem/FileIO/FileUtilities.h"

#pragma warning( disable : 26495 )
#include "../../Libraries/assimp/Importer.hpp"
#include "../../Libraries/assimp/scene.h"
#include "../../Libraries/assimp/postprocess.h"
#include "../../Libraries/assimp/config.h"
#include "../../Libraries/assimp/material.h"
#pragma warning( enable : 26495 )

// TODO: Support triangle and quad rendering? Set a macro to define the number of verts per face?
// TODO: Split functions into smaller pieces. Ex. LoadMeshFromAI() can call functions to GetVertsFromAIMesh, GetUVs, GetMats... etc

namespace QwerkE {

    // private functions
    Mesh* QwerkE_assimp_loadVertexData(aiMesh* mesh, const aiScene* scene, const char* modelFilePath);
    void QwerkE_assimp_loadMaterialTextures(aiMaterial* mat, const std::string& filePath, std::vector<std::string>& matNames);

    void QwerkE_assimp_loadSceneNodeData(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes, const std::string& filePath, std::vector<std::string>& matNames)
    {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // load VertexData
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(QwerkE_assimp_loadVertexData(mesh, scene, filePath.c_str()));

            // load Textures + materials
            if (mesh->mMaterialIndex >= 0) // has material?
                QwerkE_assimp_loadMaterialTextures(scene->mMaterials[mesh->mMaterialIndex], filePath, matNames);
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            QwerkE_assimp_loadSceneNodeData(node->mChildren[i], scene, meshes, filePath, matNames);
        }
    }

    Mesh* QwerkE_assimp_loadVertexData(aiMesh* mesh, const aiScene* scene, const char* modelFilePath)
    {
        if (Resources::MeshExists(GetFileNameWithExt(modelFilePath).c_str()))
        {
            return Resources::GetMesh(GetFileNameWithExt(modelFilePath).c_str());
        }
        // process vertex positions, normals and texture coordinates
        // std::vector<VertexData> vertices(totalVerts); // TODO: Swap to array? // PERF: really good use of a 1 frame stack allocation
        // VertexData vertex; // create outside? not a major improvement but still...
        MeshData data;
        data.positions.resize(mesh->mNumVertices);
        data.UVs.resize(mesh->mNumVertices);
        data.normals.resize(mesh->mNumVertices);
        data.tangents.resize(mesh->mNumVertices);
        data.bitangents.resize(mesh->mNumVertices);

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            // vertex positions
            vec3 pos;
            pos.x = mesh->mVertices[i].x;
            pos.y = mesh->mVertices[i].y;
            pos.z = mesh->mVertices[i].z;

            data.positions[i] = pos;

            // color
            // TODO: mesh->HasVertexColors()
            // vertex.color = vec4(mesh->mColors[i]->r, mesh->mColors[i]->g, mesh->mColors[i]->b, mesh->mColors[i]->a);

            // UVs
            // TODO: if (mesh->HasTextureCoords(?)) // does the mesh contain texture coordinates?
            data.UVs[i] = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

            // normals
            if (mesh->HasNormals()) // TODO: Separate loop to handle no normals and avoid if check
            {
                data.normals[i] = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            }

            // Tangents and Bitangents
            if (mesh->HasTangentsAndBitangents()) // Separate loop
            {
                data.tangents[i] = vec3(mesh->mTangents->x, mesh->mTangents->y, mesh->mTangents->z);
                data.bitangents[i] = vec3(mesh->mBitangents->x, mesh->mBitangents->y, mesh->mBitangents->z);
            }
        }

        // process indices
        std::vector<unsigned int> indices(mesh->mNumFaces * 3); // TODO: Swap to array? // PERF: really good use of a 1 frame stack allocation
        aiFace face;
        int counter = 0;
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices[counter++] = face.mIndices[j]; // For each vertex in face
        }

        data.indices = indices;
        Mesh* rMesh = nullptr;

        // TODO: More error checking + handling
        if (data.positions.size() > 0)
        {
            // init mesh and return it
            rMesh = new Mesh();
            rMesh->BufferMeshData(&data);
            rMesh->SetName(mesh->mName.C_Str());
            rMesh->SetFileName(GetFileNameWithExt(modelFilePath));
            Resources::AddMesh(rMesh->GetName().c_str(), rMesh);
        }
        else
            rMesh = Resources::GetMesh(null_mesh);

        return rMesh;
    }

    void QwerkE_assimp_loadMaterialTextures(aiMaterial* mat, const std::string& filePath, std::vector<std::string>& matNames)
    {
        // check if material is already loaded
        aiString name;
        mat->Get(AI_MATKEY_NAME, name);
        // TODO: Support "DefaultMaterial"
        if (Resources::MaterialExists(name.C_Str()))
        {
            // material exists already
        }
        else
        {
            //create new material
            Material* material = new Material(); // TODO: delete if null
            material->SetMaterialName(name.C_Str());
            // load each map/texture into a new material

            // iterate through all known texture types, then load the textures
            // into the Resources and assign handles to the return material.
            // mat->GetTextureCount(); // optimization
            int num = aiTextureType_UNKNOWN - 1;
            for (int i = aiTextureType_NONE + 1; i < num; i++)
            {
                aiString str;
                Texture* texture = nullptr;

                mat->GetTexture((aiTextureType)i, 0, &str);

                if (*str.C_Str())
                {
                    texture = Resources::GetTexture(str.C_Str());
                }

                // handle = 1;
                switch (i)
                {
                case aiTextureType_DIFFUSE:
                    material->AddTexture(texture, eMaterialMaps::MatMap_Diffuse);
                    break;
                case aiTextureType_SPECULAR:
                    material->AddTexture(texture, eMaterialMaps::MatMap_Specular);
                    break;
                case aiTextureType_AMBIENT:
                    material->AddTexture(texture, eMaterialMaps::MatMap_Ambient);
                    break;
                case aiTextureType_EMISSIVE:
                    material->AddTexture(texture, eMaterialMaps::MatMap_Emissive);
                    break;
                case aiTextureType_HEIGHT:
                    material->AddTexture(texture, eMaterialMaps::MatMap_Height);
                    break;
                case aiTextureType_NORMALS:
                    material->AddTexture(texture, eMaterialMaps::MatMap_Normals);
                    break;
                case aiTextureType_SHININESS:
                    material->AddTexture(texture, eMaterialMaps::MatMap_Shininess);
                    break;
                case aiTextureType_OPACITY:
                    material->AddTexture(texture, eMaterialMaps::MatMap_Opacity);
                    break;
                case aiTextureType_DISPLACEMENT:
                    material->AddTexture(texture, eMaterialMaps::MatMap_Displacement);
                    break;
                case aiTextureType_LIGHTMAP:
                    material->AddTexture(texture, eMaterialMaps::MatMap_LightMap);
                    break;
                case aiTextureType_REFLECTION:
                    material->AddTexture(texture, eMaterialMaps::MatMap_Reflection);
                    break;
                }
            }

            // TODO: Support external material loading
            // resMan->AddMaterial(data->s_Name.c_str(), data); // add initialized material
        }

        matNames.push_back(name.C_Str()); // get name for mat loading later
    }

    void QwerkE_assimp_loadMeshByName(aiNode* node, const aiScene* scene, Mesh*& mesh, const char* modeFilePath, const char* meshName)
    {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // load VertexData
            aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
            if (strcmp(aimesh->mName.C_Str(), meshName) == 0)
            {
                mesh = QwerkE_assimp_loadVertexData(aimesh, scene, modeFilePath);
                return;
            }
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            QwerkE_assimp_loadMeshByName(node->mChildren[i], scene, mesh, modeFilePath, meshName);
        }
    }

    void QwerkE_assimp_loadModelAs1Mesh(aiNode* node, const aiScene* scene, Mesh*& mesh, const char* modelFilePath)
    {
        // TODO: write function. probably a good idea to cleanup above functions and split them up to use here.
        mesh = nullptr;
    }

}
