#pragma once

#include <QWidget>
#include <QImage>
#include <QVector>
#include <QMap>

class QMenu;

class cPlot : public QWidget
{
    Q_OBJECT

public:
    struct sPlot
    {
        int id;
        int x;
        int y;
        int width;
        int height;
        int nDivision;
    };

    using sPlots = QVector<sPlot>;
    using sData = QVector<QPointF>;
    using sImages = QMap<int, QImage>;
    using sDatas = QMap<int, sData>;
    using sXShiftValues = QMap<int, double>;
    using sAnimatePlots = QMap<int, bool>;
    using sOffsets = QMap<int, QPointF>;

public:
    explicit cPlot(QWidget *parent = nullptr);
    ~cPlot();
    void render();
    void setBackgroundColor(const QColor _color);
    void addPlot();
    bool isMax() const;

    const QColor &getBackgroundColor() const { return m_backgroundColor; }
    sPlots &getPlots() { return m_plots; }
    const sPlots &getPlots() const { return m_plots; }
    int getSize() const { return m_plots.size(); }

private:
    void addPlotImage(int _plotId, int _width, int _height);
    void addPlotXShiftValue(int _plotId);
    void addPlotOffset(int _plotId);
    //
    void initScreenSize();
    void createPlotMenu();
    bool loadAllPlots(sPlots &_plots) const;
    bool loadPlot(int _x, int _y, sPlot &_plot) const;
    bool isActivePlot(const QPoint &_pos) const;
    bool isActivePlot(const QPoint &_pos, int &_plotId) const;
    bool hasPlotImage(int _plotId) const;
    bool hasPlotData(int _plotId) const;
    bool hasPlotXShiftValue(int _plotId) const;
    bool hasPlotOffset(int _plotId) const;
    bool isAnimatePlot(int _plotId) const;
    void generatePlotData(sData &_datas, double _xShiftValue);
    QPointF pointToPlot(const QPointF &_point) const;
    void drawText(QPaintDevice *_image, int _x, int _y, int _width, int _height, int _fontSize, bool _isBold, const QColor &_color, int _align, const QString &_text);
    //
    void drawPlotBackgroundColor();
    void drawPlotsBackgroundColor();
    void drawPlotsDefaultBorder();
    void drawPlotsBorder();
    void drawTextNoPlots();
    void drawActivePlots();
    void drawPlotsGrids();
    void drawPlotsGridsDivs();
    void drawPlotsGridsTicks();
    void drawPlotsGridsTicksDivs();
    void drawPlotsGridsDivsValues();
    void drawAnimatePlots();
    void drawPlotsDatas();
    void drawPlots();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void onResizePlot(const QSize &_size);
    void onPlotMenu(const QPoint &_pos);
    void onAddPlotData();
    void onAnimatePlotData();
    void onPlotClick(const QPoint &_pos);

signals:
    void emitResizePlot(QSize _size);
    void emitPlotMenu(QPoint _pos);
    void emitPlotClick(QPoint _pos);

private:
    sPlots m_plots;
    sImages m_images;
    sDatas m_datas;
    sXShiftValues m_xShiftValues;
    sAnimatePlots m_isAnimatePlots;
    sOffsets m_offsets;
    //
    QSize m_screenSize;
    QImage m_image;
    QMenu *m_plotMenu;
    QColor m_backgroundColor;
    //
    double m_scaleFactor;
};
