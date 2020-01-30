#pragma once

#define WINCX 800
#define WINCY 600

#define NULL_CHECK(ptr) if(nullptr == (ptr)) return;
#define NULL_CHECK_MSG(ptr, msg) if(nullptr == (ptr)) { MessageBox(0, msg, L"Error", MB_OK); return; }
#define NULL_CHECK_RETURN(ptr, val) if(nullptr == (ptr)) return val;
#define NULL_CHECK_MSG_RETURN(ptr, msg, val) if(nullptr == (ptr)) { MessageBox(0, msg, L"Error", MB_OK); return val; }