/*
 |    FileName: CAFileScan.c
 |      
 |        
 | Description:
 |
 */
#ifdef __cpluscplus
extern "C"
{
#endif

/* standard head files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <iconv.h>

/* common lib head files */
#include "sccca.h"
#include "scctype.h"
#include "basetype.h"
#include "list.h"

typedef struct tagKeywords
{
    STL_NODE_S stNode;
    CHAR szKeyWord[0];
} KEYWORD_NODE_S;

typedef VOID (*FILESCAN_CALLBACK_PF)(CHAR *pcFilePath, STL_HEAD_S *pstKeWordsList);

#define SCANNING_STR    "Scanning"
#define FOUND_STR       "FOUND"
#define FOUND_CNT       "#TOTAL:"
#define SCAN_SUMMARY    "----------- SCAN SUMMARY -----------"
#define SCAN_HELPINFO   "\nCAFileScan: You need to give a path following by some keywords.\n"\
                        "Usage: CAFileScan PATH KEYWORD1 [ KEYWORD2 ...]\n"\
                        "PATH\t\t the root directory path that you want to search the keywords\n"\
                        "KEYWORD\t\t the keyword you need to search\n"

#define CONTENT_BUFFER_SIZE 0x10000
STATIC ULONG g_ulFoundCnt = 0;

/*
 |    Function: CA_UseCA
 |      
 | Description: use CA
 |   Arguments: VTHDOC const hDoc, char *pcFilePath, const STL_HEAD_S *pstKeWordsList
 |      Return:
 |
 */
STATIC DAERR CA_UseCA(VTHDOC const hDoc, CHAR *pcFilePath, const STL_HEAD_S *pstKeWordsList)
{
    BOOL_T bFound;
    DAERR daErr;
    VTHCONTENT hCAContent;
    SCCCAGETCONTENT stCAContent;
    STL_NODE_S *pstEntry;
    KEYWORD_NODE_S *pstKeyWordNode;
    VTBYTE szbuffer[CONTENT_BUFFER_SIZE];

    printf("%s %s\n", SCANNING_STR, pcFilePath);

    daErr = CAOpenContent(hDoc, &hCAContent);
    if (daErr != DAERR_OK)
    {
        return daErr;
    }

    memset(szbuffer, 0, sizeof(szbuffer));
    stCAContent.dwStructSize = sizeof(SCCCAGETCONTENT);
    stCAContent.dwFlags = 0;
    stCAContent.dwMaxBufSize = CONTENT_BUFFER_SIZE;
    stCAContent.pDataBuf = szbuffer;

    daErr = CAReadFirst(hCAContent, &stCAContent);
    if (daErr != DAERR_OK)
    {
        CACloseContent(hCAContent);
        return daErr;
    }

    bFound = BOOL_FALSE;
    while (daErr == DAERR_OK || daErr == DAERR_MISALIGNMENT)
    {
        if ((SCCCA_TEXT == stCAContent.dwType) && (0 != (SCCCA_DOCUMENTTEXT & stCAContent.dwSubType)))
        {
            STL_FOREACH_NODE(pstKeWordsList, pstEntry)
            {
                pstKeyWordNode = (KEYWORD_NODE_S *) pstEntry;
                if (NULL != strstr((VTBYTE*) (stCAContent.pDataBuf), pstKeyWordNode->szKeyWord))
                {
                    printf("%s %s\n", pcFilePath, FOUND_STR);
                    g_ulFoundCnt++;

                    bFound = BOOL_TRUE;
                    break;
                }
            }

            if (BOOL_TRUE == bFound)
            {
                break;
            }
        }

        daErr = CAReadNext(hCAContent, &stCAContent);
    }

    (VOID) CACloseContent(hCAContent);

    return daErr;
}

/*
 |    Function: CA_FileSearch
 |      
 |        
 | Description: CA file search the keywords
 |   Arguments: CHAR *pcFilePath, STL_HEAD_S *pstKeWordsList
 |      Return:
 |
 */
STATIC VOID CA_FileSearch(CHAR *pcFilePath, STL_HEAD_S *pstKeWordsList)
{
    VTHDOC hDoc;
    DAERR daErr;
    VTDWORD dwordOptionValue;

    daErr = DAOpenDocument(&hDoc, IOTYPE_UNIXPATH, pcFilePath, 0);
    if (daErr == DAERR_OK)
    {
        dwordOptionValue = SO_ANSI936;
        DASetOption(hDoc, SCCOPT_DEFAULTINPUTCHARSET, &dwordOptionValue, sizeof(dwordOptionValue));
        DASetOption(hDoc, SCCOPT_OUTPUTCHARACTERSET, &dwordOptionValue, sizeof(dwordOptionValue));

        (VOID) CA_UseCA(hDoc, pcFilePath, pstKeWordsList);
        (VOID) DACloseDocument(hDoc);
    }

    return;
}

/*
 |    Function: SCAN_CheckArgs
 |      
 |        
 | Description: check if the given argumens is right
 |   Arguments: INT iArgc, CHAR **ppArgv
 |      Return: BOOL_T
 |
 */
STATIC BOOL_T SCAN_CheckArgs(INT iArgc, CHAR **ppArgv)
{
    BOOL_T bRet = BOOL_TRUE;
    DIR *pstDirectory;

    if (2 >= iArgc)
    {
        bRet = BOOL_FALSE;
    }
    else
    {
        /* check if the PATH is valid or readable */
        pstDirectory = opendir(ppArgv[1]);
        if (NULL == pstDirectory)
        {
            printf("CAFileScan: the given path is not avalid.\n");
            bRet = BOOL_FALSE;
        }
        else
        {
            closedir(pstDirectory);
        }
    }

    if (BOOL_TRUE != bRet)
    {
        printf(SCAN_HELPINFO);
    }

    return bRet;
}

/*
 |    Function: SCAN_SaveKeyWords
 |      
 |        
 | Description: save the keywords to the list
 |   Arguments: STL_HEAD_S *pstList, CHAR *pcKeyWord
 |      Return:
 |
 */
STATIC VOID SCAN_SaveKeyWords(INT iArgc, CHAR **ppArgv, STL_HEAD_S *pstList)
{
    LONG i;
    LONG lInLen;
    LONG lOutLen;
    CHAR *pcUtf8;
    CHAR *pcGbk;
    iconv_t hConv;
    KEYWORD_NODE_S *pstKeyWord;

    for (i = 2; i < iArgc; i++)
    {
        pcUtf8 = ppArgv[i];
        lInLen = strlen(pcUtf8) + 1;
        lOutLen = lInLen * 4;

        pstKeyWord = (KEYWORD_NODE_S *) malloc(sizeof(KEYWORD_NODE_S) + lOutLen);
        if (NULL != pstKeyWord)
        {
            memset((VOID *) pstKeyWord, 0, sizeof(KEYWORD_NODE_S) + lOutLen);
            hConv = iconv_open("GBK", "UTF-8");
            pcGbk = (CHAR *) pstKeyWord->szKeyWord;
            iconv(hConv, &pcUtf8, (size_t *) &lInLen, &pcGbk, (size_t *) &lOutLen);
            iconv_close(hConv);

            STL_InitNode(&(pstKeyWord->stNode));
            STL_AddTail(pstList, &(pstKeyWord->stNode));
        }
    }

    return;
}

/*
 |    Function: SCAN_DirScan
 |      
 |        
 | Description: search the root path and all the sub dirs
 |   Arguments: CHAR *pcRootPath, STL_HEAD_S *pstKeyWordsList, FILE_SCAN_CALLBACK_PF pfCallBack
 |      Return:
 |
 */
STATIC VOID SCAN_DirScan(CHAR *pcDirPath, STL_HEAD_S *pstKeyWordsList, FILESCAN_CALLBACK_PF pfCallBack)
{
    ULONG ulDirPathLen;
    ULONG ulPathLen;
    CHAR *pcPathName;
    DIR *pstDirectory;
    struct dirent *dir_entry;

    pstDirectory = opendir(pcDirPath);
    if (NULL == pstDirectory)
    {
        printf("CAFileScan: opendir %s failed.\r\n", pcDirPath);
        return;
    }

    ulDirPathLen = strlen(pcDirPath);
    if ('/' == pcDirPath[ulDirPathLen - 1])
    {
        pcDirPath[ulDirPathLen - 1] = 0;
    }

    ulDirPathLen = strlen(pcDirPath) + 2;
    while (NULL != (dir_entry = readdir(pstDirectory)))
    {
        if (dir_entry->d_type & DT_DIR)
        {
            if (strcmp(dir_entry->d_name, ".") == 0 || strcmp(dir_entry->d_name, "..") == 0)
            {
                continue;
            }

            ulPathLen = ulDirPathLen + strlen(dir_entry->d_name);
            pcPathName = (CHAR *) malloc(ulPathLen);
            if (NULL != pcPathName)
            {
                sprintf(pcPathName, "%s/%s", pcDirPath, dir_entry->d_name);
                SCAN_DirScan(pcPathName, pstKeyWordsList, pfCallBack);
                free(pcPathName);
            }
        }
        else if (dir_entry->d_type & DT_REG)
        {
            ulPathLen = ulDirPathLen + strlen(dir_entry->d_name);
            pcPathName = (CHAR *) malloc(ulPathLen);
            if (NULL != pcPathName)
            {
                sprintf(pcPathName, "%s/%s", pcDirPath, dir_entry->d_name);
                pfCallBack(pcPathName, pstKeyWordsList);
                free(pcPathName);
            }
        }
    }

    closedir(pstDirectory);

    return;
}

/*
 |    Function: main
 |      
 |        
 | Description: Main Route, search given keywords frome the path
 |   Arguments: INT iArgc, CHAR **ppArgv
 |      Return:
 |
 */
INT main(INT iArgc, CHAR **ppArgv)
{
    DAERR daErr;
    STL_HEAD_S stKeyWordsList;

    if (BOOL_TRUE != SCAN_CheckArgs(iArgc, ppArgv))
    {
        return -1;
    }

    STL_InitHead(&stKeyWordsList);
    SCAN_SaveKeyWords(iArgc, ppArgv, &stKeyWordsList);

    daErr = DAInitEx(SCCOPT_INIT_NOTHREADS, OI_INIT_DEFAULT);
    if (daErr == DAERR_OK)
    {
        SCAN_DirScan(ppArgv[1], &stKeyWordsList, CA_FileSearch);
        printf("%s\n%s%d\n", SCAN_SUMMARY, FOUND_CNT, g_ulFoundCnt);

        (VOID) DADeInit();
    }

    STL_FreeAll(&stKeyWordsList, free);

    return 0;
}

#ifdef __cpluscplus
}
#endif
