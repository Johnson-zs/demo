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
#ifndef WINDOWEVENTHANDLER_H
#define WINDOWEVENTHANDLER_H

#include "event/eventcallproxy.h"

class WindowEventHandler: public EventHandler, AutoEventHandlerRegister<WindowEventHandler>
{
    Q_OBJECT

public:
    WindowEventHandler(): AutoEventHandlerRegister<WindowEventHandler>() {}

    static EventHandler::Type type()
    {
        return EventHandler::Type::Sync;
    }

    static QStringList topics()
    {
         return QStringList() << "WindowEvent";
    }

    void eventProcess(const Event&) override;

    Q_SIGNAL void testSignal(const Event&);
    Q_SLOT void slotEventProcess(const Event&);

};

#endif // WINDOWEVENTHANDLER_H
