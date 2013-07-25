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

#ifndef APP_COMMON_TEXTHELPER_H
#define APP_COMMON_TEXTHELPER_H

/**
 * Define function read/write to/from a text file
 */
namespace TextHelper
{
	/**
	 * Open file in the path, read content and store to a char pointer
	 * @param pPath		: path of text file
	 * @return			: char pointer that used to store content of text file
	 */
	char* ReadFile(char *pPath);

	/**
	 * Create a file follow path and write source on it
	 * @param pPath		: path of new file
	 * @param pSource 	: content that used to write on new file
	 * @return			: status
	 */
	int WriteFile(char *pPath, char *pSource);
}

#endif // APP_COMMON_TEXTHELPER_H

///////////////////////////////////////////////////////////////////////////////
