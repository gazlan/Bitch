// http://www.codeproject.com/Articles/5257/XCrashReport-Exception-Handling-and-Crash-Reportin
// MiniVersion.h  Version 1.1
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

#ifndef _MINIVERSION_HPP_
#define _MINIVERSION_HPP_

class CMiniVersion
{
   // constructors
   public:

      CMiniVersion(LPCTSTR lpszPath = NULL);
      
      BOOL  Init();
      void  Release();

   // attributes
   public:

      // fixed info
      BOOL  GetFileVersion   (WORD* pwVersion);
      BOOL  GetProductVersion(WORD* pwVersion);
      
      BOOL  GetFileFlags  (DWORD& rdwFlags);
      BOOL  GetFileOS     (DWORD& rdwOS);
      BOOL  GetFileType   (DWORD& rdwType);
      BOOL  GetFileSubtype(DWORD& rdwType);   
      
      // string info
      BOOL  GetCompanyName    (LPTSTR lpszCompanyName,    DWORD dwSize);
      BOOL  GetFileDescription(LPTSTR lpszFileDescription,DWORD dwSize);
      BOOL  GetProductName    (LPTSTR lpszProductName,    DWORD dwSize);

   // implementation
   protected:

      BOOL  GetFixedInfo(VS_FIXEDFILEINFO& rFixedInfo);
      BOOL  GetStringInfo(LPCTSTR lpszKey,LPTSTR lpszValue);
            
      BYTE*    m_pData;
      DWORD    m_dwHandle;
      WORD     m_wFileVersion   [4];
      WORD     m_wProductVersion[4];
      DWORD    m_dwFileFlags;
      DWORD    m_dwFileOS;
      DWORD    m_dwFileType;
      DWORD    m_dwFileSubtype;
               
      TCHAR    m_szPath           [MAX_PATH * 2 + 1];
      TCHAR    m_szCompanyName    [MAX_PATH * 2 + 1];
      TCHAR    m_szProductName    [MAX_PATH * 2 + 1];
      TCHAR    m_szFileDescription[MAX_PATH * 2 + 1];
};

#endif
