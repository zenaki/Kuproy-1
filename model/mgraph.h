#ifndef MGRAPH_H
#define MGRAPH_H

#include <QObject>
#include <QInputDialog>

#include "util/global.h"
#include "model/qcustomplot.h"

class mGraph : public QObject
{
    Q_OBJECT
public:
    explicit mGraph(QObject *parent = 0);

    QCustomPlot *customPlot;
    void setupGrafik(QWidget *parent, QCustomPlot *customPlot);

public slots:
    void titleDoubleClick(QWidget *parent, QMouseEvent *event, QCustomPlot *customPlot);
    void axisLabelDoubleClick(QWidget *parent, QCPAxis *axis, QCPAxis::SelectablePart part, QCustomPlot *customPlot);
    void legendDoubleClick(QWidget *parent, QCPLegend *legend, QCPAbstractLegendItem *item, QCustomPlot *customPlot);
    void selectionChanged(QCustomPlot *customPlot);
    void mousePress(QCustomPlot *customPlot);
    void mouseWheel(QCustomPlot *customPlot);
    void moveLegend(QCustomPlot *customPlot);
    void addRandomGraph(QCustomPlot *customPlot);
    void removeSelectedGraph(QCustomPlot *customPlot);
    void removeAllGraphs(QCustomPlot *customPlot);
    void contextMenuRequest(QWidget *parent, QPoint pos, QCustomPlot *customPlot);
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
};

#endif // MGRAPH_H
