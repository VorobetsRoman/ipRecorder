#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <QSettings>

class UserSettings
{
public:
    inline static void store(const QString &key
                             , const QVariant& value);
    inline static QVariant valueFor(const QString &key
                                    , const QVariant& value = 0);

private:
    UserSettings(){};
    static QSettings *sharedInstance();
};

#endif // USERSETTINGS_H
