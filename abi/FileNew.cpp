//
// Created by zhangs on 2021/8/1.
//

#include "FileNew.h"

#include <iostream>

class FileNew::Impl {
public:
    std::function<int (int)> openFunc;
    std::function<int (int)> closeFunc;
    std::function<int (int, char *)> readFunc;
};

FileNew::FileNew() : impl(new Impl) {}

int FileNew::open(int fd) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (impl && impl->openFunc)
        return impl->openFunc(fd);
    return 0;
}

int FileNew::close(int fd) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (impl && impl->closeFunc)
        return impl->closeFunc(fd);
    return 0;
}

int FileNew::read(int fd, char *buf) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (impl && impl->readFunc)
        return impl->readFunc(fd, buf);
    return 0;
}

void FileNew::registerOpen(const FileNew::OpenFunc &func) {
    impl->openFunc = func;
}

void FileNew::registerClose(const FileNew::CloseFunc &func) {
    impl->closeFunc = func;
}

void FileNew::registerRead(const FileNew::ReadFunc &func) {
    impl->readFunc = func;
}

int MTPFile::open(int fd) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 0;
}

int MTPFile::close(int fd) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 0;
}

int MTPFile::read(int fd, char *buf) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 0;
}

