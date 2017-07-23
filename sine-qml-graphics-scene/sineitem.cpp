#include <QtQuick/qsgnode.h>
#include <QtQuick/qsgflatcolormaterial.h>

#include "math.h"

#include "sineitem.h"

#define PI 3.14159265

SineItem::SineItem(QQuickItem *parent)
    : QQuickItem(parent)
    , m_segmentCount(36)
    , m_degree(0)
{
    setFlag(ItemHasContents, true);
}

SineItem::~SineItem()
{
}

void SineItem::setDegree(int num)
{
    if (m_degree == num)
        return;

    m_degree = num;
    emit degreeChanged();
    update();
}

QSGNode *SineItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGGeometryNode *node = 0;
    QSGGeometry *geometry = 0;

    if (!oldNode) {
        node = new QSGGeometryNode;
        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), m_segmentCount);
        geometry->setLineWidth(2);
        geometry->setDrawingMode(GL_LINE_STRIP);
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(QColor(153, 0, 153));
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    } else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(m_segmentCount);
    }

    int param = degree();
    int x = 0;
    QRectF bounds = boundingRect();
    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
    for (int i = 0; i < m_segmentCount; ++i) {

        double y = sin((param%360)*PI/180) + 1;

        double final_x = bounds.x() + x/360.0 * bounds.width();
        double final_y = bounds.y() + y/2.0 * bounds.height();

        vertices[i].set(final_x, final_y);
        param += 10;
        x += 10;
    }
    node->markDirty(QSGNode::DirtyGeometry);

    return node;
}
