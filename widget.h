#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCharts>
#include <QFontDialog>
#include <QDebug>
#include <QString>
#include <QPicture>
#include <QPaintEvent>
#include <QCloseEvent>
#include "QLine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    QWidget *Large;
    ~Widget();

    QChart *chart;
    QFile *file;
    int *code=new int();
    QBarSet *set0;//统计图条棒系列
    QPieSeries *Pseries=NULL;
    Qline *Lseries=NULL;
    QBarSeries  *Bseries=NULL;
    bool *tag=new bool(true);
    QBarCategoryAxis *axisBX=NULL;
    QValueAxis *axisY=new QValueAxis();
    QValueAxis *axisX=new QValueAxis();
    int *Pietag=new int(1);
    double MinX;
    double MinY;
    double MaxX;
    double MaxY;
    int curBR;
    int curBC;
    int curPC;
    int curLR;
    int curLC;
    int *VirtulSum;
    bool *largetag = new bool(1);
    QPushButton *large2;
    bool *XYtag=new bool(true);


    void LARGE();   //大页面
    void SAVE();    //保存图片
    void BARCHANGED();      //条形图表格变化
    void PIECHANGED();      //扇形图表格变化
    void LINECHANGED();     //折线图表格变化
    void ROWCHANGED();      //行数变化
    void COLUMNCHANGED();   //列变化
    void DATAPAGECHANGED(); //数据页面切换
    void DIVIDE();          //扇形分离
    void DRAWCHART();       //绘图触发

    void BarCharts();       //绘条形图
    void PieCharts();       //绘扇形图
    void LineCharts();      //绘折线图
    void ChartSet();        //图设置
    void BXYSet(QAbstractSeries *);     //条形图坐标轴
    void LXYSet(Qline *);               //折线图坐标轴
    void InitP(QPieSeries *);           //虚圆构造



private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
