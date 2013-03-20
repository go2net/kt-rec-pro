#ifndef _FATFS
#define _FATFS

#include "config.h"
#include "diskio.h"

#ifdef __C51__

/* File system API info */
typedef struct _FSAPIMSG
{
    u16     fileCounter;		// 文件计数,搜索文件时,可以用它来计算总的文件数
    u16	    fileNumber;			// 当前文件序号
    u16	    fileTotal;			// 文件总数
    u16     dirTotal;			// 文件夹总数
    u16     fileTotalInDir;     // 当前目录的根下有效文件的个数
    u16     fileTotalOutDir;	// 当前目录前的文件总数，目录循环模式下，需要用它来计算文件序号
    u8	    deepth;				// dir deepth for search
    u16     file_index;
    u16     dir_index;
    u8      fname[12];		    //当前文件的短名
    u8      dname[12];		    //当前目录的短名
} FSAPIMSG;

/* File object structure */
typedef struct _FIL
{
    u8      flag;
    u32		fptr;				// File R/W pointer
    u32 	curr_clust;			// Current cluster
    u32		curr_sect;			// Current sector
    u32 	org_clust;			// File start cluster
    u32		fsize;				// File size
    u32     seek_size;
    u32     start_clust;		// 连续簇开始
    u32     end_clust;          // 连续簇结束
    u8      _xdata *buf;
} FIL;

typedef struct _FIL_BACKUP
{
    u8      flag;
    u32		fptr;				// File R/W pointer
    u32 	curr_clust;			// Current cluster
    u32		curr_sect;			// Current sector
} FIL_BACKUP;

enum
{
    SEEK_SET = 0x10,
    SEEK_CUR = 0x20
};
#endif


#endif /* _FATFS */
