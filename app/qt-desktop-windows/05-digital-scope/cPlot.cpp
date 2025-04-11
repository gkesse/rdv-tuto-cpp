#include "cPlot.h"
#include "cMainWindow.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMenu>
#include <QApplication>
#include <QScreen>
#include <QMessageBox>

// debug
static const bool DEF_DEBUG_ON = false;

// plot
static const int DEF_PLOT_MAX = 9;
static const int DEF_PLOT_MARGIN_LEFT = 70;
static const int DEF_PLOT_MARGIN_BOTTOM = 50;
static const int DEF_PLOT_MARGIN_TOP = 30;
static const int DEF_PLOT_MARGIN_RIGHT = 10;
static const int DEF_PLOT_PIXEL_PER_DIV = 40;
static const int DEF_PLOT_TEXT_FONT_SIZE = 10;
static const int DEF_PLOT_DATA_NUMBER = 1024;
static const double DEF_PLOT_X_MIN = -45;
static const double DEF_PLOT_X_MAX = 2000;
static const double DEF_PLOT_X_SHIT_VALUE = 45;
static const double DEF_PLOT_X_SHIT_PER_TIME = 5;
static const QPointF DEF_PLOT_OFFSET = QPointF(-5, -3);

static const double DEF_PLOT_X_PER_DIV = 90.0 / 2.0;
static const double DEF_PLOT_Y_PER_DIV = 1.0 / 2.0;

static const int DEF_PLOT_DEFAULT_BORDER_THICKNESS = 1;
static const int DEF_PLOT_BORDER_THICKNESS = 2;
static const int DEF_PLOT_DATA_THICKNESS = 2;

static const QColor DEF_PLOT_BACKGROUND_COLOR = "#FF000000";
static const QColor DEF_PLOT_DEFAULT_BORDER_COLOR = "#FF404040";
static const QColor DEF_PLOT_BORDER_COLOR = "#FFAA0000";
static const QColor DEF_PLOT_TEXT_COLOR = "#FFAA0000";
static const QColor DEF_NO_PLOT_TEXT_COLOR = "#FF808080";
static const QColor DEF_NO_PLOT_BACKGROUND_COLOR = "#80808080";
static const QColor DEF_PLOT_DATA_COLOR = "#FFAA00AA";

static const QString DEF_PLOT_FONT_FAMILY = "Arial";

static const QString DEF_NO_PLOT_TEXT = "[NO-PLOT]";
static const QString DEF_NO_PLOT_ITEM_TEXT = "NO-PLOT-[%1]";
static const QString DEF_PLOT_ITEM_TEXT = "PLOT-[%1]";

// axis
static const int DEF_AXIS_DIV_PER_GRID = 2;

static const int DEF_AXIS_THICKNESS = 2;
static const int DEF_AXIS_GRID_THICKNESS = 1;
static const int DEF_AXIS_TICK_THICKNESS = 1;
static const int DEF_AXIS_TICK_DIV_THICKNESS = 2;
static const int DEF_AXIS_DIV_PER_GRID_THICKNESS = 2;

static const int DEF_AXIS_TICK_SIZE = 5;
static const int DEF_AXIS_TICK_GRID_SIZE = 10;
static const int DEF_AXIS_DIV_VALUE_FONT_SIZE = 10;

static const double DEF_AXIS_TICK_PER_DIV = 5.0;
static const double DEF_AXIS_TICK_DIV_PER_GRID = 2.0;

static const QColor DEF_AXIS_COLOR = "#FF808080";
static const QColor DEF_AXIS_TICK_COLOR = "#FFAA0000";
static const QColor DEF_AXIS_TICK_VALUE_COLOR = "#FFAA0000";
static const QColor DEF_AXIS_GRID_COLOR = "#FF333333";
static const QColor DEF_AXIS_DIV_PER_GRID_COLOR = "#FF222222";

cPlot::cPlot(QWidget *parent)
    : QWidget(parent),
      m_image(parent->width(), parent->height(), QImage::Format_ARGB32),
      m_scaleFactor(1.0),
      m_backgroundColor(DEF_PLOT_BACKGROUND_COLOR)
{
    initScreenSize();
    createPlotMenu();
    connect(this, &cPlot::emitResizePlot, this, &cPlot::onResizePlot);
    connect(this, &cPlot::emitPlotMenu, this, &cPlot::onPlotMenu);
    connect(this, &cPlot::emitPlotClick, this, &cPlot::onPlotClick);
}

cPlot::~cPlot()
{
}

void cPlot::render()
{
    drawPlotBackgroundColor();
    drawPlotsBackgroundColor();
    drawPlotsDefaultBorder();
    drawTextNoPlots();
    drawActivePlots();
    drawPlotsGrids();
    drawPlotsGridsDivs();
    drawPlotsGridsTicks();
    drawPlotsGridsTicksDivs();
    drawPlotsGridsDivsValues();
    drawAnimatePlots();
    drawPlotsDatas();
    drawPlotsBorder();
    drawPlots();
}

void cPlot::setBackgroundColor(const QColor _color)
{
    if (m_backgroundColor != _color)
    {
        m_backgroundColor = _color;
    }
}

void cPlot::addPlot()
{
    if (isMax())
        return;

    m_plots.push_back(sPlot());

    int oSzie = m_plots.size();
    double oSqrt = sqrt((double)oSzie);
    int oCeil = (int)ceil(oSqrt);
    int oDivision = oCeil;
    int oWidth = width() / oDivision;
    int oHeight = height() / oDivision;

    for (int iCount = 0; iCount < m_plots.size(); iCount++)
    {
        int oId = iCount;
        int iX = iCount % oDivision;
        int iY = iCount / oDivision;
        int oX = iX * oWidth;
        int oY = iY * oHeight;

        sPlot &oPlot = m_plots[iCount];
        oPlot.id = oId;
        oPlot.x = oX;
        oPlot.y = oY;
        oPlot.width = oWidth;
        oPlot.height = oHeight;
        oPlot.nDivision = oDivision;

        addPlotImage(oPlot.id, oWidth, oHeight);
        addPlotXShiftValue(oPlot.id);
        addPlotOffset(oPlot.id);
    }

    if (m_plots.size() && DEF_DEBUG_ON)
    {
        qDebug() << "\nLe calcul des parametres de l'oscillosocpe.";

        for (const auto &oPlot : m_plots)
        {
            qDebug() << "|id=" << oPlot.id
                     << "|x=" << oPlot.x
                     << "|y=" << oPlot.y
                     << "|width=" << oPlot.width
                     << "|height=" << oPlot.height
                     << "|WIDTH=" << width()
                     << "|HEIGHT=" << height()
                     << "|nSCOPE=" << oPlot.nDivision * oPlot.nDivision;
        }
    }
}

bool cPlot::isMax() const
{
    return (m_plots.size() >= DEF_PLOT_MAX);
}

void cPlot::addPlotImage(int _plotId, int _width, int _height)
{
    if (hasPlotImage(_plotId))
    {
        QImage &oImage = m_images[_plotId];
        oImage = oImage.scaled(QSize(_width, _height) * m_scaleFactor);
    }
    else
    {
        m_images[_plotId] = QImage(QSize(_width, _height) * m_scaleFactor, QImage::Format_ARGB32);
    }
}

void cPlot::addPlotXShiftValue(int _plotId)
{
    if (!hasPlotXShiftValue(_plotId))
    {
        m_xShiftValues[_plotId] = _plotId * DEF_PLOT_X_SHIT_VALUE;
    }
}

void cPlot::addPlotOffset(int _plotId)
{
    if (!hasPlotOffset(_plotId))
    {
        m_offsets[_plotId] = DEF_PLOT_OFFSET;
    }
}

void cPlot::initScreenSize()
{
    m_screenSize = QApplication::primaryScreen()->geometry().size();
    qDebug() << Q_FUNC_INFO
             << "|screenSize=" << m_screenSize;
}

void cPlot::createPlotMenu()
{
    m_plotMenu = new QMenu(this);
    QAction *oAction;

    oAction = new QAction("Ajouter des données");
    connect(oAction, &QAction::triggered, this, &cPlot::onAddPlotData);
    m_plotMenu->addAction(oAction);

    oAction = new QAction("Animer les données");
    connect(oAction, &QAction::triggered, this, &cPlot::onAnimatePlotData);
    m_plotMenu->addAction(oAction);
}

bool cPlot::loadAllPlots(sPlots &_plots) const
{
    if (m_plots.isEmpty())
        return false;

    const sPlot &oPlot = m_plots[0];
    int oDivision = oPlot.nDivision;
    int oWidth = oPlot.width;
    int oHeight = oPlot.height;
    int oSize = oDivision * oDivision;

    for (int iCount = 0; iCount < oSize; iCount++)
    {
        int oId = iCount;
        int iX = iCount % oDivision;
        int iY = iCount / oDivision;
        int oX = iX * oWidth;
        int oY = iY * oHeight;

        sPlot iPlot;
        iPlot.id = oId;
        iPlot.x = oX;
        iPlot.y = oY;
        iPlot.width = oWidth;
        iPlot.height = oHeight;
        iPlot.nDivision = oDivision;

        _plots.push_back(iPlot);
    }

    if (_plots.size() && DEF_DEBUG_ON)
    {
        qDebug() << "\nLe calcul des parametres de l'oscillosocpe [par défaut].";

        for (const auto &iPlot : _plots)
        {
            qDebug() << "|id=" << iPlot.id
                     << "|x=" << iPlot.x
                     << "|y=" << iPlot.y
                     << "|width=" << iPlot.width
                     << "|height=" << iPlot.height
                     << "|WIDTH=" << width()
                     << "|HEIGHT=" << height()
                     << "|nSCOPE=" << iPlot.nDivision * iPlot.nDivision;
        }
    }

    return true;
}

bool cPlot::loadPlot(int _x, int _y, sPlot &_plot) const
{
    if (m_plots.size())
    {
        sPlots oPlots;
        if (loadAllPlots(oPlots))
        {
            for (const auto &oPlot : oPlots)
            {
                QRegion oRegion(oPlot.x, oPlot.y, oPlot.width, oPlot.height);
                if (oRegion.contains(QPoint(_x, _y)))
                {
                    _plot = oPlot;
                    return true;
                }
            }
        }
    }
    return false;
}

bool cPlot::isActivePlot(const QPoint &_pos) const
{
    for (const auto &oPlot : m_plots)
    {
        QRegion oRegion(oPlot.x, oPlot.y, oPlot.width, oPlot.height);
        if (oRegion.contains(_pos))
        {
            return true;
        }
    }
    return false;
}

bool cPlot::isActivePlot(const QPoint &_pos, int &_plotId) const
{
    for (const auto &oPlot : m_plots)
    {
        QRegion oRegion(oPlot.x, oPlot.y, oPlot.width, oPlot.height);
        if (oRegion.contains(_pos))
        {
            _plotId = oPlot.id;
            return true;
        }
    }
    return false;
}

bool cPlot::hasPlotImage(int _plotId) const
{
    for (const auto &oPlotId : m_images.keys())
    {
        if (oPlotId == _plotId)
        {
            return true;
        }
    }
    return false;
}

bool cPlot::hasPlotData(int _plotId) const
{
    for (const auto &oPlotId : m_datas.keys())
    {
        if (oPlotId == _plotId)
        {
            return true;
        }
    }
    return false;
}

bool cPlot::hasPlotXShiftValue(int _plotId) const
{
    for (const auto &oPlotId : m_xShiftValues.keys())
    {
        if (oPlotId == _plotId)
        {
            return true;
        }
    }
    return false;
}

bool cPlot::hasPlotOffset(int _plotId) const
{
    for (const auto &oPlotId : m_offsets.keys())
    {
        if (oPlotId == _plotId)
        {
            return true;
        }
    }
    return false;
}

bool cPlot::isAnimatePlot(int _plotId) const
{
    for (const auto &oPlotId : m_isAnimatePlots.keys())
    {
        if (oPlotId == _plotId)
        {
            return true;
        }
    }
    return false;
}

void cPlot::generatePlotData(sData &_datas, double _xShiftValue)
{
    for (int iX = 0; iX < DEF_PLOT_DATA_NUMBER; iX++)
    {
        double oX = DEF_PLOT_X_MIN + ((DEF_PLOT_X_MAX - DEF_PLOT_X_MIN) * iX) / DEF_PLOT_DATA_NUMBER;
        double oY = 1 + qSin(qDegreesToRadians(oX));
        oX = oX - _xShiftValue;
        QPointF oData(oX, oY);
        _datas.push_back(oData);
    }
}

QPointF cPlot::pointToPlot(const QPointF &_point) const
{
    double oX = _point.x() * DEF_PLOT_PIXEL_PER_DIV / DEF_PLOT_X_PER_DIV;
    double oY = _point.y() * DEF_PLOT_PIXEL_PER_DIV / DEF_PLOT_Y_PER_DIV;
    return QPointF(oX, oY);
}

void cPlot::drawText(QPaintDevice *_image, int _x, int _y, int _width, int _height, int _fontSize, bool _isBold, const QColor &_color, int _align, const QString &_text)
{
    QPainter oPainter;
    oPainter.begin(_image);
    oPainter.setRenderHint(QPainter::TextAntialiasing);
    oPainter.setPen(_color);

    QFont oFont = oPainter.font();
    oFont.setPointSize(_fontSize);
    oFont.setStyleHint(QFont::Helvetica, QFont::PreferAntialias);
    oFont.setBold(_isBold);
    oFont.setFamily(DEF_PLOT_FONT_FAMILY);

    oPainter.setFont(oFont);
    oPainter.drawText(QRect(_x, _y, _width, _height), _align, _text);
    oPainter.end();
}

void cPlot::drawPlotBackgroundColor()
{
    QPainter oPainter;
    oPainter.begin(&m_image);
    oPainter.fillRect(0, 0, m_image.width(), m_image.height(), m_backgroundColor);
    oPainter.end();
}

void cPlot::drawPlotsBackgroundColor()
{
    for (sPlot &oPlot : m_plots)
    {
        if (hasPlotImage(oPlot.id))
        {
            QImage &oImage = m_images[oPlot.id];
            QPainter oPainter;
            oPainter.begin(&oImage);
            oPainter.fillRect(0, 0, oPlot.width, oPlot.height, m_backgroundColor);
            oPainter.end();
        }
    }
}

void cPlot::drawPlotsDefaultBorder()
{
    sPlots oPlots;
    if (loadAllPlots(oPlots))
    {
        for (int iCount = 0; iCount < oPlots.size(); iCount++)
        {
            if (iCount < m_plots.size())
            {
                sPlot &oPlot = m_plots[iCount];
                if (hasPlotImage(oPlot.id))
                {
                    QImage &oImage = m_images[oPlot.id];
                    QPainter oPainter;
                    oPainter.begin(&oImage);
                    oPainter.setPen(QPen(DEF_PLOT_DEFAULT_BORDER_COLOR, DEF_PLOT_DEFAULT_BORDER_THICKNESS, Qt::DashLine));
                    oPainter.drawRect(0, 0, oPlot.width, oPlot.height);
                    oPainter.end();
                }
            }
            else
            {
                sPlot &oPlot = oPlots[iCount];
                QPainter oPainter;
                oPainter.begin(&m_image);
                oPainter.setPen(QPen(DEF_PLOT_DEFAULT_BORDER_COLOR, DEF_PLOT_DEFAULT_BORDER_THICKNESS, Qt::DashLine));
                oPainter.drawRect(oPlot.x, oPlot.y, oPlot.width, oPlot.height);
                oPainter.end();
            }
        }
    }
}

void cPlot::drawPlotsBorder()
{
    for (auto &oPlot : m_plots)
    {
        if (hasPlotImage(oPlot.id))
        {
            QImage &oImage = m_images[oPlot.id];
            int oX = DEF_PLOT_MARGIN_LEFT;
            int oY = DEF_PLOT_MARGIN_TOP;
            int oWidth = oPlot.width - (DEF_PLOT_MARGIN_LEFT + DEF_PLOT_MARGIN_RIGHT);
            int oHeight = oPlot.height - (DEF_PLOT_MARGIN_TOP + DEF_PLOT_MARGIN_BOTTOM);

            QPainter oPainter;
            oPainter.begin(&oImage);
            oPainter.setPen(QPen(DEF_PLOT_BORDER_COLOR, DEF_PLOT_BORDER_THICKNESS));
            oPainter.drawRect(oX, oY, oWidth, oHeight);
            oPainter.end();
        }
    }
}

void cPlot::drawTextNoPlots()
{
    if (m_plots.isEmpty())
    {
        drawText(&m_image, 0, 0, width(), height(), DEF_PLOT_TEXT_FONT_SIZE, false,
                 DEF_NO_PLOT_TEXT_COLOR, Qt::AlignCenter, DEF_NO_PLOT_TEXT);
        return;
    }

    sPlots oPlots;
    if (loadAllPlots(oPlots))
    {
        for (int iCount = 0; iCount < oPlots.size(); iCount++)
        {
            QString oText;

            if (iCount < m_plots.size())
            {
                sPlot &oPlot = m_plots[iCount];
                if (hasPlotImage(oPlot.id))
                {
                    QImage &oImage = m_images[oPlot.id];
                    oText = QString(DEF_PLOT_ITEM_TEXT).arg(oPlot.id);
                    drawText(&oImage, 0, 0, oPlot.width, DEF_PLOT_MARGIN_TOP, DEF_PLOT_TEXT_FONT_SIZE, false,
                             DEF_PLOT_TEXT_COLOR, Qt::AlignCenter, oText);
                }
            }
            else
            {
                sPlot &oPlot = oPlots[iCount];
                oText = QString(DEF_NO_PLOT_ITEM_TEXT).arg(oPlot.id);
                drawText(&m_image, oPlot.x, oPlot.y, oPlot.width, oPlot.height, DEF_PLOT_TEXT_FONT_SIZE, false,
                         DEF_NO_PLOT_TEXT_COLOR, Qt::AlignCenter, oText);
            }
        }
    }
}

void cPlot::drawActivePlots()
{
    if (m_plots.size())
    {
        QRegion oRegion(0, 0, width(), height());
        for (const auto &oPlot : m_plots)
        {
            QRegion iRegion(oPlot.x, oPlot.y, oPlot.width, oPlot.height);
            oRegion = oRegion.subtracted(iRegion);
        }
        QPainter oPainter;
        oPainter.begin(&m_image);
        oPainter.setClipRegion(oRegion);
        oPainter.fillRect(0, 0, width(), height(), DEF_NO_PLOT_BACKGROUND_COLOR);
        oPainter.end();
    }
}

void cPlot::drawPlotsGrids()
{
    for (auto &oPlot : m_plots)
    {
        if (hasPlotImage(oPlot.id))
        {
            QImage &oImage = m_images[oPlot.id];
            const double &xShiftValue = m_xShiftValues[oPlot.id];

            int oXmax = oPlot.width - (DEF_PLOT_MARGIN_LEFT + DEF_PLOT_MARGIN_RIGHT);
            int oYmax = oPlot.height - (DEF_PLOT_MARGIN_TOP + DEF_PLOT_MARGIN_BOTTOM);
            QRect oRect(DEF_PLOT_MARGIN_LEFT, DEF_PLOT_MARGIN_TOP, oXmax, oYmax);

            for (int iX = 0; iX < 3 * oXmax; iX += DEF_PLOT_PIXEL_PER_DIV)
            {
                QPainter oPainter;
                oPainter.begin(&oImage);
                oPainter.setClipRect(oRect);
                oPainter.translate(oRect.bottomLeft());
                oPainter.scale(1.0, -1.0);

                int oDx = iX - xShiftValue;

                oPainter.setPen(QPen(DEF_AXIS_GRID_COLOR, DEF_AXIS_GRID_THICKNESS, Qt::DotLine));
                oPainter.drawLine(oDx, 0, oDx, oYmax);
                oPainter.end();
            }

            for (int iY = 0; iY < oYmax; iY += DEF_PLOT_PIXEL_PER_DIV)
            {
                QPainter oPainter;
                oPainter.begin(&oImage);
                oPainter.setClipRect(oRect);
                oPainter.translate(oRect.bottomLeft());
                oPainter.scale(1.0, -1.0);

                oPainter.setPen(QPen(DEF_AXIS_GRID_COLOR, DEF_AXIS_GRID_THICKNESS, Qt::DotLine));
                oPainter.drawLine(0, iY, oXmax, iY);
                oPainter.end();
            }
        }
    }
}

void cPlot::drawPlotsGridsDivs()
{
    for (auto &oPlot : m_plots)
    {
        if (hasPlotImage(oPlot.id))
        {
            QImage &oImage = m_images[oPlot.id];
            const double &xShiftValue = m_xShiftValues[oPlot.id];

            int oXmax = oPlot.width - (DEF_PLOT_MARGIN_LEFT + DEF_PLOT_MARGIN_RIGHT);
            int oYmax = oPlot.height - (DEF_PLOT_MARGIN_TOP + DEF_PLOT_MARGIN_BOTTOM);
            QRect oRect(DEF_PLOT_MARGIN_LEFT, DEF_PLOT_MARGIN_TOP, oXmax, oYmax);
            int oDiv = DEF_AXIS_DIV_PER_GRID * DEF_PLOT_PIXEL_PER_DIV;

            for (int iX = 0; iX < 3 * oXmax; iX += oDiv)
            {
                QPainter oPainter;
                oPainter.begin(&oImage);
                oPainter.setClipRect(oRect);
                oPainter.translate(oRect.bottomLeft());
                oPainter.scale(1.0, -1.0);

                int oDx = iX - xShiftValue;

                oPainter.setPen(QPen(DEF_AXIS_DIV_PER_GRID_COLOR, DEF_AXIS_DIV_PER_GRID_THICKNESS));
                oPainter.drawLine(oDx, 0, oDx, oYmax);
                oPainter.end();
            }

            for (int iY = 0; iY < oYmax; iY += oDiv)
            {
                QPainter oPainter;
                oPainter.begin(&oImage);
                oPainter.setClipRect(oRect);
                oPainter.translate(oRect.bottomLeft());
                oPainter.scale(1.0, -1.0);

                oPainter.setPen(QPen(DEF_AXIS_DIV_PER_GRID_COLOR, DEF_AXIS_DIV_PER_GRID_THICKNESS));
                oPainter.drawLine(0, iY, oXmax, iY);
                oPainter.end();
            }
        }
    }
}

void cPlot::drawPlotsGridsTicks()
{
    for (auto &oPlot : m_plots)
    {
        if (hasPlotImage(oPlot.id))
        {
            QImage &oImage = m_images[oPlot.id];
            const double &xShiftValue = m_xShiftValues[oPlot.id];

            int oXmax = oPlot.width - (DEF_PLOT_MARGIN_LEFT + DEF_PLOT_MARGIN_RIGHT);
            int oYmax = oPlot.height - (DEF_PLOT_MARGIN_TOP + DEF_PLOT_MARGIN_BOTTOM);
            QRect oRect(DEF_PLOT_MARGIN_LEFT, DEF_PLOT_MARGIN_TOP, oXmax, oYmax);
            int oTick = DEF_PLOT_PIXEL_PER_DIV / DEF_AXIS_TICK_PER_DIV;

            for (int iX = 0; iX < 3 * oXmax; iX += oTick)
            {
                QPainter oPainter;
                oPainter.begin(&oImage);
                oPainter.setClipRect(oRect);
                oPainter.translate(oRect.bottomLeft());
                oPainter.scale(1.0, -1.0);

                int oDx = iX - xShiftValue;

                oPainter.setPen(QPen(DEF_AXIS_TICK_COLOR, DEF_AXIS_TICK_THICKNESS, Qt::SolidLine));
                oPainter.drawLine(oDx, -DEF_AXIS_TICK_SIZE, oDx, DEF_AXIS_TICK_SIZE);
                oPainter.end();
            }

            for (int iY = 0; iY < oYmax; iY += oTick)
            {
                QPainter oPainter;
                oPainter.begin(&oImage);
                oPainter.setClipRect(oRect);
                oPainter.translate(oRect.bottomLeft());
                oPainter.scale(1.0, -1.0);

                oPainter.setPen(QPen(DEF_AXIS_TICK_COLOR, DEF_AXIS_TICK_THICKNESS, Qt::SolidLine));
                oPainter.drawLine(-DEF_AXIS_TICK_SIZE, iY, DEF_AXIS_TICK_SIZE, iY);
                oPainter.end();
            }
        }
    }
}

void cPlot::drawPlotsGridsTicksDivs()
{
    for (auto &oPlot : m_plots)
    {
        if (hasPlotImage(oPlot.id))
        {
            QImage &oImage = m_images[oPlot.id];
            const double &xShiftValue = m_xShiftValues[oPlot.id];

            int oXmax = oPlot.width - (DEF_PLOT_MARGIN_LEFT + DEF_PLOT_MARGIN_RIGHT);
            int oYmax = oPlot.height - (DEF_PLOT_MARGIN_TOP + DEF_PLOT_MARGIN_BOTTOM);
            QRect oRect(DEF_PLOT_MARGIN_LEFT, DEF_PLOT_MARGIN_TOP, oXmax, oYmax);
            int oDiv = DEF_PLOT_PIXEL_PER_DIV * DEF_AXIS_TICK_DIV_PER_GRID;

            for (int iX = 0; iX < 3 * oXmax; iX += oDiv)
            {
                QPainter oPainter;
                oPainter.begin(&oImage);
                oPainter.setClipRect(oRect);
                oPainter.translate(oRect.bottomLeft());
                oPainter.scale(1.0, -1.0);

                int oDx = iX - xShiftValue;

                oPainter.setPen(QPen(DEF_AXIS_TICK_COLOR, DEF_AXIS_TICK_DIV_THICKNESS, Qt::SolidLine));
                oPainter.drawLine(oDx, -DEF_AXIS_TICK_GRID_SIZE, oDx, DEF_AXIS_TICK_GRID_SIZE);
                oPainter.end();
            }

            oDiv = DEF_PLOT_PIXEL_PER_DIV;
            for (int iY = 0; iY < oYmax; iY += oDiv)
            {
                QPainter oPainter;
                oPainter.begin(&oImage);
                oPainter.setClipRect(oRect);
                oPainter.translate(oRect.bottomLeft());
                oPainter.scale(1.0, -1.0);

                oPainter.setPen(QPen(DEF_AXIS_TICK_COLOR, DEF_AXIS_TICK_DIV_THICKNESS, Qt::SolidLine));
                oPainter.drawLine(-DEF_AXIS_TICK_GRID_SIZE, iY, DEF_AXIS_TICK_GRID_SIZE, iY);
                oPainter.end();
            }
        }
    }
}

void cPlot::drawPlotsGridsDivsValues()
{
    for (auto &oPlot : m_plots)
    {
        if (hasPlotImage(oPlot.id))
        {
            QImage &oImage = m_images[oPlot.id];
            const double &xShiftValue = m_xShiftValues[oPlot.id];

            int oXmax = oPlot.width - (DEF_PLOT_MARGIN_LEFT + DEF_PLOT_MARGIN_RIGHT);
            int oYmax = oPlot.height - (DEF_PLOT_MARGIN_TOP + DEF_PLOT_MARGIN_BOTTOM);
            QRect oRect(DEF_PLOT_MARGIN_LEFT, DEF_PLOT_MARGIN_TOP, oXmax, oYmax);
            QRect oRect2(DEF_PLOT_MARGIN_LEFT - 10, DEF_PLOT_MARGIN_TOP, oXmax + DEF_PLOT_MARGIN_RIGHT, oYmax + DEF_PLOT_MARGIN_BOTTOM);
            int oDiv = DEF_PLOT_PIXEL_PER_DIV * DEF_AXIS_TICK_DIV_PER_GRID;

            for (int iX = 0; iX < 3 * oXmax; iX += oDiv)
            {
                double oX = iX * DEF_PLOT_X_PER_DIV / DEF_PLOT_PIXEL_PER_DIV;

                QString oValue = QString("%1").arg(oX);

                QPainter oPainter;
                oPainter.begin(&oImage);
                oPainter.setClipRect(oRect2);
                oPainter.translate(oRect.bottomLeft());
                oPainter.scale(1.0, 1.0);
                oPainter.setPen(DEF_AXIS_TICK_VALUE_COLOR);

                int oDx = iX - xShiftValue;

                QFont oFont = oPainter.font();
                oFont.setPointSize(DEF_AXIS_DIV_VALUE_FONT_SIZE);
                oFont.setStyleHint(QFont::Helvetica, QFont::PreferAntialias);
                oFont.setFamily(DEF_PLOT_FONT_FAMILY);
                oPainter.setFont(oFont);

                oPainter.drawText(oDx - 40, 10, 80, 25, Qt::AlignHCenter | Qt::AlignTop, oValue);
                oPainter.end();
            }

            oDiv = DEF_PLOT_PIXEL_PER_DIV;
            for (int iY = 0; iY < oYmax; iY += oDiv)
            {
                double oY = iY * DEF_PLOT_Y_PER_DIV / DEF_PLOT_PIXEL_PER_DIV;

                QString oValue = QString("%1").arg(oY);

                QPainter oPainter;
                oPainter.begin(&oImage);
                oPainter.translate(oRect.bottomLeft());
                oPainter.scale(1.0, 1.0);
                oPainter.setPen(DEF_AXIS_TICK_VALUE_COLOR);

                QFont oFont = oPainter.font();
                oFont.setPointSize(DEF_AXIS_DIV_VALUE_FONT_SIZE);
                oFont.setStyleHint(QFont::Helvetica, QFont::PreferAntialias);
                oFont.setFamily(DEF_PLOT_FONT_FAMILY);
                oPainter.setFont(oFont);

                oPainter.drawText(-80 - 15, -iY - 20, 80, 40, Qt::AlignVCenter | Qt::AlignRight, oValue);
                oPainter.end();
            }
        }
    }
}

void cPlot::drawAnimatePlots()
{
    for (const auto &oPlotId : m_isAnimatePlots.keys())
    {
        const bool &isAnimatePlot = m_isAnimatePlots[oPlotId];

        if (hasPlotXShiftValue(oPlotId) && isAnimatePlot)
        {
            sData oData;
            double &xShiftValues = m_xShiftValues[oPlotId];
            xShiftValues += DEF_PLOT_X_SHIT_PER_TIME;
            generatePlotData(oData, xShiftValues);
            m_datas[oPlotId] = oData;
        }
    }
}

void cPlot::drawPlotsDatas()
{
    for (const auto &oPlotId : m_datas.keys())
    {
        const sData &oDatas = m_datas[oPlotId];
        const sPlot &oPlot = m_plots[oPlotId];
        QImage &oImage = m_images[oPlot.id];

        int oXmax = oPlot.width - (DEF_PLOT_MARGIN_LEFT + DEF_PLOT_MARGIN_RIGHT);
        int oYmax = oPlot.height - (DEF_PLOT_MARGIN_TOP + DEF_PLOT_MARGIN_BOTTOM);
        QRect oRect(DEF_PLOT_MARGIN_LEFT, DEF_PLOT_MARGIN_TOP, oXmax, oYmax);

        for (int iX = 0; iX < oDatas.size() - 1; iX++)
        {
            QPointF oPoint1 = pointToPlot(oDatas[iX]);
            QPointF oPoint2 = pointToPlot(oDatas[iX + 1]);

            QPainter oPainter;
            oPainter.begin(&oImage);
            oPainter.setClipRect(oRect);
            oPainter.translate(oRect.bottomLeft());
            oPainter.scale(1.0, -1.0);

            oPainter.setPen(QPen(DEF_PLOT_DATA_COLOR, DEF_PLOT_DATA_THICKNESS, Qt::SolidLine));
            oPainter.drawLine(oPoint1, oPoint2);
            oPainter.end();
        }
    }
}

void cPlot::drawPlots()
{
    for (auto &oPlot : m_plots)
    {
        if (hasPlotImage(oPlot.id))
        {
            QImage &oImage = m_images[oPlot.id];
            QPainter oPainter;
            oPainter.begin(&m_image);
            oPainter.drawImage(oPlot.x, oPlot.y, oImage.scaled(QSize(oPlot.width, oPlot.height) * m_scaleFactor));
            oPainter.end();
        }
    }
}

void cPlot::paintEvent(QPaintEvent *event)
{
    QPainter oPainter(this);
    QRect oRect = rect() & event->rect();
    oPainter.setClipRect(oRect);
    oPainter.drawImage(0, 0, m_image.scaled(size() * m_scaleFactor));
}

void cPlot::resizeEvent(QResizeEvent *event)
{
    m_image = m_image.scaled(event->size() * m_scaleFactor);
    emit emitResizePlot(event->size());
}

void cPlot::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit emitPlotClick(event->pos());
    }
    else if (event->button() == Qt::RightButton)
    {
        emit emitPlotMenu(event->pos());
    }
}

void cPlot::wheelEvent(QWheelEvent *event)
{
    qDebug() << "cPlot::wheelEvent()...";
}

void cPlot::onResizePlot(const QSize &_size)
{
    if (m_plots.size())
    {
        const sPlot &oPlot = m_plots[0];
        int oDivision = oPlot.nDivision;
        int oWidth = _size.width() / oDivision;
        int oHeight = _size.height() / oDivision;

        for (int iCount = 0; iCount < m_plots.size(); iCount++)
        {
            sPlot &iPlot = m_plots[iCount];

            int oId = iCount;
            int iX = iCount % oDivision;
            int iY = iCount / oDivision;
            int oX = iX * oWidth;
            int oY = iY * oHeight;

            iPlot.id = oId;
            iPlot.x = oX;
            iPlot.y = oY;
            iPlot.width = oWidth;
            iPlot.height = oHeight;
            iPlot.nDivision = oDivision;

            if (hasPlotImage(iPlot.id))
            {
                QImage &oImage = m_images[iPlot.id];
                oImage = oImage.scaled(QSize(oWidth, oHeight) * m_scaleFactor);
            }
        }
    }

    if (m_plots.size() && DEF_DEBUG_ON)
    {
        qDebug() << "\nLe calcul des parametres de l'oscillosocpe.";

        for (const auto &oPlot : m_plots)
        {
            qDebug() << "|id=" << oPlot.id
                     << "|x=" << oPlot.x
                     << "|y=" << oPlot.y
                     << "|width=" << oPlot.width
                     << "|height=" << oPlot.height
                     << "|WIDTH=" << _size.width()
                     << "|HEIGHT=" << _size.height()
                     << "|nSCOPE=" << oPlot.nDivision * oPlot.nDivision;
        }
    }
}

void cPlot::onPlotMenu(const QPoint &_pos)
{
    if (isActivePlot(_pos))
    {
        m_plotMenu->exec(mapToGlobal(_pos));
    }
}

void cPlot::onAddPlotData()
{
    QPoint oPos = mapFromGlobal(m_plotMenu->pos());
    int oPlotId;
    if (isActivePlot(oPos, oPlotId))
    {
        if (hasPlotData(oPlotId))
        {
            QMessageBox::critical(this, tr("Messages d'erreurs"),
                                  tr("L'oscilloscope [%1] contient déjà des données.").arg(oPlotId));
            return;
        }

        if (hasPlotXShiftValue(oPlotId))
        {
            sData oData;
            const double &oXShiftValues = m_xShiftValues[oPlotId];
            generatePlotData(oData, oXShiftValues);
            m_datas[oPlotId] = oData;
        }
    }
}

void cPlot::onAnimatePlotData()
{
    QPoint oPos = mapFromGlobal(m_plotMenu->pos());
    int oPlotId;
    if (isActivePlot(oPos, oPlotId))
    {
        if (!hasPlotData(oPlotId))
        {
            QMessageBox::critical(this, tr("Messages d'erreurs"),
                                  tr("L'oscilloscope [%1] doit contenir des données.").arg(oPlotId));
            return;
        }
        if (isAnimatePlot(oPlotId))
        {
            bool &isAnimatePlot = m_isAnimatePlots[oPlotId];
            isAnimatePlot = !isAnimatePlot;
        }
        else
        {
            m_isAnimatePlots[oPlotId] = true;
        }
    }
}

void cPlot::onPlotClick(const QPoint &_pos)
{
    sPlot oPlot;
    if (loadPlot(_pos.x(), _pos.y(), oPlot))
    {
        qDebug() << "cPlot::mousePressEvent()...\n"
                 << "|x=" << _pos.x()
                 << "|y=" << _pos.y()
                 << "|oPlot.id=" << oPlot.id
                 << "|oPlot.x=" << oPlot.x
                 << "|oPlot.y=" << oPlot.y
                 << "|oPlot.width=" << oPlot.width
                 << "|oPlot.height=" << oPlot.height
                 << "|m_image.bytesPerLine=" << m_image.bytesPerLine()
                 << "|m_image.width=" << m_image.width()
                 << "|m_image.bits=" << m_image.bits()
                 << "|m_image.bits=" << m_image.depth();
    }
}
