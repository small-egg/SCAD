#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include "declarations.h"

#include <QFrame>
#include <QMap>
#include <QStandardItemModel>

class SceneWidget : public QFrame
{
    Q_OBJECT

    struct Params
    {
        qreal   length{0};
        qreal   heigth{0};
    };

public:
    enum StressType{NX, UX, SX};

public:
    explicit SceneWidget(QWidget *parent = Q_NULLPTR);

    void    setCores(QStandardItemModel* model)  { cores = model;  }
    void    setCLoads(QStandardItemModel* model) { cLoads = model; }
    void    setResult(const QVector<QVector<Stress>>& res);

    void    addCore(const Core& core);
    void    editCore(int index, const Core& core);
    void    removeCore(int index);

    void    addCLoad(int node, double f);

    void    setHasLeftSupport(bool has)  { hasLeftSupport = has; }
    void    setHasRightSupport(bool has) { hasRightSupport = has; }

    Core    core(int index) const;

public slots:
     void    setStressType(StressType type) { st = type; repaint(); }

protected:
    void    paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private: // Methods
    void    drawAxis(QPainter& painter);

    void    drawConstruction(QPainter& painter);
    void    drawCore(QPainter& painter, qreal length, qreal area, qreal X_BEGIN_POS);
    void    drawDistributedLoad(QPainter& painter, qreal length, const double Q, qreal X_BEGIN_POS);

    void    drawConcentratedLoads(QPainter& painter);
    void    drawConcentratedLoad(QPainter& painter,  const double F, qreal X_BEGIN_POS);

    void    drawLeftSupport(QPainter& painter, qreal xPos, qreal height);
    void    drawRightSupport(QPainter& painter, qreal xPos, qreal height);

    void    drawResult(QPainter& painter);

    qreal   stressVal(const Stress& stress) const;

    qreal   calcScale(const Params& params) const;
    Params  calcParams() const;

private:
    QStandardItemModel* cores;
    QStandardItemModel* cLoads;

    QVector<QVector<Stress>>  result;

    bool                hasLeftSupport{false};
    bool                hasRightSupport{false};

    const qreal X_BEGIN_POS = 20;

    qreal   scale{30};

    StressType st{SX};
};

#endif // SCENEWIDGET_H
