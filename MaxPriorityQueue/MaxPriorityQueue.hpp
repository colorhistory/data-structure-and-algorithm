#ifndef MAXPRIORITYQUEUE_HPP
#define MAXPRIORITYQUEUE_HPP

namespace DSAA {

    template <typename T>
    class MaxPriorityQueue {
      public:
        virtual ~MaxPriorityQueue() {
        }

        // ADT
        virtual bool empty() const = 0;
        virtual int size() const = 0;
        virtual const T& top() = 0;
        virtual void pop() = 0;
        virtual void push(const T& theElement) = 0;
    };

}  // namespace DSAA
#endif  // MAXPRIORITYQUEUE_HPP
