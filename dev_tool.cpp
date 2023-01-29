#include "dev_tool.h"
#include "ui_dev_tool.h"

Dev_tool::Dev_tool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dev_tool)
{
    ui->setupUi(this);

    //固定窗口
    this->setWindowFlag(Qt::Dialog);
    this->setFixedSize(this->width(), this->height());

    tab1_init();
    tab2_init();
    tab3_init();
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
    return;
}

void Dev_tool::tab1_init()
{
    //框内输入时可以回车进行计算，下类同
    connect(ui->num_input, SIGNAL(returnPressed()), this, SLOT(on_calc_num_btn_clicked()));
    ui->status_label_tab1->setText("初始化完成，请输入溢出数");
    return;
}

void Dev_tool::tab2_init()
{
    QFile type_file("./Type_list.txt");
    if (!type_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->omap_ret->setText("打开类型文件出错！");
        ui->omap_ret->append("当前路径为：");
        ui->omap_ret->append(QDir::currentPath());
        ui->omap_btn->setEnabled(false);
        ui->type_list->setEnabled(false);
        return;
    }
    QTextStream typefile_list(&type_file);
    while (!typefile_list.atEnd())
    {
        QString type = typefile_list.readLine();
        ui->type_list->addItem(type);
    }
    type_file.close();
    ui->omap_ret->setText("初始化完成！");
    return;
}

void Dev_tool::tab3_init()
{
    ui->gm_src->setPlaceholderText("输入格式(YYYY-MM-DD-HH-MM-SS)");
    ui->gm_src->setAlignment(Qt::AlignCenter);
    ui->utc_src->setAlignment(Qt::AlignCenter);
    connect(ui->utc_src, SIGNAL(returnPressed()), this, SLOT(on_utc_to_gm_btn_clicked()));
    connect(ui->gm_src, SIGNAL(returnPressed()), this, SLOT(on_gm_to_utc_btn_clicked()));
    return;
}


void Dev_tool::on_omap_btn_clicked()
{
    ui->omap_ret->clear();
    if (ui->omap_label->text().isEmpty())
    {
        ui->omap_ret->setText("标签名为空！");
        return;
    }
    if (ui->bit_count->text().isEmpty())
    {
        ui->omap_ret->setText("显示位数为空！");
        return;
    }
    else if (0 == ui->bit_count->text().toInt())
    {
        ui->omap_ret->setText("显示位数输入错误！");
        return;
    }
    if (ui->omap_page->text().isEmpty())
    {
        ui->omap_ret->setText("OMAP页数为空!");
        return;
    }
    else if (0 == ui->omap_page->text().toInt())
    {
        ui->omap_ret->setText("OMAP页数输入错误!");
        return;
    }
    if (ui->omap_line->text().isEmpty())
    {
        ui->omap_ret->setText("OMAP行号为空!");
        return;
    }
    else if (0 == ui->omap_line->text().toInt())
    {
        ui->omap_ret->setText("OMAP行号输入错误!");
        return;
    }
    ui->omap_ret->setText("<Data>");
    ui->omap_ret->append("    <Label>" + ui->omap_label->text() + "</Label>");
    ui->omap_ret->append("    <TYPE>" + ui->type_list->currentText() + "</TYPE>");
    ui->omap_ret->append("    <Bit_count>" + ui->bit_count->text() + "</Bit_count>");
    ui->omap_ret->append("    <OMAP_display>");
    ui->omap_ret->append("        <PAGE>" + ui->omap_page->text() + "</PAGE>");
    ui->omap_ret->append("        <LINE>" + ui->omap_line->text() + "</LINE>");
    ui->omap_ret->append("        <COL>" + ui->omap_col->currentText() + "</COL>");
    ui->omap_ret->append("    </OMAP_display>");
    ui->omap_ret->append("</Data>");
    return;
}

void Dev_tool::on_utc_to_gm_btn_clicked()
{
    ui->utc_to_gm_msg->clear();
    ui->gm_time_ret->clear();
    ui->bj_time_ret->clear();
    if (ui->utc_src->text().isEmpty())
    {
        ui->utc_to_gm_msg->setText("输入为空");
        return;
    }
    bool ok = false;
    time_t utc_time = ui->utc_src->text().toLongLong(&ok);
    if (!ok || utc_time <= 0)
    {
        ui->utc_to_gm_msg->setText("输入有误，请检查");
        return;
    }
    struct tm *time = gmtime(&utc_time);
    char time_str[25] = {0};
    strftime(time_str, 25, "%Y-%m-%d %H:%M:%S", time);
    ui->gm_time_ret->setText(QString(time_str));
    ui->gm_time_ret->setAlignment(Qt::AlignVCenter);
    ui->gm_time_ret->setAlignment(Qt::AlignHCenter);

    memset((void *)time_str, 0, sizeof(time_str));
    utc_time += 8 * 3600;

    time = gmtime(&utc_time);
    strftime(time_str, 25, "%Y-%m-%d %H:%M:%S", time);
    ui->bj_time_ret->setText(QString(time_str));
    ui->bj_time_ret->setAlignment(Qt::AlignVCenter);
    ui->bj_time_ret->setAlignment(Qt::AlignHCenter);
    return;
}


void Dev_tool::on_gm_to_utc_btn_clicked()
{
    ui->gm_to_utc_msg->clear();
    ui->utc_ret->clear();
    if (ui->gm_src->text().isEmpty())
    {
        ui->gm_to_utc_msg->setText("输入为空");
        return;
    }
    QString time_input = ui->gm_src->text();
    auto time_msg_input = time_input.split("-");
    if (time_msg_input.size() != 6)
    {
        ui->gm_to_utc_msg->setText("输入参数格式错误");
        return;
    }
    int time_msg[6] = {0};
    int i = 0;
    for (const QString &msg : time_msg_input)
    {
        bool ok = false;
        time_msg[i] = msg.toInt(&ok);
        if (false == ok)
        {
            ui->gm_to_utc_msg->setText("输入参数中存在非数值");
            return;
        }
        ++i;
    }
    do
    {
        if (time_msg[0] < 1970 || time_msg[0] > 2040)
        {
            ui->gm_to_utc_msg->setText("输入年份错误");
            return;
        }
        if (time_msg[1] < 1 || time_msg[1] > 12)
        {
            ui->gm_to_utc_msg->setText("输入月份错误");
            return;
        }
        if (time_msg[2] < 1 || time_msg[2] > 31)
        {
            ui->gm_to_utc_msg->setText("输入日错误");
            return;
        }
        if (time_msg[3] < 0 || time_msg[3] > 23)
        {
            ui->gm_to_utc_msg->setText("输入小时错误");
            return;
        }
        if (time_msg[4] < 0 || time_msg[4] > 59)
        {
            ui->gm_to_utc_msg->setText("输入分钟错误");
            return;
        }
        if (time_msg[5] < 0 || time_msg[5] > 59)
        {
            ui->gm_to_utc_msg->setText("输入秒错误");
            return;
        }
    }while(0);  // 1900-01-01 00:00:00 to 2038-12-31 23:59:59

    struct tm time;
    memset((void *)&time, 0, sizeof(struct tm));
    time.tm_year = time_msg[0] - 1900;
    time.tm_mon = time_msg[1] - 1;
    time.tm_mday = time_msg[2];
    time.tm_hour = time_msg[3];
    time.tm_min = time_msg[4];
    time.tm_sec = time_msg[5];
    ui->utc_ret->setText(QString::number(mktime(&time)));
    ui->utc_ret->setAlignment(Qt::AlignVCenter);
    ui->utc_ret->setAlignment(Qt::AlignHCenter);
    return;
}

