#include <iostream>
#include <memory>
#include <functional>

#include "FileOld.h"
#include "FileNew.h"

/*
 * 传统的虚函数实现运行时多态的方法
 * 不具备 ABI 兼容性
 */
void virtualFunctionMethod()
{
    // 常规做法，父类指针指向子类对象
    std::shared_ptr<FileOld> file = std::make_shared<FtpFile>();
    file->open(0);
    file->close(0);
}

/*
 * 使用 pimpl+std::bind+std::function 的方法来保证
 * ABI 兼容性
 */
void abiMethod()
{
    // 父类指针不再需要指向子类对象
    std::shared_ptr<FileNew> file = std::make_shared<FileNew>();

    // 手动绑定，实现多态
    using namespace std::placeholders;
    std::shared_ptr<MTPFile> mtp = std::make_shared<MTPFile>();
    file->registerOpen(std::bind(&MTPFile::open, mtp, _1));
    file->registerClose(std::bind(&MTPFile::close, mtp, _1));
    file->registerRead(std::bind(&MTPFile::read, mtp, _1, _2));

    file->open(0);
    file->close(0);
    file->read(0, nullptr);
}

int main() {
    std::cout << "start virtualFunctionMethod\n";
    virtualFunctionMethod();
    std::cout << "end virtualFunctionMethod\n";

    std::cout << "start abiMethod\n";
    abiMethod();
    std::cout << "end abiMethod\n";

    return 0;
}
