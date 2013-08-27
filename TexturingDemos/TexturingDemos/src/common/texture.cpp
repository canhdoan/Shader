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

namespace Texture
{
	GLuint LoadBmpTexture(const char *pImage)
	{
		unsigned char header[54]; // Each BMP file begins by a 54-bytes header
		unsigned int dataPos;     // Position in the file where the actual data begins
		unsigned int width, height;
		unsigned int imageSize;   // = width*height*3
		unsigned char * data;
		// Open the file
	    FILE * file = fopen(pImage,"rb");
	    if (!file)
	    {
	        printf("Image could not be opened\n");
	        return 0;
	    }

	    if (fread(header, 1, 54, file)!=54)
	    { 
	        // If not 54 bytes read : problem
	        printf("Not a correct BMP file\n");
	        return 0;
	    }

	    if (header[0] != 'B' || header[1] != 'M')
	    {
	        printf("Not a correct BMP file\n");
	        return 0;
	    }

	    // Read ints from the byte array
	    dataPos    = *(int*)&(header[0x0A]);
	    imageSize  = *(int*)&(header[0x22]);
	    width      = *(int*)&(header[0x12]);
	    height     = *(int*)&(header[0x16]);

	    // Some BMP files are misformatted, guess missing information
	    if (imageSize==0)
	        imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	    
	    if (dataPos==0)
	        dataPos=54; // The BMP header is done that way

	    // Create a buffer
	    data = new unsigned char [imageSize];
	     
	    // Read the actual data from the file into the buffer
	    fread(data,1,imageSize,file);
	     
	    //Everything is in memory now, the file can be closed
	    fclose(file);

	    // Create OpenGL texture
	    GLuint textureID;
	    glGenTextures(1, &textureID);

	    // Bind the new texture has created
	    glBindTexture(GL_TEXTURE_2D, textureID);

	    // Give the image to the OpenGL
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	    return textureID;
	}

	/*RGBbytepixel* BMP_Loader(const char *filename)
	{
		FILE *fp;
		sBMP_header *header;
		sBMP_info *info;
		DWORD_ alignedBytesPerScanline;
		DWORD_ fileSize;
		BYTE_ *fileBuffer;
		BYTE_ *data;
		DWORD_ i, x, y;
		RGBbytepixel *pixel;
		RGBbytepixel *pixmap;

		if( (fp = fopen(filename, "rb")) == NULL )
		{
			return(NULL);
		}

		// Move fp to the end.
		fseek( fp, 0 ,SEEK_END );
		
		// get the file size.
		fileSize = (DWORD_)ftell( fp );

		// Move fp to the beginning.
		fseek( fp, 0 ,SEEK_SET );

		// Alloc a buffer to store the whole file
		fileBuffer = (BYTE_ *)malloc( fileSize * sizeof(BYTE_) );
		if( fileBuffer==NULL )
		{
			return(NULL);
		}

		// Read file entirely.
		fread( fileBuffer, fileSize * sizeof(BYTE_), 1, fp );

		// Ok, the is in buffer, so we can close the file.
		fclose( fp );

		// Retrieval of bmp file header structure.
		header = (sBMP_header *)fileBuffer;

		// Retrieval of bmp file info structure.
		info = (sBMP_info *)(fileBuffer + 14 );


		// Check right format. //////////////////////////////////////////////////////

		if(info->LargeurImage != 256 || info->HauteurImage !=256 )
		{
			free( fileBuffer );
			printf( "\nLoading image failed. Must be 256x256." );
			return(NULL);
		}

		if(info->BitParPixel != 24 ) 
		{
			free( fileBuffer );
			printf( "\nLoading image failed. Must be 24 bits/pixels." );
			return(NULL);
		}

		if(info->FormatCompressImage != 0 )
		{
			free( fileBuffer );
			return(NULL);
		}

		// Retrieval bmp data.
		data = (BYTE_ *)(fileBuffer + 14 + 40 );

		// Allocate a buffer to store the bitmap data.
		pixmap = new RGBbytepixel[info->LargeurImage * info->HauteurImage];
		if( pixmap==NULL )
		{
			free( fileBuffer );
			return(NULL);
		}


		// Compute the aligned bytes per scanline.
		alignedBytesPerScanline = (((info->LargeurImage * 24) + 31) & ~31) >> 3;

		i=0;
		for( y = 0; y < info->HauteurImage; y++ )
		{
			pixel = (RGBbytepixel *)(data + (y * alignedBytesPerScanline));

			for( x=0; x<info->LargeurImage; x++ )
			{
				( (RGBbytepixel*)pixmap + i )->m_R = pixel->m_B; 
				( (RGBbytepixel*)pixmap + i )->m_G = pixel->m_G; 
				( (RGBbytepixel*)pixmap + i )->m_B = pixel->m_R; 
				i++;
				pixel++;
			}
		}

		g_texture_width = info->LargeurImage;
		g_texture_height = info->HauteurImage;

		free( fileBuffer );

		return(pixmap);
	}*/
	
	
	/*GLuint LoadJpgTexture(const char *pImage)
	{
		
	}*/
};


///////////////////////////////////////////////////////////////////////////////
