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
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node {//����ü node ����
	int key;
	struct Node* llink;//����ü ������ ���� llink ����
	struct Node* rlink;//����ü ������ ���� rlink ����
} listNode;



typedef struct Head {//����ü Head ����
	struct Node* first;//����ü ������ ���� first ����
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         lab3�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
		printf("[2019038059]    [���°�]\n");
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
		scanf(" %c", &command);//Ŀ�ǵ� �Է�

		switch(command) {
		case 'z': case 'Z'://z�Ǵ� Z�� �Է¹��� ���
			initialize(&headnode);//intalize �Լ��� headnode �ּ� �Է�
			break;
		case 'p': case 'P'://p�Ǵ� P �� �Է¹��� ���
			printList(headnode);// printList �Լ� ����
			break;
		case 'i': case 'I'://i�Ǵ� I�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է� 
			insertNode(headnode, key);// insertnode �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 'd': case 'D'://d�Ǵ�D�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է�
			deleteNode(headnode, key);//deleteNode �Լ� ���� -> key���� �Ѱ��ش� 
			break;
		case 'n': case 'N'://n�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key�� �Է� 
			insertLast(headnode, key);//insertLast �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 'e': case 'E'://e�Ǵ� E�� �Է¹��� ���
			deleteLast(headnode);//deleteLast �Լ� ���� 
			break;
		case 'f': case 'F'://f�Ǵ� F��  �Է¹��� �ܿ�
			printf("Your Key = ");
			scanf("%d", &key);//key�� �Է�
			insertFirst(headnode, key);//insertFirst �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 't': case 'T'://t�Ǵ� T�� �Է¹��� ���
			deleteFirst(headnode);//deleteFirst �Լ� ����
			break;
		case 'r': case 'R'://r�Ǵ� R�� �Է¹��� ���
			invertList(headnode);//invertList �Լ� ����
			break;
		case 'q': case 'Q'://q�Ǵ� Q�� �Է¹��� ���
			freeList(headnode);//freeList �Լ� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode));// headNode�� ���� ������ ���� h �޸� ���� �Ҵ�
	(*h)->first = NULL;//���ο� ���� ����Ʈ ����
	return 1;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first; //����ü listNode�� ������ ���� p�� ����Ʈ�� ���� �ּ� ����

	listNode* prev = NULL;//prev��� ���ο� ���� ����Ʈ ����
	while(p != NULL) {//p���� NULL�� �ƴҋ�
		prev = p;//prev�� p����
		p = p->rlink;//p���� p->rlink ����
		free(prev);//prev �޸� �Ҵ� ����
	}
	free(h);//h �޸� �Ҵ� ����
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;//����ü ������ ���� ����

	printf("\n---PRINT\n");

	if(h == NULL) {//h���� NULL�ϋ�
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;//p�� ����带 ����Ŵ

	while(p != NULL) {//��尡 NuLL�� �ƴҶ�
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;//p�� ���� ��带 ����Ű�� ��
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));//listNode ����ü ������ ���� node�� �����Ҵ�
	node->key = key;//���ο� ����� key���� �Է¹��� key�� ����
	node->rlink = NULL;//node->rlink�� ����� ���� ����
	node->llink = NULL;//node->llink�� ����� ���� ����

	if (h->first == NULL)//��尡 NULL�ΰ��
	{
		h->first = node;//ù���� ��忡 �Է¹��� node�� ����
		return 0;
	}

	listNode* n = h->first;// ���ο� ��带 ���� �� ���Ḯ��Ʈ ù��° �ּҸ� ����
	while(n->rlink != NULL) {//
		n = n->rlink;//n�� n->rlink�� ����
	}
	n->rlink = node;//	n->rlink�� node�� ����
	node->llink = n;//node->llink �� n ����
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)//����� ����NuLL�ΰ��
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;//n�� ����� ����Ŵ
	listNode* trail = NULL; //����ִ� ��带 �����Ѵ�

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->rlink != NULL) {//��带 ��ĭ�� �̵��ϸ� ������ ������ �̵�
		trail = n;//trail�� n�� ����
		n = n->rlink;
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL;
	free(n); //�޸��Ҵ� ����

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));//node ���� �Ҵ� ����
	node->key = key;//node key���� �Է¹��� key���� ����
	node->rlink = node->llink = NULL;

	if(h->first == NULL)//��� ��尡 NULL��
	{
		h->first = node;//��� ��忡 node�Է�
		return 1;
	}

	node->rlink = h->first; //node ->rlink�� ù��° ��带 ����Ű�� ��
	node->llink = NULL;

	listNode *p = h->first;
	p->llink = node;//
	h->first = node;//��� ��带 ����

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)//����尡 NULL�ΰ��
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;//n�� ��� ��带 ����Ŵ
	h->first = n->rlink;//2��° ��带 ������ ���� 

	free(n);

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //����� ���� NuLL��
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first; //n�� ����带 ����Ŵ
	listNode *trail = NULL;// ����ִ� ��带 ����
	listNode *middle = NULL; // ����ִ� ��带 ����

	while(n != NULL){//���尡 �ƴҰ�� �ݺ�
		trail = middle; //trail�� middle�� ����
		middle = n; //middle�� n�� ����  ����
		n = n->rlink;//n�� n->rlink�� �־���
		middle->rlink = trail;//middle->rlink�� trail�� ����Ŵ
		middle->llink = n;//middle->llink�� n�� ����Ŵ
	}

	h->first = middle; //���������� n�� null�� ����Ű�� middle�� ������ ��带 ����Ű�� ������ middle�� ����尡 �ȴ�

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {//��忡 ���� �Է��ϴ� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode));//listNode ����ü ������ ���� node�� �����Ҵ�
	node->key = key; // ���ο� ����� key���� �Է¹��� key���� ����
	node->llink = node->rlink = NULL;// node->llink�� node->rlink�� ����� ���� ������ ��Ÿ��

	if (h->first == NULL)//��尡 NuLL�� ���
	{
		h->first = node;//ù��° ��忡 �Է¹��� node �� ����
		return 0;
	}

	listNode* n = h->first; // ���ο� ��带 ���� �� ���Ḯ��Ʈ ù��° �ּҸ� ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key >= key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {
				insertFirst(h, key);
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;//node->rlink�� n�� ����
				node->llink = n->llink;//node->llink�� n->llink����
				n->llink->rlink = node;//n->llink->rlink�� node�� ����
			}
			return 0;
		}

		n = n->rlink;//n�� n->rlink�Է�
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)//����尡 NULL�ΰ��
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;//n�� ��� ��带 ����Ŵ

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);
			} else if (n->rlink == NULL){ /* ������ ����� ��� */
				deleteLast(h);
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink;//n->llink->rlink��  n->rlink �ٲ���
				n->rlink->llink = n->llink;//n->rlink->llink��n->llinkfh �ٲ���
				free(n);//�޸� �Ҵ� ����
			}
			return 1;
		}

		n = n->rlink;//n��n->rlink�� ����
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


