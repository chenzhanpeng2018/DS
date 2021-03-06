#if 0
//2019.12.26
//1.
//将两个有序序列合并成为一个有序序列
#include<iostream>
#include<windows.h>
using namespace std;
int main()
{
	int M1[] = { 1, 3, 4, 6, 8 };
	int M2[] = { 2, 5, 8, 9, 20, 30};
	int size1 = sizeof(M1)/sizeof(M1[0]);
	int size2 = sizeof(M2)/sizeof(M2[0]);
	//printf("%d %d", size1, size2);
	int index1 = 0;
	int index2 = 0;
	int index = 0;
	int M[100];
	while (index1<size1&&index2<size2)
	{
		if (M1[index1] <= M2[index2])
		{
			M[index++] = M1[index1++];
		}
		else
		{
			M[index++] = M2[index2++];
		}
	}
	while (index1 < size1)
	{
		M[index++] = M1[index1++];
	}
	while (index2 < size2)
	{
		M[index++] = M2[index2++];
	}


	int i = 0;
	for (; i < size1 + size2; i++)
	{
		printf("%d ", M[i]);
	}
	system("pause");
	return 0;
}
#endif

#if 0
//2.
//查找字符串第一个出现一次的字符
#include<iostream>
#include<windows.h>
using namespace std;

int main()
{
	char str[100]="abcdfeabcd";
	int all[256]={0};
	int len=strlen(str);
	int i=0;
	for(;i<len;i++)
	{
		all[str[i]]++;	
	} 

	for(i=0;i<len;i++)
	{
		if(1==all[str[i]])
		{
			printf("%c\n",str[i]);
			break; 
		}
	}
	system("pause");
	return 0;
}
#endif


#if 0
//3.
//顺序表的操作
#include<iostream>
#include<assert.h>
#include<windows.h>
using namespace std;

//动态顺序表结构
//优势：存储元素个数不受限，不够再给你开辟
typedef int  DataType;
typedef struct SeqList
{
	DataType* array;  //数组
	int capacity;     //表示空间总大小
	int size;        //记录有效元素个数
}SeqList;

//顺序表基本接口实现


//顺序表的初始化
void SeqListInit(SeqList* ps, int capacity)
{
	//将ps所指向的SeqList类型结构体变量个个字段初始化
	//申请capacity大小的一段空间
	//size,记录元素个数

	//条件：
	//判断是否申请成功
	//所给容量不能小于等于0
	//ps指针不能为空，为空就不用处理了
	if (NULL == ps)
	{
		assert(0);
		return;  //跳出去
	}

	ps->capacity = capacity <= 0 ? 10 : capacity;
	ps->array = (DataType*)malloc(ps->capacity*sizeof(DataType));
	ps->size = 0;
}

//顺序表的销毁
void SeqListDestroy(SeqList* ps)
{
	if (ps)
	{
		free(ps->array);  //释放申请的空间
		ps->array = NULL; //指针置空
		ps->capacity = 0; //容量置0
		ps->size = 0;     //元素个数置0
	}
}

//扩容
void SeqListCheckCapacity(SeqList* ps)// 检查空间，如果满了，进行增容
{
	size_t newcapacity;
	assert(ps);
	if (ps->size == ps->capacity)
	{
		newcapacity = (ps->capacity == 0) ? 4 : ps->capacity * 2;//三目运算符
		ps->array = (DataType*)realloc(ps->array, sizeof(DataType)*newcapacity);
		ps->capacity = newcapacity;
	}
}

//尾插 O(1)
void SeqListPushBack(SeqList* ps, DataType data)
{
	if (NULL == ps)
	{
		assert(0);
		return;
    }
	//检测容量，考虑是否需要扩容
	SeqListCheckCapacity(ps);


	ps->array[ps->size] = data;
	ps->size++;
}

//尾删  O(1)
void SeqListPopBack(SeqList* ps)
{

	//ps指向的顺序表的结构体类型变量是否为空
	if (NULL == ps)
	{
		assert(0);
		return;
	}

	//顺序表为空:顺序表存在,只是顺序变中没有有效元素
	if (0 == ps->size)
	{
		return;
	}

	ps->size--;
}

//头插  O(N)
void SeqListPushFront(SeqList* ps, DataType data)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}
	//检测是否需要扩容
	SeqListCheckCapacity(ps);

	//插入元素
	//1.将顺序表中的所有元素往后挪一个位置，从后往前一个一个挪
	for (int i = ps->size - 1; i >= 0; i--)  //i:待挪位置的元素下标
	{
		ps->array[i + 1] = ps->array[i];//挪到后面（i->i+1）
	}
	//2.插入元素
	ps->array[0] = data;
	ps->size++;
}

//头删
void SeqListPopFront(SeqList* ps)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}

	//判断是否有元素
	if (0 == ps->size)
	{
		return;
	}

	//将0号位置之后的元素一次向前挪一个位置,直接覆盖就行
	for (int i = 1; i < ps->size; i++)
	{
		ps->array[i - 1] = ps->array[i];
	}
	ps->size--;
}

//任意位置的插入
void SeqListInsert(SeqList* ps, int pos, DataType data)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}
	//容量检测
	SeqListCheckCapacity(ps);

	//插入元素
	//1.将顺序表中pos位置开始的元素往后挪一个位置，从后往前一个一个挪
	for (int i = ps->size - 1; i >= pos; i--)  //i:待挪位置的元素下标
	{
		ps->array[i + 1] = ps->array[i];//挪到后面（i->i+1）
	}
	//2.插入元素
	ps->array[pos] = data;
	ps->size++;
}

//任意位置的删除
void SeqListErase(SeqList* ps, int pos)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}
	//从pos后一个位置开始，依次覆盖前面的元素
	for (int i = pos+1; i < ps->size; i++)
	{
		ps->array[i - 1] = ps->array[i];
	}
	ps->size--;
}

//在顺序表中查找值为data的元素，返回下标
int SeqListFind(SeqList* ps, DataType data)
{
	if (NULL == ps)
	{
		assert(0);
		return 0;
	}

	for (int i = 0; i < ps->size; i++)
	{
		if (data == ps->array[i])
		{
			return i;
		}
	}

	return -1;
}

//检测顺序表中是否为空
int SeqListEmpty(SeqList* ps)
{
	if (NULL == ps)
	{
		assert(0);
		return 0;
	}

	return ps->size == 0;
}

//将顺序表中的元素清空
void SeqListClear(SeqList* ps)
{
	if (NULL == ps)
	{
		assert(0);
		return;
	}

	ps->size = 0;
}
//打印顺序表
void PrintfSList(SeqList* ps)
{
	for (DataType i = 0; i < ps->size; i++)
	{
		printf("%d ", ps->array[i]);
	}
}
int main()
{
	SeqList  L;
	SeqListInit(&L, 10);
	//尾插
	SeqListPushBack(&L, 1);
	SeqListPushBack(&L, 2);
	SeqListPushBack(&L, 3);
	SeqListPushBack(&L, 4);
	SeqListPushBack(&L, 5);
	PrintfSList(&L);
	printf("\n");
	SeqListInsert(&L, 0, 15);
	PrintfSList(&L);

	system("pause");
	return 0;
}
#endif



#if 0
//4
//无头结点单链表基本操作
#include<iostream>
#include<assert.h>
#include<malloc.h>
#include<Windows.h>
using namespace std;
typedef int DateType;

typedef struct SLNode
{
	int data;//当前内容
	struct SLNode* next;//下一个位置
}SLNode;//重命名
//自己验证：按照上述方法定义结构体，加typedef和不加,SLNode的区别

/*
如果方法中需要修改头指针(L)的指向，就传递二级指针
如果不需要修改，传递一级指针
*/
//尾插/删
void SLPushBack(SLNode** head, DateType data);
void SLPopBack(SLNode** head);
//头插/删
void SLPushFront(SLNode** head, DateType data);
void SLPopFront(SLNode** head);
//在pos位置之后插入data
void SLInsertAfter(SLNode*  pos, int data);
//把pos位置的节点删除(有可能是第一个节点)
void SLErase(SLNode** head, SLNode* pos);
//获取链表节点个数
int SLSize(SLNode* head);
//在链表中找到值为data的节点
SLNode* SLFind(SLNode* head, int data);
//销毁链表
void SLDestroy(SLNode** head);
//打印当前链表(没有修改，只需要打印，传一级指针就行)
void PrintfSList(SLNode* head);
//测试函数
void TestSList1();
void TestSList();


//申请节点
SLNode* BuySLNode(DateType data)
{
	//申请一个SLNode结构体类型的newNode
	SLNode* newNode = (SLNode*)malloc(sizeof(SLNode));
	if (NULL == newNode)
	{
		printf("申请节点失败！\n");
		assert(newNode);
	}

	newNode->data = data; //把内容存下来
	newNode->next = NULL; //把下一个地址先置空
	return newNode;
}
//尾插
//head中的内容就是&L
//如果想要改变实参L的指向,*head结果就是L本身
//注意：空链表和链表不存在的区别
//空链表：链表已经存在,只不过链表中没有有效节点
//链表不存在：都没有头指针

//assert:一般用于针对程序的非法情况
//if判断：程序正常的一种可能性情况
void SLPushBack(SLNode** head, DateType data)
{
	//1.要先遍历到链表最后一个节点tail
	//  最后一个节点的特点,next为NULL
	//  借助一个临时指针tail,从链表的起始位置不断遍历(检测tail->next是否为空即可)
	//2.让最后一个节点的next域指向新节点
	// tail->next=newNode
	
	//链表是否存在
	assert(head);
	SLNode* newNode = BuySLNode(data);
	
	//链表是否为空链表(没有任何节点的链表)
	if (NULL == *head)
	{
		//第一个节点为空,第一个节点的插入方式
		*head = newNode;
	}
	else
	{
		//说明链表中有节点
		//尾插
		//1.先去找链表中最后一个节点(next为NULL)
		SLNode* tail = *head;
		while (tail->next)
		{
			//注意：tail++;(这种像顺序表的遍历方式(直接++)是错误的)
			tail = tail->next;
		}
		//2.将新节点连接在最后一个节点之后
		tail->next = newNode;
	}
}
//尾删
void SLPopBack(SLNode** head)
{
	//在删除时链表是什么样子？
	//1.空链表 L=NULL;不需要删除,直接返回；
	//2.链表中只有一个节点：L--->1--->NULL;将1节点删除,链表成为空链表 L=NULL;
	//3.链表中有多个节点：L--->1--->2--->3--->4--->5--->NULL;
	//while(cur->next)  cur=cur->next  找到最后一个节点(尾)
	//并且用prev保存cur的前一个节点
	//prev->next=cur->next; free(cur); 就行

	assert(head);
	
	//空链表
	if (NULL == *head)
		return;
	else if (NULL == (*head)->next)
	{
		//链表中只有一个节点
		free(*head);
		*head = NULL;
	}
	else
	{
		//有多个节点
		//借助cur先找到最后一个节点,并用prev保存cur的前一个节点
		SLNode* cur = *head;
		SLNode* prev = NULL;
		while (cur->next)
		{
			prev = cur;
			cur = cur->next;
		}
		prev->next = cur->next;
		free(cur);
	}
}
//头插
void SLPushFront(SLNode** head, DateType data)
{
	//1.空链表 L=NULL; 插入成功后：L--->1--->NULL;
	//2.非空 L--->1--->2--->3--->4--->NULL;
	//0先指向1;L再指向0;(顺序不能改变)  L--->0--->1--->2--->3--->4--->NULL;
	//newNode->next=*head;
	//*head=newNode;
	assert(head);

	SLNode* newNode = BuySLNode(data);
	newNode->next = *head;
	*head = newNode;
}
//头删
void SLPopFront(SLNode** head)
{
	//head--->4--->3--->2--->1--->NULL;
	//先连接head--->3-->2--->1--->NULL;
	//再删除第一个节点(4);


	//链表是否存在
	assert(head);
	//链表是否为空
	if (NULL == *head)
	{
		return;
	}
	else
	{
		//一个节点和多个节点都适用(SLPopBack就不行)
		//把需要删的先保存起来(head指向的就是需要删除的)
		SLNode* delNode = *head;
		*head = delNode->next;
		free(delNode);
	}
}
//在pos位置之后插入data
void SLInsertAfter(SLNode*  pos, int data)
{
	//参数检测
	if (NULL == pos)
	{
		return;
	}
	SLNode* newNode = NULL;
	newNode = BuySLNode(data);
	newNode->next = pos->next;
	pos->next = newNode;
}
//把pos位置之后的节点删除(第一个节点删不了)
void SLEraseAfter(SLNode** head, SLNode* pos)
{
	//pos如果不存在
	//pos是最后一个节点
	//先连接，再删节点
	SLNode* delNode = NULL;
	if (NULL == pos || NULL == pos->next)
	{
		return;
	}
	delNode = pos->next;
	pos->next = delNode->next;
	free(delNode);
}
//获取链表节点个数
//head--->1--->2--->3--->4--->NULL
int SLSize(SLNode* head)
{
	int count = 0;
	SLNode* cur = head;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return count;
}
//在链表中找到值为data的节点
SLNode* SLFind(SLNode* head, int data)
{
	SLNode* cur = head;
	while (cur)
	{
		if (data == cur->data)
		{
			return cur;
		}
		cur=cur->next;
	}
	return NULL;
}
//销毁链表
void SLDestroy(SLNode** head)
{
	assert(head);
	SLNode *cur = *head;
	//先连接，再删除
	//头删法
	while (cur)
	{
		*head = cur->next;
		free(cur);
		cur = *head;
	}
}
//打印当前链表
void PrintfSList(SLNode* head)
{
	SLNode* cur = head;
	while (cur)
	{
		printf("%d--->",cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}
SLNode* reverseList(SLNode* head) {
	SLNode *p;
	for (p = NULL; head; swap(head, p))
		swap(p, head->next);
	return p;
}

////////////////////////////////////////
//测试函数
void TestSList1()
{
	//L:空的链表
	SLNode* L = NULL;
	//尾插 1,2,3,4,5
	SLPushBack(&L, 1);
	SLPushBack(&L, 2);
	SLPushBack(&L, 3);
	SLPushBack(&L, 4);
	SLPushBack(&L, 5);
	PrintfSList(L);

	//反转链表,原地算法
	//PrintfSList(reverseList(L));
	
	//SLInsertAfter(L, 8);
	//PrintfSList(L);

    //尾删
	//SLPopBack(&L);
	//PrintfSList(L);
	
	//头删
	//SLPopFront(&L);
	//PrintfSList(L);

	////任意位置后插入
	//SLInsertAfter(SLFind(L, 3), 6);
	//PrintfSList(L);

	////打印节点个数
	//printf("%d\n",SLSize(L));

	////删除pos之后的节点
	//SLEraseAfter(&L,SLFind(L, 3));
	//PrintfSList(L);

	////销毁
	//SLDestroy(&L);
	//PrintfSList(L);

}
//测试函数
void TestSList()
{
	TestSList1();
}
int main()
{
	TestSList();
	system("pause");
	return 0;
}

#endif

#if 0
//5
//带头结点双向循环链表
//可以不用二级指针，因为头结点位置不会改变
//所有的操作都是基于头结点之后去操作的
#include<iostream>
#include<assert.h>
#include<malloc.h>

typedef int DataType;

typedef struct DListNode
{
	DataType data;
	struct DListNode *next;
	struct DListNode *prev;
}DListNode;

//申请节点空间
DListNode *BuyDListNode(DataType data);
//创建空链表，含头结点
DListNode* CreatDList();
//尾插/删
void DListPushBack(DListNode* pHead, DataType data);
void DListPopBack(DListNode* pHead);
//头插/删
void DListPushFront(DListNode* pHead, DataType data);
void DListPopFront(DListNode*pHead);
//在pos位置插入新节点(往pos位置前面插入)
void DListInsert(DListNode* pos, DataType data);
//删除pos位置节点
void DListErase(DListNode* pos);
//查找Data数据节点
DListNode* DListFind(DListNode* pHead, DataType data);
//销毁链表
void DListDestroy(DListNode* pHead);


//申请节点空间
DListNode *BuyDListNode(DataType data)
{
	DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
	if (NULL == newNode)
	{
		assert(0);
		return NULL;
	}
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}
//申请头结点
//带头结点的双向循环链表
//空链表也有头结点，且自己指自己
DListNode* CreatDList()
{
	DListNode* head = BuyDListNode(0);
	head->next = head;
	head->prev = head;
	return head;
}
//尾插
void DListPushBack(DListNode* pHead, DataType data)
{
	if (NULL == pHead)
	{
		return ;
	}
	//申请节点
	DListNode* newNode = BuyDListNode(data);

	//先连接再断开
	newNode->prev = pHead->prev;//把pHead->prev(链表中的最后一个节点)给newNode->prev
	newNode->next = pHead;
	pHead->prev->next = newNode;
	pHead->prev = newNode;
}
//尾删
void DListPopBack(DListNode* pHead)
{ 
	assert(pHead);//assert是一个调试宏，在debug底下有效，release底下不存在
	if (NULL == pHead)
	{
		assert(0);
		return;
	}
	//检测是否为空链表
	if (pHead->next == pHead)
	{
		return;
	}
	//先连接再删除
	DListNode *pos = pHead->prev;

	pHead->prev = pos->prev;
	pos->prev->next = pHead;
	free(pos);

}
//头插
void DListPushFront(DListNode* pHead, DataType data)
{
	if (NULL == pHead)
	{
		return;
	}
	//调用pos位置的插入
	DListInsert(pHead->next, data);
}
//头删
void DListPopFront(DListNode* pHead)
{
	if (NULL == pHead)
	{
		return;
	}
	//调用pos位置的删除
	DListErase(pHead->next);
}
//在pos位置插入新节点(往pos位置前面插入)
void DListInsert(DListNode* pos, DataType data)
{
	DListNode* newNode = BuyDListNode(data);
	//先连接再断开
	newNode->prev = pos->prev;
	newNode->next = pos;
	newNode->prev->next = newNode;
	pos->prev = newNode;
}
//删除pos位置节点
void DListErase(DListNode* pos)
{
	if (NULL == pos)
	{
		return;
	}
	//先连接，再删除
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
}
//查找Data数据节点
DListNode* DListFind(DListNode* pHead, DataType data)
{
	//检测链表是否存在
	if (NULL == pHead)
	{
		return NULL;
	}
	DListNode* cur = pHead->next;
	while (cur != pHead)
	{
		if (cur->data== data)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
//销毁链表
//最后要改变头指针使其指向NULL，所以必须传递二级指针
void DListDestroy(DListNode** pHead)
{
	DListNode* cur = NULL;
	//保证链表存在
	if (NULL == pHead)
	{
		return;
	}
	//删除有效节点
	cur = (*pHead)->next;
	while (cur != *pHead)
	{
		(*pHead)->next = cur->next;
		free(cur);
		cur = (*pHead)->next;
	}
	free(*pHead);
	*pHead = NULL;
}
//打印双向循环链表
void PrintfDList(DListNode* pHead)
{
	if (NULL == pHead)
	{
		return;
	}
	DListNode *cur = pHead->next;
	printf("pHead-->");
	while (cur != pHead)
	{
		printf("%d-->", cur->data);
		cur = cur->next;
	}
	printf("pHead\n");
}
//测试函数
void Test1()
{
	//申请头结点
	DListNode* head = CreatDList();
	//尾插
	DListPushBack(head, 1);
	DListPushBack(head, 2);
	DListPushBack(head, 3);
	DListPushBack(head, 4);
	DListPushBack(head, 5);
	PrintfDList(head);

	//销毁链表
	DListDestroy(&head);
}
//测试函数
void Test()
{
	Test1();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
#endif

#if 0
//6
//栈结构实现
//静态栈-->栈中存储元素个数受限
//实际应用中很少用静态栈，因为元素受限
//在笔试中需要用到栈而没有结构时，临时实现栈结构-->建议：实现静态的栈(容易实现)
#include<iostream>
#include<assert.h>
#include<malloc.h>

typedef int DataType;
#define MAX_SIZE 100

typedef struct Stack
{
	DataType* array;
	int capacity;  //容量
	int size;
}Stack;

//栈的初始化
void StackInit(Stack* ps);
//容量检测
void CheckCapacity(Stack* ps);
//入栈
void StackPush(Stack* ps);
//出栈
void StackPop(Stack* ps);
//获取栈顶元素
DataType StackTop(Stack* ps);
//获取栈中有效元素个数
DataType StackSize(Stack* ps);
//检测栈是否为空
DataType StackEmpty(Stack* ps);
//销毁
void StackDestroy(Stack* ps);


//栈的初始化
void StackInit(Stack* ps)
{
	assert(ps);
	ps->array = (DataType*)malloc(sizeof(DataType) * 10);
	ps->capacity = 10;
	ps->size = 0;
}
//检测容量
void CheckCapacity(Stack* ps)
{
	//1.申请新空间
	//2.拷贝元素
	//3.释放旧空间
	if (ps->size >= ps->capacity)
	{
		//申请新空间
		int newCapacity = ps->capacity * 2;
		DataType* temp = (DataType*)malloc(sizeof(DataType)*newCapacity);

		if (temp)
		{
			//拷贝元素
			//memcpy(temp,ps->array,sizeof(DataType)*ps->capacity);
			for (int i = 0; i < ps->size; i++)
			{
				temp[i] = ps->array[i];
			}
			//释放旧空间
			free(ps->array);

			ps->array = temp;
		}
	}
}
//入栈
void StackPush(Stack* ps,DataType data)
{
	assert(ps);
	//检测容量是否够
	CheckCapacity(ps);

	//插入元素
	ps->array[ps->size] = data;
	ps->size++;
}
//出栈
void StackPop(Stack* ps)
{
	if (StackEmpty(ps))
	{
		return;
	}
	ps->size--;
}
//获取栈顶元素
DataType StackTop(Stack* ps)
{
	assert(ps);
	return ps->array[ps->size-1];
}
//获取栈中有效元素个数
DataType StackSize(Stack* ps)
{
	assert(ps);
	return ps->size;
}
//检测栈是否为空
DataType StackEmpty(Stack* ps)
{
	assert(ps);
	return 0 == ps->size;
}
//销毁
void StackDestroy(Stack* ps)
{
	assert(ps);
	free(ps);
	ps->capacity=0;
	ps->size = 0;
}



//测试函数
void Test1()
{
	Stack s;
	//栈的初始化
	StackInit(&s);
	//入栈
	StackPush(&s, 1);
	StackPush(&s, 2);
	StackPush(&s, 3);
	StackPush(&s, 4);
	StackPush(&s, 5);
	printf("%d\n",StackTop(&s));
	printf("%d\n",StackSize(&s));
	StackPop(&s);
	//销毁
	StackDestroy(&s);
}
//测试函数
void Test()
{
	Test1();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
#endif


#if 0
//7
//队列结构实现
#include<iostream>
#include<assert.h>
#include<malloc.h>

typedef int QDataType;

//队列底层使用链表中的节点结构
typedef struct QNode
{
	struct QNode* next;
	QDataType val;
}QNode;

struct Queue
{
	QNode* head;
	QNode* rear;
	int size;
};
//申请节点
QNode* BuyQNode(int val);
//队列的初始化
void QueueInit(Queue* q);
//入队列
void QueuePush(Queue* q);
//出队列
void QueuePop(Queue* q);
//获取队列中有效元素个数
QDataType QueueSize(Queue* q);
//检测队列是否为空
QDataType QueueEmpty(Queue* q);
//获取队头元素
QDataType QueueFront(Queue* q);
//获取队尾元素
QDataType QueueBack(Queue* q);
//销毁队列
void QueueDestroy(Queue* q);


//申请节点
QNode* BuyQNode(int val)
{
	QNode* newNode = (QNode*)malloc(sizeof(QNode));
	if (NULL == newNode)
	{
		assert(0);
		return NULL;
	}
	newNode->val = val;
	newNode->next = NULL;
	return newNode;
}
//队列的初始化
//加个头结点
void QueueInit(Queue* q)
{
	assert(q);
	q->head = BuyQNode(0);
	q->size = 0;
	q->rear = q->head;
}
//入队列
void QueuePush(Queue* q, QDataType val)
{
	assert(q);
	QNode* newNode = BuyQNode(val);
	q->rear->next = newNode;
	q->rear = newNode;
	q->size++;
}
//出队列
void QueuePop(Queue* q)
{
	QNode* pDelNode = NULL;
	if (QueueEmpty(q))
	{
		return;
	}
	pDelNode = q->head->next;
	q->head->next = pDelNode->next;
	free(pDelNode);
	q->size--;
	if (0 == q->size)
	{
		q->rear = q->head;
	}
}
//获取队列中有效元素个数
int QueueSize(Queue* q)
{
	assert(q);
	return q->size;
}
//检测队列是否为空
int QueueEmpty(Queue* q)
{
	assert(q);
	return 0 == q->size;
}
//获取队头元素
QDataType QueueFront(Queue* q)
{
	assert(!QueueEmpty(q));
	return q->head->next->val;
}
//获取队尾元素
QDataType QueueBack(Queue* q)
{
	assert(!QueueEmpty(q));
	return q->rear->val;
}
//销毁队列
void QueueDestroy(Queue* q)
{
	assert(q);
	QNode* cur =q->head->next;
	while(cur)
	{
		q->head->next=cur->next;
		free(cur);
		cur = q->head;
	}
	free(q);
	q = NULL;
}


//测试函数
void Test1()
{
	Queue q;
	//初始化
	QueueInit(&q);
	//入队列
	QueuePush(&q, 1);
	QueuePush(&q, 2);
	QueuePush(&q, 3);
	QueuePush(&q, 4);
	QueuePush(&q, 5);
	
	printf("size=%d\n", QueueSize(&q));
	printf("Front=%d\n", QueueFront(&q));
	printf("Back=%d\n", QueueBack(&q));
	
	
	////出队列
	//void QueuePop(Queue* q);
	////获取队列中有效元素个数
	//QDataType QueueSize(Queue* q);
	////检测队列是否为空
	//QDataType QueueEmpty(Queue* q);
	////获取队头元素
	//QDataType QueueFront(Queue* q);
	////获取队尾元素
	//QDataType QueueBack(Queue* q);
}
//测试函数
void Test()
{
	Test1();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
#endif


#if 0
//8
//2020.3.23
//堆的实现
#include<iostream>
#include<assert.h>
#include<malloc.h>

typedef int HPDataType;

int Less(int left, int right);
int Greater(int left, int right);
//pCompare:是一个函数指针-->表示返回int 参数为两个整型参数的一系列函数
//int (*pCompare(int left,int right));

//pCompare:函数指针类型
typedef int(*PCOM)(int left, int right);
typedef struct Heap
{
	HPDataType* array;
	int capacity;
	int size;
	PCOM Compare; //到时候让Compare指向Less或者Greater,只要函数两个参数都是整型，都可以用Compare接收。
}Heap;

//堆的创建
void HeapCreate(Heap* hp, HPDataType* a, int size, PCOM compare);
//堆的销毁
void HeapDestory(Heap* hp);
//堆的插入
void HeapPush(Heap*  hp, HPDataType data);
//堆的删除
void HeapPop(Heap* hp);
//取堆顶元素
HPDataType HeapTop(Heap* hp);
//堆的数据个数
int HeapSize(Heap* hp);
//堆的判空
int HeapEmpty(Heap* hp);
//堆的销毁
void HeapDestroy(Heap* hp);
//容量检测
void CheckCapacity(Heap* hp);

//对数组进行堆排序
void HeapSort(int* a, int size);


int Less(int left, int right)
{
	return left < right;
}
int Greater(int left, int right)
{
	return left > right;
}
//元素交换
void Swap(HPDataType* left, HPDataType* right)
{
	*left ^= *right;
	*right ^= *left;
	*left ^= *right;
}
//向上调整
void AdjustUP(Heap* hp,int child)
{
	//把新插入的孩子节点调整到合适的位置
	int parent = (child - 1) >> 1;

	while (child)
	{
		if (hp->Compare(hp->array[child] ,hp->array[parent]))
		{
			Swap(&hp->array[child], &hp->array[parent]);
			//小的元素往上移动，可能会导致上层不满足堆的性质
			//需要继续往上调整
			child = parent;
			parent = (child - 1) >> 1;
		}
		else
		{
			return;
		}
	}
}
//向下调整(只有堆顶元素不满足堆的结构)
//假设：创建的是小堆
//parent:需要调整的元素在堆结构中的下标(从0开始)
//    将parent和孩子中的较小者进行比较
//       是-->parent满足堆的特性
//       否-->将parent和较小的孩子进行交换
//                      交换之后底下的子数可能会不满足堆的性质，故需要继续向下调整
void AdjustDown(Heap* hp, int parent)
{
	//child作用：标记parent的较小孩子
	//默认标记左孩子。因为完全二叉树中一个节点可能有左没有右。
	int child = parent * 2 + 1;

	//while循环条件：保证左孩子存在，如果左孩子不存在，右孩子肯定也不存在
	while (child<hp->size)
	{
		//先保证右孩子存在，再找两个孩子中较小的孩子，防止越界
		//如果右孩子＜左孩子，child++
		if (child+1< hp->size&&hp->Compare(hp->array[child + 1] ,hp->array[child]))
		{ 
			child++;
		}

		//检测parent是否比较小的孩子child小
		if (hp->Compare(hp->array[child] ,hp->array[parent]))
		{
			Swap(&hp->array[child], &hp->array[parent]);

			//parent大的元素往下移动，可能会导致子树不满足堆的性质
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			//不用调整了
			return;
		}
	}
}
void CheckCapacity(Heap* hp)
{
	assert(hp);
	if (hp->size >= hp->capacity)
	{
		//需要扩容
		//1.申请新空间
		int newCapacity = hp->size * 2;
		HPDataType* temp = (HPDataType*)malloc(sizeof(HPDataType)*newCapacity);
		if (NULL == temp)
		{
			return;
		}
		//拷贝元素
		for (int i = 0; i < hp->size;i++)
		{
			temp[i] = hp->array[i];
		}
		//memcpy(temp,hp->array,hp->size*sizeof(HPDataType));
		
		//3.释放旧空间
		free(hp->array);
		hp->array = temp;
		hp->capacity = newCapacity;
	}
}
//堆的创建
void HeapCreate(Heap* hp, HPDataType* arr, int size, PCOM compare)
{
	assert(hp);
	//1.先将arr中的元素放到堆的结构中
	//初始化堆的结构
   	hp->array = (HPDataType*)malloc(sizeof(HPDataType)*size);
	if (NULL == hp->array)
	{
		assert(0);
		return;
	}
	hp->capacity = size;
	memcpy(hp->array, arr, sizeof(HPDataType)*size);
	hp->size = size;
	hp->Compare = compare;

	//2.对堆中的元素进行调整
	//从下往上，从第一个非叶子节点开始调整
	for (int root = (size - 2) >> 1; root >= 0; root--)
	{
		AdjustDown(hp, root);
	}
}
//堆的销毁
void HeapDestory(Heap* hp)
{

}
//堆的插入
void HeapPush(Heap*  hp, HPDataType data)
{
	//1.把元素插入到最后
	//2.向上调整一遍
	assert(hp);
	CheckCapacity(hp);
	hp->array[hp->size++] = data;
	AdjustUP(hp, hp->size - 1);

}
//堆的删除(删堆顶元素）
void HeapPop(Heap* hp)
{
	//1.把堆顶元素和最后一个元素进行交换
	//2.size-1
	//3.从堆顶进行向下调整
	assert(hp);
	if (HeapEmpty(hp))
	{
		return;
	}
	Swap(&hp->array[0], &hp->array[hp->size - 1]);
	hp->size--;
	AdjustDown(hp, 0);
}
//取堆顶元素
HPDataType HeapTop(Heap* hp)
{
	assert(hp&&!HeapEmpty(hp));
	return hp->array[0];

}
//堆的数据个数
int HeapSize(Heap* hp)
{
	assert(hp);
	return hp->size;
}
//堆的判空
int HeapEmpty(Heap* hp)
{
	assert(hp);
	return 0 == hp->size;
}
///////////////////////////////////////////
//对数组进行堆排序
//降序建小堆，升序建大堆
void HeapAdjust(int* array, int size,int parent)
{
	//小堆，降序，向下调整
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size&&array[child + 1] < array[child])
		{
			child++;
		}
		if (array[child] < array[parent])
		{
			int temp = array[child];
			array[child] = array[parent];
			array[parent] = temp;

			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			return;
		}
	}
}
void HeapSort(int* array, int size)
{
	//建堆
	for (int root = (size - 2) >> 1; root >= 0; root--)
	{
		HeapAdjust(array, size, root);
	}
	//采用堆删除的思想来进行排序
	int end = size - 1;
	while (end)
	{
		int temp = array[0];
		array[0] = array[end];
		array[end] = temp;
		
		HeapAdjust(array, end, 0);
		end--;
	}
}
///////////////////////////////////////////
//堆的销毁
void HeapDestroy(Heap* hp)
{
	assert(hp);
	if (hp->array)
	{
		free(hp->array);
		hp->array = NULL;
		hp->capacity = 0;
		hp->size = 0;
	}
}


//测试函数
void Test1()
{
	int array[] = { 5, 3, 8, 4, 2, 7, 6, 1, 0 };
	//HeapSort(array, sizeof(array)/sizeof(array[0]));
	Heap hp;
	HeapCreate(&hp, array, sizeof(array) / sizeof(array[0]),Greater);
	printf("size=%d\n", HeapSize(&hp));
	printf("Top=%d\n", HeapTop(&hp));
}
//测试函数
void Test()
{
	Test1();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
#endif

#if 0
//9
//2020.3.28
//二叉树的实现与基本操作
#include<iostream>
#include<assert.h>
#include<malloc.h>
#include<queue>
using namespace std;

typedef int BTDataType;

typedef struct BinTreeNode
{
	BTDataType val;
	struct BinTreeNode* pLeft;
	struct BinTreeNode* pRight;
}BTNode;

BTNode* BuyBinTreeNode(BTDataType val)
{
	BTNode* pNewNode = (BTNode*)malloc(sizeof(BTNode));
	if (NULL == pNewNode)
	{
		assert(0);
		return NULL;
	}
	pNewNode->pLeft = NULL;
	pNewNode->pRight = NULL;
	pNewNode->val = val;
	return pNewNode;
}
//BTNode* CreatBinTree()
//{
//	//            1
//	//          /   \ 
//	//         2     4
//	//       /     /   \
//	//      3     5     6
//	BTNode* node1 = BuyBinTreeNode(1);
//	BTNode* node2 = BuyBinTreeNode(2);
//	BTNode* node3 = BuyBinTreeNode(3);
//	BTNode* node4 = BuyBinTreeNode(4);
//	BTNode* node5 = BuyBinTreeNode(5);
//	BTNode* node6 = BuyBinTreeNode(6);
//	//BTNode* node7 = BuyBinTreeNode(7);
//	//BTNode* node8 = BuyBinTreeNode(8);
//	//BTNode* node9 = BuyBinTreeNode(9);
//
//	BTNode* pRoot = node1;
//	node1->pLeft = node2;
//	node2->pLeft = node3;
//	node1->pRight = node4;
//	node4->pLeft = node5;
//	node4->pRight = node6;
//	//node3->pRight = node7;
//	//node5->pRight = node8;
//	//node8->pRight = node9;
//	return pRoot;
//
//}


//前序遍历
void PreOrder(BTNode* pRoot);
//中序遍历
void InOrder(BTNode* pRoot);
//后序遍历
void PostOrder(BTNode* pRoot);
//层序遍历
void LevelOrder(BTNode *pRoot);
//判断是否为完全二叉树
bool isCBT(BTNode* pRoot);
//获取二叉树中节点个数
int GetNodeCount(BTNode* pRoot);
//获取叶子节点个数
int GetLeafCount();
//获取第K层节点个数
int GetKLevelCount();
//获取二叉树高度
int GetHeight();
//返回X元素在树中所对应的节点
BTNode* Find(BTNode* pRoot, BTDataType x);
//获取pNode的双亲
BTNode* FindParent(BTNode* pRoot, BTNode* pNode);
//二叉树的销毁
void TreeDestroy(BTNode** pRoot);
//构建二叉树   invalid:NULL节点的标记符号
BTNode* CreateBinTree(int * array, int size, int index, BTDataType invalid);









//构建二叉树   invalid:NULL节点标记
BTNode* _CreateBinTree(int * array, int size, int* index, BTDataType invalid)
{
	BTNode* pRoot = NULL;
	if (*index < size&&array[*index] != invalid)
	{
		//创建根节点
		pRoot = BuyBinTreeNode(array[*index]);

		//创建根节点的左子树
		++(*index);
		pRoot->pLeft = _CreateBinTree(array, size, index, invalid);

		//递归创建根节点的右子树
		++(*index);
		pRoot->pRight = _CreateBinTree(array, size, index, invalid);
	}
	return pRoot;
}
BTNode* CreateBinTree(int * array, int size, BTDataType invalid)
{
	int index = 0;
	return _CreateBinTree(array, size, &index, invalid);
}

//先序遍历
void PreOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		printf("%d ", pRoot->val);
		PreOrder(pRoot->pLeft);
		PreOrder(pRoot->pRight);
	}
}
//中序遍历
void InOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		InOrder(pRoot->pLeft);
		printf("%d ", pRoot->val);
		InOrder(pRoot->pRight);
	}
}
//后序遍历
void PostOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		PostOrder(pRoot->pLeft);
		PostOrder(pRoot->pRight);
		printf("%d ", pRoot->val);

	}
}
//层序遍历
void LevelOrder(BTNode *pRoot)
{
	queue<BTNode*> q;
	if (pRoot == NULL)
	{
		return;
	}
	q.push(pRoot);

	while (!q.empty())
	{
		BTNode* front = q.front();
		q.pop();

		if (front->pLeft) q.push(front->pLeft);
		if (front->pRight) q.push(front->pRight);
		cout<<front->val<<" ";
	}
}

//判断是否为完全二叉树
bool isCBT(BTNode* pRoot)//判断以pRoot为头节点的二叉树是否为完全二叉树
{
	assert(pRoot);
	if (pRoot == NULL)
		return true;
	
	queue < BTNode* >q;//通过队列q实现二叉树的层次遍历，通过层次遍历来判断是否为完全二叉树
	q.push(pRoot);//加入头节点
	
	bool leaf = false;//leaf变量用来标记一个状态是否发生（只要当前节点的左孩子和右孩子都为空或者左孩子不为空，右孩子为空时，这个状态就发生，
	                  //只要发生了这个状态，以后访问到的节点必须都是叶节点）
	
	while (!q.empty())
	{
		BTNode* p = q.front();
		q.pop();
		if ((leaf && (p->pLeft != NULL || p->pRight != NULL)) || (p->pLeft == NULL&&p->pRight != NULL))//这些判断条件是所有的不满足是完全二叉树的条件。条件一（第二个||前面的条件）：上述的状态已经发生，但是当前访问到的节点不是叶节点（有左孩子或者右孩子）。条件二：当前节点有右孩子，没有左孩子
			return false;
		if (p->pLeft != NULL)//左孩子不为空，加入到队列中去
			q.push(p->pLeft);
		if (p->pRight != NULL)//右孩子不为空，加入到队列中去
			q.push(p->pRight);
		if ((p->pLeft != NULL&&p->pRight == NULL) || (p->pLeft == NULL&&p->pRight == NULL))//这个if语句就是判断状态是否要发生
			leaf = true;
	}
	return true;
}
//获取二叉树中节点个数
//int count=0;
//int GetNodeCount(BTNode* pRoot)
//{   
//	
//	if (pRoot)
//	{
//		::count++;
//		GetNodeCount(pRoot->pLeft);
//		GetNodeCount(pRoot->pRight);
//	}
//	return ::count;
//}
int GetNodeCount(BTNode* pRoot)
{
	if (NULL==pRoot)
	{
		return 0;
	}
	return 1+GetNodeCount(pRoot->pLeft)+
		   GetNodeCount(pRoot->pRight);
}
//获取叶子节点个数
int GetLeafCount(BTNode* pRoot)
{
	if (NULL == pRoot)
	{
		return 0;
	}
	if (NULL == pRoot->pLeft&&NULL == pRoot->pRight)
	{
		return 1;
	}
	return GetLeafCount(pRoot->pLeft)+GetLeafCount(pRoot->pRight);
}
//获取第K层节点个数
int GetKLevelCount(BTNode* pRoot,int k)
{
	if (NULL == pRoot || k < 1)
	{
		return 0;
	}
	if (1 == k)
	{
		return 1;
	}
	//int left=GetKLevelCount(pRoot->pLeft, k - 1);
	//int right=GetKLevelCount(pRoot->pRight, k - 1);
	//return left+right;
	return GetKLevelCount(pRoot->pLeft, k - 1) + GetKLevelCount(pRoot->pRight, k - 1);
}
//获取二叉树高度
int GetHeight(BTNode* pRoot)
{
	if (NULL == pRoot)
	{
		return 0;
	}
	int leftHeight = GetHeight(pRoot->pLeft);
	int rightHeight = GetHeight(pRoot->pRight);
	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}
//返回X元素在树中所对应的节点
BTNode* Find(BTNode* pRoot, BTDataType x)
{
	BTNode* pNode = NULL;
	if (NULL == pRoot)
	{
		return NULL;
	}
	if (pRoot->val == x)
	{
		return pRoot;
	}
	//Find(pRoot->pLeft, x);
	//Find(pRoot->pRight, x);
	if ((pNode = Find(pRoot->pLeft, x)) || (pNode = Find(pRoot->pRight, x)))
	{
		return pNode;
	}
	return NULL;
}
//获取pNode的双亲
BTNode* GetParent(BTNode* pRoot, BTNode* pNode)
{
	BTNode* pParent = NULL;
	if (NULL == pRoot || NULL == pNode || pNode == pRoot)
	{
		return NULL;
	}
	if (pRoot->pLeft == pNode || pRoot->pRight == pNode)
	{
		return pRoot;
	}
	//pParent = GetParent(pRoot->pLeft, pNode);
	//pParent = GetParent(pRoot->pRight, pNode);
	//if (NULL != pParent)
	//{
	//	return pParent;
	//}
	if ((pParent = GetParent(pRoot->pLeft, pNode)) || (pParent = GetParent(pRoot->pRight, pNode)))
	{
		return pParent;
	}
	return NULL;
}
//二叉树的销毁
void DestroyNode(BTNode* node)
{
     free(node);
     return;
 }

void TreeDestroy(BTNode** pRoot)
 {
	assert(pRoot);
	if (*pRoot == NULL)
	{
		//空树
		return;
    }
	TreeDestroy(&((*pRoot)->pLeft));
	TreeDestroy(&((*pRoot)->pRight));
	DestroyNode(*pRoot);
	*pRoot = NULL;
	return;
 }

//测试函数
void Test1()
{
	int array[] = { 1, 2, 3, -1, -1, -1, 4, 5, -1, -1, 6 };
	BTNode* pRoot = CreateBinTree(array, sizeof(array) / sizeof(array[0]), -1);
	
	cout << "先序遍历为： "; 
	PreOrder(pRoot);
	cout << endl;

	cout << "中序遍历为： ";
	InOrder(pRoot);
	cout << endl;

	cout << "后序遍历为:  ";
	PostOrder(pRoot);
	cout << endl;

	cout << "层序遍历为:  ";
	LevelOrder(pRoot);
	cout << endl;

	//判断是否为完全二叉树
	if (isCBT(pRoot))//判断以pRoot为头节点的二叉树是否为完全二叉树
	{
		cout << "is CBT" << endl;
	}
	else
	{
		cout << "no is CBT" << endl;
	}

	//获取节点个数
	cout << "节点个数为:  ";
	cout<<GetNodeCount(pRoot)<<endl;
	
	//获取叶子节点
	cout << "叶子节点数为:";
	cout<<GetLeafCount(pRoot)<<endl;

	//高度
	cout << "二叉树高度为:";
	cout << GetHeight(pRoot)<<endl;

	//第K层节点个数
	cout << "第3层节点个数为:";
	cout<<GetKLevelCount(pRoot, 3)<<endl;

	//返回X元素在树中所对应的节点
	if (Find(pRoot, 3))
	{
		cout << "节点找到了!" <<endl;
	}
	else
	{
		cout << "节点没找到!" << endl;
	}
	BTNode* pNode = Find(pRoot, 3);
	BTNode* pParent = GetParent(pRoot, Find(pRoot, 3));
	//找双亲
	if (pParent)
	{
		cout << "双亲is "<<pParent->val << endl;
	}
	else
	{
		cout << "双亲没找到!" << endl;
	}
	//销毁
	TreeDestroy(&pRoot);
}
//测试函数
void Test()
{
	Test1();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
#endif

#if 0
//10
//2020.4.1
//排序
#include<iostream>
#include<assert.h>
#include<malloc.h>
#include<queue>
#include<stack>
using namespace std;

// 插入排序
void InsertSort(int* a, int n);
// 希尔排序
void ShellSort(int* a, int n);
// 选择排序
void SelectSort(int* a, int n);
// 堆排序
void AdjustDown(int* a, int n, int root);
void HeapSort(int* a, int n);
// 冒泡排序
void BubbleSort(int* a, int n);
// 快速排序递归实现
// 快速排序hoare版本
int PartSort1(int* a, int left, int right);
// 快速排序挖坑法
int PartSort2(int* a, int left, int right);
// 快速排序前后指针法
int PartSort3(int* a, int left, int right);
void QuickSort(int* a, int left, int right);
// 快速排序 非递归实现
void QuickSortNonR(int* a, int size);
// 归并排序递归实现
void MergeSort(int* a, int n);
// 归并排序非递归实现
void MergeSortNonR(int* a, int n);
// 计数排序
void CountSort(int* a, int n);





//void Swap(int* a, int* b)
//{
//	int temp=*a;
//	*a = *b;
//	*b = temp;
//}


//1.插入排序
//应用场景:数据量小,接近有序。
//1.1直接插入排序
//时间复杂度:O(n^2)
//空间复杂度:O(1)
void InsertSort(int* array, int size)
{
	for (int i = 1; i < size; i++)
	{
		int key = array[i];
		int end = i - 1;
		//找位置
		while (end >= 0 && key < array[end])
		{
			array[end + 1] = array[end];
			end--;
		}
		//插入数据
		array[end + 1] = key;
	}
}
//1.2希尔排序 
//当数据量大,且杂乱
//先按照某一步长分组，组内进行插入排序，折半减少步长，直至为1
//故三层循环 最外层为步长。
//时间复杂度:O(N^1.3-N^2）
//空间复杂度:O(1)
void ShellSort(int* array, int size)
{
	int gap = size;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = gap; i < size; i++)
		{
			int key = array[i];
			int end = i - gap;
			//找位置
			while (end >= 0 && key < array[end])
			{
				array[end + gap] = array[end];
				end-=gap;
			}
			//插入数据
			array[end + gap] = key;
		}
	}
}
//2.选择排序
//2.1选择排序
//时间复杂度:O(N^2)
//空间复杂度:O(1)
void SelectSort(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		int minPos = i;
		for (int j = i ; j < size; j++)
		{
			if (array[j] < array[minPos])
			{
				minPos = j;
			}
		}
		swap(array[i], array[minPos]);
	}
}
//2.2堆排序
//升序建大堆，降序建小堆
//时间复杂度:O(NlogN)
//空间复杂度:O(1)
//小堆
void HeapSort(int* array, int size)
{
	//建堆
	//从第一个非叶子节点开始倒退调整
	for (int root = (size - 2) >> 1; root >= 0; root--)
	{
		AdjustDown(array, size, root);
	}
	//采用堆删除的思想来进行排序
	int end = size - 1;
	while (end)
	{
		int temp = array[0];
		array[0] = array[end];
		array[end] = temp;

		AdjustDown(array, end, 0);
		end--;
	}
}
void AdjustDown(int* array, int size, int parent)
{
	//小堆，降序，向下调整
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size&&array[child + 1] < array[child])
		{
			child++;
		}
		if (array[child] < array[parent])
		{
			int temp = array[child];
			array[child] = array[parent];
			array[parent] = temp;

			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			return;
		}
	}
}
//3.交换排序
//3.1冒泡排序
//时间复杂度:O(n^2)
//空间复杂度:O(1)
//升序
void BubbleSort(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
        int flag = 1;
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (array[j]>array[j+1])
			{
				swap(array[j], array[j+1]);
				flag = 0;
			}
		}
		if (flag) break;
	}
}
//3.2快速排序
//时间复杂度:O(N*logN)
//时间复杂度:O(logN)--O(N)
//不稳定排序
//快速排序递归实现
//快速排序hoare版本(前后交换)
int GetIndexOfMid(int* array, int left, int right)
{
	int a = array[left];
	int b = array[(left + right) / 2];
	int c = array[right];
	if (a > b)
	{
		if (b > c)
		{
			return (left + right) / 2;
		}
		if (a<c)
		{
			return left;
		}
		else
		{
			return right;
		}
	}
	if (a<b)
	{
		if (a > c)
		{
			return left;
		}
		if (b<c)
		{
			return (left + right) / 2;
		}
		else
		{
			return right;
		}
	}
	return 0;
	//return a > b ? (b > c ? b : a < c ? a : c) : (a > c ? a : b < c ? b : c);
}
int PartSort1(int* array, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int key = array[end];

	while (begin < end)
	{
		//让begin从前往后找，找比基准值大的元素，找到之后停止
		while (begin<end&&array[begin] <= key)
			begin++;
		//让end从后往前找，找到比基准值小的元素，找到之后停止
		while (begin<end&&array[end] >= key)
			end--;

		if (begin < end)
		{
			swap(array[begin], array[end]);
		}
	}
	
	if (begin!=right-1)
	swap(array[begin], array[right-1]);
	
	return begin; //新div
}
// 快速排序挖坑法
int PartSort2(int* array, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int key = array[begin]; //array[begin]就是第一个坑

	while (begin < end)
	{
		// 从右向左找小于key的数来填array[begin]
		while (begin < end && array[end] >= key)
			end--;
		if (begin < end)
		{
			array[begin] = array[end]; //将array[end]填到array[begin]中，array[end]就形成了一个新的坑
			begin++;
		}

		// 从左向右找大于或等于key的数来填array[end]
		while (begin < end && array[begin] <= key)
			begin++;
		if (begin < end)
		{
			array[end] = array[begin]; //将array[begin]填到array[end]中，array[begin]就形成了一个新的坑
			end--;
		}
	}
	//退出时，begin等于end,将key填到这个坑中。
	array[begin] = key;

	return begin;//返回新的div
}
// 快速排序前后指针法
int PartSort3(int* array, int left, int right)
{
	int cur = 0;
	int prev = cur - 1;
	int key;
	int mid = GetIndexOfMid(array, left, right); //取前中后三数中间值最为基准值，避免时间复杂度过高
	swap(array[mid], array[right - 1]);
	key = array[right - 1];

	while (cur < right)
	{
		if (array[cur] < key&&++prev != cur)
		{
			swap(array[prev], array[cur]);
		}
		cur++;
	}
	swap(array[++prev], array[right - 1]);
	return prev;
}

void QuickSort(int* array, int left, int right)
{
	//左闭右开
	//如果有元素（递归出口）
	if (right - left < 5)
	{
		InsertSort(array + left, right - left);
	}
	else
	{
		int div = PartSort3(array, left, right);
		QuickSort(array, left, div);
		QuickSort(array, div + 1, right);
	}
}
// 快速排序 非递归实现
void QuickSortNonR(int* a, int left, int right)
{
	stack<int> s;
	if (left < right)
	{
		s.push(left);
		s.push(right);
	}
	while (!s.empty())
	{
		int right = s.top();
		s.pop();
		int left = s.top();
		s.pop();


		int div = PartSort1(a, left, right);	
		if (left < div - 1)
	    {
		   s.push(left);
		   s.push(div - 1);
		}
		if (div + 1<right)
		{
		  s.push(div + 1);
		  s.push(right);
		}

		/*if (left < right)
		{
			int div = PartSort1(a, left, right);
			s.push(right);
			s.push(div + 1);
			s.push(div - 1);
			s.push(left);
		}*/
	}
}
void QuickSortNonR1(int* a, int size)
{
	stack<int> s;
	s.push(size);
	s.push(0);
	while (!s.empty())
	{
		int left = s.top();
		s.pop();
		int right = s.top();
		s.pop();

		if (right - left > 1)
		{

			int div = PartSort1(a, left, right);
			//div是基准值的位置
			//左半部：[left,div)
			//右半部：[div+1,right)
			//先放右，再放左
			s.push(right);
			s.push(div + 1);

			s.push(div);
			s.push(left);
		}
	}
}
//4.归并排序
//归并排序递归实现
//时间复杂度:O(NlogN)
//空间复杂度:O(N)
//稳定排序
void MergeData(int* array, int left, int mid, int right,int* temp)
{
	//左闭右开
	int begin1 = left, end1 = mid;
	int begin2 = mid, end2 = right;
	int index = left;

	while (begin1 < end1&&begin2 < end2)
	{
		if (array[begin1] <= array[begin2])
		{
			temp[index++] = array[begin1++];
		}
		else
			temp[index++] = array[begin2++];
	}
	while (begin1<end1)
		temp[index++] = array[begin1++];
	while (begin2<end2)
		temp[index++] = array[begin2++];
}
void _MergeSort(int* array, int left, int right, int* temp)
{
	if (right - left > 1)
	{
		int mid = left + ((right - left) >> 1);
		_MergeSort(array, left, mid, temp);
		_MergeSort(array, mid, right, temp);
		MergeData(array, left, mid, right, temp);//归并
		//把临时空间temp拷贝到原空间array中去
		memcpy(array + left, temp + left, (right - left)*sizeof(array[0]));
	}
}
void MergeSort(int* array, int size)
{
	int* temp = (int*)malloc(sizeof(array[0])*size);
	if (NULL == temp)
	{
		assert(0);
		return ;
	}
	_MergeSort(array, 0, size, temp);
	free(temp);
}
//归并排序非递归实现
void MergeSortNonR(int* array, int size)
{
	int gap = 1;
	int* temp = (int*)malloc(sizeof(array[0])*size);
	if (NULL == temp)
	{
		assert(0);
		return;
	}
	while (gap < size)
	{
		for (int i = 0; i < size; i += 2 * gap)
		{
			int left = i;
			int mid = left + gap;
			int right = mid + gap;
			//防止越界
			if (mid > size)
			{
				mid = size;
			}
			if (right > size)
			{
				right = size;
			}
			//归并
			MergeData(array, left, mid, right, temp);
		}
		memcpy(array, temp, size*sizeof(array[0]));
		gap <<= 1;
	}
	free(temp);
}
//计数排序
void CountSort(int* array, int size)
{
	//1.统计数据范围----并不是必须的，（如果用户告诉范围了，就不需要统计了）
	int minValue = array[0];
	int maxValue = array[0];
	for (int i = 0; i < size; i++)
	{
		if (array[i] < minValue)
			minValue = array[i];
		if (array[i] > maxValue)
			maxValue = array[i];
	}
	//不同种类元素个数
	int range = maxValue - minValue + 1;
	//2.申请空间
	int* ArrayCount = (int*)malloc(range*sizeof(int));
	if (NULL == ArrayCount)
	{
		assert(0);
		return;
	}
	memset(ArrayCount, 0, range*sizeof(int));
    //3.统计没个元素出现的次数
	for (int i = 0; i < size; i++)
	{
		ArrayCount[array[i] - minValue]++;
	}
	//4.对数据进行回收
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		while (ArrayCount[i])
		{
			array[index++] = i + minValue;
			ArrayCount[i]--;
		}
	}
	free(ArrayCount);
}
//打印函数
void Printf(int *array, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}
	cout << endl;
}

void Swap1(int &a, int &b)
{
	int c;
	c = a;
	a = b; 
	b = c;
}
//测试函数
void Test1()
{
	int array[] = { 3, 6, 9, 4, 2, 8, 7, 10, 1, 5 };
	
	//InsertSort(array, sizeof(array) / sizeof(array[0]));
	//cout << "直接插入排序: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));
	

	//ShellSort(array, sizeof(array) / sizeof(array[0]));
	//cout << "希尔排序: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));


	//int a = 6, b = 7;
	//Swap1(a, b);
	//cout << a << b << endl;

	//SelectSort(array, sizeof(array) / sizeof(array[0]));
	//cout << "选择排序: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//HeapSort(array, sizeof(array)/sizeof(array[0]));
	//cout << "堆排序: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//BubbleSort(array, sizeof(array) / sizeof(array[0]));
	//cout << "冒泡排序: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//QuickSort(array, 0, sizeof(array) / sizeof(array[0]));
	//cout << "快速排序: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//QuickSortNonR1(array,sizeof(array) / sizeof(array[0]));
	//cout << "快速排序非递归: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//MergeSort(array, sizeof(array) / sizeof(array[0]));
	//cout << "归并排序: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//MergeSortNonR(array, sizeof(array) / sizeof(array[0]));
	//cout << "归并排序非递归: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

	//CountSort(array, sizeof(array) / sizeof(array[0]));
	//cout << "计数排序: ";
	//Printf(array, sizeof(array) / sizeof(array[0]));

}
//测试函数
void Test()
{
	Test1();
}
int main()
{
	Test();
	system("pause");
	return 0;
}
#endif