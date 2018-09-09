#include "SeqQueue.h"
#include "SeqList.h"

SeqQueue* SeqQueue_Create(int capacity)
{
	return SeqList_Create(capacity);
}

void SeqQueue_Destroy(SeqQueue* queue)
{
	SeqList_Destroy(queue);
}

void SeqQueue_Clear(SeqQueue* queue)
{
	SeqList_Clear(queue);
}

int SeqQueue_Capacity(SeqQueue* queue)
{
	return SeqList_Capacity(queue);
}

int SeqQueue_Length(SeqQueue* queue)
{
	return SeqList_Length(queue);
}

int SeqQueue_Append(SeqQueue* queue,void* item)
{
	return SeqList_Insert(queue,(SeqListNode*)item,SeqList_Length(queue));
}

void* SeqQueue_Retrieve(SeqQueue* queue)
{
	return SeqList_Delete(queue,0);
}

void* SeqQueue_Header(SeqQueue* queue)
{
	return SeqList_Get(queue,0);
}
