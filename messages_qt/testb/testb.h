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
#ifndef TESTB_H
#define TESTB_H

#include <QObject>

namespace message {
class Receiver;
} // namespace message

class TestB: public QObject
{
    Q_OBJECT
public:
    TestB(QObject *parent = nullptr);
    ~TestB();

    Q_SIGNAL void testSig(int a, int b);

    Q_SLOT void testSlot();
    Q_SLOT qint64 testSlot2(int a, double b);
    Q_SLOT qint64 testSlot3(int a, double b, const QString &str);

};


#endif // TESTB_H
