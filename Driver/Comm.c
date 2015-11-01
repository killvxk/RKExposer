#include "Comm.h"
#include "Utils.h"

//
//命令分发函数，用于分发R3发出的命令
//
NTSTATUS UserCmdDispatcher (IN PDEVICE_OBJECT DeviceObject,IN PIRP pIrp)
{
    NTSTATUS status				= STATUS_SUCCESS;
    PIO_STACK_LOCATION stack	= NULL;
    ULONG cbin					= 0;
    ULONG cbout					= 0;
    ULONG cmd					= 0;
    ULONG info					= 0;
    stack	= IoGetCurrentIrpStackLocation(pIrp);
    /*输入缓冲区大小*/
    cbin    = stack->Parameters.DeviceIoControl.InputBufferLength;
    /*输出缓冲区大小*/
    cbout   = stack->Parameters.DeviceIoControl.OutputBufferLength;
    //得到命令码
    cmd		= stack->Parameters.DeviceIoControl.IoControlCode;
    switch(cmd){
    case RKE_COMM_TEST:
        {

        }
        break;

    default:
        status  = STATUS_INVALID_VARIANT;
        break;
    }
    /*设置irp完成状态*/
    pIrp->IoStatus.Status      = status;
    /*设置irp请求的操作数*/
    pIrp->IoStatus.Information = info;
    //结束irp请求
    IoCompleteRequest(pIrp,IO_NO_INCREMENT);
    return status;
}

//
//删除通信设备
//
VOID CmDeleteComm(IN PDRIVER_OBJECT pDriverObj)
{
    PDEVICE_OBJECT		pDevObj			= NULL;
    UNICODE_STRING		uniSymLink   	= {0};

    pDevObj = pDriverObj->DeviceObject;
    if (pDevObj != NULL){
        /*删除符号链接*/
        RtlInitUnicodeString(&uniSymLink,COMM_SYMLINK_R0);
        IoDeleteSymbolicLink(&uniSymLink);

        /*删除设备*/
        IoDeleteDevice(pDevObj);
        pDevObj = NULL;
        LogPrint("CmDeleteComm ok!\r\n");
    }

}

//
//建立R3与R0的通信
//
NTSTATUS CmSetupComm(PDRIVER_OBJECT pDriverObj)
{
    NTSTATUS			ntStatus		= STATUS_UNSUCCESSFUL;	
    UNICODE_STRING		uniDeviceName	= {0};
    UNICODE_STRING		uniSymLink  	= {0};
    PDEVICE_OBJECT		pDevObj			= NULL;

    /*创建设备*/
    RtlInitUnicodeString(&uniDeviceName,COMM_DEVICE_NAME_R0);
    ntStatus = IoCreateDevice(pDriverObj,
        0,
        &uniDeviceName,
        FILE_DEVICE_UNKNOWN,
        0,
        TRUE,
        &pDevObj);
    if (!NT_SUCCESS(ntStatus)){
        LogPrint("IoCreateDevice failed...\r\n");
        return ntStatus;
    }
    /*配置设备通信模式*/
    pDevObj->Flags |= DO_BUFFERED_IO;

    /*创建符号链接*/
    RtlInitUnicodeString(&uniSymLink,COMM_SYMLINK_R0);
    ntStatus = IoCreateSymbolicLink(&uniSymLink,&uniDeviceName);
    if(!NT_SUCCESS(ntStatus)){
        LogPrint("IoCreateSymbolicLink failed...\r\n");
        IoDeleteDevice(pDevObj);
        return ntStatus;
    }
    LogPrint("CmSetupComm ok!\r\n");
    /*创建成功，注册派遣例程，这里只注册了 io control的派遣*/
    pDriverObj->MajorFunction[IRP_MJ_DEVICE_CONTROL]    = UserCmdDispatcher;
    return STATUS_SUCCESS;
}