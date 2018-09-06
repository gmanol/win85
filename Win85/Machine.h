// Machine.h: interface for the CMachine class.
//
//////////////////////////////////////////////////////////////////////
#include "cpudef.h" // Added by emc
#include "Memory.h"	// Added by ClassView

#if !defined(AFX_MACHINE_H__1989A102_4349_11D3_8906_D2A118946F00__INCLUDED_)
#define AFX_MACHINE_H__1989A102_4349_11D3_8906_D2A118946F00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Cwin85View;
class CMachine  
{

public:
	CString ReadMemoryBlock(WORD start);

	void Reset();
	CString ReadMemoryBlockSolid(WORD start);

	int ExecuteNext();
	int Execute(BYTE opcode,BYTE byte2,BYTE byte3);

	CString ReadStackBlock(WORD start);
	CString ReadMemoryBlock16i(WORD start);
	CString ReadMemoryBlock16(WORD start);
	int Assembly(CString text,WORD address);
	CString Disassembly(BYTE opcode,BYTE b2,BYTE b3);
	void Fetch();

	CMemory Memory;

	BYTE A;BYTE FLAGS;
	WORD BC;
	WORD DE;
	WORD HL;
	WORD SP;
	WORD PC;

	BYTE* pB;BYTE* pC;
	BYTE* pD;BYTE* pE;
	BYTE* pH;BYTE* pL;
	BYTE* pPCH;BYTE* pPCL;
	BYTE* pSPH;BYTE* pSPL;
	
	DWORD clocks;
	BOOL Hold;


	BOOL Irq_Enable;
	BYTE Irq_Mask;			// M7.5 - M6.5 - M5.5
	
	CMachine();
	virtual ~CMachine();

	BYTE OpcodeLength[256];
	CString OpcodeTable[256];
	CString AsmTable[256];
	DWORD TState[256];

private:
	DWORD OpcodeTime;
	CString Byte2Dec(BYTE i);
	BYTE ParityTable[256];

	BYTE fOpcode;
	BYTE fByte2;
	BYTE fByte3;


	int ReadBit(BYTE bit);
	void SetBit(BYTE bit,int status);

	BYTE TEMPB;

	DWORD	TEMPD;
	WORD TEMPW;
	BYTE* pTEMPWH;
	BYTE* pTEMPWL;

	int i,j;

};

#endif // !defined(AFX_MACHINE_H__1989A102_4349_11D3_8906_D2A118946F00__INCLUDED_)
