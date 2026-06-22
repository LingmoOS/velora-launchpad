#include "standalonelauncher.h"
#include "pluginfactory.h"
#include "launchercontroller.h"
#include <blurhashimageprovider.h>

#include <DDBusSender>
#include <QLoggingCategory>

#include <applet.h>
#include <qmlengine.h>

DS_USE_NAMESPACE

namespace {
Q_LOGGING_CATEGORY(logApplet, "org.deepin.ds.launcher")
}

StandaloneLauncher::StandaloneLauncher(QObject *parent)
    : DApplet(parent)
{
}

bool StandaloneLauncher::init()
{
    DApplet::init();

    DQmlEngine().engine()->addImageProvider(QLatin1String("blurhash"), new BlurhashImageProvider);

    QDBusConnection connection = QDBusConnection::sessionBus();
    if (!connection.registerService(QStringLiteral("org.deepin.dde.Launcher1")) ||
        !connection.registerObject(QStringLiteral("/org/deepin/dde/Launcher1"), &LauncherController::instance())) {
        qCWarning(logApplet) << "Register D-Bus service failed";
    }
    qCInfo(logApplet) << "StandaloneLauncher initialization completed";
    return true;
}

D_APPLET_CLASS(StandaloneLauncher)

#include "standalonelauncher.moc"
