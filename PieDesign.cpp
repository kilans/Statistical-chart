#include"widget.cpp"
void Widget::PieCharts()
{

        Pseries = new QPieSeries();
        Pseries->setPieSize(ui->PieSize->value());
        ui->PieTool->show();
        Pseries->setPieStartAngle(0);
        Pseries->setPieEndAngle(-360);
        for(int i=0,j=0;i<ui->Piedata->columnCount();i++)
        {

            if(ui->Piedata->item(1,i)->text().toFloat() != 0)
            {
//                if(ui->Piedata->item(0,i)==NULL)
//                {
//                    Pseries->append("",ui->Piedata->item(1,i)->text().toInt());
//                    Pseries->slices().at(i)->setLabel("%"+ QString::number(ui->Piedata->item(1,i)->text().toDouble()));
//                }
//                else
                {
                    Pseries->append(ui->Piedata->item(0,i)->text()+":%",ui->Piedata->item(1,i)->text().toInt());
//                    QString perca=QString::number(virtulP.slices().at(i)->percentage(),'f',ui->Float->value());
                    Pseries->slices().at(j)->setLabel(Pseries->slices().at(j)->label()+QString::number(ui->Piedata->item(2,i)->text().toFloat()*100,'f',ui->Float->value()-2));
                    Pseries->slices().at(j)->setColor(QColor(rand()%256,rand()%256,rand()%256));
                    Pseries->slices().at(j)->setLabelColor(Pseries->slices().at(j)->color());
                }
                connect(Pseries->slices().at(j),&QPieSlice::doubleClicked,[=](){
                    QColor *color = new QColor(Pseries->slices().at(j)->color());
                    Pseries->slices().at(j)->setColor(QColorDialog::getColor());
                    Pseries->slices().at(j)->setLabelColor( Pseries->slices().at(j)->color());
                    if(Pseries->slices().at(j)->color().red()==0 && Pseries->slices().at(j)->color().green()==0 && Pseries->slices().at(j)->color().blue()==0)
                    {
                        Pseries->slices().at(j)->setColor(*color);
                        Pseries->slices().at(j)->setLabelColor( *color);
                    }
                });
                j++;
            }
            qDebug()<<i;
        }

        Pseries->setLabelsVisible(true);
        Pseries->setUseOpenGL(true);
}
void Widget::DIVIDE()
{
    for(int i=0;i<Pseries->count();i++)
    {
        Pseries->slices().at(i)->setExploded(*tag);
    }
    update();
    if(*tag=!(*tag))
    ui->Divide->setText("切片分离");
    else
    ui->Divide->setText("切片聚合");
}
void Widget::PIECHANGED()
{
    if((ui->Piedata->currentItem()&&(ui->Piedata->currentItem()->text()=="" || *(ui->Piedata->currentItem()->text().toLocal8Bit().data()) < 48 ||*(ui->Piedata->currentItem()->text().toLocal8Bit().data()) > 57)))
        {
            if(ui->Piedata->currentItem()->row()!=0 )ui->Piedata->currentItem()->setText("0");
        }
    //&&
    else if(ui->Piedata->currentRow() == 1 )
    {
        QPieSeries virtulP;//虚圆构造
        InitP(&virtulP);
//            qDebug()<<"虚圆构造";

        *VirtulSum=virtulP.sum();
        float wei=1;
        for(int i=0;i<ui->Float->value();i++)
            wei/=10;
        qDebug()<<wei;
        for(int i=0;i<ui->Piedata->columnCount();i++)
        {

//                qDebug()<<i<<"占比 : "<<virtulP.slices().at(i)->percentage();
//                qDebug()<<virtulP.slices().at(i)->percentage() <<"-"<<ui->Piedata->item(2,i)->text().toDouble()<<"="<<
//                          virtulP.slices().at(i)->percentage() - ui->Piedata->item(2,i)->text().toDouble();
            if(ui->Piedata->item(2,i)/*&&((virtulP.slices().at(i)->percentage() - ui->Piedata->item(2,i)->text().toDouble() >wei) || (virtulP.slices().at(i)->percentage() - ui->Piedata->item(2,i)->text().toDouble() <-wei)*/)
            {
                qDebug()<<"偏差值符合 : "<<virtulP.slices().at(i)->percentage();
                QString perca=QString::number(virtulP.slices().at(i)->percentage(),'f',ui->Float->value());
                qDebug()<<perca;
                ui->Piedata->item(2,i)->setText(perca);
            }
        }
    }
    else if(ui->Piedata->currentRow()==2)
    {
//            qDebug()<<"啊？";
        float c,b;
        b=ui->Piedata->currentItem()->text().toFloat();
        c=ui->Piedata->item(1,ui->Piedata->currentColumn())->text().toFloat();
        float per=(((*VirtulSum)*b-c))/(1-b);
//            qDebug()<<*a<<"*"<<b<<"-"<<c<<"/"<<"1-"<<b<<"="<<per;
        QString res=QString::number((int)(per+c));
        *VirtulSum += per;
//            qDebug()<<"res"<<res;
        ui->Piedata->item(1,ui->Piedata->currentItem()->column())->setText(res);
        QPieSeries virtulP;//虚圆构造
        InitP(&virtulP);
//            qDebug()<<"虚圆构造";
        *VirtulSum=virtulP.sum();
        float wei=1;
        for(int i=0;i<ui->Float->value();i++)
            wei/=10;
        qDebug()<<wei;
        for(int i=0;i<ui->Piedata->columnCount();i++)
        {
//                qDebug()<<i;
//                qDebug()<<i<<"占比 : "<<virtulP.slices().at(i)->percentage();
//                qDebug()<<virtulP.slices().at(i)->percentage() <<"-"<<ui->Piedata->item(2,i)->text().toDouble()<<"="<<
//                          virtulP.slices().at(i)->percentage() - ui->Piedata->item(2,i)->text().toDouble();
            if(ui->Piedata->item(2,i)/*&&((virtulP.slices().at(i)->percentage() - ui->Piedata->item(2,i)->text().toDouble() >wei) || (virtulP.slices().at(i)->percentage() - ui->Piedata->item(2,i)->text().toDouble() < -wei)*/)
            {
                qDebug()<<"偏差值符合 : "<<virtulP.slices().at(i)->percentage();
                QString perca=QString::number(virtulP.slices().at(i)->percentage(),'f',ui->Float->value());
                qDebug()<<perca;
                ui->Piedata->item(2,i)->setText(perca);
            }
        }
    }
}
void Widget::InitP(QPieSeries *temp)
{
    for(int i=0;i<ui->Piedata->columnCount();i++)
    {
        if(ui->Piedata->item(1,i)!=NULL)
        {

                (temp)->append("",ui->Piedata->item(1,i)->text().toInt());
        }
    }
}
