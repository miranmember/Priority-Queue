// priorityqueue.h
//
// TODO:  write this header comment
#pragma once

#include <iostream>
#include <sstream>
#include <set>
#include <string>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)
    
    void _recursiveFunciton(NODE* node, ostream& output){
    	if (node == nullptr) {
    		return;
    	}
    	
    	
    	_recursiveFunciton(node->left, output);   	
    	if (node->dup) {
    		NODE *tmp = node;
    		while (tmp != nullptr) {
    			output << tmp->priority << " value: " << tmp->value << endl;
    			tmp = tmp->link;
    		}
    	} else {
    		output << node->priority << " value: " << node->value << endl;
    	}
    	_recursiveFunciton(node->right, output);
    }

    
    void _clear(NODE *cur) {
    	if (cur == nullptr) {
    		return;
    	}
    	_clear(cur->left);
    	_clear(cur->right);
    	if (cur->dup) {
    		NODE *tmp = cur;
    		NODE *next = nullptr;
    		while (tmp != nullptr) {
    			next = tmp->link;
    			delete tmp;
    			tmp = next;
    		}
    	} else {
    		delete cur;
    	}
    }
    
    void clone(NODE *tmp, NODE *parent, NODE *&n) {
    	if (tmp == nullptr) { n = nullptr; return; }
    	n = new NODE;
    	size++;
    	n->priority = tmp->priority;
    	n->value = tmp->value;
    	n->dup = tmp->dup;
    	clone(tmp->link, n, n->link);
    }
    
    void _copy(NODE* tmp, NODE *parent, NODE *& n) {
    	if (tmp == nullptr) {
    		n = nullptr;
    		return;
    	}
    	
    	
    	if (tmp->dup) {
    		n = new NODE;
    		size++;
	    	n->priority = tmp->priority;
	    	n->value = tmp->value;
	    	n->dup = tmp->dup;
	   		NODE *TEMP = tmp->link;
	    	clone(TEMP, n, n->link);
    	} else {
	    	n = new NODE;
	    	size++;
	    	n->priority = tmp->priority;
	    	n->value = tmp->value;
	    	n->dup = tmp->dup;
	    	n->link = nullptr;
    	}
    	_copy(tmp->left, n, n->left);
    	_copy(tmp->right, n, n->right);
    }
    
    void _enqueue(NODE* cur, T value, int priority) {
    	cur->dup = true;
    	while(cur->link != nullptr) {
    		cur = cur->link;
    	}
    	NODE *n = new NODE;
    	n->priority = priority;
    	n->value = value;
    	n->link = nullptr;
    	n->right = nullptr;
    	n->left = nullptr;
    	n->parent = cur;
    	cur->link = n;
    	size++;
    }
    
    NODE* _dequeue(NODE *&head, int priority, NODE *parent) {
    	if (head == nullptr) {
    		return nullptr;
    	}
    	
    	if (head->priority > priority) {
    		head->left = _dequeue(head->left, priority, head);
    	} else if (head->priority < priority) {
    		head->right = _dequeue(head->right, priority, head);
    	} else {
    		if (head->link) {
    			NODE *tmp = head->link;
    			tmp->parent = head->parent;
    			tmp->left = head->left;
    			tmp->right = head->right;
    			delete head;
    			return tmp;
    		}
    		
    		if(head->right == nullptr && head->left == nullptr) {
				delete head;
				return nullptr;
    		}  else if (head->right != nullptr && head->left == nullptr) {
    			NODE* right = head->right;
    			right->parent = parent;
    			delete head;
    			return right;
    		} else if (head->right == nullptr && head->left != nullptr) {
    			NODE* left = head->left;
    			left->parent = parent;
    			delete head;
    			return left;
    		} else {
    			NODE *tmp = head->right;
    			while(tmp != nullptr) {
    				tmp = tmp->left;
    			}
    			head->priority = tmp->priority;
    			head->dup = tmp->dup;
    			head->value = tmp->value;
    			head->link = tmp->link;
    			head->link->parent = head;
    			tmp->link = nullptr;
    			head->right = _dequeue(head->right, head->priority, head);
    		}
    	}
    	return head;
    }
    
    bool _check(NODE *root, NODE *O) const {
    	if (root == nullptr || O == nullptr) { return false; }
    	
    	_check(root->left, O->left);
    	_check(root->right, O->right);
    	if (root->value == O->value && root->priority == O->priority) {
    		if (root->link && O->link) {
    			NODE *tmp = root, *tmp1 = O;
    			while (true) {
    				if (root->value == O->value && root->priority == O->priority) {
    					continue;
    				} else {
    					return false;
    				}
    			}
    		}
    		return true;
    	}
    	return false;
    }
    
public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
    	curr = nullptr;
    	root = nullptr;
    	size = 0;
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    
    priorityqueue& operator=(const priorityqueue& other) {
        clear();
        NODE* tmp = other.root;
        _copy(tmp, nullptr, root);
        return *this;
    }
    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    
    void clear() {
    	_clear(root);
    	root = nullptr;
    	curr = nullptr;
    	size = 0;
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        clear();
        // TO DO: write this function.
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    
    void enqueue(T value, int priority) {
        NODE* prev = nullptr;
        NODE* cur = root;
        
        while(cur != nullptr) {
        	if (priority == cur->priority) {
        		_enqueue(cur, value, priority);
        		return;
        	}
        	if (priority < cur->priority) {
        		prev = cur;
        		cur = cur->left;
        	} else {
        		prev = cur;
        		cur = cur->right;
        	}
        }
        
        NODE *n = new NODE;
        n->priority = priority;
        n->value = value;
        n->dup = false;
        n->link = nullptr;
        n->left = nullptr;
        n->right = nullptr;
        n->parent = prev;
        
        if (prev == nullptr) {
        	root = n;
        } else if (priority < prev->priority) {
        	prev->left = n;
        } else {
        	prev->right = n;
        }
        size++;
    }
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    
    T dequeue() {
        if (root == nullptr) {
        	return T();
        }
        NODE *tmp = root;
        while(tmp->left != nullptr) {
        	tmp = tmp->left;
        }
		
        T value = tmp->value;
        size--;
        root = _dequeue(root, tmp->priority, nullptr);
        return value; // TO DO: update this return
    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        return size; // TO DO: update this return
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
	
    void begin() {
    	curr = root;
		if (curr->left != nullptr) {
			while (curr->left != nullptr) {
				curr = curr->left;
			}
		}
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(?) - hard to say.  But approximately O(logn + m).  Definitely not O(n).
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
    	if (curr == nullptr) {
    		return false;
    	}
    	
    	value = curr->value;
    	priority = curr->priority;
    	
    	if(curr->link != nullptr) {
    		curr = curr->link;
    		return true;
    	}
    	
    	while(curr->priority != priority && curr->dup) {
    		curr = curr->parent;
    	}
    	if (curr->right != nullptr) {
    		curr = curr->right;
    		while(curr->left != nullptr) {
    			curr = curr->left;
    		}
    		if (curr != nullptr) {
    			return true;
    		}
    	} else {
    		while(curr->parent != nullptr) {
    			if (curr->parent->left == curr) {
    				curr = curr->parent;
    				return true;
    			}
    			curr = curr->parent;
    		}
    	}
    	return false;
    }
    
    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    
    

    string toString() {
        stringstream output;
        NODE *tmp = root;
        _recursiveFunciton(tmp, output);
        string S = output.str();
        return S;
    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T peek() {
        if (!root) {
        	return T();
        }
        
        NODE *tmp = root;
        while(tmp->left != nullptr) {
        	tmp = tmp->left;
        }
		
        T value = tmp->value;
        return value;
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    
    bool operator==(const priorityqueue& other) const {
        if (this == &other) {
        	return true;
        }
        if (size == other.size) {
        	return true;
        } else {
        	return false;
        }
        
        NODE *tmp = root;
        NODE *tmp1 = other.root;
        bool C = _check(tmp, tmp1);
        return C;
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
