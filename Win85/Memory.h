// Memory.h: interface for the CMemory class.
//
//////////////////////////////////////////////////////////////////////
#include "cpudef.h" // Added by emc

#if !defined(AFX_MEMORY_H__1989A103_4349_11D3_8906_D2A118946F00__INCLUDED_)
#define AFX_MEMORY_H__1989A103_4349_11D3_8906_D2A118946F00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct MEMORY_BANK
{
	int NumOfMirrors;		//	������� �������
	int Mirrors[64];		//	������
	BOOL WriteAccess;		//	RAM � ROM
};

class CMemory  
{
public:
	BYTE Peek(WORD addr);					//	������� ���������
	void Poke(WORD addr,BYTE data);			//	������� ��������
	void ForcePoke(WORD addr,BYTE data);	//	������� ������������ ��������


	BOOL MemoryAccess(WORD addr);
	CString MemoryType (WORD addr);

	CMemory();
	virtual ~CMemory();

private:
	BYTE Memory[0x10000];					//	64kb ������
	MEMORY_BANK Banks[64];					//	��������� �������
	void FillRange(WORD start,WORD end,BYTE data);
	
};

#endif // !defined(AFX_MEMORY_H__1989A103_4349_11D3_8906_D2A118946F00__INCLUDED_)
