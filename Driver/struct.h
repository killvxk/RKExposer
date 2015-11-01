#pragma  once


//typedef wchar_t         WCHAR;
//typedef unsigned char  BOOL, *PBOOL;
//typedef unsigned char  BYTE, *PBYTE;
//typedef unsigned long  DWORD, *PDWORD;
//typedef unsigned short WORD, *PWORD;
//
//typedef unsigned int    UINT;
//
//自己定义的结构体
//
#define MAX_BUFFER_LENGTH       (260)

#pragma pack(push)
#pragma pack(1)
//-----------------------------------------------------------------------------
// 通信中信息传输相关的结构体
//-----------------------------------------------------------------------------

//
//应用层访问状态
//
typedef enum USER_ACCESS_STATE{
    UAS_ACCESSIBLE  = 0,    //可访问
    UAS_REFUSED     = 1,    //拒绝
    UAS_OTHER       = 100   //其他
};
//
//内核层检测状态
//
typedef enum KERNEL_DETECT_STATE{
    KDS_NORMAL      = 0,
    KDS_HIDE        = 1
};

//
//进程相关信息结构体
//
typedef struct tagRKE_PROCESS_INFORMATION{
    wchar_t ImageName[MAX_BUFFER_LENGTH];           //进程映像名
    unsigned long Eprocess;                         //进程对象
    unsigned long ProcessId;                        //进程id
    unsigned long ParentId;                         //父进程id
    wchar_t ImagePath[MAX_BUFFER_LENGTH];           //进程路径
    wchar_t FileManufacturer[MAX_BUFFER_LENGTH];    //文件厂商
    KERNEL_DETECT_STATE KernelDetState;             //内核里检测的结果，正常还是 隐藏

}RKE_PROCESS_INFORMATION,*PRKE_PROCESS_INFORMATION;
#pragma pack(pop)