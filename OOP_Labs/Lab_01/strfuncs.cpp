#include "stdafx.h"
#include "strfuncs.h"
#include <stdlib.h>

using namespace System;

namespace WinFormsTemplate
{
	char *str2char(String^ str)
	{
		char *res = (char*)malloc(sizeof(char)* (str->Length + 1));
		if (res == NULL)
		{
			return NULL;
		}
		int i = 0;
		for (; i < str->Length; i++)
		{
			res[i] = str[i];
		}
		res[i] = '\0';
		return res;
	}
}