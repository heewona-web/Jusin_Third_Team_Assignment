#pragma once

enum OBJID{OBJ_PLAYER, OBJ_WALL, OBJ_END};

struct DeleteObj
{
	template<typename T>
	void operator()(T& p)
	{
		if (p) {
			delete p;
			p = nullptr;
		}
	}
};