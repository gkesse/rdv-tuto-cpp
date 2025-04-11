#include "cMainWindow.h"
#include "ui_cMainWindow.h"
#include <QFileDialog>
#include <QSettings>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QCloseEvent>

// Organization
static const QString DEF_ORGANIZATION_NAME = "ReadyDEV";
static const QString DEF_APP_NAME = "ReadySCOPE";
// Settings : General
static const QString DEF_INPUT_DEVICE = "InputDevice";
static const QString DEF_BUFFER_SIZE = "BufferSize";
static const QString DEF_NAN_VALUE = "NanValue";
static const QString DEF_AFTER_GLOW = "AfterGlow";
static const QString DEF_REFRESH_RATE = "RefreshRate";
static const QString DEF_SETTINGS_PATH = "SettingsPath";
// Settings : Format
static const QString DEF_SETTINGS_FORMAT = "Format";
static const QString DEF_DISPLAY_FORMAT = "DisplayFormat";
static const QString DEF_BINARY_FORMAT = "BinaryFormat";
// Settings : Scaling
static const QString DEF_SETTINGS_SCALING = "Scaling";
static const QString DEF_SCALING_A = "ScalingA";
static const QString DEF_SCALING_B = "ScalingB";
static const QString DEF_SCALING_ENABLED = "ScalingEnabled";

cMainWindow::cMainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::cMainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->pageHome);
    QSettings oSettings(DEF_ORGANIZATION_NAME, DEF_APP_NAME);
    sSettingsDTO oSettingsDTO;
    loadSettings(oSettings, oSettingsDTO);
    writeSettings(oSettingsDTO);
}

cMainWindow::~cMainWindow()
{
    delete ui;
}

void cMainWindow::loadDefaultValue(sSettingsDTO &_settingsDTO)
{
    // General
    _settingsDTO.inputDevice = "[input-device]";
    _settingsDTO.bufferSize = 100000;
    _settingsDTO.nanValue = 0;
    _settingsDTO.isAfterGlow = false;
    _settingsDTO.refreshRate = 10;
    _settingsDTO.settingsPath = QDir::homePath();
    // Format
    _settingsDTO.displayFormat = "[display-format]";
    _settingsDTO.binaryFormat = "[binary-format]";
    // Scaling
    _settingsDTO.scalingA = 1.0;
    _settingsDTO.scalingB = 0.0;
    _settingsDTO.isScalingEnabled = false;
}

void cMainWindow::readSettings(sSettingsDTO &_settingsDTO)
{
    // General
    _settingsDTO.inputDevice = ui->edtInputDevice->text();
    _settingsDTO.bufferSize = ui->edtBufferSize->value();
    _settingsDTO.nanValue = ui->edtNanValue->value();
    _settingsDTO.isAfterGlow = ui->radAfterGlowYes->isChecked();
    _settingsDTO.refreshRate = ui->edtRefreshRate->value();
    _settingsDTO.settingsPath = m_settingsPath;
    // Format
    _settingsDTO.displayFormat = ui->edtDisplayFormat->text();
    _settingsDTO.binaryFormat = ui->edtBinaryFormat->text();
    // Scaling
    _settingsDTO.scalingA = ui->edtScalingA->value();
    _settingsDTO.scalingB = ui->edtScalingB->value();
    _settingsDTO.isScalingEnabled = ui->chbScalingEnabled->isChecked();
}

void cMainWindow::writeSettings(const sSettingsDTO &_settingsDTO)
{
    // General
    ui->edtInputDevice->setText(_settingsDTO.inputDevice);
    ui->edtBufferSize->setValue(_settingsDTO.bufferSize);
    ui->edtNanValue->setValue(_settingsDTO.nanValue);
    ui->radAfterGlowYes->setChecked(_settingsDTO.isAfterGlow);
    ui->radAfterGlowNo->setChecked(!_settingsDTO.isAfterGlow);
    ui->edtRefreshRate->setValue(_settingsDTO.refreshRate);
    m_settingsPath = _settingsDTO.settingsPath;
    // Format
    ui->edtDisplayFormat->setText(_settingsDTO.displayFormat);
    ui->edtBinaryFormat->setText(_settingsDTO.binaryFormat);
    // Scaling
    ui->edtScalingA->setValue(_settingsDTO.scalingA);
    ui->edtScalingB->setValue(_settingsDTO.scalingB);
    ui->chbScalingEnabled->setChecked(_settingsDTO.isScalingEnabled);
}

void cMainWindow::saveSettings(QSettings &_settings, const sSettingsDTO &_settingsDTO)
{
    // General
    _settings.setValue(DEF_INPUT_DEVICE, _settingsDTO.inputDevice);
    _settings.setValue(DEF_BUFFER_SIZE, _settingsDTO.bufferSize);
    _settings.setValue(DEF_NAN_VALUE, _settingsDTO.nanValue);
    _settings.setValue(DEF_AFTER_GLOW, _settingsDTO.isAfterGlow);
    _settings.setValue(DEF_REFRESH_RATE, _settingsDTO.refreshRate);
    _settings.setValue(DEF_SETTINGS_PATH, _settingsDTO.settingsPath);
    // Format
    _settings.beginGroup(DEF_SETTINGS_FORMAT);
    _settings.setValue(DEF_DISPLAY_FORMAT, _settingsDTO.displayFormat);
    _settings.setValue(DEF_BINARY_FORMAT, _settingsDTO.binaryFormat);
    _settings.endGroup();
    // Scaling
    _settings.beginGroup(DEF_SETTINGS_SCALING);
    _settings.setValue(DEF_SCALING_A, _settingsDTO.scalingA);
    _settings.setValue(DEF_SCALING_B, _settingsDTO.scalingB);
    _settings.setValue(DEF_SCALING_ENABLED, _settingsDTO.isScalingEnabled);
    _settings.endGroup();
}

void cMainWindow::loadSettings(QSettings &_settings, sSettingsDTO &_settingsDTO)
{
    sSettingsDTO oSettingsDTO;
    loadDefaultValue(oSettingsDTO);

    // General
    _settingsDTO.inputDevice = _settings.value(DEF_INPUT_DEVICE, oSettingsDTO.inputDevice).toString();
    _settingsDTO.bufferSize = _settings.value(DEF_BUFFER_SIZE, oSettingsDTO.bufferSize).toInt();
    _settingsDTO.nanValue = _settings.value(DEF_NAN_VALUE, oSettingsDTO.nanValue).toInt();
    _settingsDTO.isAfterGlow = _settings.value(DEF_AFTER_GLOW, oSettingsDTO.isAfterGlow).toBool();
    _settingsDTO.refreshRate = _settings.value(DEF_REFRESH_RATE, oSettingsDTO.refreshRate).toInt();
    _settingsDTO.settingsPath = _settings.value(DEF_SETTINGS_PATH, oSettingsDTO.settingsPath).toString();
    // Format
    _settings.beginGroup(DEF_SETTINGS_FORMAT);
    _settingsDTO.displayFormat = _settings.value(DEF_DISPLAY_FORMAT, oSettingsDTO.displayFormat).toString();
    _settingsDTO.binaryFormat = _settings.value(DEF_BINARY_FORMAT, oSettingsDTO.binaryFormat).toString();
    _settings.endGroup();
    // Scaling
    _settings.beginGroup(DEF_SETTINGS_SCALING);
    _settingsDTO.scalingA = _settings.value(DEF_SCALING_A, oSettingsDTO.scalingA).toDouble();
    _settingsDTO.scalingB = _settings.value(DEF_SCALING_B, oSettingsDTO.scalingB).toDouble();
    _settingsDTO.isScalingEnabled = _settings.value(DEF_SCALING_ENABLED, oSettingsDTO.isScalingEnabled).toBool();
    _settings.endGroup();
}

void cMainWindow::closeEvent(QCloseEvent *event)
{
    sSettingsDTO oSettingsDTO;
    readSettings(oSettingsDTO);
    QSettings oSettings(DEF_ORGANIZATION_NAME, DEF_APP_NAME);
    saveSettings(oSettings, oSettingsDTO);
}

void cMainWindow::on_actionSaveSettings_triggered()
{

    QString oFilename = QFileDialog::getSaveFileName(this, tr("Sauvegarder les configurations"), m_settingsPath, tr("Settings (*.ini)"));
    if (oFilename.isEmpty())
    {
        qDebug() << "L'enregistrement des configurations a ete annule.";
        return;
    }

    m_settingsPath = QFileInfo(oFilename).absolutePath();

    sSettingsDTO oSettingsDTO;
    readSettings(oSettingsDTO);
    QSettings oSettings(oFilename, QSettings::IniFormat);
    saveSettings(oSettings, oSettingsDTO);

    qDebug() << "L'enregistrement des configurations s'est bien deroule."
             << "|filename=" << oFilename;
}

void cMainWindow::on_actionLoadSettings_triggered()
{
    QString oFilename = QFileDialog::getOpenFileName(this, tr("Charger les configurations"), m_settingsPath, tr("Settings (*.ini)"));
    if (oFilename.isEmpty())
    {
        qDebug() << "Le chargement des configurations a ete annule.";
        return;
    }

    m_settingsPath = QFileInfo(oFilename).absolutePath();

    sSettingsDTO oSettingsDTO;
    QSettings oSettings(oFilename, QSettings::IniFormat);
    loadSettings(oSettings, oSettingsDTO);
    writeSettings(oSettingsDTO);

    qDebug() << "Le chargement des configurations s'est bien deroule."
             << "|filename=" << oFilename;
}

void cMainWindow::on_actionSettingsPage_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSettings);
}

void cMainWindow::on_btnSettingsOK_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageHome);
}
