#if !defined(AFX_DEVICEDLG_H__A49D2C4D_CF7A_11D3_9FBB_84A70E15680A__INCLUDED_)
#define AFX_DEVICEDLG_H__A49D2C4D_CF7A_11D3_9FBB_84A70E15680A__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KeyboardDlg.h : header file
//
#include "AboutDlg.h"
#include "DeviceEmul.h"	// Added by ClassView
#include "ConfigDlg.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CKeyboardDlg dialog

class CKeyboardDlg : public CDialog
{
// Construction
public:
	void ExternalConfig();
	CKeyboardDlg(CWnd* pParent = NULL);   // standard constructor
	CDeviceEmul Device;

#define	IRQ_TRAP *(Device.m_pIRQPenting+0)
#define	IRQ_RST75 *(Device.m_pIRQPenting+1)
#define	IRQ_RST65 *(Device.m_pIRQPenting+2)
#define	IRQ_RST55 *(Device.m_pIRQPenting+3)
#define	IRQ_INTR *(Device.m_pIRQPenting+4)


// Dialog Data
	//{{AFX_DATA(CKeyboardDlg)
	enum { IDD = IDD_KEYBOARD_DLG };
	CButton	m_button9;
	CButton	m_button8;
	CButton	m_button7;
	CButton	m_button6;
	CButton	m_button5;
	CButton	m_button4;
	CButton	m_button31;
	CButton	m_button30;
	CButton	m_button3;
	CButton	m_button29;
	CButton	m_button28;
	CButton	m_button27;
	CButton	m_button26;
	CButton	m_button25;
	CButton	m_button24;
	CButton	m_button23;
	CButton	m_button22;
	CButton	m_button21;
	CButton	m_button20;
	CButton	m_button2;
	CButton	m_button19;
	CButton	m_button18;
	CButton	m_button17;
	CButton	m_button16;
	CButton	m_button15;
	CButton	m_button14;
	CButton	m_button13;
	CButton	m_button12;
	CButton	m_button11;
	CButton	m_button10;
	CButton	m_button1;
	CButton	m_button0;
	CButton	m_right_shift;
	CButton	m_left_shift;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyboardDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKeyboardDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuAbout();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	afx_msg void OnButton11();
	afx_msg void OnButton12();
	afx_msg void OnButton13();
	afx_msg void OnButton14();
	afx_msg void OnButton15();
	afx_msg void OnButton16();
	afx_msg void OnButton17();
	afx_msg void OnButton18();
	afx_msg void OnButton19();
	afx_msg void OnButton20();
	afx_msg void OnButton21();
	afx_msg void OnButton22();
	afx_msg void OnButton23();
	afx_msg void OnButton24();
	afx_msg void OnButton25();
	afx_msg void OnButton26();
	afx_msg void OnButton27();
	afx_msg void OnButton28();
	afx_msg void OnButton31();
	afx_msg void OnButton29();
	afx_msg void OnButton30();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMenu* pMenu;
	CString m_AppFileName;
	CString m_ExecutablePath;
	void SaveConfiguration();
	void LoadConfiguration();

	HACCEL m_hAccel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICEDLG_H__A49D2C4D_CF7A_11D3_9FBB_84A70E15680A__INCLUDED_)
