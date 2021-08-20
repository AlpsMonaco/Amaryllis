#pragma once

#ifdef _WIN32
#define _WIN_ENVIROMENT 1
#include "cs_win.h"
namespace Amaryllis
{
	using server = server_win;
}
#else
namespace Amaryllis
{
	using server = server_linux;
}
#endif
