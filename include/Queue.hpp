#ifndef QUEUE_HPP
#define QUEUE_HPP

template <class T>
class Queue {
  public:
    virtual ~Queue() {
    }

    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& front() = 0;
    virtual T& back() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};

#endif /* QUEUE_HPP */
