#include "messageitemwidget.h"
#include <QDateTime>
#include <QDebug>
#include <QPainter>
#include <cmath>

MessageItemWidget::MessageItemWidget(QWidget* parent)
    : QWidget(parent)
{
    QFont te_font = this->font();
    te_font.setFamily("Noto Mono");
    te_font.setPointSize(13);
    this->setFont(te_font);
}

void MessageItemWidget::setItemData(MessageItemData data)
{
    m_itemData = data;
    m_direction = data.messageDirection;
    m_content = data.messageContent;
    m_date = QDateTime::fromTime_t(data.messageTime).toString(Qt::DateFormat::SystemLocaleDate);
    genPaintRects();
}

QSize MessageItemWidget::getBorderSize() const
{
    return m_bordersize;
}

void MessageItemWidget::genPaintRects()
{
    int borderWidth = width() * 0.8;
    m_margin = 15;
    m_bordersize = genBorderSize(borderWidth - 2 * m_margin);
    borderWidth = m_bordersize.width();
    int borderHeight = m_bordersize.height();
    int contentWidth = m_bordersize.width() - 2 * m_margin;
    int contentHeight = m_bordersize.height() - 2 * m_margin;
    if (m_direction < 0) {
        //收到的消息
        m_borderRect.setRect(m_margin * 2, m_margin,
            borderWidth, borderHeight);
        m_contentRect.setRect(m_borderRect.left() + m_margin, m_borderRect.top() + m_margin,
            contentWidth, contentHeight);
    } else if (m_direction > 0) {
        //发送的消息
        m_borderRect.setRect(width() - m_margin * 3 - borderWidth, m_margin,
            borderWidth, borderHeight);
        m_contentRect.setRect(m_borderRect.left() + m_margin, m_borderRect.top() + m_margin,
            contentWidth, contentHeight);
    } else {
        qDebug() << "m_direction value is 0";
    }
    //TODO: 这里21作为暂时高度
    m_timeRect.setRect(m_margin, m_contentRect.bottom(), contentWidth, 21);
}

QSize MessageItemWidget::genBorderSize(int contentWidth)
{
    QString src = m_content;
    QFontMetricsF fm(this->font());
    int lineHeight = fm.lineSpacing();
    int count = src.count("\n");
    int maxWidth = 0;
    QSize borderSize;
    if (count == 0) {
        maxWidth = fm.width(src);
        QString value = src;
        if (maxWidth > contentWidth) {
            maxWidth = contentWidth;
            int lineSize = contentWidth / fm.width(" "); //一行能容纳的空格数
            int contentLen = (fm.width(value)); //总空格数
            double contentWid = ((lineSize / 3) * 3 * fm.width(" "));
            int num = (contentLen / contentWid);
            count += num;
            borderSize = QSize(maxWidth + 2 * m_margin, (count + 1) * fm.height() * 1.08 + 2 * m_margin);
            sizeWidget = QSize(borderSize.width(), borderSize.height() + 2 * m_margin);
        } else {
            borderSize = QSize(maxWidth + 2 * m_margin, (count + 1) * fm.height() + 2 * m_margin);
            sizeWidget = QSize(borderSize.width(), borderSize.height() + 2 * m_margin);
        }
    } else {
        if (width() == 736) {
            qDebug() << "hello";
        }
        int n = count + 1; // 行数，循环次数
        for (int i = 0; i < n; i++) {
            QString value = src.split("\n").at(i);
            maxWidth = fm.width(value) > maxWidth ? fm.width(value) : maxWidth;
            if (fm.width(value) > contentWidth) {
                maxWidth = contentWidth;
                int lineSize = contentWidth / fm.width(" "); //一行能容纳的空格数
                int contentLen = ceil(fm.width(value)); //总空格数
                double contentWid = ((lineSize / 3) * 3 * fm.width(" "));
                int num = (contentLen / contentWid);
                count += num;
            }
        }
        borderSize = QSize(maxWidth + 2 * m_margin, (count + 1) * fm.height() * 1.08 + 2 * m_margin);
        sizeWidget = QSize(borderSize.width(), borderSize.height() + 2 * m_margin);
    }
    //TODO spacewidth暂时为20,作为文本和框的左右间隔
    return borderSize;
}

void MessageItemWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform); //消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    //绘制消息边框
    painter.setBrush(QBrush(QColor(Qt::gray)));
    painter.drawRoundedRect(m_borderRect, 10, 10);

    //绘制消息本身
    painter.setPen(QPen(QColor(Qt::black)));
    QTextOption option(Qt::AlignLeft);
    //option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    option.setWrapMode(QTextOption::WrapAnywhere);
    painter.setFont(this->font());
    painter.drawText(m_contentRect, m_content, option);
    //TODO 绘制时间
}
