#include "stdafx.h"
#include "UserMessage.h"

void ShowMessage(String^ msg)
{
	MessageBox::Show(msg);
}