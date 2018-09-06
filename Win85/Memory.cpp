// Memory.cpp: implementation of the CMemory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Win85.h"
#include "Memory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemory::CMemory()
{
//	Αρχικοποίηση συστήματος
//	8kb  ROM, 56kb RAM

	for (int i=0;i<64;i++)	//	Χωρίς είδωλα
	{
		Banks[i].NumOfMirrors=1;	
		Banks[i].Mirrors[0]=i << 10;
		Banks[i].WriteAccess=TRUE;
	}

//  0000h-2000h : ROM (8kb)
	Banks[0].WriteAccess=FALSE;	Banks[1].WriteAccess=FALSE;
	Banks[2].WriteAccess=FALSE;	Banks[3].WriteAccess=FALSE;
	Banks[4].WriteAccess=FALSE;	Banks[5].WriteAccess=FALSE;
	Banks[6].WriteAccess=FALSE;	Banks[7].WriteAccess=FALSE;

	FillRange(0,0xffff,0);	//	Γέμισε με μηδενικά
}

CMemory::~CMemory()
{

}

void CMemory::FillRange(WORD start, WORD end, BYTE data)
{
	for (int i=start;i<end+1;i++)
	{
		ForcePoke(i,data);
	}
}

BYTE CMemory::Peek(WORD addr)
{
	return Memory[addr];
}

void CMemory::Poke(WORD addr, BYTE data)
{
	WORD i,Bank,Bank_Offset;

	Bank=addr>>10;Bank_Offset=addr & 0x3ff;

	if (Banks[Bank].WriteAccess==TRUE)
	{
		for (i=0;i<Banks[Bank].NumOfMirrors;i++)
		{
		Memory[Banks[Bank].Mirrors[i] | Bank_Offset]=data;
		}
	}
}

void CMemory::ForcePoke(WORD addr, BYTE data)
{
	WORD i,Bank,Bank_Offset;

	Bank=addr>>10;Bank_Offset=addr & 0x3ff;
	
	for (i=0;i<Banks[Bank].NumOfMirrors;i++)
	{
	Memory[Banks[Bank].Mirrors[i] | Bank_Offset]=data;
	}
}

CString CMemory::MemoryType(WORD addr)
{
 	WORD Bank;
 	Bank=addr>>10;
 
 	if (Banks[Bank].WriteAccess==TRUE)
 	return "RAM:";
 	else
 	return "ROM:";
}



BOOL CMemory::MemoryAccess(WORD addr)
{
 	WORD Bank;
 	Bank=addr>>10;
 
 	if (Banks[Bank].WriteAccess==TRUE)
 	return TRUE;
 	else
 	return FALSE;
}
