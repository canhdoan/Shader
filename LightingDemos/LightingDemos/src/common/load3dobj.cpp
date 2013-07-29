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

	void LoadObjModel()
	{

	}
	
	///
	
	void CalcNormalVector(void)
	{
	
	}
	
	///
	
	void CalcTangentVector(void)
	{
	
	}
	 
	///
	
	void CalcBiTangentVector(void)
	{
	
	}
	
	///
};

///////////////////////////////////////////////////////////////////////////////