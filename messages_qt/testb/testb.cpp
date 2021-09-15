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
#include "testb.h"
#include "message.h"

#include <QDebug>


TestB::TestB(QObject *parent)
    : QObject (parent)
{

}

TestB::~TestB()
{
    if (r)
        delete r;
}

void TestB::subMessage(const QString &id)
{
    r = new message::Receiver(id);
    r->bind(this, &TestB::testSlot);
}

qint64 TestB::testSlot(int a, double b)
{
    return a + static_cast<qint64>(b);
}

qint64 TestB::testSlot1(int a, double b, const QString &str)
{
    qDebug() << str;
    return a + static_cast<qint64>(b);
}
