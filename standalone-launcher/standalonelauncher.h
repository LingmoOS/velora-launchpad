#pragma once

#include "applet.h"
#include "dsglobal.h"

class StandaloneLauncher : public DS_NAMESPACE::DApplet
{
    Q_OBJECT
public:
    explicit StandaloneLauncher(QObject *parent = nullptr);
    virtual bool init() override;
};
