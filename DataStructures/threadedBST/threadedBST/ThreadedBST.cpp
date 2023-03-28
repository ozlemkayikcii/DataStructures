
#include "ThreadedBST.h"

///-----------------------------------------------
/// Erases all nodes in the tree
/// 
void ThreadedBST::eraseTreeNodes(BSTNode* node) {
	BSTNode* currentNode = this->min();

	while (currentNode != NULL) {

		BSTNode* Node_ = this->next(currentNode);
		delete currentNode;
		currentNode = Node_;
	}

} //end-eraseTreeNodes

///-----------------------------------------------
/// Adds a given key to the BST
/// 
void ThreadedBST::add(int key) {
	// Fill this in
	//alýnan deðerdeki node'u bulma
	BSTNode* parent = NULL;//eklenilecek olan key parent
	BSTNode* _p = root;

	while (_p) {
		//key çoktan varsa
		if (key == (_p->key)) {
			printf("This key (%d) id duplicated!\n", key);
			return;
		}
		//parent pointerýný güncelle
		parent = _p;
		//sol alt aðaçta arama
		if (key < _p->key) {
			if (_p->leftLinkType == CHILD) {
				_p = _p->left;
			}
			else {
				break;
			}

		}
		//sað alt aðaçta arama
		else {
			if (_p->rightLinkType == CHILD) {
				_p = _p->right;
			}
			else {
				break;
			}
		}
	}
	//yeni bir node oluþtur.
	BSTNode* newNode = new BSTNode(key);
	//sað-sol threads ve nodes olultur
	if (parent == NULL) {
		root = newNode;
		newNode->left = NULL;
		newNode->right = NULL;
	}
	else {
		//sol çapraza geç
		if (key < parent->key) {
			newNode->left = parent->left;
			newNode->right = parent;
			parent->leftLinkType = CHILD;
			parent->left = newNode;
		}
		else {
			//sað çapraza geçt
			newNode->left = parent;
			newNode->right = parent->right;
			parent->rightLinkType = CHILD;
			parent->right = newNode;
		}
	}
} // end-add

///-----------------------------------------------
/// Removes a given key from the BST (if it exists)
/// 
void ThreadedBST::remove(int key) {
	// Fill this in
	BSTNode* _node = root;
	BSTNode* parent = root;

	//parent node ve node'u ara
	if (parent == NULL) {
		printf("root is empty\n");
	}
	else {
		while (true) {
			if (_node->key < key) {
				if (_node->rightLinkType == THREAD) {
					return;
				}
				parent = _node;
				_node = _node->right;
			}
			else if (_node->key > key) {
				if (_node->leftLinkType == THREAD) {
					return;
				}
				parent = _node;
				_node = _node->left;
			}
			else {
				break;
			}
		}
		BSTNode* catcher = _node;
		if (!(_node->rightLinkType == THREAD) && !(_node->leftLinkType == THREAD)) {
			parent = _node; //2 çocuðu var
			catcher = _node->left; //soldaki çocuðun en büyük nodeu
			while (!(catcher->rightLinkType == THREAD)) {
				parent = catcher;
				catcher = catcher->right;
			}
			_node->key = catcher->key; //yer deðiþtir
		}
		//only left child
		if (parent->key >= catcher->key) {
			if (catcher->rightLinkType == THREAD && catcher->leftLinkType == THREAD) {
				parent->left = catcher->left;
				parent->leftLinkType = THREAD;
			}
			else if (catcher->rightLinkType == THREAD) {
				BSTNode* greatest = catcher->left;
				while (!(greatest->rightLinkType == THREAD)) {
					greatest = greatest->right;
				}
				greatest->right = parent;
				parent->left = catcher->left;
			}
			else {
				BSTNode* smallest = catcher->right;
				while (!(smallest->leftLinkType == THREAD)) {
					smallest = smallest->left;
				}
				smallest->left = catcher->left;
				parent->left = catcher->right;
			}
		}
		else {
			//only right child
			if (catcher->rightLinkType == THREAD && catcher->leftLinkType == THREAD) {
				parent->right = catcher->right;
				parent->rightLinkType = THREAD;
			}
			else if (catcher->rightLinkType == THREAD) {
				BSTNode* greatest = catcher->left;
				while (!(greatest->rightLinkType == THREAD)) {
					greatest = greatest->right;
				}
				greatest->right = catcher->right;
				parent->right = catcher->left;
			}
			else {
				BSTNode* smallest = catcher->right;
				while (!(smallest->leftLinkType == THREAD)) {
					smallest = smallest->left;
				}
				smallest->left = parent;
				parent->right = catcher->right;
			}
		}
	}

} // end-remove

///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::find(int key) {
	// Fill this in
	BSTNode* _p = root;
	while (_p != nullptr) {
		if (key == _p->key) {
			return _p;
		}
		else if (key < _p->key) {
			_p = _p->left;

		}
		else {
			_p = _p->right;
		}
	}

	return NULL;
} // end-find

///-----------------------------------------------
/// Returns the minimum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::min() {
	// Fill this in
	if (root == NULL) {
		printf("BST::min - Tree is empty\n");
		return NULL;
	}
	BSTNode* _p = root;
	while (_p->left != NULL) {
		_p = _p->left;
	}
	return _p;
} // end-min

///-----------------------------------------------
/// Returns the maximum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::max() {
	// Fill this in
	if (root == NULL) {
		printf("BST::max -Tree is empty\n");
		return NULL;
	}
	BSTNode* _p = root;
	while (_p->right != NULL) {
		_p = _p->right;
	}
	return _p;
} // end-max

///-----------------------------------------------
/// Given a valid pointer to a node in ThreadedBST,
/// returns a pointer to the node that contains the inorder predecessor
/// If the inorder predecessor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::previous(BSTNode* node) {
	// Fill this in

	if (node->leftLinkType == THREAD) {
		return node->left;
	}
	else {
		node = node->left;
		while (node->rightLinkType == CHILD) {
			node = node->right;
		}
		return node;
	}
	return NULL;

} // end-previous

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node) {
	// Fill this in

	if (node->rightLinkType == THREAD) {
		return node->right;
	}
	else {
		node = node->right;
		while (node->leftLinkType == CHILD) {
			node = node->left;
		}
		return node;
	}
	return NULL;
} // end-next