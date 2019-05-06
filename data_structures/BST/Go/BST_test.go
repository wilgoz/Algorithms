// brain-dead unit tests

package bst

import (
    "testing"
    "reflect"
)

var tree *BST

func init() { restore() }

func restore() {
    tree = NewBST(20)
    tree.Insert(10)
    tree.Insert(40)
    tree.Insert(70)
    tree.Insert(30)
    tree.Insert(60)
    tree.Insert(65)
    tree.Insert(80)
    tree.Insert(28)
    tree.Insert(29)
}

func TestSize(t *testing.T) {
    if v := tree.GetSize(); v != 10 {
        t.Error("Expected: 10, got:", v)
    }
}

func TestSizeUninitTree(t *testing.T) {
    var temp *BST
    if v := temp.GetSize(); v != 0 {
        t.Error("Expected: 0, got:", v)
    }
}

func TestInsertUninitializedTree(t *testing.T) {
    var temp *BST
    if err := temp.Insert(10); err != nil {
        switch err {
        case errUninitTree:
        default:
            t.Error("Expected:", errUninitTree, "got", err)
        }
    } else {
        t.Error("Expected exception")
    }
}

func TestDeleteUninitializedTree(t *testing.T) {
    var temp *BST
    if err := temp.DeleteNode(10); err != nil {
        switch err {
        case errUninitTree:
        default:
            t.Error("Expected:", errUninitTree, "got", err)
        }
    } else {
        t.Error("Expected exception")
    }
}

func TestTraverseUninitializedTree(t *testing.T) {
    var temp *BST
    if _, err := temp.TraversePostorder(); err != nil {
        switch err {
        case errUninitTree:
        default:
            t.Error("Expected:", errUninitTree, "got", err)
        }
    } else {
        t.Error("Expected exception")
    }
}

func TestSearchUninitializedTree(t *testing.T) {
    var temp *BST
    if _, err := temp.Search(10); err != nil {
        switch err {
        case errUninitTree:
        default:
            t.Error("Expected:", errUninitTree, "got", err)
        }
    } else {
        t.Error("Expected exception")
    }
}

func TestGetSuccUninitializedTree(t *testing.T) {
    var temp *BST
    if _, err := temp.GetSuccessor(10); err != nil {
        switch err {
        case errUninitTree:
        default:
            t.Error("Expected:", errUninitTree, "got", err)
        }
    } else {
        t.Error("Expected exception")
    }
}

func TestInsertLarger(t *testing.T) {
    if v := tree.root.rPtr.data; v != 40 {
        t.Error("Expected 40, got", v)
    }
}

func TestInsertSmaller(t *testing.T) {
    if v := tree.root.lPtr.data; v != 10 {
        t.Error("Expected 10, got", v)
    }
}

func TestGetSuccNoRightSubtree(t *testing.T) {
    if v, _ := tree.GetSuccessor(65); v != 70 {
        t.Error("Expected 70, got", v)
    }
}

func TestGetSuccNoSucc(t *testing.T) {
    if _, err := tree.GetSuccessor(80); err != nil {
        switch err {
        case errSuccNotFound:
        default:
            t.Error("Expected:", errSuccNotFound, "got", err)
        }
    } else {
        t.Error("Expected exception")
    }
}

func TestGetSuccRightSubtreeExists(t *testing.T) {
    if v, _ := tree.GetSuccessor(40); v != 60 {
        t.Error("Expected 60, got", v)
    }
}

func TestSearchFound(t *testing.T) {
    if v, _ := tree.Search(65); v == false {
        t.Error("Expected true, got", v)
    }
}

func TestSearchNotFound(t *testing.T) {
    if v, _ := tree.Search(2); v == true {
        t.Error("Expected false, got", v)
    }
}

func TestPostOrder(t *testing.T) {
    val, _ := tree.TraversePostorder();
    want   := []int64 { 10, 29, 28, 30, 65, 60, 80, 70, 40, 20 }
    if reflect.DeepEqual(val, want) == false {
        t.Error("Expected", want, "got", val)
    }
}


func TestDeleteNoRightSubtree(t *testing.T) {
    tree.DeleteNode(30)
    val, _ := tree.TraversePostorder()
    want   := []int64 { 10, 29, 28, 65, 60, 80, 70, 40, 20 }
    if reflect.DeepEqual(val, want) == false {
        t.Error("Expected", want, "got", val)
    }
    restore()
}

func TestDeleteNoLeftSubtree(t *testing.T) {
    tree.DeleteNode(28)
    val, _ := tree.TraversePostorder()
    want   := []int64 { 10, 29, 30, 65, 60, 80, 70, 40, 20 }
    if reflect.DeepEqual(val, want) == false {
        t.Error("Expected", want, "got", val)
    }
    restore()
}

func TestDeleteHasBothSubtrees(t *testing.T) {
    tree.DeleteNode(40)
    val, _ := tree.TraversePostorder()
    want   := []int64 { 10, 29, 28, 30, 65, 80, 70, 60, 20 }
    if reflect.DeepEqual(val, want) == false {
        t.Error("Expected", want, "got", val)
    }
    restore()
}
