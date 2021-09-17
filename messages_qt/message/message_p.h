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
#ifndef MESSAGE_P_H
#define MESSAGE_P_H

#include <QGlobalStatic>
#include <QMutexLocker>
#include <QHash>
#include <QThreadPool>

namespace message {

Q_GLOBAL_STATIC(QThreadPool, threadPool)

class Receiver;
class MessageManager final {
public:
    static MessageManager& instance();
    bool registerReceiver(const QString &id, message::Receiver *receiver);
    void unregisterReceiver(const QString &id);

    QMutex mutex;
    QHash<QString, message::Receiver*> allReceivers;
};
Q_GLOBAL_STATIC(message::MessageManager, manager)

MessageManager &MessageManager::instance()
{
    return *manager;
}

bool MessageManager::registerReceiver(const QString &id, Receiver *receiver)
{
    QMutexLocker locker(&mutex);

    if (allReceivers.contains(id))
        return false;

    allReceivers.insert(id, receiver);
    return true;
}

void MessageManager::unregisterReceiver(const QString &id)
{
    QMutexLocker locker(&mutex);

    if (allReceivers.contains(id))
        allReceivers.remove(id);
}

} // namespace message



#endif // MESSAGE_P_H
