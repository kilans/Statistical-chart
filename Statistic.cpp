#include"widget.h"
#include "ui_widget.h"
void Widget::BarCharts()
{
        Bseries = new QBarSeries();
        ui->PieTool->hide();
        for(int i=1;i<ui->Bardata->rowCount();i++)
        {
            if(ui->Bardata->item(i,0))
            {
                QBarSet *temp=new QBarSet(ui->Bardata->item(i,0)->text());  //统计条系列
                temp->setColor(QColor(rand()%256,rand()%256,rand()%256));   //设置颜色
                connect(temp,&QBarSet::doubleClicked,[=](){                 //双击设置颜色
                    QColor *color = new QColor(temp->color());
                    temp->setColor(QColorDialog::getColor(QColor(rand()%256,rand()%256,rand()%256)));
                    if(temp->color().red()==0 && temp->color().blue()==0 && temp->color().green()==0) temp->setColor(*color);
                });
                for(int j=1;j<ui->Bardata->columnCount();j++)
                    if(ui->Bardata->item(i,j))  temp->append(ui->Bardata->item(i,j)->text().toFloat());//系列添加统计棒
                if(temp->sum())   Bseries->append(temp);        //总和为0则不计入该统计图系列
                else              delete(temp);
            }
        }
        Bseries->setLabelsVisible(true);
        Bseries->setVisible(true);                              //可视化
        Bseries->setBarWidth(ui->Barwidth->value()*0.01);       //设置条宽
        connect(ui->Barwidth,&QSpinBox::valueChanged,[=](){
        Bseries->setBarWidth(ui->Barwidth->value()*0.01);
        });
        chart->addSeries(Bseries);                              //条形统计图加入视图
}
void Widget::LineCharts()
{
        Lseries = new Qline(1,ui->Linedata);                    //线系列
        ui->PieTool->hide();
        Qline temps=Qline(1,ui->Linedata);
        MaxX=temps.MaxX;
        MaxY=temps.MaxY;
        MinX=temps.MinX;
        MinY=temps.MinY;
        for(int i=1;i<ui->Linedata->rowCount();i+=3)
        {
            Qline *temp=new Qline(i,ui->Linedata);
            if(!temp->XRange || !temp->YRange)
            {
                 delete(temp);
                 continue;
            }

            chart->addSeries(temp);                             //折线系列添加入视图
            if(temp->MaxX > MaxX)  MaxX=temp->MaxX;             //折线图轴线边界动态规划
            if(temp->MinX < MinX)  MinX=temp->MinX;
            if(temp->MaxY > MaxY)  MaxY=temp->MaxY;
            if(temp->MinY < MinY)  MinY=temp->MinY;
        }
        ui->widget->setRenderHint(QPainter::Antialiasing);

}
void Widget::ChartSet()
{
    chart->setTheme(QChart::ChartThemeLight);//设置白色主题
    chart->setDropShadowEnabled(true);//背景阴影
    chart->setTitleBrush(QBrush(QColor(0,0,255)));//设置标题Brush
    chart->setTitleFont(QFont("微软雅黑"));//设置标题字体

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    chart->legend()->setBackgroundVisible(true);//设置背景是否可视
    chart->legend()->setAutoFillBackground(true);//设置背景自动填充
    chart->legend()->setColor(QColor(222,233,251));//设置颜色
    chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色
    chart->legend()->setMaximumHeight(50);
    ui->widget->setRenderHint(QPainter::Antialiasing);
}
void Widget::BXYSet(QAbstractSeries *series)
{
    delete(axisBX);
    axisBX = new QBarCategoryAxis();
    axisBX->setLineVisible(true);
    axisBX->setGridLineVisible(true);
    delete(axisY);
    axisY = new QValueAxis;
    axisY->setLineVisible(true);
    axisY->setGridLineVisible(true);
    ui->BarCd->setValue(axisY->tickCount());    //网格线
    for(int i=1;i<ui->Bardata->columnCount();i++)                       //
    {
        if(ui->Bardata->item(0,i) == NULL) continue;
        else
        {
            axisBX->append(ui->Bardata->item(0,i)->text());             //横坐标加入统计类名称
        }
    }
    axisBX->setLabelsColor(QColor(7,28,96));
    axisY->setRange(ui->BarYdown->text().toFloat(),ui->BarYup->text().toFloat());   //坐标轴边界
    ui->BarCd->setValue(axisY->tickCount());
    chart->setAxisX(axisBX,series);                                  //添加坐标轴
    chart->setAxisY(axisY,series);                                   //添加坐标轴
    ui->BarYdown->setText(QString(QString::number(axisY->min ())));
    ui->BarYup->setText(((QString::number(axisY->max()))));
}
void Widget::LXYSet(Qline *series)
{
        delete(axisX);
        axisX = new QValueAxis;
//        axisX->setLabelFormat("%dS");
        axisX->setLineVisible(true);
        axisX->setGridLineVisible(true);
        delete(axisY);
        axisY = new QValueAxis;
        axisY->setTitleText("value值");
        axisY->setLineVisible(true);
        axisY->setGridLineVisible(true);
        ui->BarCd->setValue(axisY->tickCount());    //网格线
        for(int i =0;i<chart->series().count();i++)
        {
            chart->setAxisX(axisX,chart->series().at(i));                   //坐标轴加入
            chart->setAxisY(axisY,chart->series().at(i));                   //坐标轴加入
        }
        if(*this->XYtag == true)        //第一次根据线集合定义区间
        {
            axisX->setRange(MinX-50,MaxX+50);
            axisY->setRange(MinY-50,MaxY+50);
        }
        else
        {
            axisX->setRange(ui->Xdown->text().toFloat(),ui->Xup->text().toFloat()); //边界根据边界文本设置
            axisY->setRange(ui->Ydown->text().toFloat(),ui->Yup->text().toFloat());
        }
        ui->Xdown->setText(QString(QString::number(axisX->min())));                 //边界文本根据边界设置
        ui->Xup->setText(((QString::number(axisX->max()))));
        ui->Ydown->setText(QString(QString::number(axisY->min ())));
        ui->Yup->setText(((QString::number(axisY->max()))));
        *this->XYtag=true;
}
