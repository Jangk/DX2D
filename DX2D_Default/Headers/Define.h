#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__

#define WINCX 1280
#define WINCY 800


#define PI 3.141592f
#define GRAVITY 9.8f

#define NO_EVENT				0
#define DEAD_EVENT				1
#define CHANGE_SCENE			2
#define SCENE_CHANGE_EVENT		3

// null checker
#define NULL_CHECK(ptr) if(nullptr == (ptr)) return;
#define NULL_CHECK_MSG(ptr, msg) if(nullptr == (ptr)) { ::MessageBox(0, msg, L"Error", MB_OK); return; }
#define NULL_CHECK_RETURN(ptr, val) if(nullptr == (ptr)) return val;
#define NULL_CHECK_MSG_RETURN(ptr, msg, val) if(nullptr == (ptr)) { ::MessageBox(0, msg, L"Error", MB_OK); return val; }

// �̱��� ��ũ��
#define NO_COPY(ClassName)						\
private:										\
	ClassName(const ClassName&);				\
	ClassName& operator=(const ClassName&);

// ���
#define DECLARE_SINGLETON(ClassName)			\
		NO_COPY(ClassName)						\
public:											\
	static ClassName* GetInstance();			\
	void DestroyInstance();						\
private:										\
	static ClassName* m_pInstance;

// cpp
#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;	\
ClassName* ClassName::GetInstance()				\
{												\
	if(nullptr == m_pInstance)					\
		m_pInstance = new ClassName;			\
	return m_pInstance;							\
}												\
void ClassName::DestroyInstance()				\
{												\
	if(m_pInstance)								\
	{											\
		delete m_pInstance;						\
		m_pInstance = nullptr;					\
	}											\
}
#endif