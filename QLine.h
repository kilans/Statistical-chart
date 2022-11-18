#ifndef QLINE
#define QLINE

#include <QObject>
#include<QtCharts>


class Qline : public QLineSeries
{
     Q_OBJECT
public:
    explicit Qline(QLineSeries *parent = nullptr);
    Qline(int,QTableWidget*);
    double XRange=0;
    double YRange=0;
    double MaxX=0;
    double MinX=0;
    double MaxY=0;
    double MinY=0;
    bool tag=true;
signals:

};

#endif // QLINE
