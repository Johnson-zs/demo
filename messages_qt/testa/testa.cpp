/*
 * Copyright (C) 2020 ~ 2021 Uniontech Software Technology Co., Ltd.
 *
 * Author:     zhangsheng<zhangsheng@uniontech.com>
 *
 * Maintainer: max-lv<lvwujun@uniontech.com>
 *             lanxuesong<lanxuesong@uniontech.com>
 *             xushitong<xushitong@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "testa.h"
#include "message.h"

#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <QDebug>

static const QString MsgId = "test_id";

TestA::TestA(QObject *parent)
    : QObject (parent)
{

}
void TestA::sync()
{
    message::Sender sender(MsgId);
    auto ret = sender.send(1, 2, 3);
    qDebug() << ret.r << ret.v;
//    QMap<QString, QVariant> map;
//    map["a"] = 11;
//    map["b"] = 22;
//    message::Sender sender(MsgId);
//    auto v = sender.send(map, 5, "123", 123, 2);
//    sender.send("fe");

//    QVariantList list;
//    list << "aaa" << 5 << 2.58;
//    sender.send(list);
//    QString teststr("asasfwegger");
//    const QString &ref = teststr;
//    sender.send(ref);

//    sender.post(5, "123", 123, 2);
//    sender.post("fe");
//    sender.post(list);

//    pid_t fd = fork();
//    if (fd == 0) {
//        qDebug() << "child";
//    } else if (fd > 0) {

//    } else {
//        abort();
//    }

//    int status;
    //    waitpid(-1, &status, WNOHANG);
}

void TestA::async()
{
    message::Sender sender(MsgId);
    auto future = sender.asyncSend(1, 2, 3);
    future.waitForFinished();
    auto ret = future.result();
    qDebug() << ret.r << ret.v;
}
