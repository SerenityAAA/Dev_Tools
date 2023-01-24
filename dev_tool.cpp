#include "dev_tool.h"
#include "ui_dev_tool.h"

Dev_tool::Dev_tool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dev_tool)
{
    ui->setupUi(this);
    ui->bit8_ret->setReadOnly(true);
    ui->bit16_ret->setReadOnly(true);
    ui->bit32_ret->setReadOnly(true);
    ui->bit64_ret->setReadOnly(true);
    connect(ui->num_input, SIGNAL(returnPressed()), this, SLOT(on_calc_num_btn_clicked()));

    ui->status_label_tab1->setText("初始化完成，请输入溢出数");
}

Dev_tool::~Dev_tool()
{
    delete ui;
}

void Dev_tool::clear_calc_browser()
{
    ui->bit8_ret->clear();
    ui->bit16_ret->clear();
    ui->bit32_ret->clear();
    ui->bit64_ret->clear();
    return;
}

void Dev_tool::on_calc_num_btn_clicked()
{
    QString str = ui->num_input->text();
    if (ui->num_input->text().length() < 2)
    {
        ui->status_label_tab1->setText("输入数非溢出数，请重新输入");
        clear_calc_browser();
        return;
    }
    for (int i = 1; i < str.length(); ++i)
    {
        if (!str[i].isDigit())
        {
            ui->status_label_tab1->setText("输入数非溢出数，请重新输入");
            clear_calc_browser();
            return;
        }
    }
    long long num = str.toLongLong();
    if (num >= 0)
    {
        ui->status_label_tab1->setText("输入数非溢出数，请重新输入");
        clear_calc_browser();
        return;
    }
    else
    {
        ui->status_label_tab1->setText("计算完成");
    }
    if (num < INT8_MIN)
    {
        ui->bit8_ret->setText("N/A");
    }
    else
    {
        ui->bit8_ret->setText(QString::number((UINT8_MAX + (1 + num))));
    }
    if (num < INT16_MIN)
    {
        ui->bit16_ret->setText("N/A");
    }
    else
    {
        ui->bit16_ret->setText(QString::number((UINT16_MAX + (1 + num))));
    }
    if (num < INT32_MIN)
    {
        ui->bit32_ret->setText("N/A");
    }
    else
    {
        ui->bit32_ret->setText(QString::number((UINT32_MAX + (1 + num))));
    }
    if (num < INT64_MIN)
    {
        ui->bit64_ret->setText("N/A"); //TODO: 实际走不到这里，64位系统限制
    }
    else
    {
        ui->bit64_ret->setText(QString::number((UINT64_MAX + (1 + num))));
    }
}

