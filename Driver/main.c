//
//头文件包含
//
#include <ntddk.h>
#include "Comm.h"
#include "Utils.h"

//
//函数声明
//
VOID DriverUnload(IN PDRIVER_OBJECT pDriverObj);


//
//驱动入口函数
//
NTSTATUS
DriverEntry(IN PDRIVER_OBJECT pDriverObj, IN PUNICODE_STRING pRegistryString)
{
    NTSTATUS status = STATUS_UNSUCCESSFUL;
    /*注册卸载函数*/
    pDriverObj->DriverUnload = DriverUnload;

    /*建立通信*/
    status = CmSetupComm(pDriverObj);
    if(!NT_SUCCESS(status))
        return status;


    return STATUS_SUCCESS;
}

//
//驱动卸载函数
//
VOID
 DriverUnload(IN PDRIVER_OBJECT pDriverObj)
{	
    LogPrint("DriverUnload called\r\n");
    /*删除通信*/
    CmDeleteComm(pDriverObj);
}