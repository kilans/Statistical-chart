#include "widget.h"
#include "ui_widget.h"
void Widget::DRAWCHART()
{
    chart->removeAllSeries();
    chart->removeAxis(this->axisBX);
    chart->removeAxis(axisX);
    chart->removeAxis(axisY);
    chart->setTitle(ui->name->text());
    switch(ui->Datapage->currentIndex())        //根据当前页决定绘制图的类型
    {
    case 0:     BarCharts();ChartSet();BXYSet(Bseries);break;
    case 1:     PieCharts();chart->addSeries(Pseries);ChartSet();break;
    case 2:     if(ui->DrawChart->text()=="绘制")   ui->DrawChart->setText("复原");
                ChartSet();LineCharts();LXYSet(Lseries);;break;
     }
    ui->widget->hide();
    ui->widget->show();
}
void Widget::COLUMNCHANGED()
{
    switch(ui->Datapage->currentIndex())        //根据当前页决定添加行列的变化
    {
    case 0:
    {
        ui->Bardata->setColumnCount(ui->column->value());
        if(this->curBC<ui->column->value())
        for(int i=1;i<ui->Bardata->rowCount();i++)      //动态添加"0"活着"类"
        {
            ui->Bardata->setItem(i,ui->Bardata->columnCount()-1,new QTableWidgetItem("0"));
        }
        ui->Bardata->setItem(0,ui->Bardata->columnCount()-1,new QTableWidgetItem(QString("类%1").arg(ui->Bardata->columnCount()-1)));
        this->curBC=ui->column->value();
    }break;
    case 1:
    {
        ui->Piedata->setColumnCount(ui->column->value());
        if(this->curPC<ui->column->value())
        for(int i=1;i<ui->Piedata->rowCount();i++)
        {
            {
                ui->Piedata->setItem(i,ui->Piedata->columnCount()-1,new QTableWidgetItem("0"));
            }
            ui->Piedata->setItem(0,ui->Piedata->columnCount()-1,new QTableWidgetItem(QString("类%1").arg(ui->Piedata->columnCount())));
        }
        this->curPC=ui->column->value();
    }break;
    case 2:
    {
        ui->Linedata->setColumnCount(ui->column->value());
        if(this->curLC<ui->column->value())
        for(int i=1;i<ui->Linedata->rowCount();i+=3)
        {
            ui->Linedata->setItem(i,ui->Linedata->columnCount()-1,new QTableWidgetItem("0"));
            ui->Linedata->setItem(i+1,ui->Linedata->columnCount()-1,new QTableWidgetItem("0"));
        }
        ui->Linedata->setHorizontalHeaderItem(ui->Linedata->columnCount()-1,new QTableWidgetItem(QString::number(ui->Linedata->columnCount()-1)));
        this->curLC=ui->column->value();
    }break;
    }
}
void Widget::ROWCHANGED()
{
    switch(ui->Datapage->currentIndex())            //根据当前页决定行变化
    {
    case 0:
    {
        ui->Bardata->setRowCount(ui->row->value());
        if(this->curBR<ui->row->value())
        for(int i=1;i<ui->Bardata->columnCount();i++)
        {
            if(ui->Bardata->item(ui->Bardata->rowCount()-1,i)==NULL)
            {
                ui->Bardata->setItem(ui->Bardata->rowCount()-1,i,new QTableWidgetItem("0"));
                ui->Bardata->setItem(ui->Bardata->rowCount()-1,0,new QTableWidgetItem(QString("系列%1").arg(ui->Bardata->rowCount()-1)));
            }
        }
        this->curBR=ui->row->value();
    }break;
    case 2:
    {
        ui->Linedata->setRowCount(ui->row->value()*3);
        if(this->curLR<ui->row->value())
        {
            for(int i=1;i<ui->Linedata->columnCount();i++)
            {
                ui->Linedata->setItem(ui->Linedata->rowCount()-2,i,new QTableWidgetItem("0"));
                ui->Linedata->setItem(ui->Linedata->rowCount()-1,i,new QTableWidgetItem("0"));
            }
                ui->Linedata->setItem(ui->Linedata->rowCount()-3,0,new QTableWidgetItem(QString("系列%1").arg(ui->Linedata->rowCount()/3)));
                ui->Linedata->setItem(ui->Linedata->rowCount()-2,0,new QTableWidgetItem(QString("X")));
                ui->Linedata->setItem(ui->Linedata->rowCount()-1,0,new QTableWidgetItem(QString("Y")));
        }
        this->curLR=ui->row->value();
    }break;
    }
}

void Widget::DATAPAGECHANGED()
{
    *this->XYtag=1;
    switch(ui->Datapage->currentIndex())                        //根据当前页判定界面变化设计
    {
    case 0:
    {

        ui->widget_4->setParent(ui->Datapage->widget(0));
        ui->widget_4->show();
        ui->label_2->show();
        ui->Barwidth->show();
        ui->row->setValue(ui->Bardata->rowCount());
        ui->row->setMinimum(2);
        ui->column->setValue(ui->Bardata->columnCount());
        ui->row->show();
        ui->Float->hide();
        ui->Floatline->hide();
        ui->PieTool->hide();
        ui->BarYup->show();
        ui->BarYdown->show();
        ui->widget_2->show();
        ui->lineEdit_3->show();
        ui->Xdown->hide();
        ui->Xup->hide();
        ui->Ydown->hide();
        ui->Yup->hide();
        ui->lineEdit_4->hide();
        ui->label_3->hide();
        ui->DrawChart->setText("绘制");

    }break;
    case 1:
    {
        ui->widget_4->setParent(ui->Datapage->widget(1));
        ui->column->setMinimum(2);
        ui->widget_4->show();
        ui->Float->show();
        ui->Floatline->show();
        ui->column->setValue(ui->Piedata->columnCount());
        ui->row->hide();
        ui->widget_2->hide();
        ui->lineEdit_3->hide();
    }break;
    case 2:
    {
        ui->column->setMinimum(2);
        ui->widget_4->setParent(ui->Datapage->widget(2));
        ui->widget_4->show();
        ui->row->setMinimum(1);
        ui->row->setValue(ui->Linedata->rowCount()/3);
        ui->Float->hide();
        ui->Floatline->hide();
        ui->column->setValue(ui->Linedata->columnCount());
        ui->label_2->hide();
        ui->Barwidth->hide();
        ui->row->show();
        ui->PieTool->hide();
        ui->widget_2->show();
        ui->lineEdit_3->show();
        ui->BarYdown->hide();
        ui->BarYup->hide();
        ui->Xdown->show();
        ui->Xup->show();
        ui->Ydown->show();
        ui->Yup->show();
        ui->lineEdit_4->show();
        ui->label_3->show();
        ui->DrawChart->setText("绘制");
    }break;
    }
}
void Widget::LINECHANGED()              //折线表格的输入变化限制
{
    if(ui->Linedata->currentItem()&& ((ui->Linedata->currentRow()%3==1) ||(ui->Linedata->currentRow()%3==2)) && (ui->Linedata->currentColumn()!=0))
    {
        if(ui->Linedata->currentItem()->text()=="" ||  *(ui->Linedata->currentItem()->text().toLocal8Bit().data()) < 48 ||*(ui->Linedata->currentItem()->text().toLocal8Bit().data()) > 57)
        ui->Linedata->currentItem()->setText("0");
    }
    else if(ui->Linedata->currentItem() &&  ((ui->Linedata->currentRow()%3==1) ||(ui->Linedata->currentRow()%3==2)))
    {
        ui->Linedata->currentItem()->setText(QString("%1").arg(char(ui->Linedata->currentRow()%3+'W')));
    }
    ui->DrawChart->setText("绘制");
    *this->XYtag = 1;
}

void Widget::BARCHANGED()           //统计图表格的输入变化限制
{
    if(ui->Bardata->currentItem() && ui->Bardata->currentColumn()!=0 && ui->Bardata->currentRow() !=0)
    {
        if(ui->Bardata->currentItem()&&(ui->Bardata->currentItem()->text()=="" || *(ui->Bardata->currentItem()->text().toLocal8Bit().data()) < 48 ||*(ui->Bardata->currentItem()->text().toLocal8Bit().data()) > 57))
        ui->Bardata->currentItem()->setText("0");
        *XYtag=false;
        ui->DrawChart->setText("绘制");
    }
}
void Widget::SAVE()             //保存文件
{
    QImage *image=new QImage(ui->widget->grab().toImage());
    qDebug()<<"code"<<*code;
    QString filepath=QFileDialog::getSaveFileName(NULL,tr("选择路径"),"chart"+QString::number(*code)+".png","*.jpg *.png");
    if(filepath!="")
    {
        if(image->save(filepath))
        {
            file->open(QIODevice::WriteOnly);
            file->write(QString(QString::number((*code)++)).toLocal8Bit());
            file->close();
            QMessageBox::information(this,"info","保存成功");
        }
        else
            QMessageBox::information(this,"info","保存失败！");
    }
}

void Widget::LARGE()            //大页面设计
{
    if(*largetag)
    {
       ui->Datapage->setParent(Large);
       ui->Datapage->setFixedSize(Large->size());
       ui->Datapage->move(0,0);
        ui->widget_5->setParent(this);
        ui->widget_5->show();
        ui->widget_5->move(50,350);
        ui->Bardata->setFixedWidth(Large->width());
        ui->Bardata->setFixedHeight(Large->height()-100);
        ui->Piedata->setFixedWidth(Large->width());
        ui->Piedata->setFixedHeight(Large->height()-100);
        ui->Linedata->setFixedWidth(Large->width());
        ui->Linedata->setFixedHeight(Large->height()-100);
    ui->widget_4->move(Large->width()/2,Large->height()-80);
    ui->large->setParent(Large);
    ui->large->move(Large->width()-ui->large->width(),0);
    Large->show();
    *largetag = false;
    large2->show();
    }
  else                      //大页面恢复小页面
    {
        ui->widget_5->setParent(ui->Datapage);
        ui->widget_5->show();
        ui->widget_4->setParent(ui->Datapage);
        ui->widget_4->move(0,290);
        ui->widget_4->show();
        ui->Datapage->setParent(this);
        ui->Datapage->setFixedSize(411,441);
        ui->Bardata->setFixedSize(401,281);
        ui->Piedata->setFixedSize(401,281);
        ui->Linedata->setFixedSize(401,281);
        ui->large->setParent(ui->Datapage);
        ui->large->move(ui->Datapage->width()-ui->large->width()-8,0);
        ui->Datapage->show();
        Large->hide();
        large2->hide();
        *largetag = true;
    }
}
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{   
    ui->setupUi(this);
    file=new QFile("report.txt");
    if(file->open(QIODevice::ReadOnly))     //图片名规划
    {
        char ch;
        file->getChar(&ch);
        if( ch == EOF)
            *code=1;
        else
        {
            file->putChar(ch);
            *code=file->readAll().toInt();
        }
    }
    else
        *code=1;
    file->close();
    ui->large->setParent(ui->Datapage);
    ui->large->setFixedHeight(ui->large->height()+4);
    ui->large->move(ui->Datapage->width()-ui->large->width()-8,0);
    large2=new QPushButton(this);
    large2->setText("^");
    large2->setFixedSize(ui->large->size());
    large2->move(ui->Datapage->width()-ui->large->width()-8,0);
    large2->hide();
    ui->widget_5->setParent(ui->Datapage);
    ui->widget_5->move(50,350);
    ui->widget->setParent(NULL);
    ui->widget->setGeometry(250,250,700,500);
    ui->widget->setWindowTitle("统计图");
    this->curBC=ui->Bardata->columnCount();
    this->curBR=ui->Bardata->rowCount();
    this->curLC=ui->Linedata->columnCount();
    this->curLR=ui->Linedata->rowCount();
    this->curPC=ui->Piedata->columnCount();
    ui->Float->hide();
    ui->Floatline->hide();
    ui->Bardata->horizontalHeader()->hide();
    ui->Bardata->verticalHeader()->hide();
    ui->Linedata->verticalHeader()->hide();
    ui->Piedata->horizontalHeader()->hide();
    ui->PieTool->hide();
    ui->Xdown->hide();
    ui->Xup->hide();
    ui->lineEdit_4->hide();
    ui->label_3->hide();
    ui->widget->setAttribute(Qt::WA_QuitOnClose, false);
    chart =new QChart();
    ui->widget->setChart(chart);   
    Large = new QWidget();
    Large->setFixedSize(QSize(800,600));
    bool *FO=new bool;
    for(int i=0;i<ui->Piedata->columnCount();i++)           //初步虚圆构造
    {
        *VirtulSum=ui->Piedata->item(1,i)->text().toFloat();
    }
    connect(large2,&QPushButton::clicked,ui->large,&QPushButton::clicked);    //大页面
    connect(ui->large,&QPushButton::clicked,this,&Widget::LARGE);           //大页面
    connect(ui->Save,&QPushButton::clicked,this,&Widget::SAVE);             //文件保存
    connect(ui->Bardata,&QTableWidget::cellChanged,this,&Widget::BARCHANGED);//条形表变化
    connect(ui->Float,&QSpinBox::valueChanged,[=](){                        //浮点位变化
                ui->Piedata->cellChanged(1,1);
                ui->Piedata->cellChanged(2,1);
    });
    connect(ui->Piedata,&QTableWidget::cellChanged,this,&Widget::PIECHANGED);//扇形表变化
    connect(ui->Linedata,&QTableWidget::cellChanged,this,&Widget::LINECHANGED);//折线表变化
    connect(ui->Xdown,&QLineEdit::textChanged,[=](){                        //坐标轴文本变化
        if(ui->Xdown->text()!="0")
        if(ui->Xdown->text().toFloat()==0)
                ui->Xdown->setText("0");
        *XYtag=0;
        ui->DrawChart->setText("绘制");

    });
    connect(ui->Xup,&QLineEdit::textChanged,[=](){
        if(ui->Xup->text()!="0.")
        if(ui->Xup->text().toFloat()==0)
                ui->Xup->setText("0");
        *XYtag=0;
        ui->DrawChart->setText("绘制");
    });
    connect(ui->Ydown,&QLineEdit::textChanged,[=](){
        if(ui->Ydown->text()!="0.")
        if(ui->Ydown->text().toFloat()==0)
                ui->Ydown->setText("0");
        *XYtag=0;
        ui->DrawChart->setText("绘制");
    });
    connect(ui->Yup,&QLineEdit::textChanged,[=](){
        if(ui->Yup->text()!="0.")
        if(ui->Yup->text().toFloat()==0)
                ui->Yup->setText("0");
       *XYtag=0;
        ui->DrawChart->setText("绘制");
    });
    connect(ui->BarCd,&QSpinBox::valueChanged,[=](){            //网格线设定
            axisY->setTickCount(ui->BarCd->value());
    });
    connect(ui->Divide,&QPushButton::clicked,this,&Widget::DIVIDE);//切片分离
    connect(ui->Datapage,&QTabWidget::currentChanged,this,&Widget::DATAPAGECHANGED);//数据页面切换
    connect(ui->row,&QSpinBox::valueChanged,this,&Widget::ROWCHANGED);  //行变化
    connect(ui->column,&QSpinBox::valueChanged,this,&Widget::COLUMNCHANGED);    //列变化
    connect(ui->DrawChart,&QPushButton::clicked,this,&Widget::DRAWCHART);   //绘图触发
    connect(ui->colorB,&QToolButton::clicked,[=](){                     //标题颜色
        chart->setTitleBrush(QColorDialog::getColor());
    });
    connect(ui->fontB,&QToolButton::clicked,this,[=](){                       //标题字体
        chart->setTitleFont(QFontDialog::getFont(FO,QFont("华文新魏",10)));
    });
    connect(ui->PieSize,&QDoubleSpinBox::valueChanged,[=](){                //圆规模
        Pseries->setPieSize(ui->PieSize->value());
    });
    connect(ui->spin,&QSlider::valueChanged,[=](){                      //圆角度调整
            Pseries->setPieStartAngle(ui->spin->value());
            Pseries->setPieEndAngle(ui->spin->value()-360);
    });
}
Widget::~Widget()
{
    delete ui;
}

