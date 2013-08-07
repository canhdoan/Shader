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

namespace TextHelper
{
	char* ReadFile(const char *pPath)
	{
		FILE *file;
		char *content = NULL;
		
		int count = 0;
		
		// Open file if the path is not null
		if (pPath != NULL)
			file = fopen(pPath, "rt");
		else
			printf("ERROR: Path not exist!");
			
		if (file != NULL)
		{
			fseek(file, 0, SEEK_END);
			count = ftell(file);
			rewind(file);
			if (count > 0)
			{
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content, sizeof(char), count, file);
				content[count] = '\0';
			}
			fclose(file);
		}
		else
		{
			printf("ERROR: File not found!");
		}
		
		return content;
	}

	int WriteFile(char *pPath, char *pSource)
	{
		FILE *file;
		int status = 0;
		
		// Create new file if the path is not null
		if (pPath != NULL)
		{
			file = fopen(pPath, "w");
			
			if (file != NULL)
			{
				if (fwrite(pSource,sizeof(char),strlen(pSource),file) == strlen(pSource))
					status = 1;
				fclose(file);
			}			
		}
		else
		{
			printf("ERROR: Path not exist!");
		}
		
		return status;
	}
};

///////////////////////////////////////////////////////////////////////////////
