//
// Created by zhangs on 2021/8/1.
//

#ifndef ABI_FILENEW_H
#define ABI_FILENEW_H

#include <memory>
#include <functional>

class FileNew {
public:
    using OpenFunc  = std::function<int (int)>;
    using CloseFunc = std::function<int (int)>;
    using ReadFunc  = std::function<int (int, char *)>;

public:
    // 构造函数初始化 imp;
    FileNew();

    // 不再以虚函数方式进行扩展
    int open(int fd);
    int close(int fd);

    // 新增的接口也直接写普通的成员函数接口，不会破坏 ABI
    int read(int fd, char *buf);

    // 注册接口，手动实现多态
    void registerOpen(const OpenFunc &func);
    void registerClose(const CloseFunc &func);
    void registerRead(const ReadFunc &func);

private:
    class Impl;
    std::shared_ptr<Impl> impl;
};

/*
 * 假设 MTP 协议有自己的实现, 此处也不再不需要继承
 */
class MTPFile {
public:
    int open(int fd);
    int close(int fd);
    int read(int fd, char *buf);
};


#endif //ABI_FILENEW_H
