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
#include <QApplication>
#include <QPointer>
#include <QDebug>
#include <QThread>
#include <benchmark/benchmark.h>

#include "event/eventcallproxy.h"
#include "windoweventhandler.h"

static void bench_event_sync(benchmark::State &state)
{
    Event e("WindowEvent");
    e.setData("123");
    e.setProperty("aa", "bb");

    for (auto _: state) {
        EventCallProxy::pubEvent(e);
    }
}
BENCHMARK(bench_event_sync);

static WindowEventHandler handler;
static void bench_qt_signal_slot(benchmark::State &state)
{
    Event e("WindowEvent");
    e.setData("123");
    e.setProperty("aa", "bb");
    QObject::connect(&handler, &WindowEventHandler::testSignal,
                     &handler, &WindowEventHandler::slotEventProcess);

    for (auto _: state) {
        emit handler.testSignal(e);
    }
}
BENCHMARK(bench_qt_signal_slot);

BENCHMARK_MAIN();
