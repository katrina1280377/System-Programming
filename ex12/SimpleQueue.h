// Copyright 2023 <Copyright Owner>
// Name: Wei-Mei(Katrina) Hsiung, Email: whsiung@uw.edu

#ifndef SIMPLEQUEUE_H_
#define SIMPLEQUEUE_H_

#include <string>
#include <memory>

// A simple FIFO queue class that stores strings
// Your task: Make SimpleQueue thread safe!
class SimpleQueue {
 public:
  SimpleQueue();

  ~SimpleQueue();

  // Enqueues the given item
  void Enqueue(const std::string& item);

  // Dequeues the item at the front of the queue
  // and stores it at the location pointed to by result.
  // Returns true if there was an item to return and
  // false if the queue was empty.
  bool Dequeue(std::string* const result);

  // Returns the size of the queue
  int Size() const;

  // Returns true if the queue if empty, false otherwise
  bool IsEmpty() const;

 private:
  struct Node {
    std::string item;
    std::shared_ptr<Node> next;
  };
  std::shared_ptr<Node> front_;
  std::shared_ptr<Node> end_;
  int size_;
  mutable pthread_mutex_t mtx_;
};  // class SimpleQueue

#endif  // SIMPLEQUEUE_H_
