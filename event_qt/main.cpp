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

#include <QCoreApplication>
#include <QDebug>

#include "event/eventcallproxy.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Event e("WindowEvent");
    e.setData("123");
    e.setProperty("aa", "bb");
    EventCallProxy::pubEvent(e);

    Event e2("FileEvent");
    e2.setData("12345");
    e2.setProperty("aa", "bb");
    EventCallProxy::pubEvent(e2);
    EventCallProxy::pubEvent(e);

    EventCallProxy::removeHandler("WindowEventHandler");
    EventCallProxy::removeAllHandlers();
    return a.exec();
}

