#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_

typedef void DLinkStack;

DLinkStack* DLinkStack_Create();

void DLinkStack_Destroy(DLinkStack* stack);

void DLinkStack_Clear(DLinkStack* stack);

int DLinkStack_Length(DLinkStack* stack);

int DLinkStack_Push(DLinkStack* stack,void* item);

void* DLinkStack_Pop(DLinkStack* stack);

void* DLinkStack_Top(DLinkStack* stack);

#endif
