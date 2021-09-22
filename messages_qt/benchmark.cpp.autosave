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

#include "message.h"
#include "testa/testa.h"
#include "testb/testb.h"

#include <benchmark/benchmark.h>


static TestA aobj;
static TestB bobj;

// 直接调用（带参数）
static void bench_direct_call(benchmark::State &state)
{
    for (auto _: state) {
        bobj.testSlot2(1, 2);
    }
}
BENCHMARK(bench_direct_call);

// Qt 信号槽通信（带参数）
static void bench_qt_signalslot(benchmark::State &state)
{
    QObject::connect(&aobj, &TestA::testSignal2, &bobj, &TestB::testSlot2);

    for (auto _: state) {
        emit aobj.testSignal2(1, 2);
    }
}
BENCHMARK(bench_qt_signalslot);

// messgge 机制通信（带参数）
static void bench_message(benchmark::State &state)
{
    message::Sender sender("test");
    message::Receiver receiver("test");
    receiver.bind(&bobj, &TestB::testSlot2);

    for (auto _: state) {
        sender.send(1, 2);
    }
}
BENCHMARK(bench_message);

// 直接调用
static void bench_direct_call_no_param(benchmark::State &state)
{
    for (auto _: state) {
        bobj.testSlot();
    }
}
BENCHMARK(bench_direct_call_no_param);

// Qt 信号槽通信
static void bench_qt_signalslot_no_param(benchmark::State &state)
{
    QObject::connect(&aobj, &TestA::testSignal, &bobj, &TestB::testSlot);

    for (auto _: state) {
        emit aobj.testSignal();
    }
}
BENCHMARK(bench_qt_signalslot_no_param);

// messgge 机制通信
static void bench_message_no_param(benchmark::State &state)
{
    message::Sender sender("test");
    message::Receiver receiver("test");
    receiver.bind(&bobj, &TestB::testSlot);

    for (auto _: state) {
        sender.send();
    }
}
BENCHMARK(bench_message_no_param);

// messgge 机制异步通信
static void bench_message_no_param_async(benchmark::State &state)
{
    message::Sender sender("test");
    message::Receiver receiver("test");
    receiver.bind(&bobj, &TestB::testSlot);

    for (auto _: state) {
        sender.asyncSend();
    }
}
BENCHMARK(bench_message_no_param_async);


BENCHMARK_MAIN();
