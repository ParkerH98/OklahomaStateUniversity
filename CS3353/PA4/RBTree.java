package CS3353.PA4;

//Parker Hague
// Red Black Tree implementation

import java.io.*;

// data structure that represents a node in the tree
class Node {
	int data; // holds the key
	Node parent; // pointer to the parent
	Node left; // pointer to left child
	Node right; // pointer to right child
	int color; // 1 . Red, 0 . Black
}


// class RedBlackTree implements the operations in Red Black Tree
public class RBTree {

	private Node root; // root of tree
    private Node nullNode; // used for null value comparisons

    
    public RBTree() {
		nullNode = new Node();
		nullNode.color = 0;
		nullNode.left = null;
		nullNode.right = null;
		root = nullNode;
	}
	

	private Node searchTreeHelper(Node node, int key) {
		if (node == nullNode || key == node.data) {
			return node;
		}

		if (key < node.data) {
			return searchTreeHelper(node.left, key);
		} 
		return searchTreeHelper(node.right, key);
	}


	// fix the rb tree modified by the delete operation
	private void fixDelete(Node n) {
		Node s;
		while (n != root && n.color == 0) {
			if (n == n.parent.left) {
				s = n.parent.right;
				if (s.color == 1) {
					// case 3.1
					s.color = 0;
					n.parent.color = 1;
					lRotate(n.parent);
					s = n.parent.right;
				}

				if (s.left.color == 0 && s.right.color == 0) {
					// case 3.2
					s.color = 1;
					n = n.parent;
				} else {
					if (s.right.color == 0) {
						// case 3.3
						s.left.color = 0;
						s.color = 1;
						rRotate(s);
						s = n.parent.right;
					} 

					// case 3.4
					s.color = n.parent.color;
					n.parent.color = 0;
					s.right.color = 0;
					lRotate(n.parent);
					n = root;
				}
			} else {
				s = n.parent.left;
				if (s.color == 1) {
					// case 3.1
					s.color = 0;
					n.parent.color = 1;
					rRotate(n.parent);
					s = n.parent.left;
				}

				if (s.right.color == 0 && s.right.color == 0) {
					// case 3.2
					s.color = 1;
					n = n.parent;
				} else {
					if (s.left.color == 0) {
						// case 3.3
						s.right.color = 0;
						s.color = 1;
						lRotate(s);
						s = n.parent.left;
					} 

					// case 3.4
					s.color = n.parent.color;
					n.parent.color = 0;
					s.left.color = 0;
					rRotate(n.parent);
					n = root;
				}
			} 
		}
		n.color = 0;
	}


	private void rbSwap(Node u, Node v){
		if (u.parent == null) {
			root = v;
		} else if (u == u.parent.left){
			u.parent.left = v;
		} else {
			u.parent.right = v;
		}
		v.parent = u.parent;
	}


    // insert the key to the tree in its appropriate position
	// and fix the tree
	public void insert(int ketemp) {

        Node s = searchTree(ketemp);
        if (s.data == ketemp){
            System.out.println("DUPLICATE KEY");
            return;
        }

		// Ordinary Binary Search Insertion
		Node node = new Node();
		node.parent = null;
		node.data = ketemp;
		node.left = nullNode;
		node.right = nullNode;
		node.color = 1; // new node must be red

		Node temp = null;
		Node n = this.root;

		while (n != nullNode) {
			temp = n;
			if (node.data < n.data) {
				n = n.left;
			} else {
				n = n.right;
			}
		}

		// temp is parent of n
		node.parent = temp;
		if (temp == null) {
			root = node;
		} else if (node.data < temp.data) {
			temp.left = node;
		} else {
			temp.right = node;
		}

		// if new node is a root node, simply return
		if (node.parent == null){
			node.color = 0;
			return;
		}

		// if the grandparent is null, simply return
		if (node.parent.parent == null) {
			return;
		}

		// Fix the tree
		fixInsert(node);
	}
    
    
	// fix the red-black tree
	private void fixInsert(Node k){
		Node u;
		while (k.parent.color == 1) {
			if (k.parent == k.parent.parent.right) {
				u = k.parent.parent.left; // uncle
				if (u.color == 1) {
					// case 3.1
					u.color = 0;
					k.parent.color = 0;
					k.parent.parent.color = 1;
					k = k.parent.parent;
				} else {
					if (k == k.parent.left) {
						// case 3.2.2
						k = k.parent;
						rRotate(k);
					}
					// case 3.2.1
					k.parent.color = 0;
					k.parent.parent.color = 1;
					lRotate(k.parent.parent);
				}
			} else {
				u = k.parent.parent.right; // uncle

				if (u.color == 1) {
					// mirror case 3.1
					u.color = 0;
					k.parent.color = 0;
					k.parent.parent.color = 1;
					k = k.parent.parent;	
				} else {
					if (k == k.parent.right) {
						// mirror case 3.2.2
						k = k.parent;
						lRotate(k);
					}
					// mirror case 3.2.1
					k.parent.color = 0;
					k.parent.parent.color = 1;
					rRotate(k.parent.parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root.color = 0;
	}


	// search the tree for the key k
	// and return the corresponding node
	public Node searchTree(int k) {
		return searchTreeHelper(this.root, k);
	}


	// find the node with the min key
	public Node min(Node node) {
		while (node.left != nullNode) {
			node = node.left;
		}
		return node;
    }
    

	// find the node with the max key
	public Node max(Node node) {
		while (node.right != nullNode) {
			node = node.right;
		}
		return node;
	}


	// find the successor of a given node
	public Node succ(Node n) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (n.right != nullNode) {
			return min(n.right);
		}

		// else it is the lowest ancestor of n whose
		// left child is also an ancestor of n.
		Node temp = n.parent;
		while (temp != nullNode && n == temp.right) {
			n = temp;
			temp = temp.parent;
		}
		return temp;
	}


	// find the predecessor of a given node
	public Node predecessor(Node n) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (n.left != nullNode) {
			return min(n.left);
		}

		Node temp = n.parent;
		while (temp != nullNode && n == temp.left) {
			n = temp;
			temp = temp.parent;
		}

		return temp;
	}


	// rotate left at node n
	public void lRotate(Node n) {
		Node temp = n.right;
		n.right = temp.left;
		if (temp.left != nullNode) {
			temp.left.parent = n;
		}
		temp.parent = n.parent;
		if (n.parent == null) {
			this.root = temp;
		} else if (n == n.parent.left) {
			n.parent.left = temp;
		} else {
			n.parent.right = temp;
		}
		temp.left = n;
		n.parent = temp;
	}


	// rotate right at node n
    public void rRotate(Node n){
        Node temp = n.left;
        n.left = temp.right;
        if (temp.right != nullNode) {
            temp.right.parent = n;
        }
        temp.parent = n.parent;
        if (n.parent == null) {
            this.root = temp;
        } else if (n == n.parent.right) {
            n.parent.right = temp;
        } else {
            n.parent.left = temp;
        }
        temp.right = n;
        n.parent = temp;
    }


	public Node getRoot(){
		return this.root;
	}


	// delete the node from the tree
	public void deleteNode(int data) {
		deleteNodeHelper(this.root, data);
    }

    private void deleteNodeHelper(Node node, int key) {
		// find the node containing key
		Node a = nullNode;
		Node n, temp;
		while (node != nullNode){
			if (node.data == key) {
				a = node;
			}

			if (node.data <= key) {
				node = node.right;
			} else {
				node = node.left;
			}
		}

		if (a == nullNode) {
			System.out.println("the key does not exist");
			return;
		} 

		temp = a;
		int tempOriginalColor = temp.color;
		if (a.left == nullNode) {
			n = a.right;
			rbSwap(a, a.right);
		} else if (a.right == nullNode) {
			n = a.left;
			rbSwap(a, a.left);
		} else {
			temp = min(a.right);
			tempOriginalColor = temp.color;
			n = temp.right;
			if (temp.parent == a) {
				n.parent = temp;
			} else {
				rbSwap(temp, temp.right);
				temp.right = a.right;
				temp.right.parent = temp;
			}

			rbSwap(a, temp);
			temp.left = a.left;
			temp.left.parent = temp;
			temp.color = a.color;
		}
		if (tempOriginalColor == 0){
			fixDelete(n);
		}
    }
    

    private void preOrderHelper(Node node) {
		if (node != nullNode) {

            String c = "R";
            if (node.color == 0) c = "B";

			System.out.print(node.data + c + " ");
			preOrderHelper(node.left);
			preOrderHelper(node.right);
		} 
	}


	private void inOrderHelper(Node node) {
		if (node != nullNode) {
            inOrderHelper(node.left);
            
            String c = "R";
            if (node.color == 0) c = "B";

			System.out.print(node.data + c + " ");
			inOrderHelper(node.right);
		} 
	}


	private void postOrderHelper(Node node) {
		if (node != nullNode) {
			postOrderHelper(node.left);
            postOrderHelper(node.right);
            
            String c = "R";
            if (node.color == 0) c = "B";

			System.out.print(node.data + c + " ");
		} 
    }
    

    // Pre-Order traversal
	// Node.left Subtree.Right Subtree
	public void printPreorder() {
		preOrderHelper(this.root);
	}


	// In-Order traversal
	// left Subtree . Node . Right Subtree
	public void printInorder() {
		inOrderHelper(this.root);
	}

    
	// Post-Order traversal
	// left Subtree . Right Subtree . Node
	public void printPostorder() {
		postOrderHelper(this.root);
	}

	
	public static void main(String[] args) {
        

        //String inFile = "RB.txt";
        String inFile = args[0];
        File fileName = new File(inFile);
        String readInput;
        String[] commands;
        String[] dotCommands;
        RBTree test = new RBTree();

        try { // try needed for file input

            BufferedReader in = new BufferedReader(new FileReader(fileName)); // reads file input

            while ((readInput = in.readLine()) != null){

                commands = readInput.split(" "); // separates each operation by the new line and stores them in an array

                for (String command : commands) {
                    if (command == commands[0]) continue;

                    if (command.contains("."));{ // further separates the commands into corresponding instance variable
        
                        dotCommands = command.split("\\.");
                    }
       
                    // stores the strings into temporay variables
                    int num = Integer.parseInt(dotCommands[0]);
                    String operation = dotCommands[1];


                    System.out.println("Operation: " + command);
                    System.out.print("Before: ");

                    if (commands[0].equals("pre")) test.printPreorder();
                    if (commands[0].equals("in")) test.printInorder();
                    if (commands[0].equals("post")) test.printPostorder();

                    System.out.println();


                    if (operation.equals("in")){
                   
                        test.insert(num);
                    }

                    if (operation.equals("del")){
            
                        test.deleteNode(num);
                    }

                    System.out.print("After: ");
               
                    if (commands[0].equals("pre")) test.printPreorder();
                    if (commands[0].equals("in")) test.printInorder();
                    if (commands[0].equals("post")) test.printPostorder();

                    System.out.println();
                    System.out.println();

                }
            }
            in.close();

        } catch (FileNotFoundException e) { // needed for file input
            System.out.println("FILE NOT FOUND");;
        }
          catch (IOException e){ // needed for file input
            e.printStackTrace();
        }

    }
}