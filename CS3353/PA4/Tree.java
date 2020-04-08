package CS3353.PA4;

import java.util.Comparator;

import javafx.scene.paint.Color;

// if a node is red, both its children are black





public class Tree implements Comparator{


    Node root = null;
    private int size = 0;



    public void insert(int element){

        Node temp = root;

        if (temp == null){
            root = new Node(element);
            size = 1;
        }


        Node parent;
        int compare;
        

        do{

            parent = temp;
            compare = compare(element, root.element);

            if (compare < 0){
                temp = temp.leftChild;
            }

            else if (compare > 0){
                temp = temp.rightChild;
            }

            else return;

        } while (temp != null);

        Node n = new Node(element);

        if (compare < 0){
            parent.leftChild = n;
        }

        else {
            parent.rightChild = n;
            correctInsertion(n);
            size++;
            return;
        }
    }


    public void correctInsertion(Node x){


        x.color = Color.RED;

        while (x != null && x != root && x.parent.color == Color.RED){
            if (x.parent.element == x.leftChild.parent.parent.element){
                Node y = x.rightChild.parent.parent;
                if (y.color == Color.RED){
                    setColor(x.parent, Color.BLACK);
                    setColor(y, Color.BLACK);
                    setColor(x.parent.parent, Color.RED);
                }
            }
        }



    }

    @Override
    public int compare(Object o1, Object o2) {

        Node n1 = (Node) o1;
        Node n2 = (Node) o2;

        if (n1.element > n2.element){
            return 1;
        }
        if (n1.element < n2.element){
            return -1;
        }
        
        return 0;
    }
}