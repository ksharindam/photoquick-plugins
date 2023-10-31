#pragma once
#include "plugin.h"
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>


class ToolPlugin : public QObject, Plugin
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


class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog(QWidget *parent);

    QLabel *currentVersionLabel;
    QLabel *barcodeLabel;
    QLineEdit *textEdit;
    QPushButton *generateBtn;
    QPushButton *closeBtn;

    QImage result;

private slots:
    void generateBarcode();
    void onAcceptClick();
};
