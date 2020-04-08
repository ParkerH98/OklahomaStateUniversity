package CS3353.PA4;

import javafx.scene.paint.Color;

public class Node {

    
    public Node parent;
    public Node rightChild;
    public Node leftChild;
    public int element;
    public Color color;


    Node(int element){
        this.element = element;
    }


    public void setParent(Node parent){


        this.parent = parent;

    }


    public void setLeftChild(Node leftChild){

        this.leftChild = leftChild;
        if (this.leftChild != null){
            this.leftChild.setParent(this);
        }
    }

    public void setRightChild(Node rightChild){

        this.rightChild = rightChild;
        if (this.leftChild != null){
            this.leftChild.setParent(this);
        }
    }

    public int setElement(int element){
        this.element = element;
        return element;
    }
}