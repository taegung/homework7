/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {//구조체 node 정의
	int key;
	struct Node* llink;//구조체 포인터 변수 llink 선언
	struct Node* rlink;//구조체 포인터 변수 rlink 선언
} listNode;



typedef struct Head {//구조체 Head 정의
	struct Node* first;//구조체 포인터 변수 first 선언
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("[2019038059]    [윤태경]\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//커맨드 입력

		switch(command) {
		case 'z': case 'Z'://z또는 Z를 입력받은 경우
			initialize(&headnode);//intalize 함수에 headnode 주소 입력
			break;
		case 'p': case 'P'://p또는 P 를 입력받은 경우
			printList(headnode);// printList 함수 실행
			break;
		case 'i': case 'I'://i또는 I를 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력 
			insertNode(headnode, key);// insertnode 함수 실행 -> key값을 넘겨준다
			break;
		case 'd': case 'D'://d또는D를 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력
			deleteNode(headnode, key);//deleteNode 함수 실행 -> key값을 넘겨준다 
			break;
		case 'n': case 'N'://n을 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값 입력 
			insertLast(headnode, key);//insertLast 함수 실행 -> key값을 넘겨준다
			break;
		case 'e': case 'E'://e또는 E를 입력받은 경우
			deleteLast(headnode);//deleteLast 함수 실행 
			break;
		case 'f': case 'F'://f또는 F를  입력받은 겨우
			printf("Your Key = ");
			scanf("%d", &key);//key값 입력
			insertFirst(headnode, key);//insertFirst 함수 실행 -> key값을 넘겨준다
			break;
		case 't': case 'T'://t또는 T를 입력받은 경우
			deleteFirst(headnode);//deleteFirst 함수 실행
			break;
		case 'r': case 'R'://r또는 R을 입력받은 경우
			invertList(headnode);//invertList 함수 실행
			break;
		case 'q': case 'Q'://q또는 Q를 입력받은 경우
			freeList(headnode);//freeList 함수 실행
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));// headNode에 대한 포인터 변수 h 메모리 동적 할당
	(*h)->first = NULL;//새로운 공백 리스트 만듬
	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //구조체 listNode의 포인터 변수 p에 리스트의 시작 주소 대입

	listNode* prev = NULL;//prev라는 새로운 공백 리스트 생성
	while(p != NULL) {//p값이 NULL이 아닐떄
		prev = p;//prev에 p대입
		p = p->rlink;//p값에 p->rlink 대입
		free(prev);//prev 메모리 할당 해제
	}
	free(h);//h 메모리 할당 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;//구조체 포인터 변수 선언

	printf("\n---PRINT\n");

	if(h == NULL) {//h값이 NULL일떄
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;//p가 헤드노드를 가리킴

	while(p != NULL) {//노드가 NuLL이 아닐때
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;//p에 다음 노드를 가리키게 함
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));//listNode 구조체 포인터 변수 node를 동적할당
	node->key = key;//새로운 노드의 key값에 입력받은 key값 대입
	node->rlink = NULL;//node->rlink가 연결된 값이 없음
	node->llink = NULL;//node->llink가 연결된 값이 없음

	if (h->first == NULL)//노드가 NULL인경우
	{
		h->first = node;//첫번쨰 노드에 입력받은 node값 대입
		return 0;
	}

	listNode* n = h->first;// 새로운 노드를 만든 후 연결리스트 첫번째 주소를 대입
	while(n->rlink != NULL) {//
		n = n->rlink;//n에 n->rlink값 연결
	}
	n->rlink = node;//	n->rlink에 node값 대입
	node->llink = n;//node->llink 에 n 대입
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)//노드의 값이NuLL인경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;//n이 헤드노드 가리킴
	listNode* trail = NULL; //비어있는 노드를 생성한다

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {//노드를 한칸씩 이동하며 마지막 노드까지 이동
		trail = n;//trail에 n값 대입
		n = n->rlink;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;
	free(n); //메모리할당 해제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));//node 동적 할당 해줌
	node->key = key;//node key값에 입력받은 key값을 대입
	node->rlink = node->llink = NULL;

	if(h->first == NULL)//헤드 노드가 NULL때
	{
		h->first = node;//헤드 노드에 node입력
		return 1;
	}

	node->rlink = h->first; //node ->rlink가 첫번째 노드를 가리키게 함
	node->llink = NULL;

	listNode *p = h->first;
	p->llink = node;//
	h->first = node;//헤드 노드를 변경

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)//헤드노드가 NULL인경우
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;//n이 헤드 노드를 가리킴
	h->first = n->rlink;//2번째 노드를 헤드노드로 변경 

	free(n);

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //노드의 값이 NuLL일
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //n이 헤드노드를 가리킴
	listNode *trail = NULL;// 비어있는 노드를 생성
	listNode *middle = NULL; // 비어있는 노드를 생성

	while(n != NULL){//빈노드가 아닐경우 반복
		trail = middle; //trail에 middle값 대입
		middle = n; //middle은 n에 값을  대입
		n = n->rlink;//n은 n->rlink를 넣어줌
		middle->rlink = trail;//middle->rlink가 trail을 가르킴
		middle->llink = n;//middle->llink가 n을 가르킴
	}

	h->first = middle; //마지막에는 n이 null을 가리키고 middle이 마지막 노드를 가리키기 때문에 middle이 헤드노드가 된다

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {//노드에 값을 입력하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));//listNode 구조체 포인터 변수 node를 동적할당
	node->key = key; // 새로운 노드의 key값에 입력받은 key값을 대입
	node->llink = node->rlink = NULL;// node->llink와 node->rlink가 연결된 값이 없음을 나타냄

	if (h->first == NULL)//노드가 NuLL일 경우
	{
		h->first = node;//첫번째 노드에 입력받은 node 값 대입
		return 0;
	}

	listNode* n = h->first; // 새로운 노드를 만든 후 연결리스트 첫번째 주소를 대입

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key >= key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;//node->rlink를 n과 연결
				node->llink = n->llink;//node->llink를 n->llink연결
				n->llink->rlink = node;//n->llink->rlink을 node와 연결
			}
			return 0;
		}

		n = n->rlink;//n에 n->rlink입력
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)//헤드노드가 NULL인경우
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;//n이 헤드 노드를 가리킴

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;//n->llink->rlink을  n->rlink 바꿔줌
				n->rlink->llink = n->llink;//n->rlink->llink을n->llinkfh 바꿔줌
				free(n);//메모리 할당 해제
			}
			return 1;
		}

		n = n->rlink;//n에n->rlink값 대입
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


