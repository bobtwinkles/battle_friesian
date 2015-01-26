#ifndef _UTIL_TREE_H_
#define _UTIL_TREE_H_

#include <map>
#include <vector>
#include <cassert>

namespace fri {
  namespace util {
    template<typename KeyType, typename ValueType>
    class TreeNode {
      private:
        std::map<KeyType, TreeNode<KeyType, ValueType>* > _children;
        TreeNode<KeyType, ValueType> * _parent;
        ValueType _value;
        KeyType _key;

      public:
        TreeNode(KeyType Key, ValueType Value) {
          _key = Key;
          _value = Value;
          _parent = nullptr;
        }

        ~TreeNode() {
        }

        void AddChild(TreeNode<KeyType, ValueType> * Child) {
          Child->_parent = this;
          _children.insert(std::make_pair(Child->_key, Child));
        }

        TreeNode<KeyType, ValueType> * GetChild(KeyType K) {
          auto a = _children.find(K);
          if (a == _children.end()) {
            return nullptr;
          }
          return a->second;
        }

        inline const KeyType & GetKey() const { return _key; }
        inline ValueType & GetValue() { return _value; }
        inline void SetValue(const ValueType & Value) { _value = Value; }
    };

    template<typename KeyType, typename ValueType>
    class Tree {
      private:
        TreeNode<KeyType, ValueType> _root;
        std::vector<TreeNode<KeyType, ValueType> *> _nodes;
      public:
        Tree(KeyType RootKey, ValueType RootValue) :
          _root(RootKey, RootValue) {
        }

        ~Tree() {
          for (auto i : _nodes) {
            delete i;
          }
        }

        ValueType * GetValueTerminator(KeyType * Keys, KeyType Terminator) {
          assert(Terminator);
          return GetValueCustom(Keys, [&] (int depth, TreeNode<KeyType, ValueType> current) { return Keys[depth] == Terminator; } );
        }

        TreeNode<KeyType, ValueType> * GetValueMaxKeys(KeyType * Keys, int MaxKeys) {
          assert(MaxKeys > 0);
          return GetValueCustom(Keys, [&] (int depth, TreeNode<KeyType, ValueType> current) { return depth == MaxKeys - 1; } );
        }

        // The Accept() function gets (current_depth, current_node)
        TreeNode<KeyType, ValueType> * GetValue(KeyType * Keys, bool (*Accept)(int, TreeNode<KeyType, ValueType>&)) {
          assert(Accept != nullptr);
          TreeNode<KeyType, ValueType> * current = &_root;
          TreeNode<KeyType, ValueType> * next;
          int depth = 0;
          while (!Accept(Keys, depth, *current) &&
                 (next = current->GetChild(Keys[depth]))) {
            current = next;
            ++depth;
          }
          if (!Accept(Keys, depth, current)) {
            return nullptr;
          } else {
            return current;
          }
        }

        // Abort is called to determine whether or not the next key as specified by Keys[arg0] should be inserted
        //   arg1 is the prospective parent of the current node.
        //   should return true if arg0[arg1] should not be inserted
        // ValueFor is called to determine what value should be inserted for a given key (Keys[arg0])
        TreeNode<KeyType, ValueType> * Insert(KeyType * Keys, bool (*Abort)(int, TreeNode<KeyType, ValueType> &), ValueType & (*ValueFor)(int, TreeNode<KeyType, ValueType> &)) {
          assert(Abort != nullptr);
          assert(ValueFor != nullptr);
          TreeNode<KeyType, ValueType> * current = &_root;
          TreeNode<KeyType, ValueType> * next;
          int depth = 0;

          while (!Abort(depth, *current) &&
                 ((next = current->GetChild(Keys[depth])))) {
            current = next;
            ++depth;
          }

          if (Abort(depth, *current)) {
            return nullptr;
          }

          while (!Abort(depth, *current)) {
            next = new TreeNode<KeyType, ValueType>(Keys[depth], ValueFor(depth, *current));
            _nodes.push_back(next);
            current->AddChild(next);
            ++depth;
          }
        }
    };
  }
}

#endif
