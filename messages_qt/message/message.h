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

#include <QMap>
#include <QPointer>
#include <QFuture>

#include <functional>

namespace message {

struct Result {
    bool r;
    QVariant v;
};

class Future {
public:
    explicit Future(const QFuture<message::Result> &future);

    void cancel();
    bool isCanceled() const;

    bool isStarted() const;
    bool isFinished() const;
    bool isRunning() const;

    void waitForFinished();
    message::Result result() const;

private:
    QFuture<message::Result> curFuture;
};

class Sender final
{
public:
    explicit Sender(const QString &id);

    message::Result send();
    message::Result send(const QVariantList &params);
    template <class T, class ...Args>
    inline message::Result send(T param, Args&& ...args) {
        QVariantList ret;
        makeVariantList(&ret, param, std::forward<Args>(args)...);
        return send(ret);
    }

    message::Future asyncSend();
    message::Future asyncSend(const QVariantList &params);
    template <class T, class ...Args>
    inline message::Future asyncSend(T param, Args&& ...args) {
        QVariantList ret;
        makeVariantList(&ret, param, std::forward<Args>(args)...);
        return asyncSend(ret);
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

    void unbind();

    template <class T, class Func>
    inline bool rebind(T *obj, Func method) {
        static_assert(std::is_base_of<QObject, T>::value, "Template type T must be derived QObject");
        static_assert(!std::is_pointer<T>::value, "Receiver::bind's template type T must not be a pointer type");
        unbind();
        return bind(obj, method);
    }
private:
    bool doBind();

private:
    QString messageId;
    std::function<QVariant(const QVariantList&)> func;
};
} // namespace message

#endif // MESSAGE_H
