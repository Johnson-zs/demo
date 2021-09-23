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

class Event;
class EventHandler : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(EventHandler)

public:
    /*!
     * \brief You should derived the class, and
     * write a static function named type that returns `Type`
     *
     * // for example:
     * static Type type()
     * {
     *     assert(!registered!;
     *     return EventHandler::Sync;
     * }
     *
     */
    enum class Type : uint8_t
    {
        Sync,
        Async
    };

    /**
     * @brief EventHandler 构造函数
     */
    explicit EventHandler(QObject *parent = nullptr);
    virtual ~EventHandler() {}

    /**
     * @brief eventProcess 事件处理入口
     */
    virtual void eventProcess(const Event&) = 0;

    // TODO:
Q_SIGNALS:
    void handError(const QString &error);
    void handInfo(const QString &info);
};


template <typename T>
class AutoEventHandlerRegister
{
public:
    AutoEventHandlerRegister()
    {
        // must keep it!!!
        // Otherwise `trigger` will not be called !
        qDebug() << isRegistered;
    }

    static bool trigger();

private:
    static bool isRegistered;
};

// for example:

/*!
 * class WindowEventHandler: public EventHandler, AutoEventHandlerRegister<WindowEventHandler>
 * {
 *     Q_OBJECT
 *
 * public:
 *     static EventHandler::Type type()
 *     {
 *         assert(!registered!;
 *         return EventHandler::Type::Sync;
 *     }
 *
 *     static QStringList topics()
 *     {
 *          return "WindowEvent";
 *     }
 *
 *     void eventProcess(const Event&) override
 *     {
 *          do something..
 *     }
 * };
 */
#endif // EVENTHANDLER_H
