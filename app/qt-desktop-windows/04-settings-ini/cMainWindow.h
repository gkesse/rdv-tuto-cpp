#pragma once

#include <QMainWindow>

class QLabel;
class QSettings;

namespace Ui
{
    class cMainWindow;
}

class cMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct sSettingsDTO
    {
        // General
        QString inputDevice;
        int bufferSize;
        int nanValue;
        bool isAfterGlow;
        int refreshRate;
        QString settingsPath;
        // Format
        QString displayFormat;
        QString binaryFormat;
        // Sacling
        double scalingA;
        double scalingB;
        bool isScalingEnabled;
    };

public:
    explicit cMainWindow(QWidget *parent = 0);
    ~cMainWindow();

private:
    void loadDefaultValue(sSettingsDTO &_settingsDTO);
    void readSettings(sSettingsDTO &_settingsDTO);
    void writeSettings(const sSettingsDTO &_settingsDTO);
    void saveSettings(QSettings &_settings, const sSettingsDTO &_settingsDTO);
    void loadSettings(QSettings &_settings, sSettingsDTO &_settingsDTO);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionSaveSettings_triggered();
    void on_actionLoadSettings_triggered();
    void on_actionSettingsPage_triggered();
    void on_btnSettingsOK_clicked();

private:
    Ui::cMainWindow *ui;
    QString m_settingsPath;
};
