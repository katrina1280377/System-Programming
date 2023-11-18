// Copyright 2023 <Wei-Mei(Katrina) Hsiung>
// Email: whsiung@uw.edu
#ifndef LINKEDINTLIST_H_
#define LINKEDINTLIST_H_

#include <memory>
#include "IntList.h"

using std::shared_ptr;
using std::weak_ptr;

namespace intlist333 {

// LinkedIntList is an implementation of
// the IntList abstract class. Implemented using
// a doubly linked list
class LinkedIntList : public IntList{
 public:
  // deafault constructor
  LinkedIntList(): num_elements_(0), head_(nullptr), tail_() { }

  // explicitly disable
  LinkedIntList(const LinkedIntList& other) = delete;
  LinkedIntList& operator=(const LinkedIntList& other) = delete;

  // Destructor should be kept default
  // since smart pointers should clean
  // everything up for us
  virtual ~LinkedIntList() { }

  int num_elements() const override { return num_elements_; }
  void Push(const int value) override;
  void Append(const int value) override;
  bool Pop(int* const ptr) override;
  bool Slice(int* const ptr) override;

 private:
  int num_elements_;
  // Note that these should be modified
  // to use smart pointers at some point
  struct Node {
    int payload;
    shared_ptr<Node> next;
    weak_ptr<Node> prev;
  };
  shared_ptr<Node> head_;
  weak_ptr<Node> tail_;
};

}  // namespace intlist333

#endif  // LINKEDINTLIST_H_
