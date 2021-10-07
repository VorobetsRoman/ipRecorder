#include "usersettings.h"

void UserSettings::
store(const QString &key
      , const QVariant &value)
{
    auto settings = UserSettings::sharedInstance();
    settings->setValue(key, value);
}

QVariant UserSettings::
valueFor(const QString &key
         , const QVariant& value)
{
    auto settings = UserSettings::sharedInstance();
    if (settings->contains(key)) {
        return settings->value(key, value);
    } else {
        settings->setValue(key, value);
        return value;
    }
}

QSettings* UserSettings::
sharedInstance()
{
    static QSettings settings(
                QSettings::IniFormat
                , QSettings::UserScope
                , QStringLiteral("ipRecorder"));
    return &settings;
}
