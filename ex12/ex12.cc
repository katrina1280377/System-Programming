// Copyright 2023 <Copyright Owner>
// Name: Wei-Mei(Katrina) Hsiung, Email: whsiung@uw.edu

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <string>
#include <ctime>
#include <pthread.h>
#include "SimpleQueue.h"

using std::cout;
using std::endl;
using std::string;
using std::thread;
using std::cerr;

static constexpr int kNumSnacks = 6;
static SimpleQueue queue;
static unsigned int seed = time(nullptr);
static pthread_mutex_t write_lock;

// Thread safe print that prints the given str on a line
void thread_safe_print(const string& str) {
  pthread_mutex_lock(&write_lock);
  // Only one thread can hold the lock at a time, making it safe to
  // use cout. If we didn't lock before using cout, the order of things
  // put into the stream could be mixed up.
  cout << str << endl;
  pthread_mutex_unlock(&write_lock);
}

// Produces kNumSnacks snacks of the given type
// You should NOT modify this method at all
void producer(const string& snack_type) {
  for (int i = 0; i < kNumSnacks; i++) {
    queue.Enqueue(snack_type);
    thread_safe_print(snack_type + " ready!");
    int sleep_time = rand_r(&seed) % 500 + 1;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  }
}

// Eats 2 * kNumSnacks snacks
// You should NOT modify this method at all
void consumer() {
  for (int i = 0; i < kNumSnacks * 2; i++) {
    bool successful = false;
    string snack_type;
    while (!successful) {
      while (queue.IsEmpty()) {
        // Sleep for a bit and then check again
        int sleep_time = rand_r(&seed) % 800 + 1;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      }
      successful = queue.Dequeue(&snack_type);
    }
    thread_safe_print(snack_type + " eaten!");
  }
}

void* consumer_start(void* arg) {
  consumer();
  return nullptr;
}

void* producer_start(void* arg) {
  producer(*(reinterpret_cast<string*>(arg)));
  return nullptr;
}

int main(int argc, char** argv) {
  srand(time(nullptr));
  pthread_mutex_init(&write_lock, nullptr);
  // Your task: Make the two producers and the single consumer
  // all run concurrently (hint: use pthreads)
  string snack1 = "piroshki";
  string snack2 = "nalysnyky";
  pthread_t pthd1, pthd2, cthd;
  if (pthread_create(&pthd1, nullptr,
                     producer_start, &snack1) != 0) {
    cerr << "Piroshki producer pthread_create failed!";
  }
  if (pthread_create(&pthd2, nullptr,
                     producer_start, &snack2) != 0) {
    cerr << "Nalysnyky producer pthread_create failed!";
  }
  if (pthread_create(&cthd, nullptr, consumer_start, nullptr) != 0) {
    cerr << "Consumer pthread_create failed!" << endl;
  }

  if (pthread_join(pthd1, nullptr) != 0) {
    cerr << "Piroshki producer pthread_join failed!";
  }
  if (pthread_join(pthd2, nullptr) != 0) {
    cerr << "Nalysnyky producer pthread_join failed!";
  }
  if (pthread_join(cthd, nullptr) != 0) {
    cerr << "Consumer pthread_join failed!" << endl;
  }
  pthread_mutex_destroy(&write_lock);
  return EXIT_SUCCESS;
}
