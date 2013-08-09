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

#include "package.h"

///////////////////////////////////////////////////////////////////////////////

namespace Load3DObj
{
	void Load3dsModel(char *pFileName, OBJECT_3DS_PTR pObject)
	{
		int i; //Index variable
	
		FILE *l_file; //File pointer
		
		unsigned short l_chunk_id; //Chunk identifier
		unsigned int l_chunk_length; //Chunk length

		unsigned char l_char; //Char variable
		unsigned short l_qty; //Number of elements in each chunk

		unsigned short l_face_flags; //Flag that stores some face information

		if (pFileName =='\0')
			printf("ERROR: The file name is empty!");

		if ((l_file=fopen (pFileName, "rb"))== NULL) 
		{
			printf("ERROR: 3DS file not found!");
		}

		while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file 
		{
			//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

			fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
			printf("ChunkID: %x\n",l_chunk_id); 
			fread (&l_chunk_length, 4, 1, l_file); //Read the length of the chunk
			printf("ChunkLength: %x\n",l_chunk_length);

			switch (l_chunk_id)
			{
				//----------------- MAIN3DS -----------------
				// Description: Main chunk, contains all the other chunks
				// Chunk ID: 4d4d 
				// Chunk Length: 0 + sub chunks
				//-------------------------------------------
				case 0x4d4d: 
				break;    

				//----------------- EDIT3DS -----------------
				// Description: 3D Editor chunk, objects layout info 
				// Chunk ID: 3d3d (hex)
				// Chunk Length: 0 + sub chunks
				//-------------------------------------------
				case 0x3d3d:
				break;
				
				//--------------- EDIT_OBJECT ---------------
				// Description: Object block, info for each object
				// Chunk ID: 4000 (hex)
				// Chunk Length: len(object name) + sub chunks
				//-------------------------------------------
				case 0x4000: 
					i=0;
					do
					{
						fread (&l_char, 1, 1, l_file);
						pObject->name[i]=l_char;
						i++;
					}while(l_char != '\0' && i<20);
				break;

				//--------------- OBJ_TRIMESH ---------------
				// Description: Triangular mesh, contains chunks for 3d mesh info
				// Chunk ID: 4100 (hex)
				// Chunk Length: 0 + sub chunks
				//-------------------------------------------
				case 0x4100:
				break;
				
				//--------------- TRI_VERTEXL ---------------
				// Description: Vertices list
				// Chunk ID: 4110 (hex)
				// Chunk Length: 1 x unsigned short (number of vertices) 
				//             + 3 x float (vertex coordinates) x (number of vertices)
				//             + sub chunks
				//-------------------------------------------
				case 0x4110: 
					fread (&l_qty, sizeof (unsigned short), 1, l_file);
					pObject->num_vertices = l_qty;
					printf("Number of vertices: %d\n",l_qty);
					if (l_qty>MAX_VERTICES) 
					{
						printf("ERROR: Number of vertices too high!");
					}
					for (i=0; i<l_qty; i++)
					{
						fread (&pObject->vertex[i].x, sizeof(float), 1, l_file);
						printf("Vertices list x: %f\n",pObject->vertex[i].x);
						fread (&pObject->vertex[i].y, sizeof(float), 1, l_file);
						printf("Vertices list y: %f\n",pObject->vertex[i].y);
						fread (&pObject->vertex[i].z, sizeof(float), 1, l_file);
						printf("Vertices list z: %f\n",pObject->vertex[i].z);
					}
					break;

				//--------------- TRI_FACEL1 ----------------
				// Description: Polygons (faces) list
				// Chunk ID: 4120 (hex)
				// Chunk Length: 1 x unsigned short (number of polygons) 
				//             + 3 x unsigned short (polygon points) x (number of polygons)
				//             + sub chunks
				//-------------------------------------------
				case 0x4120:
					fread (&l_qty, sizeof (unsigned short), 1, l_file);
					pObject->num_polygons = l_qty;
					printf("Number of polygons: %d\n",l_qty); 
					if (l_qty>MAX_POLYGONS) 
					{
						printf("ERROR: Number of polygons too high!");
					}				
					for (i=0; i<l_qty; i++)
					{
						fread (&pObject->polygon[i].a, sizeof (unsigned short), 1, l_file);
						printf("Polygon point a: %d\n",pObject->polygon[i].a);
						fread (&pObject->polygon[i].b, sizeof (unsigned short), 1, l_file);
						printf("Polygon point b: %d\n",pObject->polygon[i].b);
						fread (&pObject->polygon[i].c, sizeof (unsigned short), 1, l_file);
						printf("Polygon point c: %d\n",pObject->polygon[i].c);
						fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
						printf("Face flags: %x\n",l_face_flags);
					}
					break;

				//------------- TRI_MAPPINGCOORS ------------
				// Description: Vertices list
				// Chunk ID: 4140 (hex)
				// Chunk Length: 1 x unsigned short (number of mapping points) 
				//             + 2 x float (mapping coordinates) x (number of mapping points)
				//             + sub chunks
				//-------------------------------------------
				case 0x4140:
					fread (&l_qty, sizeof (unsigned short), 1, l_file);
					for (i=0; i<l_qty; i++)
					{
						fread (&pObject->textcoord[i].u, sizeof (float), 1, l_file);
						printf("Mapping list u: %f\n",pObject->textcoord[i].u);
						fread (&pObject->textcoord[i].v, sizeof (float), 1, l_file);
						printf("Mapping list v: %f\n",pObject->textcoord[i].v);
					}
					break;

				//----------- Skip unknow chunks ------------
				//We need to skip all the chunks that currently we don't use
				//We use the chunk length information to set the file pointer
				//to the same level next chunk
				//-------------------------------------------
				default:
					 fseek(l_file, l_chunk_length-6, SEEK_CUR);
			} 
		}
		fclose (l_file); // Closes the file stream
	}
	
	///

	void LoadObjModel(char *pFileName, OBJECT_3DS_PTR pObject)
	{
		int vertexIndices, uvIndices, normalIndices, poligonIndices;
		vertexIndices = 0;
		uvIndices = 0;
		normalIndices = 0;
		poligonIndices = 0;

		VERTEX vertex[MAX_VERTICES];
		VERTEX normal[MAX_VERTICES];
		TEXTCOORD textcoord[MAX_VERTICES];

		float x, y, z; // vertex coordinate

		// variable for load polygon
		float vt1, vt2, vt3, uv1, uv2, uv3, vn1, vn2,vn3;


		FILE *file = fopen(pFileName, "rb");
		if (file == NULL)
		{
			printf("ERROR: %s is not exist!\n", pFileName);
			return;
		}

		while(1)
		{
			char lineHeader[128];
			// Read the first word of line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break;

			if (strcmp(lineHeader, "v") == 0)
			{
				fscanf(file, "%f %f %f\n", &x, &y, &z);
				vertex[vertexIndices].x = x;
				vertex[vertexIndices].y = y;
				vertex[vertexIndices].z = z;
				++vertexIndices;
			}
			else if (strcmp(lineHeader, "vt") == 0)
			{
				fscanf(file, "%f %f\n", &x, &y);
				// y = -y; // invert the v coordinate if use for *.dds texture. This line of code need to remove if use the *.bmp or *.tga texture
				textcoord[uvIndices].u = x;
				textcoord[uvIndices].v = y;
				++uvIndices;
			}
			else if (strcmp(lineHeader, "vn") == 0)
			{
				fscanf(file, "%f %f %f\n", &x, &y, &z);
				normal[normalIndices].x = x;
				normal[normalIndices].y = y;
				normal[normalIndices].z = z;
				++normalIndices;
			}
			else if (strcmp(lineHeader, "f") == 0)
			{
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vt1, %uv1, %vn1, &vt2, %uv2, %vn2, &vt3, %uv3, %vn3);
				if (matches != 9)
				{
					printf("ERROR: Can not parse polygon index!");
					return;
				}
			}
		}
	}
	
	///
	
	void CalcNormalVector(OBJECT_3DS_PTR pObject)
	{
		// Some variable local
		int i;
		glm::vec3 vec1, vec2, vec3, bvec1, bvec2 ,vec_normal;
		int polygon_connection[MAX_VERTICES]; // number of polygon around each vertex
		
		// Reset normal array
		for (i = 0; i < pObject->num_vertices; i++)
		{
			pObject->normal[i].x = 0.0;
			pObject->normal[i].y = 0.0;
			pObject->normal[i].z = 0.0;
			polygon_connection[i] = 0;
		}
		
		// Calculate normal vector
		for (i = 0; i < pObject->num_polygons; i++)
		{
			vec1.x = pObject->vertex[pObject->polygon[i].a].x;
			vec1.y = pObject->vertex[pObject->polygon[i].a].y;
			vec1.z = pObject->vertex[pObject->polygon[i].a].z;
			
			vec2.x = pObject->vertex[pObject->polygon[i].b].x;
			vec2.y = pObject->vertex[pObject->polygon[i].b].y;
			vec2.z = pObject->vertex[pObject->polygon[i].b].z;
			
			vec3.x = pObject->vertex[pObject->polygon[i].c].x;
			vec3.y = pObject->vertex[pObject->polygon[i].c].y;
			vec3.z = pObject->vertex[pObject->polygon[i].c].z;
			
			// Polygon normal calculation
			bvec1 = vec1 - vec2; // Vector from first vertex to second vertex
			bvec2 = vec1 - vec3; // Vector form first vertex to third vertex
			vec_normal = glm::cross(bvec1, bvec2); // Normalize dot product of two vector
			vec_normal = glm::normalize(vec_normal);

			// For each vertex shared by polygon, increase connection
			polygon_connection[pObject->polygon[i].a] += 1;
			polygon_connection[pObject->polygon[i].b] += 1;
			polygon_connection[pObject->polygon[i].c] += 1;

			// For each polygon, add normal vector
			pObject->normal[pObject->polygon[i].a].x += vec_normal.x;
			pObject->normal[pObject->polygon[i].a].y += vec_normal.y;
			pObject->normal[pObject->polygon[i].a].z += vec_normal.z;

			pObject->normal[pObject->polygon[i].b].x += vec_normal.x;
			pObject->normal[pObject->polygon[i].b].y += vec_normal.y;
			pObject->normal[pObject->polygon[i].b].z += vec_normal.z;

			pObject->normal[pObject->polygon[i].c].x += vec_normal.x;
			pObject->normal[pObject->polygon[i].c].y += vec_normal.y;
			pObject->normal[pObject->polygon[i].c].z += vec_normal.z;
		}

		// Average polygon normal to obtain vertex normal
		for (i = 0; i < pObject->num_vertices; ++i)
		{
			if (polygon_connection[i] > 0)
			{
				pObject->normal[i].x /= polygon_connection[i];
				pObject->normal[i].y /= polygon_connection[i];
				pObject->normal[i].z /= polygon_connection[i];
			}
		}
	}
	
	///
	
	void CalcTangentVector(OBJECT_3DS_PTR pObject)
	{
	
	}
	 
	///
	
	void CalcBiTangentVector(OBJECT_3DS_PTR pObject)
	{
	
	}
	
	///
};

///////////////////////////////////////////////////////////////////////////////