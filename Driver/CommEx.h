#pragma once

//
//这个.h文件R3和R0都要引用
//

//-----------------------------------------------------------------------------
// R3和R0下使用的符号链接名
//-----------------------------------------------------------------------------
#define COMM_DEVICE_NAME_R0			L"\\Device\\RkExposerDevice"            //R0设备名
#define COMM_SYMLINK_R0				L"\\??\\RkExposer"                      //R0符号链接名
#define COMM_SYMLINK_R3				L"\\\\.\\RkExposer"                     //R3符号链接名，用于打开设备获取句柄

//-----------------------------------------------------------------------------
// 定义R3和R0的通信命令通过DeviceIoControl来控制
//-----------------------------------------------------------------------------
#define FILE_DEVICE_UNKNOWN             0x00000022
#define METHOD_BUFFERED                 0
#define FILE_ANY_ACCESS                 0

#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
    )
#define  CTRL_BASE 0xa00	// 大于0x800
#define CTRL_EXPRESSION(i)   CTL_CODE(FILE_DEVICE_UNKNOWN,(CTRL_BASE+i),METHOD_BUFFERED,FILE_ANY_ACCESS)
//判断是不是控制码
//#define CTRL_SUCCESS(code) (((code) &  0x88880000) == 0x88880000)

//
//定义一系列控制码，用于R3和R0通信，命令码开始以 "RKE"开始
//
#define RKE_COMM_TEST		                    CTRL_EXPRESSION(0)			//测试通信
#define RKE_ENUM_PROCESS_INFORMATION            CTRL_EXPRESSION(1)          //枚举进程信息命令
#define RKE_ENUM_THREAD_INFORMATION             CTRL_EXPRESSION(2)          //枚举线程信息命令

