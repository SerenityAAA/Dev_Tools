#ifndef DEV_TOOL_H
#define DEV_TOOL_H

#include <QMainWindow>
#include <QString>

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

private:
    Ui::Dev_tool *ui; 
    void clear_calc_browser();
};
#endif // DEV_TOOL_H
