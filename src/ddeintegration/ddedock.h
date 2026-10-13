// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>
#include <QRect>

class __Dock1;
class DdeDock : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Qt::ArrowType direction READ direction NOTIFY directionChanged)
    Q_PROPERTY(QRect geometry READ geometry NOTIFY geometryChanged)
    Q_PROPERTY(int displayMode READ displayMode NOTIFY displayModeChanged)

public:
    // 取值与 org.deepin.dde.daemon.Dock1 的 DisplayMode 属性一致
    enum DisplayMode {
        Fashion = 0,
        Efficient = 1,
    };
    Q_ENUM(DisplayMode)

    explicit DdeDock(QObject *parent = nullptr);
    ~DdeDock();

    Qt::ArrowType direction() const;
    QRect geometry() const;
    int displayMode() const;

    bool isDocked(const QString & desktop) const;
    void sendToDock(const QString & desktop, int idx = -1);
    void removeFromDock(const QString & desktop);

signals:
    void directionChanged();
    void geometryChanged();
    void displayModeChanged();

private:
    void updateDockRectAndPositionFromDBus();
    void updateDockPositionFromDBus();
    void updateDockRectFromDBus();
    void updateDockDisplayModeFromDBus();

    __Dock1 * m_dbusDaemonDockIface;

    Qt::ArrowType m_direction;
    QRect m_rect;
    // 默认按时尚模式处理：拿不到 dock 状态时维持原来的居中行为
    int m_displayMode = DisplayMode::Fashion;
};
