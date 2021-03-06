#pragma once
#include "plugin.h"
#include <QDialog>
#include <QDoubleSpinBox>


class FilterPlugin : public QObject, Plugin
{
    Q_OBJECT
    Q_INTERFACES(Plugin)
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID Plugin_iid)
#endif

public:
    QString menuItem();

public slots:
    void onMenuClick();

signals:
    void imageChanged();
    void optimumSizeRequested();
    void sendNotification(QString title, QString message);
};


class Mantiuk06Dialog : public QDialog
{
public:
    QDoubleSpinBox *contrastSpin;
    QDoubleSpinBox *saturationSpin;

    Mantiuk06Dialog(QWidget *parent);
};
