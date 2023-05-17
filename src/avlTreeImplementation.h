#ifndef ASD_2021_AVL_IMPL_H
#define ASD_2021_AVL_IMPL_H

#include <utility>
#include <algorithm>

template<typename Key>
avlTree<Key>::avlTree() : root(nullptr) {
}

template<typename Key>
avlTree<Key>::avlTree(avlTree const &other) : root(nullptr){
   copy(root,other.root);
}

template<typename Key>
avlTree<Key>::~avlTree() {
   destructor(this->root);
   root = nullptr;
}

template<typename Key>
avlTree<Key>& avlTree<Key>::operator=(const avlTree<Key> &other){
    if(this != &other) {
        avlTree tmp(other);
        std::swap(this->root, tmp.root);
    }
    return *this;
}

template<typename Key>
void avlTree<Key>::insert(Key const& k) {
	avl::insertSubtreeAndBalance(root, k);
}

template<typename Key>
std::ostream& avlTree<Key>::show_indented(std::ostream& os) const {
    return avl::showIndented(root, os);
}

template<typename Key>
std::ostream &operator<<(std::ostream & out, avlTree<Key> const & tree) {
   return avl::display(tree.root, out);
}
template<typename Key>
bool avlTree<Key>::contains(Key const& k) const noexcept
{
   return avl::exist(this->root, k);
}

template<typename Key>
Key const& avlTree<Key>::min() const{
   return avl::minMax(this->root, avl::LEFT);
}

template<typename Key>
Key const& avlTree<Key>::max() const{
   return avl::minMax(this->root, avl::RIGHT);
}

template<typename Key>
void avlTree<Key>::erase_min(){
   avl::deleteNode(this->root, avl::LEFT);
}

template<typename Key>
void avlTree<Key>::erase_max(){
   avl::deleteNode(this->root, avl::RIGHT);
}

template<typename Key>
void avlTree<Key>::erase (Key const& k) noexcept{
   avl::deleteKey(this->root, k);
}

template<typename Key>
[[nodiscard]] unsigned char avlTree<Key>::height() const noexcept{
   return avl::getNodeHeight(this->root);
}

#endif //ASD_2021_AVL_IMPL_H
