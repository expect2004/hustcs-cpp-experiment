#include "ex1_queue.h"

void initQueue(Queue *const p, int m) {
    *(int**)&p -> elems = new int [m];
    *(int*)&p -> max = m;
    p -> head = p -> tail = 0;
}

void initQueue(Queue *const p, const Queue &s) {
    *(int**)&p -> elems = new int [s.max];
    *(int*)&p -> max = s.max;
    p -> head = s.head, p -> tail = s.tail;
    for(int i = 0; i < s.max; ++i) {
        p -> elems[i] = s.elems[i];
    }
}

void initQueue(Queue *const p, Queue && s) {
    *(int**)&p -> elems = s.elems;
    *(int*)&p -> max = s.max;
    p -> head = s.head, p -> tail = s.tail;
    *(int**)&s.elems = 0;
    *(int*)&s.max = 0;
    s.head = s.tail = 0;
}

int number(const Queue *const p) {
    if(p -> max == 0) return 0;
    return (p -> tail - p -> head + p -> max) % p -> max;
}

int size(const Queue *const p) {
    return p -> max;
}

Queue *const enter(Queue *const p, int e) {
    if((p -> tail + 1) % p -> max == p -> head) {
        throw "Full Queue";
    }
    p -> elems[p -> tail] = e;
    p -> tail = (p -> tail + 1) % p -> max;
    return p;
}

Queue *const leave(Queue *const p, int &e) {
    if(p -> head == p -> tail) {
        throw "Empty Queue";
    }
    e = p -> elems[p -> head];
    p -> head = (p -> head + 1) % p -> max;
    return p;
}

Queue *const assign(Queue *const p, const Queue &q) {
    if(p == &q) return p;
    if(p -> elems) delete [] p -> elems;
    *(int**)&p -> elems = new int [q.max];
    *(int*)&p -> max = q.max;
    p -> tail = q.tail, p -> head = q.head;
    for(int i = 0; i < q.max; i++) {
        p -> elems[i] = q.elems[i];
    }
    return p;
}

Queue *const assign(Queue *const p, Queue &&q) {
    if(p == &q) return p;
    if(p -> elems) delete [] p -> elems;
    *(int**)&p -> elems = q.elems;
    *(int*)&p -> max = q.max;
    p -> head = q.head, p -> tail = q.tail;
    *(int**)q.elems = NULL;
    *(int*)q.max = 0;
    q.head = q.tail = 0;
    return p;
}

char *print(const Queue *const p, char *s) {
	for (int i = p -> head; i != p -> tail; i = (i + 1) % p -> max) {
		s += sprintf(s, "%d,", p -> elems[i]);
	}
	return s;
}

void destroyQueue(Queue *const p) {
    if(p -> elems) delete [] p -> elems;
    *(int**)&p -> elems = NULL;
    *(int*)&p -> max = 0;
    p -> tail = p -> head = 0;
}