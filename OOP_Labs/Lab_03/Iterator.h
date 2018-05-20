#pragma once

template<class ITEM_TYPE>
class Iterator
{
public:
	virtual ITEM_TYPE First() = 0;
	virtual ITEM_TYPE Next() = 0;
	virtual bool isDone() = 0;
	virtual ITEM_TYPE CurrentItem() = 0;
};