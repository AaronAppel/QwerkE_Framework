#include "MeshUtilities.h"
#include "VertexData.h"
#include "../../../../../Shared_Generic/Math_Includes.h"

void ScaleUVCOORDS(VertexData verts[], int numVerts, vec2 UVScale)
{
	for (int i = 0; i < numVerts; i++)
	{
		//verts[i].uv.x * UVScale.x;
		//verts[i].uv.y * UVScale.y;
	}

	vec2 NewScale;
	NewScale.x = 1.0f / UVScale.x;
	NewScale.y = 1.0f / UVScale.y;

	for (int i = 0; i < numVerts; i++)
	{
		verts[i].UV.x = verts[i].UV.x / NewScale.x;
		verts[i].UV.y = verts[i].UV.y / NewScale.y;
	}
}

void CalculateUVCoords(std::vector<VertexData> &verts) // fill UV coordinates of each vertex value based on its current position in object space
{
	// initialize temporary storage values to a valid vertex position to compare with
	VertexData t_InitializeValue = verts.at(0);
	// x
	float t_LeftX = t_InitializeValue.position.x;
	float t_RightX = t_InitializeValue.position.x;
	// y
	float t_BottomY = t_InitializeValue.position.y;
	float t_TopY = t_InitializeValue.position.y;

	// find furthest values / boundaries. These values are the least or greatest X or Y position values
	for (VertexData t_TempValue : verts)
	{
		if (t_TempValue.position.x > t_RightX)
		{
			t_RightX = t_TempValue.position.x;
		}
		if (t_TempValue.position.x < t_LeftX)
		{
			t_LeftX = t_TempValue.position.x;
		}
		if (t_TempValue.position.y < t_BottomY)
		{
			t_BottomY = t_TempValue.position.y;
		}
		if (t_TempValue.position.y > t_TopY)
		{
			t_TopY = t_TempValue.position.y;
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
		verts.at(i).UV.x = verts.at(i).position.x + t_ShiftValueX;
		verts.at(i).UV.y = verts.at(i).position.y + t_ShiftValueY;
	}

	// calculate distance between boundaries in object space
	float t_DistanceX = t_RightX - t_LeftX;
	float t_DistanceY = t_TopY - t_BottomY;

	// normalize UV points to 0 - 1 for UV coord space using the distance between boundaries
	for (unsigned int i = 0; i < verts.size(); i++)
	{
		if (t_DistanceX != 0.0f && t_DistanceY != 0.0f) // check to make sure we are not dividing by 0
		{
			verts.at(i).UV.x /= t_DistanceX;
			verts.at(i).UV.y /= t_DistanceY;
		}
	}
}

void CalculateUVCoords(VertexData vertArray[], int numVertices) // fill UV coordinates of each vertex value based on its current position in object space
{
	// initialize temporary storage values to a valid vertice position to compare with
	std::vector<VertexData> verts;

	for (int i = 0; i < numVertices; i++)
	{
		verts.push_back(vertArray[i]);
	}

	VertexData t_InitializeValue = verts.at(0);
	// x
	float t_LeftX = t_InitializeValue.position.x;
	float t_RightX = t_InitializeValue.position.x;
	// y
	float t_BottomY = t_InitializeValue.position.y;
	float t_TopY = t_InitializeValue.position.y;

	// find furthest values / boundaries. These values are the least or greatest X or Y position values
	for (VertexData t_TempValue : verts)
	{
		if (t_TempValue.position.x > t_RightX)
		{
			t_RightX = t_TempValue.position.x;
		}
		if (t_TempValue.position.x < t_LeftX)
		{
			t_LeftX = t_TempValue.position.x;
		}
		if (t_TempValue.position.y < t_BottomY)
		{
			t_BottomY = t_TempValue.position.y;
		}
		if (t_TempValue.position.y > t_TopY)
		{
			t_TopY = t_TempValue.position.y;
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
		verts.at(i).UV.x = verts.at(i).position.x + t_ShiftValueX;
		verts.at(i).UV.y = verts.at(i).position.y + t_ShiftValueY;
	}

	// calculate distance between boundaries in object space
	float t_DistanceX = t_RightX - t_LeftX;
	float t_DistanceY = t_TopY - t_BottomY;

	// normalize UV points to 0 - 1 for UV coord space using the distance between boundaries
	for (unsigned int i = 0; i < verts.size(); i++)
	{
		if (t_DistanceX != 0.0f && t_DistanceY != 0.0f) // check to make sure we are not dividing by 0
		{
			verts.at(i).UV.x /= t_DistanceX;
			verts.at(i).UV.y /= t_DistanceY;
		}
	}

	// transfer uv coords back to array

	for (int i = 0; i < numVertices; i++)
	{
		vertArray[i].UV = verts.at(i).UV;
	}
}

void CalculateXZUVCoords(VertexData vertArray[], int numVertices) // fill UV coordinates of each vertex value based on its current position in object space
{
	// initialize temporary storage values to a valid vertice position to compare with
	std::vector<VertexData> verts;

	for (int i = 0; i < numVertices; i++)
	{
		verts.push_back(vertArray[i]);
	}

	VertexData t_InitializeValue = verts.at(0);
	// x
	float t_LeftX = t_InitializeValue.position.x;
	float t_RightX = t_InitializeValue.position.x;
	// y
	float t_BottomZ = t_InitializeValue.position.z;
	float t_Topz = t_InitializeValue.position.z;

	// find furthest values / boundaries. These values are the least or greatest X or z position values
	for (VertexData t_TempValue : verts)
	{
		if (t_TempValue.position.x > t_RightX)
		{
			t_RightX = t_TempValue.position.x;
		}
		if (t_TempValue.position.x < t_LeftX)
		{
			t_LeftX = t_TempValue.position.x;
		}
		if (t_TempValue.position.z < t_BottomZ)
		{
			t_BottomZ = t_TempValue.position.z;
		}
		if (t_TempValue.position.z > t_Topz)
		{
			t_Topz = t_TempValue.position.z;
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
		verts.at(i).UV.x = verts.at(i).position.x + t_ShiftValueX;
		verts.at(i).UV.y = verts.at(i).position.z + t_ShiftValuez;
	}

	// calculate distance between boundaries in object space
	float t_DistanceX = t_RightX - t_LeftX;
	float t_DistanceZ = t_Topz - t_BottomZ;

	// normalize UV points to 0 - 1 for UV coord space using the distance between boundaries
	for (unsigned int i = 0; i < verts.size(); i++)
	{
		if (t_DistanceX != 0.0f && t_DistanceZ != 0.0f) // check to make sure we are not dividing by 0
		{
			verts.at(i).UV.x /= t_DistanceX;
			verts.at(i).UV.y /= t_DistanceZ;
		}
	}

	// transfer uv coords back to array

	for (int i = 0; i < numVertices; i++)
	{
		vertArray[i].UV = verts.at(i).UV;
	}
}

void PaintObject(std::vector<VertexData> &verts, vec4 color)
{
	for (VertexData t_LoopVar : verts)
	{
		t_LoopVar.color = color;
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

void ScaleVertices(VertexData verts[], int numVerts, vec3 scale)
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
	for (int i = 0; i < numVerts; i++)
	{
		verts[i].position.x = verts[i].position.x * scale.x;
		verts[i].position.y = verts[i].position.y * scale.y;
		verts[i].position.z = verts[i].position.z * scale.z;
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