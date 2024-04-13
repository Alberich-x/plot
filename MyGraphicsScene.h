#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H
#include <qgraphicsview.h>
#include <iostream>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <qdebug.h>
#include <cmath>
#include <qgraphicsitem.h>
#include <qscrollbar.h>
#include <QVector>
class MyGraphicsView : public QGraphicsView {
	Q_OBJECT
public:
	MyGraphicsView(QWidget* parent = nullptr) : QGraphicsView(parent) {
		update();
		//this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	};
	MyGraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr) : QGraphicsView(scene, parent) {};
private:
	QPainter* _painterViewport;


	bool _isSelect;
	bool _isScale = false;
	QGraphicsScene* _scene1;	//�洢����ͼֽ
	QGraphicsScene* _scene2;	//�洢��ʼ��С�̶���
	QGraphicsScene* _scene3;	//��ʱscene, �洢��̬������
	QGraphicsScene* _scene4;	//�洢��ʼ��ҳ��ͼ��, ������ʹ�ú�ɾ��
	QGraphicsScene* _scene5;
	QGraphicsScene* _sceneCS;

	float width;
	float height;

	QRectF _selectRec, _selectRecNow, _thisRec;
	QPoint _selectPos;
	QPoint _startPos;
	int flag = 7;

	float ratio_gpt;
	// 0: select״̬, 1: ����״̬, 2: measure״̬, 6:������ʱͼ��. 7:��������ͼ��,  8:��ʾ�������ݺ��������, 9: ��ʼ��ͼƬ

	//QVector<QPointF> _DataSin;
	struct data_set {
		QVector<QPointF> dataset;
		QPainterPath path;
	};
	QVector<data_set> _dataSin;

	QRectF caculateMinRect()
	{
		float width_now = _selectRec.width();
		float height_now = _selectRec.height();
		float ratio_wh = float(viewport()->width()) / float(viewport()->height());
		//if (width_now / ratio_wh > height_now)
		if (0)
		{
			return QRectF(_selectRec.topLeft().x(), _selectRec.topLeft().y(), width_now, width_now / ratio_wh);
		}
		else
		{
			return QRectF(_selectRec.topLeft().x(), _selectRec.topLeft().y(), height_now * ratio_wh, height_now);
		}
	}




protected:
	void mouseMoveEvent(QMouseEvent* event) override
	{
		switch (flag)
		{
		case 0:
		{
			_selectPos = event->pos();
			_selectRec.setBottomRight(_selectPos);
			//qDebug() << _selectRec.width() << _selectRec.height();

			viewport()->update();

			break;
		}

		case 1:
		{
			break;
		}
		default:
			break;
		}
	}
	void mousePressEvent(QMouseEvent* event)override
	{
		switch (flag)
		{
		case 0:
		{
			_isSelect = true;
			_selectPos = event->pos();
			_startPos = _selectPos;
			qDebug() << event->pos();
			_selectRec.setTopLeft(_selectPos);
			break;
		}
		case 1:
		{
			qDebug() << "reset " << flag;
			this->resetTransform();
			viewport()->repaint();
			flag = 4;
			viewport()->repaint();
			flag = 1;
		}
		default:
			break;
		}

	}
	void mouseReleaseEvent(QMouseEvent* event)override
	{
		switch (flag)
		{
		case 0:
		{

			//flag = 5;
			//viewport()->repaint();


			//_selectRecNow = caculateMinRect();
			flag = 0;
			//_selectRec = QRectF();

			_isSelect = false;
			QRectF _selectRecNow = mapToScene(QRect(_startPos, event->pos())).boundingRect();
			_selectRecNow = mapToScene(QRect(_selectRec.topLeft().toPoint(), _selectRec.bottomRight().toPoint())).boundingRect();
			//�ɰ�, ����ֱ������
			//flag = 5;
			//viewport()->repaint();
			//fitInView(_thisRec, Qt::KeepAspectRatio);
			//_isScale = true;
			//viewport()->repaint();
			flag = 6;
			viewport()->repaint();
			flag = 1;
			break;
		}

		case 1:
		{
			flag = 0;
			qDebug() << "Set the flag to 0";
			break;
		}
		default:
			break;
		}
	}
	void MyGraphicsView::wheelEvent(QWheelEvent* event) override
	{
		switch (flag)
		{
		case 0:
		{
			int delta = event->angleDelta().y();
			horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta);
			break;
		}
		case 1:
		{
			viewport()->update();
			int delta = event->angleDelta().y();
			horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta);
			flag = 5;
			break;
		}
		default:
			break;
		}
	}





	void paintEvent(QPaintEvent* event) override;

signals:
	//void sendRec(QRect rec);
	//void sendPos(QPoint pos);
};


#endif



