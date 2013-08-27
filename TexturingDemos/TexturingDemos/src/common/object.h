///////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2010 AsNet Co., Ltd.
// All Rights Reserved. These instructions, statements, computer
// programs, and/or related material (collectively, the "Source")
// contain unpublished information proprietary to AsNet Co., Ltd
// which is protected by US federal copyright law and by 
// international treaties. This Source may NOT be disclosed to 
// third parties, or be copied or duplicated, in whole or in 
// part, without the written consent of AsNet Co., Ltd.
///////////////////////////////////////////////////////////////////////////////
// Author: Canh Doan
///////////////////////////////////////////////////////////////////////////////

#ifndef APP_COMMON_OBJECT_H
#define APP_COMMON_OBJECT_H

///////////////////////////////////////////////////////////////////////////////
// Type Declaration
#define MAX_VERTICES 10000 // Max number of vertices (for each object)
#define MAX_POLYGONS 10000 // Max number of polygons (for each object)
// Vertex type
typedef struct vertex_type
{
	float x, y, z;
} VERTEX;

// Texture coordinate type
typedef struct texture_coordinate
{
	float u, v;
} TEXTCOORD;

// Polygon type (Triangle)
typedef struct polygon_type
{
	unsigned short a, b, c;
}POLYGON;

// 3DS object type
typedef struct object_type_3ds
{
	// Name of object
	char name[20];
	
	int num_vertices; // Number of vertices
    int num_polygons; // Number of polygons

    VERTEX vertex[MAX_VERTICES]; // Array of vertices
    VERTEX normal[MAX_VERTICES]; // Array of the vertices' normals
    POLYGON polygon[MAX_POLYGONS]; // Array of polygons (numbers that point to the vertices' list)
    TEXTCOORD textcoord[MAX_VERTICES]; // Array of U,V coordinates for texture mapping

    unsigned int texture_id; // Number of the texture 
	
} OBJECT_3DS, *OBJECT_3DS_PTR;


typedef struct object_type_obj
{
	int num_vertices; // Number of vertices
	int num_polygons; // Number of polygon
	
	VERTEX vertex[MAX_VERTICES]; // Array of vertices
    VERTEX normal[MAX_VERTICES]; // Array of the vertices' normals
	TEXTCOORD textcoord[MAX_VERTICES]; // Array of U,V coordinates for texture mapping
	POLYGON polygon[MAX_POLYGONS]; // Array of polygons (numbers that point to the vertices' list)

	unsigned int texture_id; // Number of the texture
}OBJECT_OBJ, *OBJECT_OBJ_PTR;

#endif // APP_COMMON_OBJECT_H

///////////////////////////////////////////////////////////////////////////////
