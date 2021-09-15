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
#ifndef MESSAGE_H
#define MESSAGE_H

#include "invokehelper.h"
#include "messagehelper.h"

#include <QDebug>
#include <QSet>
#include <QMap>

#include <functional>

namespace message {

class Sender final
{
public:
    struct Result {
        bool r;
        QVariant v;
    };

public:
    explicit Sender(const QString &id);

    Result send(const QVariantList &params);
    void post(const QVariantList &params);

    template <class T, class ...Args>
    inline Result send(T param, Args&& ...args) {
        QVariantList ret;
        makeVariantList(&ret, param, args...);
        return send(ret);
    }

    template <class T, class ...Args>
    inline void post(T param, Args&& ...args) {
        QVariantList ret;
        makeVariantList(&ret, param, args...);
        return post(ret);
    }

private:
    template <class T, class ...Args>
    inline static void makeVariantList(QVariantList *list, T t, Args&& ...args) {
        *list << t;
        if constexpr (sizeof ...(args) > 0)
            packParamsHelper(*list, std::forward<Args>(args)...);
    }

private:
    QString messageId;
};

class Receiver final
{
    Q_DISABLE_COPY(Receiver)
public:
    explicit Receiver(const QString &id);
    ~Receiver();
    QString id() const;
    std::function<QVariant(const QVariantList&)> callback() const;

    template <class T, class Func>
    inline bool bind(T *obj, Func method) {
        static_assert(std::is_base_of<QObject, T>::value, "Template type T must be derived QObject");
        static_assert(!std::is_pointer<T>::value, "Receiver::bind's template type T must not be a pointer type");
        func = [obj, method] (const QVariantList& args)->QVariant {
            MessageHelper<decltype(method)> helper = (MessageHelper<decltype(method)>(obj, method));
            return helper.invoke(args);
        };

        return doBind();
    }

private:
    bool doBind();

private:
    QString messageId;
    std::function<QVariant(const QVariantList&)> func; // 最终接收 message 参数并执行的函数
};
} // namespace message

#endif // MESSAGE_H
