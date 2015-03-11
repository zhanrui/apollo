/*
 ============================================================================
 Name        : CAFileScan.c
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "scctype.h"
#include "sccca.h"

#define MAX_PATH_LENGTH 2048
#define ERROR_BUFFER_SIZE 0x100
#define CONTENT_BUFFER_SIZE  0x10000
#ifdef UNIX
#define PATH_TYPE   IOTYPE_UNIXPATH
#else
#define PATH_TYPE   IOTYPE_ANSIPATH
#endif
#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif
#define BOOL_TRUE ((unsigned short)1)
#define BOOL_FALSE ((unsigned short)0)

static char* SCANNING_STR = "Scanning ";
static char* FOUND_STR = " FOUND";
static char* FOUND_CNT = "#TOTAL:";
static char* SCAN_SUMMARY = "----------- SCAN SUMMARY -----------";
int CNT = 0;

typedef void (*FileProcCallBack)(int iIsDir, char *pcPathName,
		const char *keyWord);

/**  \brief Display an error message.  */
VTVOID displayError(DAERR const daErr, VTCHAR const * const source);
/**  \brief Process the given document through CA.  */
DAERR useCA(VTHDOC const hDoc, char *fileName, const char *keyWord);
DAERR setOptions(VTHDOC const hDoc);
int CAFileScan(char *fileName, const char *keyWord);

/******************************************************************************
 *    Function: DirectoryListNest
 * Description: 列出给定目录下的所有文件和子目录，并调用回调函数处理
 *   Arguments: const char *pcDirPath, const char *keyWord, FileProcCallBack pfCallBack
 *      Return: void
 *****************************************************************************/
static void DirectoryListNest(char *pcDirPath, const char *keyWord,
		FileProcCallBack pfCallBack) {

	DIR *pstDirectory;
	struct dirent *dir_entry;
	char szPathName[MAX_PATH_LENGTH];

	pstDirectory = opendir(pcDirPath);
	if (NULL == pstDirectory) {
		printf("opendir %s failed.\r\n", pcDirPath);
		return;
	}

	while (NULL != (dir_entry = readdir(pstDirectory))) {
		if (dir_entry->d_type & DT_DIR) {
			if (strcmp(dir_entry->d_name, ".") == 0
					|| strcmp(dir_entry->d_name, "..") == 0) {
				continue;
			}

			sprintf(szPathName, "%s/%s", pcDirPath, dir_entry->d_name);
			pfCallBack(1, szPathName, keyWord);
			DirectoryListNest(szPathName, keyWord, pfCallBack);
		} else if (dir_entry->d_type & DT_REG) {
			sprintf(szPathName, "%s/%s", pcDirPath, dir_entry->d_name);
			pfCallBack(0, szPathName, keyWord);
		}
	}

	closedir(pstDirectory);
	return;
}

/******************************************************************************
 *    Function: ProcPath
 * Description: 处理每个文件的回调处理函数
 *   Arguments: int iIsDir, const char *pcPathName
 *      Return:
 *****************************************************************************/
void SearchPath(int iIsDir, char *pathName, const char *keyWord) {
	// iIsDir ==  Dir
	// !iIsDir == File
	VTHDOC hDoc;
	DAERR daErr;
	VTDWORD optionValue;
	VTDWORD dwXLSChanges;
	if (!iIsDir) {
		// 调用CA，判断文件内容是否匹配字符串
		/*
		 Open our input document.
		 */
		VTDWORD dwordOptionValue = CS_WINDOWS_936;
		DASetOption(hDoc, SCCOPT_DEFAULTINPUTCHARSET, &dwordOptionValue,
				sizeof(dwordOptionValue));
		dwordOptionValue = CS_WINDOWS_936;
		DASetOption(hDoc, SCCOPT_OUTPUTCHARACTERSET, &dwordOptionValue,
				sizeof(dwordOptionValue));

//		daErr = DAOpenDocument(&hDoc, PATH_TYPE, pathName, 0);
		daErr = DAOpenDocument(&hDoc, IOTYPE_UNIXPATH, pathName, 0);

		if (daErr != DAERR_OK) {
			displayError(daErr, "DAOpenDocument");
			DADeInit();
			return;
		}
		/*  Use CA to process the document.  */
		daErr = useCA(hDoc, pathName, keyWord);
		if (daErr != DAERR_OK) {
			displayError(daErr, "useCA");
			DACloseDocument(hDoc);
			DADeInit();
			return;
		}
		daErr = DACloseDocument(hDoc);
		if (daErr != DAERR_OK) {
			displayError(daErr, "DACloseDocument");
			DADeInit();
			return;
		}

	}
	return;
}

/**
 Exercise CA by processing the given document.  This function can be
 called recursively to process sub-documents (embeddings for example).

 \param  hDoc    A handle to the document to be processed.  This handle
 is created by a call to DAOpenDocument or DAOpenTreeRecord.

 \return A DA related error code.  DAERR_OK for success.
 */
DAERR useCA(VTHDOC const hDoc, char *fileName, const char *keyWord) {

	printf("%s%s\n", SCANNING_STR, fileName);

	DAERR daErr;
	VTHCONTENT hcaContent;
	SCCCAGETCONTENT caContent;
	VTBYTE buffer[CONTENT_BUFFER_SIZE];

	/*
	 Initialize the CA content handle.  Successful calls to CAOpenContent
	 should be matched by calls to CACloseContent.

	 CAOpenContent Parameters:
	 1)  A handle to the document to be processed.
	 2)  Pointer to a handle that will receive a value uniquely
	 identifying the document to the Content Access routines.

	 CAOpenContent returns a DAERR code.  DAERR_OK indicates success.
	 */
	daErr = CAOpenContent(hDoc, &hcaContent);
	if (daErr != DAERR_OK) {
		displayError(daErr, "CAOpenContent");
		return daErr;
	}

	/*
	 Set up the structure used to return CA items.  Particularly, it is
	 the consumer's responsibility to provide a buffer of at least 1K
	 bytes.  SCCCA_GENERATED, and SCCCA_SHEET items require that the
	 buffer be aligned on a 2 byte boundary.
	 */
	caContent.dwStructSize = sizeof(SCCCAGETCONTENT);
	caContent.dwFlags = 0;
	caContent.dwMaxBufSize = CONTENT_BUFFER_SIZE;
	caContent.pDataBuf = buffer;

	/*
	 Read the first CA item.  If successful, CAReadFirst will return the
	 file properties and initial character set of the source.

	 CAReadFirst Parameters:
	 1)  The Content Access handle for the document as returned by
	 CAOpenContent.
	 2)  A pointer to a structure to be filled with CA data.
	 CAReadFirst will fill this structure with SCCCA_FILEPROPERTY
	 related information if successful.

	 CAReadFirst returns a DAERR code.  DAERR_OK indicates success.
	 */
	daErr = CAReadFirst(hcaContent, &caContent);
	if (daErr != DAERR_OK) {
		displayError(daErr, "CAReadFirst");
		CACloseContent(hcaContent);
		return daErr;
	}

	/*
	 Process CA items.  During CA processing several error codes are of
	 interest:

	 DAERR_OK:   Successful creation of a CA item.
	 DAERR_MISALIGNMENT:
	 pDataBuf was not aligned properly for the item CA
	 was trying to create.  CA will still provide
	 reasonable values in the content structure, and
	 processing can continue.
	 DAERR_EOF:  End of file was reached.  This signals normal
	 successful completion.
	 */
	int flag = 0;
	while (daErr == DAERR_OK || daErr == DAERR_MISALIGNMENT) {
		switch (caContent.dwType) {
		case SCCCA_TEXT:
			/*
			 Text.

			 When dwType is SCCCA_TEXT:
			 dwSubType     contains flags providing attribute
			 information about the text (SCCCA_BOLD
			 to indicate that the text is bold, for
			 example).
			 dwData1       is the number of characters in the text.
			 dwData2       shows the input character set of the text.
			 dwDataBufSize contains the size of the text in bytes.
			 pDataBuf      points to the buffer containing the text.
			 */
			// 0x14b00000 -- CS_UNICODE
			// #define CS_WINDOWS_936  SO_ANSI936  /* Windows Code Page 936 (Simplified Chinese GBK)
			if (flag == 0
					&& NULL
							!= strstr((VTBYTE*) (caContent.pDataBuf),
									keyWord)) {
				CNT++;
				printf("%s%s\n", fileName, FOUND_STR);
				flag = 1;
			}
			break;

		default:
			/*  Unknown CA type. Do nothing. */
//			printf("\t***  Error:  Unexpected type (0x%08x) from CA.  ***\n",
//					caContent.dwType);
			break;
		}

		/*
		 Read the next CA item.

		 CAReadNext Parameters:
		 1)  The Content Access handle for the document as returned
		 by CAOpenContent.
		 2)  A pointer to a structure to be filled with CA data.

		 CAReadNext returns a DAERR code.
		 */
		daErr = CAReadNext(hcaContent, &caContent);
	}

	/*  EOF is normal successful completion.  */
	if (daErr != DAERR_EOF) {
		displayError(daErr, "CAReadNext");
		CACloseContent(hcaContent);
		return daErr;
	}

	/*
	 Close the CA content.

	 CACloseContent Parameters:
	 1)  The Content Access handle for the document as returned by
	 CAOpenContent.

	 CACloseContent returns a DAERR code.  DAERR_OK indicates success.
	 */
	daErr = CACloseContent(hcaContent);
	if (daErr != DAERR_OK) {
		displayError(daErr, "CACloseContent");
	}

	return daErr;
}


DAERR setOptions(VTHDOC const hDoc) {
	DAERR daErr;
	VTDWORD dwordOptionValue;
	VTBOOL bExtractXMPMetadata = FALSE;

	/*  Set default input character set.  */
	dwordOptionValue = CS_WINDOWS_936;
	daErr = DASetOption(hDoc, SCCOPT_DEFAULTINPUTCHARSET, &dwordOptionValue,
			sizeof(dwordOptionValue));
	if (daErr != DAERR_OK) {
		displayError(daErr, "DASetOption");
	}

	/*  Set output character set.  */
	dwordOptionValue = CS_WINDOWS_936;
	daErr = DASetOption(hDoc, SCCOPT_OUTPUTCHARACTERSET, &dwordOptionValue,
			sizeof(dwordOptionValue));
	if (daErr != DAERR_OK) {
		displayError(daErr, "DASetOption");
	}
	/*
	 set extract xmp metadata
	 daErr = DASetOption(hDoc, SCCOPT_EXTRACTXMPMETADATA, &bExtractXMPMetadata,
	 sizeof(VTBOOL));
	 if (daErr != DAERR_OK) {
	 displayError(daErr, "DASetOption");
	 }*/
	return daErr;
}

VTVOID displayError(DAERR const daErr, VTCHAR const * const source) {
	char buffer[ERROR_BUFFER_SIZE];
	/*
	 While there is no way to know how big an error message is going to be,
	 DAGetErrorString will truncate if needed.

	 DAGetErrorString Parameters:
	 1)  A DA related error code.
	 2)  A pointer to a buffer to receive the error related message.
	 3)  The size of the buffer in parameter 2.
	 */
	DAGetErrorString(daErr, buffer, ERROR_BUFFER_SIZE);

	fprintf(stderr, "\n***  Error: %s in %s.  ***\n\n", buffer, source);
}

int CAFileScan(char *fileName, const char *keyWord) {

	// init CA
	DAERR daErr = DAInitEx(SCCOPT_INIT_NOTHREADS, OI_INIT_DEFAULT);
	if (daErr != DAERR_OK) {
		displayError(daErr, "DAInitEx");
		return daErr;
	}
	DirectoryListNest(fileName, keyWord, SearchPath);
	printf("%s\n%s%d\n", SCAN_SUMMARY, FOUND_CNT, CNT);

	// deinit CA
	daErr = DADeInit();
	if (daErr != DAERR_OK) {
		displayError(daErr, "DADeInit");
	}
	return 1;
}

int main(int argc, char* argv[]) {

	if (argc != 3) {
		printf("参数错误: %s  %s\n", argv[1], argv[2]);
		return -1;
	}

	return CAFileScan(argv[1], argv[2]);

}
