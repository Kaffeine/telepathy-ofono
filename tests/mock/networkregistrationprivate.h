#ifndef NETWORKREGISTRATIONPRIVATE_H
#define NETWORKREGISTRATIONPRIVATE_H

#include <QDBusContext>
#define OFONO_MOCK_NETWORK_REGISTRATION_OBJECT "/OfonoNetworkRegistration"

class OfonoNetworkRegistration;
class OfonoInterface;

class NetworkRegistrationPrivate : public QObject, protected QDBusContext {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.ofono.NetworkRegistration")
public:
    NetworkRegistrationPrivate(OfonoNetworkRegistration *iface, OfonoInterface *prop_iface, QObject *parent = 0);
    ~NetworkRegistrationPrivate();
    OfonoInterface *getPropertiesInterface() {
        return mOfonoInterface;
    }
//Q_SIGNALS:
//    void PropertyChanged(const QString &, const QVariant &);
public Q_SLOTS:
    void setProperty(const QString &name, const QString &value);
private:
    OfonoNetworkRegistration *mOfonoNetworkRegistration;
    OfonoInterface *mOfonoInterface;
};

static QMap<QString, NetworkRegistrationPrivate*> networkRegistrationData;

#endif
