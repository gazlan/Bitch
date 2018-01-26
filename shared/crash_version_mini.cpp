// http://www.codeproject.com/Articles/5257/XCrashReport-Exception-Handling-and-Crash-Reportin
// MiniVersion.cpp  Version 1.1
//
// Author:  Hans Dietrich
//          hdietrich2@hotmail.com
//
// This software is released into the public domain.
// You are free to use it in any way you like, except
// that you may not sell this source code.
//
// This software is provided "as is" with no expressed
// or implied warranty. I accept no liability for any
// damage or loss of business that this software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "crash_version_mini.h"

#pragma message("automatic link to VERSION.LIB")
#pragma comment(lib,"version.lib")

///////////////////////////////////////////////////////////////////////////////
CMiniVersion::CMiniVersion(LPCTSTR lpszPath)
{
   ZeroMemory(m_szPath,sizeof(m_szPath));

   if (lpszPath && *lpszPath)
   {
      lstrcpyn(m_szPath,lpszPath,sizeof(m_szPath) - 1);
   }

   m_pData    = NULL;
   m_dwHandle = 0;

   for (int ii = 0; ii < 4; ++ii)
   {
      m_wFileVersion[ii]    = 0;
      m_wProductVersion[ii] = 0;
   }

   m_dwFileFlags   = 0;
   m_dwFileOS      = 0;
   m_dwFileType    = 0;
   m_dwFileSubtype = 0;

   ZeroMemory(m_szCompanyName,sizeof(m_szCompanyName));
   ZeroMemory(m_szProductName,sizeof(m_szProductName));
   ZeroMemory(m_szFileDescription,sizeof(m_szFileDescription));

   Init();
}

///////////////////////////////////////////////////////////////////////////////

BOOL CMiniVersion::Init()
{
   if (m_pData)
   {
      // Error !
      // Already Initialized
      return FALSE;
   }

   DWORD    dwHandle = 0;

   DWORD    dwSize = ::GetFileVersionInfoSize((LPSTR)(LPCTSTR)m_szPath,&dwHandle);

   if (!dwSize)
   {
      // Error !
      return FALSE;
   }

   m_pData = new BYTE[dwSize + 1]; 

   ZeroMemory(m_pData,dwSize + 1);

   BOOL     rc = ::GetFileVersionInfo((LPSTR)(LPCTSTR) m_szPath,dwHandle,dwSize,m_pData);

   if (!rc)
   {
      // Error !
      if (m_pData)
      {
         delete[] m_pData;
         m_pData = NULL;
      }

      return FALSE;
   }

   // get fixed info
   VS_FIXEDFILEINFO     FixedInfo;

   if (!GetFixedInfo(FixedInfo))
   {
      // Error !
      if (m_pData)
      {
         delete[] m_pData;
         m_pData = NULL;
      }

      return FALSE;
   }

   m_wFileVersion[0] = HIWORD(FixedInfo.dwFileVersionMS);
   m_wFileVersion[1] = LOWORD(FixedInfo.dwFileVersionMS);
   m_wFileVersion[2] = HIWORD(FixedInfo.dwFileVersionLS);
   m_wFileVersion[3] = LOWORD(FixedInfo.dwFileVersionLS);

   m_wProductVersion[0] = HIWORD(FixedInfo.dwProductVersionMS);
   m_wProductVersion[1] = LOWORD(FixedInfo.dwProductVersionMS);
   m_wProductVersion[2] = HIWORD(FixedInfo.dwProductVersionLS);
   m_wProductVersion[3] = LOWORD(FixedInfo.dwProductVersionLS);

   m_dwFileFlags   = FixedInfo.dwFileFlags;
   m_dwFileOS      = FixedInfo.dwFileOS;
   m_dwFileType    = FixedInfo.dwFileType;
   m_dwFileSubtype = FixedInfo.dwFileSubtype;

   // get string info
   GetStringInfo(_T("CompanyName"),    m_szCompanyName);
   GetStringInfo(_T("FileDescription"),m_szFileDescription);
   GetStringInfo(_T("ProductName"),    m_szProductName);

   return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

void CMiniVersion::Release()
{
   // Do this manually, because we can't use objects requiring
   // a destructor within an exception handler
   if (m_pData)
   {
      delete[] m_pData;
      m_pData = NULL;
   }
}

///////////////////////////////////////////////////////////////////////////////

BOOL CMiniVersion::GetFileVersion(WORD* pwVersion)
{
   for (int ii = 0; ii < 4; ++ii)
   {
      *pwVersion++ = m_wFileVersion[ii];
   }

   return TRUE;
}                  

///////////////////////////////////////////////////////////////////////////////

BOOL CMiniVersion::GetProductVersion(WORD* pwVersion)
{
   for (int ii = 0; ii < 4; ++ii)
   {
      *pwVersion++ = m_wProductVersion[ii];
   }

   return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

BOOL CMiniVersion::GetFileFlags(DWORD& rdwFlags)
{
   rdwFlags = m_dwFileFlags;

   return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

BOOL CMiniVersion::GetFileOS(DWORD& rdwOS)
{
   rdwOS = m_dwFileOS;
   
   return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

BOOL CMiniVersion::GetFileType(DWORD& rdwType)
{
   rdwType = m_dwFileType;

   return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

BOOL CMiniVersion::GetFileSubtype(DWORD& rdwType)
{
   rdwType = m_dwFileSubtype;

   return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

BOOL CMiniVersion::GetCompanyName(LPTSTR lpszCompanyName,DWORD dwSize)
{
   if (!lpszCompanyName || !dwSize)
   {
      return FALSE;
   }

   ZeroMemory(lpszCompanyName,dwSize);

   lstrcpyn(lpszCompanyName,m_szCompanyName,dwSize - 1);

   return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

BOOL CMiniVersion::GetFileDescription(LPTSTR lpszFileDescription,DWORD dwSize)
{
   if (!lpszFileDescription || !dwSize)
   {
      return FALSE;
   }

   ZeroMemory(lpszFileDescription,dwSize);

   lstrcpyn(lpszFileDescription,m_szFileDescription,dwSize - 1);

   return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

BOOL CMiniVersion::GetProductName(LPTSTR lpszProductName,DWORD dwSize)
{
   if (!lpszProductName || !dwSize)
   {
      return FALSE;
   }

   ZeroMemory(lpszProductName,dwSize);

   lstrcpyn(lpszProductName,m_szProductName,dwSize - 1);

   return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

BOOL CMiniVersion::GetFixedInfo(VS_FIXEDFILEINFO& rFixedInfo)
{
   BOOL     rc;

   UINT     nLength = 0;

   VS_FIXEDFILEINFO*    pFixedInfo  = NULL;

   if (!m_pData)
   {
      return FALSE;
   }

   if (m_pData)
   {
      rc = ::VerQueryValue(m_pData,_T("\\"),(void * *) &pFixedInfo,&nLength);
   }
   else
   {
      rc = FALSE;
   }

   if (rc)
   {
      memcpy(&rFixedInfo,pFixedInfo,sizeof(VS_FIXEDFILEINFO));
   }

   return rc;
}

///////////////////////////////////////////////////////////////////////////////

BOOL CMiniVersion::GetStringInfo(LPCSTR lpszKey,LPTSTR lpszReturnValue)
{
   BOOL     rc;

   DWORD*   pdwTranslation;

   UINT     nLength;

   LPTSTR   lpszValue;

   if (!m_pData)
   {
      return FALSE;
   }

   if (!lpszReturnValue)
   {
      return FALSE;
   }

   if (!lpszKey)
   {
      return FALSE;
   }

   *lpszReturnValue = 0;

   rc = ::VerQueryValue(m_pData,_T("\\VarFileInfo\\Translation"),(void * *) &pdwTranslation,&nLength);

   if (!rc)
   {
      return FALSE;
   }

   char     szKey[2048];

   wsprintf(szKey,_T("\\StringFileInfo\\%04x%04x\\%s"),LOWORD(*pdwTranslation),HIWORD(*pdwTranslation),lpszKey);

   rc = ::VerQueryValue(m_pData,szKey,(void**)&lpszValue,&nLength);

   if (!rc)
   {
      return FALSE;
   }   

   lstrcpy(lpszReturnValue,lpszValue);

   return TRUE;
}
