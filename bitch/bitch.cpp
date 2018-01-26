/* ******************************************************************** **
** @@ Bitch - SGDT decryptor
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Dscr   :
** ******************************************************************** */

/* ******************************************************************** **
**                uses pre-compiled headers
** ******************************************************************** */

#include "stdafx.h"

#include "..\shared\mmf.h"
#include "..\shared\file.h"
#include "..\shared\search_bmh.h"
#include "..\shared\file_walker.h"

/* ******************************************************************** **
** @@                   internal defines
** ******************************************************************** */

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef NDEBUG
#pragma optimize("gsy",on)
#pragma comment(linker,"/FILEALIGN:512 /MERGE:.rdata=.text /MERGE:.data=.text /SECTION:.text,EWR /IGNORE:4078")
#endif

#define BLOCK_SIZE            (176)
#define MAX_BLOCK_CNT         (5)
#define CODEBOOK_SIZE         (BLOCK_SIZE * MAX_BLOCK_CNT)
#define MAX_LOOP_CNT          (5)

const DWORD  pCodeBook[CODEBOOK_SIZE / sizeof(DWORD)] =
{
   0x00000000, 0x00000000, 0x00000000, 0x00000000, 
   0x00000000, 0x00000000, 0x00000000, 0x00000000, 
   0x00000000, 0x00000000, 0x00000000, 0x00000000, 
   0x00000000, 0x00000000, 0x00000000, 0x00000000, 
   0x00000000, 0x00000000, 0x00000000, 0x00000000, 
   0x00000000, 0x00000000, 0x00000000, 0x00000000, 
   0x00000000, 0x00000000, 0x00000000, 0x00000000, 
   0x00000000, 0x00000000, 0x00000000, 0x00000000, 
   0x00000000, 0x00000000, 0x00000000, 0x00000000, 
   0x00000000, 0x00000000, 0x00000000, 0x00000000, 
   0x00000000, 0x00000000, 0x00000000, 0x00000000, 
   0x1801BB90, 0x379BC904, 0x432BB753, 0xA669A752, 
   0x7C7BA634, 0x9315F5E9, 0xEFE7F05A, 0x7FFB22F4, 
   0x0CC1A20B, 0x9742288F, 0x156F8C10, 0x12D59460, 
   0x09C7BDAE, 0x22BE4835, 0x480F93C0, 0xC32EA25B, 
   0x4EB7DE18, 0x16C39262, 0x9B15E513, 0xA7990A5D, 
   0x3E52D21E, 0xF89AFB97, 0xEC615F2B, 0x3022B361, 
   0x2585F8F2, 0x6C5B256D, 0x66C3C5B8, 0xE8507BDB, 
   0x60B4C881, 0xFD2845F1, 0x7DA24579, 0x0BFA4AE8, 
   0x558A2D90, 0x3BF7272D, 0x7CCD2437, 0x1B691725, 
   0xACEC44AA, 0x36B8DEFE, 0xD1F89A90, 0x222074FD, 
   0x73708B47, 0xD69E16FC, 0x735A79FC, 0xE59ECAC4, 
   0xEC615F2B, 0x3022B361, 0x2585F8F2, 0x6C5B256D, 
   0x66C3C5B8, 0xE8507BDB, 0x60B4C881, 0xFD2845F1, 
   0x7DA24579, 0x0BFA4AE8, 0x558A2D90, 0x9CD96C7B, 
   0x04F5A5FB, 0xC6E5F591, 0x353EF6E7, 0x4D4956AE, 
   0x880EAC32, 0xE18F97B0, 0x3A09CAC5, 0x3EA76E70, 
   0xFD31A474, 0x5AD77572, 0xB57611FA, 0x5A29C1D3, 
   0x086EF511, 0x2E767E9E, 0x4343E839, 0x7A9BEC50, 
   0xD44803DF, 0x34DE82EB, 0x2D5AC0A8, 0x8DE8762E, 
   0x8A6E086D, 0x12D59460, 0x09C7BDAE, 0x22BE4835, 
   0x480F93C0, 0xC32EA25B, 0x4EB7DE18, 0x16C39262, 
   0x9B15E513, 0xA7990A5D, 0x3E52D21E, 0xF89AFB97, 
   0xEC5B16E3, 0x15AAE5E9, 0xBBC4A774, 0x7A9BEC50, 
   0x16C39262, 0xE8507BDB, 0x09AB9821, 0xFD09BF73, 
   0x7DA0F331, 0x08AE7B48, 0xF9FB9618, 0x9CD96C7B, 
   0x3CD15DA5, 0xC6E5F591, 0x4EB7DE18, 0x4D4956AE, 
   0x880EAC32, 0xE18F97B0, 0xE0E46CA6, 0x3EA76E70, 
   0xFD31A474, 0x5AD77572, 0x139EA0D5, 0x3022B361, 
   0x2585F8F2, 0x6C5B256D, 0x5866F5A3, 0xE8507BDB, 
   0x60B4C881, 0xFD2845F1, 0x7DA24579, 0x0BFA4AE8, 
   0x558A2D90, 0xB57611FA, 0x7A9BEC50, 0x086EF511, 
   0x2E767E9E, 0x4343E839, 0x7A9BEC50, 0xD44803DF, 
   0x2A082B20, 0x64EA1AED, 0x8DE8762E, 0xF7910AEF, 
   0x179788F7, 0x6E3585EA, 0xE6777412, 0xEDFE1E2A, 
   0x406C7B13, 0xACBE5AA0, 0x70F17224, 0x438CDB45, 
   0xAA1F024D, 0x5942E380, 0x23E95B3A, 0x707C4FED, 
   0x593A59B3, 0x6524F37C, 0x2A9CE4F5, 0x8EC43AA3, 
   0xCF3DD419, 0x7628708F, 0xDD75992D, 0x9E082B73, 
   0xC13474CC, 0xCEB19880, 0x80DE032E, 0xCFFCBC19, 
   0x948E611F, 0xACFBE939, 0x3CCD324D, 0xC131EB48, 
   0x9A2046C8, 0x3B42B6AF, 0x6409B2CD, 0xD65C9DFA, 
   0x1C5F940D, 0xF8E4535E, 0xFC15D81D, 0x790D41D9, 
   0x1ECDA9CA, 0xAA71F160, 0x7FDE7F63, 0x7BD99BBC, 
   0xEC9BD84D, 0xD1B41411, 0xF3122163, 0x6101AD34 
};

/* ******************************************************************** **
** @@                   internal prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@                   external global variables
** ******************************************************************** */

extern DWORD   dwKeepError = 0;

/* ******************************************************************** **
** @@                   static global variables
** ******************************************************************** */

static MMF     _MF;

BYTE*    _pBuf     = NULL;
DWORD    _dwSize   = 0;
FILE*    _pOut     = NULL;
DWORD    _dwMarker = 0;

/* ******************************************************************** **
** @@                   real code
** ******************************************************************** */

/* ******************************************************************** **
** @@ SaveIcon()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static DWORD SaveIcon(const BYTE* const pBuf,DWORD dwSize,const char* const pszName)
{
   if (!pBuf || !dwSize)
   {
      // Error !
      return 0;
   }

   if (IsBadReadPtr(pBuf,dwSize))
   {
      printf("SaveIcon(): Bad ReadPtr [%p] / [%08X]\n",pBuf,dwSize);
      #ifdef _DEBUG
      fprintf(_pOut,"SaveIcon(): Bad ReadPtr [%p] / [%08X]\n",pBuf,dwSize);
      #endif
      return 0;
   }
   
   _dwMarker = *(DWORD*)pBuf;

   DWORD    dwJSize = *((DWORD*)pBuf + 1);

   if (_pOut)
   {
      #ifdef _DEBUG
      fprintf(_pOut,"Marker: %08X  Size: %08X  %s\n",_dwMarker,dwJSize,pszName);
      #endif
   }

   char     pszJpegName[_MAX_PATH];
   char     pszDrive   [_MAX_DRIVE];
   char     pszDir     [_MAX_DIR];
   char     pszFName   [_MAX_FNAME];
   char     pszExt     [_MAX_EXT];

   _splitpath(pszName,    pszDrive,pszDir,pszFName,pszExt);
   _makepath( pszJpegName,pszDrive,pszDir,pszFName,"00.jpg");

   HANDLE   hFile = CreateFile(pszJpegName);

   if (hFile != INVALID_HANDLE_VALUE)
   {
      WriteBuffer(hFile,pBuf + sizeof(DWORD) * 2,dwJSize);

      CloseHandle(hFile);
      hFile = INVALID_HANDLE_VALUE;
   }

   return dwJSize + sizeof(DWORD) * 2;
}

/* ******************************************************************** **
** @@ SavePix()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static DWORD SavePix(const BYTE* const pBuf,DWORD dwSize,int iNum,const char* const pszName)
{
   if (!pBuf || !dwSize)
   {
      // Error !
      return 0;
   }

   DWORD    dwJSize = *(DWORD*)pBuf;

   if (IsBadReadPtr(pBuf,dwJSize))
   {
      printf("SavePix(): Bad ReadPtr %02d: [%p] / [%08X]\n",iNum,pBuf,dwJSize);
      #ifdef _DEBUG
      fprintf(_pOut,"SavePix(): Bad ReadPtr %02d: [%p] / [%08X]\n",iNum,pBuf,dwJSize);
      #endif
      return 0;
   }

   if (_pOut)
   {
      #ifdef _DEBUG
      fprintf(_pOut,"%02d: Size: %08X\n",iNum,dwJSize);
      #endif
   }

   char     pszJpegName[_MAX_PATH];
   char     pszDrive   [_MAX_DRIVE];
   char     pszDir     [_MAX_DIR];
   char     pszFName   [_MAX_FNAME];
   char     pszExt     [_MAX_EXT];

   char     pszPixExt[MAX_PATH + 1];

   sprintf(pszPixExt,"%02d.jpg",iNum);

   _splitpath(pszName,    pszDrive,pszDir,pszFName,pszExt);
   _makepath( pszJpegName,pszDrive,pszDir,pszFName,pszPixExt);

   HANDLE   hFile = CreateFile(pszJpegName);

   if (hFile != INVALID_HANDLE_VALUE)
   {
      WriteBuffer(hFile,pBuf + sizeof(DWORD),dwJSize);

      CloseHandle(hFile);
      hFile = INVALID_HANDLE_VALUE;
   }

   return dwJSize + sizeof(DWORD);
}

/* ******************************************************************** **
** @@ SaveRaw()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static DWORD SaveRaw(const BYTE* const pBuf,DWORD dwSize,const char* const pszName)
{
   if (!pBuf || !dwSize)
   {
      // Error !
      return 0;
   }

   if (IsBadReadPtr(pBuf,dwSize))
   {
      printf("SaveRaw(): Bad ReadPtr: [%p] / [%08X]\n",pBuf,dwSize);
      #ifdef _DEBUG
      fprintf(_pOut,"SaveRaw(): Bad ReadPtr [%p] / [%08X]\n",pBuf,dwSize);
      #endif
      return 0;
   }

   if (_pOut)
   {
      #ifdef _DEBUG
      fprintf(_pOut,"SaveRaw(): Size: %08X\n",dwSize);
      #endif
   }

   char     pszRawName[_MAX_PATH];
   char     pszDrive  [_MAX_DRIVE];
   char     pszDir    [_MAX_DIR];
   char     pszFName  [_MAX_FNAME];
   char     pszExt    [_MAX_EXT];

   char     pszRawExt[MAX_PATH + 1];

   strcpy(pszRawExt,".raw");

   _splitpath(pszName,   pszDrive,pszDir,pszFName,pszExt);
   _makepath( pszRawName,pszDrive,pszDir,pszFName,pszRawExt);

   HANDLE   hFile = CreateFile(pszRawName);

   if (hFile != INVALID_HANDLE_VALUE)
   {
      WriteBuffer(hFile,pBuf + sizeof(DWORD),dwSize);

      CloseHandle(hFile);
      hFile = INVALID_HANDLE_VALUE;
   }

   return dwSize;
}

/* ******************************************************************** **
** @@ Decrypt()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

// 00418420 Decrypt_418420  proc near 
// 00418420
// 00418420 var_7           = byte ptr -7
// 00418420 var_6           = word ptr -6
// 00418420 var_4           = dword ptr -4
// 00418420 pCodeBook_0     = dword ptr  8
// 00418420 pBuf_4          = dword ptr  0Ch
// 00418420 Size_8          = dword ptr  10h
// 00418420
// 00418420                 push    ebp
// 00418421                 mov     ebp, esp
// 00418423                 add     esp, -8
// 00418426                 push    ebx
// 00418427                 push    esi
// 00418428                 xor     eax, eax
// 0041842A                 mov     [ebp+var_4], eax
// 0041842D
// 0041842D OuterLoop_41842D:                       ; CODE XREF: Decrypt_418420+81j
// 0041842D                 mov     [ebp+var_6], 0
// 00418433                 mov     ecx, [ebp+Size_8]
// 00418436                 dec     ecx
// 00418437                 mov     esi, ecx
// 00418439                 mov     eax, ecx
// 0041843B                 mov     ecx, 0B0h       ; BLOCK_SIZE
// 00418440                 cdq                     ; Convert double-word to quad-word
// 00418440                                         ; Sign-extends EAX into EDX, forming the quad-word EDX:EAX.
// 00418440                                         ; Since (I)DIV uses EDX:EAX as its input, CDQ must be called after setting EAX
// 00418440                                         ; if EDX is not manually initialized (as in 64/32 division) before (I)DIV.
// 00418441                 idiv    ecx             ; Signed divide
// 00418441                                         ; DX:AX = DX:AX / r/m; resulting DX = remainder
// 00418443                 mov     ebx, edx
// 00418445                 mov     eax, [ebp+pBuf_4]
// 00418448                 lea     ecx, [eax+esi-1]
// 0041844C                 test    esi, esi
// 0041844E                 jle     short Finish_41849A
// 00418450
// 00418450 InnerLoop_418450:                       ; CODE XREF: Decrypt_418420+78j
// 00418450                 dec     ebx
// 00418451                 jns     short Skip_418458
// 00418453                 mov     ebx, 0AFh       ; 175
// 00418458
// 00418458 Skip_418458:                            ; CODE XREF: Decrypt_418420+31j
// 00418458                 mov     eax, [ebp+pCodeBook_0]
// 0041845B                 mov     dl, [eax+ebx]
// 0041845E                 mov     byte ptr [ebp+var_6], dl
// 00418461                 mov     al, [ecx]
// 00418463                 mov     byte ptr [ebp+var_6+1], al
// 00418466                 movzx   eax, [ebp+var_6]
// 0041846A                 add     eax, esi
// 0041846C                 dec     esi
// 0041846D                 cdq                     ; Convert double-word to quad-word
// 0041846D                                         ; Sign-extends EAX into EDX, forming the quad-word EDX:EAX.
// 0041846D                                         ; Since (I)DIV uses EDX:EAX as its input, CDQ must be called after setting EAX
// 0041846D                                         ; if EDX is not manually initialized (as in 64/32 division) before (I)DIV.
// 0041846E                 idiv    [ebp+Size_8]    ; Signed divide
// 0041846E                                         ; DX:AX = DX:AX / r/m; resulting DX = remainder
// 00418471                 mov     eax, edx
// 00418473                 mov     dl, [ecx+1]
// 00418476                 mov     [ebp+var_7], dl
// 00418479                 mov     edx, [ebp+pBuf_4]
// 0041847C                 mov     dl, [edx+eax]
// 0041847F                 mov     [ecx+1], dl
// 00418482                 mov     edx, [ebp+pBuf_4]
// 00418485                 add     edx, eax
// 00418487                 mov     al, [ebp+var_7]
// 0041848A                 mov     [edx], al
// 0041848C                 mov     eax, [ebp+pCodeBook_0]
// 0041848F                 mov     dl, [eax+ebx]
// 00418492                 sub     [ecx+1], dl
// 00418495                 dec     ecx
// 00418496                 test    esi, esi
// 00418498                 jg      short InnerLoop_418450
// 0041849A
// 0041849A Finish_41849A:                          ; CODE XREF: Decrypt_418420+2Ej
// 0041849A                 inc     [ebp+var_4]
// 0041849D                 cmp     [ebp+var_4], 5
// 004184A1                 jl      short OuterLoop_41842D
// 004184A3
// 004184A3 Ret_4184A3:
// 004184A3                 pop     esi
// 004184A4                 pop     ebx
// 004184A5                 pop     ecx
// 004184A6                 pop     ecx
// 004184A7                 pop     ebp
// 004184A8                 retn
// 004184A8 Decrypt_418420  endp

static bool Decrypt(const BYTE* const pCodeBook,const BYTE* const pBuf,DWORD dwSize,const char* const pszName)
{
   if (IsBadReadPtr(pBuf,dwSize))
   {
      printf("Decrypt(): Bad ReadPtr [%p] / [%08X]\n",pBuf,dwSize);
      #ifdef _DEBUG
      fprintf(_pOut,"Decrypt(): Bad ReadPtr [%p] / [%08X]\n",pBuf,dwSize);
      #endif
      return 0;
   }

   BYTE*       pTemp = new BYTE[dwSize];

   if (!pTemp)
   {
      // Error !
      _MF.Close();
      printf("Err: Not enough memory for temp buf.\n");
      return false;
   }

   memcpy(pTemp,pBuf,dwSize);

   for (int iCnt = 0; iCnt < MAX_LOOP_CNT; ++iCnt)
   {
      WORD     wVar_6  = 0;
      BYTE     byVar_7 = 0;

      __asm
      {
         mov     ecx, dwSize
         dec     ecx
         mov     esi, ecx
         mov     eax, ecx
         mov     ecx, 0B0h       // BLOCK_SIZE
         cdq                     // Convert double-word to quad-word
                                 // Sign-extends EAX into EDX, forming the quad-word EDX:EAX.
                                 // Since (I)DIV uses EDX:EAX as its input, CDQ must be called after setting EAX
                                 // if EDX is not manually initialized (as in 64/32 division) before (I)DIV.
         idiv    ecx             // Signed divide
                                 // DX:AX = DX:AX / r/m; resulting DX = remainder
         mov     ebx, edx
         mov     eax, pTemp
         lea     ecx, [eax+esi-1]
         test    esi, esi
         jle     short Finish
      }

InnerLoop:

      __asm
      {
         dec     ebx
         jns     short Skip
         mov     ebx, 0AFh       // BLOCK_SIZE - 1
      }

Skip:

      __asm
      {
         mov     eax, pCodeBook
         mov     dl, [eax+ebx]
         mov     byte ptr [wVar_6], dl
         mov     al, [ecx]
         mov     byte ptr [wVar_6+1], al
         movzx   eax, [wVar_6]
         add     eax, esi
         dec     esi
         cdq                     // Convert double-word to quad-word
                                 // Sign-extends EAX into EDX, forming the quad-word EDX:EAX.
                                 // Since (I)DIV uses EDX:EAX as its input, CDQ must be called after setting EAX
                                 // if EDX is not manually initialized (as in 64/32 division) before (I)DIV.
         idiv    [dwSize]        // Signed divide
                                 // DX:AX = DX:AX / r/m; resulting DX = remainder
         mov     eax, edx
         mov     dl, [ecx+1]
         mov     [byVar_7], dl
         mov     edx, [pTemp]
         mov     dl, [edx+eax]
         mov     [ecx+1], dl
         mov     edx, [pTemp]
         add     edx, eax
         mov     al, [byVar_7]
         mov     [edx], al
         mov     eax, [pCodeBook]
         mov     dl, [eax+ebx]
         sub     [ecx+1], dl
         dec     ecx
         test    esi, esi
         jg      short InnerLoop
      }

Finish:

      ;  // Dummy
   }

   int   iResult = BMH_Search(pTemp,dwSize,(BYTE*)&_dwMarker,sizeof(DWORD));

   if (iResult == -1)
   {
      // Error !
      DWORD    dwResult = SaveRaw(pTemp,dwSize,pszName);

      delete[] pTemp;
      pTemp = NULL;

      return false;
   }

   DWORD    iPixCnt = *(DWORD*)(pTemp + iResult + sizeof(DWORD));

   ASSERT(iPixCnt < 32);

   DWORD    dwResult = sizeof(DWORD);

   BYTE*    pPixBuf     = (BYTE*)pTemp + iResult + sizeof(DWORD);
   DWORD    dwPixSize   = dwSize;

   for (DWORD ii = 0; ii < iPixCnt; ++ii)
   {
      pPixBuf   += dwResult;
      dwPixSize -= dwResult;

      dwResult = SavePix(pPixBuf,dwPixSize,ii + 2,pszName);
   }

   delete[] pTemp;
   pTemp = NULL;

   return true;
}

/* ******************************************************************** **
** @@ ForEach()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

static void ForEach(const char* const pszFileName)
{
   #ifdef _DEBUG
   printf("[%s]\n",pszFileName);
   #endif

   if (!_MF.OpenReadOnly(pszFileName))
   {
      // Error !
      printf("Err: Can't open for RO. [%s]\n",pszFileName);
      return;
   }

   _pBuf   = _MF.Buffer();
   _dwSize = _MF.Size();

   if (IsBadReadPtr(_pBuf,_dwSize))
   {
      printf("ForEach(): Bad ReadPtr [%p] / [%08X]\n",_pBuf,_dwSize);
      #ifdef _DEBUG
      fprintf(_pOut,"ForEach(): Bad ReadPtr [%p] / [%08X]\n",_pBuf,_dwSize);
      #endif
      return;
   }

   if (!_pBuf || !_dwSize)
   {
      // Error !
      _MF.Close();
      printf("Err: Can't open for RO. [%s]\n",pszFileName);
      return;
   }

   BYTE*    pBuf   = _pBuf;
   DWORD    dwSize = _dwSize;

   DWORD    dwResult = SaveIcon(pBuf,dwSize,pszFileName);

   pBuf   += dwResult;
   dwSize -= dwResult;

   dwResult = SavePix(pBuf,dwSize,1,pszFileName);

   pBuf   += dwResult;
   dwSize -= dwResult;

   BYTE     byFactor = *pBuf;

   int jj = 0;

   printf("%08X: ",dwResult);
   
   #ifdef _DEBUG
   fprintf(_pOut,"%02X",*pBuf[jj]);
   #endif

   for (jj = 0; jj < 1; ++jj)
   {
      printf("%02X",pBuf[jj]);
      
      #ifdef _DEBUG
      fprintf(_pOut,"%02X",*pBuf[jj]);
      #endif
   }

   printf("  ");

   for (jj = 1; jj < 2; ++jj)
   {
      printf("%02X",pBuf[jj]);
      
      #ifdef _DEBUG
      fprintf(_pOut,"%02X",*pBuf[jj]);
      #endif
   }

   printf("  ");

   for (jj = 2; jj < 5; ++jj)
   {
      printf("%02X",pBuf[jj]);
      
      #ifdef _DEBUG
      fprintf(_pOut,"%02X",*pBuf[jj]);
      #endif
   }

   printf("  ");

   for (jj = 5; jj < 9; ++jj)
   {
      printf("%02X",pBuf[jj]);
      
      #ifdef _DEBUG
      fprintf(_pOut,"%02X",*pBuf[jj]);
      #endif
   }

   printf("\n");
   
   #ifdef _DEBUG
   fprintf(_pOut,"\n");
   #endif

   pBuf   += 9;
   dwSize -= 9;

   if (IsBadReadPtr(pBuf,dwSize))
   {
      printf("ForEach(): Bad ReadPtr [%p] / [%08X]\n",pBuf,dwSize);
      #ifdef _DEBUG
      fprintf(_pOut,"ForEach(): Bad ReadPtr [%p] / [%08X]\n",pBuf,dwSize);
      #endif
      return;
   }

   if (!Decrypt((((BYTE*)pCodeBook) + (byFactor * BLOCK_SIZE)),pBuf,dwSize,pszFileName))
   {
      printf("Err: Can't decrypt [%s]\n",pszFileName);
   }
   
   _MF.Close();
}

/* ******************************************************************** **
** @@ ShowHelp()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void ShowHelp()
{
   const char  pszCopyright[] = "-*-   Bitch 1.1   *   Copyright (c) Gazlan 2011   -*-";
   const char  pszDescript [] = "SGDT decryptor";
   const char  pszE_Mail   [] = "complains_n_suggestions direct to gazlan@yandex.ru";

   printf("%s\n\n",pszCopyright);
   printf("%s\n\n",pszDescript);
   printf("Usage: bitch.com wildcards\n\n");
   printf("%s\n\n",pszE_Mail);
}

/* ******************************************************************** **
** @@ main()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

int main(int argc,char** argv)
{
   if (argc < 2)
   {
      ShowHelp();
      return 0;
   }

   if (argc == 2)
   {
      if ((!strcmp(argv[1],"?")) || (!strcmp(argv[1],"/?")) || (!strcmp(argv[1],"-?")) || (!stricmp(argv[1],"/h")) || (!stricmp(argv[1],"-h")))
      {
         ShowHelp();
      }
   }

   #ifdef _DEBUG
   _pOut = fopen("bitch.log","wt");
   #endif

   char     pszMask[MAX_PATH + 1];

   memset(pszMask,0,sizeof(pszMask));

   strncpy(pszMask,argv[1],MAX_PATH);
   pszMask[MAX_PATH] = 0; // ASCIIZ

   Walker      Visitor;

   Visitor.Init(ForEach,pszMask,false);
   Visitor.Run(".");

   #ifdef _DEBUG
   fclose(_pOut);
   _pOut = NULL;
   #endif

   return 0;
}

/* ******************************************************************** **
** @@                   End of File
** ******************************************************************** */
