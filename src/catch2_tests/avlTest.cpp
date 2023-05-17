#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"
#include "../avlTree.h"
#include <sstream>
#include <string>
using namespace std;

avlTree<int> makeTree() {
   avlTree<int> tree;
   for(int i : { 1, 2, 9, 8, 3, 4, 7, 6, 5, 10})
      tree.insert(i);
   return tree;
}

TEST_CASE( "Copy operator", "[avlTree]") {
    SECTION( "Copy of another empty tree" ) {
        avlTree<int> tree1;
        avlTree<int> tree2(tree1);
        ostringstream oss;
        oss << tree2;
        REQUIRE( oss.str()  == ".");
    }

    SECTION( "Copy of another tree" ) {
        avlTree<int> tree1;
        for (int i: {6, 2, 3, 4, 8, 7, 1, 5}) {
            tree1.insert(i);
        }
        avlTree<int> tree2(tree1);
        ostringstream oss;
        oss << tree2;
        REQUIRE(oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),8(7(.,.),.))");
    }
}

TEST_CASE( "operator=", "[avlTree]") {
    SECTION( "Affect. of another tree of the same size" ) {
        avlTree<int> tree1;
        for (int i : {6, 2, 3, 4}){
            tree1.insert(i);
        }

        avlTree<int> tree2;
        for (int i : {8, 4, 5, 6}){
            tree2.insert(i);
        }

        tree2 = tree1;
        ostringstream oss;
        oss << tree2;
        REQUIRE( oss.str()  == "3(2(.,.),6(4(.,.),.))");
    }

    SECTION( "Affect. of another tree of an empty tree" ) {
        avlTree<int> tree1;

        avlTree<int> tree2;
        tree2 = tree1;

        ostringstream oss;
        oss << tree2;
        REQUIRE( oss.str()  == ".");
    }

    SECTION( "Auto affectation" ) {
        avlTree<int> tree;
        tree = tree;
        ostringstream oss;
        oss << tree;
        REQUIRE( oss.str()  == ".");
    }

    SECTION( "Affect. of another larger tree" ) {
        avlTree<int> tree1;
        for (int i : {6, 2, 3, 4, 8, 7, 1, 5}){
            tree1.insert(i);
        }
        avlTree<int> tree2;
        for (int i : {1, 2, 3, 4}){
            tree2.insert(i);
        }
        tree2 = tree1;
        ostringstream oss;
        oss << tree2;
        REQUIRE( oss.str()  == "6(3(2(1(.,.),.),4(.,5(.,.))),8(7(.,.),.))");
    }

    SECTION( "Affect. of another smaller tree" ) {
        avlTree<int> tree1;
        for (int i : {1, 2, 3, 4}){
            tree1.insert(i);
        }
        avlTree<int> tree2;
        for (int i : {6, 2, 3, 4, 8, 7, 1, 5}){
            tree2.insert(i);
        }
        tree2 = tree1;
        ostringstream oss;
        oss << tree2;
        REQUIRE( oss.str()  == "2(1(.,.),3(.,4(.,.)))");
    }
}

TEST_CASE( "insert", "[avlTree]") {
   SECTION( "Insert into empty tree" ) {
      avlTree<int> tree;
      tree.insert(2022);
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE( oss.str() == "2022\n" );
   }

   SECTION( "Insert smaller to the left" ) {
      avlTree<int> tree;
      tree.insert(3);
      tree.insert(2);
      tree.insert(1);
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE( oss.str()  == "2\n"
                             "|_ 1\n"
                             "|_ 3\n" );
   }

   SECTION( "Insert larger to the right" ) {
      avlTree<int> tree;
      tree.insert(3);
      tree.insert(4);
      tree.insert(5);
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE( oss.str()  == "4\n"
                             "|_ 3\n"
                             "|_ 5\n" );
   }

   SECTION( "Insert twice has no effect" ) {
      avlTree<int> tree;
      tree.insert(3);
      tree.insert(3);
      tree.insert(4);
      tree.insert(4);
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE( oss.str()  == "3\n"
                             "|_ .\n"
                             "|_ 4\n" );
   }

   SECTION( "Normal tree") {
      avlTree<int> tree = makeTree();
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE( oss.str()  == "6\n"
                             "|_ 3\n"
                             "|  |_ 2\n"
                             "|  |  |_ 1\n"
                             "|  |  |_ .\n"
                             "|  |_ 4\n"
                             "|     |_ .\n"
                             "|     |_ 5\n"
                             "|_ 8\n"
                             "   |_ 7\n"
                             "   |_ 9\n"
                             "      |_ .\n"
                             "      |_ 10\n" );
   }
}

TEST_CASE("Show indented", "[avlTree]") {
   SECTION("Empty tree") {
      avlTree<int> tree;
      ostringstream oss;
      tree.show_indented(oss);
      REQUIRE(oss.str() == ".\n");
   }
}

TEST_CASE( "operator<<", "[avlTree]") {
   SECTION( "Empty tree" ) {
      avlTree<int> tree;
      ostringstream oss;
      oss << tree;
      REQUIRE( oss.str() == "." );
   }

   SECTION( "Full tree" ) {
      avlTree<int> tree = makeTree();
      ostringstream oss;
      oss << tree;
      REQUIRE( oss.str() == "6(3(2(1(.,.),.),4(.,5(.,.))),8(7(.,.),9(.,10(.,.))))" );
   }
}

TEST_CASE( "operator>>", "[avlTree]") {
   SECTION( "Empty tree" ) {
      avlTree<int> tree;
      ostringstream oss;
      oss << tree;
      REQUIRE( oss.str() == "." );
   }
}

TEST_CASE( "Contains key + insertion ", "[avlTree]") {
   SECTION( "Insertion + find a non-existing key" ) {
      avlTree<int> tree;
      for (int i : { 3, 5, 2, 6, 8, 4, 6, 4, 1 }){
         tree.insert(i);
      }
      ostringstream oss;
      oss << tree.contains(10);
      REQUIRE( oss.str() == "0" );
   }

   SECTION( "Insertion + find an existing key" ) {
      avlTree<int> tree;
      for (int i : { 3, 5, 2, 6, 8, 4, 6, 4, 1 }){
         tree.insert(i);
      }
      ostringstream oss;
      oss << tree.contains(5);
      REQUIRE( oss.str() == "1" );
   }
}

TEST_CASE( "nodeHeight", "[avlTree]") {
   SECTION( "Height of an empty tree" ) {
      avlTree<int> tree;
      ostringstream oss;
      oss << (int)tree.height();
      REQUIRE( oss.str()  == "0");
   }

   SECTION( "Get the height" ) {
      avlTree<int> tree;
      for (int i : {6, 2, 3, 4, 8, 7, 1, 5}){
         tree.insert(i);
      }
      ostringstream oss;
      oss << (int)tree.height();
      REQUIRE( oss.str()  == "4");
   }
}

TEST_CASE( "max", "[avlTree]") {
    SECTION( "Get the max key" ) {
        avlTree<int> tree;
        for (int i : { 3, 5, 2, 6, 8, 4, 6, 4, 1 }){
            tree.insert(i);
        }
        ostringstream oss;
        oss << tree.max();
        REQUIRE( oss.str() == "8" );
    }
}

TEST_CASE( "min", "[avlTree]") {
    SECTION( "Get the min key" ) {
        avlTree<int> tree;
        for (int i : { 3, 5, 2, 6, 8, 4, 6, 4, 1 }){
            tree.insert(i);
        }
        ostringstream oss;
        oss << tree.min();
        REQUIRE( oss.str() == "1" );
    }
}

TEST_CASE( "erase_max", "[avlTree]") {
    SECTION("Erase max key") {
        avlTree<int> tree;

        for (int i: {4, 3, 2, 6, 8}) {
            tree.insert(i);
        }

        ostringstream oss;
        tree.erase_max();
        oss << tree;
        REQUIRE(oss.str() == "3(2(.,.),6(4(.,.),.))");
    }

    SECTION("Erase the max key and relink sub-tree") {
        avlTree<int> tree;

        for (int i: {6, 2, 3, 4, 8, 7}) {
            tree.insert(i);
        }
        ostringstream oss;
        tree.erase_max();
        oss << tree;
        REQUIRE(oss.str() == "6(3(2(.,.),4(.,.)),7(.,.))");
    }
}

TEST_CASE( "erase_min", "[avlTree]") {
    SECTION( "Erase the min key" ) {
        avlTree<int> tree;

        for (int i : { 4, 3, 2, 6, 8 }){
            tree.insert(i);
        }

        ostringstream oss;
        tree.erase_min();
        oss << tree;
        REQUIRE( oss.str()  == "6(3(.,4(.,.)),8(.,.))");
    }

    SECTION( "Erase the min + relink the sub-tree" ) {
        avlTree<int> tree;

        for (int i : {6, 2, 4, 7, 8, 3 }){
            tree.insert(i);
        }

        ostringstream oss;
        tree.erase_min();
        oss << tree;
        REQUIRE( oss.str()  == "4(3(.,.),7(6(.,.),8(.,.)))");
    }
}

TEST_CASE( "erase", "[avlTree]") {
    SECTION( "Erase a leaf" ) {
        avlTree<int> tree;
        for (int i : {6, 2, 3, 4, 8, 7, 1, 5}){
            tree.insert(i);
        }
        ostringstream oss;
        tree.erase(5);
        oss << tree;
        REQUIRE( oss.str()  == "6(3(2(1(.,.),.),4(.,.)),8(7(.,.),.))");
    }

    SECTION( "Erase a node with deg 1" ) {
        avlTree<int> tree;

        for (int i : {6, 2, 3, 4, 8, 7, 1, 5}){
            tree.insert(i);
        }
        ostringstream oss;
        tree.erase(2);
        oss << tree;
        REQUIRE( oss.str()  == "6(3(1(.,.),4(.,5(.,.))),8(7(.,.),.))");
    }

    SECTION( "Erase a node with deg 2" ) {
        avlTree<int> tree;
        for (int i : {6, 2, 3, 4, 8, 7, 1, 5}){
            tree.insert(i);
        }
        ostringstream oss;
        tree.erase(6);
        oss << tree;
        REQUIRE( oss.str()  == "7(3(2(1(.,.),.),4(.,5(.,.))),8(.,.))");
    }
}

TEST_CASE( "Destructor", "[avlTree]") {
    SECTION( "destruction of an empty tree" ) {
        avlTree<int> tree;
        tree.~avlTree();
        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE( oss.str()  == ".\n");
    }

    SECTION( "Destruction of a full tree" ) {
        avlTree<int> tree;
        for (int i : {6, 2, 3, 4, 8, 7, 1, 5}){
            tree.insert(i);
        }
        tree.~avlTree();
        ostringstream oss;
        tree.show_indented(oss);
        REQUIRE( oss.str()  == ".\n");
    }
}