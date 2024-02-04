#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <mutex>
#include <condition_variable>
#include <deque>



template <typename T>
class MessageQueue {
    public:
        MessageQueue();
        void send(T const& msg);
        T receive();
    private:
        static MessageQueue<T> instance;
        std::mutex _mutex;
        std::condition_variable _cond;
        std::deque<T> _queue;
};



template <typename T>
MessageQueue<T>::MessageQueue() {}

template <typename T>
T MessageQueue<T>::receive() {
  // perform queue modification under the lock
  std::unique_lock<std::mutex> uLock(_mutex);
  _cond.wait(uLock, [this] { return !_queue.empty(); }); // pass unique lock to condition variable
  T msg = std::move(_queue.front()); // get message
  _queue.pop_front();
  return msg;
}

template <typename T>
void MessageQueue<T>::send(const T &msg) {
    std::lock_guard<std::mutex> uLock(_mutex);
    _queue.push_back(std::move(msg));
    _cond.notify_one(); // notify client after pushing new message
}

#endif
