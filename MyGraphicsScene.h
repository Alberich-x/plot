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
#include <QTimer>
#include <chrono>
class MyGraphicsView : public QGraphicsView {
	Q_OBJECT
public:
	MyGraphicsView(QWidget* parent = nullptr) : QGraphicsView(parent) {
		update();
		this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		this->horizontalScrollBar()->setMinimum(0);

	};
	MyGraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr) : QGraphicsView(scene, parent) {};


	int flag = 7;
private:
	const int MAX_PIXMAP = 32768;


	QPainter* _painterViewport;
	QVector<QPainterPath> _ppRatio;

	bool _isSelect;
	bool _isScale = false;
	QGraphicsScene* _scene1;	//存储数据图纸
	QGraphicsScene* _scene2;	//存储初始大小刻度线
	QGraphicsScene* _scene3;	//临时scene, 存储动态坐标轴
	QGraphicsScene* _scene4;	//存储初始化页面图形, 可以在使用后删除
	QGraphicsScene* _scene5;
	QGraphicsScene* _sceneCS;
	QGraphicsScene* _sceneMeasure;

	float width;
	float height;

	QRectF _selectRec, _selectRecNow, _thisRec;
	QLine _selectLine, _measureLine;
	QPointF _selectPos;
	QPointF _startPos;
	QPointF _vln;

	QVector<qreal> _lineVectorGlobal;

	QPainterPath pathQuickChange(qreal ratio_x, qreal ratio_y, QPainterPath pathToChange);




	float ratio_gpt;
	// 0: select状态, 1: 缩放状态, 2: measure状态, 6:绘制临时图形. 7:绘制数据图形,  8:显示导入数据后的坐标轴, 9: 初始化图片
	// 98: 绘制为原图, 99: 没有任何功能状态

	//QVector<QPointF> _DataSin;
	struct data_set {
		QVector<QPointF> dataset;
		QPainterPath path;
	};
	QVector<data_set> _dataSin;
	QVector<data_set> _dataSinRatio;

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
		case 11:
		{
			_selectPos = event->pos();
			_selectLine.setP2(_selectPos.toPoint());
			viewport()->update();
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
			_selectRec.setTopLeft(_selectPos);
			break;
		}
		case 1:
		{
			qDebug() << "reset " << flag;
			flag = 4;
			viewport()->repaint();
			flag = 1;
			break;
		}
		case 11:
		{
			_selectPos = event->pos();
			_startPos = _selectPos;
			_selectLine.setP1(event->pos());
			break;
		}

		case 99:
		{
			if (_isScale)
			{
				flag = 98;
				viewport()->repaint();
				flag = 99;
			}
			break;
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
			if (_selectRec.isEmpty())
			{
				_selectRec = QRectF();
				return;
			}

			//flag = 5;
			//viewport()->repaint();


			//_selectRecNow = caculateMinRect();
			flag = 0;


			_isSelect = false;
			//QRectF _selectRecNow = mapToScene(QRect(_startPos, event->pos())).boundingRect();
			_selectRecNow = mapToScene(QRect(_selectRec.topLeft().toPoint(), _selectRec.bottomRight().toPoint())).boundingRect();
			_selectRec = QRectF();
			//旧案, 用于直接缩放
			//flag = 5;
			//viewport()->repaint();
			//fitInView(_thisRec, Qt::KeepAspectRatio);
			//_isScale = true;
			//viewport()->repaint();
			flag = 6;
			//viewport()->repaint();
			viewport()->update();
			break;
		}

		case 1:
		{
			flag = 0;
			qDebug() << "Set the flag to 0";
			break;
		}

		case 11:
		{
			_selectLine = QLine();
			flag = 12;
			//viewport()->repaint();
			viewport()->update();
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
			//qDebug() << horizontalScrollBar()->value() << sceneRect().width();
			int delta = event->angleDelta().y();
			horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta);
			flag = 5;
			break;
		}
		case 99:
		{
			int delta = event->angleDelta().y();
			horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta);
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



