#include "mgraph.h"

mGraph::mGraph(QObject *parent) : QObject(parent)
{
}

void mGraph::setupGrafik(QWidget *parent, QCustomPlot *customPlot)
{
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    customPlot->xAxis->setRange(-8, 8);
    customPlot->yAxis->setRange(-5, 5);
    customPlot->axisRect()->setupFullAxesBox();

    customPlot->plotLayout()->insertRow(0);
    QCPTextElement *title = new QCPTextElement(customPlot, "Grafik", QFont("sans", 17, QFont::Bold));
    customPlot->plotLayout()->addElement(0, 0, title);

    customPlot->xAxis->setLabel("x Axis");
    customPlot->yAxis->setLabel("y Axis");
    customPlot->legend->setVisible(true);
//    QFont legendFont = font();
//    legendFont.setPointSize(10);
//    customPlot->legend->setFont(legendFont);
//    customPlot->legend->setSelectedFont(legendFont);
    customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

    addRandomGraph(customPlot);
    addRandomGraph(customPlot);
    addRandomGraph(customPlot);
    addRandomGraph(customPlot);
//    customPlot->rescaleAxes();

    // connect slot that ties some axis selections together (especially opposite axes):
    connect(customPlot, SIGNAL(selectionChangedByUser()), parent, SLOT(grafik_selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
//    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), parent, SLOT(grafik_mousePress()));
//    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), parent, SLOT(grafik_mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), parent, SLOT(grafik_axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    connect(customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), parent, SLOT(grafik_legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
    connect(title, SIGNAL(doubleClicked(QMouseEvent*)), parent, SLOT(grafik_titleDoubleClick(QMouseEvent*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));

    // setup policy and connect slot for context menu popup:
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), parent, SLOT(grafik_contextMenuRequest(QPoint)));
}

void mGraph::titleDoubleClick(QWidget *parent, QMouseEvent* event, QCustomPlot *customPlot)
{
  Q_UNUSED(event)
  if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender()))
  {
    // Set the plot title by double clicking on it
    bool ok;
    QString newTitle = QInputDialog::getText(parent, "QCustomPlot example", "New plot title:", QLineEdit::Normal, title->text(), &ok);
    if (ok)
    {
      title->setText(newTitle);
      customPlot->replot();
    }
  }
}

void mGraph::axisLabelDoubleClick(QWidget *parent, QCPAxis *axis, QCPAxis::SelectablePart part, QCustomPlot *customPlot)
{
  // Set an axis label by double clicking on it
  if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
  {
    bool ok;
    QString newLabel = QInputDialog::getText(parent, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
    if (ok)
    {
      axis->setLabel(newLabel);
      customPlot->replot();
    }
  }
}

void mGraph::legendDoubleClick(QWidget *parent, QCPLegend *legend, QCPAbstractLegendItem *item, QCustomPlot *customPlot)
{
  // Rename a graph by double clicking on its legend item
  Q_UNUSED(legend)
  if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
  {
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(parent, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok)
    {
      plItem->plottable()->setName(newName);
      customPlot->replot();
    }
  }
}

void mGraph::selectionChanged(QCustomPlot *customPlot)
{
  /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    customPlot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    customPlot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || customPlot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    customPlot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    customPlot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }

  // synchronize selection of graphs with selection of corresponding legend items:
  for (int i=0; i<customPlot->graphCount(); ++i)
  {
    QCPGraph *graph = customPlot->graph(i);
    QCPPlottableLegendItem *item = customPlot->legend->itemWithPlottable(graph);
    if (item->selected() || graph->selected())
    {
      item->setSelected(true);
      graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
    }
  }
}

void mGraph::mousePress(QCustomPlot *customPlot)
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged

  if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    customPlot->axisRect()->setRangeDrag(customPlot->xAxis->orientation());
  else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    customPlot->axisRect()->setRangeDrag(customPlot->yAxis->orientation());
  else
    customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void mGraph::mouseWheel(QCustomPlot *customPlot)
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    customPlot->axisRect()->setRangeZoom(customPlot->xAxis->orientation());
  else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    customPlot->axisRect()->setRangeZoom(customPlot->yAxis->orientation());
  else
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void mGraph::addRandomGraph(QCustomPlot *customPlot)
{
  int n = 50; // number of points in graph
  double xScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double yScale = (rand()/(double)RAND_MAX + 0.5)*2;
  double xOffset = (rand()/(double)RAND_MAX - 0.5)*4;
  double yOffset = (rand()/(double)RAND_MAX - 0.5)*10;
  double r1 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r2 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r3 = (rand()/(double)RAND_MAX - 0.5)*2;
  double r4 = (rand()/(double)RAND_MAX - 0.5)*2;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; i++)
  {
    x[i] = (i/(double)n-0.5)*10.0*xScale + xOffset;
    y[i] = (qSin(x[i]*r1*5)*qSin(qCos(x[i]*r2)*r4*3)+r3*qCos(qSin(x[i])*r4*2))*yScale + yOffset;
  }

  customPlot->addGraph();
  customPlot->graph()->setName(QString("Grafik %1").arg(customPlot->graphCount()-1));
  customPlot->graph()->setData(x, y);
  customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5+1));
  if (rand()%100 > 50)
    customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+1)));
  QPen graphPen;
  graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
  graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
  customPlot->graph()->setPen(graphPen);
  customPlot->replot();
}

void mGraph::removeSelectedGraph(QCustomPlot *customPlot)
{
  if (customPlot->selectedGraphs().size() > 0)
  {
    customPlot->removeGraph(customPlot->selectedGraphs().first());
    customPlot->replot();
  }
}

void mGraph::removeAllGraphs(QCustomPlot *customPlot)
{
  customPlot->clearGraphs();
  customPlot->replot();
}

void mGraph::contextMenuRequest(QWidget *parent, QPoint pos, QCustomPlot *customPlot)
{
  QMenu *menu = new QMenu(parent);
  menu->setAttribute(Qt::WA_DeleteOnClose);

  if (customPlot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
  {
//    menu->addAction("Move to top left", parent, SLOT(grafik_moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
//    menu->addAction("Move to top center", parent, SLOT(grafik_moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
//    menu->addAction("Move to top right", parent, SLOT(grafik_moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
//    menu->addAction("Move to bottom right", parent, SLOT(grafik_moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
//    menu->addAction("Move to bottom left", parent, SLOT(grafik_moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
  } else  // general context menu on graphs requested
  {
    menu->addAction("Add random graph", parent, SLOT(grafik_addRandomGraph()));
    if (customPlot->selectedGraphs().size() > 0)
      menu->addAction("Remove selected graph", parent, SLOT(grafik_removeSelectedGraph()));
    if (customPlot->graphCount() > 0)
      menu->addAction("Remove all graphs", parent, SLOT(grafik_removeAllGraphs()));
  }

  menu->popup(customPlot->mapToGlobal(pos));
}

void mGraph::moveLegend(QCustomPlot *customPlot)
{
  if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure parent slot is really called by a context menu action, so it carries the data we need
  {
    bool ok;
    int dataInt = contextAction->data().toInt(&ok);
    if (ok)
    {
      customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
      customPlot->replot();
    }
  }
}

void mGraph::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
  // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
  // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
  qDebug() << message;
//  statusBar->showMessage(message, 2500);
}
