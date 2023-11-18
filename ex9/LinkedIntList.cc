// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu
#include "LinkedIntList.h"
#include <memory>

namespace intlist333 {
  // Insert from head
  void LinkedIntList::Push(const int value) {
    shared_ptr<Node> node(new Node);
    node->payload = value;
    if (this->num_elements() == 0) {
        this->head_ = node;
        this->tail_ = node;
        node->next.reset();
        node->prev.reset();
    } else {
        node->next = this->head_;
        node->prev.reset();
        this->head_ = node;
    }
    this->num_elements_++;
  }
  // Insert from tail
  void LinkedIntList::Append(const int value) {
    shared_ptr<Node> node(new Node);
    node->payload = value;
    if (this->num_elements() == 0) {
        this->Push(value);
    } else {
        node->prev = this->tail_;
        node->next.reset();
        this->tail_.lock()->next = node;
        this->tail_ = node;
        this->num_elements_++;
    }
  }
  // Remove from head
  bool LinkedIntList::Pop(int* const ptr) {
    // empty linkedlist
    if (this->num_elements() == 0) {
        return false;
    }
    *ptr = this->head_->payload;
    if (this->num_elements() == 1) {
        this->head_.reset();
        this->tail_.reset();
    } else {
        this->head_ = this->head_->next;
    }
    this->num_elements_--;
    return true;
  }
  // Remove from tail
  bool LinkedIntList::Slice(int* const ptr) {
    // empty linkedlist
    if (this->num_elements() <= 0) {
        return this->Pop(ptr);
    }
    shared_ptr<Node> tail = this->tail_.lock();
    *ptr = tail->payload;
    this->tail_ = tail->prev;
    this->num_elements_--;
    return true;
  }
}   // namespace intlist333
