TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../include

SOURCES += main.cpp

HEADERS += \
    BinaryTree.hpp \
    BinaryTreeNode.hpp \
    LinkedBinaryTree.hpp \
    Booster.hpp
