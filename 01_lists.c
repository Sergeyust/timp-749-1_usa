#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node {
	int value; // значение, которое хранит узел
	struct node* nxt; // ссылка на следующий элемент списка
} node;
typedef struct list {
	struct node* head; // начало списка
} list;
// инициализация пустого списка
void init(list* l) {
	l->head = malloc(sizeof(node));
	l->head = NULL;
	return;
}
// удалить все элементы из списка
void clean(list* l) {
	if (!l->head) {
		return;
	}
	node* actual = l->head;
	node* temp;
	while (actual) {
		temp = actual->nxt;
		free(actual);
		actual = temp;
	}
	l->head = NULL;
	return;
}
// проверка на пустоту списка
bool is_empty(list* l) {
	if (l->head == NULL) {
		return true;
	}
	return false;
}
// поиск элемента по значению. вернуть NULL если эжемент не найден
node* find(list* l, int key) {
	node* actual = l->head;
	if (!l->head) {
		return NULL;
	}
	while (actual->value != key) {
		actual = actual->nxt;
		if (actual == NULL) {
			return NULL;
		}
	}
	return actual;
}
node* SearchEnd(list* l) {
	if (l->head == NULL) {
		return NULL;
	}
	node* actual = l->head;
	while (actual->nxt != NULL) {
		actual = actual->nxt;
	}
	return actual;
}
// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list* l, int key) {
	if (!is_empty(l)) {
		node* lastnode = SearchEnd(l);
		node* actual = malloc(sizeof(node));
		lastnode->nxt = actual;
		actual->nxt = NULL;
		actual->value = key;
	}
	else {
		node* actual = malloc(sizeof(node));
		actual->value = key;
		actual->nxt = NULL;
		l->head = actual;
	}
	return 0;
}
// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list* l, int key) {
	node* actual;
	actual = malloc(sizeof(node));
	actual->value = key;
	actual->nxt = l->head;
	l->head = actual;
	return 0;
}
// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node* n, int key) {
	if (n == NULL) {
		return 1;
	}
	node* NewNode = malloc(sizeof(node));
	NewNode->value = key;
	NewNode->nxt = n->nxt;
	n->nxt = NewNode;
	return 0;
}
// удалить первый элемент из списка с указанным значением,
// вернуть 0 если успешно
int remove_node(list* l, int key) {
	node* actual = l->head;
	node* prev = NULL;
	if (l->head == NULL) {
		return 1;
	}
	while (actual->value != key) {
		if (actual->nxt == NULL) {
			return 1;
		}
		else {
			prev = actual;
			actual = actual->nxt;
		}
	}
	if (actual == l->head) {
		l->head = l->head->nxt;
	}
	else {
		prev->nxt = actual->nxt;
	}
	free(actual);
	return 0;
}
// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list* l) {
	node* actual = l->head;
	if (actual == NULL) {
		return;
	}
	while (actual != NULL) {
		printf("%d ", actual->value);
		actual = actual->nxt;
	}
	printf("\n");
	return;
}
void checkk(node* n1, node* n2, node* n3) {
	if (n1 == NULL) {
		printf("0 ");
	}
	else {
		printf("1 ");
	}
	if (n2 == NULL) {
		printf("0 ");
	}
	else {
		printf("1 ");
	}
	if (n3 == NULL) {
		printf("0 ");
	}
	else {
		printf("1 \n");
	}
}
node* searchbyindex(list* l, int index) {
	if (l->head == NULL) {
		return NULL;
	}
	node* actual = l->head;
	int i = 0;
	while (i != index) {
		actual = actual->nxt;
		if (actual == NULL) {
			return NULL;
		}
		i++;
	}
	return actual;
}
int main() {
	int i, n, k1, k2, k3, m, t, j, x, z, a;
	(void)scanf("%d", &n);
	list* link;
	link = malloc(sizeof(list));
	init(link);
	for (i = 1; i <= n; i++) {
		(void)scanf("%d", &a);
		push_back(link, a);
	}
	print(link);
	(void)scanf("%d %d %d", &k1, &k2, &k3);
	node* finder1 = find(link, k1);
	node* finder2 = find(link, k2);
	node* finder3 = find(link, k3);
	checkk(finder1, finder2, finder3);
	(void)scanf("%d", &m);
	push_back(link, m);
	print(link);
	(void)scanf("%d", &t);
	push_front(link, t);
	print(link);
	(void)scanf("%d %d", &j, &x);
	node* FindNode = searchbyindex(link, j - 1);
	insert_after(FindNode, x);
	print(link);
	(void)scanf("%d", &z);
	remove_node(link, z);
	print(link);
	clean(link);
	link->head = NULL;
	return 0;
}
