#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>
#include <QtSerialPort>
#include <QComboBox>
#include <QDebug>
#include <QLineEdit>
#include <QCheckBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_serialPortName = getPortNameList();

    sendmodel = ASCII;
    recvmodel = ASCII;

    setWindowTitle("ComDebug");

    setWindowIcon(QIcon(":/res/bitbug_favicon.ico"));

    ui->OpenpushButton->setEnabled(true); //打开串口后“打开串口”按钮不可用

    ui->ClosepushButton->setEnabled(false); //打开串口后“关闭串口”按钮不可用

    ui->SendpushButton->setEnabled(false); //打开串口后“发送数据”按钮不可用

    ui->ClearpushButton->setEnabled(false);

    ui->Clear1pushButton->setEnabled(false);

    ui->BaudcomboBox->setEnabled(true); //设置combox可用
    ui->DataBitscomboBox->setEnabled(true);
    ui->ParitycomboBox->setEnabled(true);
    ui->StopBitscomboBox->setEnabled(true);
    ui->portnamecomboBox->setEnabled(true);


}

Widget::~Widget()
{
    delete ui;
}

QStringList Widget::getPortNameList()
 {
    QStringList serialPortName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
       m_serialPortName << info.portName();
       qDebug() <<info.portName();
    }
    ui->portnamecomboBox->addItems(m_serialPortName);

    return  serialPortName;
 }

void Widget::on_OpenpushButton_clicked()
{
    m_serialPort = new QSerialPort();//实例化串口类一个对象

    if(m_serialPort->isOpen())//如果串口已经打开了 先给他关闭了
    {
        m_serialPort->clear();
        m_serialPort->close();
    }

    //设置串口名字 假设我们上面已经成功获取到了 并且使用第一个
    m_serialPort->setPortName(ui->portnamecomboBox->currentText());

    if(!m_serialPort->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        qDebug()<<ui->portnamecomboBox->currentText() << " 打开失败!";
        return;
    }
    //打开成功

    //设置波特率
    if(ui->BaudcomboBox->currentText() == tr("9600"))//根据组合框内容对串口进行设置
       m_serialPort->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);//设置波特率和读写方向
    else if(ui->BaudcomboBox->currentText() == tr("115200"))
       m_serialPort->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);//设置波特率和读写方向

    //设置数据位
    if(ui->DataBitscomboBox->currentText() == tr("8"))
       m_serialPort->setDataBits(QSerialPort::Data8);		//数据位为8位
    else if(ui->DataBitscomboBox->currentText() == tr("7"))
       m_serialPort->setDataBits(QSerialPort::Data7);		//数据位为8位

    //设置奇偶校验
    if(ui->ParitycomboBox->currentText() == tr("无"))
        m_serialPort->setParity(QSerialPort::NoParity);	//无校验位
    else if(ui->ParitycomboBox->currentText() == tr("奇校验"))
        m_serialPort->setParity(QSerialPort::OddParity);	//奇校验位
    else if(ui->ParitycomboBox->currentText() == tr("偶校验"))
        m_serialPort->setParity(QSerialPort::EvenParity);	//偶校验位


    //设置停止位
    if(ui->StopBitscomboBox->currentText() == tr("1"))
       m_serialPort->setStopBits(QSerialPort::OneStop); //一位停止位
    else if(ui->StopBitscomboBox->currentText() == tr("2"))
       m_serialPort->setStopBits(QSerialPort::TwoStop); //两位停止位

    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制


    //连接信号槽 当下位机发送数据QSerialPortInfo 会发送个 readyRead 信号,我们定义个槽readMycom()
        connect(m_serialPort,SIGNAL(readyRead()),this,SLOT(readMycom()));
        connect(ui->textBrowser,SIGNAL(textChanged()),this,SLOT(autoScroll()));


        ui->OpenpushButton->setEnabled(false); //打开串口后“打开串口”按钮不可用

        ui->ClosepushButton->setEnabled(true); //打开串口后“关闭串口”按钮可用

        ui->SendpushButton->setEnabled(true); //打开串口后“发送数据”按钮可用

        ui->BaudcomboBox->setEnabled(false); //设置combox不可用
        ui->DataBitscomboBox->setEnabled(false);
        ui->ParitycomboBox->setEnabled(false);
        ui->StopBitscomboBox->setEnabled(false);
        ui->portnamecomboBox->setEnabled(false);

        ui->Clear1pushButton->setEnabled(true);
        ui->SendpushButton->setEnabled(true);

}


void Widget::autoScroll()
{
    QTextCursor cursor  = ui->textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textBrowser->setTextCursor(cursor);
}

void Widget::readMycom(void) //读串口函数
{
 QBAtemp = m_serialPort->readAll();
 Qstrtemp.clear();
 qDebug() <<"read mycom";
 for(int j = 0 ; j < QBAtemp.length();j++)
      Qstrtemp += QBAtemp[j];

 if(recvmodel == ASCII)
 {
      ui->textBrowser->moveCursor(QTextCursor::End);
      ui->textBrowser->insertPlainText(Qstrtemp);
      //ui->textBrowser->append(Qstrtemp);
      qDebug() << "ASCII :" << Qstrtemp;
 }
 else
 {
      ui->textBrowser->append(StringtoHex(Qstrtemp));
      qDebug() << "HEX :" << StringtoHex(QString(Qstrtemp));
 }

 ui->TesttextEdit->moveCursor(QTextCursor::End);
 ui->TesttextEdit->insertPlainText(Qstrtemp);
 qDebug() << Qstrtemp << ":" << Qstrtemp.length();
}

void Widget::on_ClearpushButton_clicked()
{
    ui->textBrowser->clear();
}

void Widget::on_ClosepushButton_clicked()
{
    m_serialPort->close();

    ui->OpenpushButton->setEnabled(true); //打开串口后“打开串口”按钮不可用

    ui->ClosepushButton->setEnabled(false); //打开串口后“关闭串口”按钮不可用

    ui->SendpushButton->setEnabled(false); //打开串口后“发送数据”按钮不可用

    ui->Clear1pushButton->setEnabled(false);

    ui->BaudcomboBox->setEnabled(true); //设置combox可用
    ui->DataBitscomboBox->setEnabled(true);
    ui->ParitycomboBox->setEnabled(true);
    ui->StopBitscomboBox->setEnabled(true);
    ui->portnamecomboBox->setEnabled(true);


}

void Widget::on_SendpushButton_clicked()
{

    if(sendmodel == ASCII)
    {
        if(ui->add_CRLF_checkBox->checkState() == Qt::Checked)
        {
            Qstrtemp = ui->SendlineEdit->text() + "\r\n";
        }
        else
           Qstrtemp = ui->SendlineEdit->text();

       m_serialPort->write(Qstrtemp.toLatin1(),Qstrtemp.length());
    }
    else
    {
        if(ui->add_CRLF_checkBox->checkState() == Qt::Checked)
        {
            Qstrtemp = ui->SendlineEdit->text() + "0D 0A";
        }
        else
            Qstrtemp = ui->SendlineEdit->text();

        qDebug() <<"666" +Qstrtemp;
       qDebug() <<"666" +HextoString(Qstrtemp);
       m_serialPort->write(HextoString(Qstrtemp).toLatin1(),HextoString(Qstrtemp).length());
    }

    //qDebug() << ui->SendlineEdit->text() << endl;
    //qDebug() << ui->SendlineEdit->text().length() << endl;
}

void Widget::on_Clear1pushButton_clicked()
{
    ui->SendlineEdit->clear();
}

void Widget::on_RecvAsciiradioButton_toggled(bool checked)
{
    if(ui->RecvAsciiradioButton->isChecked() == true)
    {
      recvmodel = ASCII;
      qDebug()<< "Ascii";
    }
    else
    {
       recvmodel = HEX;
       qDebug()<< "Hex";
    }
}

void Widget::on_SendAsciiradioButton_toggled(bool checked)
{
    if(ui->SendAsciiradioButton->isChecked() == true)
    {
      sendmodel = ASCII;
      qDebug()<< "Ascii";

      ui->SendlineEdit->setValidator(0);

       QString q = HextoString(ui->SendlineEdit->text());

      qDebug()<< ui->SendlineEdit->text().toLatin1();

      ui->SendlineEdit->clear();

      ui->SendlineEdit->setText(q);

    }
    else
    {
       sendmodel = HEX;
       qDebug()<< "Hex";

       ui->SendlineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9 A-Fa-f]+$")));

       QString q = StringtoHex(ui->SendlineEdit->text());

       qDebug() << q;

       ui->SendlineEdit->clear();

       ui->SendlineEdit->setText(q);
    }
}


QString Widget::StringtoHex(QString buf)
{
  QString sret;
  QByteArray Qba = buf.toLatin1();
  QDataStream out(&Qba,QIODevice::ReadWrite);

  while(!out.atEnd())
  {
      qint8 outchar = 0;
      out >> outchar;

      QString str = QString("%1").arg(outchar & 0xFF,2,16,QLatin1Char('0')).toUpper() + QString(" ");

      sret += str;
  }



//  QByteArray Qb =  buf.toLatin1();

//  for(int i=0; i<Qb.length()*2; i=i+2)
//     {
//          sret += Qb.toHex().mid(i,2);

//          if(i+2 >= Qb.length()*2)
//              ;
//          else
//             sret +=" ";
//     }

   return sret;
}

QString Widget::HextoString(QString buf)
{
    QByteArray ret;
    QString    Qstr;
    bool ok;
    buf = buf.trimmed();
    buf = buf.simplified();

    QStringList sl = buf.split(" ");

    foreach(QString s,sl)
    {
        if(!s.isEmpty())
        {
            char c = s.toInt(&ok,16) & 0xFF;
            if(ok){
                ret.append(c);
            }
            else
            {
                qDebug() << "非法字符";
            }

        }

    }

    for(int i = 0 ; i < ret.length();i++)
         Qstr += ret[i];

    return Qstr;

}
