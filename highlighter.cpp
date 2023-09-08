
#include "highlighter.h"
#include <QDebug>
#include <QRegExp>
#include <QTextCharFormat>

Highlighter::Highlighter(QTextDocument* parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;
    int red = 255;
    int green = 140;
    int blue = 0;



    // JSON keys
    keyFormat.setForeground(Qt::red);
    rule.pattern = QRegExp("\"(\\w+)\"\\s*:");
    rule.format = keyFormat;
    highlightingRules.append(rule);

    // JSON strings
    stringFormat.setForeground(Qt::darkGreen); // Change to the desired color for strings
    rule.pattern = QRegExp("\"([^\"]*)\"");
    rule.format = stringFormat;
    highlightingRules.append(rule);

    // JSON numbers
    numberFormat.setForeground(Qt::darkMagenta); // Change to the desired color for numbers
    rule.pattern = QRegExp("\\b-?\\d+(\\.\\d+)?([eE][-+]?\\d+)?\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);
}

void Highlighter::highlightBlock(const QString& text) {
    foreach (const HighlightingRule& rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = text.indexOf(expression);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = text.indexOf(expression, index + length);
        }
    }
}

