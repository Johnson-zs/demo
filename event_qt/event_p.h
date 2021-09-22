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
#ifndef EVENT_P_H
#define EVENT_P_H

#include "event.h"

#include <QString>
#include <QVariant>

class EventPrivate
{
    friend class Event;
    Event *const q;
    QHash<QString,QVariant> sourceHash;
    friend Q_CORE_EXPORT QDebug operator <<(QDebug, const Event &);
public:

    explicit EventPrivate(Event *qq)
        : q(qq)
    {

    }
};


#endif // EVENT_P_H
