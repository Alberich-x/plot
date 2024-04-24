#include "MyGraphicsScene.h"


void MyGraphicsView::paintEvent(QPaintEvent* event)
{
    //qDebug() << "flag:" << flag;
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




    case 4: //显示结合scene
    {
        QGraphicsView::paintEvent(event);
        _vln = mapToScene(viewport()->rect().topLeft());
        qreal ratio_position = _vln.x() / _scene5->width();



        // 设置场景矩形以适应所有项
        //combinedScene->setSceneRect(combinedScene->itemsBoundingRect());
        this->setScene(nullptr);
        this->setScene(_sceneCS);
        this->setRenderHint(QPainter::Antialiasing, true);
        this->setRenderHint(QPainter::SmoothPixmapTransform, true);
        this->horizontalScrollBar()->setValue(this->_vln.x() / _scene5->width() * _scene1->width());
        this->horizontalScrollBar()->setMinimum(0);
        flag = 1;
        _isScale = false;
        break;
    }


    case 5://重新绘制
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


        //// *非常重要, 需要根据当前视图坐标进行寻找坐标, 然后根据所获得的场景坐标进行转换*
        //QTransform viewtransform = viewportTransform();
        //QRectF visibleRect = viewport()->rect();
        //QRectF sceneRect = viewtransform.inverted().mapRect(visibleRect);
        //qDebug() << "SceneRect: " << sceneRect;


        qreal spv = _selectRecNow.topLeft().y();
        qreal epv = _selectRecNow.bottomRight().y();
        qreal height_each = qreal(viewport()->height()) / (10 * 5);
        //for (int i = 0; i < 5; i++)
        //{
        //    _painterViewport->drawLine(0, height_each * 5 *(i+1), viewport()->width(), height_each * 5 * (i + 1));
        //}

        qreal first_line = spv + (height_each * 5 - (fmod(spv, height_each * 5)));
        qreal last_line = epv - (fmod(epv, height_each * 5));
        //qDebug() << "spv: " << spv << "epv: " << epv << "height_each: " << height_each * 5;
        //qDebug() << "first_line:" << first_line << "last_line:" << last_line;
        auto numberOfLine = (last_line - first_line) / (height_each * 5);
        //qDebug() << "NumberOfLine_cal: " << numberOfLine;
        if (last_line < first_line)
        {
            qDebug() << "No hline";
            break;
        }


        numberOfLine += 1;

        qreal ratio_rect = (epv - spv) / (viewport()->height());
        qreal interval_rect = height_each * 5 / ratio_rect;
        //qDebug() << "interval_rect" << interval_rect;
        qreal line_iter = (first_line - spv) / (epv - spv) * viewport()->height();
        qreal length = viewport()->width();

        for (int i = 0; i < numberOfLine; i++)
        {
            _painterViewport->drawLine(0, line_iter, length, line_iter);
            line_iter += interval_rect;
        }
        _painterViewport->end();
        flag = 1;
        
        break;

    }








    case 6:
    {

        QPointF ltpv = mapToScene(viewport()->rect().topLeft());
        QRectF newSceneRect = sceneRect().translated(QPointF(0, 0) - ltpv);
        setSceneRect(newSceneRect);
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


        //// *非常重要, 需要根据当前视图坐标进行寻找坐标, 然后根据所获得的场景坐标进行转换*
        //QTransform viewtransform = viewportTransform();
        //QRectF visibleRect = viewport()->rect();
        //QRectF sceneRect = viewtransform.inverted().mapRect(visibleRect);
        //qDebug() << "SceneRect: " << sceneRect;


        qreal spv = _selectRecNow.topLeft().y();
        qreal epv = _selectRecNow.bottomRight().y();
        qreal height_each = qreal(viewport()->height()) / (10 * 5);

        qreal sph = _selectRecNow.topLeft().x();
        qreal eph = _selectRecNow.bottomRight().x();

        qreal first_line = spv + (height_each * 5 - (fmod(spv, height_each * 5)));
        qreal last_line = epv - (fmod(epv, height_each * 5));
        auto numberOfLine = (last_line - first_line) / (height_each * 5);
        if (last_line < first_line)
        {
            qDebug() << "No hline";
            break;
        }


        numberOfLine += 1;

        qreal ratio_rect = (epv - spv) / (viewport()->height());
        qreal interval_rect = height_each * 5 / ratio_rect;
        //qDebug() << "interval_rect" << interval_rect;
        qreal line_iter = (first_line - spv) / (epv - spv) * viewport()->height();
        //qDebug() << "Line_iter: " << line_iter;
        qreal length = viewport()->width();

        //for (int i = 0; i < numberOfLine; i++)
        //{
        //    _painterViewport->drawLine(0, line_iter, length, line_iter);
        //    line_iter += interval_rect;
        //}



        //图片缩放


        //qreal ratio_horizon = (eph - sph) / viewport()->width();
        //qreal ratio_vertical = (epv - spv) / viewport()->height();
        //for (int i = 0; i < _dataSin.size(); i++)
        //{
        //    data_set x;
        //    x.path = pathQuickChange(ratio_horizon, ratio_vertical, _dataSin[i].path);
        //    x.dataset = _dataSin[i].dataset;
        //    _dataSinRatio.push_back(x);
        //}
        //qDebug() << _dataSinRatio.size();
        //QRectF viewportRect = viewport()->rect();
        //// 设置场景的大小为与视口相同
        //scene()->setSceneRect(viewportRect);

        //_scene5 = new QGraphicsScene();




        //foreach(auto x, _dataSinRatio)
        //{
        //    QGraphicsPathItem* path_item = new QGraphicsPathItem(x.path);
        //    _scene5->addItem(path_item);
        //}



        //_painterViewport->end();
        //this->setScene(_scene5);
        //connect(_scene5, &QGraphicsScene::changed, this, [this]() {
        //    flag = 5;
        //    _isScale = true;
        //    this->update();
        //});




        











        
        //进行图片缩放
        //spv = _selectRecNow.topLeft().y();
        //epv = _selectRecNow.bottomRight().y();
        //height_each = qreal(viewport()->height()) / (10 * 5);




        qreal scale_horizon = float(viewport()->width()) / _selectRec.width();
        qreal scale_vertical = float(viewport()->height()) / _selectRec.height();

        //qDebug() << "First line: " << first_line << "LastLine: " << last_line;
        int first_data = first_line / (height_each * 5);
        int last_data = last_line / (height_each * 5);
        int number_data = last_data - first_data;
        qreal data_iter = (first_line - spv) / (epv - spv) * viewport()->height();
        //qDebug() << "data_iter: " << data_iter;

        //QPointF vp_lt = mapToScene(viewport()->rect().topLeft());
        //QPointF vp_fl = mapToScene(QPoint(0, first_line));




        QVector<QPainterPath> pp_this;
        qreal cnt_path = 0;

        QRectF viewportRect = viewport()->rect();
        // 设置场景的大小为与视口相同
        scene()->setSceneRect(viewportRect);

        qreal ratio_horizon = (eph - sph) / viewport()->width();
        qreal ratio_vertical = (epv - spv) / viewport()->height();

        //时间测量套组
        std::chrono::steady_clock::time_point start_time, end_time;
        start_time = std::chrono::steady_clock::now();

        for (int i = first_data; i <= last_data; i++)
        {
            QPainterPath path_this = QPainterPath(QPointF(_dataSin[i].dataset[0].x(), _dataSin[i].dataset[0].y()));
            for (int j = 1; j < _dataSin[i].dataset.size() - 1; j++)
            {
                //QPointF sp = _dataSin[i].dataset[j];
                //sp.setY(sp.y() / ratio_vertical + data_iter);
                //sp.setX(sp.x() / ratio_horizon);
                QPointF ep = _dataSin[i].dataset[j + 1];
                ep.setY(ep.y() / ratio_vertical + data_iter);
                ep.setX(ep.x() / ratio_horizon);
                //QPointF c1 = QPointF((sp.x() + ep.x()) / 2, (sp.y() + ep.y()) / 2);
                //path_this.quadTo(c1, ep);
                path_this.lineTo(ep);
            }
            data_iter += interval_rect;
            
            pp_this.push_back(mapToScene(path_this));
            _ppRatio = pp_this;
        }
        end_time = std::chrono::steady_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        qDebug() << "Time to paint path: " << duration_ms.count();



        _scene5 = new QGraphicsScene(); 
        foreach(QPainterPath x, pp_this)
        {
            QGraphicsPathItem* path_item = new QGraphicsPathItem(x);
            _scene5->addItem(path_item);
        }


        //纵向刻度线绘制
        qreal first_line_each = spv + height_each - fmod(spv, height_each);
        qreal last_line_each = epv - (fmod(epv, height_each));
        qreal first_line_each_ratio = (first_line_each - spv) / (epv - spv) * viewport()->height();
        QVector<QPixmap> pixmap_scale;

        









        this->setScene(nullptr);
        this->setScene(_scene5);
        this->setRenderHint(QPainter::Antialiasing, true);
        this->setRenderHint(QPainter::SmoothPixmapTransform, true);

        //for (int i = 0; i < numberOfLine; i++)
        //{
        //    _painterViewport->drawLine(0, line_iter, length, line_iter);
        //    line_iter += interval_rect;
        //}

        _painterViewport->end();


        this->horizontalScrollBar()->setValue(sph / _scene1->width() * _scene5->width());


        //flag = 5;
        connect(_scene5, &QGraphicsScene::changed, this, [this]() {
            flag = 5;
            _isScale = true;
            qDebug() << "Scene_5 changed";
            this->update();
            });
            
        break;
    }

    case 7:     //绘制数据测试.首先实现sin函数
    {
        QPointF ltpv = mapToScene(viewport()->rect().topLeft());
        QRectF newSceneRect = sceneRect().translated(QPointF(0, 0) - ltpv);
        setSceneRect(newSceneRect);
        _scene1 = new QGraphicsScene;
        //width = this->viewport()->width();
        height = this->viewport()->height();
        qreal height_each = this->viewport()->height() / (10 * 5);
        qreal height_now = height_each * 5;
        int cnt_ite = 0;
        for (int i = 0; i < 10; i++)
        {
            QVector<QPointF> point_this;
            data_set dataSet_this;
            for (qreal j = 0; j < 5000; j += 0.1)
            {
                point_this.push_back(QPointF(j * 50, qreal(sin(j)) * 30));
            }
            dataSet_this.dataset = point_this;
            dataSet_this.path = QPainterPath(point_this[0]);
            //dataSet_this = { point_this, path_this };
            _dataSin.push_back(dataSet_this);
        }




        int cnt = 0;
        //QPainterPath path(_DataSin[0]);
        for (auto dataToEdit0 = _dataSin.begin(); dataToEdit0 != _dataSin.end(); dataToEdit0++) {
            auto dataToEdit = *dataToEdit0;
            cnt++;
            for (int i = 1; i < dataToEdit.dataset.size() - 1; i++)
            {
                QPointF sp = dataToEdit.dataset[i];
                sp.setY(sp.y() + height_each * 5 * cnt);
                QPointF ep = dataToEdit.dataset[i + 1];
                ep.setY(ep.y() + height_each * 5 * cnt);
                //QPointF c1 = QPointF((sp.x() + ep.x()) / 2, (sp.y() + ep.y()) / 2);
                //dataToEdit.path.quadTo(c1, ep);
                dataToEdit.path.lineTo(ep);
            }
            QPainterPath::Element firstElement = dataToEdit.path.elementAt(0);
            firstElement.y += cnt * height_each * 5;
            dataToEdit.path.setElementPositionAt(0, firstElement.x, firstElement.y);
            *dataToEdit0 = dataToEdit;
        }
        foreach(data_set dataToEdit, _dataSin)
        {
            QGraphicsPathItem* pathItem = new QGraphicsPathItem(dataToEdit.path);
            _scene1->addItem(pathItem);
        }
        //std::cout << "_scene1 done\n";
        //this->setScene(_scene1);
        //this->setRenderHint(QPainter::Antialiasing, true);
        //this->setRenderHint(QPainter::SmoothPixmapTransform, true);
        
        flag = 0;
    }



    case 8:
    {
        _scene2 = new QGraphicsScene;
        //临时, 之后y轴大小会更改为图片大小, x轴则会根据结构内的数据更改
        //width = this->viewport()->width();
        width = _scene1->width();
        height = this->viewport()->height() - 17;
        qDebug() << "Width: " << width << "Height: " << height;
        QPixmap img_pix(width, height);
        img_pix.fill(Qt::transparent);
        //int width_each = img_pix.width() / 10;
        qreal width_each = 80;
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



        QVector<QPixmap> pixmap;

        for (int j = 0; j <= width / MAX_PIXMAP; j++)
        {
            QPixmap pixmap_this( j == int(width/MAX_PIXMAP)?fmod(width, MAX_PIXMAP) : MAX_PIXMAP, height);
            pixmap_this.fill(Qt::transparent);
            QPainter painter_this(&pixmap_this);
            QPen pen_this;
            pen_this.setColor(QColor("#787878"));
            pen_this.setDashPattern(dashes);
            painter_this.setPen(pen_this);
            for (int i = height_each * 5; i < height; i += height_each * 5)
            {
                
                painter_this.drawLine(0, i, pixmap_this.width(), i);
                _lineVectorGlobal.push_back(i);
            }
            pixmap.push_back(pixmap_this);
        }
        //painter.setPen(pen2);

        //for (int i = width_each; i < width; i += width_each)
        //{
        //    int cnt = 0; //临时变量, 以后会根据结构体内的数值确定
        //    for (int j = height_each; j < height; j += height_each)
        //    {
        //        if (cnt == 4)
        //        {
        //            cnt = 0;
        //            continue;
        //        }
        //        //横线
        //        painter.drawLine(i - 1, j, i + 1, j);
        //        cnt++;
        //    }
        //    if (!(fmod(i, (width_each * 5))))
        //    {
        //        painter.drawLine(i, 0, i, height);
        //    }
        //}

        //纵向刻度线
        for (int i = width_each; i < width; i += width_each)
        {
            int x_this = fmod(i, MAX_PIXMAP);
            int cnt_this = 0;
            QPainter painter_this(&pixmap[i/MAX_PIXMAP]);
            QPen pen_this;
            pen_this.setColor(QColor("#C0C0C0"));
            painter_this.setPen(pen_this);
            for (int j = 0; j < height; j += height_each)
            {
                if (cnt_this == 4)
                {
                    cnt_this = 0;
                    continue;
                }
                painter_this.drawLine(x_this-1, j, x_this+1, j);
            }
            if (!fmod(i, (width_each * 5)))
            {
                painter_this.drawLine(x_this, 0, x_this, height);
            }
        }





        //现案
        int width_sum = 0;
        foreach(auto x, pixmap)
        {  
            QGraphicsItem* pixItem_this = _scene2->addPixmap(x);
            pixItem_this->setPos(width_sum, 0);
            width_sum += x.width();
        }
        _scene2->setSceneRect(img_pix.rect());



        //_scene2->addPixmap(pixmap[0]);
        //_scene2->setSceneRect(img_pix.rect());

        qDebug() << "_scene1 and _scene2 width and pixmap width: " << _scene1->width() << _scene2->width() << img_pix.width();

        QGraphicsScene* combinedScene = new QGraphicsScene;
        foreach(QGraphicsItem * item, _scene2->items()) {
            combinedScene->addItem(item);
        }

        foreach(QGraphicsItem * item, _scene1->items()) {
            combinedScene->addItem(item);
        }

        // 设置场景矩形以适应所有项
        combinedScene->setSceneRect(combinedScene->itemsBoundingRect());
        _sceneCS = new QGraphicsScene;
        _sceneCS = combinedScene;
        this->setScene(combinedScene);
        this->setRenderHint(QPainter::Antialiasing, true);
        this->setRenderHint(QPainter::SmoothPixmapTransform, true);

        flag = 99;

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

    case 10: {
        QGraphicsView::paintEvent(event);
        break;
    }


    case 11: //绘制测量线
    {
        QGraphicsView::paintEvent(event);
        QPainter painter(viewport());
        painter.setPen(Qt::red);

        painter.drawLine(_selectLine);
        break;
    }

    case 12://先用朴素算法， 在拿到数据后进行特化
    {
        QGraphicsView::paintEvent(event);






        qreal diffv_abs = 999999;
        int line_number = -1;
        for (int i = 0; i < _lineVectorGlobal.size(); i++)
        {
            qreal diffv_this = abs(_lineVectorGlobal[i] - _startPos.y());
            if (diffv_this < diffv_abs)
            {
                diffv_abs = diffv_this;
                line_number = i;
            }
        }
        //qDebug() << "line_number:" << line_number << "Size of _lineVectorGlobal: " << _lineVectorGlobal.size() << " Size of _ppRatio: " << _ppRatio.size();
        
        QPointF p1_this = mapToScene(_startPos.toPoint()), p2_this = mapToScene(_selectPos.toPoint());
        qDebug() << "p1_this and p2_this: " << p1_this << p2_this;
        qreal distance_this = abs(p1_this.x() - p2_this.x());
        QPointF p1_paint, p2_paint;
        qreal line_vertical = _lineVectorGlobal[line_number];

        //此处查询距离最近的x轴坐标(需要按数据类型特化, 要是全部随机则需要替换算法)
        /*
                    for (qreal j = 0; j < 5000; j += 0.1)
            {
                point_this.push_back(QPointF(j * 50, qreal(sin(j)) * 30));
            }
        */
        //此处间隔为5
        int sxn = p1_this.x() / 5;
        int exn = p2_this.x() / 5;
        //qDebug() << "sxn and exn: " << sxn << exn;
        qreal height_each = this->viewport()->height() / (10 * 5);
        qreal height_now = height_each * 5;



        p1_paint = _dataSin[line_number].dataset[sxn];
        p1_paint.setY(p1_paint.y() + height_now * (line_number + 1));
        p2_paint = _dataSin[line_number].dataset[exn];
        p2_paint.setY(p2_paint.y() + height_now * (line_number + 1));
        //qDebug() << "p1_paint: " << p1_paint << "p2_paint: " << p2_paint;
        p1_paint = mapFromScene(p1_paint);
        p2_paint = mapFromScene(p2_paint);
        _measureLine = QLine(p1_paint.toPoint(), p2_paint.toPoint());
        //_measureLine = QLine(_startPos.toPoint(), _selectPos.toPoint());
        //qDebug() << "p1_paint and p2_paint: " << p1_paint << p2_paint;
        QPainter painter_this(viewport());
        painter_this.setPen(Qt::red);
        painter_this.drawLine(_measureLine);
        //qDebug() << "_measureLine:" << _measureLine << "_startPos: " << _startPos << "_selectPos" << _selectPos ;





        flag = 11;

        break;
    }







    case 98:
    {
        QGraphicsView::paintEvent(event);
        _vln = mapToScene(viewport()->rect().topLeft());
        qreal ratio_position = _vln.x() / _scene5->width();

        // 设置场景矩形以适应所有项
        //combinedScene->setSceneRect(combinedScene->itemsBoundingRect());
        this->setScene(nullptr);
        this->setScene(_sceneCS);
        this->setRenderHint(QPainter::Antialiasing, true);
        this->setRenderHint(QPainter::SmoothPixmapTransform, true);
        this->horizontalScrollBar()->setValue(this->_vln.x() / _scene5->width() * _scene1->width());
        _isScale = false;
        this->horizontalScrollBar()->setMinimum(0);
        break;
    }


    case 99: {
        QGraphicsView::paintEvent(event);

        break;
    }






    default:
        break;
    }
}


QPainterPath MyGraphicsView::pathQuickChange(qreal ratio_x, qreal ratio_y, QPainterPath pathToChange)
{
    qDebug() << "ratio eot: " << ratio_x << ratio_y;
    QPointF center = pathToChange.boundingRect().center();
    QTransform transform;
    transform.translate(center.x(), center.y());
    transform.scale(ratio_x, ratio_y);
    transform.translate(-center.x(), -center.y());
    return transform.map(pathToChange);
}