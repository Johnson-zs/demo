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
#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QObject>
#include <QtConcurrent>

class EventHandlerPrivate;
class Event;
class EventHandler : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(EventHandler)

    QSharedPointer<const EventHandlerPrivate> d;
public:
    enum class Type :  uint8_t
    {
        Synch,
        Asynch
    };

    /**
     * @brief EventHandler 构造函数
     */
    explicit EventHandler();

    /**
     * @brief processType 必须重载实现的获取Handler的处理类型
     * @return 处理的类型
     *  Type::Synch 表示同步
     *  Type::Asynch 表示异步
     */
    virtual Type processType() = 0;

    /**
     * @brief eventProcess 事件处理入口
     */
    virtual void eventProcess(const Event&) = 0;

Q_SIGNALS:
    void handError(const QString &error);
    void handInfo(const QString &info);
};

/**
 * @brief The SynchEventHandler class
 *  同步处理类，禁止多重继承（二义性互斥），该类禁止更改
 */
class SyncEventHandler : virtual public EventHandler
{
    Q_OBJECT
public:
    virtual Type processType() override
    {
        return EventHandler::Type::Synch;
    }
    /**
     * @brief eventProcess
     *  该函数将遵循回调函数进行调用
     * @param event
     */
    virtual void eventProcess(const Event &event) override
    {
        Q_UNUSED(event);
        // 内部可存在异步线程进行同步处理提速
        // QtConcurrent::map等
        // auto controller = QtConcurrent::run([=](){
        //      出现处理错误 可使用 emit handError("what?");
        //      外抛信息可使用 emit handInfo("");
        //      dpfCritical() << event;
        // });
        // 阻塞同步，否则将导致同步未定义行为
        // controller.waitForFinished();
    }
};

/**
 * @brief The SynchEventHandler class
 *  异步同步处理类，禁止多重继承（二义性互斥），该类禁止更改
 */
class AsyncEventHandler : virtual public EventHandler
{
    Q_OBJECT
public:
    virtual Type processType() override
    {
        return EventHandler::Type::Asynch;
    }

    /**
     * @brief eventProcess
     *  该函数将被放在异步线程中抛出
     *  阻塞主界面的耗时操作
     * @param event 传递的事件
     */
    virtual void eventProcess(const Event &event) override
    {
        Q_UNUSED(event);
        //禁用QWidget树族在该函数中操作
    }
};

#endif // EVENTHANDLER_H
