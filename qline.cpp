#include "QLine.h"
Qline::Qline(QLineSeries *parent)
    : QLineSeries{parent}
{

}
Qline::Qline(int i , QTableWidget *T)
{
    this->setName(T->item(i-1,0)->text());
    this->setVisible(true);
    this->setPointLabelsFormat("(@xPoint,@yPoint)");
    this->setPointLabelsVisible(true);
    for(int j=1;j<T->columnCount();j++)
    {
        if(T->item(i,j) && T->item(i+1,j))
        {
            if(T->item(i,j)->text().toDouble() - this->MaxX>0)
            {
                this->MaxX=T->item(i,j)->text().toDouble();
            }
            else if((T->item(i,j)->text().toDouble() - this->MinX)  < 0 )
            {
                this->MinX=T->item(i,j)->text().toDouble();
            }
            if(T->item(i+1,j)->text().toDouble() - this->MaxY>0)
            {
                this->MaxY=T->item(i+1,j)->text().toDouble();
            }
            else if((T->item(i+1,j)->text().toDouble() - this->MinY)  < 0 )
            {
                this->MinY=T->item(i+1,j)->text().toDouble();
            }
            this->append(QPointF(T->item(i,j)->text().toDouble(),T->item(i+1,j)->text().toDouble()));
        }
    }
    this->XRange=MaxX-MinX;
    this->YRange=MaxY-MinY;
    connect(this,&this->clicked,[=](){
        QColor color = this->color();
          this->setColor(QColorDialog::getColor());
        if(this->color().red()==0 && this->color().green()==0 && this->color().blue()==0)
            this->setColor(color);
          });
}
