// Filename: FamilyMember.java
// Author: Parker Hague
// Course: CS3363
// Assignment: Program7
// Due: Nov. 30th, 2020, 11:59 PM
// Submitted: Nov. 30th, 2020


public static class FamilyMember {

    //instance variables
    private String name;
    private FamilyMember parent;
    private FamilyMember sibling;
    private FamilyMember cousin;
    private FamilyMember child;
    private FamilyMember ancestor;

    
    // constructor for family member with a given name
    public FamilyMember(String name) {
        this.name = name;
    }


    // sets parent of a FamilyMember
    public void setParent(FamilyMember sonOf) {
        this.parent = sonOf;
    }

    
    //returns the parent of this FamilyMember
    public FamilyMember getParent() {
        return this.parent;
    }


    // gets the name of the current FamilyMember
    public String getParentName() {
        return this.parent.name;
    }


    // returns a boolean value to answer if a FamilyMember is a parent of another FamilyMember
    public static Boolean isParent(FamilyMember member1, FamilyMember member2) {
        if (member2.getParent() == member1) {
            member2.parent = member1;
            member1.child = member2;
            return true;
        }
        else return false;
    }


    // returns a boolean value to answer if a FamilyMember is a child of another FamilyMember
    public static Boolean isChild(FamilyMember member1, FamilyMember member2) {
        if (member1.getParent() == member2) {
            member2.child = member1;
            return true;
        } else
            return false;
    }
    

    // gets the child of the current FamilyMember
    public FamilyMember getChild() {
        return this.child;
    }


    // returns a boolean value to answer if a FamilyMember is an ancestor of another FamilyMember
    public static Boolean isAncestor(FamilyMember member1, FamilyMember member2) {
    
        FamilyMember parent1 = member2.getParent();
        FamilyMember parent2 = parent1.getParent();

        System.out.println(parent2.name);

        // ancestors from parents
        if (isParent(member1, member2)) {
            member2.ancestor = member1;
            return true;
        }

        // ancestors from grandparents and so on
        if (FamilyMember.isParent(parent2, parent1)) {
            return true;
        }
        
        else return false;
    }


    // returns a boolean value to answer if a FamilyMember is a sibling of another FamilyMember
    public static Boolean isSibling(FamilyMember member1, FamilyMember member2) {

        if (member1.getParent() == member2.getParent()) {
            member1.sibling = member2;
            member2.sibling = member1;
            return true;
        }

        else return false;
    }
    

    // returns a boolean value to answer if a FamilyMember is a cousin of another FamilyMember
    public static Boolean isCousin(FamilyMember member1, FamilyMember member2) {
    
        FamilyMember parent1 = member1.getParent();
        FamilyMember parent2 = member2.getParent();
        System.out.println("test" + FamilyMember.isSibling(parent1, parent2));

        System.out.println(member1.getParentName());
        System.out.println(member2.getParentName());


        if (isSibling(parent1, parent2) && !isSibling(member1, member2)) {
            return true;
        }
        
        else return false;
    }

    public static void main(String[] args) {

    // delcares a bunch of FamilyMember objects for testing
    FamilyMember warren = new FamilyMember("Warren");
    FamilyMember dan = new FamilyMember("Dan");
    FamilyMember david = new FamilyMember("David");
    FamilyMember robert = new FamilyMember("Robert");
    FamilyMember charyl = new FamilyMember("Charyl");
    FamilyMember parker = new FamilyMember("Parker");
    FamilyMember brin = new FamilyMember("Brin");
    FamilyMember austin = new FamilyMember("Austin");
    FamilyMember ashlyn = new FamilyMember("Ashlyn");

    // establishes all parent/child relationships
    // all other relationships are derived from these 
    // relationships
    david.setParent(warren);
    dan.setParent(warren);
    robert.setParent(david);
    charyl.setParent(david);
    parker.setParent(robert);
    brin.setParent(robert);
    austin.setParent(charyl);
    ashlyn.setParent(charyl);

    // now a bunch of queries can be made like
    // System.out.printline(parker.getParent());
    // isCousin(parker, austin);
    // isAncestor(david, charyl);
    // and more...
}

}


