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
#ifndef EVENTCALLPROXY_H
#define EVENTCALLPROXY_H

#include "eventhandler.h"
#include "event.h"

#include <QObject>
#include <QMutex>
#include <QDebug>

#include <functional>
#include <memory>

class EventCallProxy final
{
    template <typename T>
    friend class AutoEventHandlerRegister;
    struct HandlerInfo;
    using CreateFunc = std::function<EventHandler*()> ;
    using ExportFunc = std::function<void(HandlerInfo &info, const Event &event)>;

    struct HandlerInfo
    {
        QString className;
        EventHandler* handler {nullptr};
        ExportFunc invoke;
        QStringList topics;
        QFuture<void> future;
    };

public:
    EventCallProxy() = delete;
    inline static bool pubEvent(const Event& event)
    {
        bool flag = false;
        for (HandlerInfo &info : getInfoList()) {
            if (!info.topics.contains(event.topic()))
                continue;
            if (Q_LIKELY(info.invoke)) {
                info.invoke(info, event);
                flag = true;
            }
        }
        return flag;
    }

    inline static bool removeHandler(const QString &className)
    {
        QMutexLocker locker(eventMutex());
        auto &infoList = getInfoList();
        auto iter = infoList.begin();
        int i = 0;
        bool flag = false;
        while (iter != infoList.end()) {
            if (iter->className == className) {
                if (iter->future.isRunning())
                    iter->future.waitForFinished();
                if (iter->handler) {
                    delete iter->handler;
                    iter->handler = nullptr;
                }
                flag = true;
                break;
            }
            ++i;
        }

        if (flag)
            infoList.removeAt(i);
        return flag;
    }

    inline static void removeAllHandlers()
    {
        QMutexLocker locker(eventMutex());
        auto &infoList = getInfoList();
        auto iter = infoList.begin();
        while (iter != infoList.end()) {
            if (iter->future.isRunning())
                iter->future.waitForFinished();
            if (iter->handler) {
                delete iter->handler;
                iter->handler = nullptr;
            }
        }
        infoList.clear();
    }

    inline static void registerHandler(EventHandler::Type type, const QStringList &topics, CreateFunc creator)
    {
        QMutexLocker locker(eventMutex());
        auto &infoList = getInfoList();
        ExportFunc invoke {nullptr};
        if (type == EventHandler::Type::Sync) {
            invoke = [creator] (HandlerInfo &info, const Event &event) {
                fillInfo(info, creator);
                info.handler->eventProcess(event);
            };
        }

        if (type ==  EventHandler::Type::Async) {
            invoke = [creator] (HandlerInfo &info, const Event &event) {
                fillInfo(info, creator);
                info.future = QtConcurrent::run(info.handler, &EventHandler::eventProcess, event);
            };
        }

        infoList.append(HandlerInfo{"", nullptr, invoke, topics});
    }

private:
    inline static QList<HandlerInfo> &getInfoList()
    {
        static QList<HandlerInfo> eventHandlers;
        return eventHandlers;
    }

    inline static void fillInfo(HandlerInfo &info, CreateFunc creator)
    {
        if (!info.handler) {
            info.handler = creator();
            info.className = info.handler->metaObject()->className();
        }
    }

    inline static QMutex *eventMutex()
    {
        static QMutex mutex;
        return &mutex;
    }
};

// auto register all event handler
template <typename T>
bool AutoEventHandlerRegister<T>::isRegistered = AutoEventHandlerRegister<T>::trigger();
template <typename T>
bool AutoEventHandlerRegister<T>::trigger()
{
    EventCallProxy::registerHandler(T::type(), T::topics(), [] { return new T(); });
    return true;
}

#endif // EVENTCALLPROXY_H
