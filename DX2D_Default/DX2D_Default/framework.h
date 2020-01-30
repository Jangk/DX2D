#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// DirectX
// 노트북은 되는데 집컵은 다렉깔때 에러뜸
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
//
#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "Define.h"
#include "Extern.h"
#include "Struct.h"
#include "Function.h"

