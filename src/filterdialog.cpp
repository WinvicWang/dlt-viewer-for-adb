/**
 * @licence app begin@
 * Copyright (C) 2011-2012  BMW AG
 *
 * This file is part of COVESA Project Dlt Viewer.
 *
 * Contributions are licensed to the COVESA Alliance under one or more
 * Contribution License Agreements.
 *
 * \copyright
 * This Source Code Form is subject to the terms of the
 * Mozilla Public License, v. 2.0. If a  copy of the MPL was not distributed with
 * this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \file filterdialog.cpp
 * For further information see http://www.covesa.global/.
 * @licence end@
 */

#include "filterdialog.h"
#include "ui_filterdialog.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QRegularExpression>

#include "dltuiutils.h"

FilterDialog::FilterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog)
{
    ui->setupUi(this);

    connect(ui->buttonSelectColor, SIGNAL(pressed()), this, SLOT(on_buttonSelectColor_clicked()));
    connect(ui->lineEdit_msgIdMax, SIGNAL(textChanged(const QString&)), this, SLOT(checkMsgIdValid(const QString&)));
    connect(ui->lineEdit_msgIdMin, SIGNAL(textChanged(const QString&)), this, SLOT(checkMsgIdValid(const QString&)));
    connect(ui->checkBoxMessageId, SIGNAL(stateChanged(int)), this, SLOT(on_checkboxMessageId_stateChanged(int)));
    connect(ui->lineEditRegexSearch, SIGNAL(textChanged(const QString&)), this, SLOT(on_checkRegex(const QString&)));
    connect(ui->lineEditRegexReplace, SIGNAL(textChanged(const QString&)), this, SLOT(on_checkRegex(const QString&)));

    ui->pushButton_c0->setStyleSheet ("QPushButton {background-color: rgb(255, 0  , 0  );} QPushButton:disabled {background-color: rgb(255, 255, 255);}");
    ui->pushButton_c1->setStyleSheet ("QPushButton {background-color: rgb(255, 255, 0  );} QPushButton:disabled {background-color: rgb(255, 255, 255);}");
    ui->pushButton_c2->setStyleSheet ("QPushButton {background-color: rgb(  0, 255, 0  );} QPushButton:disabled {background-color: rgb(255, 255, 255);}");
    ui->pushButton_c3->setStyleSheet ("QPushButton {background-color: rgb(000, 255, 255);} QPushButton:disabled {background-color: rgb(255, 255, 255);}");
    ui->pushButton_c4->setStyleSheet ("QPushButton {background-color: rgb(000, 000, 255);} QPushButton:disabled {background-color: rgb(255, 255, 255);}");
    ui->pushButton_c5->setStyleSheet ("QPushButton {background-color: rgb(255, 000, 255);} QPushButton:disabled {background-color: rgb(255, 255, 255);}");
    ui->pushButton_c6->setStyleSheet ("QPushButton {background-color: rgb(255, 150, 150);} QPushButton:disabled {background-color: rgb(255, 255, 255);}");
    ui->pushButton_c7->setStyleSheet ("QPushButton {background-color: rgb(255, 255, 192);} QPushButton:disabled {background-color: rgb(255, 255, 255);}");
    ui->pushButton_c8->setStyleSheet ("QPushButton {background-color: rgb(150, 255, 150);} QPushButton:disabled {background-color: rgb(255, 255, 255);}");
    ui->pushButton_c9->setStyleSheet ("QPushButton {background-color: rgb(150, 150 ,255);} QPushButton:disabled {background-color: rgb(255, 255, 255);}");
    ui->pushButton_c10->setStyleSheet("QPushButton {background-color: rgb(255, 150 ,255);} QPushButton:disabled {background-color: rgb(255, 255, 255);}");
    ui->comboBoxType->setVisible(false);

    ui->lineEdit_msgIdMax->setInputMask("nnhhhhhhhh");
    ui->lineEdit_msgIdMin->setInputMask("nnhhhhhhhh");
    ui->plainTextEdit_msgIdRule->viewport()->setAutoFillBackground(false);
    QFont font=  ui->plainTextEdit_msgIdRule->font();
    font.setFamily("monospace [Consolas]");
    font.setFixedPitch(true);
    font.setStyleHint(QFont::Monospace);
    ui->plainTextEdit_msgIdRule->setFont(font);
    on_checkboxMessageId_stateChanged(0);
}

FilterDialog::~FilterDialog()
{
    delete ui;
}


void FilterDialog::setType(int value)
{
    ui->comboBoxType->setCurrentIndex(value);

    /* update ui */
    on_checkBoxMarkerClicked();
}

int FilterDialog::getType()
{
    return ui->comboBoxType->currentIndex();
}

void FilterDialog::setName(QString name)
{
    ui->lineEditName->setText(name);
}

QString FilterDialog::getName()
{
    return ui->lineEditName->text();
}

void FilterDialog::setEnableRegexp_Procid(bool state)
{
    ui->checkBoxRegexp_Procid->setChecked(state);
}

bool FilterDialog::getEnableRegexp_Procid()
{
    return (ui->checkBoxRegexp_Procid->checkState() == Qt::Checked);
}

void FilterDialog::setEnableRegexp_Context(bool state)
{
    ui->checkBoxRegexp_Context->setChecked(state);
}

bool FilterDialog::getEnableRegexp_Context()
{
    return (ui->checkBoxRegexp_Context->checkState() == Qt::Checked);
}

void FilterDialog::setEnableRegexp_Header(bool state)
{
    ui->checkBoxRegexp_Header->setChecked(state);
}

bool FilterDialog::getEnableRegexp_Header()
{
    return (ui->checkBoxRegexp_Header->checkState() == Qt::Checked);
}

void FilterDialog::setEnableRegexp_Payload(bool state)
{
    ui->checkBoxRegexp_Payload->setChecked(state);
}

bool FilterDialog::getEnableRegexp_Payload()
{
    return (ui->checkBoxRegexp_Payload->checkState() == Qt::Checked);
}

void FilterDialog::setIgnoreCase_Header(bool state)
{
    ui->checkBox_IgnoreCase_Header->setChecked(state);
}

bool FilterDialog::getIgnoreCase_Header()
{
    return (ui->checkBox_IgnoreCase_Header->checkState() == Qt::Checked);
}

void FilterDialog::setIgnoreCase_Payload(bool state)
{
    ui->checkBox_IgnoreCase_Payload->setChecked(state);
}

bool FilterDialog::getIgnoreCase_Payload()
{
    return (ui->checkBox_IgnoreCase_Payload->checkState() == Qt::Checked);
}

void FilterDialog::settag(QString id)
{
    ui->lineEdittag->setText(id);
}

QString FilterDialog::gettag()
{
    return ui->lineEdittag->text();
}

void FilterDialog::setEnabletag(bool state)
{
    ui->checkBoxtag->setCheckState(state?Qt::Checked:Qt::Unchecked);
}

bool FilterDialog::getEnabletag()
{
    return (ui->checkBoxtag->checkState() == Qt::Checked);
}

void FilterDialog::setProcessId(QString id)
{
    ui->lineEditProcessId->setText(id);
}

QString FilterDialog::getProcessId()
{
    return ui->lineEditProcessId->text();
}

void FilterDialog::setEnableProcessId(bool state)
{
    ui->checkBoxProcessId->setCheckState(state?Qt::Checked:Qt::Unchecked);
}

bool FilterDialog::getEnableProcessId()
{
    return (ui->checkBoxProcessId->checkState() == Qt::Checked);
}

void FilterDialog::setThreadId(QString id)
{
    ui->lineEditThreadId->setText(id);
}

QString FilterDialog::getThreadId()
{
    return ui->lineEditThreadId->text();
}

void FilterDialog::setEnableThreadId(bool state)
{
    ui->checkBoxThreadId->setCheckState(state?Qt::Checked:Qt::Unchecked);
}

bool FilterDialog::getEnableThreadId()
{
    return (ui->checkBoxThreadId->checkState() == Qt::Checked);
}

void FilterDialog::setHeaderText(QString id)
{
    ui->lineEditHeaderText->setText(id);
}

QString FilterDialog::getHeaderText()
{
    return ui->lineEditHeaderText->text();
}

void FilterDialog::setEnableHeaderText(bool state)
{
    ui->checkBoxHeaderText->setCheckState(state?Qt::Checked:Qt::Unchecked);
}

bool FilterDialog::getEnableHeaderText()
{
    return (ui->checkBoxHeaderText->checkState() == Qt::Checked);
}

void FilterDialog::setPayloadText(QString id)
{
    ui->lineEditPayloadText->setText(id);
}

QString FilterDialog::getPayloadText()
{
    return ui->lineEditPayloadText->text();
}

void FilterDialog::setEnablePayloadText(bool state)
{
    ui->checkBoxPayloadText->setCheckState(state?Qt::Checked:Qt::Unchecked);
}

bool FilterDialog::getEnablePayloadText()
{
    return (ui->checkBoxPayloadText->checkState() == Qt::Checked);
}


void FilterDialog::setEnableMessageId(bool state)
{
    ui->checkBoxMessageId->setCheckState(state?Qt::Checked:Qt::Unchecked);
}

bool FilterDialog::getEnableMessageId()
{
    return (ui->checkBoxMessageId->checkState() == Qt::Checked);
}

unsigned int  FilterDialog::getMessageId_min()
{
    return msgIdMin;
}

unsigned int  FilterDialog::getMessageId_max()
{
    if (msgIdMax==msgIdMin) return 0;
    return msgIdMax;
}

void FilterDialog::setMessageId_min(unsigned int min)
{
    ui->lineEdit_msgIdMin->setText(QString("%1").arg(min));
}

void FilterDialog::setMessageId_max(unsigned int max)
{
    ui->lineEdit_msgIdMax->setText(QString("%1").arg(max));
}

void FilterDialog::setFilterColour(QColor color)
{
   QPalette palette = ui->labelSelectedColor->palette();
   palette.setColor(QPalette::Active,this->backgroundRole(),color);
   palette.setColor(QPalette::Inactive,this->backgroundRole(),QColor(255,255,255,255));
   palette.setColor(QPalette::WindowText,DltUiUtils::optimalTextColor(color));
   ui->labelSelectedColor->setPalette(palette);

}

QString FilterDialog::getFilterColour()
{
    return ui->labelSelectedColor->palette().window().color().name();
}

void FilterDialog::setLogLevelMax(int value)
{
    ui->comboBoxLogLevelMax->setCurrentIndex(value);
}

int FilterDialog::getLogLevelMax()
{
    return ui->comboBoxLogLevelMax->currentIndex();
}

void FilterDialog::setEnableLogLevelMax(bool state)
{
    ui->checkBoxLogLevelMax->setCheckState(state?Qt::Checked:Qt::Unchecked);
}

bool FilterDialog::getEnableLogLevelMax()
{
    return (ui->checkBoxLogLevelMax->checkState() == Qt::Checked);
}

void FilterDialog::setLogLevelMin(int value)
{
    ui->comboBoxLogLevelMin->setCurrentIndex(value);
}

int FilterDialog::getLogLevelMin()
{
    return ui->comboBoxLogLevelMin->currentIndex();
}

void FilterDialog::setEnableLogLevelMin(bool state)
{
    ui->checkBoxLogLevelMin->setCheckState(state?Qt::Checked:Qt::Unchecked);
}

bool FilterDialog::getEnableLogLevelMin()
{
    return (ui->checkBoxLogLevelMin->checkState() == Qt::Checked);
}

void FilterDialog::setEnableCtrlMsgs(bool state)
{
    ui->checkBoxCtrlMsgs->setCheckState(state?Qt::Checked:Qt::Unchecked);
}

bool FilterDialog::getEnableCtrlMsgs()
{
    return (ui->checkBoxCtrlMsgs->checkState() == Qt::Checked);
}

void FilterDialog::setActive(bool state){
    ui->checkBoxActive->setCheckState(state?Qt::Checked:Qt::Unchecked);
}

bool FilterDialog::getEnableActive(){
    return (ui->checkBoxActive->checkState() == Qt::Checked);
}

void FilterDialog::setEnableMarker(bool state){
    ui->groupBox_marker->setChecked(state);
    /* update ui */
}

bool FilterDialog::getEnableMarker(){
    return (ui->groupBox_marker->isCheckable()&&ui->groupBox_marker->isChecked());
}

void FilterDialog::setEnableRegexSearchReplace(bool state){
    return ui->checkBoxRegexSearchReplace->setChecked(state);
}

bool FilterDialog::getEnableRegexSearchReplace(){
    return ui->checkBoxRegexSearchReplace->checkState() == Qt::Checked;
}

void FilterDialog::setRegexSearchText(const QString& str){
    ui->lineEditRegexSearch->setText(str);
}

QString FilterDialog::getRegexSearchText(){
    return ui->lineEditRegexSearch->text();
}

void FilterDialog::setRegexReplaceText(const QString& str){
    ui->lineEditRegexReplace->setText(str);
}

QString FilterDialog::getRegexReplaceText(){
    return ui->lineEditRegexReplace->text();
}


void FilterDialog::on_buttonSelectColor_clicked()
{
    QColor selectedBackgroundColor = QColorDialog::getColor(this->getFilterColour());
    if(selectedBackgroundColor.isValid())
    {
        this->setFilterColour(selectedBackgroundColor);
    }
}

void FilterDialog::on_comboBoxType_currentIndexChanged(int index){
    Q_UNUSED(index);

    on_checkBoxMarkerClicked();
}


void FilterDialog::on_checkBoxMarkerClicked()
{
    int index = ui->comboBoxType->currentIndex();
    switch (index)
        {
            case 0: ui->pushButton_Positive->setChecked(true);break;
            case 1: ui->pushButton_Negative->setChecked(true);break;
            case 2: ui->pushButton_Marker->setChecked(true);break;
        }
    on_buttonGroup_filterType_buttonClicked( -1 );

}

void FilterDialog::on_lineEditProcessId_textEdited(const QString &)
{
  if (ui->lineEditProcessId->text().length())
    ui->checkBoxProcessId->setCheckState(Qt::Checked);
  else
    ui->checkBoxProcessId->setCheckState(Qt::Unchecked);
}

void FilterDialog::on_lineEdittag_textEdited(const QString &)
{
  if (ui->lineEdittag->text().length())
    ui->checkBoxtag->setCheckState(Qt::Checked);
  else
    ui->checkBoxtag->setCheckState(Qt::Unchecked);
}

void FilterDialog::on_lineEditThreadId_textEdited(const QString &)
{
  if (ui->lineEditThreadId->text().length())
    ui->checkBoxThreadId->setCheckState(Qt::Checked);
  else
    ui->checkBoxThreadId->setCheckState(Qt::Unchecked);
}

void FilterDialog::on_lineEditHeaderText_textEdited(const QString &)
{
  if (ui->lineEditHeaderText->text().length())
    ui->checkBoxHeaderText->setCheckState(Qt::Checked);
  else
    ui->checkBoxHeaderText->setCheckState(Qt::Unchecked);
}

void FilterDialog::on_lineEditPayloadText_textEdited(const QString &)
{
  if (ui->lineEditPayloadText->text().length())
    ui->checkBoxPayloadText->setCheckState(Qt::Checked);
  else
    ui->checkBoxPayloadText->setCheckState(Qt::Unchecked);
}

void FilterDialog::on_comboBoxLogLevelMax_currentIndexChanged(int )
{
    ui->checkBoxLogLevelMax->setCheckState(Qt::Checked);
}

void FilterDialog::on_comboBoxLogLevelMin_currentIndexChanged(int )
{
    ui->checkBoxLogLevelMin->setCheckState(Qt::Checked);
}

void FilterDialog::on_checkRegex(const QString&)
{
    if (ui->lineEditRegexSearch->text().length() || ui->lineEditRegexReplace->text().length())
        ui->checkBoxRegexSearchReplace->setCheckState(Qt::Checked);
    else
        ui->checkBoxRegexSearchReplace->setCheckState(Qt::Unchecked);
}

void FilterDialog::validate()
{
    QString
    error =  "Could not parse %1 regular expression. \n";
    error += "Please correct the error or remove the regular expression.\n";
    error += "Expression: '%2' \n";
    error += "Error: %3 ";

    if (!getEnableRegexp_Procid() && 4 < ui->lineEditProcessId->text().length())
    {
      ui->lineEditProcessId->selectAll();
      QMessageBox::warning(this, "Warning", "Process Id is more than four characters in length (and not in RegExp mode).");
      ui->lineEditProcessId->setFocus();
      return;
    }

    if(!(getEnableRegexp_Context()||getEnableRegexp_Header()||getEnableRegexp_Payload()))
    {
        emit accept();
        return;
    }

    QRegularExpression rx;
    rx.setPattern(getPayloadText());
    if(!rx.isValid()) {
        QMessageBox::warning(this, "Warning", error.arg("PAYLOAD").arg(rx.pattern()).arg(rx.errorString()));
        return;
    }

    rx.setPattern(getHeaderText());
    if(!rx.isValid()) {
        QMessageBox::warning(this, "Warning", error.arg("HEADER").arg(rx.pattern()).arg(rx.errorString()));
        return;
    }

    rx.setPattern(getThreadId());
    if(!rx.isValid()) {
        QMessageBox::warning(this, "Warning", error.arg("THREADID").arg(rx.pattern()).arg(rx.errorString()));
        return;
    }

    emit accept();
}


void FilterDialog::on_pushButton_c0_clicked() { setFilterColour(((QPushButton *)sender())->palette().window().color());}
void FilterDialog::on_pushButton_c1_clicked() { setFilterColour(((QPushButton *)sender())->palette().window().color());}
void FilterDialog::on_pushButton_c2_clicked() { setFilterColour(((QPushButton *)sender())->palette().window().color());}
void FilterDialog::on_pushButton_c3_clicked() { setFilterColour(((QPushButton *)sender())->palette().window().color());}
void FilterDialog::on_pushButton_c4_clicked() { setFilterColour(((QPushButton *)sender())->palette().window().color());}
void FilterDialog::on_pushButton_c5_clicked() { setFilterColour(((QPushButton *)sender())->palette().window().color());}
void FilterDialog::on_pushButton_c6_clicked() { setFilterColour(((QPushButton *)sender())->palette().window().color());}
void FilterDialog::on_pushButton_c7_clicked() { setFilterColour(((QPushButton *)sender())->palette().window().color());}
void FilterDialog::on_pushButton_c8_clicked() { setFilterColour(((QPushButton *)sender())->palette().window().color());}
void FilterDialog::on_pushButton_c9_clicked() { setFilterColour(((QPushButton *)sender())->palette().window().color());}
void FilterDialog::on_pushButton_c10_clicked(){ setFilterColour(((QPushButton *)sender())->palette().window().color());}

void FilterDialog::on_buttonGroup_filterType_buttonClicked( int id )
{
    Q_UNUSED(id)
    int i = -1;
    if (ui->pushButton_Marker->isChecked())
      {
       ui->groupBox_marker->setEnabled(true);
       i = ui->comboBoxType->findText("marker");
       if (i != -1)
           ui->comboBoxType->setCurrentIndex(i);
       ui->groupBox_marker->setChecked(true);
       ui->groupBox_marker->setCheckable(false);
      }
    else
    {
        ui->groupBox_marker->setCheckable(true);
    }
    if ( ui->pushButton_Negative->isChecked())
      {
        ui->groupBox_marker->setEnabled(false);
        i = ui->comboBoxType->findText("negative");
        if (i != -1)
            ui->comboBoxType->setCurrentIndex(i);
        ui->groupBox_marker->setChecked(false);
        ui->groupBox_marker->setCheckable(false);

      }
    if (ui->pushButton_Positive->isChecked())
      {
        ui->groupBox_marker->setEnabled(true);
        i = ui->comboBoxType->findText("positive");
        if (i != -1)
            ui->comboBoxType->setCurrentIndex(i);
        ui->groupBox_marker->setCheckable(true);
        ui->groupBox_marker->setChecked(false);
      }
}


void FilterDialog::checkMsgIdValid(const QString&)
{

    QString hint;
    QString rule="<= ID < ";
    bool ok_min;
    bool ok_max;

    msgIdMin = ui->lineEdit_msgIdMin->text().toUInt(&ok_min,10);
    if (ok_min)
        {
            ui->lineEdit_msgIdMin->setStyleSheet("border: 2px solid blue");
        }
    else
        {
            msgIdMin = ui->lineEdit_msgIdMin->text().toUInt(&ok_min,16);
            ui->lineEdit_msgIdMin->setStyleSheet("border: 2px solid green");
        }
    if (!ok_min)
        {
            ui->lineEdit_msgIdMin->setStyleSheet("border: 2px solid red");
        }

    msgIdMax = ui->lineEdit_msgIdMax->text().toUInt(&ok_max,10);
    if (ok_max)
        {
            ui->lineEdit_msgIdMax->setStyleSheet("border: 2px solid blue");
        }
    else
        {
            msgIdMax = ui->lineEdit_msgIdMax->text().toUInt(&ok_max,16);
            ui->lineEdit_msgIdMax->setStyleSheet("border: 2px solid green");
        }
    if (!ok_max)
        {
            ui->lineEdit_msgIdMax->setStyleSheet("border: 2px solid red");
        }

    if ((!ok_max) && (!ok_min))
        {
            hint.append("[MIN & MAX invalid]");
        }
    else
        {
            if (!ok_min)
                hint.append("[MIN invalid]");
            if (!ok_max)
                hint.append("[MAX invalid]");
        }
    if (msgIdMax==0)
        {
            rule="== ID //";
            ui->lineEdit_msgIdMax->setStyleSheet("border: 2px solid grey");
        }
    else
        if (msgIdMin>=msgIdMax)
            {
                ui->lineEdit_msgIdMax->setStyleSheet("border: 2px dotted grey");
                hint.append("[MAX<=MIN !]");
                rule= "== ID //";
            }
    if (ui->checkBoxMessageId->checkState()==Qt::Checked)
        {
            ui->plainTextEdit_msgIdRule->setVisible(true);
        }
    else
        {
            ui->plainTextEdit_msgIdRule->setVisible(false);
            ui->lineEdit_msgIdMax->setStyleSheet("border: 1px solid black");
            ui->lineEdit_msgIdMin->setStyleSheet("border: 1px solid black");
        }

     ui->plainTextEdit_msgIdRule->setPlainText(
                QString("%1  %2 %3 %7 \n0x%4  %5 0x%6").\
                arg(msgIdMin,10,10,QLatin1Char(' ')).arg(rule).arg(msgIdMax,10,10,QLatin1Char(' ')).\
                arg(msgIdMin, 8,16,QLatin1Char('0')).arg(rule).arg(msgIdMax, 8,16,QLatin1Char('0')).\
                arg(hint)\
                );

}

void FilterDialog::on_checkboxMessageId_stateChanged(int)
    {
        checkMsgIdValid("");
    }
