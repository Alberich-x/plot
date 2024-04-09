#include "MyGraphicsScene.h"


void MyGraphicsView::paintEvent(QPaintEvent* event)
{
    qDebug() << "flag:" << flag;
	switch (flag)
	{
	case 0:
	{
		QGraphicsView::paintEvent(event);
		QPainter painter(viewport());
		if (!this->_selectRec.isNull())
		{
			painter.setPen(Qt::red);
			painter.drawRect(this->_selectRec);
		}
		break;
	}


	case 1:
	{
        qDebug() << "error enter";
		QGraphicsView::paintEvent(event);
		//QPainter painter(viewport());
		//if (!this->_selectRec.isNull())
		//{
		//	painter.setPen(Qt::red);
		//	painter.drawRect(this->_selectRec);
		//}
		break;
	}




    case 4: //结合并显示
    {

        QGraphicsScene* combinedScene = new QGraphicsScene;
        foreach(QGraphicsItem * item, _scene2->items()) {
            combinedScene->addItem(item);
        }

        foreach(QGraphicsItem * item, _scene1->items()) {
            combinedScene->addItem(item);
        }

        // 设置场景矩形以适应所有项
        combinedScene->setSceneRect(combinedScene->itemsBoundingRect());

        this->setScene(combinedScene);
        this->setRenderHint(QPainter::Antialiasing, true);
        this->setRenderHint(QPainter::SmoothPixmapTransform, true);
        break;
    }


    case 5://切换为纯数据
    {
        qDebug() << "Set scene to _scene1";
        this->setScene(_scene1);
        this->setRenderHint(QPainter::Antialiasing, true);
        this->setRenderHint(QPainter::SmoothPixmapTransform, true);
        break;




    }

 






    case 6:
    {





        QGraphicsView::paintEvent(event);
        
        QVector<qreal> dashes;
        dashes << 9 << 5;
        QPen pen;


        _painterViewport = new QPainter(viewport());
        // 清除之前的内容
        _painterViewport->fillRect(viewport()->rect(), Qt::transparent);



        pen.setDashPattern(dashes);
        _painterViewport->setPen(pen);
        // 清除之前的内容
        //_painterViewport->fillRect(viewport()->rect(), Qt::transparent);


        // *非常重要, 需要根据当前视图坐标进行寻找坐标, 然后根据所获得的场景坐标进行转换*
        QTransform viewtransform = viewportTransform();
        QRectF visibleRect = viewport()->rect();
        QRectF sceneRect = viewtransform.inverted().mapRect(visibleRect);
        qDebug() << "SceneRect: " << sceneRect;


        qreal spv = sceneRect.topLeft().y();
        qreal epv = sceneRect.bottomRight().y();
        qreal height_each = qreal(viewport()->height()) / (10 * 5);
        //for (int i = 0; i < 5; i++)
        //{
        //    _painterViewport->drawLine(0, height_each * 5 *(i+1), viewport()->width(), height_each * 5 * (i + 1));
        //}

        qreal first_line = spv + (height_each * 5 - (fmod(spv, height_each * 5)));
        qreal last_line = epv - (fmod(epv, height_each*5));
        qDebug() << "spv: " << spv << "epv: " << epv << "height_each: " << height_each * 5;
        qDebug() << "first_line:" << first_line << "last_line:" << last_line;
        auto numberOfLine = (last_line-first_line) / (height_each * 5) ;
        qDebug() << "NumberOfLine_cal: " << numberOfLine;
        if (last_line < first_line)
        {
            qDebug() << "No hline";
            break;
        }
  

        numberOfLine += 1;

        qreal ratio_rect = (epv - spv) / (viewport()->height());
        qDebug() << "My Caculate:" << ratio_rect << "Gpt Caculate: " << ratio_gpt;
        qreal interval_rect = height_each * 5 / ratio_rect;
        qDebug() << "interval_rect" << interval_rect;
        qreal line_iter = (first_line - spv) / (epv - spv) * viewport()->height();
        qreal length = viewport()->width();

        for (int i = 0; i < numberOfLine; i++)
        {
            _painterViewport->drawLine(0, line_iter, length, line_iter);
            line_iter += interval_rect;
        }







        flag = 1;
        break;
    }

    case 7:     //绘制数据测试.首先实现sin函数
    {
        _scene1 = new QGraphicsScene;
        width = this->viewport()->width();
        height = this->viewport()->height();
        qreal height_each = this->viewport()->height() / (10 * 5);
        for (qreal i = 0; i < 5000; i += 0.1)
        {
            _DataSin.push_back(QPointF(i*50, qreal(sin(i))*50 + height_each * 5));
        }

        QPainterPath path(_DataSin[0]);

        for (int i = 0; i < _DataSin.size() - 1; i++)
        {
            QPointF sp = _DataSin[i];
            QPointF ep = _DataSin[i+1];
            QPointF c1 = QPointF((sp.x()+ep.x())/2, (sp.y() + ep.y())/2);
            path.quadTo(c1, ep);
        }
        QPen pen(Qt::black);
        QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
        _scene1->addItem(pathItem);
        std::cout << "_scene1 done\n";
        this->setScene(_scene1);
        this->setRenderHint(QPainter::Antialiasing, true);
        this->setRenderHint(QPainter::SmoothPixmapTransform, true);
        flag = 0;
    }



    case 8:
    {
        _scene2 = new QGraphicsScene;
        //临时, 之后y轴大小会更改为图片大小, x轴则会根据结构内的数据更改
        width = this->viewport()->width();
        height = this->viewport()->height() - 17;
        qDebug() << "Width: " << width << "Height: " << height;
        QPixmap img_pix(width, height);
        img_pix.fill(Qt::transparent);
        //int width_each = img_pix.width() / 10;
        qreal width_each = 50;
        qreal height_each = qreal(img_pix.height()) / (10 * 5);
        qDebug() << height_each * 5;

        QPainter painter(&img_pix);
        QPen pen1, pen2;
        pen1.setColor(QColor("#787878"));
        pen2.setColor(QColor("#C0C0C0"));
        QVector<qreal> dashes;
        dashes << 9 << 5;
        pen1.setDashPattern(dashes);
        painter.setPen(pen1);
        for (int i = height_each * 5; i < height; i += height_each * 5)
        {
            painter.drawLine(0, i, width, i);
        }
        painter.setPen(pen2);

        for (int i = width_each; i < width; i += width_each)
        {
            int cnt = 0; //临时变量, 以后会根据结构体内的数值确定
            for (int j = height_each; j < height; j += height_each)
            {
                if (cnt == 4)
                {
                    cnt = 0;
                    continue;
                }
                //横线
                painter.drawLine(i - 1, j, i + 1, j);
                cnt++;
            }
            if (!(fmod(i, (width_each * 5))))
            {
                painter.drawLine(i, 0, i, height);
            }
        }
        _scene2->addPixmap(img_pix);
        _scene2->setSceneRect(img_pix.rect());



        QGraphicsScene* combinedScene = new QGraphicsScene;
        foreach(QGraphicsItem* item, _scene2->items()) {
            combinedScene->addItem(item);
        }

        foreach(QGraphicsItem* item, _scene1->items()) {
            combinedScene->addItem(item);
        }

        // 设置场景矩形以适应所有项
        combinedScene->setSceneRect(combinedScene->itemsBoundingRect());
        
        this->setScene(combinedScene);
        this->setRenderHint(QPainter::Antialiasing, true);
        this->setRenderHint(QPainter::SmoothPixmapTransform, true);
        
        flag = 0;

        break;
    }



	case 9: 
	{
        _scene4 = new QGraphicsScene;
        //临时, 之后会修改为每个结构自带的数据
		qreal width = this->viewport()->width();
		qreal height = this->viewport()->height();
        QPixmap img_pix(width, height);
        int width_each = img_pix.width() / 10;
        int height_each = img_pix.height() / 15;
        img_pix.fill(Qt::white);
        QPainter painter(&img_pix);

        //h刻度线笔刷
        QPen pen(Qt::black);
        pen.setColor(QColor("#787878"));
        QPen pen2(Qt::black);
        QVector<qreal> dashes;
        dashes << 9 << 5;
        pen.setDashPattern(dashes);
        painter.setPen(pen);

        for (int i = height_each - 30; i < height; i += height_each)
        {
            painter.drawLine(0, i, width, i);
        }
        pen2.setColor(QColor("#C0C0C0"));
        painter.setPen(pen2);

        int tick_interval = height_each / 5;
        int tick_length = 1;
        //for (int i = width_each; i <= width; i += width_each)
        //{
        //    for (int j = i - width_each / 5; j > i - width_each; j -= width_each / 5)
        //    {
        //        for (int k = 0; k < height; k += tick_interval)
        //        {
        //            //painter.drawLine(j, k, j, k+tick_interval);
        //            painter.drawLine(j - tick_length, k, j + tick_length, k);
        //        }
        //    }
        //    for (int j = 0; j < height; j += tick_interval)
        //    {
        //        painter.drawLine(i, j, i, j + tick_interval);
        //        painter.drawLine(i - tick_length, j, i + tick_length, j);
        //    }
        //}
        _scene4->addPixmap(img_pix);
        //scene->setSceneRect(0, 0, view->viewport()->width(), view->viewport()->height());
        _scene4->setSceneRect(img_pix.rect());
        this->setScene(_scene4);
        this->setRenderHint(QPainter::Antialiasing, true);
        this->setRenderHint(QPainter::SmoothPixmapTransform, true);
        flag = 0;



	}

	default:
		break;
	}
}