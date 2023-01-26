#ifndef DEV_TOOL_H
#define DEV_TOOL_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <time.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Dev_tool; }
QT_END_NAMESPACE

class Dev_tool : public QMainWindow
{
    Q_OBJECT

public:
    Dev_tool(QWidget *parent = nullptr);
    ~Dev_tool();

private slots:
    void on_calc_num_btn_clicked();

    void on_omap_btn_clicked();

    void on_utc_to_gm_btn_clicked();

    void on_gm_to_utc_btn_clicked();

private:
    Ui::Dev_tool *ui; 
    void tab1_init();
    void tab2_init();
    void tab3_init();
    void clear_calc_browser();
};
#endif // DEV_TOOL_H
