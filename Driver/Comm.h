#pragma once
#include <ntddk.h>
//
//负责处理R0通信相关的函数，Cm = Communication
//
#include "CommEx.h"

VOID CmDeleteComm(IN PDRIVER_OBJECT pDriverObj);

NTSTATUS CmSetupComm(PDRIVER_OBJECT pDriverObj);