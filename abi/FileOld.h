//
// Created by zhangs on 2021/8/1.
//

#ifndef ABI_FILEOLD_H
#define ABI_FILEOLD_H


class FileOld {
public:
    virtual int open(int fd) = 0;
    virtual int close(int fd) = 0;

    // 新增虚函数接口，必然破坏 ABI
    // virtual int read(int fd, char *buf) = 0;
};

/*
 * 通过重写虚函数完成扩展
 */
class FtpFile: public FileOld {
public:
    int open(int fd) override;
    int close(int fd) override;
};


#endif //ABI_FILEOLD_H
