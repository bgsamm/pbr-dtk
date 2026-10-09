#pragma once

#include <revolution/types.h>

struct GSlistNode {
    // TODO(samm) Something better?
    /* 0x0 */ union {
        GSlistNode *mNextFree;
        void *mData;
    };
    // TODO(samm) Something better?
    union {
        struct {
            /* 0x4 */ GSlistNode *mNext;
        } sll;
        struct {
            /* 0x4 */ GSlistNode *mPrev;
            /* 0x8 */ GSlistNode *mNext;
        } dll;
    };
};

class GSlinkedList {
public:
    static void init(u32 param1);
    static GSlistNode *allocNode();
    static void freeNode(GSlistNode *node);
};

struct GSsinglyLinkedList {
    /* 0x0 */ GSlistNode *mHead;

    GSsinglyLinkedList() : mHead() {}

    ~GSsinglyLinkedList() {
        clear();
    }

    bool isEmpty() const {
        return mHead == NULL;
    }

    void clear() {
        GSlistNode *curr = mHead;
        while (curr) {
            GSlistNode *next = curr->sll.mNext;
            GSlinkedList::freeNode(curr);
            curr = next;
        }
        mHead = NULL;
    }

    void append(void *item) {
        if (!item) {
            return;
        }

        GSlistNode *tail = mHead;

        if (tail) {
            if (tail->mData == item) {
                return;
            }

            GSlistNode *curr;
            while ((curr = tail->sll.mNext)) {
                if (curr->mData == item) {
                    return;
                }
                tail = curr;
            }
        }

        GSlistNode *newNode = GSlinkedList::allocNode();
        if (newNode) {
            newNode->mData = item;
            newNode->sll.mNext = NULL;
        }

        if (tail) {
            tail->sll.mNext = newNode;
        } else {
            mHead = newNode;
        }
    }

    void remove(void *item) {
        if (!item) {
            return;
        }

        GSlistNode *node = mHead;
        GSlistNode *prev = NULL;

        if (!node) {
            return;
        }

        while (node) {
            if (node->mData == item) {
                break;
            }
            prev = node;
            node = node->sll.mNext;
        }

        if (!node) {
            return;
        }

        GSlistNode *next = node->sll.mNext;
        if (prev) {
            prev->sll.mNext = next;
        } else {
            mHead = next;
        }

        GSlinkedList::freeNode(node);
    }
};

struct GSdoublyLinkedList {
    /* 0x0 */ GSlistNode *mHead;
    /* 0x4 */ GSlistNode *mTail;

    GSdoublyLinkedList() : mHead(), mTail() {}

    ~GSdoublyLinkedList() {
        GSlistNode *curr = mHead;
        while (curr) {
            GSlistNode *prev = curr->dll.mNext;
            GSlinkedList::freeNode(curr);
            curr = prev;
        }
    }

    void append(void *item) {
        if (!item) {
            return;
        }

        GSlistNode *curr = mHead;
        while (curr) {
            if (curr->mData == item) {
                return;
            }
            curr = curr->dll.mNext;
        }

        GSlistNode *newNode = GSlinkedList::allocNode();
        if (newNode) {
            newNode->mData = item;
            newNode->dll.mPrev = NULL;
            newNode->dll.mNext = NULL;
        }

        if (mTail) {
            mTail->dll.mNext = newNode;
            newNode->dll.mPrev = mTail;
            mTail = newNode;
        } else {
            mHead = newNode;
            mTail = newNode;
        }
    }

    void remove(void *item) {
        if (!item) {
            return;
        }

        GSlistNode *node = mHead;

        if (!node) {
            return;
        }

        while (node) {
            if (node->mData == item) {
                break;
            }
            node = node->dll.mNext;
        }

        if (!node) {
            return;
        }

        GSlistNode *next = node->dll.mNext;
        GSlistNode *prev = node->dll.mPrev;

        if (prev) {
            prev->dll.mNext = next;
        } else {
            mHead = next;
        }

        if (next) {
            next->dll.mPrev = prev;
        } else {
            mTail = prev;
        }

        GSlinkedList::freeNode(node);
    }
};
