#ifndef ASD_LABS_2021_AVLNODE_H
#define ASD_LABS_2021_AVLNODE_H

namespace avl {

   enum Side {
      LEFT = 0, RIGHT = 1
   };

   template<typename Key>
   struct Node {
      Key const key;
      std::array<Node *, 2> children;
      unsigned char nodeHeight;

      inline Node *&left() noexcept { return children[LEFT]; }

      inline Node *const &left() const noexcept { return children[LEFT]; }

      inline Node *&right() noexcept { return children[RIGHT]; }

      inline Node *const &right() const noexcept { return children[RIGHT]; }

      static constexpr std::array<Node *, 2> NO_CHILD{nullptr, nullptr};
   };

   //------------------Balancing functions
   template<typename Key>
   void calculateHeight (Node<Key>* const& n);

   template<typename Key>
   void rotate(Node<Key> *&n, Side s);

    template<typename Key>
   int balanceValue(Node<Key>* const& n);

   template<typename Key>
   void restoreBalance(Node<Key>*& n);

   //-------------------------------------------
   template<typename Key>
   Key const &minMax(Node<Key> *n, Side s);

   template<typename Key>
   void deleteNode(Node<Key> *&n, Side s);

   template<typename Key>
   Node<Key>* extractMin(Node <Key> *&n);

   template<typename Key>
   void deleteKey(Node <Key> *&n, Key k);

   template<typename Key>
   void insertSubtreeAndBalance(Node<Key> *&n, Key const &k);

   template<typename Key>
   std::ostream &showIndented(Node<Key> *n,
										std::ostream &out = std::cout,
										std::string before = "",
										bool isright = false);

   template<typename Key>
   void copy(Node<Key> *&n1, Node<Key> *const &n2);

   template<typename Key>
   bool exist(Node<Key>* const& n, const Key & k) noexcept;

   template<typename Key>
   void destructor(Node<Key> *&node);
   
   template<typename Key>
   std::ostream &display(Node<Key> const *n, std::ostream &os);
}
#include "avlNodeImplementation.h"
#endif //ASD_LABS_2021_AVLNODE_H
