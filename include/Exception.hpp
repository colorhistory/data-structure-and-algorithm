#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <iostream>
#include <string>

namespace DSAA {

    /*!
     * \brief The illegalParameterValue class
     */
    class IllegalParameterValue {
      public:
        IllegalParameterValue(std::string theMessage = "Illegal parameter value") {
            message = theMessage;
        }
        void what() {
            std::cout << message << std::endl;
        }

      private:
        std::string message;
    };

    /*!
     * \brief The illegalInputData class
     */
    class IllegalInputData {
      public:
        IllegalInputData(std::string theMessage = "Illegal data input") {
            message = theMessage;
        }
        void what() {
            std::cout << message << std::endl;
        }

      private:
        std::string message;
    };

    /*!
     * \brief The illegalIndex class
     */
    class IllegalIndex {
      public:
        IllegalIndex(std::string theMessage = "Illegal index") {
            message = theMessage;
        }
        void what() {
            std::cout << message << std::endl;
        }

      private:
        std::string message;
    };

    /*!
     * \brief The MatrixIndexOutOfBounds class
     */
    class MatrixIndexOutOfBounds {
      public:
        MatrixIndexOutOfBounds(std::string theMessage = "Matrix index out of bounds") {
            message = theMessage;
        }
        void what() {
            std::cout << message << std::endl;
        }

      private:
        std::string message;
    };

    /*!
     * \brief The MatrixSizeMismatch class
     */
    class MatrixSizeMismatch {
      public:
        MatrixSizeMismatch(std::string theMessage = "The size of the two matrics doesn't match") {
            message = theMessage;
        }
        void what() {
            std::cout << message << std::endl;
        }

      private:
        std::string message;
    };

    /*!
     * \brief The stackEmpty class
     */
    class StackEmpty {
      public:
        StackEmpty(std::string theMessage = "Invalid operation on empty stack") {
            message = theMessage;
        }
        void what() {
            std::cout << message << std::endl;
        }

      private:
        std::string message;
    };

    /*!
     * \brief The QueueEmpty class
     */
    class QueueEmpty {
      public:
        QueueEmpty(std::string theMessage = "Invalid operation on empty queue") {
            message = theMessage;
        }
        void what() {
            std::cout << message << std::endl;
        }

      private:
        std::string message;
    };

    /*!
     * \brief The HashTableFull class
     */
    class HashTableFull {
      public:
        HashTableFull(std::string theMessage = "The hash table is full") {
            message = theMessage;
        }
        void what() {
            std::cout << message << std::endl;
        }

      private:
        std::string message;
    };

    /*!
     * \brief The UndefinedEdgeWeight class
     */
    class UndefinedEdgeWeight {
      public:
        UndefinedEdgeWeight(std::string theMessage = "No edge weights defined") {
            message = theMessage;
        }
        void what() {
            std::cout << message << std::endl;
        }

      private:
        std::string message;
    };

    /*!
     * \brief The UndefinedMethod class
     */
    class UndefinedMethod {
      public:
        UndefinedMethod(std::string theMessage = "This method is undefined") {
            message = theMessage;
        }
        void what() {
            std::cout << message << std::endl;
        }

      private:
        std::string message;
    };

}  // namespace DSAA
#endif /* EXCEPTION_HPP */
