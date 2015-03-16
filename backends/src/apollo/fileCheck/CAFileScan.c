/*
 ============================================================================
 Name        : CAFileScan.c
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <iconv.h>

#include "sccca.h"
#include "scctype.h"
//#include "basetype.h"
//#include "list.h"

#define MAX_PATH_LENGTH 2048
#define ERROR_BUFFER_SIZE 0x100
#define CONTENT_BUFFER_SIZE  0x10000
#ifdef UNIX
#define PATH_TYPE   IOTYPE_UNIXPATH
#else
#define PATH_TYPE   IOTYPE_ANSIPATH
#endif

static char* SCANNING_STR = "Scanning ";
static char* FOUND_STR = " FOUND";
static char* FOUND_CNT = "#TOTAL:";
static char* SCAN_SUMMARY = "----------- SCAN SUMMARY -----------";
int CNT = 0;

typedef void (*FileProcCallBack)(int iIsDir, char *pcPathName, const char *keyWord);

/**  \brief Display an error message.  */
VTVOID displayError(DAERR const daErr, VTCHAR const * const source);
/**  \brief Process the given document through CA.  */
DAERR useCA(VTHDOC const hDoc, char *fileName, const char *keyWord);
int CAFileScan(char *fileName, const char *keyWord);

/******************************************************************************
 *    Function: DirectoryListNest
 * Description:
 *   Arguments: const char *pcDirPath, const char *keyWord, FileProcCallBack pfCallBack
 *      Return: void
 *****************************************************************************/
static void DirectoryListNest(char *pcDirPath, const char *keyWord, FileProcCallBack pfCallBack)
{
    DIR *pstDirectory;
    struct dirent *dir_entry;
    char szPathName[MAX_PATH_LENGTH];

    pstDirectory = opendir(pcDirPath);
    if (NULL == pstDirectory)
    {
        printf("opendir %s failed.\r\n", pcDirPath);
        return;
    }

    while (NULL != (dir_entry = readdir(pstDirectory)))
    {
        if (dir_entry->d_type & DT_DIR)
        {
            if (strcmp(dir_entry->d_name, ".") == 0 || strcmp(dir_entry->d_name, "..") == 0)
            {
                continue;
            }

            sprintf(szPathName, "%s/%s", pcDirPath, dir_entry->d_name);
            DirectoryListNest(szPathName, keyWord, pfCallBack);
        }
        else if (dir_entry->d_type & DT_REG)
        {
            sprintf(szPathName, "%s/%s", pcDirPath, dir_entry->d_name);
            pfCallBack(0, szPathName, keyWord);
        }
    }

    closedir(pstDirectory);
    return;
}

/******************************************************************************
 *    Function: ProcPath
 * Description:
 *   Arguments: int iIsDir, const char *pcPathName
 *      Return:
 *****************************************************************************/
void SearchPath(int iIsDir, char *pathName, const char *keyWord)
{
    VTHDOC hDoc;
    DAERR daErr;
    VTDWORD optionValue;
    VTDWORD dwXLSChanges;

    if (!iIsDir)
    {
        daErr = DAOpenDocument(&hDoc, IOTYPE_UNIXPATH, pathName, 0);
        if (daErr != DAERR_OK)
        {
            displayError(daErr, "DAOpenDocument");
            return;
        }

        dwXLSChanges = (VTDWORD) 1;
        daErr = DASetOption(hDoc, SCCOPT_GENERATEEXCELREVISIONS, &dwXLSChanges, sizeof(dwXLSChanges));
        if (daErr != DAERR_OK)
        {
            displayError(daErr, "DASetOption");
            return;
        }

        VTDWORD dwordOptionValue = SO_ANSI936;
        DASetOption(hDoc, SCCOPT_DEFAULTINPUTCHARSET, &dwordOptionValue, sizeof(dwordOptionValue));
        DASetOption(hDoc, SCCOPT_OUTPUTCHARACTERSET, &dwordOptionValue, sizeof(dwordOptionValue));

        daErr = useCA(hDoc, pathName, keyWord);
        if (daErr != DAERR_OK)
        {
            DACloseDocument(hDoc);
            return;
        }
        daErr = DACloseDocument(hDoc);
        if (daErr != DAERR_OK)
        {
            displayError(daErr, "DACloseDocument");
            return;
        }
    }
    return;
}

DAERR useCA(VTHDOC const hDoc, char *fileName, const char *keyWord)
{
    VTDWORD dwordOptionValue;

    printf("%s%s\n", SCANNING_STR, fileName);

    DAERR daErr;
    VTHCONTENT hcaContent;
    SCCCAGETCONTENT caContent;
    VTBYTE buffer[CONTENT_BUFFER_SIZE];

    dwordOptionValue = SCCEX_IND_GENERATED;
    daErr = DASetOption(hDoc, SCCOPT_CA_FLAGS, &dwordOptionValue, sizeof(dwordOptionValue));
    if (daErr != DAERR_OK)
    {
        displayError(daErr, "DASetOption");
    }

    /*  Set the fallback format to the FI_NONE */
    dwordOptionValue = FI_NONE;
    daErr = DASetOption(hDoc, SCCOPT_FALLBACKFORMAT, &dwordOptionValue, sizeof(dwordOptionValue));
    if (daErr != DAERR_OK)
    {
        displayError(daErr, "DASetOption");
    }

    daErr = CAOpenContent(hDoc, &hcaContent);
    if (daErr != DAERR_OK)
    {
        return daErr;
    }

    caContent.dwStructSize = sizeof(SCCCAGETCONTENT);
    caContent.dwFlags = 0;
    caContent.dwMaxBufSize = CONTENT_BUFFER_SIZE;
    caContent.pDataBuf = buffer;
    memset(buffer, 0, sizeof(buffer));

    daErr = CAReadFirst(hcaContent, &caContent);
    if (daErr != DAERR_OK)
    {
        displayError(daErr, "CAReadFirst");
        CACloseContent(hcaContent);
        return daErr;
    }

    int flag = 0;
    while ((daErr == DAERR_OK || daErr == DAERR_MISALIGNMENT) && (0 == flag))
    {
        switch (caContent.dwType)
        {
            case SCCCA_TEXT:
            {
                if (0 != (SCCCA_DOCUMENTTEXT & caContent.dwSubType))
                {
                    if (flag == 0 && NULL != strstr((VTBYTE*) (caContent.pDataBuf), keyWord))
                    {
                        CNT++;
                        printf("%s%s\n", fileName, FOUND_STR);
                        flag = 1;
                    }
                }

                break;
            }
            default:
                break;
        }

        daErr = CAReadNext(hcaContent, &caContent);
    }

    /*  EOF is normal successful completion.  */
    if ((daErr != DAERR_EOF) && (0 == flag))
    {
        displayError(daErr, "CAReadNext");
        CACloseContent(hcaContent);
        return daErr;
    }

    daErr = CACloseContent(hcaContent);
    if (daErr != DAERR_OK)
    {
        displayError(daErr, "CACloseContent");
    }

    return daErr;
}

VTVOID displayError(DAERR const daErr, VTCHAR const * const source)
{
    return;
}

int CAFileScan(char *fileName, const char *keyWord)
{
    // init CA
    VTDWORD optionValue;

    DAERR daErr = DAInitEx(SCCOPT_INIT_NOTHREADS, OI_INIT_DEFAULT);
    if (daErr != DAERR_OK)
    {
        displayError(daErr, "DAInitEx");
        return daErr;
    }

    optionValue = SCCUT_FI_EXTENDEDTEST;
    daErr = DASetOption(0, SCCOPT_FIFLAGS, &optionValue, sizeof(optionValue));
    if (daErr != DAERR_OK)
    {
        displayError(daErr, "DASetOption");
        DADeInit();
        return daErr;
    }

    DirectoryListNest(fileName, keyWord, SearchPath);
    printf("%s\n%s%d\n", SCAN_SUMMARY, FOUND_CNT, CNT);

    // deinit CA
    daErr = DADeInit();
    if (daErr != DAERR_OK)
    {
        displayError(daErr, "DADeInit");
    }
    return 1;
}

int main(int argc, char* argv[])
{
    iconv_t hConv;
    long lInLen, lOutLen, i;
    char *pcGBKBuffer;
    char *pcIn, *pcOut;

    if (argc < 3)
    {
        printf("Arguments is wrong: %s  %s\n", argv[1], argv[2]);
        return -1;
    }

    lInLen = strlen(argv[2]) + 1;
    lOutLen = lInLen * 4;
    pcGBKBuffer = (char *) malloc(lOutLen);
    if (NULL != pcGBKBuffer)
    {
        hConv = iconv_open("GBK", "UTF-8");
        bzero(pcGBKBuffer, lInLen * 4);
        pcIn = argv[2];
        pcOut = pcGBKBuffer;
        iconv(hConv, &pcIn, (size_t *) &lInLen, &pcOut, (size_t *) &lOutLen);
        iconv_close(hConv);

        CAFileScan(argv[1], pcGBKBuffer);

        free(pcGBKBuffer);
    }

    return 0;
}



