#include "MeshUtilities.h"
#include "MeshData.h"
#include "../../QwerkE_Common/Math_Includes.h"

namespace QwerkE {

	// Scaling
	void ScaleUVCOORDS(std::vector<vec2>& verts, vec2 UVScale)
	{
		for (int i = 0; i < verts.size(); i++)
		{
			//verts[i].uv.x * UVScale.x;
			//verts[i].uv.y * UVScale.y;
		}

		vec2 NewScale;
		NewScale.x = 1.0f / UVScale.x;
		NewScale.y = 1.0f / UVScale.y;

		for (int i = 0; i < verts.size(); i++)
		{
			verts[i].x = verts[i].x / NewScale.x;
			verts[i].y = verts[i].y / NewScale.y;
		}
	}

	void ScaleVertices(std::vector<vec3>& verts, vec3 scale)
	{
		// TODO:: Finish implementing proper vertex scaling

		// pivot point may not be centered.
		// shift object to be centered at 0,0,0 (assume box shape)

		/*
		// calculate distance between farthest points on each axis'
		float lowestX = FLT_MAX;
		float highestX = FLT_MIN;

		for (int i = 0; i < numVerts; i++)
		{
		if (verts[i].pos.x < lowestX)
		{
		lowestX = verts[i].position.x;
		}
		if (verts[i].position.x > highestX)
		{
		highestX = verts[i].position.x;
		}
		}


		// shift
		float distanceX = abs(highestX - lowestX) / 2.0f;

		for (int i = 0; i < numVerts; i++)
		{
		verts[i].position.x = verts[i].position.x + distanceX;
		verts[i].position.y = verts[i].position.y * scale.y;
		verts[i].position.y = verts[i].position.z * scale.z;
		}
		*/

		// scale
		for (int i = 0; i < verts.size(); i++)
		{
			verts[i].x = verts[i].x * scale.x;
			verts[i].y = verts[i].y * scale.y;
			verts[i].z = verts[i].z * scale.z;
		}

		/*
		// shift back
		for (int i = 0; i < numVerts; i++)
		{
		verts[i].position.x = verts[i].position.x - distanceX;
		verts[i].position.y = verts[i].position.y * scale.y;
		verts[i].position.y = verts[i].position.z * scale.z;
		}
		*/
	}
	// Auto UV helpers
	void CalculateUVCoords(std::vector<vec2>& UVs) // fill UV coordinates of each vertex value based on its current position in object space
	{
		if (UVs.size() < 1)
			return;

		// initialize temporary storage values to a valid vertex position to compare with
		vec2 t_InitializeValue = UVs[0];
		// x
		float t_LeftX = t_InitializeValue.x;
		float t_RightX = t_InitializeValue.x;
		// y
		float t_BottomY = t_InitializeValue.y;
		float t_TopY = t_InitializeValue.y;

		// find furthest values / boundaries. These values are the least or greatest X or Y position values
		for (vec2 t_TempValue : UVs)
		{
			if (t_TempValue.x > t_RightX)
			{
				t_RightX = t_TempValue.x;
			}
			if (t_TempValue.x < t_LeftX)
			{
				t_LeftX = t_TempValue.x;
			}
			if (t_TempValue.y < t_BottomY)
			{
				t_BottomY = t_TempValue.y;
			}
			if (t_TempValue.y > t_TopY)
			{
				t_TopY = t_TempValue.y;
			}
		}

		// store values to shift vertex to positive position values
		//x
		float t_ShiftValueX = 0.0f;
		if (t_LeftX < 0.0f)
			t_ShiftValueX = t_LeftX * -1.0f;
		else
			t_ShiftValueX = -t_LeftX;
		//y
		float t_ShiftValueY = 0.0f;
		if (t_BottomY < 0.0f)
			t_ShiftValueY = t_BottomY * -1.0f;
		else
			t_ShiftValueY = -t_BottomY;

		// assign position to UV, using t_ShiftedValue to ensure positive values
		for (unsigned int i = 0; i < UVs.size(); i++)
		{
			UVs.at(i).x = UVs.at(i).x + t_ShiftValueX;
			UVs.at(i).y = UVs.at(i).y + t_ShiftValueY;
		}

		// calculate distance between boundaries in object space
		float t_DistanceX = t_RightX - t_LeftX;
		float t_DistanceY = t_TopY - t_BottomY;

		// normalize UV points to 0 - 1 for UV coord space using the distance between boundaries
		for (unsigned int i = 0; i < UVs.size(); i++)
		{
			if (t_DistanceX != 0.0f && t_DistanceY != 0.0f) // check to make sure we are not dividing by 0
			{
				UVs.at(i).x /= t_DistanceX;
				UVs.at(i).y /= t_DistanceY;
			}
		}
	}

	void CalculateUVCoords(std::vector<vec3>& vertArray, int numVertices) // fill UV coordinates of each vertex value based on its current position in object space
	{
		// initialize temporary storage values to a valid vertex position to compare with
		std::vector<vec3> verts;

		for (int i = 0; i < numVertices; i++)
		{
			verts.push_back(vertArray[i]);
		}

		vec3 t_InitializeValue = verts.at(0);
		// x
		float t_LeftX = t_InitializeValue.x;
		float t_RightX = t_InitializeValue.x;
		// y
		float t_BottomY = t_InitializeValue.y;
		float t_TopY = t_InitializeValue.y;

		// find furthest values / boundaries. These values are the least or greatest X or Y position values
		for (vec3 t_TempValue : verts)
		{
			if (t_TempValue.x > t_RightX)
			{
				t_RightX = t_TempValue.x;
			}
			if (t_TempValue.x < t_LeftX)
			{
				t_LeftX = t_TempValue.x;
			}
			if (t_TempValue.y < t_BottomY)
			{
				t_BottomY = t_TempValue.y;
			}
			if (t_TempValue.y > t_TopY)
			{
				t_TopY = t_TempValue.y;
			}
		}

		// store values to shift vertex to positive position values
		//x
		float t_ShiftValueX = 0.0f;
		if (t_LeftX < 0.0f)
			t_ShiftValueX = t_LeftX * -1.0f;
		else
			t_ShiftValueX = -t_LeftX;
		//y
		float t_ShiftValueY = 0.0f;
		if (t_BottomY < 0.0f)
			t_ShiftValueY = t_BottomY * -1.0f;
		else
			t_ShiftValueY = -t_BottomY;

		// assign position to UV, using t_ShiftedValue to ensure positive values
		for (unsigned int i = 0; i < verts.size(); i++)
		{
			verts.at(i).x = verts.at(i).x + t_ShiftValueX;
			verts.at(i).y = verts.at(i).y + t_ShiftValueY;
		}

		// calculate distance between boundaries in object space
		float t_DistanceX = t_RightX - t_LeftX;
		float t_DistanceY = t_TopY - t_BottomY;

		// normalize UV points to 0 - 1 for UV coord space using the distance between boundaries
		for (unsigned int i = 0; i < verts.size(); i++)
		{
			if (t_DistanceX != 0.0f && t_DistanceY != 0.0f) // check to make sure we are not dividing by 0
			{
				verts.at(i).x /= t_DistanceX;
				verts.at(i).y /= t_DistanceY;
			}
		}

		// transfer uv coords back to array
		for (int i = 0; i < numVertices; i++)
		{
			vertArray[i] = verts.at(i);
		}
	}

	void CalculateXZUVCoords(MeshData& data) // fill UV coordinates of each vertex value based on its current position in object space
	{
		// initialize temporary storage values to a valid vertice position to compare with
		std::vector<vec3> verts;

		for (int i = 0; i < data.positions.size(); i++)
		{
			verts.push_back(data.positions[i]);
		}

		vec3 t_InitializeValue = verts.at(0);
		// x
		float t_LeftX = t_InitializeValue.x;
		float t_RightX = t_InitializeValue.x;
		// y
		float t_BottomZ = t_InitializeValue.z;
		float t_Topz = t_InitializeValue.z;

		// find furthest values / boundaries. These values are the least or greatest X or z position values
		for (vec3 t_TempValue : verts)
		{
			if (t_TempValue.x > t_RightX)
			{
				t_RightX = t_TempValue.x;
			}
			if (t_TempValue.x < t_LeftX)
			{
				t_LeftX = t_TempValue.x;
			}
			if (t_TempValue.z < t_BottomZ)
			{
				t_BottomZ = t_TempValue.z;
			}
			if (t_TempValue.z > t_Topz)
			{
				t_Topz = t_TempValue.z;
			}
		}

		// store values to shift vertex to positive position values
		//x
		float t_ShiftValueX = 0.0f;
		if (t_LeftX < 0.0f)
			t_ShiftValueX = t_LeftX * -1.0f;
		else
			t_ShiftValueX = -t_LeftX;
		//z
		float t_ShiftValuez = 0.0f;
		if (t_BottomZ < 0.0f)
			t_ShiftValuez = t_BottomZ * -1.0f;
		else
			t_ShiftValuez = -t_BottomZ;

		// assign position to UV, using t_ShiftedValue to ensure positive values
		for (unsigned int i = 0; i < verts.size(); i++)
		{
			verts.at(i).x = verts.at(i).x + t_ShiftValueX;
			verts.at(i).y = verts.at(i).z + t_ShiftValuez;
		}

		// calculate distance between boundaries in object space
		float t_DistanceX = t_RightX - t_LeftX;
		float t_DistanceZ = t_Topz - t_BottomZ;

		// normalize UV points to 0 - 1 for UV coord space using the distance between boundaries
		for (unsigned int i = 0; i < verts.size(); i++)
		{
			if (t_DistanceX != 0.0f && t_DistanceZ != 0.0f) // check to make sure we are not dividing by 0
			{
				verts.at(i).x /= t_DistanceX;
				verts.at(i).y /= t_DistanceZ;
			}
		}

		// transfer uv coords back to array
		for (int i = 0; i < data.positions.size(); i++)
		{
			data.positions[i] = verts.at(i);
		}
	}

	void PaintObject(MeshData& colors, vec4 color)
	{
		for (vec4 t_LoopVar : colors.colors) // TODO: Do a memset or similar for efficiency
		{
			t_LoopVar = color;
		}
	}

	void InvertFaces(unsigned int oldIBO[], unsigned int arraySize)
	{
		unsigned int* newIBO = new unsigned int[arraySize];

		for (unsigned int i = 0; i < arraySize; i++)
		{
			newIBO[i] = oldIBO[arraySize - i - 1];
		}

		for (unsigned int i = 0; i < arraySize; i++)
		{
			oldIBO[i] = newIBO[i];
		}

		delete[] newIBO;
	}

	// Tangents and bitangents
	void GenerateTangents()
	{

	}

	void GenerateBitangents()
	{

	}

}
