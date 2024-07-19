#include <QtWidgets>
#include <QRegularExpression>
#include "gotocelldialog.h"
#include <QDebug>

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    QRegularExpression regExp("[A-Za-z][1-9][0-9]{0,2}");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regExp, this);
    lineEdit->setValidator(validator);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

}

void GoToCellDialog::on_lineEdit_textChanged(const QString &arg1)
{
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(lineEdit->hasAcceptableInput());
}
/*"[A-Za-z][1-9][0-9]{0,2}" 是一个正则表达式，用于匹配特定格式的字符串。在这个表达式中：

    [A-Za-z]：匹配任意一个字母（大写或小写）。
    [1-9]：匹配任意一个从 1 到 9 的数字（不包括 0）。
    [0-9]{0,2}：匹配 0 到 2 个数字（可以是 0 到 9 的任何数字）。

组合起来，这个正则表达式的含义是：

    字符串必须以一个字母开头。
    接着必须有一个从 1 到 9 的数字。
    后面可以跟上 0 到 2 个数字（总共可以有 1 到 3 位数字）。

举个例子，这个正则表达式会匹配以下字符串：

    A1
    B10
    C123

但不会匹配：

    A0（因为数字部分不能是 0）
    A1234（因为数字部分超过了 3 位）

这种格式通常用于表示单元格位置或类似的标识符。
*/
