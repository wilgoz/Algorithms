package bst

import "errors"

var (
    errUninitTree   = errors.New("err: tree uninitialized")
    errNodeNotFound = errors.New("err: node not found")
    errSuccNotFound = errors.New("err: no successor found")
)

// Node - holds data & pointers to other nodes
type Node struct {
    data    int64
    pPtr    *Node
    lPtr    *Node
    rPtr    *Node
}

// BST - points to the root node
type BST struct {
    root    *Node
    size    int64
}

func newNode(data int64, parent *Node) *Node {
    return &Node { data, parent, nil, nil }
}

func getMin(root *Node) int64 {
    min := root
    for min.lPtr != nil {
        min = min.lPtr
    }
    return min.data
}

// NewBST - creates a new BST with an initial data
func NewBST(data int64) *BST {
    return &BST { newNode(data, nil), 1 }
}

// GetSize - returns current size
func (tree *BST) GetSize() int64 {
    if tree == nil {
        return 0
    }
    return tree.size
}

// Insert - inserts data to the BST
func (tree *BST) Insert(data int64) (err error) {
    if tree == nil {
        err = errUninitTree
    } else {
        tree.size++
        tree.root = insert(tree.root, data, tree.root)
    }
    return
}

func insert(root *Node, data int64, parent *Node) *Node {
    if root == nil {
        root = newNode(data, parent)
    } else if data >= root.data {
        root.rPtr = insert(root.rPtr, data, root)
    } else {
        root.lPtr = insert(root.lPtr, data, root)
    }
    return root
}

// GetSuccessor - returns the successor element, -1 and error if none exists
func (tree *BST) GetSuccessor(data int64) (ret int64, err error) {
    if tree == nil {
        ret, err = -1, errUninitTree
    } else {
        ret, err = getSuccessor(tree.root, data)
    }
    return
}

func getSuccessor(root *Node, key int64) (ret int64, err error) {
    if root == nil {
        ret, err = -1, errSuccNotFound
    } else if key == root.data {
        ret, err = findSucc(root)
    } else if key > root.data {
        ret, err = getSuccessor(root.rPtr, key)
    } else {
        ret, err = getSuccessor(root.lPtr, key)
    }
    return
}

// If a right subtree exists, return its left-most key
// Else, move up the current root until its no longer a right-child
// Its parent key will be the successor
func findSucc(root *Node) (ret int64, err error) {
    if right := root.rPtr; right != nil {
        return getMin(right), nil
    }
    parent := root.pPtr
    curPtr := root
    for parent != nil && curPtr == parent.rPtr {
        curPtr = parent
        parent = parent.pPtr
    }
    if parent != nil {
        ret = parent.data
    } else {
        ret, err = -1, errSuccNotFound
    }
    return
}

// DeleteNode - deletes a node with the matching data & repairs the tree
func (tree *BST) DeleteNode(data int64) (err error) {
    if tree == nil {
        err = errUninitTree
    } else {
        tree.root, err = deleteNode(tree.root, data)
        if err == nil { tree.size-- }
    }
    return
}

func deleteNode(root *Node, key int64) (_ *Node, err error) {
    if root == nil { return nil, errNodeNotFound }
    if root.data == key {
        if /*  */ root.rPtr == nil {
            root = root.lPtr
        } else if root.lPtr == nil {
            root = root.rPtr
        } else {
            replacer := getMin(root.rPtr)
            root.data = replacer
            root.rPtr, _ = deleteNode(root.rPtr, replacer)
        }
    } else if key > root.data {
        root.rPtr, err = deleteNode(root.rPtr, key)
    } else {
        root.lPtr, err = deleteNode(root.lPtr, key)
    }
    return root, err
}

// Search - returns true if the key exists
func (tree *BST) Search(key int64) (ret bool, err error) {
    if tree == nil {
        err = errUninitTree
    } else {
        ret = search(tree.root, key)
    }
    return
}

func search(root *Node, key int64) (ret bool) {
    if root == nil { return false }
    if root.data == key  {
        ret = true
    } else if key > root.data {
        ret = search(root.rPtr, key)
    } else {
        ret = search(root.lPtr, key)
    }
    return
}

// TraversePostorder - postorder traversal
func (tree *BST) TraversePostorder() (ret []int64, err error) {
    if tree == nil {
        err = errUninitTree
    } else {
        traverse(&ret, tree.root)
    }
    return
}

func traverse(buff *[]int64, root *Node) {
    if root != nil {
        traverse(buff, root.lPtr)
        traverse(buff, root.rPtr)
        *buff = append(*buff, root.data)
    }
}