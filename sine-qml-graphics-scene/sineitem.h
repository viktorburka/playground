#ifndef SINEITEM_H
#define SINEITEM_H

#include <QtQuick/QQuickItem>

class SineItem : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(int degree READ degree WRITE setDegree NOTIFY degreeChanged)

public:
    SineItem(QQuickItem *parent = 0);
    ~SineItem();

    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

    int degree() const { return m_degree; }
    void setDegree(int num);

signals:
    void degreeChanged();

private:
    int m_segmentCount;
    int m_degree;
};

#endif

