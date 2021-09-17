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
#include "message.h"
#include "message_p.h"

#include <QDebug>
#include <QVariant>
#include <QtConcurrent>

using namespace message;

Sender::Sender(const QString &id)
    : messageId(id)
{

}

message::Result Sender::send(const QVariantList &params)
{
    Result ret {false, QVariant()};

    auto &&receivers = MessageManager::instance().allReceivers;
    if (!receivers.contains(messageId))
        return ret;

    auto receiver = receivers.value(messageId);
    if (!receiver)
        return ret;

    ret.r = true;
    ret.v = receiver->callback()(params);

    return ret;
}

message::Future Sender::asyncSend(const QVariantList &params)
{
    QThreadPool *pool = message::threadPool;

    if (pool->maxThreadCount() <= pool->activeThreadCount())
        pool->setMaxThreadCount(pool->maxThreadCount() + 2);

    using type = message::Result(message::Sender::*)(const QVariantList &);
    return message::Future(QtConcurrent::run(pool, this, static_cast<type>(&Sender::send), params));
}


Receiver::Receiver(const QString &id) :
    messageId(id)
{

}

Receiver::~Receiver()
{
   unbind();
}

QString Receiver::id() const
{
    return messageId;
}

std::function<QVariant (const QVariantList &)> Receiver::callback() const
{
    return func;
}

void Receiver::unbind()
{
    MessageManager::instance().unregisterReceiver(messageId);
}

bool Receiver::doBind()
{
    return MessageManager::instance().registerReceiver(messageId, this);
}

Future::Future(const QFuture<Result> &future)
    : curFuture(future)
{

}

void Future::cancel()
{
    curFuture.cancel();
}

bool Future::isCanceled() const
{
    return curFuture.isCanceled();
}

bool Future::isStarted() const
{
    return curFuture.isStarted();
}

bool Future::isFinished() const
{
    return curFuture.isFinished();
}

bool Future::isRunning() const
{
    return curFuture.isRunning();
}

void Future::waitForFinished()
{
    curFuture.waitForFinished();
}

Result Future::result() const
{
    return curFuture.result();
}
